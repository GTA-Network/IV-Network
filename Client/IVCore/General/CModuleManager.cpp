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