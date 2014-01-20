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
#include <IV/CIVScript.h>
#include <Game/CGameFuncs.h>

extern CCore *	 g_pCore;
extern bool      g_bControlsDisabled;

#define CPlayerPed__Respawn ((void(__cdecl *) (IVPhysical* pPhysical, CVector3 * vecSpawnPosition, float fHeading))(g_pCore->GetBase() + 0x7D5220))
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
			CPlayerPed__Respawn(*(IVPhysical* *) (((unsigned char*) g_pPlayerInfos[LocalPlayerID]) + 1420), &(CVector3(0.0f, 0.0f, 0.0f)), 0.0f);
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
	if(!CLocalPlayer::m_bIsDead && IsDead())
	{
		// Get the kill info
		EntityId playerId = INVALID_ENTITY_ID;
		EntityId vehicleId = INVALID_ENTITY_ID;
		EntityId weaponId = INVALID_ENTITY_ID;
		GetKillInfo(&playerId, &vehicleId,&weaponId);

		CLogFile::Printf("HandleDeath(LocalPlayer, %d, %d, %d)", playerId, vehicleId, weaponId);
		g_pCore->GetGraphics()->GetChat()->Print(CString("HandleDeath(LocalPlayer, %d, %d, %d)", playerId, vehicleId, weaponId));

		// Send the death notification to the server
		BitStream bsSend;
		bsSend.Write(playerId);
		bsSend.Write(vehicleId);
		bsSend.Write(weaponId);
		g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_DEATH), &bsSend, HIGH_PRIORITY, RELIABLE_ORDERED, true);

		// Mark ourselves as dead
		CLocalPlayer::m_bIsDead = true;

		// Delete the object
		CIVScript::DeleteObject(&m_pObj);

		// Reset vehicle entry/exit flags
		SetExitFlag(true);
		ResetVehicleEnterExit();

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

void CLocalPlayer::Pulse()
{
	if (IsSpawned())
	{
		DoDeathCheck();

		// Copy the current control state to the previous control state
		memcpy(&m_lastControlState, &m_ControlState, sizeof(CControlState));

		// Update the current control state
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(m_ControlState);

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
			CIVScript::SetPlayerControlAdvanced(GetPlayerGameNumber(), bControl, bControl, bControl);
			m_bAdvancedControlState = bControl;
			CIVScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
			m_bAdvancedCameraState = bCamera;
			return;
		}

		if(bControl != m_bAdvancedControlState) 
		{

			// Apply current controls
			CIVScript::SetPlayerControlAdvanced(GetPlayerGameNumber(), bControl, bControl, bControl);
			m_bAdvancedControlState = bControl;
		}
		
		// Toggle camera
		if(bCamera != m_bAdvancedCameraState) 
		{
			CIVScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
			m_bAdvancedCameraState = bCamera;
		}
	}
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
