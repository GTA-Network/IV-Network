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

void InitialData(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the player id
	EntityId playerId;
	pBitStream->ReadCompressed( playerId );

	// Read the player colour
	unsigned int uiColour;
	pBitStream->Read( uiColour );

	// Read the server name string
	RakNet::RakString strServerName;
	pBitStream->Read( strServerName );

	// Read the max player count
	int iMaxPlayers;
	pBitStream->Read( iMaxPlayers );

	// Read the file transfer port
	int iPort;
	pBitStream->Read( iPort );

	// Set the localplayer id
	g_pCore->GetGame()->GetLocalPlayer()->SetId( playerId );

	// Set the localplayer colour
	g_pCore->GetGame()->GetLocalPlayer()->SetColor( uiColour );

	//
	g_pCore->GetChat()->Clear();
	g_pCore->GetChat()->Outputf( true, "#16C5F2 Successfully connected to %s.", strServerName.C_String() );

	// Start the game
	g_pCore->GetGame()->SetupGame();
}

void StartGame(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
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

void PlayerJoin(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);

	// Read the player name
	CString strPlayerName;
	pBitStream->Read(strPlayerName);

	// Add the player
	CPlayerEntity * pEntity = new CPlayerEntity();
	pEntity->SetId(playerId);
	pEntity->SetNick(strPlayerName);

	g_pCore->GetGame()->GetPlayerManager()->Add(pEntity);

	pEntity->Spawn();
	// temp
	pEntity->SetModel(7);
}

void PlayerLeave(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);

	g_pCore->GetGame()->GetPlayerManager()->Delete(playerId);
	g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId)->Destroy();
	g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId)->~CPlayerEntity();
}

void PlayerChat(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed( playerId );

	// Read the input
	RakNet::RakString strInput;
	pBitStream->Read( strInput );

	// Is the player active?
	if( g_pCore->GetGame()->GetPlayerManager()->DoesExists( playerId ) )
	{
		// Get the player pointer
		CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId);

		// Is the player pointer valid?
		if( pPlayer )
		{
			// Output the message
			g_pCore->GetChat()->Outputf( true, "#%s%s#FFFFFF: %s", CString::DecimalToString(pPlayer->GetColor()).Get(), pPlayer->GetNick().Get(), strInput.C_String() );
		}
	}
}

void RecieveSyncPackage(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed( playerId );

	// Read the player ping
	unsigned short usPing;
	pBitStream->ReadCompressed( usPing );

	// Get a pointer to the player
	CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId);

	// Is the player pointer valid?
	if( pPlayer )
	{
		// Set the player ping
		pPlayer->SetPing( usPing );

		// Is the localplayer spawned?
		if( g_pCore->GetGame()->GetLocalPlayer()->IsSpawned() )
		{
			// Fail safe
			if( playerId == g_pCore->GetGame()->GetLocalPlayer()->GetId() )
			{
				CLogFile::Printf( "FATAL ERROR: Tried to sync a ped to localplayer! (LocalPlayer: %d, Player: %d)", g_pCore->GetGame()->GetLocalPlayer()->GetId(), playerId );
				return;
			}

			ePackageType pPackageType = ePackageType();
			pBitStream->Read((char *)pPackageType);

			switch(pPackageType)
			{
				case RPC_PACKAGE_TYPE_PLAYER_ONFOOT:
				{
					// Process player deserialise package
					pPlayer->Deserialize(pBitStream, pPackageType);
					break;
				}
				default:
				{
					CLogFile::Print("Unkown package type, process...");
					break;
				}
			}
		}
	}
}



void CNetworkRPC::Register(RakNet::RPC4 * pRPC)
{
	// Are we not already registered?
	if(!m_bRegistered)
	{
		// Register the RPCs
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA), InitialData);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_START_GAME), StartGame);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_NEW_PLAYER), PlayerJoin);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_DELETE_PLAYER), PlayerLeave);
		
		// Mark as registered
		m_bRegistered = true;
	}
}

void CNetworkRPC::Unregister(RakNet::RPC4 * pRPC)
{
	// Are we registered?
	if(m_bRegistered)
	{
		// Unregister the RPCs
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_START_GAME));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_NEW_PLAYER));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_DELETE_PLAYER));
		
		// Mark as not registered
		m_bRegistered = false;
	}
}