//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CDirectInput8Proxy.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDirectInput8Proxy_h
#define CDirectInput8Proxy_h

#include "StdDXInc.h"

class CDirectInput8Proxy : public IDirectInput8 {
private:
	IDirectInput8A *    m_pDevice;

public:
	CDirectInput8Proxy(IDirectInput8 * dinput);

	/*** IUnknown methods ***/
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID * ppvObj);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();

	/*** IDirectInput8A methods ***/
	HRESULT STDMETHODCALLTYPE CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUknOuter);
	HRESULT STDMETHODCALLTYPE EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT STDMETHODCALLTYPE GetDeviceStatus(REFGUID rguidInstance);
	HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags);
	HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion);
	HRESULT STDMETHODCALLTYPE FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance);
	HRESULT STDMETHODCALLTYPE EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags);
	HRESULT STDMETHODCALLTYPE ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData);
};

#endif // CDirectInput8Proxy_h