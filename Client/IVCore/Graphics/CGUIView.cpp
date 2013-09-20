//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CGUIView.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CCore.h"

using namespace Gwen;

CGUIView::CGUIView(Renderer::DirectX9* pRenderer)
{
	m_pRenderer = pRenderer;
	
	skin.SetRender( pRenderer );
	
	m_pCanvas = new Controls::Canvas( &skin );
	m_pCanvas->SetSkin( &skin );
	
#ifdef MOUSE_DEBUG
	m_pHelper = new Controls::ImagePanel(m_pCanvas);
	m_pHelper->SetPos(0, 0);
	m_pHelper->SetSize(16, 16);
	m_pHelper->SetDrawColor(Gwen::Color(0, 0, 0, 0));
	m_pHelper->SetShouldDrawBackground(false);
	m_pHelper->SetImage(SharedUtility::GetAbsolutePath("\\multiplayer\\datafiles\\cursor.png").Get());
#endif

	m_pInput = new Input::Windows();
	m_pInput->Initialize( m_pCanvas );
}

CGUIView::~CGUIView()
{
	SAFE_DELETE(m_pInput);
	SAFE_DELETE(m_pCanvas);
}

void CGUIView::Render()
{
	m_pCanvas->RenderCanvas();
}

bool CGUIView::ProcessInput(UINT message, LPARAM lParam, WPARAM wParam)
{
	MSG msg;
	msg.message = message;
	msg.lParam = lParam;
	msg.wParam = wParam;

#ifdef MOUSE_DEBUG
	if(message == WM_MOUSEMOVE)
	{
		int y = HIWORD(msg.lParam);
		int x = LOWORD(msg.lParam);
		m_pHelper->SetPos(x+1, y+1);
		m_pHelper->BringToFront();
	}
#endif
	return m_pInput->ProcessMessage(msg);
}

void CGUIView::SetScreenSize(int iWidth, int iHeight)
{
	m_pCanvas->SetSize(iWidth, iHeight);
}		