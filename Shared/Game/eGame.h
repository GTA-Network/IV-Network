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

#ifndef eGame_h
#define eGame_h

// Define internal synchronization time
#define IVSYNC_TICKRATE 25

#include <Common.h>
#include "eIVGame.h"
#include "eInput.h"
#include <Network/CBitStream.h>
#include <Math/CMaths.h>

enum eGAMEStates
{
	GAME_STATE_NONE,
	GAME_STATE_MAIN_MENU,
	GAME_STATE_LOADING,
	GAME_STATE_INGAME,
	GAME_STATE_PAUSE_MENU,
	GAME_STATE_IVN_PAUSE_MENU,
};

enum eWeather
{
	WEATHER_EXTRA_SUNNY,
	WEATHER_SUNNY,
	WEATHER_SUNNY_WINDY,
	WEATHER_CLOUDY,
	WEATHER_RAINING,
	WEATHER_DRIZZLE,
	WEATHER_FOGGY,
	WEATHER_LIGHTNING,
	WEATHER_EXTRA_SUNNY_2,
	WEATHER_SUNNY_WINDY_2
};

enum eAbortPriority
{
	ABORT_PRIORITY_LEISURE = 0,
	ABORT_PRIORITY_URGENT,
	ABORT_PRIORITY_IMMEDIATE
};

enum eTaskPriority
{
	TASK_PRIORITY_PHYSICAL_RESPONSE,
	TASK_PRIORITY_EVENT_RESPONSE_TEMP,
	TASK_PRIORITY_EVENT_RESPONSE_NONTEMP,
	TASK_PRIORITY_PRIMARY,
	TASK_PRIORITY_DEFAULT,
	TASK_PRIORITY_MAX
};

enum eTaskSecondary
{
	TASK_SECONDARY_ATTACK,
	TASK_SECONDARY_DUCK,
	TASK_SECONDARY_SAY,
	TASK_SECONDARY_FACIAL_COMPLEX,
	TASK_SECONDARY_PARTIAL_ANIM,
	TASK_SECONDARY_IK,
	TASK_SECONDARY_MAX
};

enum eTaskMovement
{
	TASK_MOVEMENT_UNKNOWN0,
	TASK_MOVEMENT_UNKNOWN1,
	TASK_MOVEMENT_UNKNOWN2,
	TASK_MOVEMENT_MAX
};

enum eModelType
{
	MODEL_TYPE_BASE = 1,
	MODEL_TYPE_MLO,
	MODEL_TYPE_TIME,
	MODEL_TYPE_WEAPON,
	MODEL_TYPE_VEHICLE,
	MODEL_TYPE_PED
};

enum eExitVehicleType
{
	EXIT_VEHICLE_NORMAL,
	EXIT_VEHICLE_JACKED
};

enum eIVSynchronization
{
	IVSYNC_ONFOOT_STANDSTILL = 0,
	IVSYNC_ONFOOT_WALK = 1,
	IVSYNC_ONFOOT_SWITCHSTATE = 2,
	IVSYNC_ONFOOT_RUN = 3
};
struct sWeaponStructure
{
	CVector3		vecPosition;
	bool			bSwitch;
};

struct sIVSynchronization
{
	BYTE			byteMoveStyle;
	BYTE			byteOldMoveStyle;
	bool			bStoreOnFootSwitch;
};

class CVehicleEntity;
struct sPlayerEntity_VehicleData
{
	bool			bEntering;
	CVehicleEntity	* pVehicle;
	BYTE			byteSeat;
	bool			bExiting;
	bool			bRequesting;
};

struct sPlayerEntity_InterpolationData
{
	struct
	{
		CVector3      vecStart;
		CVector3      vecTarget;
		CVector3      vecError;
		float         fLastAlpha;
		unsigned long ulStartTime;
		unsigned long ulFinishTime;
	}				pPosition;
	struct
	{
		float         fStart;
		float         fTarget;
		float         fError;
		float         fLastAlpha;
		unsigned long ulStartTime;
		unsigned long ulFinishTime;
	}				pRotation;
};

struct sPlayerEntity_StoreIVSynchronization
{
	CVector3		vecPosition;
	CVector3		vecMovementSpeed;
	CVector3		vecTurnSpeed;
	CVector3		vecDirection;
	CVector3		vecRoll;

	bool			bDuckState;
	float			fHeading;

	CVector3		vecAimAtCoordinates;
	float			fArmsHeadingCircle;
	float			fArmsUpDownRotation;
	CVector3		vecShotAtCoordinates;
	CVector3		vecShotAtTarget;
	CVector3		vecLookAtCoordinates;
	/*Matrix34		pWeaponCameraA;
	Matrix34		pWeaponCameraB;
	Matrix34		pWeaponCameraC;
	*/
	CControls	   *pControls ;
	unsigned		uiPlayerIndex;
	unsigned		uiJumpTime;
};

#endif