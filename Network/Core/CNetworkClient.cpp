//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CNetworkClient.cpp
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkClient.h"

#define INVALID_PACKET_ID 0xFF

// Init
CNetworkClient::CNetworkClient()
{
	m_pNetPeer = new RakNet::RakPeer();
	m_pNetPeer->AttachPlugin(this);
}

// Cleanup
CNetworkClient::~CNetworkClient()
{
	SAFE_DELETE(m_pNetPeer);
}

// Ensures peer is started with options. If start failed, returns false
bool CNetworkClient::EnsureStarted()
{
	RakNet::StartupResult res = m_pNetPeer->Startup(1, &RakNet::SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL);

	if(res == RakNet::RAKNET_STARTED)
		m_pNetPeer->SetMaximumIncomingConnections(1);

	return res == RakNet::RAKNET_STARTED || res == RakNet::RAKNET_ALREADY_STARTED;
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

			// Set the player socket binary address
			//m_serverSocket.ulBinaryAddress = systemAddress.address.addr4.sin_addr.s_addr;

			// Set the player socket port
			m_state.usPort = ntohs(systemAddress.address.addr4.sin_port);

			// Reset the bit stream for reuse
			CBitStream bitStreamSend;

			// Write the packet id
			bitStreamSend.Write((PacketId)ID_USER_PACKET_ENUM);

			// Send the packet
			m_state.ucState = 2;
			//Send(&bitStreamSend, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, false);
			//m_bConnected = false;
			// crackfixme
			return INVALID_PACKET_ID;
		}
		break;

		// Connection accepted from server:
	case (ID_USER_PACKET_ENUM + 1):
		{
			// Set our connected state
			m_state.ucState = 3;

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
			// Create the new packet
			pPacket = new NetPacket();

			// Set the packet id
			pPacket->id = packetId;

			// Set the packet player socket
			//pPacket->pPlayerSocket = &m_serverSocket;

			// Set the packet length
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

// Sends RPC packet to server
unsigned int CNetworkClient::RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char cOrderingChannel)
{
	CBitStream bitStream;
	bitStream.Write((PacketId)PACKET_RPC);
	bitStream.Write(rpcId);
    bitStream.Write((char *)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed());

	return m_pNetPeer->Send((char *)bitStream.GetData(), bitStream.GetNumberOfBytesUsed(), 
		(PacketPriority)priority, (PacketReliability)reliability, cOrderingChannel, m_state.m_serverAddress, false);
}

// Closes connection to a client (optionally send notification)
void CNetworkClient::Disconnect(bool bSendDisconnectionNotification, ePacketPriority disconnectionPacketPriority)
{
	m_state.ucState = 0;
	m_pNetPeer->CloseConnection(m_state.m_serverAddress, bSendDisconnectionNotification, 0, (PacketPriority)disconnectionPacketPriority);
	EnsureStopped(500);
	EnsureStarted();
}