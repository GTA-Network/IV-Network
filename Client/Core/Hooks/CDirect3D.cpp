//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CDirect3D.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CDirect3D.h"

CDirect3DHook::Direct3DCreate9_t CDirect3DHook::m_pDirect3DCreate9;
bool CDirect3DHook::m_bHookInstalled = false;

IDirect3D9 * WINAPI CDirect3DHook::Direct3DCreate9_Hook(UINT SDKVersion)
{
	IDirect3D9 * pD3D = m_pDirect3DCreate9(SDKVersion);
	return pD3D ? new Direct3D9Proxy(pD3D) : NULL;
}

void CDirect3DHook::Install()
{
	if(!m_bHookInstalled)
	{
		m_pDirect3DCreate9 = (Direct3DCreate9_t)CPatcher::InstallDetourPatch("D3D9.dll", "Direct3DCreate9", (DWORD)Direct3DCreate9_Hook);

		CLogFile::Printf("Hooked 'Direct3DCreate9' in 'D3D9.dll' (0x%p)", m_pDirect3DCreate9);

		m_bHookInstalled = true;
	}
}

void CDirect3DHook::Uninstall()
{
	if(m_bHookInstalled)
	{
		if(m_pDirect3DCreate9)
			CPatcher::UninstallDetourPatch((PBYTE)m_pDirect3DCreate9, (DWORD)Direct3DCreate9_Hook);

		m_bHookInstalled = false;
	}
}
