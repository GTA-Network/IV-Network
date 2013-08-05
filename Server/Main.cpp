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

int main(int argc, char ** argv)
{
	CServer* pServer = new CServer();

	// Start our input thread which handles all the input
	CThread inputThread;

	// Start log file
	CLogFile::Open("ivmp-svr.log");

	// Start server and load all scripts
	if(!pServer->Startup())
	{
		CLogFile::Printf("Failed to start server! Exiting in 10 seconds..");
		Sleep(10 * 1000);
		ExitProcess(EXIT_FAILURE);
	}

	// Start input
	inputThread.Start(CInput::InputThread);

	// Program loop
	while(!g_bClose)
	{
		pServer->Process();
	}

	// Stop the input thread
	inputThread.Stop(true, true);

	// Shutdown
	pServer->Shutdown();
		
	// Delete our server
	SAFE_DELETE(pServer);

	// Exit process
	ExitProcess(EXIT_SUCCESS);
}