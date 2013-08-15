//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CScriptClasses.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptClasses_h
#define CScriptClasses_h

#include <Scripting/CScriptVM.h>

class CScriptClasses {
private:
	static int	CreateEntity(int * pVM);
public:
	static void Register(CScriptVM* pVM);
};

#endif // CScriptClasses_h