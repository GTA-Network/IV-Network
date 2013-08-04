//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: Main.cpp
// Project: Client.Launcher
// Author: crackHD, FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "SharedUtility.h"
#include "CString.h"
#include <ShlObj.h>
#include <mmsystem.h>
#include <Windows.h>

int ShowMessageBox(const char * szText, UINT uType = (MB_ICONEXCLAMATION | MB_OK))
{
	return MessageBox(NULL, szText, "IV:Multiplayer", uType);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// Get the GTA IV install directory from the registry
	char szInstallDirectory[MAX_PATH];
	bool bFoundCustomDirectory = false;

	// TODO: Steam registry entry support
	if(!SharedUtility::ReadRegistryString(HKEY_LOCAL_MACHINE, "Software\\Rockstar Games\\Grand Theft Auto IV", 
		"InstallFolder", NULL, szInstallDirectory, sizeof(szInstallDirectory)) || 
		!SharedUtility::Exists(szInstallDirectory))
	{
		if(!SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "gtaivdir", NULL, 
			szInstallDirectory, sizeof(szInstallDirectory)) || 
			!SharedUtility::Exists(szInstallDirectory))
		{
			if(ShowMessageBox("Failed to retrieve GTA IV install directory from registry. Specify your GTA IV path now?", 
				(MB_ICONEXCLAMATION | MB_OKCANCEL)) == IDOK)
			{
				// Taken from http://vcfaq.mvps.org/sdk/20.htm
				BROWSEINFO browseInfo = { 0 };
				browseInfo.lpszTitle = "Pick a Directory";
				ITEMIDLIST * pItemIdList = SHBrowseForFolder(&browseInfo);

				if(pItemIdList != NULL)
				{
					// Get the name of the selected folder
					if(SHGetPathFromIDList(pItemIdList, szInstallDirectory))
						bFoundCustomDirectory = true;

					// Free any memory used
					IMalloc * pIMalloc = 0;
					if(SUCCEEDED(SHGetMalloc(&pIMalloc)))
					{
						pIMalloc->Free(pItemIdList);
						pIMalloc->Release();
					}
				}
			}

			if(!bFoundCustomDirectory)
			{
				ShowMessageBox("Failed to retrieve GTA IV install directory from registry. Cannot launch IV: Multiplayer.");
				return 1;
			}
		}
	}

	// Get the full path to LaunchGTAIV.exe
	CString strApplicationPath("%s\\LaunchGTAIV.exe", szInstallDirectory);

	// Check if LaunchGTAIV.exe exists
	if(!SharedUtility::Exists(strApplicationPath.Get()))
	{
		ShowMessageBox("Failed to find LaunchGTAIV.exe. Cannot launch IV: Multiplayer.");
		return 1;
	}

	// If we have a custom directory save it
	if(bFoundCustomDirectory)
		SharedUtility::WriteRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "gtaivdir", szInstallDirectory, strlen(szInstallDirectory));

	// Get the full path of the client core
	CString strClientCore(SharedUtility::GetAbsolutePath(CLIENT_CORE_NAME DEBUG_SUFFIX LIBRARY_EXTENSION));

	// Check if the client core exists
	if(!SharedUtility::Exists(strClientCore.Get()))
	{
		ShowMessageBox("Failed to find " CLIENT_CORE_NAME DEBUG_SUFFIX LIBRARY_EXTENSION ". Cannot launch IV: Multiplayer.");
		return 1;
	}

	// Get the full path of the launch helper
	CString strLaunchHelper(SharedUtility::GetAbsolutePath(CLIENT_LAUNCH_HELPER_NAME DEBUG_SUFFIX LIBRARY_EXTENSION));

	// Check if the launch helper exists
	if(!SharedUtility::Exists(strLaunchHelper.Get()))
	{
		ShowMessageBox("Failed to find " CLIENT_LAUNCH_HELPER_NAME DEBUG_SUFFIX LIBRARY_EXTENSION". Cannot launch IV: Multiplayer.");
		return 1;
	}
	
	// Check if GTAIV is already running
	if(SharedUtility::IsProcessRunning("GTAIV.exe"))
	{
		if(ShowMessageBox("GTAIV is already running and needs to be terminated before IV: Multiplayer can be started. Do you want to do that now?", MB_ICONQUESTION | MB_YESNO ) == IDYES)
		{
			if(!SharedUtility::_TerminateProcess("GTAIV.exe"))
			{
				ShowMessageBox("GTAIV.exe could not be terminated. Cannot launch IV: Multiplayer.");
				return 1;
			}
		}
		else
		{
			ShowMessageBox("GTAIV.exe is already running. Cannot launch IV: Multiplayer.");
			return 1;
		}
	}

	// Check if LaunchGTAIV.exe is already running
	if(SharedUtility::IsProcessRunning("LaunchGTAIV.exe"))
	{
		if(ShowMessageBox("LaunchGTAIV is already running and needs to be terminated before IV: Multiplayer can be started. Do you want to do that now?", MB_ICONQUESTION | MB_YESNO ) == IDYES)
		{
			if(!SharedUtility::_TerminateProcess("LaunchGTAIV.exe"))
			{
				// Wait until we've successfully terminated the process
				Sleep(3000);
				if(SharedUtility::IsProcessRunning("LaunchGTAIV.exe"))
				{
					if(!SharedUtility::_TerminateProcess("LaunchGTAIV.exe"))
					{
						ShowMessageBox("LaunchGTAIV.exe could not be terminated. Cannot launch IV: Multiplayer.");
						return 1;
					}
				}
			}
		}
		else
		{
			ShowMessageBox("LaunchGTAIV.exe is already running. Cannot launch IV: Multiplayer.");
			return 1;
		}
	}

	// Generate the command line
	CString strCommandLine("%s %s", strApplicationPath.Get(), lpCmdLine);

	// Start LaunchGTAIV.exe
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	if(!CreateProcess(strApplicationPath.Get(), (char *)strCommandLine.Get(), NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, 
		SharedUtility::GetAppPath(), &siStartupInfo, &piProcessInfo))
	{
		ShowMessageBox("Failed to start LaunchGTAIV.exe. Cannot launch IV: Multiplayer.");
		return 1;
	}

	// Inject LauncherLibrary.dll into LaunchGTAIV.exe
	int iReturn = SharedUtility::InjectLibraryIntoProcess(piProcessInfo.hProcess, strLaunchHelper.Get());

	// Did the injection fail?
	if(iReturn > 0)
	{
		// Terminate the process
		TerminateProcess(piProcessInfo.hProcess, 0);

		// Show the error message
		CString strError("Unknown error. Cannot launch IV: Multiplayer.");

		if(iReturn == 1)
			strError = "Failed to write library path into remote process. Cannot launch IV: Multiplayer.";
		else if(iReturn == 2)
			strError = "Failed to create remote thread in remote process. Cannot launch IV: Multiplayer.";
		else if(iReturn == 3)
			strError = "Failed to open the remote process, Cannot launch IV: Multiplayer.";

		ShowMessageBox(strError.Get());
		return 1;
	}

	// Resume the LaunchGTAIV.exe thread
	ResumeThread(piProcessInfo.hThread);
	return 0;
}
