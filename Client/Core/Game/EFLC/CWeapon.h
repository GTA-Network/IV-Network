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

#ifndef CWeapon_h
#define CWeapon_h

#include "../GameCommon.h"

#include "CWeaponInfo.h"
#include <Hooks\CXLive.h>

_GAME_BEGIN

class IaudWeaponAudioEntity
{
public:
	DWORD m_dwVFTable;                      // 00-04
	WORD m4;                                // 04-06
	PAD(IVaudWeaponAudioEntity, pad0, 0x2); // 06-08
	eWeaponType m_weaponType;               // 08-0C
	DWORD mC;                               // 0C-10
	DWORD m10;                              // 10-14
	DWORD m_dwHash;                         // 14-18
};

enum eWeaponState
{
	WEAPON_STATE_READY,
	WEAPON_STATE_RELOADING = 2,
	WEAPON_STATE_OUT_OF_AMMO = 4
};

class IWeapon
{
public:
	IaudWeaponAudioEntity m_audio;     // 00-18
	eWeaponType m_weaponType;           // 18-1C
	eWeaponState m_weaponState;         // 1C-20
	DWORD m20;                          // 20-24
	BYTE m_byteIsPedWeapon;             // 24-25
	PAD(IVWeapon, pad0, 0x2B);          // 25-50
	BYTE m50;                           // 50-51
	PAD(IVWeapon, pad1, 0x3);           // 51-54
	DWORD m54;                          // 54-58
	BYTE m58;                           // 58-59
	PAD(IVWeapon, pad2, 0x3);           // 59-5C
	FakeProtectedBuffer * m_ammoInClip; // 5C-60
	FakeProtectedBuffer * m_ammoTotal;  // 60-64
	PAD(IVWeapon, pad3, 0xC);           // 64-70
};

class CWeapon
{
private:
	IWeapon * m_pWeapon;

public:
	CWeapon(IWeapon * pWeapon);
	~CWeapon();

	void         SetWeapon(IWeapon * pWeapon) { m_pWeapon = pWeapon; }
	IWeapon  *  GetWeapon() { return m_pWeapon; }

	void         Initialize(eWeaponType weaponType, DWORD dwAmmo, bool bIsPedWeapon);
	eWeaponType  GetType();
	void         SetType(eWeaponType weaponType);
	eWeaponSlot  GetSlot();
	eWeaponState GetState();
	void         SetState(eWeaponState weaponState);
	bool         IsPedWeapon();
	WORD         GetClipSize();
	DWORD        GetAmmoInClip();
	void         SetAmmoInClip(DWORD dwAmmoInClip);
	DWORD        GetAmmoTotal();
	void         SetAmmoTotal(DWORD dwAmmoTotal);
	void         Reload();
};

_GAME_END

#endif // CWeapon_h
