//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CTaskManager.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CTaskManager.h"
#include <CLogFile.h>

CTaskManager::CTaskManager()
{
	CLogFile::Printf("CTaskManager::CTaskManager");
}

CTaskManager::~CTaskManager()
{
	CLogFile::Printf("CTaskManager::~CTaskManager");
	// Loop through all the client tasks
	for(std::list< ClientTaskPair *>::iterator iter = m_taskList.begin(); iter != m_taskList.end(); iter++)
	{
		// Delete the client task pair
		delete (*iter);
	}
}

bool CTaskManager::AddTask(CIVTask * pClientTask)
{
	CLogFile::Printf("CTaskManager::AddTask(0x%p)", pClientTask);
	// Do we have an invalid task pointer?
	if(!pClientTask)
		return false;

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
	CLogFile::Printf("CTaskManager::RemoveTask(0x%p)", pClientTask);
	// Do we have an invalid task pointer?
	if(!pClientTask)
		return false;

	// Loop through all the client tasks
	for(std::list< ClientTaskPair *>::iterator iter = m_taskList.begin(); iter != m_taskList.end(); iter++)
	{
		// Is this the client task pair we are looking for?
		if((*iter)->pClientTask == pClientTask)
		{
			// Delete the client task pair
			delete (*iter);

			// Remove it from the list
			m_taskList.remove(*iter);

			return true;
		}
	}

	return false;
}

IVTask * CTaskManager::GetGameTaskFromClientTask(CIVTask * pClientTask)
{
	CLogFile::Printf("CTaskManager::GetGameTaskFromClientTask(0x%p)", pClientTask);
	// Do we have an invalid task pointer?
	if(!pClientTask)
		return NULL;

	// Loop through all the client tasks
	for(std::list< ClientTaskPair *>::iterator iter = m_taskList.begin(); iter != m_taskList.end(); iter++)
	{
		// Is this the client task pair we are looking for?
		if((*iter)->pClientTask == pClientTask)
		{
			return (*iter)->pGameTask;
		}
	}

	return NULL;
}

CIVTask * CTaskManager::GetClientTaskFromGameTask(IVTask * pGameTask, bool bCreateIfNotExist)
{
	CLogFile::Printf("CTaskManager::GetClientTaskFromGameTask(0x%p, %s)", pGameTask, bCreateIfNotExist ? "true" : "false");
	// Do we have an invalid task pointer?
	if(!pGameTask)
		return NULL;

	// Loop through all the client tasks
	for(std::list< ClientTaskPair *>::iterator iter = m_taskList.begin(); iter != m_taskList.end(); iter++)
	{
		// Is this the client task pair we are looking for?
		if((*iter)->pGameTask == pGameTask)
		{
			return (*iter)->pClientTask;
		}
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
	if(!pGameTask)
		return NULL;

	// Try and get the client task pointer for this game task
	CIVTask * pClientTask = GetClientTaskFromGameTask(pGameTask, false);

	// Do we have a valid client task pointer?
	if(pClientTask)
	{
		CLogFile::Printf("CTaskManager::HandleTaskDelete(0x%p)" , pGameTask);

		// Remove the task
		RemoveTask(pClientTask);

		// Delete the client task
		delete pClientTask;

		return true;
	}

	return false;
}