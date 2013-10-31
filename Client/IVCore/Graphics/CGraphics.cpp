//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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


struct D3DVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	DWORD dwColor;

	D3DVERTEX()
	{
		fX = 0.0f;
		fY = 0.0f;
		fZ = 0.0f;
		fRHW = 1.0f;
		dwColor = 0;
	}

	D3DVERTEX(float _fX, float _fY, float _fZ, float _fRHW, DWORD _dwColor)
	{
		fX = _fX;
		fY = _fY;
		fZ = _fZ;
		fRHW = _fRHW;
		dwColor = _dwColor;
	}
};

const unsigned char g_szPixel [] = { 0x42, 0x4D, 0x3A, 0, 0, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0x28, 0, 0,
                                    0, 0x1, 0, 0, 0, 0x1, 0, 0, 0, 0x1, 0, 0x18, 0, 0, 0, 0, 0,
                                    0x4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0xFF, 0xFF, 0xFF, 0 };

CGraphics::CGraphics() :
	m_bInitialised(false), m_uiFramesPerSecond(0), m_uiCurrentFPS(0),
	m_uiLastCheck(0), m_pDevice(NULL), m_pFont(NULL)
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

	m_uiLastCheck = GetTickCount();
}

CGraphics::~CGraphics()
{
	// Uninstall the d3d9 device hook
	m_pDeviceHook->Uninstall();

	// Delete the d3d9 device hook
	SAFE_DELETE(m_pDeviceHook);

	// Delete the font pointer
	SAFE_DELETE(m_pFont);

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
	}
}

bool CGraphics::LoadFonts()
{
	int fontsize = NULL;
	bool bSuccess = true;

	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop); 

	if (desktop.right <= 1280 && desktop.bottom <= 1024) // Small Resolution
	{
		fontsize = 14;
	}
	else if (desktop.right > 1280 && desktop.right <= 1400) // Medium Resolution
	{
		fontsize = 16;
	}
	else if (desktop.right > 1400) // Large Resolution
	{
		fontsize = 18;
	}
	bSuccess &= SUCCEEDED(D3DXCreateFont(m_pDevice, fontsize, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &m_pFont));

	if (fontsize == NULL)
	{
		CLogFile::Print("[Crash Report] The font size has not been set properly, exiting IV:Network");
		TerminateProcess(GetCurrentProcess(), false);
		return false;
	}

	return bSuccess && SUCCEEDED(D3DXCreateSprite(m_pDevice, &m_pSprite));
}


void CGraphics::DrawText(unsigned int uiLeft, unsigned int uiTop, unsigned int uiRight, unsigned int uiBottom, unsigned long ulColor, float fScaleX, float fScaleY, unsigned long ulFormat, bool bShadow, const char * szText)
{
	// Is the sprite invalid?
	if(!m_pSprite)
		return;

	// Is the font invalid?
	if (!m_pFont)
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
		m_pFont->DrawTextA(m_pSprite, szText, -1, &shadow_rect, ulFormat, D3DCOLOR_ARGB(255, 0, 0, 0));
	}

	// Draw the text
	m_pFont->DrawTextA(m_pSprite, szText, -1, &rect, ulFormat, ulColor);

	// End the sprite
    m_pSprite->End();
}

void CGraphics::DrawText(float fX, float fY, unsigned long ulColor, float fScale, unsigned long ulFormat, bool bShadow, const char * szFormat, ...)
{
	// Get the string arguments
	char szBuffer[ 2048 ];
	va_list vArgs;
	va_start(vArgs, szFormat);
	vsprintf(szBuffer, szFormat, vArgs);
	va_end(vArgs);

	// Draw the text
	DrawText((unsigned int)fX, (unsigned int)fY, (unsigned int)fX, (unsigned int)fY, ulColor, fScale, fScale, ulFormat, bShadow, szBuffer); 
}

void CGraphics::DrawText(CVector3 vecPosition, float fRange, unsigned long ulColor, float fScale, unsigned long ulFormat, bool bShadow, const char * szFormat, ...)
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
		DrawText((unsigned int)vecScreen.fX, (unsigned int)vecScreen.fY, (unsigned int)vecScreen.fX, (unsigned int)vecScreen.fY, ulColor, fScale, fScale, ulFormat, bShadow, szBuffer); 
}

void CGraphics::DrawBox(float fLeft, float fTop, float fWidth, float fHeight, DWORD dwColorBox)
{
    D3DVERTEX vertex[4];
	vertex[0] = D3DVERTEX(fLeft, fTop, 0.0f, 1.0f, dwColorBox);
    vertex[1] = D3DVERTEX((fLeft + fWidth), fTop, 0.0f, 1.0f, dwColorBox);
    vertex[2] = D3DVERTEX((fLeft + fWidth), (fTop + fHeight), 0.0f, 1.0f, dwColorBox);
    vertex[3] = D3DVERTEX(fLeft, (fTop + fHeight), 0.0f, 1.0f, dwColorBox);
    short indices[6] = {0, 1 ,2, 0, 2, 3};

    m_pDevice->SetTexture(0, NULL);
    m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
    m_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, &indices[0], D3DFMT_INDEX16, &vertex[0], sizeof(D3DVERTEX));
 
}

void CGraphics::DrawRect(float fX, float fY, float fWidth, float fHeight, unsigned long ulColor)
{
	D3DVERTEX vertex[4];
	vertex[0] = D3DVERTEX(fX, fY, 0.0f, 1.0f, ulColor);
	vertex[1] = D3DVERTEX((fX + fWidth), fY, 0.0f, 1.0f, ulColor);
	vertex[2] = D3DVERTEX((fX + fWidth), (fY + fHeight), 0.0f, 1.0f, ulColor);
	vertex[3] = D3DVERTEX(fX, (fY + fHeight), 0.0f, 1.0f, ulColor);
	short indices[6] = {0, 1, 2, 0, 2, 3};

	m_pDevice->SetTexture(0, NULL);
	m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, &indices[0], D3DFMT_INDEX16, &vertex[0], sizeof(D3DVERTEX));
}

void CGraphics::DrawLine(float fLeft, float fTop, float fRight, float fBottom, float fWidth, DWORD dwColour)
{
	D3DVERTEX vertex[2];
	vertex[0] = D3DVERTEX(fLeft, fTop, 0.0f, 1.0f, dwColour);
	vertex[1] = D3DVERTEX(fRight, fBottom, 0.0f, 1.0f, dwColour);

	m_pDevice->SetTexture(0, NULL);
	m_pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vertex[0], sizeof(D3DVERTEX));
}
ID3DXFont * CGraphics::GetFont()
{
	return m_pFont;
}

void CGraphics::OnLostDevice(IDirect3DDevice9 * pDevice)
{
	m_pFont->OnLostDevice();

	if(m_pSprite)
		m_pSprite->OnLostDevice();
}

void CGraphics::OnRestoreDevice(IDirect3DDevice9 * pDevice)
{
	m_pFont->OnResetDevice();

	if(m_pSprite)
		m_pSprite->OnResetDevice();
}

float CGraphics::GetFontHeight(float fScale)
{
	// Is the font valid?
	if (m_pFont)
	{
		D3DXFONT_DESC desc;
		m_pFont->GetDesc(&desc);
		return ((float) desc.Height * fScale);
	}

	return 0.0f;
}

float CGraphics::GetCharacterWidth(char c, float fScale)
{
	// Is the font valid?
	if (m_pFont)
	{
		HDC dc = m_pFont->GetDC();
		SIZE size;
		GetTextExtentPoint32(dc, &c, 1, &size);
		return ((float)size.cx * fScale);
	}

	return 0.0f;
}

float CGraphics::GetStringWidth(CString s, float fScale)
{
	float ret = 0.0f;
	
	for (unsigned int i = 0; i < s.GetLength(); ++i)
		ret += GetCharacterWidth(s.GetChar(i), fScale);

	return ret;
}

void CGraphics::DrawBox_2(float fLeft, float fTop, float fWidth, float fHeight, DWORD dwColorBox)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	// Generate the matrix
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &D3DXVECTOR2(fWidth, fHeight), NULL, 0.0f, &D3DXVECTOR2(fLeft, fTop));

	// Set the sprite transform
	m_pSprite->SetTransform(&matrix);

	// Draw the box
	m_pSprite->Draw(m_pPixelTexture, NULL, NULL, NULL, dwColorBox);

	// End the sprite
	m_pSprite->End();
}