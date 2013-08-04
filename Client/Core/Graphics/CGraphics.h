//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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
#include <d3dx9.h>
#include "CDirectInputDevice8Proxy.h"
#include "CDirectInput8Proxy.h"
#include "CDirectInput8Hook.h"

#include <Math\CMaths.h>
#include <Detours\detours.h>

struct sFontInfo
{
	const char			* szFontName;
	unsigned int		uiHeight;
	unsigned int		uiWeight;
};

class CDirect3D9Hook;
class CGraphics
{

private:

	IDirect3DDevice9		* m_pDevice;
	CDirect3D9Hook			* m_pDeviceHook;
	CDirectInput8Hook		* m_pDirectInput8Hook;
	ID3DXFont				* m_pFonts[NUM_FONTS];
	LPD3DXSPRITE			m_pSprite;

	bool					m_bInitialised;

	unsigned int			m_uiFramesPerSecond;
	unsigned int			m_uiCurrentFPS;
	unsigned int			m_uiLastCheck;

	bool					LoadFonts();

public:

	CGraphics();
	~CGraphics();

	void					Initialise(IDirect3DDevice9 * pDevice);
	void					Render();

	void					DrawText(unsigned int uiLeft, unsigned int uiTop, unsigned int uiRight, unsigned int uiBottom, unsigned long ulColor, float fScaleX, float fScaleY, unsigned long ulFormat, unsigned int fontIndex, bool bShadow, const char * szText);
	void					DrawText(float fX, float fY, unsigned long ulColor, float fScale, unsigned int fontIndex, unsigned long ulFormat, bool bShadow, const char * szFormat, ...);
	void					DrawText(CVector3 vecPosition, float fRange, unsigned long ulColor, float fScale, unsigned int fontIndex, unsigned long ulFormat, bool bShadow, const char *szFormat, ...);

	ID3DXFont				* GetFont(unsigned int uiIndex);

	void					OnLostDevice(IDirect3DDevice9 * pDevice);
	void					OnRestoreDevice(IDirect3DDevice9 * pDevice);

	float					GetFontHeight(float fScale = 1.0f);
	float					GetCharacterWidth(char c, float fScale = 1.0f);

	inline Vector2			GetSize()
	{
		D3DVIEWPORT9 vport;
		
		if(m_pDevice)
			m_pDevice->GetViewport(&vport);			

		return Vector2((float)vport.Width, (float)vport.Height);
	}

	IDirect3DDevice9		*GetDevice() { return m_pDevice; }
};

#endif // CGraphics_h