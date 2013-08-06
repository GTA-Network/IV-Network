//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CServerRPCHandler.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CServerRPCHandler_h
#define CServerRPCHandler_h

#include <NetCommon.h>
#include <Network/RPCIdentifiers.h>
#include <CRPCHandler.hpp>

class CServerRPCHandler : public CRPCHandler
{
private:
	// All static RPCFunction`s

public:
	void			RegisterRPCs();
	void			UnregisterRPCs();
};

#endif // CServerRPCHandler_h