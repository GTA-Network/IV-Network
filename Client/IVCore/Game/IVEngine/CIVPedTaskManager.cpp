//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPedTaskManager.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPedTaskManager.h"
#include <CCore.h>
#include "CIVPed.h"
extern CCore * g_pCore;

CIVPedTaskManager::CIVPedTaskManager(IVPedTaskManager * pPedTaskManager, CIVPed * pPed) :
	m_pPedTaskManager(pPedTaskManager), m_pPed(pPed)
{
}

void CIVPedTaskManager::SetTask(CIVTask * pTask, int iType, bool bForceNewTask)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
		{
			IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
			IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);

			_asm	push bForceNewTask;
			_asm	push iType;
			_asm	push pGameTask;
			_asm	mov ecx, pPedTaskManager;
			_asm	call COffsets::FUNC_CPedTaskManager__SetTaskPriority;
		}
	}
}

void CIVPedTaskManager::RemoveTask(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
		{
			// Make sure its not the default task
			if(iType != TASK_PRIORITY_DEFAULT)
				SetTask(NULL, iType);
		}
	}
}

CIVTask * CIVPedTaskManager::GetTask(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_PRIORITY_MAX)
			return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pPedTaskManager->m_pPrimaryTasks[iType]);
	}

	return NULL;
}

void CIVPedTaskManager::SetTaskSecondary(CIVTask * pTask, int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
		{
			IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
			IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);
			_asm
			{
				push iType
				push pGameTask
				mov ecx, pPedTaskManager
				call COffsets::FUNC_CPedTaskManager__SetTaskSecondary
			}
		}
	}
}

void CIVPedTaskManager::RemoveTaskSecondary(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
			SetTaskSecondary(NULL, iType);
	}
}

CIVTask * CIVPedTaskManager::GetTaskSecondary(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_SECONDARY_MAX)
			return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pPedTaskManager->m_pSecondaryTasks[iType]);
	}

	return NULL;
}

void CIVPedTaskManager::SetTaskMovement(CIVTask * pTask, int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
		{
			IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
			IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);
			_asm
			{
				push iType
				push pGameTask
				mov ecx, pPedTaskManager
				call COffsets::FUNC_CPedTaskManager__SetTaskMovement
			}
		}
	}
}

void CIVPedTaskManager::RemoveTaskMovment(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
			SetTaskMovement(NULL, iType);
	}
}

CIVTask * CIVPedTaskManager::GetTaskMovement(int iType)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Ensure the task type is valid
		if(iType < TASK_MOVEMENT_MAX)
		{
			if(g_pCore->GetGame()->GetTaskManager())
				return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pPedTaskManager->m_pMovementTasks[iType]);
		}
	}

	return NULL;
}

void CIVPedTaskManager::ClearTasks(int iAbortPriority)
{
	// Do we have a valid ped task manager pointer?
	if(m_pPedTaskManager)
	{
		// Clear priority tasks
		for(int i = 0; i < TASK_PRIORITY_MAX; i++)
		{
			CIVTask * pTask = GetTask(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, NULL);
		}

		// Clear secondary tasks
		for(int i = 0; i < TASK_SECONDARY_MAX; i++)
		{
			CIVTask * pTask = GetTaskSecondary(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, NULL);
		}

		// Clear movement tasks
		for(int i = 0; i < TASK_MOVEMENT_MAX; i++)
		{
			CIVTask * pTask = GetTaskMovement(i);

			if(pTask)
				pTask->MakeAbortable(m_pPed, iAbortPriority, NULL);
		}
	}
}