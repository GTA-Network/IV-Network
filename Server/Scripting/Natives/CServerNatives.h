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

#include <Scripting/CScriptVM.h>

class CServerNatives {

private:
	static int	GetConfig(int * pVM);
public:
	static void Register(CScriptVM* pVM);
};

#endif // CServerNatives_h