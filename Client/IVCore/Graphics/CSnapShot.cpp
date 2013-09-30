//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CSnapShot.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSnapShot.h"
#include <lpng142/png.h>
#include <DXSDK/Include/d3d9.h>
#include <SharedUtility.h>

#include <CCore.h>
extern CCore * g_pCore;

#define SCREEN_SHOT_FORMAT D3DFMT_A8R8G8B8
#define SCREEN_SHOT_FORMAT_BYTES_PER_PIXEL (32 / 8)

unsigned long           CSnapShot::m_ulLastScreenShotTime = 0;
CThread                 CSnapShot::m_writeThread;
unsigned char         * CSnapShot::m_ucData = NULL;
unsigned int            CSnapShot::m_uiScreenWidth = 0;
unsigned int            CSnapShot::m_uiScreenHeight = 0;
CSnapShot::ThreadData	CSnapShot::m_threadData;

CSnapShot::CSnapShot()
{
	Reset();
}

CString CSnapShot::GetScreenShotPath()
{
	// Get the screen shot directory
	CString strPath(SharedUtility::GetAbsolutePath("multiplayer\\snapshots"));

	// Ensure the screen shot directory exists
	if(!SharedUtility::Exists(strPath))
		SharedUtility::CreateDirectory(strPath);

	// Append the screen shot name to the path
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	strPath.AppendF("/ivn-%04d.%02d.%02d-%02d.%02d.%02d.png", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	return strPath;
}

int GetBitsPerPixel ( D3DFORMAT Format )
{
	switch ( Format )
	{
	    case D3DFMT_A8R8G8B8:
	    case D3DFMT_X8R8G8B8:
	    case D3DFMT_Q8W8V8U8:
	    case D3DFMT_X8L8V8U8:
	    case D3DFMT_A2B10G10R10:
	    case D3DFMT_V16U16:
	    case D3DFMT_G16R16:
	    case D3DFMT_D24X4S4:
	    case D3DFMT_D32:
	    case D3DFMT_D24X8:
	    case D3DFMT_D24S8:
		    return 32;

	    case D3DFMT_R8G8B8:
		    return 24;

	    case D3DFMT_X1R5G5B5:
	    case D3DFMT_R5G6B5:
	    case D3DFMT_A1R5G5B5:
	    case D3DFMT_D16:
	    case D3DFMT_A8L8:
	    case D3DFMT_V8U8:
	    case D3DFMT_L6V5U5:
	    case D3DFMT_D16_LOCKABLE:
	    case D3DFMT_D15S1:
	    case D3DFMT_A8P8:
	    case D3DFMT_A8R3G3B2:	
	    case D3DFMT_X4R4G4B4:
	    case D3DFMT_A4R4G4B4:
		    return 16;

	    case D3DFMT_R3G3B2:
	    case D3DFMT_A4L4:
	    case D3DFMT_P8:	
	    case D3DFMT_A8:
	    case D3DFMT_L8:	
	    case D3DFMT_DXT2:
	    case D3DFMT_DXT3:
	    case D3DFMT_DXT4:
	    case D3DFMT_DXT5:
		    return 8;

	    case D3DFMT_DXT1:
		    return 4;

	    default:
		    return 32;  // unknown - guess at 32
	}
}

void CSnapShot::GetFrontBufferPixels(UINT uiSizeX, UINT uiSizeY,unsigned char* buffer)
{
	// Get our d3d device
	IDirect3DDevice9 * pDevice = g_pCore->GetGraphics()->GetDevice();

	// Get our display mode
	D3DDISPLAYMODE displayMode;
	pDevice->GetDisplayMode(0, &displayMode);

	// Create our surface
	IDirect3DSurface9 * pSurface = NULL;
	pDevice->CreateOffscreenPlainSurface(displayMode.Width, displayMode.Height, SCREEN_SHOT_FORMAT, D3DPOOL_SCRATCH, &pSurface, NULL);

	if(pSurface)
	{
		pDevice->GetFrontBufferData(0, pSurface);

		// Create the client rect
		RECT clientRect;
		{
			POINT clientPoint;
			clientPoint.x = 0;
			clientPoint.y = 0;
			ClientToScreen(*(HWND *)COffsets::VAR_HWnd, &clientPoint);
			clientRect.left   = clientPoint.x;
			clientRect.top	  = clientPoint.y;
			clientRect.right  = (clientRect.left + displayMode.Width);
			clientRect.bottom = (clientRect.top  + displayMode.Height);
		}

		D3DLOCKED_RECT lockedRect;
		HRESULT hr = pSurface->LockRect(&lockedRect, NULL, D3DLOCK_READONLY | D3DLOCK_NOSYSLOCK | D3DLOCK_DONOTWAIT);
	
		if(SUCCEEDED(hr))
		{
			void* pBits = lockedRect.pBits;
			UINT ms_ulPitch = lockedRect.Pitch;

			for(unsigned int i = 0; i < displayMode.Height; ++i)
				memcpy(buffer + (displayMode.Width * 4) * i, (BYTE*)pBits + i * ms_ulPitch, (displayMode.Width * 4));
		}

		pSurface->UnlockRect();
		pSurface->Release();
	}
}

void CSnapShot::WriteImageToFile(CThread * pThread)
{
	m_threadData.bWriting = true;

	D3DDISPLAYMODE displayMode;
	g_pCore->GetGraphics()->GetDevice()->GetDisplayMode(0, &displayMode);

	UINT uiScreenWidth = displayMode.Width;
	UINT uiScreenHeight = displayMode.Height;
	BYTE* mem = new BYTE[SCREEN_SHOT_FORMAT_BYTES_PER_PIXEL * uiScreenWidth * uiScreenWidth];

	GetFrontBufferPixels(uiScreenWidth, uiScreenHeight, mem);

	BYTE** ScreenData = NULL;
	ScreenData = new BYTE* [uiScreenHeight];
	for (unsigned short y = 0; y < uiScreenHeight; y++) {
		ScreenData[y] = new BYTE[uiScreenWidth * SCREEN_SHOT_FORMAT_BYTES_PER_PIXEL];
	}

	UINT uiLinePitch = uiScreenWidth * SCREEN_SHOT_FORMAT_BYTES_PER_PIXEL;
	unsigned long ulLineWidth = uiScreenWidth * SCREEN_SHOT_FORMAT_BYTES_PER_PIXEL;
	for (unsigned int i = 0; i < uiScreenHeight; i++) {
		memcpy(ScreenData[i], (BYTE*) mem + i* uiLinePitch, ulLineWidth);
		for(unsigned int j = 3; j < ulLineWidth; j += SCREEN_SHOT_FORMAT_BYTES_PER_PIXEL) {
			ScreenData[i][j] = 0xFF;
		}
	}

	CString strPath = GetScreenShotPath();
	FILE *file = fopen(strPath, "wb");
	png_struct* png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_info* info_ptr = png_create_info_struct(png_ptr);
	png_init_io(png_ptr, file);
	png_set_filter(png_ptr, 0, PNG_FILTER_NONE);
	png_set_compression_level(png_ptr, 9);
	png_set_IHDR(png_ptr, info_ptr, uiScreenWidth, uiScreenHeight, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_set_rows(png_ptr, info_ptr, ScreenData);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_BGR | PNG_TRANSFORM_STRIP_ALPHA, NULL);
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(file);

	for (unsigned short y = 0; y < uiScreenHeight; y++) {
		delete []ScreenData[y];
	}

	delete []ScreenData;
	delete []mem;
	m_threadData.bWriting = false;
}

bool CSnapShot::Take()
{
	// Ensure we are not already taking a screen shot
	if(m_writeThread.IsRunning() || m_threadData.bWriting == true)
	{
		// Flag the write as not succeeded
		m_threadData.strError = "Screen shot already being taken.";
		return false;
	}

	// Only allow one screen shot per second to avoid abuse
	if((SharedUtility::GetTime() - m_ulLastScreenShotTime) < 1000)
	{
		// Flag the write as not succeeded
		m_threadData.strError = "You must wait 1 second between screen shots.";
		return false;
	}

	m_writeThread.Start(WriteImageToFile);

	// Set the last screen shot time
	m_ulLastScreenShotTime = SharedUtility::GetTime();

	return true;
}

bool CSnapShot::IsDone()
{
	bool bWriting = m_threadData.bWriting;

	return (bWriting && !m_writeThread.IsRunning());
}

bool CSnapShot::HasSucceeded()
{
	return m_threadData.bSucceeded;
}

CString CSnapShot::GetWriteName()
{
	return m_threadData.strWriteName;
}

CString CSnapShot::GetError()
{
	return m_threadData.strError;
}

void CSnapShot::Reset()
{
	// Reset the thread data
	m_threadData.bWriting = false;
	m_threadData.bSucceeded = false;
	m_threadData.strError = "";
}
