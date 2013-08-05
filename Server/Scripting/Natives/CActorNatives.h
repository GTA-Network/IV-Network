//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CActorNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CActorNatives_h
#define CActorNatives_h

#include <Scripting/CSquirrel.h>

class CActorNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CActorNatives_h