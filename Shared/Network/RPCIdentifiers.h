//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: RPCIdentifier.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef RPCIdentifier_h
#define RPCIdentifier_h

// Type of RPC
typedef unsigned short RPCIdentifier;

// RPCs definitions
enum eRPCIdentifier : RPCIdentifier
{
	RPC_INITIAL_DATA,
	RPC_START_GAME,
	RPC_NEW_PLAYER,
	RPC_DELETE_PLAYER,
	RPC_SYNC_PACKAGE,
	RPC_PLAYER_CHAT,
	RPC_PLAYER_DEATH,
	RPC_PLAYER_SPAWN,
	RPC_PLAYER_RESPAWN,
	RPC_ENTER_VEHICLE,
	RPC_EXIT_VEHICLE
};

#endif // RPCIdentifier_h