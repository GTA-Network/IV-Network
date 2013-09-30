//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
#include <Game/CGameFuncs.h>

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
					CModule * pModule = new CModule(CString("%s",FindFileData.cFileName));
					pModule->SetPath(sTempPath);

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
		strModules->AppendF("%s\n",pModule->GetName().Get());
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
			if(pModule->GetName().Find(strModule->Get()) != std::string::npos)
			{
				strRetn->AppendF("%s",pModule->GetPath().Get());
				break;
			}
		}
	}
	return strRetn;
}

void CModuleManager::LoadModule(CString *strModule, CString *strModulePath, bool bForce)
{
	// Load the module
	if(strModulePath->GetLength() < 1)
	{
		for(auto pModule:m_pModules)
		{
			if(pModule->GetName().Find(strModule->Get()) != std::string::npos)
			{
				// Update path
				strModulePath->AppendF("%s",pModule->GetPath().Get());

				// Load module
				pModule->Load();
			}
		}
	}
	return;
}