/*
* Copyright C GTA-Network Team
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