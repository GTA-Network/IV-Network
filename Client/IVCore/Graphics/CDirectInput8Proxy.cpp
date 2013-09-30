//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CDirectInput8Proxy.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

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