//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPedWeapons.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPedWeapons_h
#define CIVPedWeapons_h

#include "CIVWeapon.h"
#include "CIVPedWeaponSlot.h"

class IVObject;


class IVPedWeapons
{
public:
	PAD(IVPedWeapons, pad0, 0x18);              // 000-018
	eWeaponSlot m_currentWeaponSlot;            // 018-01C
	PAD(IVPedWeapons, pad1, 0x10);              // 01C-02C
	IVObject * m_pWeaponObject;                 // 02C-030
	PAD(IVPedWeapons, pad2, 0x8);               // 030-038
	IVWeapon * m_pSpecialWeapon;                // 038-03C
	IVPedWeaponSlot m_weapons[WEAPON_SLOT_MAX]; // 03C-0C0
	IVPedWeaponSlot m_weapon;                   // 0C0-0CC
	PAD(IVPedWeapons, pad3, 0xC);               // 0C0-0D8
	BYTE m_byteShootRate;                       // 0D8-0D9
	BYTE m_byteAccuracy;                        // 0D9-0DA
	PAD(IVPedWeapons, pad4, 0x40);              // 0DA-11A
};

class CIVObject;
class CIVPed;

class CIVPedWeapons
{
private:
	IVPedWeapons     * m_pPedWeapons;
	CIVPed           * m_pPed;
	CIVObject        * m_pWeaponObject;
	CIVWeapon        * m_pSpecialWeapon;
	CIVPedWeaponSlot * m_pWeaponSlots[WEAPON_SLOT_MAX];
	CIVPedWeaponSlot * m_pWeapon;

public:
	CIVPedWeapons(IVPedWeapons * pPedWeapons, CIVPed * pPed);
	~CIVPedWeapons();

	void               SetPedWeapons(IVPedWeapons * pPedWeapons) { m_pPedWeapons = pPedWeapons; }
	IVPedWeapons     * GetPedWeapons() { return m_pPedWeapons; }
	void               SetPed(CIVPed * pPed) { m_pPed = pPed; }
	CIVPed           * GetPed() { return m_pPed; }
	CIVWeapon        * GetCurrentWeapon();
	CIVPedWeaponSlot * GetWeapon(eWeaponSlot slot) { return m_pWeaponSlots[slot]; }
	CIVPedWeaponSlot * GetWeapon() { return m_pWeapon; }

	void               GiveWeapon(eWeaponType weaponType, int dwAmmo);
	eWeaponType        GetWeaponInSlot(eWeaponSlot weaponSlot);
	eWeaponSlot        GetCurrentWeaponSlot();
	eWeaponType        GetCurrentWeaponType();
	void               SetCurrentWeaponBySlot(eWeaponSlot weaponSlot);
	void               SetCurrentWeaponByType(eWeaponType weaponType);
	void               RemoveWeapon(eWeaponType weaponType, bool bUnknown = true);
	void               RemoveAllWeapons();
	void               SetCurrentWeaponVisible(bool bVisible);
	DWORD              GetAmmoBySlot(eWeaponSlot weaponSlot);
	DWORD              GetAmmoByType(eWeaponType weaponType);
	void               SetAmmoBySlot(eWeaponSlot weaponSlot, int dwAmmo);
	void               SetAmmoByType(eWeaponType weaponType, int dwAmmo);
	DWORD              GetAmmoInClip();
	void               SetAmmoInClip(DWORD dwAmmoInClip);
};

#endif // CIVPedWeapons_h