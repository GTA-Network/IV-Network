//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
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

CIVPedTaskManager::CIVPedTaskManager( IVPedTaskManager * pPedTaskManager, CIVPed * pPed )
{
	// Set the task manager
	SetPedTaskManager( pPedTaskManager );

	// Set the ped
	SetPed( pPed );
}

void CIVPedTaskManager::SetTask( CIVTask * pTask, int iType, bool bForceNewTask )
{
	// Is the ped task manager invalid?
	if( !m_pPedTaskManager )
		return;

	// Is the task invalid?
	if( iType >= TASK_PRIORITY_MAX )
		return;

	IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
	IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);
	int iForceNewTask = (int)bForceNewTask;

	_asm	push iForceNewTask;
	_asm	push iType;
	_asm	push pGameTask;
	_asm	mov ecx, pPedTaskManager;
	_asm	call COffsets::FUNC_CPedTaskManager__SetTaskPriority;
}

void CIVPedTaskManager::RemoveTask( int iType )
{
	// Is the ped task manager invalid?
	if( !m_pPedTaskManager )
		return;

	// Is the task invalid?
	if( iType >= TASK_PRIORITY_MAX )
		return;

	// Is the task the default task?
	if( iType == TASK_PRIORITY_DEFAULT )
		return;

	// Set the task
	SetTask( NULL, iType );
}

CIVTask * CIVPedTaskManager::GetTask( int iType )
{
	// Is the ped task manager invalid?
	if( !m_pPedTaskManager )
		return NULL;

	// Is the task invalid?
	if( iType >= TASK_PRIORITY_MAX )
		return NULL;

	return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask( m_pPedTaskManager->m_pPrimaryTasks[iType] );
}

void CIVPedTaskManager::SetSecondaryTask( CIVTask * pTask, int iType )
{
	// Is the ped task manager invalid?
	if( !m_pPedTaskManager )
		return;

	// Is the task invalid?
	if( iType >= TASK_SECONDARY_MAX )
		return;

	IVPedTaskManager * pPedTaskManager = m_pPedTaskManager;
	IVTask * pGameTask = (pTask ? pTask->GetTask() : NULL);
	
	_asm	push iType;
	_asm	push pGameTask;
	_asm	mov ecx, pPedTaskManager;
	_asm	call COffsets::FUNC_CPedTaskManager__SetTaskSecondary;
}

void CIVPedTaskManager::RemoveSecondaryTask( int iType )
{
	// Is the ped task manager invalid?
	if( !m_pPedTaskManager )
		return;

	// Is the task invalid?
	if( iType >= TASK_SECONDARY_MAX )
		return;

	// Set the task
	SetSecondaryTask( NULL, iType );
}

CIVTask * CIVPedTaskManager::GetSecondaryTask( int iType )
{
	// Is the ped task manager invalid?
	if( !m_pPedTaskManager )
		return NULL;

	// Is the task invalid?
	if( iType >= TASK_SECONDARY_MAX )
		return NULL;

	return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask( m_pPedTaskManager->m_pSecondaryTasks[iType] );
}

void CIVPedTaskManager::ClearTask( int iAbortPriority )
{
	// Is the ped task manager invalid?
	if( !m_pPedTaskManager )
		return;

	// Clear the primary tasks
	for( int i = 0; i < TASK_PRIORITY_MAX; i++ )
	{
		// Get the task pointer
		CIVTask * pTask = GetTask( i );

		// Is the task pointer valid?
		if( pTask )
		{
			// Abort the task
			pTask->MakeAbortable( m_pPed, iAbortPriority, NULL );
		}
	}

	// Clear the secondary tasks
	for( int i = 0; i < TASK_SECONDARY_MAX; i++ )
	{
		// Get the task pointer
		CIVTask * pTask = GetSecondaryTask( i );

		// Is the task pointer valid?
		if( pTask )
		{
			// Abort the task
			pTask->MakeAbortable( m_pPed, iAbortPriority, NULL );
		}
	}
}