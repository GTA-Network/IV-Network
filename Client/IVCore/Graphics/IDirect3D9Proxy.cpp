//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: IDirect3D9Proxy.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "IDirect3D9Proxy.h"
#include <CCore.h>
#include "CDirectInput8Hook.h"
#include <dinput.h>
#include <Windows.h>
#include <windowsx.h>
#include "Input.h"

extern CCore * g_pCore;
extern WNDPROC m_wWndProc;

IDirect3D9Proxy::IDirect3D9Proxy(IDirect3D9 * pD3D)
	: m_pD3D(pD3D)
{

}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::QueryInterface(REFIID riid, void ** ppvObj)
{
	return m_pD3D->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE IDirect3D9Proxy::AddRef()
{
	return m_pD3D->AddRef();
}

ULONG STDMETHODCALLTYPE IDirect3D9Proxy::Release()
{
	ULONG uRet = m_pD3D->Release();

	if(uRet == 0)
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::RegisterSoftwareDevice(void * pInitializeFunction)
{
	return m_pD3D->RegisterSoftwareDevice(pInitializeFunction);
}

UINT STDMETHODCALLTYPE IDirect3D9Proxy::GetAdapterCount()
{
	return m_pD3D->GetAdapterCount();
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 * pIdentifier)
{
	return m_pD3D->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT STDMETHODCALLTYPE IDirect3D9Proxy::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return m_pD3D->GetAdapterModeCount(Adapter, Format);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return m_pD3D->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return m_pD3D->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return m_pD3D->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return m_pD3D->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD * pQualityLevels)
{
	return m_pD3D->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return m_pD3D->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return m_pD3D->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	return m_pD3D->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR STDMETHODCALLTYPE IDirect3D9Proxy::GetAdapterMonitor(UINT Adapter)
{
	return m_pD3D->GetAdapterMonitor(Adapter);
}

HRESULT STDMETHODCALLTYPE IDirect3D9Proxy::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS * pPresentationParameters, IDirect3DDevice9 ** ppReturnedDeviceInterface)
{
	
	// Create the device
	HRESULT hr = m_pD3D->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
	
	SetWindowLong(hFocusWindow, GWL_STYLE, GetWindowLong(hFocusWindow, GWL_STYLE) & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX);

    if(!m_wWndProc)
        m_wWndProc = SubclassWindow(hFocusWindow, WndProc_Hook);
	 
	if(SUCCEEDED(hr))
	{
		// Initialise the graphics
		g_pCore->GetGraphics()->Initialise(*ppReturnedDeviceInterface);

		// Call the OnDeviceCreate callback
		g_pCore->OnDeviceCreate(*ppReturnedDeviceInterface, pPresentationParameters);

		//
		*ppReturnedDeviceInterface = new IDirect3DDevice9Proxy(*ppReturnedDeviceInterface);
	}
	return hr;
}
