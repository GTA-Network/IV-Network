//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTags.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CCore.h"
#include <cstdlib>
#include "IV\CIVScript.h"

extern CCore * g_pCore;

#define BAR_HEIGHT 10.0f
#define BAR_BORDER 2.0f
#define BAR_PADDING 4.0f

CTags::CTags()
{
	m_pFont = g_pCore->GetGUI()->GetFont("Arial", 15);
}

CTags::~CTags()
{

}

void CTags::Draw()
{
	CGUI * m_pGUI = g_pCore->GetGUI();
	CGraphics * pGraphics = g_pCore->GetGraphics();
	CPlayerManager * pPlayerManager = g_pCore->GetGame()->GetPlayerManager();
	CLocalPlayer * pLocalPlayer = g_pCore->GetGame()->GetLocalPlayer();

	// Does the graphis even exist?
	if (!pGraphics || !pGraphics->GetDevice())
		return;

	// Do our local player exist and is he spawned?
	if (pPlayerManager && pLocalPlayer && pLocalPlayer->IsSpawned() && CIVScript::IsScreenFadedIn())
	{
		CVector3 vecLocalPedPosition;
		pLocalPlayer->GetPosition(vecLocalPedPosition);

		// Render the player nametags
		for (EntityId i = 0; i < MAX_PLAYERS; i++)
		{
			// Get the active player
			CPlayerEntity * pPlayer = pPlayerManager->GetAt(i);

			// Is the player spawned?
			if (pPlayer && pPlayer->IsSpawned())
			{
				// Is the player on our screen?
				if (!pPlayer->IsOnScreen())
					continue;

				// Get the player position and add the new z position
				CVector3 vecWorldPosition;
				pPlayer->GetPosition(vecWorldPosition);
				vecWorldPosition.fZ += 1.15f;

				//Is this player not within our view range?
				if (sqrt((vecWorldPosition.fX - vecLocalPedPosition.fX)*(vecWorldPosition.fX - vecLocalPedPosition.fX) + (vecWorldPosition.fY - vecLocalPedPosition.fY)*(vecWorldPosition.fY - vecLocalPedPosition.fY)) > 60.0f)
					continue;

				// Convert the position to our screen position
				Vector2 vecScreenPosition;
				if (!CGame::GetScreenPositionFromWorldPosition(vecWorldPosition, vecScreenPosition))
					continue;

				// Set the player name
				CString strString("%s (%d)", pPlayer->GetNick().Get(), i);

				vecScreenPosition.fX -= m_pFont->getTextExtent(CEGUI::String(strString.Get())) / 2;

				// Draw the tag
				g_pCore->GetGUI()->DrawText(strString, CEGUI::Vector2(vecScreenPosition.fX, vecScreenPosition.fY), CEGUI::colour(1.0f, 1.0f, 1.0f, 1.0f), m_pFont); // Issue #48 

				vecScreenPosition.fY += m_pFont->getFontHeight() + BAR_BORDER;

				// Health Box
				g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX - BAR_BORDER, vecScreenPosition.fY - BAR_BORDER, m_pFont->getTextExtent(CEGUI::String(strString.Get())) + BAR_BORDER * 2.0f, BAR_HEIGHT + BAR_BORDER * 2.0f, D3DCOLOR_ARGB(160, 0, 0, 0));

				// Health Background
				g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX, vecScreenPosition.fY, m_pFont->getTextExtent(CEGUI::String(strString.Get())), BAR_HEIGHT, D3DCOLOR_ARGB(255, 139, 0, 0));

				// Health Bar
				g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX, vecScreenPosition.fY, m_pFont->getTextExtent(CEGUI::String(strString.Get())) * (((pPlayer->GetHealth() < 100.0f ? 100.0f : pPlayer->GetHealth()) - 100.0f) / 100.0f), BAR_HEIGHT, D3DCOLOR_ARGB(255, 255, 0, 0));

				if (pPlayer->GetArmour() > 0.0f)
				{
					vecScreenPosition.fY += BAR_HEIGHT + BAR_BORDER + BAR_PADDING;

					// Armour Box
					g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX - BAR_BORDER, vecScreenPosition.fY - BAR_BORDER, m_pFont->getTextExtent(CEGUI::String(strString.Get())) + BAR_BORDER * 2.0f, BAR_HEIGHT + BAR_BORDER * 2.0f, D3DCOLOR_ARGB(160, 0, 0, 0));

					// Armour Background
					g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX, vecScreenPosition.fY, m_pFont->getTextExtent(CEGUI::String(strString.Get())), BAR_HEIGHT, D3DCOLOR_ARGB(255, 169, 169, 169));

					// Armour Bar
					g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX, vecScreenPosition.fY, m_pFont->getTextExtent(CEGUI::String(strString.Get())) * (pPlayer->GetArmour() / 100.0f), BAR_HEIGHT, D3DCOLOR_ARGB(225, 225, 225, 225));
				}
			}
		}
	}
}