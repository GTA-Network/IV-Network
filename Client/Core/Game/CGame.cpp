//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CGame.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CGame.h"
#include <CCore.h>

#include <Game/IVEngine/CIVHud.h>
#include <Game/IVEngine/CIVWeather.h>
#include <Game/IVEngine/CIVModelInfo.h>

extern	CCore				* g_pCore;

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
	//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WaitForGameStartup, 0, 0, 0); // Remove Thread?

	g_pCore->SetClientState(GAME_STATE_LOADING);

	if(!m_pLocalPlayer)
		m_pLocalPlayer = new CLocalPlayer;

	// Add our local player into the playermanager
	/*EntityId findId = m_pPlayerManager->FindFreeSlot();
	if(findId != INVALID_ENTITY_ID)
		m_pPlayerManager->Add(findId,NULL);*/
	
	//m_pLocalPlayer->SetPlayerId(findId);
	m_pLocalPlayer->Reset();
	m_pLocalPlayer->SetSpawnLocation(DEVELOPMENT_SPAWN_POSITION,0.0f);

	// Create new civpad instance
	m_pPad = new CIVPad((IVPad *)(g_pCore->GetBase() + 0x10FB818));

	// Create task manager instance
	m_pTaskManager = new CTaskManager();

	// Create new pool instance
	m_pPool = new CPools();
}

void CGame::Initialise()
{
	// Update client state to state ingame
	g_pCore->SetClientState(GAME_STATE_INGAME);

	// Set basic localplayer attributes
	m_pLocalPlayer->Respawn();

	// Initialise/Patch our pools(IVPed,IVVehicle,IVTask)
	m_pPool->Initialise();

	// Create our camera instance if it doesn't exist/isn't created yet
	CCamera * pCamera = new CCamera;
	if(!m_pCamera)
		m_pCamera = pCamera;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pPlayerManager)
		m_pPlayerManager = new CPlayerManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pVehicleManager)
		m_pVehicleManager = new CVehicleManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pActorManager)
		m_pActorManager = new CActorManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pObjectManager)
		m_pObjectManager = new CObjectManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pFireManager)
		m_pFireManager = new CFireManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pPickupManager)
		m_pPickupManager = new CPickupManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_p3DLabelManager)
		m_p3DLabelManager = new C3DLabelManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pBlipManager)
		m_pBlipManager = new CBlipManager();

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pCheckpointManager)
		m_pCheckpointManager = new CCheckpointManager();

	PrepareWorld();
}

void CGame::Reset()
{
	// Disconnect from network
	; 

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
	// Do we need to reset the game?

	// If our network manager exists process it
	if(g_pCore->GetNetworkManager())
		g_pCore->GetNetworkManager()->Process();

	// If we have text to draw draw it
	
}

void CGame::PrepareWorld()
{
	CIVHud::SetHudVisible(false);
	CIVHud::SetRadarVisible(false);
	CIVHud::SetAreaNamesEnabled(false);
	CIVHud::SetPlayerNamesVisible(0);

	CIVWeather::SetWeather(WEATHER_SUNNY);
	CIVWeather::SetTime(7, 0);
}

CIVModelInfo * CGame::GetModelInfo(int iModelIndex)
{
	if(iModelIndex < NUM_ModelInfos && iModelIndex >= 0 && m_modelInfos[iModelIndex].IsValid())
		return &m_modelInfos[iModelIndex];

	return NULL;
}