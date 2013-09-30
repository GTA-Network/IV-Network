//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CActorNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CActorNatives_h
#define CActorNatives_h

#include <Scripting/CScriptVM.h>

class CActorNatives {

private:

public:
	static void Register(CScriptVM* pVM);
};

#endif // CActorNatives_h