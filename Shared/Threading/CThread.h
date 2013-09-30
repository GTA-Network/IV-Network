//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CThread.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CThread_h
#define CThread_h

#include "CMutex.h"
#ifdef _WIN32
#include <WinSock2.h>
#include <windows.h>
#endif

class CThread
{
private:
	typedef void     (* ThreadFunction_t)(CThread * pCreator);

#ifdef _WIN32
	HANDLE           m_hThread;
#else
	pthread_t        m_thread;
#endif
	ThreadFunction_t m_pfnThreadFunction;
	CMutex           m_startedMutex; // Mutex for m_bStarted
	bool             m_bStarted;
	CMutex           m_runningMutex; // Mutex for m_bRunning
	bool             m_bRunning;
	CMutex           m_userDataMutex; // Mutex for m_pUserData
	void *           m_pUserData;

	void        SetStarted(bool bStarted);
	bool        IsStarted();
	void        SetRunning(bool bRunning);

public:
	CThread();
	~CThread();

	void        Start(ThreadFunction_t pfnThreadFunction, bool bWaitForStart = true);
	bool        Stop(bool bWaitForExit = true, bool bTerminate = false);
	bool        IsRunning();

	template <typename DataType>
	void        SetUserData(DataType pUserData)
	{
		// Lock the user data mutex
		m_userDataMutex.Lock();

		// Set the user data
		m_pUserData = (void *)pUserData;

		// Unlock the user data mutex
		m_userDataMutex.Unlock();
	}

	template <typename ReturnType>
	ReturnType  GetUserData()
	{
		// Lock the user data mutex
		m_userDataMutex.Lock();

		// Get the user data
#ifdef _MSC_VER
#pragma warning(disable:4800) // forcing value to bool (performance warning)
#endif
		ReturnType pUserData = (ReturnType)m_pUserData;

		// Unlock the user data mutex
		m_userDataMutex.Unlock();

		return pUserData;
	}

#ifdef _WIN32
	static void StartAddress(CThread * pThis);
#else
	static void * StartAddress(void * pThis);
#endif
};

#endif // CThread_h