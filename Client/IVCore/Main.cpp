/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
#ifndef DEBUG
			InstallException();
#endif

			// Did the core fail to create or initialsie?
			if(!g_pCore || !g_pCore->Initialize())
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