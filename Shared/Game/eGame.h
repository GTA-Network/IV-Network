//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: eGame.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

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
	GAME_STATE_IVMP_PAUSE_MENU,
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
	IVSYNC_ONFOOT_RUN = 2,
	IVSYNC_ONFOOT_JUMP = 3
};
struct sWeaponStructure
{
	CVector3		vecPosition;
	bool			bSwitch;
};

struct sIVSynchronization
{
	BYTE			byteOldMoveStyle;
	bool			bStoreOnFootSwitch;
};

#endif