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
