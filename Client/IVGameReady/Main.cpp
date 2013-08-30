//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: Main.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include "resource.h"
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <commctrl.h>
#include <CRC.h>

#pragma warning(disable:4244)
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable = NULL;

	// Initialize global strings
	memcpy(szTitle, "IVMP EFLC File Copy", sizeof("IVMP EFLC File Copy"));
	memcpy(szWindowClass, "IVMPFileCopyClass", sizeof("IVMPFileCopyClass"));

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU,
	   CW_USEDEFAULT, 0, 400, 100, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
const char * szCopyFile[] = {
	{ "multiplayer\\pc\\textures\\loadingscreens.wtd" },
	{ "multiplayer\\common\\data\\loadingscreens_pc_eflc_v2.dat" },
	{ "multiplayer\\pc\\textures\\radio_hud_noncolored.wtd" }
};


const char * szCopyFileDest[] = {
	{ "%s%sloadingscreens.wtd" },
	{ "%s%sloadingscreens_pc_eflc_v2.dat" },
	{ "%s%sradio_hud_noncolored.wtd" },
};

HWND hwnd; 
DWORD transferred;
DWORD comFileSize = 0;
HWND pgCurrentFile = NULL;
HWND pgAllProgress = NULL;
void CurrentFileProgress(
    _In_     LARGE_INTEGER TotalFileSize,
    _In_     LARGE_INTEGER TotalBytesTransferred,
    _In_     LARGE_INTEGER StreamSize,
    _In_     LARGE_INTEGER StreamBytesTransferred,
    _In_     DWORD dwStreamNumber,
    _In_     DWORD dwCallbackReason,
    _In_     HANDLE hSourceFile,
    _In_     HANDLE hDestinationFile,
    _In_opt_ LPVOID lpData)
{
	SendMessage(pgCurrentFile, PBM_SETRANGE, 0, MAKELPARAM(0, 10000)); 
	float progress = ((float)TotalBytesTransferred.QuadPart/(float)TotalFileSize.QuadPart)* 10000;
	SendMessage(pgCurrentFile, PBM_SETPOS, progress, 0);
	if(TotalBytesTransferred.QuadPart == TotalFileSize.QuadPart)
	{
		transferred += (TotalFileSize.QuadPart/1024);
		float progress2 = (transferred/comFileSize)*10000;
		SendMessage(pgAllProgress, PBM_SETRANGE, 0, MAKELPARAM(0, 10000)); 
		SendMessage(pgAllProgress, PBM_SETPOS, progress2, 0);
	}
}

#include <SharedUtility.h>
CString szCopyText;
CString szCopyText2;
void CopyThread()
{
	char szEFLCDirectory[MAX_PATH];
	char szInstallDirectory[MAX_PATH];
	if(SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, REGISTRY_AREA, GAME_DIRECTORY, NULL, szInstallDirectory, sizeof(szInstallDirectory)) && SharedUtility::Exists(szInstallDirectory)) {

		if(SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, REGISTRY_AREA, GAME_DIRECTORY, NULL, szInstallDirectory, sizeof(szInstallDirectory)) && SharedUtility::Exists(szInstallDirectory)) {
			for(int n = 0; n < sizeof(szCopyFile) / sizeof(szCopyFile[0]); n++) {
				DWORD fileSize;
				FILE* pFile = fopen(CString(szCopyFile[n], szEFLCDirectory).Get(), "rb");
				GetFileSize(pFile, &fileSize);
				comFileSize += (fileSize/1024);
			}

			for(int n = 0; n < sizeof(szCopyFile) / sizeof(szCopyFile[0]); n++)
			{
				std::string source = szCopyFile[n];
				szCopyText = source.substr(source.find_last_of("\\")+1).c_str();
				szCopyText2 = CString("%i/%i", n, sizeof(szCopyFile) / sizeof(szCopyFile[0]));
				InvalidateRect(hwnd, 0, true);    

				if(CString(szCopyFile[n]).Find("ultiplayer\\common\\data\\") != std::string::npos && szCopyFile[n][0] != '%') {
					CString file(SharedUtility::GetAppPath());
					file.AppendF(szCopyFile[n]);
					if(SharedUtility::Exists(CString(szCopyFileDest[n], szInstallDirectory, "\\TBoGT\\common\\data\\").Get()))
						SetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\TBoGT\\common\\data\\").Get(), GetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\").Get()) & ~FILE_ATTRIBUTE_READONLY);
					CopyFileEx(file.Get(), CString(szCopyFileDest[n], szInstallDirectory, "\\TBoGT\\common\\data\\").Get(), (LPPROGRESS_ROUTINE)CurrentFileProgress, NULL, false, 0);
				}
				else if(CString(szCopyFile[n]).Find("ultiplayer\\pc\\textures\\") != std::string::npos && szCopyFile[n][0] != '%') {
					CString file(SharedUtility::GetAppPath());
					file.AppendF(szCopyFile[n]);
					if(SharedUtility::Exists(CString(szCopyFileDest[n], szInstallDirectory, "\\TBoGT\\pc\\textures\\").Get()))
						SetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\TBoGT\\pc\\textures\\").Get(), GetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\textures\\").Get()) & ~FILE_ATTRIBUTE_READONLY);
					CopyFileEx(file.Get(), CString(szCopyFileDest[n], szInstallDirectory, "\\TBoGT\\pc\\textures\\").Get(), (LPPROGRESS_ROUTINE)CurrentFileProgress, NULL, false, 0);
				} 
				else {
					if(SharedUtility::Exists(CString(szCopyFileDest[n], szInstallDirectory).Get()))
						SetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory).Get(), GetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory).Get()) & ~FILE_ATTRIBUTE_READONLY);
					CopyFileEx(CString(szCopyFile[n], szEFLCDirectory).Get(), CString(szCopyFileDest[n], szInstallDirectory).Get(), (LPPROGRESS_ROUTINE)CurrentFileProgress, NULL, false, 0);
				}
			}
			szCopyText = "Complete";
			szCopyText2 = CString("%i/%i", sizeof(szCopyFile) / sizeof(szCopyFile[0]), sizeof(szCopyFile) / sizeof(szCopyFile[0]));
			InvalidateRect(hwnd, 0, true);
			TerminateProcess(GetCurrentProcess(),0);
		}
	}
}

int ShowMessageBox(const char * szText, UINT uType = (MB_ICONEXCLAMATION | MB_OK))
{
	return MessageBox(NULL, szText, MOD_NAME, uType);
}

HFONT font;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		{
			hwnd = hWnd;
			pgCurrentFile = CreateWindowEx(0, PROGRESS_CLASS, NULL,
				WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
				20, 40, 345, 17,
				hWnd, NULL, hInst, NULL);
			
			font = CreateFont(18, 0, 0, 0, 300, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
			SendMessage(pgCurrentFile, PBM_SETRANGE, 0, MAKELPARAM(0, 220));
			HANDLE hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CopyThread, NULL, NULL, NULL);
			WaitForSingleObject(hThread, INFINITE);
			TerminateProcess(GetCurrentProcess(),0);

		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case -1:
			;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		HFONT hFontOld = (HFONT)SelectObject( hdc, font );
		RECT rect = { 20, 5, 1000, 1000 };
		DrawText(hdc, (LPCSTR)szCopyText.Get(), szCopyText.GetLength(), &rect, 0);
		RECT rect2= { 320, 5, 1000, 1000 };
		
		DrawText(hdc, (LPCSTR)szCopyText2.Get(), szCopyText2.GetLength(), &rect2, 0);
		SelectObject( hdc, hFontOld );
		EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
