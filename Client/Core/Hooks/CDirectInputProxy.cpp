//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CDirectInputProxy.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CDirectInputProxy.h"

#include <CLogFile.h>
#include <Patcher\CPatcher.h>

CDirectInputHook::DirectInput8Create_t CDirectInputHook::m_pDirectInput8Create;
CDirectInputHook::XInputGetState_t     CDirectInputHook::m_pXInputGetState;
bool CDirectInputHook::m_bHookInstalled = false;

// HACK: We don't want to use the proxy for our own device
bool bOurDeviceCreated = false;

HRESULT WINAPI CDirectInputHook::DirectInput8Create_Hook(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
	CLogFile::Printf("DirectInput8Create Called");

	// Call the real 'DirectInput8Create'
	HRESULT hr = m_pDirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	// If the call succeeded create our proxy device
	if(SUCCEEDED(hr))
	{
		if(bOurDeviceCreated)
		{
			IDirectInput8 * pDInput = (IDirectInput8 *)*ppvOut;
			*ppvOut = new CDirectInput8Proxy(pDInput);
		}
		else
			bOurDeviceCreated = true;
	}
	else
		CLogFile::Printf("DirectInput8Create Call Failed!");

	return hr;
}

DWORD WINAPI CDirectInputHook::XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE * pState)
{
	DWORD dwResult = m_pXInputGetState(dwUserIndex, pState);

	/*if(!CGame::GetInputState())
	{
		// If the input is disabled clear the buffer
		memset(pState, 0, sizeof(XINPUT_STATE));
	}*/

	return dwResult;
}

void CDirectInputHook::Install()
{
	if(!m_bHookInstalled)
	{
		m_pDirectInput8Create = (DirectInput8Create_t)CPatcher::InstallDetourPatch("DInput8.dll", "DirectInput8Create", (DWORD)DirectInput8Create_Hook);
		CLogFile::Printf("Hooked 'DirectInput8Create' in 'DInput8.dll' (0x%p)", m_pDirectInput8Create);

		m_pXInputGetState = (XInputGetState_t)CPatcher::InstallDetourPatch("xinput1_3.dll", "XInputGetState", (DWORD)XInputGetState_Hook);
		CLogFile::Printf("Hooked 'XInputGetState' in 'xinput1_3.dll' (0x%p)", m_pXInputGetState);

		m_bHookInstalled = true;
	}
}

void CDirectInputHook::Uninstall()
{
	if(m_bHookInstalled)
	{
		if(m_pXInputGetState)
			CPatcher::UninstallDetourPatch((PBYTE)m_pXInputGetState, (DWORD)XInputGetState_Hook);

		if(m_pDirectInput8Create)
			CPatcher::UninstallDetourPatch((PBYTE)m_pDirectInput8Create, (DWORD)DirectInput8Create_Hook);

		m_bHookInstalled = false;
	}
}
