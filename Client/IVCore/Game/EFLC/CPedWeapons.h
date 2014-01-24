/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CPedWeapons_h
#define CPedWeapons_h

#include "../GameCommon.h"
#include "CWeapon.h"
#include "CPedWeaponSlot.h"

_GAME_BEGIN

class IObject;


#pragma pack(1)
class IPedWeapons
{
public:
	PAD(IPedWeapons, pad0, 0x18);              // 000-018
	eWeaponSlot m_currentWeaponSlot;            // 018-01C
	PAD(IPedWeapons, pad1, 0x10);              // 01C-02C
	IObject * m_pWeaponObject;                 // 02C-030
	PAD(IPedWeapons, pad2, 0x8);               // 030-038
	IWeapon * m_pSpecialWeapon;                // 038-03C
	IPedWeaponSlot m_weapons[WEAPON_SLOT_MAX]; // 03C-0C0
	IPedWeaponSlot m_weapon;                   // 0C0-0CC
	PAD(IPedWeapons, pad3, 0xC);               // 0C0-0D8
	BYTE m_byteShootRate;                       // 0D8-0D9
	BYTE m_byteAccuracy;                        // 0D9-0DA
	PAD(IPedWeapons, pad4, 0x40);              // 0DA-11A
};
#pragma pack()

class CObject;
class CPed;

class CPedWeapons
{
private:
	IPedWeapons     * m_pPedWeapons;
	CPed           * m_pPed;
	CObject        * m_pWeaponObject;
	CWeapon        * m_pSpecialWeapon;
	CPedWeaponSlot * m_pWeaponSlots[WEAPON_SLOT_MAX];
	CPedWeaponSlot * m_pWeapon;

public:
	CPedWeapons(IPedWeapons * pPedWeapons, CPed * pPed);
	~CPedWeapons();

	void               SetPedWeapons(IPedWeapons * pPedWeapons) { m_pPedWeapons = pPedWeapons; }
	IPedWeapons     * GetPedWeapons() { return m_pPedWeapons; }
	void               SetPed(CPed * pPed) { m_pPed = pPed; }
	CPed           * GetPed() { return m_pPed; }
	CWeapon        * GetCurrentWeapon();
	CPedWeaponSlot * GetWeapon(eWeaponSlot slot) { return m_pWeaponSlots[slot]; }
	CPedWeaponSlot * GetWeapon() { return m_pWeapon; }

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

_GAME_END

#endif // CPedWeapons_h
