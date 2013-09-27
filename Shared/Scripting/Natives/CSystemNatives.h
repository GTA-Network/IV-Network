//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CSystemNatives.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSystemNatives_h
#define CSystemNatives_h

#include <Scripting/CScriptVM.h>

class CSystemNatives {

private:
	static int	Print(int * pVM);
	static int  Logf(int * pVM); 
	static int	CreateEntity(int * pVM);
	static int  Date(int * pVM); 
public:
	static void Register(CScriptVM* pVM);
};

#endif // CSystemNatives_h