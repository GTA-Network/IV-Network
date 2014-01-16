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
	if (!pClientTask)
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
	// Do we have an invalid task pointer?
	if (!pClientTask)
		return false;

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
		return nullptr;

	// Loop through all the client tasks
	for(auto pTask:m_taskList)
	{
		// Is this the client task pair we are looking for?
		if(pTask->pClientTask == pClientTask)
			return pTask->pGameTask;
	}

	return nullptr;
}

CIVTask * CTaskManager::GetClientTaskFromGameTask(IVTask * pGameTask, bool bCreateIfNotExist)
{
	// Do we have an invalid task pointer?
	if(!pGameTask)
		return nullptr;

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
		CIVTask * pClientTask = nullptr;

		if(bIsSimple)
			pClientTask = new CIVTaskSimple((IVTaskSimple *)pGameTask);
		else
			pClientTask = new CIVTaskComplex((IVTaskComplex *)pGameTask);

		// Add the task
		AddTask(pClientTask);

		// Return the new task
		return pClientTask;
	}

	return nullptr;
}

bool CTaskManager::HandleTaskDelete(IVTask * pGameTask)
{
	// Do we have an invalid task pointer?
	if (!pGameTask)
		return false;

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