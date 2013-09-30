//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CMutex.cpp
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

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
