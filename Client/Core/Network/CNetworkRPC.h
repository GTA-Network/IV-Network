//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetworkRPC.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CNetworkRPC_h
#define CNetworkRPC_h

#include <NetCommon.h>
#include <Network/RPCIdentifiers.h>
#include <CRPCHandler.hpp>

class CNetworkRPC {
private:
	static	bool			m_bRegistered;

public:
	static	void			RegisterRPCs(CRPCHandler * pRPC);
	static	void			UnregisterRPCs(CRPCHandler * pRPC);
	static  CString			GetRPCCodex(eRPCIdentifier pRPC) { return CString("IVMP0xF%dF",int(pRPC)).Get(); }
};

#endif