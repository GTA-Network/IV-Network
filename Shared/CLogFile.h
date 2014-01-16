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