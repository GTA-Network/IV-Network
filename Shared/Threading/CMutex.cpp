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

#include "CMutex.h"
#include <SharedUtility.h>

CMutex::CMutex()
{
	// Create the mutex
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	InitializeCriticalSection(&m_criticalSection);
#else
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
#endif
#else
	pthread_mutex_init(&m_mutex, NULL);
#endif
}

CMutex::~CMutex()
{
	// Delete the mutex
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	DeleteCriticalSection(&m_criticalSection);
#else
	CloseHandle(m_hMutex);
#endif
#else
	pthread_mutex_destroy(&m_mutex);
#endif
}

void CMutex::Lock()
{
	// Lock the mutex
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	EnterCriticalSection(&m_criticalSection);
#else
	WaitForSingleObject(m_hMutex, INFINITE);
#endif
#else
	pthread_mutex_lock(&m_mutex);
#endif
}

bool CMutex::TryLock(unsigned int uiTimeOutMilliseconds)
{
	// Attempt to lock the mutex
	bool bLocked = false;
#if defined(_WIN32) && !defined(USE_CRITICAL_SECTION)
	bLocked = (WaitForSingleObject(m_hMutex, uiTimeOutMilliseconds) == 0);
#else
	if(uiTimeOutMilliseconds == 0)
	{
#ifdef _WIN32
		bLocked = (TryEnterCriticalSection(&m_criticalSection) != 0);
#else
		bLocked = pthread_mutex_trylock(&m_mutex);
#endif
	}
	else
	{
		unsigned long ulEndTime = (SharedUtility::GetTime() + uiTimeOutMilliseconds);

		while(SharedUtility::GetTime() < ulEndTime)
		{
#ifdef _WIN32
			if(TryEnterCriticalSection(&m_criticalSection))
#else
			if(pthread_mutex_trylock(&m_mutex))
#endif
			{
				bLocked = true;
				break;
			}
		}
	}
#endif

	return bLocked;
}

void CMutex::Unlock()
{
	// Unlock the mutex
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	LeaveCriticalSection(&m_criticalSection);
#else
	ReleaseMutex(m_hMutex);
#endif
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}
