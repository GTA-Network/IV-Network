//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScriptArgument.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptArgument_h
#define CScriptArgument_h

#include <Common.h>
#include <Lua/lua.hpp>
#include "CScriptArguments.h"

class CScriptArgument {

private:
	union
	{
		int i;
		bool b;
		float f;
		CString * str;
		CScriptArguments * pArray;
	} data;
public:
	CScriptArgument();
	~CScriptArgument();
};

#endif // CScriptArgument_h