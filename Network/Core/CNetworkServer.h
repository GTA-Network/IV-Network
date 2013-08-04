//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
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

public:
	CNetworkServer();
	~CNetworkServer();

	bool EnsureStarted(unsigned short usPort, int iMaxPlayers, string strHostAddress);
	void EnsureStopped(int iBlockDuration = 10);	
	void Process();
	CNetPlayerSocket * GetPlayerSocket(EntityId playerId);
	bool IsPlayerConnected(EntityId playerId);
	unsigned int RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel);
	void DisconnectPlayer(EntityId playerid, bool bSendDisconnectionNotification, ePacketPriority disconnectionPacketPriority);
	void BanIp(string strIpAddress, unsigned int uiTimeMilliseconds);
	void UnbanIp(string strIpAddress);
	int GetPlayerLastPing(EntityId playerId);
	int GetPlayerAveragePing(EntityId playerId);

	CRPCHandler * GetRpcHandler() { return m_pRpcHandler; }
	void SetRpcHandler(CRPCHandler * pRpcHandler) { m_pRpcHandler = pRpcHandler; }
};

#endif // CNetworkServer_h