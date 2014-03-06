/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CLocalPlayer.h"
#include "Game/CGameFuncs.h"
#include <CCore.h>
#include <Game/EFLC/CScript.h>
#include <Game/CGameFuncs.h>

extern CCore *	 g_pCore;
extern bool      g_bControlsDisabled;

#define CPlayerPed__Respawn ((void(__cdecl *) (EFLC::IPhysical* pPhysical, CVector3 * vecSpawnPosition, float fHeading))(g_pCore->GetBase() + 0x7D5220))
#define g_pPlayerInfos ((DWORD *) (g_pCore->GetBase() + 0x10D9458)) //playerPool ?
#define LocalPlayerID (*(DWORD *) (g_pCore->GetBase() + 0xF16134)) //localPlayerId ?

bool isHandleLocalPlayerSpawnAlreadyCalled = false;

void HandleLocalPlayerSpawn()
{
	_asm pushad;

	if (!isHandleLocalPlayerSpawnAlreadyCalled)
	{
		g_pCore->GetGame()->GetLocalPlayer()->HandleSpawn();
		isHandleLocalPlayerSpawnAlreadyCalled = true;
	}
	else
	{
		if (LocalPlayerID != -1)
			CPlayerPed__Respawn(*(EFLC::IPhysical* *) (((unsigned char*)g_pPlayerInfos[LocalPlayerID]) + 1420), &(CVector3(0.0f, 0.0f, 0.0f)), 0.0f);
	}
	g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_REQUEST_SPAWN), NULL, HIGH_PRIORITY, RELIABLE, true);

	_asm popad;
}

CLocalPlayer::CLocalPlayer() : CPlayerEntity(true),
		m_bIsDead(false),
        m_bToggleControl(true),
        m_fSpawnAngle(0),
        m_ulLastPureSyncTime(0),
        m_uiLastInterior(0),
        m_bDisableVehicleInfo(false),
        m_bFirstSpawn(false),
        m_bFinishedInitialize(false),
        m_bRadarVisible(true),
		m_bAdvancedControlState(true),
		m_bAdvancedCameraState(true)
{
	// Patch to override spawn position and let the game call HandleSpawn
	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x7D5BAD, (DWORD) HandleLocalPlayerSpawn);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x7D5BB2, g_pCore->GetBase() + 0x7D5C77);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x7D5D3C, g_pCore->GetBase() + 0x7D5D49);

	// Patch death loading screen slow motion :D
	CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchDeathLoadingScreen, 24);
}

void CLocalPlayer::Respawn()
{
	// Get current day time so we don't have to set the time always..
	CGameFunction::GetTime(&m_iRespawnTime[0], &m_iRespawnTime[1]);

    // Set the local player state to respawning
    *(DWORD *)COffsets::VAR_LocalPlayerState = 5;
}

void CLocalPlayer::HandleSpawn()
{
    // Flag us as alive
    CLocalPlayer::m_bIsDead = false;

	// Set our current time
	CGameFunction::SetTimeOfDay(m_iRespawnTime[0],m_iRespawnTime[1]);

	// Reset vehicle enter/exit
	ResetVehicleEnterExit();

	// Set first spawn
	m_bFirstSpawn = true;
}

void CLocalPlayer::DoDeathCheck()
{
	// Have we not yet processed the death and is the local player dead?
	if(!m_bIsDead && IsDead())
	{
		// Get the kill info
		EntityId playerId = INVALID_ENTITY_ID;
		EntityId vehicleId = INVALID_ENTITY_ID;
		EntityId weaponId = INVALID_ENTITY_ID;
		GetKillInfo(playerId, vehicleId,weaponId);

		CLogFile::Printf("HandleDeath(LocalPlayer, %d, %d, %d)", playerId, vehicleId, weaponId);
		g_pCore->GetGraphics()->GetChat()->Print(CString("HandleDeath(LocalPlayer, %d, %d, %d)", playerId, vehicleId, weaponId));

		// Send the death notification to the server
		BitStream bsSend;
		bsSend.Write(playerId);
		bsSend.Write(vehicleId);
		bsSend.Write(weaponId);
		g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_DEATH), &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, true);

		// Mark ourselves as dead
		m_bIsDead = true;

		if (GetVehicle())
			RemoveFromVehicle();

		// Get current day time so we don't have to set the time always..
		CGameFunction::GetTime(&m_iRespawnTime[0], &m_iRespawnTime[1]);
	}
}
	
#define SYNC_PACKETS_PER_SECOND 50

bool CLocalPlayer::IsFullSyncNeeded()
{
	unsigned long ulCurrentTime = SharedUtility::GetTime();
	if (ulCurrentTime >= m_ulLastPureSyncTime + (1000.0f / SYNC_PACKETS_PER_SECOND))
	{
		m_ulLastPureSyncTime = ulCurrentTime;
		return true;
	}

	return false;
}

void CLocalPlayer::CheckVehicleEnterExit()
{
	// Are we spawned?
	if (IsSpawned() && g_pCore->GetGame()->GetLocalPlayer()->GetAdvancedControlState())
	{

		// Are we not in a vehicle?
		if (!InternalIsInVehicle())
		{
			if (m_pVehicleEnterExit->bEntering)
			{
				// Is the flag wrong (did the player cancel entering ?)
				if (!IsGettingIntoAVehicle())
				{
					if (IsLocalPlayer())
					{
						g_pCore->GetGraphics()->GetChat()->Print("VehicleEntryAborted");
						m_pVehicleEnterExit->bEntering = false;
					}
				}
			}
			CControlState controlState;

			GetControlState(&controlState);
			
			// Has the enter/exit vehicle key been pressed?
			if (controlState.IsUsingEnterExitVehicle() || controlState.IsUsingHorn())
			{
				// Are we not already requesting an enter?
				if (!m_pVehicleEnterExit->bEntering)
				{
					CVehicleEntity * pVehicle = nullptr;
					BYTE byteSeat = 0;
					bool bFound = GetClosestVehicle(controlState.IsUsingHorn(), &pVehicle, byteSeat);

					// Have we found a vehicle?
					if (bFound)
					{
						if (GetVehicle())
							m_pVehicle = nullptr;

						// Enter the vehicle
						EnterVehicle(pVehicle, byteSeat);

						// Send to the server
						RakNet::BitStream bitStream;
						bitStream.Write(m_pVehicleEnterExit->pVehicle->GetId());
						bitStream.Write(byteSeat);
						g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_ENTER_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);

						g_pCore->GetGraphics()->GetChat()->Print(CString("HandleVehicleEntry(%d, %d)", pVehicle->GetId(), byteSeat));
					}
				}
			}
		}
		else
		{
			CControlState controlState;

			GetControlState(&controlState);

			// Has the enter/exit vehicle key been pressed?
			if (controlState.IsUsingEnterExitVehicle())
			{
				// Are we not already requesting an exit?
				if (!m_pVehicleEnterExit->bExiting)
				{
					// Exit the vehicle
					ExitVehicle(EXIT_VEHICLE_NORMAL);

					// Send to the server
					RakNet::BitStream bitStream;
					bitStream.Write(GetVehicle()->GetId());
					bitStream.Write(GetSeat());
					g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_EXIT_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);

					g_pCore->GetGraphics()->GetChat()->Print(CString("HandleVehicleExit(%d, %d)", GetVehicle()->GetId(), GetSeat()));
				}
			}
		}
	}
}

void CLocalPlayer::ProcessVehicleEnterExit()
{
	// Are we spawned?
	if (IsSpawned())
	{
		// Are we internally in a vehicle?
		if (InternalIsInVehicle())
		{
			// Are we flagged as entering a vehicle?
			if (m_pVehicleEnterExit->bEntering)
			{
				// Has the enter vehicle task finished?
				if (!IsGettingIntoAVehicle())
				{
					// Vehicle entry is complete
					m_pVehicleEnterExit->pVehicle->SetOccupant(m_pVehicleEnterExit->byteSeat, this);

					// Store the vehicle
					m_pVehicle = m_pVehicleEnterExit->pVehicle;

					// Store the seat
					m_byteSeat = m_pVehicleEnterExit->byteSeat;

					// Reset vehicle enter/exit
					ResetVehicleEnterExit();

					// We dont have to send it to the server its handled automatically by the sync

					g_pCore->GetGraphics()->GetChat()->Print("VehicleEntryComplete()");
				}
			}
		}
		else
		{
			// Are we flagged as exiting?
			if (m_pVehicleEnterExit->bExiting)
			{
				// Has the exit vehicle task finished?
				if (!IsGettingOutOfAVehicle())
				{
					// Reset vehicle enter/exit
					ResetVehicleEnterExit();

					// We dont have to send it to the server its handled automatically by the sync

					g_pCore->GetGraphics()->GetChat()->Print("VehicleExitComplete()");
				}
			}
		}
	}
}

void CLocalPlayer::Pulse()
{
	if (IsSpawned())
	{
		DoDeathCheck();

		CControlState controlState;
		GetControlState(&controlState);
		SetLastControlState(controlState);

		// Update the current control state
		
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(controlState);
		SetControlState(&controlState);

		// Check vehicle enter/exit
		CheckVehicleEnterExit();

		// Process vehicle enter/exit
		ProcessVehicleEnterExit();

		if (IsFullSyncNeeded())
		{
			RakNet::BitStream bitStream;
			Serialize(&bitStream);

			// Send package to network
			g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), &bitStream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, true);
/*
#ifdef TASKINFO_TEST
			bitStream.Reset();
			SerializeTaskInfo(&bitStream);

			if (g_pCore->GetGame()->GetPlayerManager())
			if (g_pCore->GetGame()->GetPlayerManager()->GetAt(1))
				g_pCore->GetGame()->GetPlayerManager()->GetAt(1)->DeserializeTaskInfo(&bitStream);
#endif		*/		
		}
	}
}

void CLocalPlayer::SetPlayerControlAdvanced(bool bControl, bool bCamera, bool bForce)
{
	if(GetPlayerGameNumber() != INVALID_PLAYER_PED)
	{
		// Toggle controls
		if(bForce) 
		{
			// Apply current controls
			EFLC::CScript::SetPlayerControlAdvanced(GetPlayerGameNumber(), bControl, bControl, bControl);
			m_bAdvancedControlState = bControl;
			EFLC::CScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
			m_bAdvancedCameraState = bCamera;
			return;
		}

		if(bControl != m_bAdvancedControlState) 
		{

			// Apply current controls
			EFLC::CScript::SetPlayerControlAdvanced(GetPlayerGameNumber(), bControl, bControl, bControl);
			m_bAdvancedControlState = bControl;
		}
		
		// Toggle camera
		if(bCamera != m_bAdvancedCameraState) 
		{
			EFLC::CScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
			m_bAdvancedCameraState = bCamera;
		}
	}
}

void CLocalPlayer::ChangeNick(const CString &strNick)
{
	// Show the change in chat
	g_pCore->GetGraphics()->GetChat()->Print(CString("%s is now called %s", GetNick().Get(), strNick.Get()));

	// Assign the new nick to the local player
	SetNick(strNick);

	// Send the new nick to the server
	BitStream bitStream;
	bitStream.Write(strNick.Get());
	g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_NAME_CHANGE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);
}

unsigned short CLocalPlayer::GetPing()
{
	return (unsigned short)g_pCore->GetNetworkManager()->GetRakPeer()->GetLastPing(g_pCore->GetNetworkManager()->GetRakPeer()->GetMyGUID());
}

void CLocalPlayer::Reset()
{
    m_bFirstSpawn = false;
    m_bFinishedInitialize = false;
}
