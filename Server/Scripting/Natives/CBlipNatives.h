//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CBlipNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CBlipNatives_h
#define CBlipNatives_h

#include <Scripting/CSquirrel.h>

class CBlipNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CBlipNatives_h