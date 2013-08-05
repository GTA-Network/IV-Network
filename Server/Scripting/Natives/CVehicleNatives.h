//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CVehicleNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CVehicleNatives_h
#define CVehicleNatives_h

#include <Scripting/CSquirrel.h>

class CVehicleNatives {

private:

public:
	static void Register(CSquirrel * pVM);
};

#endif // CVehicleNatives_h