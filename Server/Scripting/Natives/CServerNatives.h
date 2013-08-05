//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CServerNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CServerNatives_h
#define CServerNatives_h

#include <Scripting/CSquirrel.h>

class CServerNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CServerNatives_h