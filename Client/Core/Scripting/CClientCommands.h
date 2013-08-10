//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CClientCommands.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CClientCommands_h
#define CClientCommands_h

#include <Common.h>

class CClientCommands {

private:

public:
	CClientCommands() { };
	~CClientCommands() { };

	static bool		HandleUserInput(CString * strCommand, CString strParameters);
};

#endif // CClientCommands_h