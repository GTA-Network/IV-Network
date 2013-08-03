//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: Main.cpp
// Project: Client.Core
// Author: xForce
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

	// Start server and load all scripts
	if(!pServer->Startup(g_strStartError))
	{
		string strErrorMsg("Failed to start server! %s", g_strStartError.Get());
		CLogFile::Printf(strErrorMsg);
#ifdef _WIN32
		ExitProcess(EXIT_FAILURE);
#else
		exit(EXIT_FAILURE);
#endif
		return EXIT_FAILURE;
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
#ifdef _WIN32
	ExitProcess(EXIT_SUCCESS);
#else
	exit(EXIT_SUCCESS);
#endif
}