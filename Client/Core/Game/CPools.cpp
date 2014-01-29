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

#include "CPools.h"
#include <Game\EFLC\CPlayerInfo.h>
#include <CCore.h>
extern CCore * g_pCore;

#define INVALID_PLAYER_PED 255

CPools::CPools() :
	m_pPedPool(nullptr),
	m_pVehiclePool(nullptr),
	m_pTaskPool(nullptr),
	m_pCamPool(nullptr),
	m_pPedMoveBlendPool(nullptr)
{
	// Modify checkpoint rendering to use our custom array
	/*
	VAR_RenderCheckpoints_FirstCP                   = (uiBase +  0x855966);
	VAR_RenderCheckpoints_LastCP                    = (uiBase +  0x856705);
	*/
	//*(DWORD *)(COffsets::VAR_RenderCheckpoints_FirstCP) = (DWORD)m_checkpoints + 0x18;
	//*(DWORD *)(COffsets::VAR_RenderCheckpoints_LastCP) = (DWORD)m_checkpoints + 0x18 + CHECKPOINT_ARRAY_SIZE * sizeof(IVCheckpoint);
}

CPools::~CPools()
{
	// Delete game pools
	SAFE_DELETE(m_pCamPool);
	SAFE_DELETE(m_pTaskPool);
	SAFE_DELETE(m_pVehiclePool);
	SAFE_DELETE(m_pPedPool);
}

void CPools::SetPtrNodeSinglePoolLimit(DWORD dwLimit)
{
	*(DWORD *)(COffsets::IV_Pool__SetPtrSinglePoolLimit) = dwLimit;
}

void CPools::SetPtrNodeDoublePoolLimit(DWORD dwLimit)
{
	*(DWORD *)(COffsets::IV_Pool__SetPtrNodeDoublePoolLimit) = dwLimit;
}

void CPools::SetEntryInfoNodePoolLimit(DWORD dwLimit)
{
	*(DWORD *)(COffsets::IV_Pool__SetEntryInfoNodePoolLimit) = dwLimit;
}

void CPools::SetPedPoolLimit(BYTE byteLimit)
{
	*(DWORD *)(COffsets::IV_Pool__SetPedPoolLimit_1) = (byteLimit * 0xF00); // sizeof(CPed) // for object memory chunk
	*(BYTE *)(COffsets::IV_Pool__SetPedPoolLimit_2) = byteLimit; // for flag memory chunk
	*(BYTE *)(COffsets::IV_Pool__SetPedPoolLimit_3) = byteLimit; // for pool object count
	*(BYTE *)(COffsets::IV_Pool__SetPedPoolLimit_4) = byteLimit; // for constructor init loop
}

void CPools::SetVehiclePoolLimit(DWORD dwLimit)
{
    *(DWORD*)(COffsets::IV_Pool__SetVehiclePoolLimit) = dwLimit;  
}

void CPools::SetVehicleStructPoolLimit(BYTE byteLimit)
{
	*(BYTE *)(COffsets::IV_Pool__SetVehicleStructPoolLimit) = byteLimit;
}

void CPools::Initialize()
{
    // Initialize game pools
	m_pPedPool = new EFLC::CPool<EFLC::IPed>(*(EFLC::IPool **)COffsets::VAR_PedPool);
	m_pVehiclePool = new EFLC::CPool<EFLC::IVehicle>(*(EFLC::IPool **)COffsets::VAR_VehiclePool);
	m_pTaskPool = new EFLC::CPool<EFLC::ITask>(*(EFLC::IPool **)COffsets::VAR_TaskPool);
	m_pCamPool = new EFLC::CPool<EFLC::ICam>(*(EFLC::IPool **)COffsets::VAR_CamPool);
	m_pPedMoveBlendPool = new EFLC::CPool<EFLC::IPedMoveBlendOnFoot>(*(EFLC::IPool **)COffsets::VAR_PedMoveBlendPool);
}

EFLC::IPlayerInfo * CPools::GetPlayerInfoFromIndex(unsigned int uiIndex)
{
	// Is the index more than the player info array size?
	if(uiIndex > PLAYER_INFO_ARRAY_SIZE)
		return nullptr;

	// Get the player info pointer array
	EFLC::IPlayerInfo ** pPlayerInfos = (EFLC::IPlayerInfo **)COffsets::VAR_PlayerInfoArray;

	// Return the player info pointer
	return pPlayerInfos[uiIndex];
}

EFLC::IPlayerInfo * CPools::GetPlayerInfoFromPlayerPed(EFLC::IPlayerPed * pPlayerPed)
{
	// Loop through all player info indexes
	for(unsigned int i = 0; i < PLAYER_INFO_ARRAY_SIZE; i++)
	{
		// Get the current player info
		EFLC::IPlayerInfo * pPlayerInfo = GetPlayerInfoFromIndex(i);

		// Does the current player info exist?
		if(pPlayerInfo)
		{
			// Is the current player infos player ped the player ped?
			if(pPlayerInfo->m_pPlayerPed == pPlayerPed)
				return pPlayerInfo;
		}
	}

	// Player info not found for player ped
	return nullptr;
}

unsigned int CPools::GetIndexFromPlayerInfo(EFLC::IPlayerInfo * pPlayerInfo)
{
	// Loop through all player info indexes
	for(unsigned int i = 0; i < PLAYER_INFO_ARRAY_SIZE; i++)
	{
		// Is the current index the player info?
		if(GetPlayerInfoFromIndex(i) == pPlayerInfo)
			return i;
	}

	// Player info not found in array
	return INVALID_PLAYER_PED;
}

void CPools::SetPlayerInfoAtIndex(unsigned int uiIndex, EFLC::IPlayerInfo * pPlayerInfo)
{
	// Is the index more than the player info array size?
	if(uiIndex > PLAYER_INFO_ARRAY_SIZE)
		return;

	// Get the player info pointer array
	EFLC::IPlayerInfo ** pPlayerInfos = (EFLC::IPlayerInfo **)COffsets::VAR_PlayerInfoArray;

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

	// No free player info indexes found
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
