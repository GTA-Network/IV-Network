//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkRPC.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CNetworkRPC_h
#define CNetworkRPC_h

#include <Network/NetCommon.h>
#include <Network/RPCIdentifiers.h>

class CNetworkRPC {
private:
	static	bool			m_bRegistered;

public:
	static	void			Register(RakNet::RPC4 * pRPC);
	static	void			Unregister(RakNet::RPC4 * pRPC);
};

#endif