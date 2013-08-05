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
//include "KeySync.h"

extern CCore *	 g_pCore;
extern bool      g_bControlsDisabled;

void GetLocalPlayerSpawnPosition(int, CVector3 * vecSpawnPosition, float * fAngle)
{
    _asm	pushad;
 
	CLogFile::Printf("%s",__FUNCTION__);
	vecSpawnPosition = &CVector3(DEVELOPMENT_SPAWN_POSITION);
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
}

void CLocalPlayer::Respawn()
{
    // Set the local player state to respawning
    *(DWORD *)COffsets::VAR_LocalPlayerState = 5;
}

void CLocalPlayer::HandleSpawn()
{
    // Flag us as alive
    m_bIsDead = false;

	// Preload world position
	/*CVector3 vecSpawnPosition;
	GetSpawnPosition(&vecSpawnPosition);
	CGameFunction::LoadWorldAtPosition(vecSpawnPosition);*/
}

void CLocalPlayer::DoDeathCheck()
{
    // Have we not yet processed the death and is the local player dead?
    if(!m_bIsDead && IsDead())
    {
        // Send the death notification to the server

        // Mark ourselves as dead
        m_bIsDead = true;
    }
}

void CLocalPlayer::Pulse()
{
	CPlayerEntity::Pulse();
	m_bSpawnMarked = true;
}

void CLocalPlayer::SetSpawnLocation(CVector3 vecPosition, float fHeading)
{
    m_vecSpawnPosition = vecPosition;
    m_fSpawnAngle = fHeading;
}

void CLocalPlayer::SetPlayerControlAdvanced(bool bControl, bool bCamera)
{
	CIVScript::SetPlayerControlAdvanced(GetScriptingHandle(), bControl, bControl, bControl);
	CIVScript::SetCameraControlsDisabledWithPlayerControls(!bCamera);
}

bool CLocalPlayer::IsDead()
{
	return false;
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