//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: NetCommon.h
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef NetCommon_h
#define NetCommon_h

#include <Common.h>
#ifdef _CLIENT
#include <RakPeerInterface.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <RPC4Plugin.h>
using namespace RakNet;
#endif
#include <Network/PacketIdentifiers.h>
#include <Network/RPCIdentifiers.h>
#include <Network/CBitStream.h>
#include <Math/CVector3.h>

// Macro
#define PEER_IS_STARTED(res) (res == RakNet::RAKNET_STARTED || res == RakNet::RAKNET_ALREADY_STARTED)

// to do: move it? ...
namespace Network
{
	// Gets the problem description for failed peer startup result code
	static CString GetErrorMessage(RakNet::StartupResult startResult)
	{
		switch(startResult)
		{
		case RakNet::INVALID_SOCKET_DESCRIPTORS:
			return "Invalid peer configuration.";

		case RakNet::INVALID_MAX_CONNECTIONS:
			return "Invalid peer \"maxConnections\" option.";

		case RakNet::SOCKET_FAMILY_NOT_SUPPORTED:
			return "Socket family requested is not supported (IPv6?).";

		case RakNet::SOCKET_FAILED_TO_BIND:
		case RakNet::PORT_CANNOT_BE_ZERO:
		case RakNet::SOCKET_PORT_ALREADY_IN_USE:
			return "Failed bind on specified port number in system (port is already in use?)";

		case RakNet::SOCKET_FAILED_TEST_SEND:
			return "Failed to finish bind (platform/system issue?).";

		case RakNet::FAILED_TO_CREATE_NETWORK_THREAD:
			return "Failed to create network thread.";

		case RakNet::COULD_NOT_GENERATE_GUID:
			return "Could not generate GUID.";

		case RakNet::STARTUP_OTHER_FAILURE:
			return "Unknown peer startup problem.";			
		}

		return NULL;
	}
};

// Represents a player socket (used on server)
class CNetPlayerSocket 
{
public:
	unsigned long ulBinaryAddress;
	unsigned short usPort;
	CString strSerial;
	EntityId playerId;

	CNetPlayerSocket()
	{
		playerId = INVALID_ENTITY_ID;
		ulBinaryAddress = 0xFFFFFFFF;
		usPort = 0xFFFF;
		strSerial.Set("00000000000000000000000000000000");
	}

	CString GetIPString(bool bIncludePort = false)
	{
		in_addr in;
		memset(&in, 0, sizeof(in));
		in.s_addr = ulBinaryAddress;

		if(bIncludePort)
			return CString("%s:%d", inet_ntoa(in), usPort);

		return CString(inet_ntoa(in));
	}
};

// Represents each network packet from known player
struct NetPacket
{
	PacketId id;
	unsigned int dataSize;
	unsigned char * data;

	CNetPlayerSocket * pPlayerSocket; // used on server only
};

// indicates in which step of connecting/joining some server we are now
enum eClientStateCode
{
	CLIENT_DISCONNECTED,
	CLIENT_CONNECTING,
	CLIENT_JOINING,
	CLIENT_CONNECTED,//joined
};

// Client state description
struct sClientState
{
	RakNet::StartupResult peerStateCode;
	RakNet::SystemAddress m_serverAddress;	// raknet server address
	EntityId localPlayerId;					// our playerId on server
	eClientStateCode joinState;			// server connection state
	CString strServerOriginal;				// original server address string (for example domain name) used to connect

	// disconnected from any server, and we are not connecting/joining at the moment
	bool IsDisconnected()			{ return joinState == CLIENT_DISCONNECTED; }
	// connecting to any server atm?
	bool IsConnecting()				{ return joinState == CLIENT_CONNECTING;; }
	// finished connection sequence to server (now joining or joined)?
	bool IsConnected()				{ return joinState > CLIENT_CONNECTING; }
	// connected to server and joining?
	bool IsJoining()				{ return joinState == CLIENT_JOINING; }
	// finished joining server (online!)?
	bool IsJoined()					{ return joinState == CLIENT_CONNECTED; }

	// peer initialization ok?
	bool IsPeerStarted()			{ return PEER_IS_STARTED(peerStateCode); }
	// error message of peer startup
	CString GetStartupErrorMessage() { return Network::GetErrorMessage(peerStateCode); }

	// server IP address
	CString GetServerIP()			{ return inet_ntoa(m_serverAddress.address.addr4.sin_addr); }
	// server port number
	unsigned short GetServerPort()	{ return ntohs(m_serverAddress.address.addr4.sin_port); }

	// clear state (only when disconnecting..)
	void Clear()
	{
		localPlayerId = INVALID_ENTITY_ID;
		strServerOriginal.Free();
		joinState = CLIENT_DISCONNECTED;
	}
};

// Enumerates supported mode of packet reliability
enum ePacketReliability
{
	// Same as regular UDP, except that it will also discard duplicate datagrams. 
	// RakNet adds (6 to 17) + 21 bits of overhead, 16 of which is used to detect duplicate packets and 6 to 17 of which is used for message length.
	RELIABILITY_UNRELIABLE,

	// Regular UDP with a sequence counter.  Out of order messages will be discarded.
	// This adds an additional 13 bits on top what is used for UNRELIABLE.
	RELIABILITY_UNRELIABLE_SEQUENCED,

	// The message is sent reliably, but not necessarily in any order.
	// Same overhead as UNRELIABLE.
	RELIABILITY_RELIABLE,

	// This message is RELIABILITY_RELIABLE and will arrive in the order you sent it.
	// Messages will be delayed while waiting for out of order messages.  Same overhead as RELIABILITY_UNRELIABLE_SEQUENCED.
	RELIABILITY_RELIABLE_ORDERED,

	// This message is RELIABILITY_RELIABLE and will arrive in the sequence you sent it.
	// Out or order messages will be dropped.  Same overhead as RELIABILITY_UNRELIABLE_SEQUENCED.
	RELIABILITY_RELIABLE_SEQUENCED,

	// Same as UNRELIABLE, however the user will get either ID_SND_RECEIPT_ACKED or ID_SND_RECEIPT_LOSS based on the result
	// of sending this message when calling RakPeerInterface::Receive().
	// Bytes 1-4 will contain the number returned from the Send() function. 
	// On disconnect or shutdown, all messages not previously acked should be considered lost.
	RELIABILITY_UNRELIABLE_WITH_ACK_RECEIPT,

	// Same as RELIABILITY_UNRELIABLE_SEQUENCED. The user will also get ID_SND_RECEIPT_ACKED after the message
	// is delivered when calling RakPeerInterface::Receive(). Bytes 1-4 will contain the number
	// returned from the Send() function. On disconnect or shutdown, all messages not previously acked should be considered lost.
	RELIABILITY_RELIABLE_WITH_ACK_RECEIPT,

	// Same as RELIABILITY_RELIABILITY_RELIABLE_ORDERED_ACK_RECEIPT.
	// The user will also get ID_SND_RECEIPT_ACKED after the message is delivered when calling RakPeerInterface::Receive().
	// Bytes 1-4 will contain the number returned from the Send() function. On disconnect or shutdown,
	// all messages not previously acked should be considered lost.
	RELIABILITY_RELIABILITY_RELIABLE_ORDERED_WITH_ACK_RECEIPT,

	// Number of packet reliabilities
	RELIABILITY_COUNT
};

// Enumerates possible packet priorities
enum ePacketPriority
{
	// The highest possible priority. These message trigger sends immediately, and are generally not buffered or aggregated into a single datagram.
	PRIORITY_IMMEDIATE,

	// For every 2 PRIORITY_IMMEDIATE messages, 1 PRIORITY_HIGH will be sent.
	// Messages at this priority and lower are buffered to be sent in groups at 10 millisecond intervals to reduce UDP overhead and better measure congestion control. 
	PRIORITY_HIGH,

	// For every 2 PRIORITY_HIGH messages, 1 PRIORITY_MEDIUM will be sent.
	// Messages at this priority and lower are buffered to be sent in groups at 10 millisecond intervals to reduce UDP overhead and better measure congestion control. 
	PRIORITY_MEDIUM,

	// For every 2 PRIORITY_MEDIUM messages, 1 PRIORITY_LOW will be sent.
	// Messages at this priority and lower are buffered to be sent in groups at 10 millisecond intervals to reduce UDP overhead and better measure congestion control. 
	PRIORITY_LOW,

	// Number of packet priorities
	PRIORITY_COUNT
};

// Packet channels
enum ePacketChannels
{	
	PACKET_CHANNEL_DEFAULT,	// Default packet channel
	
	PACKET_CHANNEL_INPUT,	// Packet channel used for input
	
	PACKET_CHANNEL_SCRIPT,	// Packet channel used for script
	
	PACKET_CHANNEL_COUNT	// Number of packet channels
};

#endif // NetCommon_h