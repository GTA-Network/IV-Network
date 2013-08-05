typedef unsigned short PacketId;

#define INTERNAL_PACKET_END 131
#define INVALID_PACKET_ID 0xFF

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