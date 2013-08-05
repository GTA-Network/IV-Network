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

#include <Scripting/CSquirrel.h>

class CPlayerNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CPlayerNatives_h