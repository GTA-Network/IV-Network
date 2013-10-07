//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CDirectInputDevice8Proxy.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CDirectInputDevice8Proxy.h"
#include <CCore.h>
extern CCore * g_pCore;

CDirectInputDevice8Proxy::CDirectInputDevice8Proxy(IDirectInputDevice8 * pDevice, eDIDeviceType DeviceType) :
	m_pDevice(pDevice),
	m_DeviceType(DeviceType)
{
	m_Cursor.x = 0;
	m_Cursor.y = 0;
	memset(m_bMouseButtons, 0, sizeof(m_bMouseButtons));
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDevice->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE CDirectInputDevice8Proxy::AddRef()
{
	return m_pDevice->AddRef();
}

ULONG STDMETHODCALLTYPE CDirectInputDevice8Proxy::Release()
{
	ULONG uRet = m_pDevice->Release( );

	if ( uRet == 0 )
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetCapabilities(LPDIDEVCAPS p0)
{
	return m_pDevice->GetCapabilities(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDevice->EnumObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetProperty(REFGUID rguid, LPDIPROPHEADER p1)
{
	return m_pDevice->GetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::SetProperty(REFGUID rguid, LPCDIPROPHEADER p1)
{
	return m_pDevice->SetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::Acquire()
{
	return m_pDevice->Acquire();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::Unacquire()
{
	return m_pDevice->Unacquire();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetDeviceState(DWORD p0, LPVOID p1)
{
	HRESULT hResult			= m_pDevice->GetDeviceState( p0, p1 );
	char * keyBuffer = (char *) p1;

	return hResult;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetDeviceData(DWORD p0, LPDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	return m_pDevice->GetDeviceData( p0, p1, p2, p3 );
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::SetDataFormat(LPCDIDATAFORMAT p0)
{
	return m_pDevice->SetDataFormat(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::SetEventNotification(HANDLE p0)
{
	return m_pDevice->SetEventNotification(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::SetCooperativeLevel(HWND p0, DWORD p1)
{
	return m_pDevice->SetCooperativeLevel(p0, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA p0, DWORD p1, DWORD p2)
{
	return m_pDevice->GetObjectInfo(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetDeviceInfo(LPDIDEVICEINSTANCEA p0)
{
	return m_pDevice->GetDeviceInfo(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::RunControlPanel(HWND p0, DWORD p1)
{
	return m_pDevice->RunControlPanel(p0, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::Initialize(HINSTANCE p0, DWORD p1, REFGUID rguid)
{
	return m_pDevice->Initialize(p0, p1, rguid);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::CreateEffect(REFGUID rguid, LPCDIEFFECT p1, LPDIRECTINPUTEFFECT * p2, LPUNKNOWN p3)
{
	return m_pDevice->CreateEffect(rguid, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::EnumEffects(LPDIENUMEFFECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDevice->EnumEffects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetEffectInfo(LPDIEFFECTINFOA p0, REFGUID rguid)
{
	return m_pDevice->GetEffectInfo(p0, rguid);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetForceFeedbackState(LPDWORD p0)
{
	return m_pDevice->GetForceFeedbackState(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::SendForceFeedbackCommand(DWORD p0)
{
	return m_pDevice->SendForceFeedbackCommand(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK p0, LPVOID p1, DWORD p2)
{
	return m_pDevice->EnumCreatedEffectObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::Escape(LPDIEFFESCAPE p0)
{
	return m_pDevice->Escape(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::Poll()
{
	return m_pDevice->Poll();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::SendDeviceData(DWORD p0, LPCDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	return m_pDevice->SendDeviceData(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::EnumEffectsInFile(LPCSTR p0, LPDIENUMEFFECTSINFILECALLBACK p1, LPVOID p2, DWORD p3)
{
	return m_pDevice->EnumEffectsInFile(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::WriteEffectToFile(LPCSTR p0, DWORD p2, LPDIFILEEFFECT p3, DWORD p4)
{
	return m_pDevice->WriteEffectToFile(p0, p2, p3, p4);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::BuildActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDevice->BuildActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::SetActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDevice->SetActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8Proxy::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA p0)
{
	return m_pDevice->GetImageInfo(p0);
}