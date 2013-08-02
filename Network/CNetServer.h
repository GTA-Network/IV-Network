//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CNetServer.h
// Project: Network.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include <StdInc.h>
#include <list>

class CNetServer : CRakNetInterface, public CNetServerInterface
{
private:
	RakNet::RakPeerInterface * m_pRakPeer;
	String                     m_strPassword;
	PacketHandler_t            m_pfnPacketHandler;
	std::list<CPlayerSocket *> m_playerSocketList;

	PacketId        ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength);
	CPacket *       Receive();
	void            DeallocatePacket(CPacket * pPacket);
	void            RejectKick(EntityId playerId);

public:
	CNetServer();
	~CNetServer();

	bool            Startup(unsigned short usPort, int iMaxPlayers, String strHostAddress = "");
	void            Shutdown(int iBlockDuration);
	void            Process();
	void            SetPassword(String strPassword);
	const char    * GetPassword();
	unsigned int    Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);
	unsigned int    RPC(RPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);
	const char    * GetPlayerIp(EntityId playerId);
	unsigned short  GetPlayerPort(EntityId playerId);
	void            SetPacketHandler(PacketHandler_t pfnPacketHandler) { m_pfnPacketHandler = pfnPacketHandler; }
	PacketHandler_t GetPacketHandler() { return m_pfnPacketHandler; }
	const char    * GetPlayerSerial(EntityId playerId);
	void            KickPlayer(EntityId playerId, bool bSendDisconnectionNotification = true, ePacketPriority disconnectionPacketPriority = PRIORITY_LOW);
	CPlayerSocket * GetPlayerSocket(EntityId playerId);
	bool            IsPlayerConnected(EntityId playerId);
	void            BanIp(String strIpAddress, unsigned int uiTimeMilliseconds);
	void            UnbanIp(String strIpAddress);
	int             GetPlayerLastPing(EntityId playerId);
	int             GetPlayerAveragePing(EntityId playerId);
};
