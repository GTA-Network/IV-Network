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

int main(int argc, char ** argv)
{
	// Open the log file
	CLogFile::Open("ivmp-svr.log", true);

	CServer* pServer = new CServer();

	if(pServer)
	{
		// Start our input thread which handles all the input
		CThread inputThread;
		inputThread.Start(CInput::InputThread);

		// Startup server and load all scripts
		if(!pServer->Startup())
		{
			CLogFile::Printf("Failed to start server!");
#ifdef _WIN32
			ExitProcess(0);
#else
			exit(0);
#endif
		}

		while(!g_bClose)
		{
			pServer->Process();
			
		}

		pServer->Shutdown();

		// Stop the input thread
		inputThread.Stop(true, true);

		// Delete our server
		SAFE_DELETE(pServer);

#ifdef _WIN32
		ExitProcess(0);
#else
		exit(0);
#endif
	}
	else
	{
		CLogFile::Printf("Unable to create the server instance");
	}
}