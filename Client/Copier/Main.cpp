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
	{ "%s\\TBoGT\\pc\\models\\cdimages\\vehicles.img" },
	{ "%s\\TLAD\\pc\\models\\cdimages\\vehicles.img" },
	{ "%s\\TBoGT\\pc\\models\\cdimages\\pedprops.img" },
	{ "%s\\TLAD\\pc\\models\\cdimages\\pedprops.img" },
	{ "%s\\TBoGT\\pc\\models\\cdimages\\weapons_e2.img" },
	{ "%s\\TLAD\\pc\\models\\cdimages\\weapons_e1.img" },

	{ "%s\\TBoGT\\common\\data\\default.ide" },
	{ "%s\\TBoGT\\common\\data\\WeaponInfo.xml" },

	{ "%s\\TLAD\\common\\data\\default.ide" },
	{ "%s\\TLAD\\common\\data\\WeaponInfo.xml" },

	{ "%s\\TBoGT\\pc\\anim\\anim.img" },
	{ "%s\\TBoGT\\pc\\models\\cdimages\\componentpeds.img" },

	{ "%s\\TLAD\\pc\\anim\\anim.img" },
	{ "%s\\TLAD\\pc\\models\\cdimages\\componentpeds.img" },

	{ "%s\\TBoGT\\common\\data\\peds.ide" },
	{ "%s\\TBoGT\\common\\data\\pedVariations.dat" },

	{ "%s\\TLAD\\common\\data\\peds.ide" },
	{ "%s\\TLAD\\common\\data\\pedVariations.dat" },

	{ "%s\\TBOGT\\pc\\data\\maps\\props\\e2_xref.img" },

	// copy to gtaiv/pc/data/eflc
	{ "multiplayer\\pc\\data\\eflc\\animgrp_eflc.dat" },
	{ "multiplayer\\pc\\data\\eflc\\default_eflc.ide" },
	{ "multiplayer\\pc\\data\\eflc\\e2_xref.ide" },
	{ "multiplayer\\common\\data\\effects\\explosionFx.dat" },
	{ "multiplayer\\pc\\data\\eflc\\loadingscreens_eflc.dat" },
	{ "multiplayer\\pc\\data\\eflc\\peds_eflc.wtd" },
	{ "multiplayer\\pc\\data\\eflc\\playerped_eflc.rpf" },

	// copy to gtaiv/common/data
	{ "multiplayer\\common\\data\\default.ide" },
	{ "multiplayer\\common\\data\\default_eflc.ide" },
	{ "multiplayer\\common\\data\\hudColor.dat" },
	{ "multiplayer\\common\\data\\loadingscreens_eflc.dat" },
	{ "multiplayer\\common\\data\\loadingscreens_eflc_pc.dat" },
	{ "multiplayer\\common\\data\\radiohud.dat" },
	{ "multiplayer\\common\\data\\RadioLogo.dat" },
	{ "multiplayer\\common\\data\\vehOff.csv" },
	{ "multiplayer\\common\\data\\WeaponInfo.xml" },
	{ "multiplayer\\common\\data\\WeaponInfo_EFLC.xml" },
	{ "multiplayer\\common\\data\\WeaponInfo_EFLC_C.xml" },
	
	{ "multiplayer\\pc\\textures\\radio_hud_noncolored.wtd" },
	{ "multiplayer\\pc\\textures\\loadingscreens_eflc.wtd" },

#if 0 // Not needed atm
	{ "%s/TBoGT/pc/data/maps/interiors/rep_public_3.img" },

	{ "%s/TBoGT/pc/data/maps/interiors/Int_1.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_2.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_3.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_4.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_5.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_6.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_7.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_8.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/Int_9.img" },

	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_1.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_2.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_3.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_4.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_5.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_6.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_7.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_8.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_9.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_10.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_11.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_12.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_13.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_14.img" },
	{ "%s/TBoGT/pc/data/maps/interiors/E2_Int_15.img" },


	{ "%s/TBoGT/pc/data/maps/jersey/nj_01.img" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_02.img" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_03.img" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_04w.img" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_05.img" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_docks.img" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_liberty.img" },

	{ "%s/TBoGT/pc/data/maps/manhat/manhat01.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat02.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat03.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat04.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat05.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat06.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat07.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat08.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat09.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat10.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat11.img" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat12.img" },

	{ "%s/TBoGT/pc/data/maps/east/queens_m.img" },
	{ "%s/TBoGT/pc/data/maps/east/queens_e.img" },
	{ "%s/TBoGT/pc/data/maps/east/queens_w2.img" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_e.img" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_e2.img" },
	{ "%s/TBoGT/pc/data/maps/east/brook_n.img" },
	{ "%s/TBoGT/pc/data/maps/east/brook_n2.img" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_w.img" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_w2.img" },
	{ "%s/TBoGT/pc/data/maps/east/brook_s.img" },
	{ "%s/TBoGT/pc/data/maps/east/brook_s2.img" },

	{ "%s/TBoGT/pc/data/maps/jersey/nj_01.ide" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_02.ide" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_03.ide" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_04w.ide" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_05.ide" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_docks.ide" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_liberty.ide" },

	{ "%s/TBoGT/pc/data/maps/manhat/manhat01.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat02.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat03.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat04.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat05.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat06.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat07.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat08.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat09.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat10.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat11.ide" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat12.ide" },

	{ "%s/TBoGT/pc/data/maps/east/queens_m.ide" },
	{ "%s/TBoGT/pc/data/maps/east/queens_e.ide" },
	{ "%s/TBoGT/pc/data/maps/east/queens_w2.ide" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_e.ide" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_e2.ide" },
	{ "%s/TBoGT/pc/data/maps/east/brook_n.ide" },
	{ "%s/TBoGT/pc/data/maps/east/brook_n2.ide" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_w.ide" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_w2.ide" },
	{ "%s/TBoGT/pc/data/maps/east/brook_s.ide" },
	{ "%s/TBoGT/pc/data/maps/east/brook_s2.ide" },

	{ "%s/TBoGT/pc/data/maps/jersey/nj_01.wpl" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_02.wpl" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_03.wpl" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_04w.wpl" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_05.wpl" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_docks.wpl" },
	{ "%s/TBoGT/pc/data/maps/jersey/nj_liberty.wpl" },

	{ "%s/TBoGT/pc/data/maps/manhat/manhat01.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat02.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat03.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat04.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat05.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat06.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat07.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat08.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat09.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat10.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat11.wpl" },
	{ "%s/TBoGT/pc/data/maps/manhat/manhat12.wpl" },

	{ "%s/TBoGT/pc/data/maps/east/queens_m.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/queens_e.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/queens_w2.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_e.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_e2.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/brook_n.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/brook_n2.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_w.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/bronx_w2.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/brook_s.wpl" },
	{ "%s/TBoGT/pc/data/maps/east/brook_s2.wpl" },


	{ "%s/TBoGT/pc/data/maps/props/e2_xref.ide" },
	{ "%s/TBoGT/pc/data/maps/props/e2_xref.img" },

	{ "%s/TBoGT/common/data/maps/scenario2.IPL" },
	{ "%s/TBoGT/common/data/maps/scenarios.ipl" },
#endif
};


const char * szCopyFileDest[] = {
	{ "%s\\pc\\models\\cdimages\\vehicles_tbogt.img" },
	{ "%s\\pc\\models\\cdimages\\vehicles_tlad.img" },
	{ "%s\\pc\\models\\cdimages\\pedprops_tbogt.img" },
	{ "%s\\pc\\models\\cdimages\\pedprops_tlad.img" },
	{ "%s\\pc\\models\\cdimages\\weapons_tbogt.img" },
	{ "%s\\pc\\models\\cdimages\\weapons_tlad.img" },

	{ "%s\\common\\data\\default_tbogt.ide" },
	{ "%s\\pc\\data\\eflc\\WeaponInfo_tbogt.xml" },

	{ "%s\\pc\\data\\eflc\\WeaponInfo_tlad.xml" },
	{ "%s\\pc\\data\\eflc\\default_tlad.ide" },

	{ "%s\\pc\\data\\eflc\\anim_eflc.img" },
	{ "%s\\pc\\data\\eflc\\componentpeds_tbogt.img" },

	{ "%s\\pc\\data\\eflc\\anim_eflc_2.img" },
	{ "%s\\pc\\data\\eflc\\componentpeds_tlad.img" },

	{ "%s\\pc\\data\\eflc\\peds_tbogt.ide" },
	{ "%s\\pc\\data\\eflc\\pedVariations_tbogt.dat" },

	{ "%s\\pc\\data\\eflc\\peds_tlad.ide" },
	{ "%s\\pc\\data\\eflc\\pedVariations_tlad.dat" },

	{ "%s\\pc\\data\\eflc\\e2_xref.img" },

	// copy to gtaiv/pc/data/eflc
	{  "%s%sanimgrp_eflc.dat" },
	{  "%s%sdefault_eflc.ide" },
	{  "%s%se2_xref.ide" },
	{  "%s%sexplosionFx.dat" },
	{  "%s%sloadingscreens_eflc.dat" },
	{  "%s%speds_eflc.wtd" },
	{  "%s%splayerped_eflc.rpf" },

	// copy to gtaiv/common/data
	{ "%s%sdefault.ide" },
	{ "%s%sdefault_eflc.ide" },
	{ "%s%shudColor.dat" },
	{ "%s%sloadingscreens_eflc.dat" },
	{ "%s%sloadingscreens_eflc_pc.dat" },
	{ "%s%sradiohud.dat" },
	{ "%s%sRadioLogo.dat" },
	{ "%s%svehOff.csv" },
	{ "%s%sWeaponInfo.xml" },
	{ "%s%sWeaponInfo_EFLC.xml" },
	{ "%s%sWeaponInfo_EFLC_C.xml" },

	{ "%s%sradio_hud_noncolored.wtd" },
	{ "%s%sloadingscreens_eflc.wtd" },

#if 0 // Not needed atm
	{ "%s/pc/data/maps/rep_public_3.img" },

	{ "%s/pc/data/tbogt/maps/interiors/Int_1.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_2.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_3.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_4.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_5.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_6.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_7.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_8.img" },
	{ "%s/pc/data/tbogt/maps/interiors/Int_9.img" },

	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_1.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_2.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_3.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_4.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_5.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_6.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_7.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_8.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_9.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_10.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_11.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_12.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_13.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_14.img" },
	{ "%s/pc/data/tbogt/maps/interiors/E2_Int_15.img" },


	{ "%s/pc/data/tbogt/maps/jersey/nj_01.img" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_02.img" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_03.img" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_04w.img" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_05.img" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_docks.img" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_liberty.img" },

	{ "%s/pc/data/tbogt/maps/manhat/manhat01.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat02.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat03.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat04.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat05.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat06.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat07.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat08.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat09.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat10.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat11.img" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat12.img" },

	{ "%s/pc/data/tbogt/maps/east/queens_m.img" },
	{ "%s/pc/data/tbogt/maps/east/queens_e.img" },
	{ "%s/pc/data/tbogt/maps/east/queens_w2.img" },
	{ "%s/pc/data/tbogt/maps/east/bronx_e.img" },
	{ "%s/pc/data/tbogt/maps/east/bronx_e2.img" },
	{ "%s/pc/data/tbogt/maps/east/brook_n.img" },
	{ "%s/pc/data/tbogt/maps/east/brook_n2.img" },
	{ "%s/pc/data/tbogt/maps/east/bronx_w.img" },
	{ "%s/pc/data/tbogt/maps/east/bronx_w2.img" },
	{ "%s/pc/data/tbogt/maps/east/brook_s.img" },
	{ "%s/pc/data/tbogt/maps/east/brook_s2.img" },

	{ "%s/pc/data/tbogt/maps/jersey/nj_01.ide" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_02.ide" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_03.ide" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_04w.ide" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_05.ide" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_docks.ide" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_liberty.ide" },

	{ "%s/pc/data/tbogt/maps/manhat/manhat01.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat02.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat03.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat04.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat05.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat06.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat07.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat08.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat09.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat10.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat11.ide" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat12.ide" },

	{ "%s/pc/data/tbogt/maps/east/queens_m.ide" },
	{ "%s/pc/data/tbogt/maps/east/queens_e.ide" },
	{ "%s/pc/data/tbogt/maps/east/queens_w2.ide" },
	{ "%s/pc/data/tbogt/maps/east/bronx_e.ide" },
	{ "%s/pc/data/tbogt/maps/east/bronx_e2.ide" },
	{ "%s/pc/data/tbogt/maps/east/brook_n.ide" },
	{ "%s/pc/data/tbogt/maps/east/brook_n2.ide" },
	{ "%s/pc/data/tbogt/maps/east/bronx_w.ide" },
	{ "%s/pc/data/tbogt/maps/east/bronx_w2.ide" },
	{ "%s/pc/data/tbogt/maps/east/brook_s.ide" },
	{ "%s/pc/data/tbogt/maps/east/brook_s2.ide" },

	{ "%s/pc/data/tbogt/maps/jersey/nj_01.wpl" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_02.wpl" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_03.wpl" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_04w.wpl" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_05.wpl" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_docks.wpl" },
	{ "%s/pc/data/tbogt/maps/jersey/nj_liberty.wpl" },

	{ "%s/pc/data/tbogt/maps/manhat/manhat01.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat02.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat03.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat04.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat05.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat06.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat07.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat08.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat09.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat10.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat11.wpl" },
	{ "%s/pc/data/tbogt/maps/manhat/manhat12.wpl" },

	{ "%s/pc/data/tbogt/maps/east/queens_m.wpl" },
	{ "%s/pc/data/tbogt/maps/east/queens_e.wpl" },
	{ "%s/pc/data/tbogt/maps/east/queens_w2.wpl" },
	{ "%s/pc/data/tbogt/maps/east/bronx_e.wpl" },
	{ "%s/pc/data/tbogt/maps/east/bronx_e2.wpl" },
	{ "%s/pc/data/tbogt/maps/east/brook_n.wpl" },
	{ "%s/pc/data/tbogt/maps/east/brook_n2.wpl" },
	{ "%s/pc/data/tbogt/maps/east/bronx_w.wpl" },
	{ "%s/pc/data/tbogt/maps/east/bronx_w2.wpl" },
	{ "%s/pc/data/tbogt/maps/east/brook_s.wpl" },
	{ "%s/pc/data/tbogt/maps/east/brook_s2.wpl" },



	{ "%s/pc/data/tbogt/maps/props/e2_xref.ide" },
	{ "%s/pc/data/tbogt/maps/props/e2_xref.img" },

	{ "%s/pc/data/tbogt/maps/scenario2.IPL" },
	{ "%s/pc/data/tbogt/maps/scenarios.ipl" },
#endif
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
	char szUsingEFLC[3];
	if(SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "usingeflc", "1", szUsingEFLC, sizeof(szUsingEFLC)))
	{
		if(CString(szUsingEFLC) == "1")
		{
			char szEFLCDirectory[MAX_PATH];
			char szInstallDirectory[MAX_PATH];
			if(SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "eflcdir", NULL, szEFLCDirectory, sizeof(szEFLCDirectory)) 
				|| SharedUtility::Exists(szEFLCDirectory)) {

					if(SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "gtaivdir", NULL,
						szInstallDirectory, sizeof(szInstallDirectory)) &&
						SharedUtility::Exists(szInstallDirectory))
					{
						SharedUtility::CreateDirectoryA(CString("%s/eflc", szEFLCDirectory).Get());
						for(int n = 0; n < sizeof(szCopyFile) / sizeof(szCopyFile[0]); n++)
						{
							DWORD fileSize;
							FILE* pFile = fopen(CString(szCopyFile[n], szEFLCDirectory).Get(), "rb");
							GetFileSize(pFile, &fileSize);
							comFileSize += (fileSize/1024);
						}

						SharedUtility::CreateDirectoryA(CString("%s%s", szInstallDirectory, "\\pc\\data\\eflc\\").Get());

						for(int n = 0; n < sizeof(szCopyFile) / sizeof(szCopyFile[0]); n++)
						{
							std::string source = szCopyFile[n];
							szCopyText = source.substr(source.find_last_of("\\")+1).c_str();
							szCopyText2 = CString("%i/%i", n, sizeof(szCopyFile) / sizeof(szCopyFile[0]));
							InvalidateRect(hwnd, 0, true);    

							if(CString(szCopyFile[n]).Find("ultiplayer\\pc\\data\\eflc\\") != std::string::npos && szCopyFile[n][0] != '%') {
								CString file(SharedUtility::GetAppPath());
								file.AppendF(szCopyFile[n]);
								if(SharedUtility::Exists(CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\data\\eflc\\").Get()))
									SetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\data\\eflc\\").Get(), GetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\data\\eflc\\").Get()) & ~FILE_ATTRIBUTE_READONLY);
								CopyFileEx(file.Get(), CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\data\\eflc\\").Get(), (LPPROGRESS_ROUTINE)CurrentFileProgress, NULL, false, 0);
							} 
							else if(CString(szCopyFile[n]).Find("ultiplayer\\common\\data\\effects\\") != std::string::npos && szCopyFile[n][0] != '%') {
								CString file(SharedUtility::GetAppPath());
								file.AppendF(szCopyFile[n]);
								if(SharedUtility::Exists(CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\effects\\").Get()))
									SetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\effects\\").Get(), GetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\effects\\").Get()) & ~FILE_ATTRIBUTE_READONLY);
								CopyFileEx(file.Get(), CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\effects\\").Get(), (LPPROGRESS_ROUTINE)CurrentFileProgress, NULL, false, 0);
							}
							else if(CString(szCopyFile[n]).Find("ultiplayer\\common\\data\\") != std::string::npos && szCopyFile[n][0] != '%') {
								CString file(SharedUtility::GetAppPath());
								file.AppendF(szCopyFile[n]);
								if(SharedUtility::Exists(CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\").Get()))
									SetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\").Get(), GetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\").Get()) & ~FILE_ATTRIBUTE_READONLY);
								CopyFileEx(file.Get(), CString(szCopyFileDest[n], szInstallDirectory, "\\common\\data\\").Get(), (LPPROGRESS_ROUTINE)CurrentFileProgress, NULL, false, 0);
							}
							else if(CString(szCopyFile[n]).Find("ultiplayer\\pc\\textures\\") != std::string::npos && szCopyFile[n][0] != '%') {
								CString file(SharedUtility::GetAppPath());
								file.AppendF(szCopyFile[n]);
								if(SharedUtility::Exists(CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\textures\\").Get()))
									SetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\textures\\").Get(), GetFileAttributes(CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\textures\\").Get()) & ~FILE_ATTRIBUTE_READONLY);
								CopyFileEx(file.Get(), CString(szCopyFileDest[n], szInstallDirectory, "\\pc\\textures\\").Get(), (LPPROGRESS_ROUTINE)CurrentFileProgress, NULL, false, 0);
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
	}


}
int ShowMessageBox(const char * szText, UINT uType = (MB_ICONEXCLAMATION | MB_OK))
{
	return MessageBox(NULL, szText, "IV:Multiplayer", uType);
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
			if(ShowMessageBox("Do you want to copy EFLC files?", MB_ICONEXCLAMATION | MB_YESNO) == IDYES)
				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CopyThread, NULL, NULL, NULL);
			else
			{
				SharedUtility::WriteRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "usingeflc", "0", 1);
				DestroyWindow(pgCurrentFile);
			}
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
