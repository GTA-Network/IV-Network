//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrelScriptArgument.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSquirrelScriptArgument_h
#define CSquirrelScriptArgument_h

#include "CScriptArgument.h"
#include <Squirrel/squirrel.h>

class CSquirrelScriptArgument : public CScriptArgument {

private:

public:
	CSquirrelScriptArgument();
	CSquirrelScriptArgument(int i) : CScriptArgument(i) { }
	CSquirrelScriptArgument(bool b) : CScriptArgument(b) { }
	CSquirrelScriptArgument(float f) : CScriptArgument(f) { }
	CSquirrelScriptArgument(CString str) : CScriptArgument(str) { }
	CSquirrelScriptArgument(CString * str) : CScriptArgument(str) { }
	CSquirrelScriptArgument(const char* sz) : CScriptArgument(sz) { }
	CSquirrelScriptArgument(CBitStream * pBitStream);
	CSquirrelScriptArgument(const CSquirrelScriptArgument& p);
	~CSquirrelScriptArgument();

	bool                 push(SQVM * pVM);
	bool                 pushFromStack(SQVM * pVM, int idx);
};

#endif // CSquirrelScriptArgument_h