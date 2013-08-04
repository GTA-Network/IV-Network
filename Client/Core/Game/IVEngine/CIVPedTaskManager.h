//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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
class IVPedTaskManager
{
public:
	IVTask * m_pPrimaryTasks[TASK_PRIORITY_MAX];
	IVTask * m_pSecondaryTasks[TASK_SECONDARY_MAX];
	IVTask * m_pMovementTasks[TASK_MOVEMENT_MAX];
};

class CIVPedTaskManager
{

private:

	IVPedTaskManager		* m_pPedTaskManager;
	CIVPed					* m_pPed;

public:

	CIVPedTaskManager( IVPedTaskManager * pPedTaskManager, CIVPed * pPed );

	void					SetPedTaskManager( IVPedTaskManager * pPedTaskManager ) { m_pPedTaskManager = pPedTaskManager; }
	IVPedTaskManager		* GetPedTaskManager( ) { return m_pPedTaskManager; }

	void					SetPed( CIVPed * pPed ) { m_pPed = pPed; }
	CIVPed					* GetPed( ) { return m_pPed; }

	// Primary tasks
	void					SetTask( CIVTask * pTask, int iType, bool bForceNewTask = false );
	void					RemoveTask( int iType );
	CIVTask					* GetTask( int iType );

	// Secondary tasks
	void					SetSecondaryTask( CIVTask * pTask, int iType );
	void					RemoveSecondaryTask( int iType );
	CIVTask					* GetSecondaryTask( int iType );

	// Movement tasks
	// todo

	void					ClearTask( int iAbortPriority );

};

#endif // CIVPedTaskManager_h