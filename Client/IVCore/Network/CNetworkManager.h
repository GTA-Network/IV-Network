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

#ifndef CNetworkManager_h
#define CNetworkManager_h

#include <Network/NetCommon.h>

class CNetworkManager {
private:
	RakNet::RakPeerInterface				* m_pRakPeer;
	RakNet::RPC4							* m_pRPC;
	RakNet::DirectoryDeltaTransfer			* m_pDirectoryDeltaTransfer;
	RakNet::FileListTransfer				* m_pFileListTransfer;
	RakNet::IncrementalReadInterface		* m_pIri;
	RakNet::SystemAddress					m_ServerAddress;

	eNetworkState							m_eNetworkState;
	unsigned int							m_uiLastConnectionTry;

	CString									m_strIp;
	unsigned short							m_usPort;
	CString									m_strPass;

	void									UpdateNetwork();
	void									ConnectionAccepted(RakNet::Packet * pPacket);

public:
											CNetworkManager();
											~CNetworkManager();

	bool									Startup();
	void									Connect(CString strIp, unsigned short usPort, CString strPass = "");
	void									Disconnect(bool bShowMessage = true);
	bool									IsConnected() { return (m_eNetworkState == NETSTATE_CONNECTED || m_eNetworkState == NETSTATE_CONNECTING); }
	void									Shutdown(int iBlockDuration, bool bShowMessage);

	void									SetNetworkState(eNetworkState netState) { m_eNetworkState = netState; }
	eNetworkState							GetNetworkState() { return m_eNetworkState; }

	void									SetLastConnection(CString strIp, unsigned short usPort, CString strPass) { m_strIp = strIp; m_usPort = usPort; m_strPass = strPass; }

	void									Pulse();

	void									Call(const char * szIdentifier, RakNet::BitStream * pBitStream, PacketPriority priority, PacketReliability reliability, bool bBroadCast);

	RakNet::RakPeerInterface				* GetRakPeer() { return m_pRakPeer; }
	RakNet::RPC4							* GetRPC() { return m_pRPC; }
	RakNet::DirectoryDeltaTransfer			* GetDirectoryDeltaTransfer() { return m_pDirectoryDeltaTransfer; }
	RakNet::FileListTransfer				* GetFileListTransfer() { return m_pFileListTransfer; }
	RakNet::IncrementalReadInterface		* GetIri() { return m_pIri; }
	RakNet::SystemAddress					GetServerAddress() { return m_ServerAddress; }

};

#endif // CNetworkManager_h