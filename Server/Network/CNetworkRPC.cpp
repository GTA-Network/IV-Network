//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkRPC.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkRPC.h"

#include "CNetworkModule.h"

#include <CLogFile.h>
#include <CServer.h>
#include <Scripting/CEvents.h>
#include <CSettings.h>
#include <time.h>

#ifndef _WIN32
typedef unsigned char byte;
#endif

#define GET_RPC_CODEX(x) CString("IVN0xF%dF", int(x)).Get()

extern CServer * g_pServer;

bool	CNetworkRPC::m_bRegistered = false;
RakNet::BitStream		bsReject;

void InitialData(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Get the playerid
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;

	// Read the player version
	DWORD dwVersion;
	pBitStream->Read(dwVersion);

	// Read the player name
	RakNet::RakString _strName;
	pBitStream->Read(_strName);
	CString strName(_strName.C_String());

	// Read the player serial
	RakNet::RakString _strSerial;
	pBitStream->Read(_strSerial);
	CString strSerial(_strSerial.C_String());

	// Is the network version invalid?
	if (dwVersion != (DWORD)/*NETWORK_VERSION*/0x0)
	{
		// TODO
	}

	// Is the nickname already in use?
	// TODO: check is nick in use

	// Is the player banned?
	// TODO: check is banned

	// Add the player to the manager
	// TODO: add to player manager
	CPlayerEntity * pPlayer = new CPlayerEntity();

	pPlayer->SetName(strName);

	// Do we need the id; maybe internal for easier sync but definetly not public to the scripting engine
	pPlayer->SetId(CServer::GetInstance()->GetPlayerManager()->Add(pPlayer));
	playerId = pPlayer->GetId();
	srand(time(NULL));
	pPlayer->SetColor(CColor(rand() % 256, rand() % 256, rand() % 256).dwHexColor); //generate random color

	CLogFile::Printf("[join] %s (%i) has connected to the server. (%s)", strName.Get(), playerId, strSerial.Get());

	CScriptArguments args;
	CScriptPlayer * pScriptPlayer = new CScriptPlayer();
	pScriptPlayer->SetEntity(pPlayer);
	pPlayer->SetScriptPlayer(pScriptPlayer);
	args.push(pScriptPlayer);
	CEvents::GetInstance()->Call("playerJoin", &args, CEventHandler::eEventType::NATIVE_EVENT, 0);

	// Construct a new bitstream
	RakNet::BitStream bitStream;

	// Write the player id
	bitStream.Write(playerId);

	// Write the player colour
	bitStream.Write(pPlayer->GetColor());

	// Write the server name
	bitStream.Write(RakNet::RakString("IV:Network DEV Server"));

	// Write the max player count
	bitStream.Write(CVAR_GET_INTEGER("maxplayers"));

	// Write the port
	bitStream.Write(CVAR_GET_INTEGER("port"));

	// Send it back to the player
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_INITIAL_DATA), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, false);

	for (EntityId i = 0; i < CServer::GetInstance()->GetPlayerManager()->GetMax(); ++i)
	{
		if (CServer::GetInstance()->GetPlayerManager()->DoesExists(i) && i != playerId)
		{
			bitStream.Reset();
			bitStream.Write(i);
			bitStream.Write(CServer::GetInstance()->GetPlayerManager()->GetAt(i)->GetName().Get());
			bitStream.Write(CServer::GetInstance()->GetPlayerManager()->GetAt(i)->GetColor());
			CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_NEW_PLAYER), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, false);
		}
	}

	for (EntityId i = 0; i < CServer::GetInstance()->GetPlayerManager()->GetMax(); ++i)
	{
		if (CServer::GetInstance()->GetPlayerManager()->DoesExists(i) && i != playerId)
		{
			bitStream.Reset();
			bitStream.Write(playerId);
			bitStream.Write(pPlayer->GetName().Get());
			bitStream.Write(pPlayer->GetColor());
			CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_NEW_PLAYER), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, i, false);
		}
	}


	for (EntityId i = 0; i < CServer::GetInstance()->GetVehicleManager()->GetMax(); ++i)
	{
		if (CServer::GetInstance()->GetVehicleManager()->DoesExists(i))
		{
			bitStream.Reset();
			CVehicleEntity * pVehicle = CServer::GetInstance()->GetVehicleManager()->GetAt(i);
			bitStream.Write(pVehicle->GetId());
			bitStream.Write(pVehicle->GetModelId());

			CVector3 vecPosition;
			pVehicle->GetPosition(vecPosition);
			bitStream.Write(vecPosition);

			CVector3 vecRotation;
			pVehicle->GetRotation(vecRotation);
			bitStream.Write(vecRotation.fX);

			bitStream.Write(pVehicle->GetColor(1));
			bitStream.Write(pVehicle->GetColor(2));
			bitStream.Write(pVehicle->GetColor(3));
			bitStream.Write(pVehicle->GetColor(4));
			bitStream.Write(pVehicle->GetColor(5));

			CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CREATE_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, false);
		}
	}

	bitStream.Reset();

	bitStream.Write(playerId);
	bitStream.Write(7);
	bitStream.Write(3);
	bitStream.Write(3);
	bitStream.Write(1);
}

void PlayerChat(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Get the playerid
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;

	// Read if this is a command
	bool bIsCommand = pBitStream->ReadBit();

	// Read the input
	RakNet::RakString strInput;
	pBitStream->Read(strInput);

	// Is the player active?
	if (CServer::GetInstance()->GetPlayerManager()->DoesExists(playerId))
	{
		// Get a pointer to the player
		CPlayerEntity * pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt(playerId);

		// Is the pointer valid?
		if (pPlayer)
		{
			// Is this not a command?
			if (!bIsCommand)
			{
				CLogFile::Printf("[chat] %s: %s", pPlayer->GetName().Get(), strInput.C_String());

				// Send the RPC back to other players
				RakNet::BitStream bitStream;
				bitStream.Write(playerId);
				bitStream.Write(strInput);
				CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_CHAT), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
			}
			else
			{
				CLogFile::Printf("[command] %s: %s", pPlayer->GetName().Get(), strInput.C_String());

				CScriptArguments args;
				args.push(strInput);
				args.push(pPlayer->GetScriptPlayer());
				CEvents::GetInstance()->Call("playerCommand", &args, CEventHandler::eEventType::NATIVE_EVENT, nullptr);
			}
		}
	}
}

void PlayerSync(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Get the player id
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;

	// Is the player active?
	if (CServer::GetInstance()->GetPlayerManager()->DoesExists(playerId))
	{
		// Deserialse the bitstream with the player
		ePackageType eType;
		while (pBitStream->Read(eType))
		{
			switch (eType)
			{
			case RPC_PACKAGE_TYPE_PLAYER_ONFOOT:
			case RPC_PACKAGE_TYPE_PLAYER_WEAPON:
			{
			   CServer::GetInstance()->GetPlayerManager()->GetAt(playerId)->Deserialize(pBitStream, eType);

				// TODO: dont send the sync directly store (queue) it make some interpolation or somthing and then send it to get a nice and smooth sync
				break;
			}
			case RPC_PACKAGE_TYPE_PLAYER_PASSENGER:
			case RPC_PACKAGE_TYPE_PLAYER_VEHICLE:
			{
				CServer::GetInstance()->GetPlayerManager()->GetAt(playerId)->Deserialize(pBitStream, eType);
				break;
			}
			}
		}
	}
}

void PlayerDeath(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	CLogFile::Printf("%s", __FUNCTION__);

	// Get the player id
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;

	// Read the killer id
	EntityId killerId;
	pBitStream->Read(killerId);

	// Get a pointer to the player
	CPlayerEntity * pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt(playerId);

	// Is the player pointer valid?
	if (pPlayer)
	{
		// Kill the player
		//pPlayer->KillForWorld();

		// Is the killer a player?
		if (killerId != INVALID_ENTITY_ID)
		{
			// Find the killer
			CPlayerEntity* pKiller = CServer::GetInstance()->GetPlayerManager()->GetAt(killerId);

			// Is the killer valid?
			if (pKiller)
				CLogFile::Printf("[death] %s has been killed by %s!", pPlayer->GetName().Get(), pKiller->GetName().Get());
			else
				CLogFile::Printf("[death] %s has been killed!", pPlayer->GetName().Get());
		}
		else
		{
			CLogFile::Printf("[death] %s has died!", pPlayer->GetName().Get());
		}

		CScriptArguments args;
		args.push(pPlayer->GetScriptPlayer());
		CEvents::GetInstance()->Call("playerDeath", &args, CEventHandler::eEventType::NATIVE_EVENT, 0);
	}
}

void PlayerRequestSpawn(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	CLogFile::Printf("%s", __FUNCTION__);

	// Get the player id
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;

	// Get a pointer to the player
	CPlayerEntity * pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt(playerId);

	// Is the player pointer valid?
	if (pPlayer)
	{
		if (CEvents::GetInstance()->IsEventRegistered("playerRequestSpawn"))
		{
			CScriptArguments args;
			args.push(pPlayer->GetScriptPlayer());
			CEvents::GetInstance()->Call("playerRequestSpawn", &args, CEventHandler::eEventType::NATIVE_EVENT, 0);
		}
		else
		{
			RakNet::BitStream bitStream;
			bitStream.Write(CVector3(DEFAULT_SPAWN_POSITION)); //spawnPos
			bitStream.Write(0.0f); //fHeading
			CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SPAWN), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, false);
		}
		CLogFile::Printf("[spawn] %s has requestred a spawn.", pPlayer->GetName().Get());
	}
}

void VehicleEnter(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Get the player id
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;

	// Read the vehicle id
	EntityId vehicleId;
	pBitStream->Read(vehicleId);

	// Read the seat
	byte byteSeat;
	pBitStream->Read(byteSeat);

	// Get the player instance
	CPlayerEntity * pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt(playerId);

	// Is the player instance valid?
	if (pPlayer)
	{
		// Just send the event to the other players
		RakNet::BitStream bitStream;
		bitStream.Write(playerId);
		bitStream.Write(vehicleId);
		bitStream.Write(byteSeat);
		CLogFile::Printf("Keks");
		CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_ENTER_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
		CScriptArguments args;
		args.push(pPlayer->GetScriptPlayer());
		CEvents::GetInstance()->Call("playerEnterVehicle", &args, CEventHandler::eEventType::NATIVE_EVENT, 0);

	}

	CLogFile::Printf("RPC_ENTER_VEHICLE - Player: %d, Vehicle: %d, Seat: %d", playerId, vehicleId, byteSeat);
}

void VehicleExit(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Get the player id
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;

	// Read the vehicle id
	EntityId vehicleId;
	pBitStream->Read(vehicleId);

	// Read the seat
	byte byteSeat;
	pBitStream->Read(byteSeat);

	// Get the player instance
	CPlayerEntity * pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt(playerId);

	// Is the player instance valid?
	if (pPlayer)
	{
		// Handle this with the player
		RakNet::BitStream bitStream;
		bitStream.Write(playerId);
		bitStream.Write(vehicleId);
		bitStream.Write(byteSeat);
		CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_EXIT_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
		CScriptArguments args;
		args.push(pPlayer->GetScriptPlayer());
		CEvents::GetInstance()->Call("playerExitVehicle", &args, CEventHandler::eEventType::NATIVE_EVENT, 0);
	}

	CLogFile::Printf("RPC_EXIT_VEHICLE - Player: %d, Vehicle: %d, Seat: %d", playerId, vehicleId, byteSeat);
}

void ClientFiles(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	EntityId playerId = (EntityId) pPacket->guid.systemIndex;
	RakNet::BitStream bitStream;
	for (auto pResource : CServer::GetInstance()->GetResourceManager()->GetResources())
	{
		bitStream.Write(RakNet::RakString(pResource->GetName().C_String()));
	}
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_FILE_LIST), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, false);
}

void CNetworkRPC::Register(RakNet::RPC4 * pRPC)
{
	// Are we already registered?
	if (m_bRegistered)
		return;

	// Default rpcs
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA), InitialData);
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_FILE_LIST), ClientFiles);

	// Player rpcs
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_PLAYER_CHAT), PlayerChat);
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_SYNC_PACKAGE), PlayerSync);
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_PLAYER_DEATH), PlayerDeath);
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_PLAYER_REQUEST_SPAWN), PlayerRequestSpawn);

	// Vehicle rpcs
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_ENTER_VEHICLE), VehicleEnter);
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_EXIT_VEHICLE), VehicleExit);
}

void CNetworkRPC::Unregister(RakNet::RPC4 * pRPC)
{
	// Are we not registered?
	if (!m_bRegistered)
		return;

	// Default rpcs
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA));

	// Player rpcs
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_PLAYER_CHAT));
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_SYNC_PACKAGE));
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_PLAYER_DEATH));
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_PLAYER_REQUEST_SPAWN));

	// Vehicle rpcs
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_ENTER_VEHICLE));
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_EXIT_VEHICLE));
}