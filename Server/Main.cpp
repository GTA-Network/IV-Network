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
	CServer* pServer = new CServer();

	if(pServer)
	{
		// Start our input thread which handles all the input
		CThread inputThread;
		inputThread.Start(CInput::InputThread);

		// Startup server and load all scripts
		if(!pServer->Startup())
		{
			CLogFile::Printf("Failed to start server! ");
			return 1;
		}

		while(!g_bClose)
		{
			pServer->Process();
		}

		pServer->Shutdown();

		// Stop the input thread
		inputThread.Stop();
		
		// Delete our server
		SAFE_DELETE(pServer);

		// Exit process
		return 1;
	}
	else
	{
		CLogFile::Printf("Unable to create the server instance");
	}
}