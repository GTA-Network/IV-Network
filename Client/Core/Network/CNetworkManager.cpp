//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
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
extern CCore * g_pCore;

CNetworkManager::CNetworkManager()
{
	SetNetworkState(NETSTATE_NONE);
	m_uiLastConnectionTry = 0;
	m_bConnecting = false;
}

CNetworkManager::~CNetworkManager()
{
	Disconnect();

}

void CNetworkManager::Process()
{
	if(GetNetworkState() == NETSTATE_TIMEOUT && (GetTickCount() - m_uiLastConnectionTry) > NETWORK_TIMEOUT)
	{
		// Attempt to connect
		Connect();
	}

	// Update the network
	UpdateNetwork();

	// Is the network connection active?
	if(IsConnected())
	{
		// Render Players
		if(g_pCore->GetGame()->GetPlayerManager())
		{
			for(EntityId i = 0; i < g_pCore->GetGame()->GetPlayerManager()->GetMax(); i++)
			{
				if(g_pCore->GetGame()->GetPlayerManager()->DoesExists(i))
				{
					g_pCore->GetGame()->GetPlayerManager()->GetAt(i)->Process();
				}
			}
		}

		// Render Vehicles
		if(g_pCore->GetGame()->GetVehicleManager())
		{
			for(EntityId i = 0; i < g_pCore->GetGame()->GetVehicleManager()->GetMax(); i++)
			{
				if(g_pCore->GetGame()->GetVehicleManager()->DoesExists(i))
				{
					g_pCore->GetGame()->GetVehicleManager()->GetAt(i)->Process();
				}
			}
		}
	}
}

void CNetworkManager::Startup()
{

	SetNetworkState(NETSTATE_STARTED);
}

void CNetworkManager::Connect()
{
	// Are we already connected?
	if(IsConnected())
		return;

	// Set the network state
	SetNetworkState(NETSTATE_CONNECTING);
}

void CNetworkManager::Disconnect()
{
	// Are we not connected?
	if(!IsConnected())
		return;

	// Set the network state
	SetNetworkState(NETSTATE_DISCONNECTED);
}

void CNetworkManager::ConnectionAccepted(NetPacket * pPacket)
{
	// Set the network state
	SetNetworkState(NETSTATE_AWAIT_JOIN);

}

void CNetworkManager::UpdateNetwork()
{
	
}

void CNetworkManager::Call(const char * szUnique, CBitStream * pBitStream, ePacketPriority priority, ePacketReliability reliability, char orderingChannel, bool bBroadcast)
{

}