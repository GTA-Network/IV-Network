//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CPickupNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPickupNatives_h
#define CPickupNatives_h

#include <Scripting/CSquirrel.h>

class CPickupNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CPickupNatives_h