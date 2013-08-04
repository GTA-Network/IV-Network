//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScriptingManager.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelScriptingManager.h"

CSquirrelScriptingManager::CSquirrelScriptingManager()
{

}

CSquirrelScriptingManager::~CSquirrelScriptingManager()
{

}

CScript* CSquirrelScriptingManager::LoadScript(CString strScript, CString strPath)
{
	CSquirrelScript * pScript = new CSquirrelScript();


	
	// Add script to our parent Script list;
	AddScript(pScript);
	

	return pScript;
}

void CSquirrelScriptingManager::UnloadScript(CScript* pScript)
{

}

void CSquirrelScriptingManager::UnloadAll()
{

}