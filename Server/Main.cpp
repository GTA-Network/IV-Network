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

#include "CServer.h"
#include "CInput.h"
#include <Common.h>
#include <CLogFile.h>
#include <Threading/CThread.h>

bool g_bClose = false;
CString g_strStartError;

int main(int argc, char ** argv)
{
	CServer* pServer = new CServer();

	// Start our input thread which handles all the input
	CThread inputThread;

	// Start log file
	CLogFile::Open("ivn-svr.log");

	// Start server and load all scripts
	if(!pServer->Startup())
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