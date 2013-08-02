//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CNetClient.h
// Project: Network.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include <StdInc.h>

class CNetClient : CRakNetInterface, public CNetClientInterface
{
private:
	RakNet::RakPeerInterface * m_pRakPeer;
	RakNet::SystemAddress      m_serverAddress;
	bool                       m_bConnected;
	String                     m_strHost;
	unsigned short             m_usPort;
	String                     m_strPassword;
	PacketHandler_t            m_pfnPacketHandler;
	CPlayerSocket              m_serverSocket;

	PacketId                 ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength);
	CPacket *                Receive();
	void                     DeallocatePacket(CPacket * pPacket);

public:
	CNetClient();
	~CNetClient();

	bool                     Startup();
	void                     Shutdown(int iBlockDuration);
	eConnectionAttemptResult Connect();
	void                     Disconnect();
	void                     Process();
	void                     SetPassword(String strPassword);
	const char             * GetPassword();
	unsigned int             Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);
	unsigned int             RPC(RPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel = PACKET_CHANNEL_DEFAULT);
	void                     SetHost(String strHost);
	const char             * GetHost();
	void                     SetPort(unsigned short usPort);
	unsigned short           GetPort();
	bool                     IsConnected();
	void                     SetPacketHandler(PacketHandler_t pfnPacketHandler) { m_pfnPacketHandler = pfnPacketHandler; }
	PacketHandler_t          GetPacketHandler() { return m_pfnPacketHandler; }
	CPlayerSocket          * GetServerSocket() { return &m_serverSocket; }
	CNetStats              * GetNetStats();
	int                      GetLastPing();
	int                      GetAveragePing();
};
