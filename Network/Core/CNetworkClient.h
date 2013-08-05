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
	sClientState m_state;

	NetPacket * Receive();
	PacketId ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength);
	void DeallocatePacket(NetPacket * pPacket);
	inline unsigned int Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);

public:
	CNetworkClient();
	~CNetworkClient();

	bool EnsureStarted();
	void EnsureStopped(int iBlockDuration = 10);	
	void Process();

	void Connect(string strServerAddress, unsigned short usPort);
	void Disconnect(bool bSendDisconnectionNotification = false, ePacketPriority disconnectionPacketPriority = PRIORITY_IMMEDIATE);
	unsigned int RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);

	CRPCHandler * GetRpcHandler() { return m_pRpcHandler; }
	void SetRpcHandler(CRPCHandler * pRpcHandler) { m_pRpcHandler = pRpcHandler; }
	sClientState GetState() { return m_state; }
};

#endif // CNetworkClient_h