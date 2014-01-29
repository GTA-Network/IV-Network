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

#include "CDirectInput8Proxy.h"
#include "CDirectInputDevice8Proxy.h"

CDirectInput8Proxy::CDirectInput8Proxy(IDirectInput8 * dinput)
	: m_pDevice(dinput)
{
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE CDirectInput8Proxy::AddRef()
{
	return m_pDevice->AddRef();
}

ULONG STDMETHODCALLTYPE CDirectInput8Proxy::Release()
{
	ULONG uRet = m_pDevice->Release();

	if ( uRet == 0 )
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUknOuter)
{
	// Create the dinput device
	HRESULT hResult = m_pDevice->CreateDevice( rguid, lplpDirectInputDevice, pUknOuter );

	if ( hResult == DI_OK )
	{
		// Get the device type
        eDIDeviceType type = DIDEVICE_TYPE_UNKNOWN;

        if(rguid == GUID_SysMouse)
			type = DIDEVICE_TYPE_MOUSE;
        else if(rguid == GUID_SysKeyboard)
            type = DIDEVICE_TYPE_KEYBOARD;
        else if(rguid == GUID_Joystick)
			type = DIDEVICE_TYPE_JOYSTICK;

		// Device created; Feed the application our proxy interface
		*lplpDirectInputDevice = new CDirectInputDevice8Proxy( *lplpDirectInputDevice, type );
	}

	return hResult;
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDevice->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::GetDeviceStatus(REFGUID rguidInstance)
{
	return m_pDevice->GetDeviceStatus(rguidInstance);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return m_pDevice->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return m_pDevice->Initialize(hinst, dwVersion);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance)
{
	return m_pDevice->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_pDevice->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8Proxy::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return m_pDevice->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}