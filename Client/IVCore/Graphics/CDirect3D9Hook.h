//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CDirect3D9Hook.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDirect3D9Hook_h
#define CDirect3D9Hook_h

#include "StdDXInc.h"

class CDirect3D9Hook {
private:
	typedef					IDirect3D9 * (WINAPI * Direct3DCreate9_t)(UINT);
	bool					m_bHookInstalled;
	static Direct3DCreate9_t m_pfnDirect3DCreate9;
	static IDirect3D9 * WINAPI Direct3DCreate9_Hook(UINT SDKVersion);
	HINSTANCE				h_dllHandle;	
public:
	CDirect3D9Hook();
	~CDirect3D9Hook();

	bool					Install();
	void					Uninstall();
};

#endif // CDirect3D9Hook_h