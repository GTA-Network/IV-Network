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

void GetLocalPlayerSpawnPosition(int, CVector3 * vecSpawnPosition, float * fAngle)
{
    _asm	pushad;
 
	CLogFile::Printf("%s",__FUNCTION__);
	memcpy(vecSpawnPosition,&CVector3(DEVELOPMENT_SPAWN_POSITION),sizeof(CVector3));

    *fAngle = g_pCore->GetGame()->GetLocalPlayer()->GetSpawnRotation();

	_asm	popad;
}

void __declspec(naked) HandleLocalPlayerSpawn()
{
    _asm	pushad;

	CLogFile::Printf("%s",__FUNCTION__);
    g_pCore->GetGame()->GetLocalPlayer()->HandleSpawn();

    _asm	popad;
    _asm	jmp COffsets::FUNC_SpawnPlayer;
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
        m_bSpawnMarked(false),
        m_bRadarVisible(true)
{
	// Temporary spawn position for development
	m_vecSpawnPosition = CVector3(DEVELOPMENT_SPAWN_POSITION);

    // Patch to override spawn position and let the game call HandleSpawn
    CPatcher::InstallCallPatch(COffsets::FUNC_GetLocalPlayerSpawnPosition, (DWORD)GetLocalPlayerSpawnPosition, 5);
    CPatcher::InstallCallPatch(COffsets::CALL_SpawnLocalPlayer, (DWORD)HandleLocalPlayerSpawn, 5);
	
	// Patch death loading screen slow motion :D
	CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x874EF7),0x18);
}

void CLocalPlayer::Respawn()
{
	// Get current day time so we don't have to set the time always..
	DWORD m_dwRespawnTime = CGameFunction::GetTimeOfDay();

    // Set the local player state to respawning
    *(DWORD *)COffsets::VAR_LocalPlayerState = 5;
}

void CLocalPlayer::HandleSpawn()
{
    // Flag us as alive
    CLocalPlayer::m_bIsDead = false;

	// Set our current time
	CGameFunction::SetTimeOfDayFormat(m_dwRespawnTime);

	// Reset vehicle enter/exit
	ResetVehicleEnterExit();
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
		CBitStream bsSend;
		bsSend.WriteCompressed(playerId);
		bsSend.WriteCompressed(vehicleId);
		bsSend.WriteCompressed(weaponId);
		//g_pCore->GetNetworkManager()->Call(NULL, &bsSend, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, 0, false);

		// Mark ourselves as dead
		CLocalPlayer::m_bIsDead = true;

		// Reset vehicle entry/exit flags
		ResetVehicleEnterExit();
	}

}

void CLocalPlayer::Pulse()
{
	CPlayerEntity::Process();

	if(IsSpawned())
		DoDeathCheck();

	m_bSpawnMarked = true;
}

void CLocalPlayer::SetSpawnLocation(CVector3 vecPosition, float fHeading)
{
    m_vecSpawnPosition = vecPosition;
    m_fSpawnAngle = fHeading;
}

void CLocalPlayer::SetPlayerControlAdvanced(bool bControl, bool bCamera)
{
	if(GetPlayerGameNumber() != INVALID_PLAYER_PED)
	{
		CIVScript::SetPlayerControlAdvanced(GetPlayerGameNumber(), bControl, bControl, bControl);
		CIVScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
	}
}

unsigned short CLocalPlayer::GetPing()
{
	//return (unsigned short)g_pCore->GetNetworkManager()->GetNetClient()->GetLastPing();
	return 0;
}

void CLocalPlayer::Reset()
{
    m_bFirstSpawn = false;
    m_bFinishedInitialize = false;
    m_bSpawnMarked = false;
}