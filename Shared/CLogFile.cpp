//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CLogFile.cpp
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CLogFile.h"
#include "SharedUtility.h"

#ifdef _LINUX
#define stricmp strcasecmp
#define vsprintf_s vsprintf
#define vsnprintf_s vsnprintf
#define sprintf_s sprintf
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#endif

FILE *            CLogFile::m_fLogFile = NULL;
bool              CLogFile::m_bUseCallback = false;
LogFileCallback_t CLogFile::m_pfnCallback = NULL;
bool              CLogFile::m_bUseTimeStamp = true;
CMutex            CLogFile::m_mutex;

void CLogFile::Open(CString strLogFile, bool bAppend)
{
	// Lock the mutex
	m_mutex.TryLock(1);

	// Open the log file
	m_fLogFile = fopen(SharedUtility::GetAbsolutePath(strLogFile).Get(), bAppend ? "a" : "w");

	// Did the log file open successfully?
	if(m_fLogFile)
	{
		// Log the log file started message
		//PrintToFile("Log file started");
	}

	// Unlock the mutex
	m_mutex.Unlock();
}

void CLogFile::Print(const char * szString)
{
	// Lock the mutex
	m_mutex.TryLock(1);

	// Print the message
	printf("%s\n", szString);

	// Flush the output buffer
	fflush(stdout);

	// Print the message to the log file
	PrintToFile(szString);

	// Unlock the mutex
	m_mutex.Unlock();
}

void CLogFile::Printf(const char * szFormat, ...)
{
	// Lock the mutex
	m_mutex.TryLock(1);

	// Collect the arguments
	va_list vaArgs;
	char szBuffer[2048];
	va_start(vaArgs, szFormat);
	vsnprintf_s(szBuffer, sizeof(szBuffer), szFormat, vaArgs);
	va_end(vaArgs);

	// Print the message
	Print(szBuffer);

	// Unlock the mutex
	m_mutex.Unlock();
}

void CLogFile::PrintDebugf(const char * szFormat, ...)
{
#ifdef IVN_DEBUG
	// Lock the mutex
	m_mutex.TryLock(1);

	// Collect the arguments
	va_list vaArgs;
	char szBuffer[2048];
	va_start(vaArgs, szFormat);
	vsnprintf_s(szBuffer, sizeof(szBuffer), szFormat, vaArgs);
	va_end(vaArgs);

	// Print the message
	Print(szBuffer);

	// Unlock the mutex
	m_mutex.Unlock();
#endif
}

void CLogFile::PrintToFile(const char * szString)
{
	// Lock the mutex
	m_mutex.TryLock(1);

	// If we have a callback and it is enabled call it
	if(m_bUseCallback && m_pfnCallback)
		m_pfnCallback(szString);

	// Is the log file open?
	if(m_fLogFile)
	{
		// Log the message
		if(m_bUseTimeStamp)
			fprintf(m_fLogFile, "%s\n", szString);
		else
			fprintf(m_fLogFile, "%s\n", szString);

		// Flush the log file buffer
		fflush(m_fLogFile);
	}

	// Unlock the mutex
	m_mutex.Unlock();
}

void CLogFile::PrintfToFile(const char * szFormat, ...)
{
	// Lock the mutex
	m_mutex.TryLock(1);

	// Collect the arguments
	va_list vaArgs;
	char szBuffer[2048];
	va_start(vaArgs, szFormat);
	vsnprintf_s(szBuffer, sizeof(szBuffer), szFormat, vaArgs);
	va_end(vaArgs);

	// Print the message to the log file
	PrintToFile(szBuffer);

	// Unlock the mutex
	m_mutex.Unlock();
}

void CLogFile::Close()
{
	// Lock the mutex
	m_mutex.TryLock(1);

	// Is the log file open?
	if(m_fLogFile)
	{
		// Log the log file finished message
		//PrintToFile("Log file finished");

		// Close the log file
		fclose(m_fLogFile);
		m_fLogFile = NULL;
	}

	// Unlock the mutex
	m_mutex.Unlock();
}
