/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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