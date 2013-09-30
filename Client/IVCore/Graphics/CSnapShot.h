//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CSnapShot.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

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