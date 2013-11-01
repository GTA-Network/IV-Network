//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: Main.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//=========================================================================================

#include "CCore.h"
#include <WinSock2.h>
#include <Windows.h>

#ifndef _CLIENT
#define _CLIENT
#endif

CCore		*g_pCore = NULL;
HMODULE		g_hModule = NULL;
extern		void InstallException();

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, void * pReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			// Store the hmodule pointer
			g_hModule = hModule;

			// Disable thread library calls
			DisableThreadLibraryCalls(hModule);

			// Delete the chatlog
			CLogFile::Open(CLIENT_CHATLOG_FILE);
			CLogFile::Close();
			
			// Open the log file
			CLogFile::Open(CLIENT_LOG_FILE);

			// Create the core instance
			g_pCore = new CCore;

			// Call install exception function
			InstallException();

			// Did the core fail to create or initialsie?
			if(!g_pCore || !g_pCore->Initialise())
			{
				CLogFile::Printf("GTA IV instance failed to create. Shutdown...");

				// Terminate the process
				TerminateProcess(GetCurrentProcess(), 0);
			}

			break;
		}

	case DLL_PROCESS_DETACH:
		{
			CLogFile::Print("DLL_PROCESS_DETACH -> GTA IV shutdown");

			// Terminate the process
			TerminateProcess(GetCurrentProcess(), 0);
			break;
		}
	}

	return TRUE;
}