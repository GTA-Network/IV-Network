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

#ifndef CPools_h
#define CPools_h

#include <Common.h>
#include <Game\IVEngine\CIVCam.h>
#include <Game\IVEngine\CIVPed.h>
#include <Game\IVEngine\CIVVehicle.h>
#include <Game\IVEngine\CIVPlayerPed.h>
#include <Game/CTaskManager.h>
#include <Game\IVEngine\CIVTask.h>
#include <Game\IVEngine\CIVPedMoveBlend.h>
#include <Game\IVEngine\TaskInfo\CIVTaskInfo.h>

// Player info array size
#define PLAYER_INFO_ARRAY_SIZE 32 // 32

// Custom (increased) checkpoint array size
#define CHECKPOINT_ARRAY_SIZE 128

// Invalid checkpoint array index
#define INVALID_CHECKPOINT 255

template <class T>
class CIVPool;

class CPools
{
private:
	// Game pools
	CIVPool<IVPed>                * m_pPedPool;
	CIVPool<IVVehicle>            * m_pVehiclePool; // Size: 140
	CIVPool<IVTask>               * m_pTaskPool; // Size: 1200
	CIVPool<IVCam>                * m_pCamPool;
	CIVPool<IVPedMoveBlendOnFoot> * m_pPedMoveBlendPool;
	CIVPool<IVTaskInfo>			  * m_pTaskInfoPool;

public:
	CPools();
	~CPools();

	// Pool increases (These must be called before pools are created obviously...)
	void                 SetPtrNodeSinglePoolLimit(DWORD dwLimit);  // 80000 default
	void                 SetPtrNodeDoublePoolLimit(DWORD dwLimit);  // 16000 default
	void                 SetEntryInfoNodePoolLimit(DWORD dwLimit);  // 16000 default
	void                 SetPedPoolLimit(BYTE byteLimit);           // 120 default
	void                 SetVehiclePoolLimit(DWORD dwLimit);        // 140 default
	void                 SetVehicleStructPoolLimit(BYTE byteLimit); // 50 default

	void                 Initialize();

	// Pools
	CIVPool<IVPed>     * GetPedPool() { return m_pPedPool; }
	CIVPool<IVVehicle> * GetVehiclePool() { return m_pVehiclePool; }
	CIVPool<IVTask>    * GetTaskPool() { return m_pTaskPool; }
	CIVPool<IVCam>     * GetCamPool() { return m_pCamPool; }
	CIVPool<IVPedMoveBlendOnFoot> * GetPedMoveBlendPool() { return m_pPedMoveBlendPool; }

	// Player Infos (An array not a pool)
	IVPlayerInfo       * GetPlayerInfoFromIndex(unsigned int uiIndex);
	IVPlayerInfo       * GetPlayerInfoFromPlayerPed(IVPlayerPed * pPlayerPed);
	unsigned int         GetIndexFromPlayerInfo(IVPlayerInfo * pPlayerInfo);
	void                 SetPlayerInfoAtIndex(unsigned int uiIndex, IVPlayerInfo * pPlayerInfo);
	unsigned int         FindFreePlayerInfoIndex();

	// Current Player Info Index (Doesn't really belong here, but it was the only place to put it)
	unsigned int         GetLocalPlayerIndex();
	void                 SetLocalPlayerIndex(unsigned int uiIndex);
};


#endif // CPools_h