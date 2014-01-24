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

#ifndef CPlayerInfo_h
#define CPlayerInfo_h

#define			INVALID_PLAYER_PED			255

#include <Common.h>
#include "../GameCommon.h"

#include "CPlayerPed.h"

_GAME_BEGIN

struct CPlayerInfo_FakeProtectedBuffer 
{
	DWORD	dwMagic;
	int		iSize;
	BYTE	byteData[4];
};

class IVehicle;

class IPlayerInfo
{
public:
	PAD(IPlayerInfo, pad0, 0x4C);          // 000-04C
	char m_szName[20];                      // 04C-060
	// 0x60 = DWORD m_dwFakeWantedLevel;?
	PAD(IPlayerInfo, pad1, 0x434);         // 060-494
	// 0x60 = CPlayerData?
	// (0x60) + 0x380 = wanted level
	DWORD m_dwLastHitPedTime;               // 494-498
	DWORD m_dwLastHitBuildingTime;          // 498-49C
	DWORD m_dwLastHitObjectTime;            // 49C-4A0
	DWORD m_dwLastDroveOnPavementTime;      // 4A0-4A4
	DWORD m_dwLastRanLightTime;             // 4A4-4A8
	DWORD m_dwLastDroveAgainstTrafficTime;  // 4A8-4AC
	PAD(IPlayerInfo, pad2, 0x2E);          // 4AC-4DA  // 0x4BC: int m_ControlStateFlag
	BYTE m_bytePlayerNumber;                // 4DA-4DB
	PAD(IPlayerInfo, pad3, 0x1);           // 4DB-4DC
	DWORD m_dwState;                        // 4DC-4E0 - 2: spawned, 3: dead, 4: arrested
	PAD(IPlayerInfo, pad4, 0x66);          // 4E0-546
	BYTE m_byteNeverGetsTired;              // 546-547
	BYTE m_byteFastReload;                  // 547-548
	BYTE m_byteFireProof;                   // 548-549
	PAD(IPlayerInfo, pad6, 0x1);           // 549-54A
	WORD m_wMaxHealth;                      // 54A-54C
	WORD m_wMaxArmour;                      // 54C-54E
	PAD(IPlayerInfo, pad7, 0x1);           // 54E-54F // Doesn't lose money after jail/arrest?
	BYTE m_byteFreeHealthCareset;           // 54F-550
	BYTE m_byteCanDoDriveBy;                // 550-551
	BYTE m_byteCanBeHassledByGangs;         // 551-552
	PAD(IPlayerInfo, pad8, 0x2);           // 552-554
	DWORD dwFlags1;                         // 554-558 - Bits 0: can use cover, 2: damaged at least one ped, 3: damaged at least one vehicle
	PAD(IPlayerInfo, pad9, 0x4);           // 558-55C
	DWORD m_dwMood;                         // 55C-560
	PAD(IPlayerInfo, pad10, 0x10);         // 560-570
	DWORD m_dwColour;                       // 570-574
	DWORD m_dwTeam;                         // 574-578
	PAD(IPlayerInfo, pad11, 0x8);          // 578-580
	BYTE m_byteNetworkHasDiedRecently;      // 580-581
	PAD(IPlayerInfo, pad12, 0xB);          // 581-58C
	IPlayerPed * m_pPlayerPed;             // 58C-590
	PAD(IPlayerInfo, pad13, 0x4);          // 590-594
	IVehicle * m_pMayOnlyEnterThisVehicle; // 594-598
	PAD(IPlayerInfo, pad14, 0x20);         // 598-5B8
	CPlayerInfo_FakeProtectedBuffer * m_pScore;         // 5B8-5BC
	CPlayerInfo_FakeProtectedBuffer * m_pDisplayScore;  // 5BC-5C0

};

class CPlayerInfo
{
private:
	bool					m_bCreatedByUs;
	IPlayerInfo			* m_pPlayerInfo;

public:
	CPlayerInfo();
	CPlayerInfo(BYTE bytePlayerNumber);
	CPlayerInfo(IPlayerInfo * pPlayerInfo);
	~CPlayerInfo();

	void				SetPlayerInfo(IPlayerInfo * pPlayerInfo);
	IPlayerInfo		* GetPlayerInfo();

	void				SetPlayerNumber(BYTE bytePlayerNumber);
	BYTE				GetPlayerNumber();

	void				SetPlayerPed(IPlayerPed * pPlayerPed);
	IPlayerPed			* GetPlayerPed();

	void				SetName(char * szName);
	char				* GetName();

	void				SetColour(DWORD dwColor);
	DWORD				GetColour();

	void				SetScore(int iScore);
	int					GetScore();

	void				SetDisplayScore(int iScore);
	int					GetDisplayScore();
};

_GAME_END

#endif // CPlayerInfo_h
