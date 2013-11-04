//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTaskManager.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CTaskManager.h"
#include <CLogFile.h>

CTaskManager::~CTaskManager()
{
	// Loop through all the client tasks
	for(auto pTask:m_taskList)
	{
		// Delete the client task pair
		delete pTask;
	}
}

bool CTaskManager::AddTask(CIVTask * pClientTask)
{
	// Do we have an invalid task pointer?
	CHECK_VALID(pClientTask);

	// Create the client task pair
	ClientTaskPair * pClientTaskPair = new ClientTaskPair;

	// Do we have an invalid task pair?
	if(!pClientTaskPair)
		return false;

	// Set the client task pair pointers
	pClientTaskPair->pGameTask = pClientTask->GetTask();
	pClientTaskPair->pClientTask = pClientTask;

	// Add the client task pair to the client task pair list
	m_taskList.push_back(pClientTaskPair);

	return true;
}

bool CTaskManager::RemoveTask(CIVTask * pClientTask)
{
	// Do we have an invalid task pointer?
	CHECK_VALID(pClientTask);

	// Loop through all the client tasks
	for(auto pTask:m_taskList)
	{
		// Is this the client task pair we are looking for?
		if(pTask->pClientTask == pClientTask)
		{
			// Delete the client task pair
			delete pTask;

			// Remove it from the list
			m_taskList.remove(pTask);

			return true;
		}
	}

	return false;
}

IVTask * CTaskManager::GetGameTaskFromClientTask(CIVTask * pClientTask)
{
	// Do we have an invalid task pointer?
	if(!pClientTask)
		return NULL;

	// Loop through all the client tasks
	for(auto pTask:m_taskList)
	{
		// Is this the client task pair we are looking for?
		if(pTask->pClientTask == pClientTask)
			return pTask->pGameTask;
	}

	return NULL;
}

CIVTask * CTaskManager::GetClientTaskFromGameTask(IVTask * pGameTask, bool bCreateIfNotExist)
{
	// Do we have an invalid task pointer?
	if(!pGameTask)
		return NULL;

	// Loop through all the client tasks
	for(auto pTask:m_taskList)
	{
		// Is this the client task pair we are looking for?
		if(pTask->pGameTask == pGameTask)
			return pTask->pClientTask;
	}

	// Create the task if requested
	if(bCreateIfNotExist)
	{
		// Create a temp intance
		CIVTask * pTempClientTask = new CIVTask(pGameTask);

		// Is this task simple?
		bool bIsSimple = pTempClientTask->IsSimple();

		// Delete the temporary instance
		delete pTempClientTask;

		// Create the client task instance
		CIVTask * pClientTask = NULL;

		if(bIsSimple)
			pClientTask = new CIVTaskSimple((IVTaskSimple *)pGameTask);
		else
			pClientTask = new CIVTaskComplex((IVTaskComplex *)pGameTask);

		// Add the task
		AddTask(pClientTask);

		// Return the new task
		return pClientTask;
	}

	return NULL;
}

bool CTaskManager::HandleTaskDelete(IVTask * pGameTask)
{
	// Do we have an invalid task pointer?
	CHECK_VALID(pGameTask);

	// Try and get the client task pointer for this game task
	CIVTask * pClientTask = GetClientTaskFromGameTask(pGameTask, false);

	// Do we have a valid client task pointer?
	if(pClientTask)
	{
		// Remove the task
		RemoveTask(pClientTask);

		// Delete the client task
		delete pClientTask;

		return true;
	}

	return false;
}