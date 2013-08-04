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
//extern CLocalPlayer			* g_pLocalPlayer;

/*
	==== Why WaitForGameStartup ====
	We can load/start the game in the background and request all resources while the player is in the main menu.
	So GTA IV loads all resources and when our player connects to a server, we have check if the game(resources are) is ready.
	If the Wrapperlist is ready, we can spawn the localplayer
*/
CLocalPlayer*   CGame::m_pLocalPlayer = 0;
CIVPad		*	CGame::m_pPad = 0;
CTaskManager*	CGame::m_pTaskManager = 0;
CPools		*	CGame::m_pPool = 0;
CCamera		*	CGame::m_pCamera = 0;

DWORD WINAPI WaitForGameStartup(LPVOID lpParam)
{
	return 1;
}

void CGame::Setup()
{
	//CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)WaitForGameStartup, 0, 0, 0 ); // Remove Thread?

	g_pCore->SetClientState(GAME_STATE_LOADING);

	if(!m_pLocalPlayer)
		m_pLocalPlayer = new CLocalPlayer;

	m_pLocalPlayer->SetPlayerId(INVALID_ENTITY_ID);
	m_pLocalPlayer->Reset();
	m_pLocalPlayer->SetSpawnLocation(DEVELOPMENT_SPAWN_POSITION,0.0f);

	// Create new civpad instance
	m_pPad = new CIVPad( (IVPad *)(g_pCore->GetBase() + 0x10FB818) );

	// Create task manager instance
	m_pTaskManager = new CTaskManager();

	// Create new pool instance
	m_pPool = new CPools( );
}

void CGame::Initialise()
{
	g_pCore->SetClientState(GAME_STATE_INGAME);

	m_pLocalPlayer->SetPlayerIndex(g_pCore->GetLocalPlayerIndex()); // Got from CIVScriptHook
	m_pLocalPlayer->SetPlayerId(INVALID_ENTITY_ID);
	m_pLocalPlayer->Respawn();

	m_pPool->Initialise();

	CCamera * pCamera = new CCamera;
	if(!m_pCamera)
		m_pCamera = pCamera;

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

CIVModelInfo * CGame::GetModelInfo( int iModelIndex )
{
	if( iModelIndex < NUM_ModelInfos && iModelIndex >= 0 && m_modelInfos[iModelIndex].IsValid() )
		return &m_modelInfos[iModelIndex];

	return NULL;
}