//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CGraphics.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

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
class CGraphics {
private:
	IDirect3DDevice9		* m_pDevice;
	CDirect3D9Hook			* m_pDeviceHook;
	CDirectInput8Hook		* m_pDirectInput8Hook;
	ID3DXFont				* m_pFont;
	LPD3DXSPRITE			m_pSprite;

	bool					m_bInitialised;

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

	void					Initialise(IDirect3DDevice9 * pDevice);
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