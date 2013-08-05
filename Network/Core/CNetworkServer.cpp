//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CNetworkServer.cpp
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkServer.h"

// Init
CNetworkServer::CNetworkServer()
{
	m_pNetPeer = new RakNet::RakPeer();
	m_pNetPeer->AttachPlugin(this);
}

// Cleanup
CNetworkServer::~CNetworkServer()
{
	SAFE_DELETE(m_pNetPeer);
}

// Ensures peer is started with options. If start failed, returns false
RakNet::StartupResult CNetworkServer::EnsureStarted(unsigned short usPort, int iMaxPlayers, string strHostAddress)
{
	RakNet::SocketDescriptor socketDescriptor(usPort, strHostAddress.Get()); 
	RakNet::StartupResult res = m_pNetPeer->Startup(iMaxPlayers, &socketDescriptor, 1, THREAD_PRIORITY_NORMAL);
	return res;
}

// Stops peer
void CNetworkServer::EnsureStopped(int iBlockDuration)
{
	m_pNetPeer->Shutdown(iBlockDuration);
}

// Process packet, to our internal packet id
PacketId CNetworkServer::ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength)
{
	// Get the player id
	EntityId playerId = (EntityId)systemAddress.systemIndex;

	// Is the player not fully connected yet?
	if(!IsPlayerConnected(playerId))
	{
		// Is this a disconnection or connection lost packet?
		if(packetId == ID_DISCONNECTION_NOTIFICATION || packetId == ID_CONNECTION_LOST)
		{
			// Ignore it
			return INVALID_PACKET_ID;
		}

		// Is this not a pre-connect packet?
		if(packetId != ID_NEW_INCOMING_CONNECTION && packetId != ID_USER_PACKET_ENUM)
		{
			// Don't process the packet
			return INVALID_PACKET_ID;
		}
	}

	// Does the packet need processing?
	switch(packetId)
	{
	case ID_NEW_INCOMING_CONNECTION: // Request initial data
		{
			// Construct the bit stream
			CBitStream bitStream;

			// Write the packet id
			bitStream.Write((PacketId)ID_USER_PACKET_ENUM);

			// Send the packet
			//Send(&bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false); // crackfixme
			return INVALID_PACKET_ID;
		}
		break;
	case (ID_USER_PACKET_ENUM + 1): // Client is ready
		return PACKET_NEW_CONNECTION;
		break;
	case ID_DISCONNECTION_NOTIFICATION:
		return PACKET_DISCONNECTED;
		break;
	case ID_CONNECTION_LOST:
			return PACKET_LOST_CONNECTION;
		break;
	}

	// Is the packet a non processed RakNet packet?
	if(packetId < INTERNAL_PACKET_END)
		return INVALID_PACKET_ID;

	// No processing needed
	return packetId;
}

// Receives a next packet on peer
NetPacket * CNetworkServer::Receive()
{
	// Get a packet from the RakNet packet queue
	// and then construct NetPacket
	RakNet::Packet * pRakPacket = m_pNetPeer->Receive();

	// Did we get a packet?
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
			pPacket = new NetPacket;

			// Set the packet player socket
			pPacket->pPlayerSocket = GetPlayerSocket((EntityId)pRakPacket->systemAddress.systemIndex);

			// Set the packet id
			pPacket->id = packetId;

			// Set the packet length
			pPacket->dataSize = uiLength;

			// Do we have any packet data?
			if(uiLength > 0)
			{
				// Allocate and set the packet data
				pPacket->data = new unsigned char[uiLength];//(unsigned char *)malloc(uiLength);

				// Copy the packet data
				memcpy(pPacket->data, ucData, uiLength);
			}
			else
			{
				// Reset the packet data pointer
				pPacket->data = NULL;
			}
		}

		// Delete the RakNet packet
		m_pNetPeer->DeallocatePacket(pRakPacket);
		return pPacket;
	}

	// No packets in the queue
	return NULL;
}

// Finishes packet
void CNetworkServer::DeallocatePacket(NetPacket * pPacket)
{
	// Check if we have a disconnection packet
	if(pPacket->id == PACKET_DISCONNECTED || pPacket->id == PACKET_LOST_CONNECTION)
	{
		// Get the player socket
		CNetPlayerSocket * pPlayerSocket = pPacket->pPlayerSocket;

		// Delete the player socket
		SAFE_DELETE(pPlayerSocket);

		// Remove the player socket from the player socket list
		if(m_playerSocketsList.size() == 1)
			m_playerSocketsList.clear();
		else
			m_playerSocketsList.remove(pPlayerSocket);
	}

	SAFE_FREE(pPacket->data);
	SAFE_DELETE(pPacket);
}

// Network server pulse
void CNetworkServer::Process()
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

// Sends RPC message to player
unsigned int CNetworkServer::RPC(eRPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel)
{
	if(IsPlayerConnected(playerId) == false)
		return 0;
	
	int dataLength = pBitStream->GetNumberOfBytesUsed();

	// Create bitStream with RPC identifier and data from bitStream argument
	CBitStream bitStream(sizeof(PacketId) + sizeof(RPCIdentifier) + dataLength);
	bitStream.Write((PacketId)PACKET_RPC);
	bitStream.Write(rpcId);
    bitStream.Write((char *)pBitStream->GetData(), dataLength);

	return Send(&bitStream, priority, reliability, playerId, bBroadcast, cOrderingChannel);
}

// Send BitStream to player
unsigned int CNetworkServer::Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel)
{
	return m_pNetPeer->Send((char *)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed(), 
		(PacketPriority)priority, (PacketReliability)reliability, cOrderingChannel,
		m_pNetPeer->GetSystemAddressFromIndex(playerId), bBroadcast);
}

// Closes the connection to a client (optionally sends notification)
void CNetworkServer::DisconnectPlayer(EntityId playerId, bool bSendDisconnectionNotification, ePacketPriority disconnectionPacketPriority)
{
	m_pNetPeer->CloseConnection(
		m_pNetPeer->GetSystemAddressFromIndex(playerId), 
		bSendDisconnectionNotification, 0, (PacketPriority)disconnectionPacketPriority);
}






// Returns socket for specified player
CNetPlayerSocket * CNetworkServer::GetPlayerSocket(EntityId playerId)
{
	// Loop through the player socket list
	for(std::list<CNetPlayerSocket *>::iterator iter = m_playerSocketsList.begin(); iter != m_playerSocketsList.end(); iter++)
	{
		// Is this the player socket we are looking for?
		if((*iter)->playerId == playerId)
		{
			// Return the player socket
			return (*iter);
			break;
		}
	}

	return NULL;
}

// Returns true if specified playerId is not invalid and player is connected
bool CNetworkServer::IsPlayerConnected(EntityId playerId)
{
	return (playerId != INVALID_ENTITY_ID && GetPlayerSocket(playerId) != NULL);
}

// Add RakNet peer ban for specified ip for time period
void CNetworkServer::BanIp(string strIpAddress, unsigned int uiTimeMilliseconds)
{
	m_pNetPeer->AddToBanList(strIpAddress, uiTimeMilliseconds);
}

// Removes IP ban from RakNet peer
void CNetworkServer::UnbanIp(string strIpAddress)
{
	m_pNetPeer->RemoveFromBanList(strIpAddress);
}

// Get player current ping
int CNetworkServer::GetPlayerLastPing(EntityId playerId)
{
	return m_pNetPeer->GetLastPing(m_pNetPeer->GetSystemAddressFromIndex(playerId));
}

// Get player average ping value
int CNetworkServer::GetPlayerAveragePing(EntityId playerId)
{
	return m_pNetPeer->GetAveragePing(m_pNetPeer->GetSystemAddressFromIndex(playerId));
}