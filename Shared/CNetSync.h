//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetSync.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CNetSync_h
#define CNetSync_h

#include "Common.h"
#include "Math/CMaths.h"

enum ePackageType
{
	RPC_PACKAGE_TYPE_SMALL = 0x1,
	RPC_PACKAGE_TYPE_PLAYER_ONFOOT = 0x21,
	RPC_PACKAGE_TYPE_PLAYER_VEHICLE = 0x22,
	RPC_PACKAGE_TYPE_PLAYER_PASSENGER = 0x23,
	RPC_PACKAGE_TYPE_VEHICLE = 0x3,
	RPC_PACKAGE_TYPE_ACTOR = 0x4,
	RPC_PACKAGE_TYPE_OBJECT = 0x5
};

enum eDisconnectReason
{
	REASON_DISCONNECT,
	REASON_TIMEOUT,
	REASON_KICKED
};

enum eNetworkState
{
	NETSTATE_NONE				= 0,
	NETSTATE_STARTED,
	NETSTATE_CONNECTING,
	NETSTATE_CONNECTED,
	NETSTATE_AWAIT_JOIN,
	NETSTATE_DISCONNECTED,
	NETSTATE_TIMEOUT,
	NETSTATE_AWAIT_CONNECT
};

enum ePackageEntityDefinition
{
	RPC_PACKET_ENTITY_PLAYER = 1,
	RPC_PACKET_ENTITY_VEHICLE = 2
};

struct sNetwork_Sync_Entity_Player
{
	CVector3 vecPosition;
	CVector3 vecMovementSpeed;
	CVector3 vecTurnSpeed;

	bool	 bDuckState;
	float	 fHeading;

	struct {
		CVector3 vecAimTarget;
		float	 vecAimSpecific[2];
		CVector3 vecShotTarget;
	}		 sWeaponData;
};

struct sNetwork_Sync_Entity_Vehicle
{
	CVector3 vecPosition;
};

struct sNetwork_Sync_Packet
{
	ePackageEntityDefinition eEntity;
	sNetwork_Sync_Entity_Player pEntityPlayer;
	sNetwork_Sync_Entity_Vehicle pEntityVehicle;
};


#define	NETWORK_TIMEOUT					3000

#endif // CNetSync_h