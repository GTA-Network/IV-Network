//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: Main.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CCore.h"
#include <Windows.h>


CCore		* pCore = NULL;
HMODULE		g_hModule = NULL;

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

			// Install the exception handler
			//CExceptionHandler::Install();

			// Create the core instance
			pCore = new CCore;

			// Did the core fail to create or initialsie?
			if(!pCore || !pCore->Initialise())
			{
				//CLogFile::Printf("Terminating...");

				// Terminate the process
				TerminateProcess(GetCurrentProcess(), 0);
			}
			break;
		}

	case DLL_PROCESS_DETACH:
		{
			//CLogFile::Print("Terminating process");

			// Terminate the process
			TerminateProcess(GetCurrentProcess(), 0);
			break;
		}
	}

	return TRUE;
}