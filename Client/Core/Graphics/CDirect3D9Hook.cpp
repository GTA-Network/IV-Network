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

#include "CDirect3D9Hook.h"
#include "IDirect3D9Proxy.h"
#include <Detours\detours.h>

CDirect3D9Hook::Direct3DCreate9_t CDirect3D9Hook::m_pfnDirect3DCreate9;

CDirect3D9Hook::CDirect3D9Hook() :
	m_bHookInstalled(false)
{
	m_pfnDirect3DCreate9 = NULL;
}

CDirect3D9Hook::~CDirect3D9Hook()
{

}

bool CDirect3D9Hook::Install()
{
	if(!m_bHookInstalled)
	{      
		m_pfnDirect3DCreate9 = reinterpret_cast<Direct3DCreate9_t>(DetourFunction(DetourFindFunction ("D3D9.DLL", "Direct3DCreate9"),  reinterpret_cast<PBYTE>(Direct3DCreate9_Hook)));
			
		m_bHookInstalled = true;
        return true;
    }
    return false;
}

void CDirect3D9Hook::Uninstall()
{
	if(m_bHookInstalled)
    {
        if ( m_pfnDirect3DCreate9 )
		{
			DetourRemove ( reinterpret_cast < PBYTE > ( m_pfnDirect3DCreate9 ), reinterpret_cast < PBYTE > ( Direct3DCreate9_Hook ) );
		}
                        
        m_bHookInstalled = false;
    }
}

IDirect3D9 * WINAPI CDirect3D9Hook::Direct3DCreate9_Hook(UINT SDKVersion)
{
    IDirect3D9 * pD3D = m_pfnDirect3DCreate9(SDKVersion);
    return (!pD3D ? NULL : new IDirect3D9Proxy(pD3D));
}