//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CScriptNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptNatives_h
#define CScriptNatives_h

#include <Scripting/CScriptVM.h>

class CScriptNatives {

private:

public:
	static void Register(CScriptVM* pVM);
};

#endif // CScriptNatives_h