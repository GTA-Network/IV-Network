//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CException.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CException.h"
#include <Common.h>
#include <Windows.h>
#include <windowsx.h>
#include <CCore.h>
#include <Game/COffsets.h>

#include <dbghelp.h>
#include <tlhelp32.h>
#pragma comment(lib, "dbghelp.lib")
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 
#endif

extern CCore * g_pCore;
extern HMODULE g_hModule;

PCONTEXT pContextRecord;
#define IDD_DIALOG1                     101
#define IDC_EDIT1                       1000
#define IDC_BUTTON1                     1001
#define IDC_BUTTON2                     1002

CHAR szErrorString[163840];

void DumpMemory(BYTE *pData, DWORD dwCount, PCHAR sz, BOOL bAsDWords = FALSE)
{
	char s[16384];

	if (bAsDWords)
	{
		for(int i=0; i<(int)dwCount; i += 16)
		{
			sprintf(s, "+%04X: 0x%08X   0x%08X   0x%08X   0x%08X\r\n", i,
					*(DWORD*)(pData+i+0), *(DWORD*)(pData+i+4),
					*(DWORD*)(pData+i+8), *(DWORD*)(pData+i+12)
				);
			strcat(sz,s);
		}
	}
	else
	{
		for(int i=0; i<(int)dwCount; i += 16)
		{
			sprintf(s, "+%04X: %02X %02X %02X %02X   %02X %02X %02X %02X   "
					"%02X %02X %02X %02X   %02X %02X %02X %02X\r\n", i,
					pData[i+0], pData[i+1], pData[i+2], pData[i+3],
					pData[i+4], pData[i+5], pData[i+6], pData[i+7],
					pData[i+8], pData[i+9], pData[i+10], pData[i+11],
					pData[i+12], pData[i+13], pData[i+14], pData[i+15]
				);
			strcat(sz,s);
		}
	}
}

void DumpLoadedModules(PCHAR sz)
{
    HANDLE        hModuleSnap = NULL; 
	MODULEENTRY32 me32;
	char s[16384];
	
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId()); 
	
	strcpy(sz, "\r\nLoaded Modules:\r\n");

	if(hModuleSnap == INVALID_HANDLE_VALUE) 
	{
		strcat(sz, "-FailedCreate-\r\n");
		return;
	}

	me32.dwSize = sizeof( MODULEENTRY32 );

	if( !Module32First( hModuleSnap, &me32 ) )
	{
		strcat(sz, "-FailedFirst-" );  // Show cause of failure
		CloseHandle( hModuleSnap );     // Must clean up the snapshot object!
		return;
	}

	do
	{
		if (me32.szModule[0] != 'f' && me32.szModule[1] != 'l' && me32.szModule[2] != 'a')
		{
			sprintf(s, "%s\tB: 0x%08X\tS: 0x%08X\t(%s)\r\n",
				me32.szModule, me32.modBaseAddr, me32.modBaseSize, me32.szExePath);
			strcat(sz, s);
		}
	} while( Module32Next( hModuleSnap, &me32 ) );

	CloseHandle( hModuleSnap );
	
	return;

}


void DumpMain(BOOL bIncModules)
{
	CHAR s[16384];
	DWORD *pdwStack;
	int x=0;

	sprintf(szErrorString,
		"Exception At Address: 0x%08X (0x%p)\r\n\r\n"
		"Registers:\r\n"
		"EAX: 0x%08X\tEBX: 0x%08X\tECX: 0x%08X\tEDX: 0x%08X\r\n"
		"ESI: 0x%08X\tEDI: 0x%08X\tEBP: 0x%08X\tESP: 0x%08X\r\n"
		"EFLAGS: 0x%08X\r\n\r\n\r\nStack:\r\n",
		pContextRecord->Eip,
		pContextRecord->Eip - g_pCore->GetBase(),
		pContextRecord->Eax,
		pContextRecord->Ebx,
		pContextRecord->Ecx,
		pContextRecord->Edx,
		pContextRecord->Esi,
		pContextRecord->Edi,
		pContextRecord->Ebp,
		pContextRecord->Esp,
		pContextRecord->EFlags);

	pdwStack = (DWORD *)pContextRecord->Esp;
	DumpMemory(reinterpret_cast<BYTE*>(pdwStack), 320, szErrorString, TRUE);

	sprintf(s, "\r\nGame Version: %d\r\n", COffsets::GetVersion());
	strcat(szErrorString,s);

	if (bIncModules) {
		DumpLoadedModules(s);
		strcat(szErrorString,s);
	}

}

void ReportCrash()
{
	// TODO
}

BOOL CALLBACK ExceptionProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SetCursor(0);
	ShowCursor(TRUE);
	switch(uMsg)
	{
		case WM_MOUSEMOVE:
		{
			ShowCursor(TRUE);
			break;
		}
		case WM_INITDIALOG:		
		{
			DumpMain(FALSE);
			SetDlgItemText(hDlg,IDC_EDIT1,szErrorString);

			/* Now we are going to write a minidump and the dumped info to a file/dir */
			//WirteCrashInfo(stErrorString); 

			SetForegroundWindow(GetDlgItem(hDlg,IDD_DIALOG1));
			SetFocus(GetDlgItem(hDlg,IDC_BUTTON1));
			break;
		
		}
		case WM_DESTROY:
		{
			EndDialog(hDlg,TRUE);
			TerminateProcess(GetCurrentProcess(), 0);
			break;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDC_BUTTON1:
				{
					EndDialog(hDlg,TRUE);
					TerminateProcess(GetCurrentProcess(), 0);
					//ExitProcess(1);
					break;
				}
				case IDC_BUTTON2:
				{
					ReportCrash();
					EnableWindow(GetDlgItem(hDlg,IDC_BUTTON2),FALSE);
					SetDlgItemText(hDlg,IDC_EDIT1,"Thanks for reporting this problem.");
					break;
				}
			}
		}
		break;
	}
	return FALSE;
}



LONG WINAPI apiExceptionHandler(_EXCEPTION_POINTERS * apiExceptionInf)
{
	pContextRecord = apiExceptionInf->ContextRecord;

	ShowWindow(*(HWND*) (g_pCore->GetBase() + 0x16A9A54), SW_MINIMIZE);
	HINSTANCE hInst = (HINSTANCE)g_hModule;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, ExceptionProc);

#ifdef _DEBUG
	return EXCEPTION_CONTINUE_SEARCH;
#else
	return EXCEPTION_EXECUTE_HANDLER;
#endif
}

void InstallException()
{
	// Set the Exception handler
	SetUnhandledExceptionFilter(apiExceptionHandler);
}