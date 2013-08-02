//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CGame.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include	"CGame.h"
#include	"CCore.h"
#include	<Windows.h>

extern	CCore				* pCore;

DWORD WINAPI WaitForWrapperList(LPVOID lpParam)
{
	return 1;
}

void CGame::Setup()
{
	// Create a thread to wait for the entity wrappers
	CreateThread( 0, 0, (LPTHREAD_START_ROUTINE)WaitForWrapperList, 0, 0, 0 ); // Remove Thread?
}