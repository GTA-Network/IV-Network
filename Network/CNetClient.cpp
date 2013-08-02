//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CNetClient.cpp
// Project: Network.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include <StdInc.h>

CNetClient::CNetClient()
{
	// Create the rak peer instance
	m_pRakPeer = new RakNet::RakPeer();

	// Attach ourselves to the rak peer instance
	m_pRakPeer->AttachPlugin(this);

	// Reset the server address
	m_serverAddress = RakNet::UNASSIGNED_SYSTEM_ADDRESS;

	// Reset the connected flag
	m_bConnected = false;

	// Reset the port
	m_usPort = 0xFFFF;

	// Reset the packet handler
	m_pfnPacketHandler = NULL;

	// Create the server socket
	m_serverSocket = CPlayerSocket();
}

CNetClient::~CNetClient()
{
	SAFE_DELETE(m_pRakPeer);
}

bool CNetClient::Startup()
{
	// TODO: Return the real result instead of a boolean
	return (m_pRakPeer->Startup(1, &RakNet::SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED);
}

void CNetClient::Shutdown(int iBlockDuration)
{
	if(IsConnected())
		Disconnect();

	m_pRakPeer->Shutdown(iBlockDuration);
}

eConnectionAttemptResult CNetClient::Connect()
{
	if(IsConnected())
		Disconnect();

	if(m_strHost.IsNotEmpty())
		return (eConnectionAttemptResult)m_pRakPeer->Connect(m_strHost.Get(), m_usPort, m_strPassword.Get(), m_strPassword.GetLength());

	return NO_HOST_SET;
}

void CNetClient::Disconnect()
{
	if(IsConnected())
	{
		m_bConnected = false;
		m_pRakPeer->CloseConnection(m_serverAddress, true);
		Shutdown(500);
		Startup();
		m_serverAddress = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
		m_serverSocket = CPlayerSocket();
	}
}

void CNetClient::Process()
{
	CPacket * pPacket = NULL;

	// Loop until we have processed all packets in the packet queue (if any)
	while(pPacket = Receive())
	{
		// Do we have a packet handler?
		if(m_pfnPacketHandler)
		{
			// Pass it to the packet handler
			m_pfnPacketHandler(pPacket);
		}
		// Deallocate the packet memory used
		DeallocatePacket(pPacket);
	}
}

void CNetClient::SetPassword(String strPassword)
{
	m_pRakPeer->SetIncomingPassword(strPassword.Get(), strPassword.GetLength());
	m_strPassword = strPassword;
}

const char * CNetClient::GetPassword()
{
	return m_strPassword.Get();
}

unsigned int CNetClient::Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel)
{
	if(IsConnected() && pBitStream)
		return m_pRakPeer->Send((char *)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed(), (PacketPriority)priority, (PacketReliability)reliability, cOrderingChannel, m_serverAddress, false);

	return 0;
}

unsigned int CNetClient::RPC(RPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel)
{
	if(IsConnected())
	{
		CBitStream bitStream;
		bitStream.Write((PacketId)PACKET_RPC);
		bitStream.Write(rpcId);

		if(pBitStream)
			bitStream.Write((char *)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed());

		return m_pRakPeer->Send((char *)bitStream.GetData(), bitStream.GetNumberOfBytesUsed(), (PacketPriority)priority, (PacketReliability)reliability, cOrderingChannel, m_serverAddress, false);
	}

	return 0;
}

void CNetClient::SetHost(String strHost)
{
	m_strHost.Set(strHost.Get());
}

const char * CNetClient::GetHost()
{
	return m_strHost.Get();
}

void CNetClient::SetPort(unsigned short usPort)
{
	m_usPort = usPort;
}

unsigned short CNetClient::GetPort()
{
	return m_usPort;
}

bool CNetClient::IsConnected()
{
	return m_bConnected;
	//return m_pRakPeer->IsConnected(UNASSIGNED_SYSTEM_ADDRESS);
}

PacketId CNetClient::ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength)
{
	// Get the player id
	EntityId playerId = (EntityId)systemAddress.systemIndex;

	// Are we not fully connected yet?
	if(!m_bConnected)
	{
		// Is this not a pre-connect packet?
		switch(packetId)
		{
		case ID_USER_PACKET_ENUM:
		case (ID_USER_PACKET_ENUM + 1):
		case PACKET_CONNECTION_REJECTED:
		case ID_CONNECTION_ATTEMPT_FAILED:
		case ID_ALREADY_CONNECTED:
		case ID_NO_FREE_INCOMING_CONNECTIONS:
		case ID_CONNECTION_BANNED:
		case ID_INVALID_PASSWORD:
			break;
		default:
			// Don't process the packet
			return INVALID_PACKET_ID;
		}
	}

	// Does the packet need processing?
	switch(packetId)
	{
	//case ID_CONNECTION_REQUEST_ACCEPTED: // No longer used (See (ID_USER_PACKET_ENUM + 1))
	case ID_USER_PACKET_ENUM: // Send initial data
		{
			// Construct the bit stream
			CBitStream bitStream(ucData, iLength, false);

			// Set our server address
			m_serverAddress = systemAddress;

			// Set the player socket id
			m_serverSocket.playerId = playerId;

			// Set the player socket binary address
			m_serverSocket.ulBinaryAddress = systemAddress.address.addr4.sin_addr.s_addr;

			// Set the player socket port
			m_serverSocket.usPort = ntohs(systemAddress.address.addr4.sin_port);

			// Reset the bit stream for reuse
			CBitStream bitStreamSend;

			// Write the packet id
			bitStreamSend.Write((PacketId)ID_USER_PACKET_ENUM);

			// Write the network module version
			bitStreamSend.Write((BYTE)NETWORK_MODULE_VERSION);

			// Send the packet
			m_bConnected = true;
			Send(&bitStreamSend, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, false);
			m_bConnected = false;
			return INVALID_PACKET_ID;
		}
		break;
	case (ID_USER_PACKET_ENUM + 1): // Connection accepted
		{
			// Set our connected state
			m_bConnected = true;

			// Construct the bit stream
			CBitStream bitStream;

			// Write the packet id
			bitStream.Write((PacketId)(ID_USER_PACKET_ENUM + 1));

			// Send the packet
			Send(&bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, false);
			return PACKET_CONNECTION_SUCCEEDED;
		}
		break;
	case ID_CONNECTION_ATTEMPT_FAILED:
		return PACKET_CONNECTION_FAILED;
		break;
	case ID_ALREADY_CONNECTED:
		return PACKET_ALREADY_CONNECTED;
		break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
		return PACKET_SERVER_FULL;
		break;
	case ID_DISCONNECTION_NOTIFICATION:
		return PACKET_DISCONNECTED;
		break;
	case ID_CONNECTION_LOST:
		return PACKET_LOST_CONNECTION;
		break;
	case PACKET_CONNECTION_REJECTED:
		return PACKET_CONNECTION_REJECTED;
		break;
	case ID_CONNECTION_BANNED:
		return PACKET_BANNED;
		break;
	case ID_INVALID_PASSWORD:
		return PACKET_PASSWORD_INVALID;
		break;
	}

	// Is the packet a non processed RakNet packet?
	if(packetId < INTERNAL_PACKET_END)
		return INVALID_PACKET_ID;

	// No translation needed
	return packetId;
}

CPacket * CNetClient::Receive()
{
	// Get a packet from the RakNet packet queue
	RakNet::Packet * pRakPacket = m_pRakPeer->Receive();

	// Did we get a valid packet?
	if(pRakPacket)
	{
		CPacket * pPacket = NULL;

		// Get the data
		unsigned char * ucData = (pRakPacket->data + sizeof(PacketId));

		// Get the data length
		unsigned int uiLength = (pRakPacket->length - sizeof(PacketId));

		// Process the packet and get the packet id
		PacketId packetId = ProcessPacket(pRakPacket->systemAddress, pRakPacket->data[0], ucData, uiLength);

		// Is this a valid packet?
		if(packetId != INVALID_PACKET_ID)
		{
			// Create the new packet
			pPacket = new CPacket();

			// Set the packet id
			pPacket->packetId = packetId;

			// Set the packet player socket
			pPacket->pPlayerSocket = &m_serverSocket;

			// Set the packet length
			pPacket->uiLength = uiLength;

			// Do we have any packet data?
			if(uiLength > 0)
			{
				// Allocate and set the packet data
				pPacket->ucData = (unsigned char *)malloc(uiLength);

				// Copy the packet data
				memcpy(pPacket->ucData, ucData, uiLength);
			}
			else
			{
				// Reset the packet data pointer
				pPacket->ucData = NULL;
			}
		}

		// Free the RakNet packet
		m_pRakPeer->DeallocatePacket(pRakPacket);
		return pPacket;
	}

	// No packets in the queue
	return NULL;
}

void CNetClient::DeallocatePacket(CPacket * pPacket)
{
	// Check if we have a disconnection packet
	if(pPacket->packetId == PACKET_CONNECTION_REJECTED || pPacket->packetId == PACKET_DISCONNECTED || pPacket->packetId == PACKET_LOST_CONNECTION)
		Disconnect();

	// Free the packet data
	SAFE_FREE(pPacket->ucData);

	// Delete the packet
	SAFE_DELETE(pPacket);
}

CNetStats * CNetClient::GetNetStats()
{
	RakNet::RakNetStatistics * pRakStats = m_pRakPeer->GetStatistics(RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	static CNetStats netStats;
	memcpy(netStats.ulValueOverLastSecond, pRakStats->valueOverLastSecond, (sizeof(NetStat_t) * NET_STAT_METRICS_COUNT));
	memcpy(netStats.ulRunningTotal, pRakStats->runningTotal, (sizeof(NetStat_t) * NET_STAT_METRICS_COUNT));
	netStats.ulConnectionStartTime = pRakStats->connectionStartTime;
	netStats.bIsLimitedByCongestionControl = pRakStats->isLimitedByCongestionControl;
	netStats.ulBPSLimitByCongestionControl = pRakStats->BPSLimitByCongestionControl;
	netStats.bIsLimitedByOutgoingBandwidthLimit = pRakStats->isLimitedByOutgoingBandwidthLimit;
	netStats.ulBPSLimitByOutgoingBandwidthLimit = pRakStats->BPSLimitByOutgoingBandwidthLimit;
	memcpy(netStats.uiMessageInSendBuffer, pRakStats->messageInSendBuffer, (sizeof(unsigned int) * PRIORITY_COUNT));
	memcpy(netStats.dBytesInSendBuffer, pRakStats->bytesInSendBuffer, (sizeof(double) * PRIORITY_COUNT));
	netStats.uiMessagesInResendBuffer = pRakStats->messagesInResendBuffer;
	netStats.ulBytesInResendBuffer = pRakStats->bytesInResendBuffer;
	netStats.fPacketlossLastSecond = pRakStats->packetlossLastSecond;
	netStats.fPacketlossTotal = pRakStats->packetlossTotal;
	return &netStats;
}

int CNetClient::GetLastPing()
{
	return m_pRakPeer->GetLastPing(m_serverAddress);
}

int CNetClient::GetAveragePing()
{
	return m_pRakPeer->GetAveragePing(m_serverAddress);
}
