//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CGame.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//=================================================================================================

#include "CGame.h"
#include <CCore.h>

#include <Game/IVEngine/CIVHud.h>
#include <Game/IVEngine/CIVWeather.h>
#include <Game/IVEngine/CIVModelInfo.h>

extern	CCore				* g_pCore;
extern bool					  g_bInvalidIndex;

CLocalPlayer				*CGame::m_pLocalPlayer = 0;
CIVPad						*CGame::m_pPad = 0;
CTaskManager				*CGame::m_pTaskManager = 0;
CPools						*CGame::m_pPool = 0;
CCamera						*CGame::m_pCamera = 0;
CPlayerManager				*CGame::m_pPlayerManager = 0;
CVehicleManager				*CGame::m_pVehicleManager = 0;
CActorManager				*CGame::m_pActorManager = 0;
CObjectManager				*CGame::m_pObjectManager = 0;
CFireManager				*CGame::m_pFireManager = 0;
CPickupManager				*CGame::m_pPickupManager = 0;
C3DLabelManager				*CGame::m_p3DLabelManager = 0;
CBlipManager				*CGame::m_pBlipManager = 0;
CCheckpointManager			*CGame::m_pCheckpointManager = 0;
CCharacterManager			*CGame::m_pCharacterManager = 0;
bool						CGame::m_LocalPlayerInitialised = 0;
CIVModelInfo				CGame::m_modelInfos[NUM_ModelInfos];
CIVWeaponInfo				CGame::m_weaponInfos[NUM_WeaponInfos];

/*
	==== Why WaitForGameStartup ====
	We can load/start the game in the background and request all resources while the player is in the main menu.
	So GTA IV loads all resources and when our player connects to a server, we have check if the game(resources are) is ready.
	If the Wrapperlist is ready, we can spawn the localplayer
*/
DWORD WINAPI WaitForGameStartup(LPVOID lpParam)
{
	return 1;
}

void CGame::Setup()
{
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WaitForGameStartup, 0, 0, 0); // Destroy Thread?(after he has finished)

	g_pCore->SetClientState(GAME_STATE_LOADING);

	// Create new civpad instance
	m_pPad = new CIVPad((IVPad *)(g_pCore->GetBase() + 0x10FB818));

	// Create task manager instance
	m_pTaskManager = new CTaskManager;

	// Create the character manager instance
	m_pCharacterManager = new CCharacterManager;

	// Create new pool instance
	m_pPool = new CPools;
	
	// Initialise our model info array
	for(int i = 0; i < NUM_ModelInfos; i++)
		m_modelInfos[i].SetIndex(i);
		
	// Initialize our weapon info array
	for(int i = 0; i < NUM_WeaponInfos; i++)
	{
		m_weaponInfos[i].SetType((eWeaponType)i);
		m_weaponInfos[i].SetWeaponInfo((IVWeaponInfo *)((g_pCore->GetBase() + ARRAY_WeaponInfos) + (i * sizeof(IVWeaponInfo))));
	}

	// Hide the chat
	g_pCore->GetChat()->SetVisible (false);
}

void CGame::Initialise()
{
	// Update client state to state ingame
	g_pCore->SetClientState(GAME_STATE_INGAME);

	// Initialise/Patch our pools(IVPed,IVVehicle,IVTask)
	m_pPool->Initialise();

	// Create our camera instance if it doesn't exist/isn't created yet
	CCamera * pCamera = new CCamera;
	if(!m_pCamera)
		m_pCamera = pCamera;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pPlayerManager)
		m_pPlayerManager = new CPlayerManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pVehicleManager)
		m_pVehicleManager = new CVehicleManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pActorManager)
		m_pActorManager = new CActorManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pObjectManager)
		m_pObjectManager = new CObjectManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pFireManager)
		m_pFireManager = new CFireManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pPickupManager)
		m_pPickupManager = new CPickupManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_p3DLabelManager)
		m_p3DLabelManager = new C3DLabelManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pBlipManager)
		m_pBlipManager = new CBlipManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pCheckpointManager)
		m_pCheckpointManager = new CCheckpointManager;

	// Show the chat
	g_pCore->GetChat()->SetVisible (true);
	
	OnEnvironmentStartUp(false);

	PrepareWorld();
}

void CGame::OnEnvironmentStartUp(bool bForce)
{
	IVPlayerInfo * pPlayerInfo = m_pPool->GetPlayerInfoFromIndex(0);
	IVPlayerPed  * _pPlayerPed = NULL;

	if(pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else
		_pPlayerPed = NULL;

	if(!g_bInvalidIndex || m_pPool->GetLocalPlayerIndex() == -1)
	{
		if(!bForce)
			return;
	}

	m_LocalPlayerInitialised = !m_LocalPlayerInitialised;

	CLogFile::Printf("[%s] GetLocalPlayerPed returns %d -> Valid -> Patching...", __FUNCTION__, g_bInvalidIndex);
	CLogFile::Printf("[%s] Creating Player..",__FUNCTION__);

	if(!m_pLocalPlayer)
		m_pLocalPlayer = new CLocalPlayer;
	
	m_pLocalPlayer->Reset();
	m_pLocalPlayer->SetSpawnLocation(CVector3(DEVELOPMENT_SPAWN_POSITION),0.0f);
	m_pLocalPlayer->SetPosition(CVector3(DEVELOPMENT_SPAWN_POSITION));

	CLogFile::Printf("[%s] Successfully create local player instance..",__FUNCTION__);
}

void CGame::Reset()
{
	// Disconnect from network
	g_pCore->GetNetworkManager()->Disconnect();

	// Delte our instance if it exists/is created
	if(m_pCamera)
		SAFE_DELETE(m_pCamera);

	// Delte our instance if it exists/is created
	if(m_pPlayerManager)
		SAFE_DELETE(m_pPlayerManager);

	// Delte our instance if it exists/is created
	if(m_pVehicleManager)
		SAFE_DELETE(m_pVehicleManager);

	// Delte our instance if it exists/is created
	if(!m_pActorManager)
		SAFE_DELETE(m_pActorManager);

	// Delte our instance if it exists/is created
	if(!m_pObjectManager)
		SAFE_DELETE(m_pObjectManager);

	// Delte our instance if it exists/is created
	if(!m_pFireManager)
		SAFE_DELETE(m_pFireManager);

	// Delte our instance if it exists/is created
	if(!m_pPickupManager)
		SAFE_DELETE(m_pPickupManager);

	// Delte our instance if it exists/is created
	if(!m_p3DLabelManager)
		SAFE_DELETE(m_p3DLabelManager);

	// Delte our instance if it exists/is created
	if(!m_pBlipManager)
		SAFE_DELETE(m_pBlipManager);

	// Delte our instance if it exists/is created
	if(!m_pCheckpointManager)
		SAFE_DELETE(m_pCheckpointManager);

	// Re-initialse our client
	Initialise();

	// Prepare our world
	PrepareWorld();
}

void CGame::UnprotectMemory()
{
	BYTE * pImageBase = (BYTE *)(g_pCore->GetBase() + 0x400000);
	PIMAGE_DOS_HEADER   pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	PIMAGE_NT_HEADERS   pNtHeader  = (PIMAGE_NT_HEADERS)(pImageBase + pDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHeader);

	for(int iSection = 0; iSection < pNtHeader->FileHeader.NumberOfSections; iSection++, pSection++)
	{
		char * pszSectionName = (char *)pSection->Name;

		if(!strcmp(pszSectionName, ".text") || !strcmp(pszSectionName, ".rdata"))
			CPatcher::Unprotect((DWORD)(pImageBase + pSection->VirtualAddress), ((pSection->Misc.VirtualSize + 4095) & ~4095));
	}
}

void CGame::RenderRAGEScripts()
{
	// If our loacl player isn't create, try to create it
	if(!m_LocalPlayerInitialised)
		OnEnvironmentStartUp(true);

	// If our network manager exists process it
	if(g_pCore->GetNetworkManager())
		g_pCore->GetNetworkManager()->Process();

	// If our local player exists, pulse him
	if(m_pLocalPlayer)
		m_pLocalPlayer->Process();
	
}

void CGame::PrepareWorld()
{
	CIVHud::SetHudVisible(false);
	CIVHud::SetRadarVisible(false);
	CIVHud::SetAreaNamesEnabled(false);
	CIVHud::SetPlayerNamesVisible(0);

	CIVWeather::SetWeather(WEATHER_SUNNY);
	CIVWeather::SetTime(0, 0);

	CGameFunction::LoadWorldAtPosition(CVector3(GAME_LOAD_CAMERA_POS));
	m_pCamera->SetCameraPosition(CVector3(GAME_LOAD_CAMERA_POS));
	m_pCamera->SetLookAtPosition(CVector3(GAME_LOAD_CAMERA_LOOKAT));

	g_pCore->GetChat()->Output("Enter /spawn to spawn your local player ...",false);
}

void CGame::OnClientReadyToGamePlay()
{
	m_pLocalPlayer->Teleport(CVector3(DEVELOPMENT_SPAWN_POSITION));

	m_pCamera->SetCamBehindPed(m_pLocalPlayer->GetScriptingHandle());

	CIVWeather::SetTime(8,0);
}

CIVModelInfo * CGame::GetModelInfo(int iModelIndex)
{
	if(iModelIndex < NUM_ModelInfos && iModelIndex >= 0 && m_modelInfos[iModelIndex].IsValid())
		return &m_modelInfos[iModelIndex];

	return NULL;
}

CIVWeaponInfo * CGame::GetWeaponInfo(eWeaponType weaponType)
{
    if(weaponType < NUM_WeaponInfos && weaponType >= 0)
            return &m_weaponInfos[weaponType];

    return NULL;
}

bool CGame::CheckInstances(bool bInitialised)
{
	// Check Pools
	if(!bInitialised)
	{
		CHECK_PTR(m_pPool);
		CHECK_PTR(m_pPad);
		CHECK_PTR(m_pTaskManager);
		CHECK_PTR(m_pCharacterManager);
		CHECK_PTR(m_pCamera);
	}
	else if(bInitialised)
	{
		CHECK_PTR(m_pPool);
		CHECK_PTR(m_pPad);
		CHECK_PTR(m_pTaskManager);
		CHECK_PTR(m_pCharacterManager);
		CHECK_PTR(m_pCamera);
		CHECK_PTR(m_pLocalPlayer);

		CHECK_PTR(m_pPlayerManager);
		CHECK_PTR(m_pVehicleManager);
		CHECK_PTR(m_pActorManager);
		CHECK_PTR(m_pObjectManager);
		CHECK_PTR(m_pFireManager);
		CHECK_PTR(m_pPickupManager);
		CHECK_PTR(m_p3DLabelManager);
		CHECK_PTR(m_pBlipManager);
		CHECK_PTR(m_pCheckpointManager);
		CHECK_PTR(m_pCharacterManager);
	}

	return true;
}