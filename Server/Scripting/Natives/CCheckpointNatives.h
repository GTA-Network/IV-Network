//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CCheckpointNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CCheckpointNatives_h
#define CCheckpointNatives_h

#include <Scripting/CSquirrel.h>

class CCheckpointNatives {

private:

public:
	static void Register(CSquirrel* pVM);
};

#endif // CCheckpointNatives_h