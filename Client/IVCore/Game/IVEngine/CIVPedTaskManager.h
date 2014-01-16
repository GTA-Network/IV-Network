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