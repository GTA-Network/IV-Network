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