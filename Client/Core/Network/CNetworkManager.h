//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetworkManager.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CNetworkManager_h
#define CNetworkManager_h

#include <NetCommon.h>

class CNetworkManager {
private:
	unsigned					m_uiLastConnectionTry;
	bool						m_bConnecting;
	eNetworkState				m_eState;
	
	void						UpdateNetwork();
	void						ConnectionAccepted(NetPacket * pPacket);

public:
								CNetworkManager();
								~CNetworkManager();

	virtual void				Process();
	
	virtual void				Startup();
	virtual void				ShutDown();
	virtual void				Connect();
	virtual void				Disconnect();
	virtual bool				IsConnected() { return (m_eState == NETSTATE_CONNECTED); }
	virtual void				Call(const char * szUnique, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char orderingChannel, bool bBroadcast );
	
	virtual void 				SetNetworkState(eNetworkState pState) { m_eState = pState; }
	virtual eNetworkState		GetNetworkState() { return m_eState; }
};

#endif // CNetworkManager_h