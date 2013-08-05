//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CNetworkClient.cpp
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkClient.h"

// Init
CNetworkClient::CNetworkClient()
{
	m_pNetPeer = new RakNet::RakPeer();
	m_pNetPeer->AttachPlugin(this);
	m_state.Clear();
}

// Cleanup
CNetworkClient::~CNetworkClient()
{
	SAFE_DELETE(m_pNetPeer);
}

// Ensures client peer is started. If start failed, returns false
bool CNetworkClient::EnsureStarted()
{
	m_state.peerStateCode = m_pNetPeer->Startup(1, &RakNet::SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL);
	return (m_state.peerStateCode == RakNet::RAKNET_STARTED || m_state.peerStateCode == RakNet::RAKNET_ALREADY_STARTED);
}

// Stops peer
void CNetworkClient::EnsureStopped(int iBlockDuration)
{
	if(!m_state.IsDisconnected())
		Disconnect();

	m_pNetPeer->Shutdown(iBlockDuration);
}

// Process received packet to an internal packet id
PacketId CNetworkClient::ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength)
{
	// Get the player id
	EntityId playerId = (EntityId)systemAddress.systemIndex;

	// Are we not fully connected yet?
	if(!m_state.IsConnected())
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

		// First server reply received, send ack
	case ID_USER_PACKET_ENUM:
		{
			// Construct the bit stream
			CBitStream bitStream(ucData, iLength, false);

			// Set our server address
			m_state.m_serverAddress = systemAddress;

			// Set the player socket id
			//m_serverSocket.playerId = playerId; // crackfixme
			m_state.localPlayerId = playerId;

			// Reset the bit stream for reuse
			CBitStream bitStreamSend;

			// Write the packet id
			bitStreamSend.Write((PacketId)ID_USER_PACKET_ENUM);

			// Send the packet
			m_state.joinState = CLIENT_JOINING;
			Send(&bitStreamSend, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, false);
			return INVALID_PACKET_ID;
		}
		break;

		// Connection accepted from server:
	case (ID_USER_PACKET_ENUM + 1):
		{
			// Set our connected state
			m_state.joinState = CLIENT_JOINING;

			// TODO: Reply wth same packet id

			return PACKET_CONNECTION_SUCCEEDED;
		}

	case ID_CONNECTION_ATTEMPT_FAILED:		return PACKET_CONNECTION_FAILED;
	case ID_ALREADY_CONNECTED:				return PACKET_ALREADY_CONNECTED;
	case ID_NO_FREE_INCOMING_CONNECTIONS:	return PACKET_SERVER_FULL;
	case ID_DISCONNECTION_NOTIFICATION:		return PACKET_DISCONNECTED;
	case ID_CONNECTION_LOST:				return PACKET_LOST_CONNECTION;
	case PACKET_CONNECTION_REJECTED:		return PACKET_CONNECTION_REJECTED;
	case ID_CONNECTION_BANNED:				return PACKET_BANNED;
	case ID_INVALID_PASSWORD:				return PACKET_PASSWORD_INVALID;
	}

	// Is the packet a non processed RakNet packet?
	if(packetId < INTERNAL_PACKET_END)
		return INVALID_PACKET_ID;

	// No translation needed
	return packetId;
}

// Receive packet
NetPacket * CNetworkClient::Receive()
{
	// Get a packet from the RakNet packet queue
	RakNet::Packet * pRakPacket = m_pNetPeer->Receive();

	// Did we get a valid packet?
	if(pRakPacket)
	{
		NetPacket * pPacket = NULL;

		// Get the data
		unsigned char * ucData = (pRakPacket->data + sizeof(PacketId));

		// Get the data length
		unsigned int uiLength = (pRakPacket->length - sizeof(PacketId));

		// Process the packet and get the packet id
		PacketId packetId = ProcessPacket(pRakPacket->systemAddress, pRakPacket->data[0], ucData, uiLength);

		// Is this a valid packet?
		if(packetId != INVALID_PACKET_ID)
		{
			// Create the new NetPacket
			pPacket = new NetPacket();
			pPacket->id = packetId;
			pPacket->dataSize = uiLength;

			// Do we have any packet data?
			if(uiLength > 0)
			{
				// Allocate and copy the packet data
				pPacket->data = (unsigned char *)malloc(uiLength);
				memcpy(pPacket->data, ucData, uiLength);
			}
			else
			{
				// Reset the packet data pointer
				pPacket->data = NULL;
			}
		}

		// Free the RakNet packet
		m_pNetPeer->DeallocatePacket(pRakPacket);
		return pPacket;
	}

	// No packets in the queue
	return NULL;
}

// Deallocate NetPacket (after handled)
void CNetworkClient::DeallocatePacket(NetPacket * pPacket)
{
	// Check if we have a disconnection packet
	if(pPacket->id == PACKET_CONNECTION_REJECTED || pPacket->id == PACKET_DISCONNECTED || pPacket->id == PACKET_LOST_CONNECTION)
		Disconnect();

	// Free the packet data
	SAFE_FREE(pPacket->data);

	// Delete the packet
	SAFE_DELETE(pPacket);
}

// Network server pulse
void CNetworkClient::Process()
{
	NetPacket * pPacket = NULL;

	// Loop until we have processed all packets in the packet queue (if any)
	while(pPacket = Receive())
	{
		if(m_pRpcHandler)
			m_pRpcHandler->HandlePacket(pPacket);

		// Deallocate the packet memory used
		DeallocatePacket(pPacket);
	}
}

// Send RPC message to server
unsigned int CNetworkClient::RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel)
{
	int dataLength = pBitStream->GetNumberOfBytesUsed();

	// Create bitStream with RPC identifier and data from bitStream argument
	CBitStream bitStream(sizeof(PacketId) + sizeof(RPCIdentifier) + dataLength);
	bitStream.Write((PacketId)PACKET_RPC);
	bitStream.Write(rpcId);
    bitStream.Write((char *)pBitStream->GetData(), dataLength);

	return Send(&bitStream, priority, reliability, cOrderingChannel);
}

// Send BitStream to server
unsigned int CNetworkClient::Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel)
{
	return m_pNetPeer->Send((char *)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed(), 
		(PacketPriority)priority, (PacketReliability)reliability, cOrderingChannel, m_state.m_serverAddress, false);
}

// Closes connection to a client (optionally send notification)
void CNetworkClient::Disconnect(bool bSendDisconnectionNotification, ePacketPriority disconnectionPacketPriority)
{
	m_state.Clear(); // drop connected flag lol..
	m_pNetPeer->CloseConnection(m_state.m_serverAddress, bSendDisconnectionNotification, 0, (PacketPriority)disconnectionPacketPriority);
	//EnsureStopped();
	//EnsureStarted();
}