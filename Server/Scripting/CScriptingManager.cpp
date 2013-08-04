//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScriptingManager.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptingManager.h"

CScriptingManager::CScriptingManager()
{

}


CScriptingManager::~CScriptingManager()
{

}


void CScriptingManager::UnloadAll()
{
	for(auto pScript : m_Scripts)
	{
		UnloadScript(pScript);
	}
}