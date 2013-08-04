//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CNetworkManager.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkManager.h"
#include <CCore.h>
extern CCore * g_pCore;

CNetworkManager::CNetworkManager()
{

}

CNetworkManager::~CNetworkManager()
{

}

void CNetworkManager::Process()
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