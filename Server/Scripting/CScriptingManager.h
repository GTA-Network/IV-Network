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

	virtual void				AddScript(CScript * pScript) { m_Scripts.push_back(pScript); }
	virtual void				Remove(CScript * pScript) { m_Scripts.remove(pScript); }
	virtual CScript*			LoadScript(CString strScript, CString strPath) = 0;
	virtual void				UnloadScript(CScript* pScript) = 0;
	virtual void				UnloadAll();

	std::list<CScript *>	  * GetScriptList() { return &m_Scripts; }
	unsigned int				GetScriptCount() { return m_Scripts.size(); }
};

#endif // CScriptingManager_h