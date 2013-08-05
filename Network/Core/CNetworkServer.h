//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
//
// File: CNetworkServer.h
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CNetworkServer_h
#define CNetworkServer_h

#include "CRakNetInterface.h"
#include "NetCommon.h"
#include <list>
#include "CRPCHandler.hpp"

class CNetworkServer : CRakNetInterface {

private:
	RakNet::RakPeer * m_pNetPeer;
	std::list< CNetPlayerSocket* > m_playerSocketsList;
	CRPCHandler * m_pRpcHandler;

	NetPacket * Receive();
	PacketId ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength);
	void DeallocatePacket(NetPacket * pPacket);
	inline unsigned int Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);

public:
	CNetworkServer();
	~CNetworkServer();

	RakNet::StartupResult Start(unsigned short usPort, int iMaxPlayers, string strHostAddress);
	void EnsureStopped(int iBlockDuration = 10);	
	void Process();
	unsigned int RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel);

	CNetPlayerSocket * GetPlayerSocket(EntityId playerId);
	bool IsPlayerConnected(EntityId playerId);
	void BanIp(string strIpAddress, unsigned int uiTimeMilliseconds);
	void UnbanIp(string strIpAddress);
	int GetPlayerLastPing(EntityId playerId);
	int GetPlayerAveragePing(EntityId playerId);
	void DisconnectPlayer(EntityId playerid, bool bSendDisconnectionNotification, ePacketPriority disconnectionPacketPriority);

	CRPCHandler * GetRpcHandler() { return m_pRpcHandler; }
	void SetRpcHandler(CRPCHandler * pRpcHandler) { m_pRpcHandler = pRpcHandler; }
};

#endif // CNetworkServer_h