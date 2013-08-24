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
        m_bRadarVisible(true),
		m_bAdvancedControlState(true),
		m_bAdvancedCameraState(true),
		m_bParachuteCheck(false),
		m_bParachuteIntitialised(false)
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

	// Reset parachute
	m_bParachuteCheck = false;
	
	// Fade screen in
	if(m_bFirstSpawn)
		CIVScript::DoScreenFadeIn(1000);

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
		g_pCore->GetChat()->Outputf(false, "HandleDeath(LocalPlayer, %d, %d, %d)", playerId, vehicleId, weaponId);

		// Send the death notification to the server
		CBitStream bsSend;
		bsSend.WriteCompressed(playerId);
		bsSend.WriteCompressed(vehicleId);
		bsSend.WriteCompressed(weaponId);
		//g_pCore->GetNetworkManager()->Call(NULL, &bsSend, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, 0, false);

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
	CPlayerEntity::Process();

	if(IsSpawned()) {
		DoDeathCheck();
		
		if(!m_bParachuteCheck) {

			// Create "simulated" parachute
			CIVScript::GiveWeaponToChar(GetScriptingHandle(), 41, 1, false);
			DWORD dwParachute = 0x4C19FE43; //0x402B7648;
			CVector3 vecCurrPos;
			GetPosition(vecCurrPos);

			CIVScript::CreateObject(dwParachute, vecCurrPos.fX, vecCurrPos.fY, -25.0 , &m_pObj, 1);
			CIVScript::SetObjectDynamic(m_pObj, 1);
			CIVScript::SetObjectCollision(m_pObj, 1);
			CIVScript::SetObjectVisible(m_pObj, 0);
			CIVScript::SetActivateObjectPhysicsAsSoonAsItIsUnfrozen(m_pObj, 1);
			CIVScript::AttachObjectToPed(m_pObj, GetScriptingHandle(), 1202, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 1);

			m_bParachuteCheck = true;
		}

		if(!m_bParachuteIntitialised)
		{
			//g_pCore->GetGame()->OnClientPastGameJoin();
			m_bParachuteIntitialised = true;
		}
	}
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
		// Toggle controls
		if(bControl != m_bAdvancedControlState)
		{
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
	//return (unsigned short)g_pCore->GetNetworkManager()->GetNetClient()->GetLastPing();
	return 0;
}

void CLocalPlayer::Reset()
{
    m_bFirstSpawn = false;
    m_bFinishedInitialize = false;
    m_bSpawnMarked = false;
}
