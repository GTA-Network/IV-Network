//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CServerNatives.cpp
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CServerNatives.h"
#include <CSettings.h>
#include <Scripting/ResourceSystem/CResourceManager.h> 
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <SharedUtility.h>
#include <CInput.h>

void CServerNatives::Register(CScriptVM* pVM)
{
	pVM->RegisterFunction("getConfig", GetConfig);
	pVM->RegisterFunction("getTickCount", GetTickCount);
	pVM->RegisterFunction("sendConsoleInput", SendConsoleInput);
}


int CServerNatives::GetConfig(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	CScriptArguments settingsTable;
	for(std::map<CString, SettingsValue *>::iterator iter = CSettings::GetValues()->begin(); iter != CSettings::GetValues()->end(); iter++)
	{
		// Get the setting
		SettingsValue * setting = iter->second;
		
		// Push the setting name onto the stack
		
		// Push the value onto the stack
		if(setting->IsBool())
		{
			settingsTable.push(iter->first.Get());
			settingsTable.push(setting->bValue);
		}
		else if(setting->IsInteger())
		{
			settingsTable.push(iter->first.Get());
			settingsTable.push(setting->iValue);
		}
		else if(setting->IsFloat())
		{
			settingsTable.push(iter->first.Get());
			settingsTable.push(setting->fValue);
		}
		else if(setting->IsString())
		{
			settingsTable.push(iter->first.Get());
			settingsTable.push(CString(setting->strValue));
		}
		else if(setting->IsList())
		{
			settingsTable.push(iter->first.Get());
			// Create a new array
			CScriptArguments settingsArray;

			for(std::list<CString>::iterator iter2 = setting->listValue.begin(); iter2 != setting->listValue.end(); iter2++)
			{
				// Push the list value onto the stack
				settingsArray.push(CString((*iter2).Get()));
			}

			settingsTable.push(settingsArray, true);
		}
	}

	pVM->PushTable(settingsTable);

	pVM->ResetStackIndex();

	return 1;
}

int CServerNatives::Shutdown(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	extern bool g_bClose;
	g_bClose = true;

	pVM->ResetStackIndex();

	return 1;
}

int CServerNatives::GetTickCount(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->Push((int)SharedUtility::GetTime());

	pVM->ResetStackIndex();

	return 1;
}

int CServerNatives::SendConsoleInput(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	CString strPrint;
	pVM->Pop(strPrint);
	CInput::ProcessInput(strPrint);

	pVM->ResetStackIndex();

	return 1;
}