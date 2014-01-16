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

#include "CThread.h"

#ifdef _LINUX
#include <unistd.h>
#include <pthread.h>
#define Sleep usleep
#endif

CThread::CThread() :
	m_bStarted(false),
	m_bRunning(false),
	m_pUserData(NULL)
{
}

CThread::~CThread()
{
	// Stop the thread if it is started
	Stop();
}

void CThread::Start(ThreadFunction_t pfnThreadFunction, bool bWaitForStart)
{
	// Stop the thread if it is started
	Stop();

	// Set the thread function pointer
	m_pfnThreadFunction = pfnThreadFunction;

	// Set the started state to false
	m_bStarted = false;

	// Set the running state to false
	m_bRunning = false;

	// Create the thread
#ifdef _WIN32
	m_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartAddress, (void *)this, 0, NULL);
#else
	pthread_create(&m_thread, NULL, StartAddress, (void *)this);
#endif

	// Are we supposed to wait for the thread to start?
	if(bWaitForStart)
	{
		// Wait for the thread to start
		while(!IsStarted())
		{
			// Sleep for 1ms
			Sleep(1);
		}
	}
}

bool CThread::Stop(bool bWaitForExit, bool bTerminate)
{
	// Is the thread started?
	if(IsStarted())
	{
		// Do we need to terminate the thread?
		if(bTerminate)
		{
			// Terminate the thread
#ifdef _WIN32
			TerminateThread(m_hThread, 0);
#else
			pthread_cancel(m_thread);
#endif
		}

		// Delete the thread
#ifdef _WIN32
		CloseHandle(m_hThread);
#else
		pthread_cancel(m_thread);
#endif

		// Are we not terminating the thread and are we
		// supposed to wait for the thread to exit?
		if(!bTerminate && bWaitForExit)
		{
			// Wait for the thread to exit
			while(IsRunning())
			{
				// Sleep for 1ms
				Sleep(1);
			}
		}

		// Set the running state to false
		SetRunning(false);

		// Set the started state to false
		SetStarted(false);

#ifdef _WIN32
		// Reset the thread handle
		m_hThread = NULL;
#else
		m_thread = NULL;
#endif

		return true;
	}

	return false;
}

void CThread::SetStarted(bool bStarted)
{
	// Lock the started state mutex
	m_startedMutex.Lock();

	// Set the started state
	m_bStarted = bStarted;

	// Unlock the started state mutex
	m_startedMutex.Unlock();
}

bool CThread::IsStarted()
{
	// Lock the started state mutex
	m_startedMutex.Lock();

	// Get the started state
	bool bStarted = m_bStarted;

	// Unlock the started state mutex
	m_startedMutex.Unlock();

	return bStarted;
}

void CThread::SetRunning(bool bRunning)
{
	// Lock the running state mutex
	m_runningMutex.Lock();

	// Set the running state
	m_bRunning = bRunning;

	// Unlock the running state mutex
	m_runningMutex.Unlock();
}

bool CThread::IsRunning()
{
	// Lock the running state mutex
	m_runningMutex.Lock();

	// Get the running state
	bool bRunning = m_bRunning;

	// Unlock the running state mutex
	m_runningMutex.Unlock();

	return bRunning;
}

#ifdef _WIN32
void CThread::StartAddress(CThread * pThis)
#else
void * CThread::StartAddress(void * pVoidThis)
#endif
{
#ifndef WIN32
        // Get the thread this pointer
        CThread * pThis = (CThread *)pVoidThis;
#endif
	// Set the started state to true
	pThis->SetStarted(true);

	// Set the running state to true
	pThis->SetRunning(true);

	// Call the thread function
	pThis->m_pfnThreadFunction(pThis);

	// Set the running state to false
	pThis->SetRunning(false);

#ifndef WIN32
	return (void *)1;
#endif
}
