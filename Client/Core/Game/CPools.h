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
#include <Game\EFLC\CPool.h>
#include <Game\EFLC\CCam.h>
#include <Game\EFLC\CVehicle.h>
#include <Game\EFLC\CPed.h>
#include <Game\EFLC\CPlayerInfo.h>
#include <Game\EFLC\CPlayerPed.h>

// Player info array size
#define PLAYER_INFO_ARRAY_SIZE 32 // 32

// Custom (increased) checkpoint array size
#define CHECKPOINT_ARRAY_SIZE 128

// Invalid checkpoint array index
#define INVALID_CHECKPOINT 255

_GAME_BEGIN
template <class T>
class CPool;
typedef CPool<IVehicle> CVehiclePool;
typedef CPool<IPed> CPedPool;
typedef CPool<ICam> CCamPool;
typedef CPool<IPedMoveBlendOnFoot> CPedMoveBlendPool;
typedef CPool<ITaskInfo> CTaskInfoPool;
_GAME_END

class CPools
{
private:
	// Game pools
	EFLC::CPedPool          * m_pPedPool;
	EFLC::CVehiclePool      * m_pVehiclePool; // Size: 140
	EFLC::CTaskPool         * m_pTaskPool; // Size: 1200
	EFLC::CCamPool          * m_pCamPool;
	EFLC::CPedMoveBlendPool * m_pPedMoveBlendPool;
	EFLC::CTaskInfoPool     * m_pTaskInfoPool;

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
	const decltype(m_pPedPool) GetPedPool() { return m_pPedPool; }
	const decltype(m_pVehiclePool) GetVehiclePool() { return m_pVehiclePool; }
	const decltype(m_pTaskPool) GetTaskPool() { return m_pTaskPool; }
	const decltype(m_pCamPool) GetCamPool() { return m_pCamPool; }
	const decltype(m_pPedMoveBlendPool) GetPedMoveBlendPool() { return m_pPedMoveBlendPool; }

	// Player Infos (An array not a pool)
	EFLC::IPlayerInfo       * GetPlayerInfoFromIndex(unsigned int uiIndex);
	EFLC::IPlayerInfo       * GetPlayerInfoFromPlayerPed(EFLC::IPlayerPed * pPlayerPed);
	unsigned int         GetIndexFromPlayerInfo(EFLC::IPlayerInfo * pPlayerInfo);
	void                 SetPlayerInfoAtIndex(unsigned int uiIndex, EFLC::IPlayerInfo * pPlayerInfo);
	unsigned int         FindFreePlayerInfoIndex();

	// Current Player Info Index (Doesn't really belong here, but it was the only place to put it)
	unsigned int         GetLocalPlayerIndex();
	void                 SetLocalPlayerIndex(unsigned int uiIndex);
};


#endif // CPools_h