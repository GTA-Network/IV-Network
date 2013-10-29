//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkManager.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CNetworkManager_h
#define CNetworkManager_h

#include <Network/NetCommon.h>

class CNetworkManager {
private:
	RakNet::RakPeerInterface				* m_pRakPeer;
	static RakNet::RPC4						* m_pRPC;
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
	static RakNet::RPC4						* GetRPC() { return m_pRPC; }
	RakNet::DirectoryDeltaTransfer			* GetDirectoryDeltaTransfer() { return m_pDirectoryDeltaTransfer; }
	RakNet::FileListTransfer				* GetFileListTransfer() { return m_pFileListTransfer; }
	RakNet::IncrementalReadInterface		* GetIri() { return m_pIri; }
	RakNet::SystemAddress					GetServerAddress() { return m_ServerAddress; }

};

#endif // CNetworkManager_h