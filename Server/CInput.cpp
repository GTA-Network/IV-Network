//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CInput.cpp
// Project: Server
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CInput.h"
#include <CLogFile.h>
#include <Scripting/CEvents.h>
#include "CServer.h"

extern bool g_bClose;

void CInput::InputThread(CThread* pThread)
{
	CString strInput = GetInput();
	while(pThread->IsRunning())
	{
		ProcessInput(strInput);

		strInput = GetInput();
	}
}

CScriptVehicle * pScriptVehicle = nullptr;
void CInput::ProcessInput(CString strInput)
{
	// Get the command and parameters
	size_t sSplit = strInput.Find(' ', 0);
	CString strCommand = strInput.Substring(0, sSplit++);
	CString strParameters = strInput.Substring(sSplit, (strInput.GetLength() - sSplit));

	if(strCommand.IsEmpty())
		return;
	else if(strCommand == "quit" || strCommand == "Quit" || strCommand == "exit") {
		CLogFile::Print("[Server] Server is going to shutdown NOW ....");
		g_bClose = true;
		return;

	} else if(strCommand == "help" || strCommand == "?" || strCommand == "--usage") {
		printf("========== Available console commands: ==========\n");
		printf("say <text>\n");
		printf("uptime\n");
		printf("resources\n");
		printf("players\n");
		printf("loadresource <name>\n");
		printf("reloadresource <name>\n");
		printf("unloadresource <name>\n");
		printf("exit\n");
		return;
	}
	else if (strCommand == "setSyncRate") {
		int rate = atoi(strParameters.Get());
		CServer::GetInstance()->SetSyncRate(rate);
	}
	else if (strCommand == "setMaxFPS") {
		int fps = atoi(strParameters.Get());
		CServer::GetInstance()->SetMaximumFPS(fps);
	}
}


CString CInput::GetInput()
{
	char szInputBuffer[512]; // Buffer MUST be 3 or more (input char, \n, \0)
	CString strInputString;

	// Wait for input from the console
	fgets(szInputBuffer, sizeof(szInputBuffer), stdin);

	// Do we have anything in the input?
	if(szInputBuffer[0] != '\n')
	{
		// Append the input to the input string
		strInputString += szInputBuffer;

		// Get the input string length
		size_t sLength = strInputString.GetLength();

		// Is this the last of the input?
		if(strInputString[sLength - 1] == '\n')
		{
#ifdef _WIN32
			// Replace '\n' with '\0'
			strInputString.Truncate(sLength - 1);
#else
			// Replace '\r\n' with '\0'
			strInputString.Truncate(sLength - 2);
#endif

			// Return the input
			return strInputString;
		}
	}
	return strInputString;
}