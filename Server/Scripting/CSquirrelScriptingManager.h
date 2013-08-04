//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScriptingManager.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSquirrelScriptingManager_h
#define CSquirrelScriptingManager_h

#include "CScriptingManager.h"
#include "CSquirrelScript.h"

class CSquirrelScriptingManager : public CScriptingManager {

private:

public:
	CSquirrelScriptingManager();
	~CSquirrelScriptingManager();

	CScript *			LoadScript(CString strScript, CString strPath);
	void				UnloadScript(CScript* pScript);
	void				UnloadAll();
	void				RegisterConstant(CString strConstantName, CScriptArgument value);
};

#endif // CSquirrelScriptingManager_h