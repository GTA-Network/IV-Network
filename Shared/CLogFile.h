//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CLogFile.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CLogFile_h
#define CLogFile_h

#include "CString.h"
#include "Threading/CMutex.h"
#include <stdio.h>

#define PRINT_FUNCTION ; //CLogFile::Print(__FUNCTION__);
typedef void (* LogFileCallback_t)(const char * szBuffer);

class CLogFile
{
private:
	static FILE *            m_fLogFile;
	static bool              m_bUseCallback;
	static LogFileCallback_t m_pfnCallback;
	static bool              m_bUseTimeStamp;
	static CMutex            m_mutex;

public: 
	static void              SetUseCallback(bool bUseCallback) { m_mutex.Lock(); m_bUseCallback = bUseCallback; m_mutex.Unlock(); }
	static bool              GetUseCallback() { m_mutex.Lock(); bool bUseCallback = m_bUseCallback; m_mutex.Unlock(); return bUseCallback; }
	static void              SetCallback(LogFileCallback_t pfnCallback) { m_mutex.Lock(); m_pfnCallback = pfnCallback; m_mutex.Unlock(); }
	static LogFileCallback_t GetCallback() { m_mutex.Lock(); LogFileCallback_t pfnLogFileCallback = m_pfnCallback; m_mutex.Unlock(); return pfnLogFileCallback; }
	static void				 SetUseTimeStamp(bool bTimeStamp) { m_mutex.Lock(); m_bUseTimeStamp = bTimeStamp; m_mutex.Unlock(); }
	static bool              GetUseTimeStamp() { m_mutex.Lock(); bool bTimeStamp = m_bUseTimeStamp; m_mutex.Unlock(); return bTimeStamp; }
	static void              Open(CString strLogFile, bool bAppend = false);
	static void              Print(const char * szString);
	static void              Printf(const char * szFormat, ...);
	static void              PrintDebugf(const char * szFormat, ...);
	static void              PrintToFile(const char * szString);
	static void              PrintfToFile(const char * szFormat, ...);
	static void              Close();
};

#endif // CLogFile_h