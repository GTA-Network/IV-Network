//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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

class CNetworkServer : CRakNetInterface {

private:
	RakNet::RakPeer * m_pNetPeer;
	std::list< CNetPlayerSocket* > m_playerSocketsList;

	NetPacket * Receive();
	PacketId ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength);
	void DeallocatePacket(NetPacket * pPacket);

public:
	CNetworkServer();
	~CNetworkServer();

	bool EnsureStarted(unsigned short usPort, int iMaxPlayers, string strHostAddress);
	void EnsureStopped(int iBlockDuration);	
	void Process();
	CNetPlayerSocket * GetPlayerSocket(EntityId playerId);
	bool CNetworkServer::IsPlayerConnected(EntityId playerId);
	unsigned int Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);
	unsigned int RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel);
	void DisconnectPlayer(EntityId playerid, bool bSendDisconnectionNotification, ePacketPriority disconnectionPacketPriority);
	void BanIp(string strIpAddress, unsigned int uiTimeMilliseconds);
	void UnbanIp(string strIpAddress);
	int GetPlayerLastPing(EntityId playerId);
	int GetPlayerAveragePing(EntityId playerId);
};

#endif // CNetworkServer_h