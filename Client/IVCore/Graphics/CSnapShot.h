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

#ifndef CSnapShot_h
#define CSnapShot_h

#include <Common.h>
#include <DXSDK/Include/d3d9.h>
#include <Threading/CMutex.h>
#include <Threading/CThread.h>

class CSnapShot {
public:
	struct ThreadData
	{
		bool   bWriting;
		bool   bSucceeded;
		CString strWriteName;
		CString strError;
	};

private:
	static unsigned long		m_ulLastScreenShotTime;
	static CThread				m_writeThread;
	static unsigned char *		m_ucData;
	static unsigned int			m_uiScreenWidth;
	static unsigned int			m_uiScreenHeight;
	static ThreadData			m_threadData;

	static CString				GetScreenShotPath();
	static void					GetFrontBufferPixels(UINT uiSizeX, UINT uiSizeY,unsigned char* buffer);
	static void					WriteImageToFile(CThread * pThread);

public:
								CSnapShot();
								~CSnapShot();

	static bool					Take();
	static bool					IsDone();
	static bool					HasSucceeded();
	
	static CString				GetWriteName();
	static CString				GetError();
	static void					Reset();
};

#endif // CSnapShot_h