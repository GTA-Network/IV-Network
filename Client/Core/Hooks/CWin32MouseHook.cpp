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

#include "CWin32MouseHook.h"
#include "Patcher/CPatcher.h"
#include <CLogFile.h>

CCursorHook::ShowCursor_t CCursorHook::m_pShowCursor;
bool CCursorHook::m_bHookInstalled = false;

int WINAPI CCursorHook::ShowCursor_Hook(BOOL bShow)
{
	//SetCursor(LoadCursor(NULL, IDC_ARROW));
	CLogFile::Printf("ShowCursor(%d)", bShow);

	SetCursor(NULL);
	return m_pShowCursor(bShow);
}

void CCursorHook::Install()
{
	if(!m_bHookInstalled)
	{
		m_pShowCursor = (ShowCursor_t)CPatcher::InstallDetourPatch("User32.dll", "ShowCursor", (DWORD)ShowCursor_Hook);
		CLogFile::Printf("Hooked 'ShowCursor' in 'User32.dll' (0x%p)", m_pShowCursor);
		m_bHookInstalled = true;
	}
}

void CCursorHook::Uninstall()
{
	if(m_bHookInstalled)
	{
		if(m_pShowCursor)
			CPatcher::UninstallDetourPatch((PBYTE)m_pShowCursor, (DWORD)ShowCursor_Hook);

		m_bHookInstalled = false;
	}
}
