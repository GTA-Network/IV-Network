//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: Main.cpp
// Project: Client.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#include "windows.h"
#include "Common.h"

int ShowMessageBox(const char* szText, UINT uType = (MB_ICONERROR | MB_OK))
{
	return MessageBox(NULL, szText, "IV:Multiplayer - Launcher", uType);
}

#define ExitError(reason) { strError = reason; goto onError; }

// Launcher entry point
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	string strError;

	// 1. Ensure client is installed correctly.
	// i mean launcher helper and client core, CEGUI folder etc.
	bool bIvmpInstalled = false;
	if(bIvmpInstalled == false)
		ExitError("IV:MP is not installed correctly, please repair the installation.");

	// 2. Ensure GTA IV is installed.
	// If not, select the directory, or try to get path from config file

	// 3. Ensure GTA IV or IV:MP is not running.
	// If it is running, ask for termination.

	// 4. Process the "-connect ip:port" commandline argument
	// CrackHD: I know how to make it easier, leave this to me

	// 5. Inject helper library into process,
	// and exit.

onError:
	// Display error message if we have one
	if(strError.IsNotEmpty())
	{
		ShowMessageBox(string("An error has occured. IV:MP cannot start.\r\n%s\r\n\r\nhttp://www.iv-multiplayer.com/", strError.Get()));
		return 1;
	}
	else
		return 0;
}