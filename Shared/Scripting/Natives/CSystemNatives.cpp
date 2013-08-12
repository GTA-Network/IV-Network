//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CSystemNatives.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSystemNatives.h"

#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>

void CSystemNatives::Register(CScriptVM * pVM)
{
	pVM->RegisterFunction("print", Print);
}

int CSystemNatives::Print(int * VM)
{
	// Just an example how the new scripting works with a lua or a squirrel vm its not needed to create a native for every language
	CResource* pResource = CResourceManager::GetInstance()->Get(VM);
	
	if(pResource)
	{
		// We do not have to split it here cause our CScriptVM class provides the nessessary push and pop/get methods
		CScriptVM* pVM = pResource->GetVM();
		pVM->ResetStackIndex();
		CString strPrint;
		pVM->PopString(strPrint);
		CLogFile::Printf(strPrint);

		pVM->ResetStackIndex();
	}

	return 0;
}