//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CPools.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CPools.h"
#include <Game\IVEngine\CIVPlayerInfo.h>
#include <CCore.h>
extern CCore * g_pCore;

#define INVALID_PLAYER_PED 255

CPools::CPools()
{
	// Reset the ped pool
	m_pPedPool = NULL;

	// Reset the vehicle pool
	m_pVehiclePool = NULL;

	// Reset the task pool
	m_pTaskPool = NULL;

	// Reset the cam pool
	m_pCamPool = NULL;
}

CPools::~CPools()
{
	// Delete the cam pool
	SAFE_DELETE(m_pCamPool);

	// Delete the task pool
	SAFE_DELETE(m_pTaskPool);

	// Delete the vehicle pool
	SAFE_DELETE(m_pVehiclePool);

	// Delete the ped pool
	SAFE_DELETE(m_pPedPool);
}

void CPools::Initialise()
{
	// Get the ped pool
	m_pPedPool = new CIVPool< IVPed >(*(IVPool **)COffsets::VAR_PedPool);

	// Get the vehicle pool
	m_pVehiclePool = new CIVPool< IVVehicle >(*(IVPool **)COffsets::VAR_VehiclePool);

	// Get the task pool
	m_pTaskPool = new CIVPool< IVTask >(*(IVPool **)COffsets::VAR_TaskPool);

	// Get the cam pool
	m_pCamPool = new CIVPool< IVCam >(*(IVPool **)COffsets::VAR_CamPool);
}

IVPlayerInfo * CPools::GetPlayerInfoFromIndex(unsigned int uiIndex)
{
	// Is the index more than the player info array size?
	if(uiIndex > PLAYER_INFO_ARRAY_SIZE)
		return NULL;

	// Get the player info pointer array
	IVPlayerInfo ** pPlayerInfos = (IVPlayerInfo **)COffsets::VAR_PlayerInfoArray;

	// Return the player info pointer
	return pPlayerInfos[uiIndex];
}

IVPlayerInfo * CPools::GetPlayerInfoFromPlayerPed(IVPlayerPed * pPlayerPed)
{
	// Loop through all player info indexes
	for(unsigned int i = 0; i < PLAYER_INFO_ARRAY_SIZE; i++)
	{
		// Get the current player info
		IVPlayerInfo * pPlayerInfo = GetPlayerInfoFromIndex(i);

		// Does the current player info exist?
		if(pPlayerInfo)
		{
			// Is the current player infos playerped the playerped?
			if(pPlayerInfo->m_pPlayerPed == pPlayerPed)
				return pPlayerInfo;
		}
	}

	return NULL;
}

unsigned int CPools::GetIndexFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	// Loop through all player info indexes
	for(unsigned int i = 0; i < PLAYER_INFO_ARRAY_SIZE; i++)
	{
		// Is the current index the player info?
		if(GetPlayerInfoFromIndex(i) == pPlayerInfo)
			return i;
	}

	return INVALID_PLAYER_PED;
}

void CPools::SetPlayerInfoAtIndex(unsigned int uiIndex, IVPlayerInfo * pPlayerInfo)
{
	// Is the index more than the player info array size?
	if(uiIndex > PLAYER_INFO_ARRAY_SIZE)
		return;

	// Get the player info array pointer
	IVPlayerInfo ** pPlayerInfos = (IVPlayerInfo **)COffsets::VAR_PlayerInfoArray;

	// Set the player info pointer
	pPlayerInfos[uiIndex] = pPlayerInfo;
}

unsigned int CPools::FindFreePlayerInfoIndex()
{
	// Loop through all player info indexes
	for(unsigned int i = 0; i < PLAYER_INFO_ARRAY_SIZE; i++)
	{
		// Is the current index free?
		if(!GetPlayerInfoFromIndex(i))
			return i;
	}

	return INVALID_PLAYER_PED;
}

unsigned int CPools::GetLocalPlayerIndex()
{
	return *(unsigned int *)COffsets::VAR_LocalPlayerId;
}

void CPools::SetLocalPlayerIndex(unsigned int uiIndex)
{
	*(unsigned int *)COffsets::VAR_LocalPlayerId = uiIndex;
}