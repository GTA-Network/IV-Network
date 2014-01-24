//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CPedWeaponSlot.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CPedWeaponSlot.h"
#include "CPedWeapons.h"
#include "../CGame.h"
#include <CLogFile.h>

#include <CCore.h>
extern CCore * g_pCore;

_GAME_BEGIN

CPedWeaponSlot::CPedWeaponSlot(IPedWeaponSlot * pWeapon, CPedWeapons * pPedWeapons) :
	m_pPedWeaponSlot(pWeapon), 
	m_pPedWeapons(pPedWeapons)
{
}

eWeaponType CPedWeaponSlot::GetType()
{
	if(m_pPedWeaponSlot)
		return m_pPedWeaponSlot->m_type;

	return WEAPON_TYPE_UNARMED;
}

void CPedWeaponSlot::SetAmmo(DWORD dwAmmo)
{
	if(m_pPedWeaponSlot)
	{
		if(dwAmmo > 25000)
			dwAmmo = 25000;

		XLivePBufferSetDWORD(m_pPedWeaponSlot->m_pAmmo, 0, dwAmmo);
	}
}

DWORD CPedWeaponSlot::GetAmmo()
{
	if(m_pPedWeaponSlot)
	{
		DWORD dwAmmo;
		XLivePBufferGetDWORD(m_pPedWeaponSlot->m_pAmmo, 0, &dwAmmo);
		return dwAmmo;
	}

	return 0;
}

void CPedWeaponSlot::Remove()
{
	if(m_pPedWeaponSlot)
	{
		if(m_pPedWeaponSlot->m_byteWeaponModelLoaded)
		{
			CWeaponInfo * pWeaponInfo = g_pCore->GetGame()->GetWeaponInfo(m_pPedWeaponSlot->m_type);

			if(pWeaponInfo)
			{
#if 0
				int iModelIndex = CGame::GetStreaming()->GetModelIndexFromHash(pWeaponInfo->GetWeaponInfo()->m_dwModelHash);

				if(iModelIndex != -1)
				{
					CModelInfo * pModelInfo = g_pCore->GetGame()->GetModelInfo(iModelIndex);

					if(pModelInfo)
						pModelInfo->GetModelInfo()->dwReferenceCount--;
				}
#endif
			}
		}

		m_pPedWeaponSlot->m_byteWeaponModelLoaded = 0;
		m_pPedWeaponSlot->m_type = WEAPON_TYPE_UNARMED;
		SetAmmo(0);
	}
}

void CPedWeaponSlot::SetCurrent()
{
	if(m_pPedWeaponSlot)
		m_pPedWeapons->SetCurrentWeaponByType(m_pPedWeaponSlot->m_type);
}

_GAME_END