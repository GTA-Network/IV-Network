//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CLocalPlayer.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CLocalPlayer.h"
#include "Game/CGameFuncs.h"
#include <CCore.h>
#include <IV/CIVScript.h>
#include <Game/CGameFuncs.h>

extern CCore *	 g_pCore;
extern bool      g_bControlsDisabled;

#define sub_7D5220 ((void(__cdecl *) (IVPhysical* pPhysical, CVector3 * vecSpawnPosition, float fHeading))(g_pCore->GetBase() + 0x7D5220))
#define dword_10D9458 ((DWORD *) (g_pCore->GetBase() + 0x10D9458)) //playerPool ?
#define dword_F16134 (*(DWORD *) (g_pCore->GetBase() + 0xF16134)) //localPlayerId ?

bool isHandleLocalPlayerSpawnAlreadyCalled = false;

void HandleLocalPlayerSpawn()
{
	_asm pushad;

	CLogFile::Printf("%s", __FUNCTION__);

	if (!isHandleLocalPlayerSpawnAlreadyCalled)
	{
		g_pCore->GetGame()->GetLocalPlayer()->HandleSpawn();
		isHandleLocalPlayerSpawnAlreadyCalled = true;
	}
	else
	{
		if (dword_F16134 != -1)
			sub_7D5220(*(IVPhysical* *) (((unsigned char*) dword_10D9458[dword_F16134]) + 1420), &(CVector3(0.0f, 0.0f, 0.0f)), 0.0f);

		g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_REQUEST_SPAWN), NULL, HIGH_PRIORITY, RELIABLE, true);
	}

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

	// Force to draw components on slot 8(parachute etc.)
	int iResult;
    switch (CIVScript::GetCharDrawableVariation(GetScriptingHandle(), 1))
    {
        case 0: iResult = 1; break;
        case 1: iResult = 2; break;
        case 2: iResult = 2; break;
        case 3: iResult = 1; break;
        case 4: iResult = 1; break;
		default: break;
    }

	CIVScript::SetDrawPlayerComponent(8, 1); // special 3
	CIVScript::SetCharComponentVariation(GetScriptingHandle(), 8, iResult, 0);

	// Set basic skin in developmet mode
#ifdef _DEV
	SetPedClothes(1, 1);
	SetPedClothes(2, 1);
	SetPedClothes(3, 0);
#endif

	//g_pCore->GetMainMenu()->SetVisible(true);

	// Notify the server 
	g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_SPAWN), NULL, HIGH_PRIORITY, RELIABLE, true);
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
		g_pCore->GetChat()->Outputf(false, "HandleDeath(LocalPlayer, %d, %d, %d)", playerId, vehicleId, weaponId);

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
	
void CLocalPlayer::Pulse()
{
	CPlayerEntity::Pulse();

	if(IsSpawned())
		DoDeathCheck();
}

void CLocalPlayer::SetPlayerControlAdvanced(bool bControl, bool bCamera, bool bForce)
{
	if(GetPlayerGameNumber() != INVALID_PLAYER_PED)
	{
		// Toggle controls
		if(bForce) {
			// Apply current controls
			CIVScript::SetPlayerControlAdvanced(GetPlayerGameNumber(), bControl, bControl, bControl);
			m_bAdvancedControlState = bControl;
			CIVScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
			m_bAdvancedCameraState = bCamera;
			return;
		}

		if(bControl != m_bAdvancedControlState) {

			// Check if our player is driver of a vehicle
			if(GetVehicleEntity() && GetVehicleEntity()->GetDriver() == reinterpret_cast<CPlayerEntity*>(this))
				if(!bControl)
					return;

			// Apply current controls
			CIVScript::SetPlayerControlAdvanced(GetPlayerGameNumber(), bControl, bControl, bControl);
			m_bAdvancedControlState = bControl;
		}
		
		// Toggle camera
		if(bCamera != m_bAdvancedCameraState) {
			CIVScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
			m_bAdvancedCameraState = bCamera;
		}
	}
}

unsigned short CLocalPlayer::GetPing()
{
	return static_cast<unsigned short>((unsigned short)g_pCore->GetNetworkManager()->GetRakPeer()->GetLastPing(g_pCore->GetNetworkManager()->GetRakPeer()->GetMyGUID()));
}

void CLocalPlayer::Reset()
{
    m_bFirstSpawn = false;
    m_bFinishedInitialize = false;
}
