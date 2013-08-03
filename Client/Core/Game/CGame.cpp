//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CGame.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	<CCore.h>
#include	"CGame.h"
#include	<Network\CLocalPlayer.h>
#include	<Patcher\CPatcher.h>
#include	<Windows.h>
extern	CCore				* g_pCore;

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
	CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)WaitForGameStartup, 0, 0, 0 ); // Remove Thread?
}

void CGame::Initialise()
{
	g_pCore->SetClientState(GAME_STATE_NONE);

	if(!m_pLocalPlayer)
		m_pLocalPlayer = new CLocalPlayer();

	m_pLocalPlayer->SetPlayerId(INVALID_ENTITY_ID);
	m_pLocalPlayer->Reset();
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