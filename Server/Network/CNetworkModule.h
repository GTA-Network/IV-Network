//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkModule.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CNetworkModule_h
#define CNetworkModule_h

#include <Network/NetCommon.h>

#include <RakNet/NetworkIDManager.h>
#include <RakNet/ReplicaManager3.h>


/*
Client adds local player replica to replica manager
This will be synced to server and all client
Local player serialize itself so PlayerReplica is a LocalPlayerReplica
*/


class CNetworkModule {

private:

	RakNet::RakPeerInterface				* m_pRakPeer;
	RakNet::RPC4							* m_pRPC;
	RakNet::DirectoryDeltaTransfer			* m_pDirectoryDeltaTransfer;
	RakNet::FileListTransfer				* m_pFileListTransfer;
	RakNet::IncrementalReadInterface		* m_pIri;

	eNetworkState							m_eNetworkState;

	void									UpdateNetwork(void );

public:

	CNetworkModule(void );
	~CNetworkModule(void );

	bool									Startup(void );

	void									SetNetworkState(eNetworkState netState ) { m_eNetworkState = netState; }
	eNetworkState							GetNetworkState(void ) { return m_eNetworkState; }

	void									Pulse(void );

	void									Call(const char * szIdentifier, RakNet::BitStream * pBitStream, PacketPriority priority, PacketReliability reliability, EntityId playerId, bool bBroadCast );
	int										GetPlayerPing(EntityId playerId );

	RakNet::RakPeerInterface				* GetRakPeer(void ) { return m_pRakPeer; }
	RakNet::RPC4							* GetRPC(void ) { return m_pRPC; }
	RakNet::DirectoryDeltaTransfer			* GetDirectoryDeltaTransfer() { return m_pDirectoryDeltaTransfer; }
	RakNet::FileListTransfer				* GetFileListTransfer() { return m_pFileListTransfer; }
	RakNet::IncrementalReadInterface		* GetIri() { return m_pIri; }

};

#endif // CNetworkModule_h