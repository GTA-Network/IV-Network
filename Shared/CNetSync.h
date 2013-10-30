//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
#include "Game/eInput.h"

enum ePackageType
{
	RPC_PACKAGE_TYPE_SMALL = 0x1,
	RPC_PACKAGE_TYPE_PLAYER_ONFOOT = 0x20,
	RPC_PACKAGE_TYPE_PLAYER_WEAPON = 0x22,
	RPC_PACKAGE_TYPE_PLAYER_PASSENGER = 0x23,
	RPC_PACKAGE_TYPE_PLAYER_VEHICLE = 0x30,
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
	NETSTATE_NONE = 0,
	NETSTATE_STARTED,
	NETSTATE_CONNECTING,
	NETSTATE_CONNECTED,
	NETSTATE_AWAIT_JOIN,
	NETSTATE_DISCONNECTED,
	NETSTATE_TIMEOUT,
	NETSTATE_AWAIT_CONNECT
};

enum eEntityType
{
	PLAYER_ENTITY,
	VEHICLE_ENTITY,
	OBJECT_ENTITY,
	PICKUP_ENTITY,
	LABEL_ENTITY,
	FIRE_ENTITY,
	CHECKPOINT_ENTITY,
	BLIP_ENTITY,
	ACTOR_ENTITY,
	UNKNOWN_ENTITY, // MAX_ENTITY
	INVALID_ENTITY,
};


// Handles data between client ped and network sync(stores the values)
class CNetworkPlayerSyncPacket {
private:
public:
	CControls					pControlState; 
	CVector3					vecPosition;
	CVector3					vecMovementSpeed;
	CVector3					vecTurnSpeed;
	CVector3					vecDirection;
	CVector3					vecRoll;

	bool						bDuckState;
	float						fHeading;
	float						fHealth;
	// Add player members to sync(like weapon sync, key sync etc.)
};

class CNetworkPlayerWeaponSyncPacket {
public:
	CVector3       vecAimShotAtCoordinates; // When fire this is shot at when aiming this is Aim at
	//float          fArmsHeadingCircle;
	//float          fArmsUpDownRotation;
	CVector3       vecShotSource;
	char		   weaponType;
	int			   iAmmo;
};

class CNetworkPlayerVehicleSyncPacket {
public:
	CControls					ControlState;
	EntityId					vehicleId;
	Matrix						matrix;
	CVector3					vecMoveSpeed;
	CVector3					vecTurnSpeed;
	float						health;
	float						petrol;
	float						steeringAngle;
	float						fHeading;
	bool						bEngineState;

};

class CSyncWeapon
{
public:
	char	weaponSlot;
	char	weaponType;
	int		iAmmo;
	int		iClip;
};

// Handles data between client ped and network sync(stores the values)
class CNetworkEntityVehicleSyncPacket {
private:

public:
	CVector3					vecPosition;
	CVector3					vecMovementSpeed;
	CVector3					vecTurnSpeed;
	CVector3					vecDirection;
	CVector3					vecRoll;
	// Add vehicle members to sync(like indicators, variation etc.)
};

#define	NETWORK_TIMEOUT					3000

#endif // CNetSync_h