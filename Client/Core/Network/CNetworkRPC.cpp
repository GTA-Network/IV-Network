//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetworkRPC.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CNetworkRPC.h"
#include "CNetworkManager.h"
#include <IV/CIVScript.h>
#include <Game/IVEngine/CIVWeather.h>
#include <CCore.h>

extern CCore * g_pCore;
bool   CNetworkRPC::m_bRegistered = false;

void StartGame(CBitStream * pBitStream, NetPacket * pPacket)
{
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);
	
	int iHour, iMinute, iWeather, iDay;
	pBitStream->Read(iHour);
	pBitStream->Read(iMinute);
	pBitStream->Read(iWeather);
	pBitStream->Read(iDay);

	// Set the localplayer id
	g_pCore->GetGame()->GetLocalPlayer()->SetPlayerId(playerId);

	// Set the network state
	g_pCore->GetNetworkManager()->SetNetworkState(NETSTATE_CONNECTED);

	// Spawn the localplayer

	// Set the stuff from server
	CIVWeather::SetTime(iHour,iMinute);
	CIVWeather::SetWeather((eWeather)iWeather);
	CIVWeather::SetDayOfWeek(iDay);
}

void PlayerJoin(CBitStream * pBitStream, NetPacket * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);

	// Read the player name
	CString strPlayerName;
	pBitStream->Read(strPlayerName);
}

void PlayerLeave(CBitStream * pBitStream, NetPacket * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);
}


void CNetworkRPC::RegisterRPCs(CRPCHandler * pRPC)
{
	// Are we not already registered?
	if(!m_bRegistered)
	{
		// Register the RPCs
		pRPC->AddFunction(RPC_START_GAME, (RPCFunction_t)StartGame);
		pRPC->AddFunction(RPC_NEW_PLAYER, (RPCFunction_t)PlayerJoin);
		pRPC->AddFunction(RPC_DELETE_PLAYER, (RPCFunction_t)PlayerLeave);
		
		// Mark as registered
		m_bRegistered = true;
	}
}

void CNetworkRPC::UnregisterRPCs(CRPCHandler * pRPC)
{
	// Are we registered?
	if(m_bRegistered)
	{
		// Unregister the RPCs
		pRPC->RemoveFunction(RPC_START_GAME);
		pRPC->RemoveFunction(RPC_NEW_PLAYER);
		pRPC->RemoveFunction(RPC_DELETE_PLAYER);
		
		// Mark as not registered
		m_bRegistered = false;
	}
}