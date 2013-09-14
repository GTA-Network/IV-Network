//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CGUI.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include "CCore.h"

class CGUI
{
	private: 
			// The Gwen Stuff
			Gwen::Renderer::DirectX9			* m_pRenderer;
			Gwen::Skin::TexturedBase			* m_pSkin;
			Gwen::Controls::Canvas				* m_pCanvas;
			Gwen::Input::Windows				m_input;		
			
			// The Window Size Variable
			unsigned int						m_uiWidth;
			unsigned int						m_uiHeight;
	
	public:
			CGUI(IDirect3DDevice9 * pDevice, unsigned int uiWidth, unsigned int uiHeight);
			~CGUI(void);

			
			// The GWEN Rendering Stuff
			void								Render(void);
			bool								ProcessInput(UINT uMessage, LPARAM lParam, WPARAM wParam);
			
			// The Windows Stuff
			unsigned int						GetWindowWidth() {return *(int*)0xC17044;}
			unsigned int						GetWindowHeight() {return *(int*)0xC17048;}
};
		