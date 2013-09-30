//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPedTaskManager.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPedTaskManager_h
#define CIVPedTaskManager_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

#include "CIVTask.h"

class IVTask;
class IVPed;

class IVPedTaskManager {
public:
	IVTask * m_pPrimaryTasks[TASK_PRIORITY_MAX];    // 00-14
	IVTask * m_pSecondaryTasks[TASK_SECONDARY_MAX]; // 14-2C
	IVTask * m_pMovementTasks[TASK_MOVEMENT_MAX];   // 2C-38
	IVPed * m_pPed;                                 // 38-3C
	PAD(IVPedTaskManager, pad0, 0x4);               // 3C-40
};

class CIVPedTaskManager {
private:
	IVPedTaskManager * m_pPedTaskManager;
	CIVPed           * m_pPed;

public:
	CIVPedTaskManager(IVPedTaskManager * pPedTaskManager, CIVPed * pPed);

	void               SetPedTaskManager(IVPedTaskManager * pPedTaskManager) { m_pPedTaskManager = pPedTaskManager; }
	IVPedTaskManager * GetPedTaskManager() { return m_pPedTaskManager; }
	void               SetPed(CIVPed * pPed) { m_pPed = pPed; }
	CIVPed           * GetPed() { return m_pPed; }

	// Primary tasks
	void               SetTask(CIVTask * pTask, int iType, bool bForceNewTask = false);
	void               RemoveTask(int iType);
	CIVTask          * GetTask(int iType);

	// Secondary tasks
	void               SetTaskSecondary(CIVTask * pTask, int iType);
	void               RemoveTaskSecondary(int iType);
	CIVTask          * GetTaskSecondary(int iType);

	// Movement tasks
	void               SetTaskMovement(CIVTask * pTask, int iType);
	void               RemoveTaskMovment(int iType);
	CIVTask          * GetTaskMovement(int iType);

	void               ClearTasks(int iAbortPriority);
};

#endif // CIVPedTaskManager_h