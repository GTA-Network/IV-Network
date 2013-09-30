//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkRPC.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CNetworkRPC_h
#define CNetworkRPC_h

#include <Network/NetCommon.h>

class CNetworkRPC
{
private:

	static	bool		m_bRegistered;

public:

	static	void		Register(RakNet::RPC4 * pRPC);
	static	void		Unregister(RakNet::RPC4 * pRPC);

};

#endif // CNetworkRPC_h