//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: Main.cpp
// Project: Client.LaunchHelper
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

// TODO: Replace with Hook function..

#include "SharedUtility.h"
#include <Patcher\CPatcher.h>
#include <ShlObj.h>
#include <mmsystem.h>
#include <Windows.h>
#include <windowsx.h>

typedef UINT_PTR (WINAPI * SetTimer_t)(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc);
typedef BOOL (WINAPI * CreateProcessW_t)(LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION);
typedef BOOL (WINAPI * ShowWindow_t)(HWND, int);

LRESULT ProcessMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

enum
{
	STATE_LOGIN_WINDOW,
	STATE_WAIT_FOR_SECOND_WINDOW,
	STATE_STFU_RGSC_I_WANNA_PLAY_OFFLINE,
	STATE_DONE
}	eSocialClubWindowState;

WNDPROC          oldWndProc;
SetTimer_t       g_pfnSetTimer = NULL;
CreateProcessW_t g_pfnCreateProcessW = NULL;
ShowWindow_t     g_pfnShowWindow = NULL;

int ShowMessageBox(const char * szText, UINT uType = (MB_ICONEXCLAMATION | MB_OK))
{
	return MessageBox(NULL, szText, MOD_NAME, uType);
}

UINT_PTR WINAPI SetTimer_Hook(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
{
	return g_pfnSetTimer(hWnd, nIDEvent, 0, lpTimerFunc);
}

BOOL WINAPI CreateProcessW_Hook(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	// If this is not a call to start the 'GTAIV.exe' process then just call the original CreateProcessW
	if(wcscmp(lpApplicationName, L"EFLC.exe"))
		return g_pfnCreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);

	// Set the CREATE_SUSPENDED flag in the creation flags
	dwCreationFlags |= CREATE_SUSPENDED;

	// Get the GTA IV install directory from the registry
	char szInstallDirectory[MAX_PATH];
	bool bFoundCustomDirectory = false;

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
				return FALSE;
			}
		}
	}

	// Get the full path to GTAIV.exe
	CString strApplicationPath("%s\\EFLC.exe", szInstallDirectory);

	// Make sure the GTAIV.exe path is valid
	if(!SharedUtility::Exists(strApplicationPath.Get()))
	{
		ShowMessageBox("Failed to find EFLC.exe. Cannot launch IV: Multiplayer.");
		return FALSE;
	}

	// If we have a custom directory save it
	if(bFoundCustomDirectory)
		SharedUtility::WriteRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "gtaivdir", szInstallDirectory, strlen(szInstallDirectory));

	// Convert the install directory to unicode
	wchar_t wszInstallDirectory[MAX_PATH];
	int iInstallDirectoryLength = SharedUtility::AnsiToUnicode(szInstallDirectory, strlen(szInstallDirectory), wszInstallDirectory, sizeof(wszInstallDirectory));
	wszInstallDirectory[iInstallDirectoryLength] = '\0';

	// Convert the application path to unicode
	wchar_t wszApplicationPath[MAX_PATH];
	int iApplicationPathLength = SharedUtility::AnsiToUnicode(strApplicationPath.Get(), strApplicationPath.GetLength(), wszApplicationPath, sizeof(wszApplicationPath));
	wszApplicationPath[iApplicationPathLength] = '\0';

	// Create the process
	BOOL bReturn = g_pfnCreateProcessW(wszApplicationPath, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, wszInstallDirectory, lpStartupInfo, lpProcessInformation);

	if(bReturn)
	{
		// Get the full path of the client dll
		CString strLibraryPath(SharedUtility::GetAbsolutePath(CLIENT_CORE_NAME DEBUG_SUFFIX LIBRARY_EXTENSION));

		// Inject Client.dll into GTAIV.exe
		int iReturn = SharedUtility::InjectLibraryIntoProcess(lpProcessInformation->hProcess, strLibraryPath.Get());

		// Did the injection fail?
		if(iReturn > 0)
		{
			// Terminate the process
			TerminateProcess(lpProcessInformation->hProcess, 0);
			CString strError("Unknown error. Cannot launch IV: Multiplayer.");

			if(iReturn == 1)
				strError = "Failed to write library path into remote process. Cannot launch IV: Multiplayer.";
			else if(iReturn == 2)
				strError = "Failed to create remote thread in remote process. Cannot launch IV: Multiplayer";
			else if(iReturn == 3)
				strError = "Failed to open the remote process, Cannot launch IV: Multiplayer.";

			ShowMessageBox(strError.Get());
			return FALSE;
		}

		// Resume the GTAIV.exe thread
		ResumeThread(lpProcessInformation->hThread);
	}

	return bReturn;
}

static BOOL WINAPI ShowWindow_Hook(HWND hWnd, int nShow)
{
	BOOL bReturn = g_pfnShowWindow(hWnd, nShow);

	// This is usually called twice, once for the RGSC window, once for
	// "but you play offline, so you cant upload videos to social club"
	// - both windows we want to have
	//
	// *most* Securom errors (e.g. no disk in drive) do not use ShowWindow?
	if((eSocialClubWindowState == STATE_LOGIN_WINDOW || eSocialClubWindowState == STATE_WAIT_FOR_SECOND_WINDOW))
	{
		DWORD dwWindowProc = (DWORD)GetWindowLong(hWnd, GWL_WNDPROC);

		// RGSC windows seem to be always in this range (if not, above is the code that I used to see where they are)
		// securom windows are outside of this range (or have always been for me) - e.g. 5003 (IDA running)
		if(dwWindowProc >= 0xFFFF0000 && dwWindowProc < 0xFFFFFFFF)
		{
			// Save the old window proc so we can call it later
			oldWndProc = SubclassWindow(hWnd, ProcessMessage);

			// set it somewhere far far away so nobody'd see it. we need it shown tho or it'll ignore window messages. or unless that's patched in the exe
			SetWindowPos(hWnd, NULL, 4000, 4000, 1, 1, SWP_NOSENDCHANGING | SWP_NOREDRAW | SWP_NOSIZE | SWP_NOOWNERZORDER);

			// We're waiting for the cry-you-arent-logged-in-window, so make sure ProcessMessage knows that.
			if(eSocialClubWindowState == STATE_WAIT_FOR_SECOND_WINDOW)
			{
				eSocialClubWindowState = STATE_STFU_RGSC_I_WANNA_PLAY_OFFLINE;
			}
		}
	}

	return bReturn;
}

LRESULT ProcessMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DRAWITEM:
		if(eSocialClubWindowState == STATE_LOGIN_WINDOW && wParam == 4)
		{
			// First Window (RGSC Login, username, pw, etc.), button 4 = Play Offline

			// Save our state
			eSocialClubWindowState = STATE_WAIT_FOR_SECOND_WINDOW;

			// Simulate the Play Offline button to be pressed
			CallWindowProc(oldWndProc, hwnd, WM_COMMAND, 4, 0);

			// make sure the window is hidden so it's not getting into the taskbar
			g_pfnShowWindow(hwnd, FALSE);
		}
		else if(eSocialClubWindowState == STATE_STFU_RGSC_I_WANNA_PLAY_OFFLINE && wParam == 1)
		{
			// Second Window (You are playing offline + can't upload videos to social club)

			// Save our state
			eSocialClubWindowState = STATE_DONE;

			// Simulate the OK button to be pressed
			CallWindowProc(oldWndProc, hwnd, WM_COMMAND, 1, 0);

			// make sure the window is hidden so it's not getting into the taskbar
			g_pfnShowWindow(hwnd, FALSE);
		}
		break;
	case WM_ACTIVATE:
	case WM_ACTIVATEAPP:
		// Skip any activation calls so the window won't show in the task bar
		return FALSE;
	}

	return CallWindowProc(oldWndProc, hwnd, uMsg, wParam, lParam);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch(fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			// Disable thread library notifications
			DisableThreadLibraryCalls(hModule);

			// Install the SetTimer hook
			g_pfnSetTimer = (SetTimer_t)CPatcher::InstallDetourPatch("User32.dll", "SetTimer", (DWORD)SetTimer_Hook);

			// Install the CreateProcessW hook
			g_pfnCreateProcessW = (CreateProcessW_t)CPatcher::InstallDetourPatch("Kernel32.dll", "CreateProcessW", (DWORD)CreateProcessW_Hook);

			// Install the ShowWindow hook
			g_pfnShowWindow = (ShowWindow_t)CPatcher::InstallDetourPatch("User32.dll", "ShowWindow", (DWORD)ShowWindow_Hook);
		}
		break;
	case DLL_PROCESS_DETACH:
		{
			// Uninstall our SetTimer hook
			CPatcher::UninstallDetourPatch((void *)g_pfnSetTimer, (DWORD)SetTimer);

			// Uninstall our CreateProcessW hook
			CPatcher::UninstallDetourPatch((void *)g_pfnCreateProcessW, (DWORD)CreateProcessW);

			// Uninstall our ShowWindow hook
			CPatcher::UninstallDetourPatch((void *)g_pfnShowWindow, (DWORD)ShowWindow);
		}
		break;
	}

	return TRUE;
}
