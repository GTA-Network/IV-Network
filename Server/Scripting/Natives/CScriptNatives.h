//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScriptNatives.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptNatives_h
#define CScriptNatives_h

#include <Scripting/CSquirrel.h>

class CScriptNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CScriptNatives_h