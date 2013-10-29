//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: Main.cpp
// Project: Client.Launcher
// Author: crackHD, FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
// Parts taken from http://vcfaq.mvps.org/sdk/20.htm
//
//==========================================================================================

#include <Common.h>
#include <ShlObj.h>
#include <mmsystem.h>
#include <CSettings.h>

// temp
#include <SharedUtility.h>
#include <CLogFile.h>

int ShowMessageBox(const char * szText, UINT uType = (MB_ICONEXCLAMATION | MB_OK))
{
	return MessageBox(NULL, szText, MOD_NAME, uType);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Get the GTA IV install directory from the registry
	char szInstallDirectory[MAX_PATH];
	bool bFoundCustomDirectory = false, bRenewProtocol = false;
	std::string strReNewEntries = lpCmdLine;

	char szProtocolDirectory[MAX_PATH];
	CString strCommand = CString("\"%s\" \"%%1\"",SharedUtility::GetAbsolutePath(MP_START_EXECUTABLE));

	if(strcmp(szProtocolDirectory, strCommand.Get()))
		bRenewProtocol = true;

	// Check if protocol 'ivn' and 'ivnetwork' is avaiable in registry
	if(!SharedUtility::ReadRegistryString(HKEY_CLASSES_ROOT, SHORT_URI_LAUNCH_3, NULL, "", NULL, NULL)
		|| !SharedUtility::ReadRegistryString(HKEY_CLASSES_ROOT, SHORT_URI_LAUNCH_4, NULL, "", NULL, NULL) || bRenewProtocol) {

		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_3,"",CLIENT_CORE_NAME,strlen(CLIENT_CORE_NAME));
		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_4,"",CLIENT_CORE_NAME,strlen(CLIENT_CORE_NAME));

		CString strcommand = CString("\"%s\" \"%%1\"",SharedUtility::GetAbsolutePath(MP_START_EXECUTABLE));

		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_3 ,"Url Protocol","",0);
		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_3"\\shell\\open\\command\\","",CString("%s",strcommand.Get()).GetData(),strcommand.GetLength());
		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_3"\\DefaultIcon","", CString(MP_START_EXECUTABLE" ,1").GetData(),strlen(MP_START_EXECUTABLE" ,1"));

		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_4,"Url Protocol","",0);
		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_4"\\shell\\open\\command\\","",CString("%s",strcommand.Get()).GetData(),strcommand.GetLength());
		SharedUtility::WriteRegistryString(HKEY_CLASSES_ROOT,SHORT_URI_LAUNCH_4"\\DefaultIcon","", CString(MP_START_EXECUTABLE" ,1").GetData(),strlen(MP_START_EXECUTABLE" ,1"));
	}

	if(!SharedUtility::ReadRegistryString(HKEY_LOCAL_MACHINE, DEFAULT_REGISTRY_GAME_DIRECTORY,
		"InstallFolder", NULL, szInstallDirectory, sizeof(szInstallDirectory)) ||
		!SharedUtility::Exists(szInstallDirectory)) {

		if(!SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, REGISTRY_AREA, GAME_DIRECTORY, NULL,
			szInstallDirectory, sizeof(szInstallDirectory)) ||
			!SharedUtility::Exists(szInstallDirectory)) {

			if(ShowMessageBox("Failed to retrieve the install directory from "GAME_DEFAULT_EXECUTABLE"'s registry. Specify your game path now?",
				(MB_ICONEXCLAMATION | MB_OKCANCEL)) == IDOK)  {
				
				BROWSEINFO browseInfo = { 0 };
				browseInfo.lpszTitle = MOD_NAME" - Pick a Directory";
				ITEMIDLIST * pItemIdList = SHBrowseForFolder(&browseInfo);

				if(pItemIdList != NULL) {
					// Get the name of the selected folder
					if(SHGetPathFromIDList(pItemIdList, szInstallDirectory))
						bFoundCustomDirectory = true;

					// Free any memory used
					IMalloc * pIMalloc = 0;
					if(SUCCEEDED(SHGetMalloc(&pIMalloc))) {
						pIMalloc->Free(pItemIdList);
						pIMalloc->Release();
					}
				}
			}

			if(!bFoundCustomDirectory) {
				ShowMessageBox("Failed to retrieve the install directory from registry or browser window. Cannot launch "MOD_NAME".");
				return 1;
			}
		}
	}

	// Create basic directories for extracting files(..)
	SharedUtility::CreateBasicMPDirectories();

	Sleep(500);

	// Get the full path to EFLC.exe
	CString strApplicationPath("%s\\"GAME_DEFAULT_EXECUTABLE, szInstallDirectory);

	// Check if EFLC.exe exists
	if(!SharedUtility::Exists(strApplicationPath.Get()))
		return ShowMessageBox("Failed to find "GAME_DEFAULT_EXECUTABLE". Cannot launch "MOD_NAME".");

	// If we have a custom directory save it
	if(bFoundCustomDirectory)
		SharedUtility::WriteRegistryString(HKEY_CURRENT_USER, REGISTRY_AREA, GAME_DIRECTORY, szInstallDirectory, strlen(szInstallDirectory));

	// Get the full path of the client core
	CString strClientCore(SharedUtility::GetAbsolutePath(CLIENT_CORE_NAME DEBUG_SUFFIX LIBRARY_EXTENSION));

	// Check if the client core exists
	if(!SharedUtility::Exists(strClientCore.Get()))
		return ShowMessageBox("Failed to find " CLIENT_CORE_NAME DEBUG_SUFFIX LIBRARY_EXTENSION ". Cannot launch "MOD_NAME".");

	// Get the full path of the launch helper
	CString strCore(SharedUtility::GetAbsolutePath(CLIENT_CORE_NAME DEBUG_SUFFIX LIBRARY_EXTENSION));

	// Check if the launch helper exists
	if (!SharedUtility::Exists(strCore.Get()))
		return ShowMessageBox("Failed to find " CLIENT_CORE_NAME DEBUG_SUFFIX LIBRARY_EXTENSION". Cannot launch "MOD_NAME".");

	// Get the full path of the launch helper
	CString strBass(SharedUtility::GetAbsolutePath("bass.dll"));

	// Check if the launch helper exists
	if (!SharedUtility::Exists(strBass.Get()))
		return ShowMessageBox("Failed to find bass.dll. Cannot launch "MOD_NAME".");

	// Check if GTAEFLC is already running
	if (SharedUtility::IsProcessRunning(GAME_DEFAULT_EXECUTABLE))
	{
		if (ShowMessageBox(GAME_DEFAULT_EXECUTABLE" is already running and needs to be terminated before "MOD_NAME" can be started. Do you want to do that now?",
			MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			if (!SharedUtility::_TerminateProcess(GAME_DEFAULT_EXECUTABLE))
			{
				if (ShowMessageBox("Do you want to start it?",
					MB_ICONQUESTION | MB_YESNO) == IDYES) {
				}
				else
				{
					return ShowMessageBox(GAME_DEFAULT_EXECUTABLE" could not be terminated. Cannot launch "MOD_NAME".");
				}
			}
		}
		else
			return ShowMessageBox(GAME_DEFAULT_EXECUTABLE" is already running. Cannot launch "MOD_NAME".");
	}

	// TODO ADD WINDOW COMMANDLINE SUPPORT!

	// Check if we have an server connect command
	CString strServer, strPort;
	std::string strServerCheck = CString(lpCmdLine);
	std::size_t sizetCMDFound = strServerCheck.find(SHORT_COMMANDLINE_LAUNCH_1);
	int iOffset = 0;
	bool bCommandFound = false;
	CString strNewCommandLine = lpCmdLine;

	// Check for shortcut commandline
	if(sizetCMDFound != std::string::npos) {
		iOffset = 6;
		bCommandFound = true;
	}

	// Check for ivn protocol
	if(!bCommandFound) {
		sizetCMDFound = strServerCheck.find(SHORT_URI_LAUNCH_1); 
		if(sizetCMDFound != std::string::npos) {
			iOffset = 7;
			bCommandFound = true;
		}
	}

	// Check for ivmultiplayer protocol
	if(!bCommandFound) {
		sizetCMDFound = strServerCheck.find(SHORT_URI_LAUNCH_2);
		if(sizetCMDFound != std::string::npos) {
			iOffset = 16;
			bCommandFound = true;
		}
	}

	// Open default clientsettings
	CSettings::Open(SharedUtility::GetAbsolutePath(CLIENT_SETTINGS_FILE), true, true, true);

	// If we have found an direct connect force
	if(bCommandFound)
	{
		std::string strServerInst = strServerCheck.substr(sizetCMDFound+iOffset,strServerCheck.length());
		std::size_t sizetCMDFound_2 = strServerInst.find(":");

		// Have we an : in our instruction
		if(sizetCMDFound_2 != std::string::npos) {
			// Grab our connect data
			strServer = CString("%s",strServerInst.substr(0,sizetCMDFound_2).c_str());
			strPort = CString("%s",strServerInst.substr(sizetCMDFound_2+1,strServerInst.length()).c_str());

			// Parse the command line
			CSettings::ParseCommandLine(GetCommandLine());

			// Write connect data to settings xml
			CVAR_SET_STRING("currentconnect_server",strServer.Get());
			CVAR_SET_INTEGER("currentconnect_port",strPort.ToInteger());

			// Generate new commandline
			strNewCommandLine = CString("%s -directconnect", lpCmdLine);
		}
		else // Something is wrong with our URI 
		{
			if(ShowMessageBox("Something is wrong with your server direct-connect URI, do you want to start "MOD_NAME" without direct-connect?", MB_ICONQUESTION | MB_YESNO ) == IDYES)
			{
				// Set default server direct connect values
				CVAR_SET_STRING("currentconnect_server","0.0.0.0");
				CVAR_SET_INTEGER("currentconnect_port",9999);

				strNewCommandLine = lpCmdLine;
			}
			else // Terminate IV:N
			{
				if(!SharedUtility::_TerminateProcess(MP_START_EXECUTABLE))
					return ShowMessageBox(MP_START_EXECUTABLE" could not be terminated. Cannot launch IV:Network.");
			}

		}
	}
	else {
		CSettings::ParseCommandLine(GetCommandLine());
		// If we haven't found a server connect command, delte the old instructions(if the client had crashed before)
		CVAR_SET_STRING("currentconnect_server","0.0.0.0");
		CVAR_SET_INTEGER("currentconnect_port",9999);
	}

	// Close settings...
	CSettings::Close();

	// Generate the command line
	CString strCommandLine("%s %s", strApplicationPath.Get(), strNewCommandLine.Get());

	// Start LaunchGTAIV.exe
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	if (!CreateProcess(strApplicationPath.Get(), (char *) strCommandLine.Get(), NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, szInstallDirectory, &siStartupInfo, &piProcessInfo)) {
		ShowMessageBox("Failed to start "GAME_DEFAULT_EXECUTABLE". Cannot launch "MOD_NAME".");
		return 1;
	}

	// Inject bass.dll into EFLC.exe
	int iReturn = SharedUtility::InjectLibraryIntoProcess(piProcessInfo.hProcess, strBass.Get());

	// Inject IVNetwork.dll into EFLC.exe
	iReturn += SharedUtility::InjectLibraryIntoProcess(piProcessInfo.hProcess, strCore.Get());

	// Did the injection fail?
	if(iReturn > 0) {
		// Terminate the process
		TerminateProcess(piProcessInfo.hProcess, 0);

		// Show the error message
		CString strError("Unknown error. Cannot launch "MOD_NAME".");

		if(iReturn == 1)
			strError = "Failed to write library path into remote process. Cannot launch "MOD_NAME".";
		else if(iReturn == 2)
			strError = "Failed to create remote thread in remote process. Cannot launch "MOD_NAME".";
		else if(iReturn == 3)
			strError = "Failed to open the remote process, Cannot launch "MOD_NAME".";

		ShowMessageBox(strError.Get());
		return 1;
	}

	// Resume the thread
	ResumeThread(piProcessInfo.hThread);
	return 0;
}
