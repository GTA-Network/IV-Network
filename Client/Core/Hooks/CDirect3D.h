//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CDirect3DHook.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDirect3DHook_h
#define CDirect3DHook_h

#include <CCore.h>
#include <Graphics\CDirect3D9Proxy.h>
#include <Patcher/CPatcher.h>
#include <CLogFile.h>

class CDirect3DHook {
private:
	typedef IDirect3D9 *	   (WINAPI * Direct3DCreate9_t)(UINT);

	static Direct3DCreate9_t   m_pDirect3DCreate9;
	static bool				   m_bHookInstalled;

	static IDirect3D9 * WINAPI Direct3DCreate9_Hook(UINT SDKVersion);

public:
	static void Install();
	static void Uninstall();
};

#endif // CDirect3DHook_h
