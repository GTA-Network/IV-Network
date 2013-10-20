//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
	pBitStream->ReadCompressed(playerId);

	// Read the player colour
	unsigned int uiColour;
	pBitStream->Read(uiColour);

	// Read the server name string
	RakNet::RakString strServerName;
	pBitStream->Read(strServerName);

	// Read the max player count
	int iMaxPlayers;
	pBitStream->Read(iMaxPlayers);

	// Read the file transfer port
	int iPort;
	pBitStream->Read(iPort);

	// Set the localplayer id
	g_pCore->GetGame()->GetLocalPlayer()->SetId(playerId);

	// Add the local player to the playermanager
	g_pCore->GetGame()->GetPlayerManager()->Add(playerId, reinterpret_cast<CPlayerEntity *>(g_pCore->GetGame()->GetLocalPlayer()));

	// Set the localplayer colour
	g_pCore->GetGame()->GetLocalPlayer()->SetColor(uiColour);

	// Set the servername
	g_pCore->SetServerName(strServerName.C_String());

	// Notify the player via chat
	g_pCore->GetChat()->Outputf(true, "#16C5F2 Connection established waiting for welcome message %s.", strServerName.C_String());

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

	// Set the stuff from server
	g_pCore->GetTimeManagementInstance()->SetTime(iHour, iMinute);
	CIVWeather::SetTime(iHour, iMinute);
	CIVWeather::SetWeather((eWeather) iWeather);
	CIVWeather::SetDayOfWeek(iDay);

	// Notify the client
	g_pCore->GetChat()->Clear();
	g_pCore->GetChat()->Outputf(true, "#16C5F2 Successfully connected to %s...", g_pCore->GetServerName().Get());
}

void PlayerJoin(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);

	// Read the player name
	CString strPlayerName;
	pBitStream->Read(strPlayerName);

	// Check if we are the local player(thx for broadcasting to XForce, *keks*)
	if (g_pCore->GetGame()->GetLocalPlayer()->GetId() == playerId)
		return;

	// Add the player
	CPlayerEntity * pEntity = new CPlayerEntity;
	pEntity->SetModel(0); // Set temporary to luis lol
	pEntity->Create();
	pEntity->SetNick(strPlayerName);
	pEntity->SetId(playerId);

	// Notify the playermanager that we're having a new player
	g_pCore->GetGame()->GetPlayerManager()->Add(playerId, pEntity);

	// Temporary set the position to our dev spawn
	pEntity->SetPosition(CVector3(DEVELOPMENT_SPAWN_POSITION));
}

void PlayerLeave(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);

	// Remove the player from the player manager
	g_pCore->GetGame()->GetPlayerManager()->Delete(playerId);
}

void PlayerChat(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->ReadCompressed(playerId);

	// Read the input
	RakNet::RakString strInput;
	pBitStream->Read(strInput);

	// Is the player active?
	if (g_pCore->GetGame()->GetPlayerManager()->DoesExists(playerId))
	{
		// Get the player pointer
		CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId);

		// Is the player pointer valid?
		if (pPlayer)
		{
			// Output the message
			g_pCore->GetChat()->Outputf(true, "#%s%s#FFFFFF: %s", CString::DecimalToString(pPlayer->GetColor()).Get(), pPlayer->GetNick().Get(), strInput.C_String());
		}
	}
}

void RecieveSyncPackage(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->Read(playerId);

	// Read the player ping
	int iPing;
	pBitStream->Read(iPing);

	// Get a pointer to the player
	CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId);

	// Is the player pointer valid?
	if (pPlayer)
	{
		// Set the player ping
		pPlayer->SetPing(iPing);

		// Check for local player
		if (pPlayer->IsLocalPlayer())
			return;

		// Is the localplayer spawned?
		if (g_pCore->GetGame()->GetLocalPlayer()->IsSpawned())
		{
			// Fail safe
			if (playerId == g_pCore->GetGame()->GetLocalPlayer()->GetId())
			{
				CLogFile::Printf("FATAL ERROR: Tried to sync a ped to localplayer! (LocalPlayer: %d, Player: %d)", g_pCore->GetGame()->GetLocalPlayer()->GetId(), playerId);
				return;
			}

			auto oldReadOffset = pBitStream->GetReadOffset();
			ePackageType eType;
			pBitStream->Read(eType);
			// Set it back so that the deserialize function can identify which packet is incoming 
			// I dont want to pass a argument to Deserialize it should do what the name says deserialize a bitstream this means also the package id  
			pBitStream->SetReadOffset(oldReadOffset);
			switch (eType)
			{
			case RPC_PACKAGE_TYPE_PLAYER_ONFOOT:
			case RPC_PACKAGE_TYPE_PLAYER_WEAPON:
			case RPC_PACKAGE_TYPE_PLAYER_VEHICLE:
				{
					pPlayer->Deserialize(pBitStream);
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

void SetPlayerPosition(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Read the playerid
	EntityId playerId;
	pBitStream->Read(playerId);

	// Get a pointer to the player
	CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId);

	// Is the player pointer valid?
	if (pPlayer)
	{
		CVector3 vecPos;

		pBitStream->Read(vecPos);

		pPlayer->SetPosition(vecPos);
	}
}

void SetPlayerHealth(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	EntityId playerId;
	pBitStream->Read(playerId);

	// Get a pointer to the player
	CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId);

	// Is the player pointer valid?
	if (pPlayer)
	{
		float fHealth;

		pBitStream->Read(fHealth);

		pPlayer->SetHealth(fHealth);
	}
}

void GivePlayerWeapon(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{

	EntityId playerId;
	pBitStream->Read(playerId);
	
	g_pCore->GetChat()->Output("Kekse");

	// Get a pointer to the player
	CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(playerId);

	// Is the player pointer valid?
	if (pPlayer)
	{
		int id;
		int uiAmmo;
		pBitStream->Read(id);
		pBitStream->Read(uiAmmo);

		pPlayer->GiveWeapon(id, uiAmmo);
	}
}

void CreateVehicle(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	EntityId vehicleId;
	pBitStream->Read(vehicleId);

	int vehicleModel;
	pBitStream->Read(vehicleModel);

	CVector3 vecPosition;
	pBitStream->Read(vecPosition);
	vecPosition.fZ += 1.0f;


	g_pCore->GetChat()->Outputf(false, "%i %i %f %f %f", vehicleId, vehicleModel, vecPosition.fX, vecPosition.fY, vecPosition.fZ);

	CVehicleEntity * pVehicle = new CVehicleEntity(vehicleModel, vecPosition, 0.0f, 0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF);
	if (pVehicle) 
	{
	//	// Add our vehicle
		g_pCore->GetGame()->GetVehicleManager()->Add(vehicleId, pVehicle);
		pVehicle->SetId(vehicleId);
		pVehicle->Create();
		pVehicle->SetPosition(vecPosition, true);
	}
}

void CNetworkRPC::Register(RakNet::RPC4 * pRPC)
{
	// Are we not already registered?
	if (!m_bRegistered)
	{
		// Register the RPCs
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA), InitialData);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_START_GAME), StartGame);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_NEW_PLAYER), PlayerJoin);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_PLAYER_CHAT), PlayerChat);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_DELETE_PLAYER), PlayerLeave);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_SYNC_PACKAGE), RecieveSyncPackage);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_CREATE_VEHICLE), CreateVehicle);


		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_PLAYER_SET_POSITION), SetPlayerPosition);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_PLAYER_SET_HEALTH), SetPlayerHealth);
		pRPC->RegisterFunction(GET_RPC_CODEX(RPC_PLAYER_GIVE_WEAPON), GivePlayerWeapon);
		
		// Mark as registered
		m_bRegistered = true;
	}
}

void CNetworkRPC::Unregister(RakNet::RPC4 * pRPC)
{
	// Are we registered?
	if (m_bRegistered)
	{
		// Unregister the RPCs
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_START_GAME));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_NEW_PLAYER));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_PLAYER_CHAT));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_DELETE_PLAYER));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_SYNC_PACKAGE));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_CREATE_VEHICLE));

		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_PLAYER_SET_POSITION));
		pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_PLAYER_SET_HEALTH));

		// Mark as not registered
		m_bRegistered = false;
	}
}