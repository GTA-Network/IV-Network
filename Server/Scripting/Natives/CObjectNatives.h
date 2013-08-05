//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CObjectNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CObjectNatives_h
#define CObjectNatives_h

#include <Scripting/CSquirrel.h>

class CObjectNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CObjectNatives_h