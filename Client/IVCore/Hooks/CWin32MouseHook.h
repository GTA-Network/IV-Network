//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CWin32MouseHook.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CWin32MouseHook_h
#define CWin32MouseHook_h

#include <Common.h>
#include <winsock2.h>
#include <windows.h>

class CCursorHook {
private:
	typedef int			(WINAPI * ShowCursor_t)(BOOL);

	static ShowCursor_t m_pShowCursor;
	static bool			m_bHookInstalled;

	static int WINAPI	ShowCursor_Hook(BOOL bShow);

public:
	static void Install();
	static void Uninstall();
};

#endif
