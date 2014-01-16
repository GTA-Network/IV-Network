/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
	Matrix						matrix;
	float						fHeading;
	CVector3					vecMoveSpeed;
	CVector3					vecTurnSpeed;
	float						fHealth;
	float						fArmor;
	bool						bDuckState;
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