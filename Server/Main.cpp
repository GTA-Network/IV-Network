//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: Main.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================


#include "CServer.h"
#include "CInput.h"
#include <Common.h>
#include <CLogFile.h>
#include <Threading/CThread.h>

bool g_bClose = false;
string g_strStartError;

CServer * g_pServer = NULL;

int main(int argc, char ** argv)
{
	g_pServer = new CServer();

	// Start our input thread which handles all the input
	CThread inputThread;

	// Start log file
	CLogFile::Open("ivmp-svr.log");

	// Start server and load all scripts
	if(!g_pServer->Startup())
	{
		CLogFile::Printf("Failed to start server! Exiting in 10 seconds..");
#ifdef _WIN32
		Sleep(10 * 1000);
#else
		sleep(10);
#endif
		ExitProcess(EXIT_FAILURE);
	}

	// Start input
	inputThread.Start(CInput::InputThread);

	// Program loop
	while(!g_bClose)
	{
		g_pServer->Process();
	}

	// Stop the input thread
	inputThread.Stop(true, true);

	// Shutdown
	g_pServer->Shutdown();
		
	// Delete our server
	SAFE_DELETE(g_pServer);

	// Exit process
	ExitProcess(EXIT_SUCCESS);
}