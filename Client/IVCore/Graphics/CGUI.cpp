//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CGUI.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CCore.h"

using namespace Gwen;

CGUI::CGUI(IDirect3DDevice9 * pDevice, unsigned int uiWidth, unsigned int uiHeight)
{
	// Create the GWEN Renderer
	m_pRenderer = new Gwen::Renderer::DirectX9(pDevice);


	// Create the GWEN Skin 
	// Todo: Change the skin to a custom one
	m_pSkin = new Gwen::Skin::TexturedBase();
	m_pSkin->SetRender(m_pRenderer);
	m_pSkin->Init("multiplayer\\datafiles\\DefaultSkin.png");

	// Create the GWEN Canvas
	m_pCanvas = new Gwen::Controls::Canvas(m_pSkin);
	m_pCanvas->SetSize(uiWidth, uiHeight);

	// Initialize the GWEN Input
	m_input.Initialize(m_pCanvas);
}

CGUI::~CGUI()
{
	// Clean up the GWEN Stuff
	delete m_pCanvas;
	delete m_pSkin;
	delete m_pRenderer;
}

void CGUI::Render(void)
{
	// The skin won't load render properly without this
	m_pRenderer->DrawFilledRect(Gwen::Rect(0, 0, 0, 0));

	// Render the GWEN Canvas
	m_pCanvas->RenderCanvas();
}

bool CGUI::ProcessInput(UINT uMessage, LPARAM lParam, WPARAM wParam)
{
	return false;
}