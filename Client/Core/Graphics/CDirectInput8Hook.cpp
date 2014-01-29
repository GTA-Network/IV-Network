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

#include "CDirectInput8Hook.h"
#include <CCore.h>
#include <dinput.h>

extern	CCore					* g_pCore;
bool							CDirectInput8Hook::m_bInstalled = false;
DirectInput8Create_t			CDirectInput8Hook::m_pDirectInput8Create = NULL;

HRESULT WINAPI DirectInput8Create__Hook( HINSTANCE hInst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter )
{
	// Call the real DirectInput8Create
	HRESULT hResult = CDirectInput8Hook::m_pDirectInput8Create( hInst, dwVersion, riidltf, ppvOut, punkOuter );

	// Did the call succeed?
	if( SUCCEEDED( hResult ) )
	{
		// Get the directinput8 pointer
		IDirectInput8 * pInput = (IDirectInput8 *)*ppvOut;

		// Create the proxy
		*ppvOut = new CDirectInput8Proxy( pInput );
	}

	return hResult;
}

bool CDirectInput8Hook::Install( )
{
	// Is the proxy already installed?
	if( m_bInstalled )
		return false;

	// Install the detour patch
	m_pDirectInput8Create = ( DirectInput8Create_t ) DetourFunction( DetourFindFunction( "dinput8.dll", "DirectInput8Create" ), (PBYTE)DirectInput8Create__Hook );

	// Mark as installed
	m_bInstalled = true;

	return true;
}

void CDirectInput8Hook::Uninstall( )
{
	// Is the proxy not installed?
	if( !m_bInstalled )
		return;

	// Uninstall the detour patch
	DetourRemove( (PBYTE)m_pDirectInput8Create, (PBYTE)DirectInput8Create__Hook );

	// Mark as not installed
	m_bInstalled = false;
}