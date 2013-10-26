//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTags.h
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#pragma once

#include "Graphics\CGUI.h"
#include <Math\CVector3.h>

class CTags
{
	private:
			CEGUI::Font * m_pFont;
			void DrawTag(CString strName, unsigned int uiHealth, unsigned int uiArmour, Vector2 vecScreenPosition, DWORD dwColor);

	public:
			CTags();
			~CTags();

			void Draw();
};