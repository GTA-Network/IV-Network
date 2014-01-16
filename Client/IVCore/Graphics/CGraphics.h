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

#ifndef CGraphics_h
#define CGraphics_h

#include "StdDXInc.h"
#include "IDirect3DDevice9Proxy.h"
#include "IDirect3D9Proxy.h"
#include "CDirect3D9Hook.h"

#include <dinput.h>
#include "CDirectInputDevice8Proxy.h"
#include "CDirectInput8Proxy.h"
#include "CDirectInput8Hook.h"

#include <Math\CMaths.h>
#include <Detours\detours.h>

#ifdef DrawText
#undef DrawText
#endif

class CDirect3D9Hook;
class CGraphics
{
private:
	IDirect3DDevice9		* m_pDevice;
	CDirect3D9Hook			* m_pDeviceHook;
	CDirectInput8Hook		* m_pDirectInput8Hook;
	ID3DXFont				* m_pFont;
	LPD3DXSPRITE			m_pSprite;

	bool					m_bInitialized;

	unsigned int			m_uiFramesPerSecond;
	unsigned int			m_uiCurrentFPS;
	unsigned int			m_uiLastCheck;

	bool					LoadFonts();

	struct ID3DXLine*       m_pLineInterface;
	IDirect3DTexture9		* m_pDXPixelTexture;
	IDirect3DTexture9		* m_pPixelTexture;
public:
	CGraphics();
	~CGraphics();

	void					Initialize(IDirect3DDevice9 * pDevice);
	void					Render();

	void					DrawText(unsigned int uiLeft, unsigned int uiTop, unsigned int uiRight, unsigned int uiBottom, unsigned long ulColor, float fScaleX, float fScaleY, unsigned long ulFormat, bool bShadow, const char * szText);
	void					DrawText(float fX, float fY, unsigned long ulColor, float fScale, unsigned long ulFormat, bool bShadow, const char * szFormat, ...);
	void					DrawText(CVector3 vecPosition, float fRange, unsigned long ulColor, float fScale, unsigned long ulFormat, bool bShadow, const char *szFormat, ...);
	void					DrawBox(float fLeft, float fTop, float fWidth, float fHeight, DWORD dwColorBox);
	void					DrawLine(float fLeft, float fTop, float fRight, float fBottom, float fWidth, DWORD dwColour);
	void					DrawRect(float fX, float fY, float fWidth, float fHeight, unsigned long ulColor);
	void					DrawBox_2(float fLeft, float fTop, float fWidth, float fHeight, DWORD dwColorBox);

	ID3DXFont				* GetFont();

	void					OnLostDevice(IDirect3DDevice9 * pDevice);
	void					OnRestoreDevice(IDirect3DDevice9 * pDevice);

	float					GetFontHeight(float fScale = 1.0f);
	float					GetCharacterWidth(char c, float fScale = 1.0f);
	float					GetStringWidth(CString s, float fScale = 1.0f);

	inline Vector2			GetSize()
	{
		D3DVIEWPORT9 vport;
		
		if(m_pDevice)
			m_pDevice->GetViewport(&vport);			

		return Vector2((float)vport.Width, (float)vport.Height);
	}

	IDirect3DDevice9		*GetDevice() { return m_pDevice; }
	
	// member function public
	LPDIRECT3DTEXTURE9		pLoadingScreenTexture;
	LPD3DXSPRITE			GetSprite() { return m_pSprite; }
};

#endif // CGraphics_h