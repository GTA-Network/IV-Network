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

#include "Common.h"
#include "Math\CVector3.h"

typedef unsigned short PacketId;

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

#define INTERNAL_PACKET_END 131

// Network packet identifiers (types)
enum ePacketIdentfier : PacketId
{
	PACKET_CONNECTION_REJECTED = INTERNAL_PACKET_END,

	PACKET_CONNECTION_SUCCEEDED,
	
	PACKET_CONNECTION_FAILED,	// We failed to connect to the server
	
	PACKET_ALREADY_CONNECTED,	// We are already connected to the server
	
	PACKET_SERVER_FULL,			// The server is full
	
	PACKET_NEW_CONNECTION,		// A client has connected to us
	
	PACKET_DISCONNECTED,		// We have been disconnected from the client/server
	
	PACKET_LOST_CONNECTION,		// We have lost connection to the client/server
	
	PACKET_BANNED,				// We are banned from this server
	
	PACKET_PASSWORD_INVALID,	// The password we supplied to the server was invalid
		
	PACKET_RPC,					// Remote procedure call
	
	PACKET_COUNT				// Number of packet identifiers (types)
};

// From RakNet
// Threshold at which to do a malloc / free rather than pushing data onto a fixed stack
// Arbitrary size, just picking something likely to be larger than most packets
#define BUFFER_STACK_ALLOCATION_SIZE 256

#define MUL_OF_8(x) (((x) & 7) == 0)

#define READ_TEMPLATE(size, out) \
	/* Read from the buffer */ \
	return ReadBits((unsigned char *)&out, (size * 8));

#define READ_COMPRESSED_TEMPLATE(size, out) \
	/* Read from the buffer */ \
	return ReadCompressed((unsigned char *)&out, (size * 8), true);

#define WRITE_TEMPLATE(size, in) \
	/* Write to the buffer */ \
	WriteBits((unsigned char *)&in, (size * 8), true);

#define WRITE_COMPRESSED_TEMPLATE(size, in) \
	/* Write to the buffer */ \
	WriteCompressed((unsigned char *)&in, (size * 8), true);

// Based on RakNet's BitStream class (With permission)
// Used to construct network packets
class CBitStream
{
private:
	
	unsigned char * m_pData;				// Pointer to data	
	unsigned int    m_uiBufferSizeInBits;	// Amount of memory allocated (In bits)	
	unsigned int    m_uiWriteOffsetInBits;	// Current write offset (In bits)	
	unsigned int    m_uiReadOffsetInBits;	// Current read offset (In bits)	
	bool            m_bCopyData;			// True if the internal buffer is a copy of data. False if it is a reference to a pointer
	
	// BitStreams that use less than BUFFER_STACK_ALLOCATION_SIZE use the stack,
	// rather than the heap to store data.  It switches over if BUFFER_STACK_ALLOCATION_SIZE is exceeded
	unsigned char   m_stackData[BUFFER_STACK_ALLOCATION_SIZE];

public:
	CBitStream();
	CBitStream(const unsigned int uiSizeInBytes);
	CBitStream(unsigned char * pBuffer, unsigned int uiSizeInBytes, bool bCopyData = false);
	~CBitStream();

	// Reset the BitStream for reuse.
	void                     Reset(void);

	// Reallocates (if necessary) in preparation of writing uiSizeInBits
	void                     AddBitsAndReallocate(unsigned int uiSizeInBits);

	// Reset the BitStream read pointer for reuse.
	void                     ResetReadPointer(void);

	// Reset the BitStream write pointer for reuse.
	void                     ResetWritePointer(void);

	// Write any integral type to the BitStream.
	void                     Write(const bool &bIn) { WRITE_TEMPLATE(sizeof(bool), bIn); }
	void                     Write(const char &cIn) { WRITE_TEMPLATE(sizeof(char), cIn); }
	void                     Write(const unsigned char &ucIn) { WRITE_TEMPLATE(sizeof(unsigned char), ucIn); }
	void                     Write(const short &sIn) { WRITE_TEMPLATE(sizeof(short), sIn); }
	void                     Write(const unsigned short &usIn) { WRITE_TEMPLATE(sizeof(unsigned short), usIn); }
	void                     Write(const int &iIn) { WRITE_TEMPLATE(sizeof(int), iIn); }
	void                     Write(const unsigned int &uiIn) { WRITE_TEMPLATE(sizeof(unsigned int), uiIn); }
	void                     Write(const long &lIn) { WRITE_TEMPLATE(sizeof(long), lIn); }
	void                     Write(const unsigned long &ulIn) { WRITE_TEMPLATE(sizeof(unsigned long), ulIn); }
	void                     Write(const float &fIn) { WRITE_TEMPLATE(sizeof(float), fIn); }
	void                     Write(const double &dIn) { WRITE_TEMPLATE(sizeof(double), dIn); }
	void                     Write(const string &strIn);
	void                     Write(const CVector3 &vecIn);
	//void                     Write(const CControlState &in);

	// Write any integral type compressed to the BitStream.
	void                     WriteCompressed(const bool &bIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(bool), bIn); }
	void                     WriteCompressed(const char &cIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(char), cIn); }
	void                     WriteCompressed(const unsigned char &ucIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned char), ucIn); }
	void                     WriteCompressed(const short &sIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(short), sIn); }
	void                     WriteCompressed(const unsigned short &usIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned short), usIn); }
	void                     WriteCompressed(const int &iIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(int), iIn); }
	void                     WriteCompressed(const unsigned int &uiIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned int), uiIn); }
	void                     WriteCompressed(const long &lIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(long), lIn); }
	void                     WriteCompressed(const unsigned long &ulIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(unsigned long), ulIn); }
	void                     WriteCompressed(const float &fIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(float), fIn); }
	void                     WriteCompressed(const double &dIn) { WRITE_COMPRESSED_TEMPLATE(sizeof(double), dIn); }

	// Read any integral type from the BitStream.
	bool                     Read(bool& bOut) { READ_TEMPLATE(sizeof(bool), bOut); }
	bool                     Read(char& cOut) { READ_TEMPLATE(sizeof(char), cOut); }
	bool                     Read(unsigned char& ucOut) { READ_TEMPLATE(sizeof(unsigned char), ucOut); }
	bool                     Read(short& sOut) { READ_TEMPLATE(sizeof(short), sOut); }
	bool                     Read(unsigned short& usOut) { READ_TEMPLATE(sizeof(unsigned short), usOut); }
	bool                     Read(int& iOut) { READ_TEMPLATE(sizeof(int), iOut); }
	bool                     Read(unsigned int& uiOut) { READ_TEMPLATE(sizeof(unsigned int), uiOut); }
	bool                     Read(long& lOut) { READ_TEMPLATE(sizeof(long), lOut); }
	bool                     Read(unsigned long& ulOut) { READ_TEMPLATE(sizeof(unsigned long), ulOut); }
	bool                     Read(float& fOut) { READ_TEMPLATE(sizeof(float), fOut); }
	bool                     Read(double& dOut) { READ_TEMPLATE(sizeof(double), dOut); }
	bool                     Read(string &strOut);
	bool                     Read(CVector3 &vecOut);
	//bool                     Read(CControlState &out);

	// Read any compressed integral type from the BitStream.
	bool                     ReadCompressed(bool &bOut) { READ_COMPRESSED_TEMPLATE(sizeof(bool), bOut); }
	bool                     ReadCompressed(char &cOut) { READ_COMPRESSED_TEMPLATE(sizeof(char), cOut); }
	bool                     ReadCompressed(unsigned char &ucOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned char), ucOut); }
	bool                     ReadCompressed(short &sOut) { READ_COMPRESSED_TEMPLATE(sizeof(short), sOut); }
	bool                     ReadCompressed(unsigned short &usOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned short), usOut); }
	bool                     ReadCompressed(int &iOut) { READ_COMPRESSED_TEMPLATE(sizeof(int), iOut); }
	bool                     ReadCompressed(unsigned int &uiOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned int), uiOut); }
	bool                     ReadCompressed(long &lOut) { READ_COMPRESSED_TEMPLATE(sizeof(long), lOut); }
	bool                     ReadCompressed(unsigned long &ulOut) { READ_COMPRESSED_TEMPLATE(sizeof(unsigned long), ulOut); }
	bool                     ReadCompressed(float &fOut) { READ_COMPRESSED_TEMPLATE(sizeof(float), fOut); }
	bool                     ReadCompressed(double &dOut) { READ_COMPRESSED_TEMPLATE(sizeof(double), dOut); }

	// Write an array or casted stream or raw data to the BitStream.
	void                     Write(const char * inputByteArray, const unsigned int numberOfBytes);

	// Read an array or casted stream or raw data from the BitStream.
	bool                     Read(char * outputByteArray, const unsigned int numberOfBytes);

private:
	// Assume the input source points to a native type, Compress and write it
	void                     WriteCompressed(const unsigned char * inByteArray, const unsigned int size, const bool unsignedData);

	// Assume the input source points to a compressed native type. Decompress and read it.
	bool                     ReadCompressed(unsigned char* inOutByteArray,	const unsigned int size, const bool unsignedData);

public:
	// Write a sequence of bits to the BitStream.
	void                     WriteBits(const unsigned char * inByteArray, unsigned int numberOfBitsToWrite, bool bAlignBitsToRight = true);

	// Read a sequence of bits from the BitStream.
	bool                     ReadBits(unsigned char * inOutByteArray, unsigned int numberOfBitsToRead, bool bAlignBitsToRight = true);

	// Write a 0 or 1 to the BitStream.
	void                     WriteBit(bool bState);

	// Write a 0 to the BitStream.
	void                     Write0(void);

	// Write a 1 to the BitStream.
	void                     Write1(void);

	// Returns true if the next data read is a 1, false if it is a 0.
	bool                     ReadBit(void);

	// Returns a pointer to the data in the BitStream.
	unsigned char *          GetData() const { return m_pData; }

	// Returns the number of bits used in the BitStream.
	unsigned int             GetNumberOfBitsUsed() const { return m_uiWriteOffsetInBits; }

	// Returns the number of bytes used in the BitStream.
	unsigned int             GetNumberOfBytesUsed() const { return BITS_TO_BYTES(m_uiWriteOffsetInBits); }

	// Returns the number of unread bits left in the BitStream.
	unsigned int             GetNumberOfUnreadBits() const { return (m_uiWriteOffsetInBits - m_uiReadOffsetInBits); }

	// Returns the number of unread bytes left in the BitStream.
	unsigned int             GetNumberOfUnreadBytes() const { return BITS_TO_BYTES(m_uiWriteOffsetInBits - m_uiReadOffsetInBits); }

	// Ignore data we don't intend to read.
	void                     IgnoreBits(const unsigned int uiSizeInBits) { m_uiReadOffsetInBits += uiSizeInBits; }

	// Ignore data we don't intend to read.
	void                     IgnoreBytes(const unsigned int uiSizeInBytes) { m_uiReadOffsetInBits += BYTES_TO_BITS(uiSizeInBytes); }

	// Write zeros until the BitStream is filled up to uiSizeInBytes.
	void                     PadWithZeroToByteLength(unsigned int uiSizeInBytes);

	// Align the write offset to a byte boundary.
	void                     AlignWriteToByteBoundary() { m_uiWriteOffsetInBits += 8 - (((m_uiWriteOffsetInBits - 1) & 7) + 1); }

	// Align the read offset to a byte boundary.
	void                     AlignReadToByteBoundary() { m_uiReadOffsetInBits += 8 - (((m_uiReadOffsetInBits - 1) & 7) + 1);}
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

// Type of RPC
typedef unsigned short RPCIdentifier;

// RPCs definitions
enum eRPCIdentifier : RPCIdentifier
{
	RPC_PlayerConnectRequest
};

#endif // NetCommon_h