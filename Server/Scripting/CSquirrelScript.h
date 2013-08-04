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

	static void      PrintFunction(SQVM * pVM, const char * szFormat, ...);
	static void      CompilerErrorFunction(SQVM * pVM, const char * szError, const char * szSource, int iLine, int iColumn);
	static SQInteger PrintErrorFunction(SQVM * pVM);
public:
	CSquirrelScript();
	~CSquirrelScript();

	bool		Load(CString strName, CString strPath);
	void		Unload();

	bool		Execute();


	void		RegisterConstant(CString strConstantName, CSquirrelScriptArgument value);
	void		RegisterFunction(CString strFunctionName, SQFUNCTION pfnFunction, int iParameterCount, CString strFunctionTemplate);
};

#endif // CSquirrelScript_h