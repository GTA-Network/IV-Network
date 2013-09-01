//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CGraphics.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CGraphics.h"

#include <CCore.h>
#include "CDirect3D9Hook.h"
#include "CDirectInput8Hook.h"

extern CCore *g_pCore;

const unsigned char g_szPixel [] = { 0x42, 0x4D, 0x3A, 0, 0, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0x28, 0, 0,
                                    0, 0x1, 0, 0, 0, 0x1, 0, 0, 0, 0x1, 0, 0x18, 0, 0, 0, 0, 0,
                                    0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0xFF, 0xFF, 0xFF, 0 };

CGraphics::CGraphics()
{
	// Create the d3d9 device hook
	m_pDeviceHook = new CDirect3D9Hook;

	// Did the hook fail to create or install?
	if(!m_pDeviceHook || !m_pDeviceHook->Install())
		return;

	// Create the dinput8 hook
	m_pDirectInput8Hook = new CDirectInput8Hook;

	// Did the hook fail to create or install?
	if(!m_pDirectInput8Hook || !m_pDirectInput8Hook->Install())
		return;

	// Reset variables
	m_bInitialised = false;
	m_uiFramesPerSecond = NULL;
	m_uiCurrentFPS = 0;
	m_uiLastCheck = GetTickCount();
	m_pDevice = NULL;

	// Invalidate the font pointers
	for(int i = 0; i < NUM_FONTS; i++)
	{
		m_pFonts[i] = NULL;
	}
}

CGraphics::~CGraphics()
{
	// Uninstall the d3d9 device hook
	m_pDeviceHook->Uninstall();

	// Delete the d3d9 device hook
	SAFE_DELETE(m_pDeviceHook);

	// Delete the font pointers
	for(int i = 0; i < NUM_FONTS; i++)
	{
		SAFE_DELETE(m_pFonts[i]);
	}

	// Delete the sprite
	SAFE_DELETE(m_pSprite);

	// Mark as not initialised
	m_bInitialised = false;
}

void CGraphics::Initialise(IDirect3DDevice9 * pDevice)
{
	// Is the d3d9 device valid?
	if(pDevice)
	{
		// Store the d3d9 device pointer
		m_pDevice = pDevice;

		// Load the fonts
		if(!LoadFonts())
		{
			CLogFile::Printf("Failed to load the fonts!");

			// Terminate process
			TerminateProcess(GetCurrentProcess(), 0);
		}

		/*// Basic initialize
		D3DXCreateLine ( pDevice, &m_pLineInterface );
		D3DXCreateTextureFromFileInMemory ( pDevice, g_szPixel, sizeof ( g_szPixel ), &m_pDXPixelTexture );

		D3DDEVICE_CREATION_PARAMETERS cparams;
		RECT rect;

		m_pDevice->GetCreationParameters(&cparams);
		GetWindowRect(cparams.hFocusWindow, &rect);
		
		int width=rect.bottom-rect.top;
		int height=rect.right-rect.left;

		D3DXCreateTextureFromFile( pDevice, "multiplayer/logo.png", &pLoadingScreenTexture);
		m_pDevice->SetTexture(0, pLoadingScreenTexture);

		// Reset our device
		g_pCore->OnDeviceReset(m_pDevice);*/
	}
}

bool CGraphics::LoadFonts()
{
	// Create the font and sprite objects
	static const sFontInfo fontInfos[] =
	{
		{ "default",		15,		FW_NORMAL },
		{ "default-bold",	15,		FW_BOLD },
		{ "tahoma",			15,		FW_NORMAL },
		{ "tahoma-bold",	15,		FW_BOLD },
		{ "verdana",		15,		FW_NORMAL },
		{ "arial",			15,		FW_NORMAL }
	};

	bool bSuccess = true;
	for(int i = 0; bSuccess && i < NUM_FONTS; i++)
	{
		bSuccess &= SUCCEEDED(D3DXCreateFont(m_pDevice, fontInfos[i].uiHeight, 0, fontInfos[i].uiWeight, 1, FALSE,
						DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontInfos[i].szFontName,
                        &m_pFonts[i]));
	}

	return bSuccess && SUCCEEDED(D3DXCreateSprite(m_pDevice, &m_pSprite));
}

void CGraphics::DrawText(unsigned int uiLeft, unsigned int uiTop, unsigned int uiRight, unsigned int uiBottom, unsigned long ulColor, float fScaleX, float fScaleY, unsigned long ulFormat, unsigned int fontIndex, bool bShadow, const char * szText)
{
	// Is the sprite invalid?
	if(!m_pSprite)
		return;

	// Get the font
	ID3DXFont * pFont = GetFont(fontIndex);

	// Is the font invalid?
	if(!pFont)
		return;

	// Prevent the rect from getting scaled along with the size
	uiLeft = unsigned int ((float) uiLeft * (1.0f / fScaleX));
	uiTop = unsigned int ((float) uiTop * (1.0f / fScaleY));
	uiRight = unsigned int ((float) uiRight * (1.0f / fScaleX));
	uiBottom = unsigned int ((float) uiBottom * (1.0f / fScaleY));

	// Create the rect
	RECT rect;
	SetRect(&rect, uiLeft, uiTop, uiRight, uiBottom);

	D3DXMATRIX matrix;
	D3DXVECTOR2 scalingCentre(0.5f, 0.5f);
	D3DXVECTOR2 scaling(fScaleX, fScaleY);

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, NULL, 0.0f, NULL);

	m_pSprite->SetTransform(&matrix);

	// If we need to draw shadow do it now
	if (bShadow)
	{
		RECT shadow_rect;        
		SetRect(&shadow_rect, uiLeft + 1, uiTop + 1, uiRight + 1, uiBottom + 1);  
		pFont->DrawText(m_pSprite, szText, -1, &shadow_rect, ulFormat, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	// Draw the text
	pFont->DrawText(m_pSprite, szText, -1, &rect, ulFormat, ulColor);

	// End the sprite
    m_pSprite->End();
}

void CGraphics::DrawText(float fX, float fY, unsigned long ulColor, float fScale, unsigned int fontIndex, unsigned long ulFormat, bool bShadow, const char * szFormat, ...)
{
	// Get the string arguments
	char szBuffer[ 2048 ];
	va_list vArgs;
	va_start(vArgs, szFormat);
	vsprintf(szBuffer, szFormat, vArgs);
	va_end(vArgs);

	// Draw the text
	DrawText((unsigned int)fX, (unsigned int)fY, (unsigned int)fX, (unsigned int)fY, ulColor, fScale, fScale, ulFormat, fontIndex, bShadow, szBuffer); 
}

void CGraphics::DrawText(CVector3 vecPosition, float fRange, unsigned long ulColor, float fScale, unsigned int fontIndex, unsigned long ulFormat, bool bShadow, const char * szFormat, ...)
{
	// Get the string arguments
	char szBuffer[ 2048 ];
	va_list vArgs;
	va_start(vArgs, szFormat);
	vsprintf(szBuffer, szFormat, vArgs);
	va_end(vArgs);

	// Calc function
	Vector2 vecScreen;

	// Define viewport pointer
	D3DVIEWPORT9 Viewport;

	// Out (2d) position.
	D3DXVECTOR3 Out;

	// Grab 3d position.
	D3DXVECTOR3 Position;
	Position.x = vecPosition.fX;
	Position.y = vecPosition.fY;
	Position.z = vecPosition.fZ;

	// Define all matrix's
	D3DXMATRIX matIdent, matProj, matView;

	// Calculate position.
	D3DXMatrixIdentity(&matIdent);
	m_pDevice->GetViewport(&Viewport);
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXVec3Project(&Out, &Position, &Viewport, &matProj, &matView, &matIdent);

	// Wrap out positions for vector.
	vecScreen.fX = Out.x; vecScreen.fY = Out.y;

	// Calculating range.
	float _fRange = 1.0f;
	CVector3 vecLocalPos;		
	g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecLocalPos);

	// Check range status. (Is -1 disabled)
	if(fRange != -1.0f)
		_fRange = abs(sqrt((vecLocalPos.fX*vecPosition.fX)+(vecLocalPos.fY*vecPosition.fY)+(vecLocalPos.fZ*vecPosition.fZ)));

	// Draw the text
	if(_fRange >= fRange)
		DrawText((unsigned int)vecScreen.fX, (unsigned int)vecScreen.fY, (unsigned int)vecScreen.fX, (unsigned int)vecScreen.fY, ulColor, fScale, fScale, ulFormat, fontIndex, bShadow, szBuffer); 
}

ID3DXFont * CGraphics::GetFont(unsigned int uiIndex)
{
	if(uiIndex > NUM_FONTS)
		return NULL;

	return m_pFonts[ uiIndex ];
}

void CGraphics::OnLostDevice(IDirect3DDevice9 * pDevice)
{
	for(int i = 0; i < NUM_FONTS; i++)
	{
		m_pFonts[i]->OnLostDevice();
	}

	if(m_pSprite)
		m_pSprite->OnLostDevice();
}

void CGraphics::OnRestoreDevice(IDirect3DDevice9 * pDevice)
{
	for(int i = 0; i < NUM_FONTS; i++)
	{
		m_pFonts[i]->OnResetDevice();
	}

	if(m_pSprite)
		m_pSprite->OnResetDevice();
}

float CGraphics::GetFontHeight(float fScale)
{
	// Get the font
	LPD3DXFONT pFont = GetFont(0);

	// Is the font valid?
	if(pFont)
	{
		D3DXFONT_DESC desc;
		pFont->GetDesc(&desc);
		return ((float) desc.Height * fScale);
	}

	return 0.0f;
}

float CGraphics::GetCharacterWidth(char c, float fScale)
{
	// Get the font
	LPD3DXFONT pFont = GetFont(0);

	// Is the font valid?
	if(pFont)
	{
		HDC dc = pFont->GetDC();
		SIZE size;
		GetTextExtentPoint32(dc, &c, 1, &size);
		return ((float)size.cx * fScale);
	}

	return 0.0f;
}