//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPools.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

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
#include <Game\IVEngine\CIVCheckpoint.h>

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

	// Custom checkpoint array
	IVCheckpoint                    m_checkpoints[CHECKPOINT_ARRAY_SIZE];

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

	// Checkpoints (An array not a pool)
	IVCheckpoint       * GetCheckpointFromIndex(unsigned int uiIndex);
	unsigned int         FindFreeCheckpointIndex();
};


#endif // CPools_h