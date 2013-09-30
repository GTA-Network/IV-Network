//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPedWeaponSlot.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPedWeaponSlot_h
#define CIVPedWeaponSlot_h

#include <IV/IVCommon.h>
#include "CIVWeaponInfo.h"
#include <Hooks\CXLive.h>

class IVPedWeaponSlot
{
public:
	eWeaponType           m_type;                  // 00-04
	FakeProtectedBuffer * m_pAmmo;                 // 04-08
	BYTE                  m_byteWeaponModelLoaded; // 08-09
	PAD(IVPedWeaponSlot, pad0, 3);                 // 09-0C
};

class CIVPedWeapons;

class CIVPedWeaponSlot
{
private:
	IVPedWeaponSlot * m_pPedWeaponSlot;
	CIVPedWeapons   * m_pPedWeapons;

public:
	CIVPedWeaponSlot(IVPedWeaponSlot * pWeapon, CIVPedWeapons * pPedWeapons);

	void              SetWeaponSlot(IVPedWeaponSlot * pWeaponSlot) { m_pPedWeaponSlot = pWeaponSlot; }
	IVPedWeaponSlot * GetWeaponSlot() { return m_pPedWeaponSlot; }
	void              SetPedWeapons(CIVPedWeapons * pPedWeapons) { m_pPedWeapons = pPedWeapons; }
	CIVPedWeapons   * GetPedWeapons() { return m_pPedWeapons; }

	eWeaponType       GetType();
	void              SetAmmo(DWORD dwAmmo);
	DWORD             GetAmmo();
	void              Remove();
	void              SetCurrent();
};

#endif // CIVPedWeaponSlot_h