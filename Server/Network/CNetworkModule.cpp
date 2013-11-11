//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkModule.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkModule.h"

#include <CServer.h>
#include <CSettings.h>
#include <CLogFile.h>
#include "CNetworkRPC.h"
#include <Common.h>
#include <SharedUtility.h>
#include <Scripting/CEvents.h>

CNetworkModule::CNetworkModule(void)
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


	m_pDirectoryDeltaTransfer->SetApplicationDirectory(SharedUtility::GetAppPath());

	// Register the RPC's
	CNetworkRPC::Register(m_pRPC);

	// Set the network state
	SetNetworkState(NETSTATE_NONE);
}

CNetworkModule::~CNetworkModule(void)
{
	// Shutdown RakNet
	m_pRakPeer->Shutdown(500);

	// Unregister the RPC's
	CNetworkRPC::Unregister(m_pRPC);

	// Detach RPC4 from RakPeerInterface
	m_pRakPeer->DetachPlugin(m_pRPC);

	// Destroy the RPC4 instance
	RakNet::RPC4::DestroyInstance(m_pRPC);

	// Destroy the RakPeerInterface instance
	RakNet::RakPeerInterface::DestroyInstance(m_pRakPeer);
}

bool CNetworkModule::Startup(void)
{
	// Create the socket descriptor
	RakNet::SocketDescriptor socketDescriptor(CVAR_GET_INTEGER("port"), CVAR_GET_STRING("hostaddress").Get());

	// Attempt to startup raknet
	bool bReturn = (m_pRakPeer->Startup(CVAR_GET_INTEGER("maxplayers"), &socketDescriptor, 1, 0) == RakNet::RAKNET_STARTED);

	// Did it start?
	if(bReturn)
	{
		// Set the maximum incoming connections
		m_pRakPeer->SetMaximumIncomingConnections(CVAR_GET_INTEGER("maxplayers"));

		// Get the password string
		CString strPassword = CVAR_GET_STRING("password");

		// Do we have a password?
		if(strPassword.GetLength() > 0)
		{
			// Set the server password
			m_pRakPeer->SetIncomingPassword(strPassword.Get(), strPassword.GetLength());
		}
	}

	// Return
	return bReturn;
}

void CNetworkModule::Pulse(void)
{
	// Update the network
	UpdateNetwork();
}

void CNetworkModule::Call(const char * szIdentifier, RakNet::BitStream * pBitStream, PacketPriority priority, PacketReliability reliability, EntityId playerId, bool bBroadCast)
{
	// Pass it to RPC4
	m_pRPC->Call(szIdentifier, pBitStream, priority, reliability, 0, (playerId != INVALID_ENTITY_ID ? m_pRakPeer->GetSystemAddressFromIndex(playerId) : RakNet::UNASSIGNED_SYSTEM_ADDRESS), bBroadCast);
}

int CNetworkModule::GetPlayerPing(EntityId playerId)
{
	return m_pRakPeer->GetLastPing(m_pRakPeer->GetSystemAddressFromIndex(playerId));
}

void CNetworkModule::UpdateNetwork(void)
{
	// Create a packet
	RakNet::Packet * pPacket = NULL;

	// Process RakNet
	while(pPacket = m_pRakPeer->Receive())
	{
		switch(pPacket->data[0])
		{
			case ID_NEW_INCOMING_CONNECTION:
			{
				CLogFile::Printf("[network] Incoming connection from %s.", pPacket->systemAddress.ToString(true, ':'));
				break;
			}

			case ID_DISCONNECTION_NOTIFICATION:
			{
				// Is the player active in the player manager?
				if(CServer::GetInstance()->GetPlayerManager()->Exists((EntityId)pPacket->systemAddress.systemIndex))
				{
					CPlayerEntity * pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt((EntityId)pPacket->systemAddress.systemIndex);
					CLogFile::Printf("[quit] %s has left the server (%s).", pPlayer->GetName().Get(), SharedUtility::DiconnectReasonToString(1).Get());
					
					RakNet::BitStream bitStream;
					bitStream.Write(CServer::GetInstance()->GetPlayerManager()->GetAt((EntityId) pPacket->systemAddress.systemIndex)->GetId());
					CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_DELETE_PLAYER), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
					
					// Delete the player from the manager
					CServer::GetInstance()->GetPlayerManager()->Delete((EntityId)pPacket->systemAddress.systemIndex);
				}
				break;
			}

			case ID_CONNECTION_LOST:
			{
				// Is the player active in the player manager?
				if(CServer::GetInstance()->GetPlayerManager()->Exists((EntityId)pPacket->systemAddress.systemIndex))
				{
					CPlayerEntity * pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt((EntityId)pPacket->systemAddress.systemIndex);
					CLogFile::Printf("[quit] %s has left the server (%s).", pPlayer->GetName().Get(), SharedUtility::DiconnectReasonToString(0).Get());
					
					CScriptArguments args;
					args.push(pPlayer->GetScriptPlayer());
					CEvents::GetInstance()->Call("playerQuit", &args, CEventHandler::eEventType::NATIVE_EVENT, 0);

					RakNet::BitStream bitStream;
					bitStream.Write(CServer::GetInstance()->GetPlayerManager()->GetAt((EntityId) pPacket->systemAddress.systemIndex)->GetId());
					CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_DELETE_PLAYER), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);

					// Delete the player from the manager
					CServer::GetInstance()->GetPlayerManager()->Delete((EntityId)pPacket->systemAddress.systemIndex);

				}
				break;
			}
		}

		// Deallocate the memory used by the packet
		m_pRakPeer->DeallocatePacket(pPacket);
	}
}