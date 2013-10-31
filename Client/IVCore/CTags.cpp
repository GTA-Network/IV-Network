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

#define BAR_HEIGHT 5.0f
#define BAR_BORDER 2.0f
#define BAR_PADDING 4.0f

CTags::CTags()
{

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
	if (pPlayerManager && pLocalPlayer && pLocalPlayer->IsSpawned())
	{
		CVector3 vecLocalHeadPosition;
		CIVScript::GetPedBonePosition(pLocalPlayer->GetScriptingHandle(), CIVScript::ePedBone::BONE_HEAD, 0.0f, 0.0f, 0.0f, &vecLocalHeadPosition);

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

				// Get the player's head position
				CVector3 vecHeadPosition;
				CIVScript::GetPedBonePosition(pPlayer->GetScriptingHandle(), CIVScript::ePedBone::BONE_HEAD, 0.0f, 0.0f, 0.0f, &vecHeadPosition);

				//Is this player not within our view range?
				if (sqrt((vecHeadPosition.fX - vecLocalHeadPosition.fX)*(vecHeadPosition.fX - vecLocalHeadPosition.fX) + (vecHeadPosition.fY - vecLocalHeadPosition.fY)*(vecHeadPosition.fY - vecLocalHeadPosition.fY)) > 60.0f)
					continue;

				vecHeadPosition.fZ += 0.4f;

				// Convert the position to our screen position
				Vector2 vecScreenPosition;
				CIVScript::GetViewportPositionOfCoord(&vecHeadPosition, &vecScreenPosition, 2);

				// Set the player name
				CString strString("%s (%d)", pPlayer->GetNick().Get(), i);
				
				vecScreenPosition.fX -= g_pCore->GetGraphics()->GetStringWidth(strString) / 2;

				// Draw the tag
				g_pCore->GetGraphics()->DrawText(vecScreenPosition.fX, vecScreenPosition.fY, (pPlayer->GetColor() >> 8) | 0xFF000000, 1.0f, DT_NOCLIP, false, strString);

				vecScreenPosition.fY += g_pCore->GetGraphics()->GetFontHeight() + BAR_BORDER;

				// Health Box
				g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX - BAR_BORDER, vecScreenPosition.fY - BAR_BORDER, g_pCore->GetGraphics()->GetStringWidth(strString) + BAR_BORDER * 2.0f, BAR_HEIGHT + BAR_BORDER * 2.0f, D3DCOLOR_ARGB(160, 0, 0, 0));

				// Health Bar
				g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX, vecScreenPosition.fY, g_pCore->GetGraphics()->GetStringWidth(strString) * (((pPlayer->GetHealth() < 100.0f ? 100.0f : pPlayer->GetHealth()) - 100.0f) / 100.0f), BAR_HEIGHT, D3DCOLOR_ARGB(255, 87, 124, 88));

				if (pPlayer->GetArmour() > 0.0f)
				{
					vecScreenPosition.fY += BAR_HEIGHT + BAR_BORDER + BAR_PADDING;

					// Armour Box
					g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX - BAR_BORDER, vecScreenPosition.fY - BAR_BORDER, g_pCore->GetGraphics()->GetStringWidth(strString) + BAR_BORDER * 2.0f, BAR_HEIGHT + BAR_BORDER * 2.0f, D3DCOLOR_ARGB(160, 0, 0, 0));

					// Armour Bar
					g_pCore->GetGraphics()->DrawBox(vecScreenPosition.fX, vecScreenPosition.fY, g_pCore->GetGraphics()->GetStringWidth(strString) * (pPlayer->GetArmour() / 100.0f), BAR_HEIGHT, D3DCOLOR_ARGB(225, 74, 148, 160));
				}
			}
		}
	}
}