//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CObjectNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CObjectNatives_h
#define CObjectNatives_h

#include <Scripting/CScriptVM.h>

class CObjectNatives {

private:

public:
	static void Register(CScriptVM* pVM);
};

#endif // CObjectNatives_h