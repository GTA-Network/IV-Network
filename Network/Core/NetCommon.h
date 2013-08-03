//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
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
#include <Network/CPacketIdentifiers.h>
#include <Network/CRPCIdentifiers.h>
#include <Network/CBitStream.h>
#include <Math/CVector3.h>

// Represents a player socket on server
class CNetPlayerSocket 
{
public:
	unsigned long ulBinaryAddress;
	unsigned short usPort;
	string strSerial;
	EntityId playerId;

	CNetPlayerSocket()
	{
		playerId = INVALID_ENTITY_ID;
		ulBinaryAddress = 0xFFFFFFFF;
		usPort = 0xFFFF;
		strSerial.Set("00000000000000000000000000000000");
	}

	string GetIPString(bool bIncludePort = false)
	{
		in_addr in;
		memset(&in, 0, sizeof(in));
		in.s_addr = ulBinaryAddress;

		if(bIncludePort)
			return string("%s:%d", inet_ntoa(in), usPort);

		return string(inet_ntoa(in));
	}
};

// Represents each network packet from known player
struct NetPacket
{
	PacketId id;
	CNetPlayerSocket * pPlayerSocket;
	unsigned int dataSize;
	unsigned char * data;
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