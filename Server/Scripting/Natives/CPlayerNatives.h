//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CPlayerNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPlayerNatives_h
#define CPlayerNatives_h

#include <Scripting/CScriptVM.h>
#include <lua/lua.h>

class CPlayerNatives {

private:
	static int	Create(int* pVM);
public:
	static void Register(CScriptVM* pVM);
};

#endif // CPlayerNatives_h