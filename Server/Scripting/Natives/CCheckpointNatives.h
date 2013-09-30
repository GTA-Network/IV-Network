//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CCheckpointNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CCheckpointNatives_h
#define CCheckpointNatives_h

#include <Scripting/CScriptVM.h>

class CCheckpointNatives {

private:

public:
	static void Register(CScriptVM* pVM);
};

#endif // CCheckpointNatives_h