//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CNetServer.cpp
// Project: Network.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include <StdInc.h>

CNetServer::CNetServer()
{
	// Create the rak peer instance
	m_pRakPeer = new RakNet::RakPeer();

	// Attach ourselves to the rak peer instance
	m_pRakPeer->AttachPlugin(this);

	// Reset the packet handler
	m_pfnPacketHandler = NULL;
}

CNetServer::~CNetServer()
{
	SAFE_DELETE(m_pRakPeer);
}

bool CNetServer::Startup(unsigned short usPort, int iMaxPlayers, String strHostAddress)
{
	RakNet::SocketDescriptor socketDescriptor(usPort, strHostAddress.Get());
	// TODO: Return the real result instead of a boolean
	bool bStarted = (m_pRakPeer->Startup(iMaxPlayers, &socketDescriptor, 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED);

	if(bStarted)
		m_pRakPeer->SetMaximumIncomingConnections(iMaxPlayers);

	return bStarted;
}

void CNetServer::Shutdown(int iBlockDuration)
{
	m_pRakPeer->Shutdown(iBlockDuration);
}

void CNetServer::Process()
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

void CNetServer::SetPassword(String strPassword)
{
	m_pRakPeer->SetIncomingPassword(strPassword.Get(), strPassword.GetLength());
	m_strPassword = strPassword;
}

const char * CNetServer::GetPassword()
{
	return m_strPassword.Get();
}

unsigned int CNetServer::Send(CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel)
{
	if(!pBitStream)
		return 0;

	return m_pRakPeer->Send((char *)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed(), (PacketPriority)priority, (PacketReliability)reliability, cOrderingChannel, 
		(playerId == INVALID_ENTITY_ID) ? RakNet::UNASSIGNED_SYSTEM_ADDRESS : m_pRakPeer->GetSystemAddressFromIndex(playerId), bBroadcast);
}

unsigned int CNetServer::RPC(RPCIdentifier rpcId, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, EntityId playerId, bool bBroadcast, char cOrderingChannel)
{

	if(playerId != INVALID_ENTITY_ID && !IsPlayerConnected(playerId))
		return 0;

	CBitStream bitStream;
	bitStream.Write((PacketId)PACKET_RPC);
	bitStream.Write(rpcId);

	if(pBitStream)
		bitStream.Write((char *)pBitStream->GetData(), pBitStream->GetNumberOfBytesUsed());

	return m_pRakPeer->Send((char *)bitStream.GetData(), bitStream.GetNumberOfBytesUsed(), (PacketPriority)priority, (PacketReliability)reliability, cOrderingChannel, 
		(playerId == INVALID_ENTITY_ID) ? RakNet::UNASSIGNED_SYSTEM_ADDRESS : m_pRakPeer->GetSystemAddressFromIndex(playerId), bBroadcast);
}

void CNetServer::RejectKick(EntityId playerId)
{
	// Construct the bit stream
	CBitStream bitStream;

	// Write the packet id
	bitStream.Write((PacketId)PACKET_CONNECTION_REJECTED);

	// Send the packet
	Send(&bitStream, PRIORITY_IMMEDIATE, RELIABILITY_RELIABLE_ORDERED, playerId, false);

	// Kick the player
	KickPlayer(playerId, false);
}

PacketId CNetServer::ProcessPacket(RakNet::SystemAddress systemAddress, PacketId packetId, unsigned char * ucData, int iLength)
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
			Send(&bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false);
			return INVALID_PACKET_ID;
		}
		break;
	case ID_USER_PACKET_ENUM: // Receive initial data
		{
			// Construct the bit stream
			CBitStream bitStream(ucData, iLength, false);

			// Read the network version
			BYTE byteNetworkModuleVersion;

			if(!bitStream.Read(byteNetworkModuleVersion))
			{
				// Reject the players connection
				RejectKick(playerId);
				return INVALID_PACKET_ID;
			}

			// Verify the network module version
			if(byteNetworkModuleVersion != NETWORK_MODULE_VERSION)
			{
				// Reject the players connection
				RejectKick(playerId);
				return INVALID_PACKET_ID;
			}

			// Construct the new player socket
			CPlayerSocket * pPlayerSocket = new CPlayerSocket;

			// Set the player socket id
			pPlayerSocket->playerId = playerId;

			// Set the player socket binary address
			pPlayerSocket->ulBinaryAddress = systemAddress.address.addr4.sin_addr.s_addr;

			// Set the player socket port
			pPlayerSocket->usPort = ntohs(systemAddress.address.addr4.sin_port);

			// Add the player socket to the player socket list
			m_playerSocketList.push_back(pPlayerSocket);

			// Reset the bit stream for reuse
			bitStream.Reset();

			// Write the packet id
			bitStream.Write((PacketId)(ID_USER_PACKET_ENUM + 1));

			// Send the packet
			Send(&bitStream, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED, playerId, false);
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

CPacket * CNetServer::Receive()
{
	// Get a packet from the RakNet packet queue
	RakNet::Packet * pRakPacket = m_pRakPeer->Receive();

	// Did we get a packet?
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
			pPacket = new CPacket;

			// Set the packet player socket
			pPacket->pPlayerSocket = GetPlayerSocket((EntityId)pRakPacket->systemAddress.systemIndex);

			// Set the packet id
			pPacket->packetId = packetId;

			// Set the packet length
			pPacket->uiLength = uiLength;

			// Do we have any packet data?
			if(uiLength > 0)
			{
				// Allocate and set the packet data
				pPacket->ucData = new unsigned char[uiLength];//(unsigned char *)malloc(uiLength);

				// Copy the packet data
				memcpy(pPacket->ucData, ucData, uiLength);
			}
			else
			{
				// Reset the packet data pointer
				pPacket->ucData = NULL;
			}
		}

		// Delete the RakNet packet
		m_pRakPeer->DeallocatePacket(pRakPacket);
		return pPacket;
	}

	// No packets in the queue
	return NULL;
}

void CNetServer::DeallocatePacket(CPacket * pPacket)
{
	// Check if we have a disconnection packet
	if(pPacket->packetId == PACKET_DISCONNECTED || pPacket->packetId == PACKET_LOST_CONNECTION)
	{
		// Get the player socket
		CPlayerSocket * pPlayerSocket = pPacket->pPlayerSocket;

		// Delete the player socket
		SAFE_DELETE(pPlayerSocket);

		// Remove the player socket from the player socket list
		if(m_playerSocketList.size() == 1)
			m_playerSocketList.clear();
		else
			m_playerSocketList.remove(pPlayerSocket);
	}

	// Delete the packet data
	SAFE_DELETE(pPacket->ucData);

	// Delete the packet
	SAFE_DELETE(pPacket);
}

const char * CNetServer::GetPlayerIp(EntityId playerId)
{
	return GetPlayerSocket(playerId)->GetAddress(false).Get();
}

unsigned short CNetServer::GetPlayerPort(EntityId playerId)
{
	return GetPlayerSocket(playerId)->usPort;
}

const char * CNetServer::GetPlayerSerial(EntityId playerId)
{
	return GetPlayerSocket(playerId)->strSerial.Get();
}

void CNetServer::KickPlayer(EntityId playerId, bool bSendDisconnectionNotification, ePacketPriority disconnectionPacketPriority)
{
	m_pRakPeer->CloseConnection(m_pRakPeer->GetSystemAddressFromIndex(playerId), bSendDisconnectionNotification, 0, (PacketPriority)disconnectionPacketPriority);
}

CPlayerSocket * CNetServer::GetPlayerSocket(EntityId playerId)
{
	// Loop through the player socket list
	for(std::list<CPlayerSocket *>::iterator iter = m_playerSocketList.begin(); iter != m_playerSocketList.end(); iter++)
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

bool CNetServer::IsPlayerConnected(EntityId playerId)
{
	return (GetPlayerSocket(playerId) != NULL);
}

void CNetServer::BanIp(String strIpAddress, unsigned int uiTimeMilliseconds)
{
	m_pRakPeer->AddToBanList(strIpAddress, uiTimeMilliseconds);
}

void CNetServer::UnbanIp(String strIpAddress)
{
	m_pRakPeer->RemoveFromBanList(strIpAddress);
}

int CNetServer::GetPlayerLastPing(EntityId playerId)
{
	return m_pRakPeer->GetLastPing(m_pRakPeer->GetSystemAddressFromIndex(playerId));
}

int CNetServer::GetPlayerAveragePing(EntityId playerId)
{
	return m_pRakPeer->GetAveragePing(m_pRakPeer->GetSystemAddressFromIndex(playerId));
}
