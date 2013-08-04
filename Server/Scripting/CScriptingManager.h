//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScriptingManager.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptingManager_h
#define CScriptingManager_h

#include <Common.h>
#include <list>
#include "CScript.h"

class CScriptingManager {

private:
	std::list<CScript*> m_Scripts;
public:
	CScriptingManager();
	~CScriptingManager();

	virtual void		AddScript(CScript * pScript) { m_Scripts.push_back(pScript); }
	virtual CScript*	LoadScript(CString strScript, CString strPath) = 0;
	virtual void		UnloadScript(CScript* pScript) = 0;
	virtual void		UnloadAll() = 0;
};

#endif // CScriptingManager_h