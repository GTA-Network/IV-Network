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

CGUI::CGUI(IDirect3DDevice9* pDevice)
{
	m_pActiveView = NULL;
	memset(m_pViews, 0, sizeof(m_pViews));

	m_pRenderer = new Renderer::DirectX9(pDevice);

	m_iScreenWidth = 1680;
	m_iScreenHeight = 1050;

	ClearView(GUI_MAIN);
	ClearView(GUI_SERVER);

	// Create the main menu instance
	new CMainMenu(GetCanvas(GUI_MAIN));

	SetView(GUI_NONE);
}

CGUI::~CGUI()
{
	for (int i = 0; i < GUI_NONE; ++i)
	{
		SAFE_DELETE(m_pViews[i]);
	}
}

void CGUI::Render()
{
	if (m_pActiveView)
	{
		m_pActiveView->Render();
	}
}

bool CGUI::ProcessInput(UINT message, LPARAM lParam, WPARAM wParam)
{
	if (m_pActiveView)
	{
		return m_pActiveView->ProcessInput(message, lParam, wParam);
	}
	return false;
}

CGUI::eGUIView CGUI::GetView()
{
	if (!m_pActiveView)
		return GUI_NONE;

	for (int i = 0; i < GUI_NONE; ++i)
	{
		if (m_pViews[i] == m_pActiveView)
		{
			return (eGUIView) i;
		}
	}
	return GUI_NONE;
}

void CGUI::SetView(eGUIView view)
{
	if (view < GUI_NONE)
	{
		m_pActiveView = m_pViews[view];
	}
	else
	{
		m_pActiveView = NULL;
	}
}

void CGUI::ClearView(eGUIView view)
{
	if (view >= GUI_NONE)
		return;

	if (m_pActiveView && m_pActiveView == m_pViews[view])
		SetView(GUI_NONE);

	SAFE_DELETE(m_pViews[view]);

	CGUIView* pView = new CGUIView(m_pRenderer);

	pView->SetScreenSize(m_iScreenWidth, m_iScreenHeight);

	m_pViews[view] = pView;
}

void CGUI::SetScreenSize(int iWidth, int iHeight)
{
	for (int i = 0; i < GUI_NONE; ++i)
		m_pViews[i]->SetScreenSize(iWidth, iHeight);

	m_iScreenWidth = iWidth;
	m_iScreenHeight = iHeight;
}

void CGUI::GetScreenSize(int* iWidth, int* iHeight)
{
	*iWidth = m_iScreenWidth;
	*iHeight = m_iScreenHeight;
}

Gwen::Controls::Canvas* CGUI::GetCanvas(eGUIView view)
{
	if (view < GUI_NONE)
		return m_pViews[view]->GetCanvas();
	return NULL;
}