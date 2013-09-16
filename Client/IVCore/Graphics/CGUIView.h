//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CGUIView.h
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CCore.h"

#define MOUSE_DEBUG 1

class CGUIView
{
public:
		CGUIView(Gwen::Renderer::DirectX9* pRenderer);
		~CGUIView();
		
		void Render();
		bool ProcessInput(UINT message, LPARAM lParam, WPARAM wParam);
		
		void SetScreenSize(int iWidth, int iHeight);
		Gwen::Controls::Canvas* GetCanvas() { return m_pCanvas; }
private:
		Gwen::Renderer::DirectX9* m_pRenderer;
		Gwen::Skin::Simple skin;
		Gwen::Controls::Canvas* m_pCanvas;
		Gwen::Input::Windows* m_pInput;

#ifdef MOUSE_DEBUG
	// Button that is used as a mouse 
	Gwen::Controls::Button* m_pHelper;
#endif
};