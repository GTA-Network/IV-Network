//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTags.cpp
// Project: Client.Core
// Author: ViruZz <blazee14@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CTags.h"
#include "CCore.h"
#include <cstdlib>

extern CCore * g_pCore;

float fWidh = 68.0f;
float fHeight = 10.0f;
CPlayerEntity * pPlayer = NULL;
CString strString;

CTags::CTags()
{
	m_pFont = g_pCore->GetGUI()->GetFont("Arial", 10);
}

CTags::~CTags()
{

}

void CTags::Draw()
{
	CGraphics * pGraphics = g_pCore->GetGraphics();
	CPlayerManager * pPlayerManager = g_pCore->GetGame()->GetPlayerManager();
	CLocalPlayer * pLocalPlayer = g_pCore->GetGame()->GetLocalPlayer();


	// Does the graphis even exist?
	if (!pGraphics || !pGraphics->GetDevice())
		return;

	// Do our local player exist and is he spawned?
	if (pPlayerManager && pLocalPlayer && pLocalPlayer->IsSpawned())
	{
		// Retrieve the local player position
		CVector3 vecLocalPedPosition;
		CVector3 vecWorldPosition;
		Vector2 vecScreenPosition;
		pLocalPlayer->GetPosition(vecLocalPedPosition);

		// Render the player nametags
		for (EntityId i = 0; i < MAX_PLAYERS; i++)
		{
			// Get the active player
			CPlayerEntity * pPlayer = pPlayerManager->GetAt(i);

			// Is the player spawned and the player isn't us?
			if (pPlayer && pPlayer->IsSpawned() && !pPlayer->IsLocalPlayer())
			{
				// Get the player position and add the new z position
				pPlayer->GetPosition(vecWorldPosition);
				vecWorldPosition.fZ += 1.15f;

				// Is the player on our screen?
				if (!pPlayer->IsOnScreen())
					continue;

				// Convert the position to our screen position
				if (!CGame::GetScreenPositionFromWorldPosition(vecWorldPosition, vecScreenPosition))
					continue;

				// Is this player not within our view range?
				if ((vecLocalPedPosition = vecWorldPosition).Length() > 60.0f)
					continue;

				// Set the player name
				CString strString("(%d) %s", i, pPlayer->GetNick().Get());

				// Get the player color
				DWORD dwColor = ((pPlayer->GetColor() >> 8) | 0xFF000000);

				// Get the player health & armour
				unsigned int uiHealth = (pPlayer->GetHealth() - 100);
				unsigned int uiArmour = (pPlayer->GetArmour());

				// Draw the tag as it's done being setup
				DrawTag(strString, uiHealth, uiArmour, vecScreenPosition, dwColor);
			}
		}
	}

}

void CTags::DrawTag(CString strString, unsigned int uiHealth, unsigned int uiArmour, Vector2 vecScreenPosition, DWORD dwColor)
{
	// Get + Calculate the tag position
	CGUI * m_pGUI = g_pCore->GetGUI();
	float fX = (vecScreenPosition.fX - (80 / 2));
	float fY = vecScreenPosition.fY;

	// Draw the background
	g_pCore->GetGUI()->DrawText(strString, CEGUI::Vector2((fX + 1.0f), (fY + 1.0f)), (CEGUI::colour)D3DCOLOR_ARGB(120, 0, 0, 0), "Arial", false, false);

	// Draw the tag
	g_pCore->GetGUI()->DrawText(strString, CEGUI::Vector2(fX, fY), CEGUI::colour(dwColor), "Arial", false, false);

	if (uiHealth < 0)
		uiHealth = 0;

	if (uiHealth > 100)
		uiHealth = 100;

	if (uiArmour < 0)
		uiArmour = 0;

	if (uiArmour > 100)
		uiArmour = 100;

	// Get the correct health and armour values
	float fHealth((11 - 2) * ((float) uiHealth / 100));
	float fArmour((11 - 2) * ((float) uiArmour / 100));

	if (fHealth < 0)
		fHealth = 0;

	if (fArmour < 0)
		fArmour = 0;

	// Get the correct health and armour width
	float fHealthWidth = Math::Clamp<float>(0.0f, (2 + fHealth), 100.0f);
	float fArmourWidth = Math::Clamp<float>(0.0f, (2 + fArmour), 100.0f);

	// Get our Graphics Instance
	CGraphics * pGraphics = g_pCore->GetGraphics();

	// Draw boxes
	if (uiArmour > 2)
	{
		// Background
		pGraphics->DrawBox_2((vecScreenPosition.fX - (80 / 2)), (vecScreenPosition.fY + 18), 80, 11, D3DCOLOR_ARGB(120, 0, 0, 0));

		// Armour background
		pGraphics->DrawBox_2((vecScreenPosition.fX - ((80 / 2) - 2)), (vecScreenPosition.fY + (18 + 2)), (80 - (2 * 2)), (11 - (2 * 2)), D3DCOLOR_ARGB(180, 180, 180, 180));

		// Armour
		pGraphics->DrawBox_2((vecScreenPosition.fX - ((80 / 2) - 2)), (vecScreenPosition.fY + (18 + 2)), fArmourWidth, (11 - (2 * 2)), D3DCOLOR_ARGB(225, 225, 225, 225));

		// Background
		pGraphics->DrawBox_2((vecScreenPosition.fX - (80 / 2)), (vecScreenPosition.fY + 30), 80, 11, D3DCOLOR_ARGB(120, 0, 0, 0));

		// Health background
		pGraphics->DrawBox_2((vecScreenPosition.fX - ((80 / 2) - 2)), (vecScreenPosition.fY + (30+ 2)), (11 - (2 * 2)), (11 - (2 * 2)), D3DCOLOR_ARGB(180, 110, 0, 0));

		// Health
		pGraphics->DrawBox_2((vecScreenPosition.fX - ((80 / 2) - 2)), (vecScreenPosition.fY + (30 + 2)), fHealthWidth, (11 - (2 * 2)), D3DCOLOR_ARGB(180, 255, 0, 0));
	}
	else
	{
		// Background
		pGraphics->DrawBox_2((vecScreenPosition.fX - (80 / 2)), (vecScreenPosition.fY + 18), 80, 11, D3DCOLOR_ARGB(120, 0, 0, 0));

		// Health background
		pGraphics->DrawBox_2((vecScreenPosition.fX - ((80 / 2) - 2)), (vecScreenPosition.fY + (18 + 2)), (80 - (2 * 2)), (11 - (2 * 2)), D3DCOLOR_ARGB(180, 110, 0, 0));

		// Health
		pGraphics->DrawBox_2((vecScreenPosition.fX - ((80 / 2) - 2)), (vecScreenPosition.fY + (18 + 2)), fHealthWidth, (11 - (2 * 2)), D3DCOLOR_ARGB(180, 255, 0, 0));

	}
}