//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CModuleManager.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CModuleManager.h"
#include <SharedUtility.h>
#include <CLogFile.h>

std::list<CModule *>		CModuleManager::m_pModules;
void CModuleManager::FetchModules()
{
	CString strPath;
	std::string szPath;

	WIN32_FIND_DATA FindFileData;
	CString sOrigPath = SharedUtility::GetAppPath();
	
	CString sTempPath = SharedUtility::GetAppPath();
	sTempPath.AppendF("multiplayer\\modules\\*",&FindFileData);

	HANDLE hFind = FindFirstFile(sTempPath, &FindFileData);
	if(hFind == INVALID_HANDLE_VALUE)
		return;
	else
	{
		do
		{
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(strcmp(".", FindFileData.cFileName) && strcmp("..", FindFileData.cFileName))
				{
					// Found directoy, go to next
					break;
				}
			}
			else
			{
				sTempPath = CString("%smultiplayer\\modules\\",sOrigPath.Get()).Get();
				sTempPath.AppendF("%s",FindFileData.cFileName);
				if(sTempPath.EndsWith(".dll"))
				{
					CModule * pModule = new CModule;
					pModule->strModuleName = new CString;
					pModule->strModulePath = new CString;

					pModule->strModuleName->AppendF("%s",FindFileData.cFileName);
					pModule->strModulePath = &sTempPath;
					m_pModules.push_back(pModule);
					CLogFile::Printf("  --> Modulemanager: Fetched module %s",FindFileData.cFileName);
				}
			}
		}
		while(FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}
}

CString *CModuleManager::GetModules()
{
	CString * strModules = new CString;
	for(auto pModule:m_pModules)
	{
		strModules->AppendF("%s\n",pModule->strModuleName->Get());
	}
	return strModules;
}

CString *CModuleManager::GetModulePath(CString *strModule)
{
	CString * strRetn = new CString;

	// Load the test module
	if(strModule->GetLength() > 0)
	{
		for(auto pModule:m_pModules)
		{
			if(pModule->strModuleName->Find(strModule->Get()) != std::string::npos)
			{
				strRetn->AppendF("%s",pModule->strModulePath->Get());
				break;
			}
		}
	}
	return strRetn;
}

void CModuleManager::LoadModule(CString *strModule, CString *strModulePath, bool bForce)
{
	// Load the test module
	if(strModulePath->GetLength() < 1)
	{
		for(auto pModule:m_pModules)
		{
			if(pModule->strModuleName->Find(strModule->Get()) != std::string::npos)
			{
				strModulePath->AppendF("%s",pModule->strModulePath->Get());
				break;
			}
		}
	}

	// Check if we have found any modules
	if(strModulePath->GetLength() < 1)
		return;

	CString strModuleToLoad = CString("%s",strModulePath->Get());

	// Load it
	HMODULE hModule = LoadLibraryA(strModuleToLoad.Get());
	if(hModule != NULL)
	{
		typedef void (*SetScriptHandler)(DWORD);
		SetScriptHandler pScriptHandler;
		pScriptHandler = (SetScriptHandler)GetProcAddress(hModule,"SetOffset");
				
		if(pScriptHandler != NULL)
			pScriptHandler(0xFFFFFFF);
	}
}