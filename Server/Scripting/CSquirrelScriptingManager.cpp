//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScriptingManager.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSquirrelScriptingManager.h"
#include <CLogFile.h>

CSquirrelScriptingManager::CSquirrelScriptingManager()
{

}

CSquirrelScriptingManager::~CSquirrelScriptingManager()
{

}

CScript* CSquirrelScriptingManager::LoadScript(CString strScript, CString strPath)
{
	CSquirrelScript * pScript = new CSquirrelScript();

	if(!pScript->Load(strScript, strPath))
	{
		delete pScript;

		return NULL;
	}
	
	// Add script to our parent Script list;
	AddScript(pScript);
	
	// Load script into vm and execute it
	if(!pScript->Execute())
	{
		Remove(pScript);

		delete pScript;

		CLogFile::Printf("Failed to execute script %s", strScript.Get());
		
		return NULL;
	}

	// TODO: add event calls to scriptInit and scriptLoad

	return pScript;
}

void CSquirrelScriptingManager::UnloadScript(CScript* pScript)
{
	if(pScript)
	{
		// TODO: add event calls to scriptExit and scriptUnload


		pScript->Unload();

		// Remove the script from parent´s list
		Remove(pScript);

		delete pScript;
	}
}

void CSquirrelScriptingManager::UnloadAll()
{
	CScriptingManager::UnloadAll();
}