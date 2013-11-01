//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkManager.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkManager.h"
#include "CNetworkRPC.h"

#include <CCore.h>
extern	CCore			* g_pCore;
RakNet::RPC4			* CNetworkManager::m_pRPC = NULL;

CNetworkManager::CNetworkManager()
{
	// Get the RakPeerInterface instance
	m_pRakPeer = RakNet::RakPeerInterface::GetInstance();

	// Get the RPC4 instance
	m_pRPC = RakNet::RPC4::GetInstance();

	m_pDirectoryDeltaTransfer = RakNet::DirectoryDeltaTransfer::GetInstance();

	m_pFileListTransfer = RakNet::FileListTransfer::GetInstance();

	m_pIri = new RakNet::IncrementalReadInterface();

	m_pDirectoryDeltaTransfer->SetDownloadRequestIncrementalReadInterface(m_pIri, 1000000);

	// Attact RPC4 to RakPeerInterface
	m_pRakPeer->AttachPlugin(m_pRPC);

	m_pRakPeer->AttachPlugin(m_pDirectoryDeltaTransfer);

	m_pRakPeer->AttachPlugin(m_pFileListTransfer);

	m_pRakPeer->SetSplitMessageProgressInterval(100);

	m_pDirectoryDeltaTransfer->SetFileListTransferPlugin(m_pFileListTransfer);

	// Register the RPC's
	CNetworkRPC::Register(m_pRPC);

	// Set the network state
	SetNetworkState(NETSTATE_NONE);

	m_ServerAddress = RakNet::UNASSIGNED_SYSTEM_ADDRESS;

	// Reset the last connection try
	m_uiLastConnectionTry = (unsigned int)SharedUtility::GetTime();
}

CNetworkManager::~CNetworkManager()
{
	// Are we connected?
	if(IsConnected())
	{
		// Disconnect from the network
		Disconnect();
	}

	// Unregister the RPC's
	CNetworkRPC::Unregister(m_pRPC);

	// Detach RPC4 from RakPeerInterface
	m_pRakPeer->DetachPlugin(m_pRPC);

	// Destroy the RPC4 instance
	RakNet::RPC4::DestroyInstance(m_pRPC);

	// Destroy the RakPeerInterface instance
	RakNet::RakPeerInterface::DestroyInstance(m_pRakPeer);
}

bool CNetworkManager::Startup()
{
	return (m_pRakPeer->Startup(1, &RakNet::SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED);
}

void CNetworkManager::Connect(CString strHost, unsigned short usPort, CString strPass)
{
	// Are we already connected?
	if(IsConnected())
	{
		// Disconnect
		Disconnect();
	}

	// Store the connection info
	SetLastConnection(strHost, usPort, strPass);

	// Attempt to connect
	int iConnectionResult = m_pRakPeer->Connect(strHost.Get(), usPort, strPass.Get(), strPass.GetLength());

	// Set the network state
	SetNetworkState(NETSTATE_CONNECTING);

	// Create the string for the connection message
	CString strMessage("Failed to connected!");

	// Get the result from the connection
	switch(iConnectionResult)
	{
		case 0: strMessage.Format("Connecting to %s:%d...", strHost.Get(), usPort); break;
		case 1: strMessage.Set("Failed to connect! (Invalid parameter)"); break;
		case 2: strMessage.Set("Failed to connect! (Cannot resolve domain name)"); break;
		case 3: strMessage.Set("Failed to connect! (Already connected)"); break;
		case 4: strMessage.Set("Failed to connect! (Connection attempt already in progress)"); break;
		case 5: strMessage.Set("Failed to connect! (Security initialization failed)"); break;
		case 6: strMessage.Set("Failed to connect! (No host set)"); break;
	}

	// Did we fail to connect?
	if(iConnectionResult != 0)
	{
		// Set the network state
		SetNetworkState(NETSTATE_DISCONNECTED);

		// Set the last connection try
		m_uiLastConnectionTry = (unsigned int)SharedUtility::GetTime();
	}

	CGUI* pGUI = g_pCore->GetGUI();
	if (pGUI)
	{
		//pGUI->ClearView(CGUI::GUI_SERVER);
		//pGUI->SetView(CGUI::GUI_SERVER);
	}

	// Output the connection message
	g_pCore->GetChat()->Print(CString("#16C5F2%s", strMessage.Get()));
}

void CNetworkManager::Disconnect(bool bShowMessage)
{
	// Are we not connected?
	if(!IsConnected())
		return;

	// Close the connection
	m_pRakPeer->CloseConnection(m_ServerAddress, true);

	// Set the network state
	SetNetworkState(NETSTATE_DISCONNECTED);
	
	Shutdown(500, true);
	Startup();
	
	m_ServerAddress = RakNet::UNASSIGNED_SYSTEM_ADDRESS;

	// Should we output a message?
	if(bShowMessage)
		g_pCore->GetChat()->Print("#16C5F2The server connection closed.");
}

void CNetworkManager::Shutdown(int iBlockDuration, bool bShowMessage)
{
	// Are we connected?
	if(IsConnected())
		Disconnect(bShowMessage);

	// Shutdown RakPeerInterface
	m_pRakPeer->Shutdown(iBlockDuration);
}

void CNetworkManager::Pulse()
{
	// Is the game not loaded?
	if(!g_pCore->IsGameLoaded())
		return;

	// Are we disconnected from the network?
	if(GetNetworkState() == NETSTATE_DISCONNECTED)
		return;

	// Should we try connecting again?
	if(GetNetworkState() == NETSTATE_TIMEOUT && ((unsigned short)SharedUtility::GetTime() - m_uiLastConnectionTry) >= NETWORK_TIMEOUT)
	{
		// Attempt to reconnect
		Connect(m_strIp, m_usPort, m_strPass);

		// Set the network state
		SetNetworkState(NETSTATE_CONNECTING);

		// Set the last connection try
		m_uiLastConnectionTry = (unsigned int)SharedUtility::GetTime();
	}

	// Process the network
	UpdateNetwork();

	// Are we connected?
	if(IsConnected())
	{
		// Pulse the player manager
		g_pCore->GetGame()->GetPlayerManager()->Pulse();

		// Pulse the vehicle manager
		g_pCore->GetGame()->GetVehicleManager()->Pulse();
	}
}

void CNetworkManager::Call(const char * szIdentifier, RakNet::BitStream * pBitStream, PacketPriority priority, PacketReliability reliability, bool bBroadCast)
{
	// Are we not connected to a server?
	if(!IsConnected())
		return;

	// Pass it to RPC4
	m_pRPC->Call(szIdentifier, pBitStream, priority, reliability, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, bBroadCast);
}

void CNetworkManager::UpdateNetwork()
{
	// Create a packet
	RakNet::Packet * pPacket = NULL;

	// Process RakNet
	while(pPacket = m_pRakPeer->Receive())
	{
		switch(pPacket->data[0])
		{
			case ID_NO_FREE_INCOMING_CONNECTIONS:
			{
				g_pCore->GetChat()->Print("#16C5F2The server is full. Rerying...");

				// Set the network state
				SetNetworkState(NETSTATE_TIMEOUT);

				// Set the last connection try
				m_uiLastConnectionTry = GetTickCount();
				break;
			}

			case ID_DISCONNECTION_NOTIFICATION:
			{
				g_pCore->GetChat()->Print("#16C5F2The server connection closed.");
				
				// Set the network state
				SetNetworkState(NETSTATE_DISCONNECTED);

				// Shutdown the core
				//pCore->HandleNetworkShutdown();
				break;
			}

			case ID_INVALID_PASSWORD:
			{
				g_pCore->GetChat()->Print("#16C5F2Incorrect server password.");

				// Set the network state
				SetNetworkState(NETSTATE_DISCONNECTED);
				break;
			}

			case ID_CONNECTION_BANNED:
			{
				g_pCore->GetChat()->Print("#16C5F2You're banned from this server.");

				// Set the network state
				SetNetworkState(NETSTATE_DISCONNECTED);
				break;
			}

			case ID_CONNECTION_LOST:
			{
				g_pCore->GetChat()->Print("#16C5F2Lost connection to the server. Reconnecting...");

				// Set the network state
				SetNetworkState(NETSTATE_TIMEOUT);

				// Handle the connection timeout
				g_pCore->OnNetworkTimeout();

				// Set the last connection try
				m_uiLastConnectionTry = GetTickCount();
				break;
			}

			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				ConnectionAccepted(pPacket);
				break;
			}

			case ID_CONNECTION_ATTEMPT_FAILED:
			{
				g_pCore->GetChat()->Print("#16C5F2Failed to connect to the server. Retrying...");

				// Set the network state
				SetNetworkState(NETSTATE_TIMEOUT);

				// Set the last connection try
				m_uiLastConnectionTry = GetTickCount();
				break;
			}
		}

		// Deallocate the memory used by the packet
		m_pRakPeer->DeallocatePacket(pPacket);
	}
}

void CNetworkManager::ConnectionAccepted(RakNet::Packet * pPacket)
{
	// Set the network state
	SetNetworkState(NETSTATE_CONNECTED);

	m_ServerAddress = pPacket->systemAddress;

	// Send to the server
	Call(GET_RPC_CODEX(RPC_FILE_LIST), nullptr, HIGH_PRIORITY, RELIABLE_ORDERED, true);
}
