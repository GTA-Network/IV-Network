//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CGame.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CGame.h"
#include	<CCore.h>
#include	<Windows.h>

extern	CCore				* pCore;

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