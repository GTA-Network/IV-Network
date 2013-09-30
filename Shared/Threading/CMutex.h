//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CMutex.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CMutex_h
#define CMutex_h

#include <Common.h>
#include <CString.h>

#define USE_CRITICAL_SECTION

class CMutex
{
private:
#ifdef _WIN32
#ifdef USE_CRITICAL_SECTION
	// Faster than a standard mutex (But not shared among processes)
	CRITICAL_SECTION m_criticalSection;
#else
	HANDLE m_hMutex;
#endif
#else
	pthread_mutex_t m_mutex;
#endif

public:
	CMutex();
	~CMutex();

	void Lock();
	bool TryLock(unsigned int uiTimeOutMilliseconds = 0);
	void Unlock();
};

#endif // CMutex_h