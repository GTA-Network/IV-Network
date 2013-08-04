//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CNetworkClient.h
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CNetworkClient_h
#define CNetworkClient_h

#include "CRakNetInterface.h"
#include "NetCommon.h"
#include <list>
#include "CRPCHandler.hpp"

class CNetworkClient : CRakNetInterface {

private:
	RakNet::RakPeer *		m_pNetPeer;
	CRPCHandler *			m_pRpcHandler;
	
	// Connection status
	struct sConnectionState
	{
		unsigned char ucState;
		RakNet::SystemAddress m_serverAddress;
		EntityId localPlayerId;
		string strHost;
		unsigned short usPort;
		
		bool IsDisconnected() { return ucState == 0; }
		bool IsConnected() { return ucState == 3; }
		bool IsConnecting() { return ucState > 0 && ucState < 3; }
	} m_state;

	NetPacket * Receive();
	PacketId ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength);
	void DeallocatePacket(NetPacket * pPacket);

public:
	CNetworkClient();
	~CNetworkClient();

	bool EnsureStarted();
	void EnsureStopped(int iBlockDuration = 10);	
	void Process();
	sConnectionState GetState() { return m_state; }

	void Connect(string strServerAddress, unsigned short usPort);
	void Disconnect(bool bSendDisconnectionNotification = false, ePacketPriority disconnectionPacketPriority = PRIORITY_IMMEDIATE);
	unsigned int RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);

	CRPCHandler * GetRpcHandler() { return m_pRpcHandler; }
	void SetRpcHandler(CRPCHandler * pRpcHandler) { m_pRpcHandler = pRpcHandler; }
};

#endif // CNetworkClient_h