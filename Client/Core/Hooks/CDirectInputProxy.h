//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CDirectInputProxy.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDirectInputProxy_h
#define CDirectInputProxy_h

#include <Common.h>
#include <Graphics\CDirectInput8Proxy.h>
#include <DXSDK/Include/XInput.h>

class CDirectInputHook
{
private:
	typedef HRESULT				 (WINAPI * DirectInput8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN);
	typedef DWORD                (WINAPI * XInputGetState_t)(DWORD dwUserIndex, XINPUT_STATE * pState);

	static DirectInput8Create_t  m_pDirectInput8Create;
	static XInputGetState_t      m_pXInputGetState;
	static bool					 m_bHookInstalled;

	static HRESULT WINAPI		 DirectInput8Create_Hook(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);
	static DWORD WINAPI          XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE * pState);

public:
	static void Install();
	static void Uninstall();
};

#endif // CDirectInputProxy_h


