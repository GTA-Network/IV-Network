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

class CSyncWeapon
{
public:
	//char	weaponSlot;
	char	weaponType;
	int		iAmmo;
	//int		iClip;
};

// Handles data between client ped and network sync(stores the values)
class CNetworkPlayerSyncPacket {
private:
public:
	CControls					pControlState; 
	CVector3					vecPosition;
	float						fHeading;
	CVector3					vecMoveSpeed;
	CVector3					vecTurnSpeed;
	float						fHealth;
	float						fArmor;
	bool						bDuckState;
	CVector3					vecDirection;
	CVector3					vecRoll;
	CSyncWeapon					weapon;
};



class CNetworkPlayerWeaponSyncPacket {
public:
	CVector3       vecAimShotAtCoordinates; // When fire this is shot at when aiming this is Aim at
	CVector3       vecShotSource;
	CSyncWeapon	   weapon;
};

// Pure sync packet
class CNetworkPlayerVehicleSyncPacket {
public:
	EntityId					vehicleId;
	CControls					ControlState;
	Matrix						matrix;
	CVector3					vecMoveSpeed;
	CVector3					vecTurnSpeed;
	float						vehHealth;
	float						playerHealth;
	float						playerArmor;
	float						fHeading;
	bool						bEngineState;
	CSyncWeapon					weapon;
};

class CNetworkPlayerPassengerSyncPacket {
public:
	EntityId					vehicleId;
	unsigned char				byteSeatId;
	CControls					ControlState;
	CVector3					vecPosition;
	float						playerHealth;
	float						playerArmor;
};



#define	NETWORK_TIMEOUT					3000

#endif // CNetSync_h