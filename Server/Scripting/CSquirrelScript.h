//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScript.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSquirrelScript_h
#define CSquirrelScript_h

#include "CScript.h"
#include "CSquirrelScriptArgument.h"
#include <Squirrel/squirrel.h>

class CSquirrelScript : public CScript {

private:
	SQVM		* m_pVM;
public:
	CSquirrelScript();
	~CSquirrelScript();

	bool		Load(CString strName, CString strPath);
	void		Unload();

	bool		Execute();


	void		RegisterConstant(CString strConstantName, CSquirrelScriptArgument value);
};

#endif // CSquirrelScript_h