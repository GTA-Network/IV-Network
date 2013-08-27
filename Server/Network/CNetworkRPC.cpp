//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
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

#define GET_RPC_CODEX(x) CString("IVMP0xF%dF", int(x)).Get()

extern CServer * g_pServer;

bool	CNetworkRPC::m_bRegistered = false;
RakNet::BitStream		bsReject;

void InitialData(RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	// Get the playerid
	EntityId playerId = (EntityId)pPacket->guid.systemIndex;

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
	if(dwVersion != (DWORD)/*NETWORK_VERSION*/0x0)
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
	// Do we need the id; maybe internal for easier sync but definetly not public to the scripting engine
	pPlayer->SetId(CServer::GetInstance()->GetPlayerManager()->Add(pPlayer));

	// Add everyone else connected for this player
	// TODO: handle client join

	// Handle this player with the client scripting manager
	//pCore->GetClientScriptingManager()->HandlePlayerJoin(playerId);

	// Construct a new bitstream
	RakNet::BitStream bitStream;

	// Write the player id
	bitStream.WriteCompressed(playerId);

	// Write the player colour
	//bitStream.Write(pCore->GetPlayerManager()->Get(playerId)->GetColour());

	// Write the server name
	bitStream.Write(RakNet::RakString(CVAR_GET_STRING("hostname").Get()));

	// Write the max player count
	bitStream.Write(CVAR_GET_INTEGER("maxplayers"));

	// Write the file transfer port
	bitStream.Write(CVAR_GET_INTEGER("httpport"));

	// Send it back to the player
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_INITIAL_DATA), &bitStream, HIGH_PRIORITY, RELIABLE, playerId, false);
}

void CNetworkRPC::Register(RakNet::RPC4 * pRPC)
{
	// Are we already registered?
	if(m_bRegistered)
		return;

	// Default rpcs
	pRPC->RegisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA), InitialData);
}

void CNetworkRPC::Unregister(RakNet::RPC4 * pRPC)
{
	// Are we not registered?
	if(!m_bRegistered)
		return;

	// Default rpcs
	pRPC->UnregisterFunction(GET_RPC_CODEX(RPC_INITIAL_DATA));
}