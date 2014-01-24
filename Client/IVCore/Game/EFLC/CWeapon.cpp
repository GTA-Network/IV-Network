//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CWeapon.cpp
// Project: Client.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include "CWeapon.h"
#include <Game/CGame.h>

#include <CCore.h>
extern CCore * g_pCore;

_GAME_BEGIN

CWeapon::CWeapon(IWeapon * pWeapon) :
	m_pWeapon(pWeapon)
{

}

CWeapon::~CWeapon()
{

}

void CWeapon::Initialize(eWeaponType weaponType, DWORD dwAmmo, bool bIsPedWeapon)
{
	IWeapon * pWeapon = m_pWeapon;

	_asm	push bIsPedWeapon;
	_asm	push dwAmmo;
	_asm	push weaponType;
	_asm	mov ecx, pWeapon;
	_asm	call COffsets::FUNC_CWeapon__Initialize;
}

eWeaponType CWeapon::GetType()
{
	if(m_pWeapon)
		return m_pWeapon->m_weaponType;

	return (eWeaponType)0;
}

void CWeapon::SetType(eWeaponType weaponType)
{
	if(m_pWeapon)
		m_pWeapon->m_weaponType = weaponType;
}

eWeaponSlot CWeapon::GetSlot()
{
	if(m_pWeapon)
	{
		CWeaponInfo * pWeaponInfo = g_pCore->GetGame()->GetWeaponInfo(m_pWeapon->m_weaponType);

		if(pWeaponInfo)
			return pWeaponInfo->GetWeaponInfo()->m_slot;
	}

	return WEAPON_SLOT_UNARMED;
}

eWeaponState CWeapon::GetState()
{
	if(m_pWeapon)
		return m_pWeapon->m_weaponState;

	return (eWeaponState)0;
}

void CWeapon::SetState(eWeaponState weaponState)
{
	if(m_pWeapon)
		m_pWeapon->m_weaponState = weaponState;
}

bool CWeapon::IsPedWeapon()
{
	if(m_pWeapon)
		return (m_pWeapon->m_byteIsPedWeapon != 0);

	return false;
}

WORD CWeapon::GetClipSize()
{
	if(m_pWeapon)
	{
		CWeaponInfo * pWeaponInfo = g_pCore->GetGame()->GetWeaponInfo(m_pWeapon->m_weaponType);

		if(pWeaponInfo)
			return pWeaponInfo->GetWeaponInfo()->m_wClipSize;
	}

	return 0;
}

DWORD CWeapon::GetAmmoInClip()
{
	DWORD dwAmmoInClip = 0;

	if(m_pWeapon)
		XLivePBufferGetDWORD(m_pWeapon->m_ammoInClip, 0, &dwAmmoInClip);

	return dwAmmoInClip;
}

void CWeapon::SetAmmoInClip(DWORD dwAmmoInClip)
{
	if(m_pWeapon)
	{
		WORD wClipSize = GetClipSize();

		if(dwAmmoInClip > wClipSize)
			dwAmmoInClip = wClipSize;

		XLivePBufferSetDWORD(m_pWeapon->m_ammoInClip, 0, dwAmmoInClip);
	}
}

DWORD CWeapon::GetAmmoTotal()
{
	DWORD dwAmmoTotal = 0;

	if(m_pWeapon)
		XLivePBufferGetDWORD(m_pWeapon->m_ammoTotal, 0, &dwAmmoTotal);

	return dwAmmoTotal;
}

void CWeapon::SetAmmoTotal(DWORD dwAmmoTotal)
{
	if(m_pWeapon)
	{
		if(dwAmmoTotal > 25000)
			dwAmmoTotal = 25000;

		XLivePBufferSetDWORD(m_pWeapon->m_ammoTotal, 0, dwAmmoTotal);
	}
}

void CWeapon::Reload()
{
	DWORD dwAmmoTotal = GetAmmoTotal();

	if(dwAmmoTotal)
	{
		WORD wClipSize = GetClipSize();

		if(dwAmmoTotal >= wClipSize)
			SetAmmoInClip(wClipSize);
		else
			SetAmmoInClip(dwAmmoTotal);

		SetState(WEAPON_STATE_READY);
	}
	else
		SetState(WEAPON_STATE_OUT_OF_AMMO);
}

_GAME_END