//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPlayerNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPlayerNatives_h
#define CPlayerNatives_h

#include <Scripting/CScriptVM.h>
#include <lua/lua.h>

#define GET_SET_(x) static int Get##x(int * VM); \
	static int Set##x(int * VM);

class CPlayerNatives {

private:
	static int	IsConnected(int * pVM);

	GET_SET_(Armour);
	GET_SET_(Clothes);
	GET_SET_(Color);
	GET_SET_(Dimension);
	GET_SET_(Heading);
	GET_SET_(Health);
	GET_SET_(Model);
	GET_SET_(Name);
public:
	static void Register(CScriptVM* pVM);
};

#endif // CPlayerNatives_h