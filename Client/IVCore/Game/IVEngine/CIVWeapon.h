//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVWeapon.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVWeapon_h
#define CIVWeapon_h

#include <IV/IVCommon.h>
#include "CIVWeaponInfo.h"
#include <Hooks\CXLive.h>

class IVaudWeaponAudioEntity
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

class IVWeapon
{
public:
	IVaudWeaponAudioEntity m_audio;     // 00-18
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

class CIVWeapon
{
private:
	IVWeapon * m_pWeapon;

public:
	CIVWeapon(IVWeapon * pWeapon);
	~CIVWeapon();

	void         SetWeapon(IVWeapon * pWeapon) { m_pWeapon = pWeapon; }
	IVWeapon  *  GetWeapon() { return m_pWeapon; }

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

#endif // CIVWeapon_h