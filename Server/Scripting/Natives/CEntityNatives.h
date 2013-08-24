//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CEntityNatives.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEntityNatives_h
#define CEntityNatives_h

#include <Scripting/CScriptVM.h>

class CEntityNatives {
private:
	static int	SetPosition(int * VM);
	static int	GetPosition(int * VM);
	
	static int	SetRotation(int * VM);
	static int	GetRotation(int * VM);

	static int	SetMoveSpeed(int * VM);
	static int	GetMoveSpeed(int * VM);

	static int	SetTurnSpeed(int * VM);
	static int	GetTurnSpeed(int * VM);

	static int	Destroy(int * VM);
public:
	static void Register(CScriptVM * pVM);
};

#endif // CEntityNatives_h