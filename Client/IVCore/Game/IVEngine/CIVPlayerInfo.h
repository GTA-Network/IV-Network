//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPlayerInfo.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPlayerInfo_h
#define CIVPlayerInfo_h

#define			INVALID_PLAYER_PED			255

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVPlayerPed.h"

struct CIVPlayerInfo_FakeProtectedBuffer 
{
	DWORD	dwMagic;
	int		iSize;
	BYTE	byteData[4];
};

class IVPlayerInfo {
public:
	PAD(IVPlayerInfo, pad0, 0x4C);          // 000-04C
	char m_szName[20];                      // 04C-060
	// 0x60 = DWORD m_dwFakeWantedLevel;?
	PAD(IVPlayerInfo, pad1, 0x434);         // 060-494
	// 0x60 = CPlayerData?
	// (0x60) + 0x380 = wanted level
	DWORD m_dwLastHitPedTime;               // 494-498
	DWORD m_dwLastHitBuildingTime;          // 498-49C
	DWORD m_dwLastHitObjectTime;            // 49C-4A0
	DWORD m_dwLastDroveOnPavementTime;      // 4A0-4A4
	DWORD m_dwLastRanLightTime;             // 4A4-4A8
	DWORD m_dwLastDroveAgainstTrafficTime;  // 4A8-4AC
	PAD(IVPlayerInfo, pad2, 0x2E);          // 4AC-4DA  // 0x4BC: int m_ControlStateFlag
	BYTE m_bytePlayerNumber;                // 4DA-4DB
	PAD(IVPlayerInfo, pad3, 0x1);           // 4DB-4DC
	DWORD m_dwState;                        // 4DC-4E0 - 2: spawned, 3: dead, 4: arrested
	PAD(IVPlayerInfo, pad4, 0x66);          // 4E0-546
	BYTE m_byteNeverGetsTired;              // 546-547
	BYTE m_byteFastReload;                  // 547-548
	BYTE m_byteFireProof;                   // 548-549
	PAD(IVPlayerInfo, pad6, 0x1);           // 549-54A
	WORD m_wMaxHealth;                      // 54A-54C
	WORD m_wMaxArmour;                      // 54C-54E
	PAD(IVPlayerInfo, pad7, 0x1);           // 54E-54F // Doesn't lose money after jail/arrest?
	BYTE m_byteFreeHealthCareset;           // 54F-550
	BYTE m_byteCanDoDriveBy;                // 550-551
	BYTE m_byteCanBeHassledByGangs;         // 551-552
	PAD(IVPlayerInfo, pad8, 0x2);           // 552-554
	DWORD dwFlags1;                         // 554-558 - Bits 0: can use cover, 2: damaged at least one ped, 3: damaged at least one vehicle
	PAD(IVPlayerInfo, pad9, 0x4);           // 558-55C
	DWORD m_dwMood;                         // 55C-560
	PAD(IVPlayerInfo, pad10, 0x10);         // 560-570
	DWORD m_dwColour;                       // 570-574
	DWORD m_dwTeam;                         // 574-578
	PAD(IVPlayerInfo, pad11, 0x8);          // 578-580
	BYTE m_byteNetworkHasDiedRecently;      // 580-581
	PAD(IVPlayerInfo, pad12, 0xB);          // 581-58C
	IVPlayerPed * m_pPlayerPed;             // 58C-590
	PAD(IVPlayerInfo, pad13, 0x4);          // 590-594
	IVVehicle * m_pMayOnlyEnterThisVehicle; // 594-598
	PAD(IVPlayerInfo, pad14, 0x20);         // 598-5B8
	CIVPlayerInfo_FakeProtectedBuffer * m_pScore;         // 5B8-5BC
	CIVPlayerInfo_FakeProtectedBuffer * m_pDisplayScore;  // 5BC-5C0

};

class CIVPlayerInfo {
private:
	bool					m_bCreatedByUs;
	IVPlayerInfo			* m_pPlayerInfo;

public:
	CIVPlayerInfo();
	CIVPlayerInfo(BYTE bytePlayerNumber);
	CIVPlayerInfo(IVPlayerInfo * pPlayerInfo);
	~CIVPlayerInfo();

	void				SetPlayerInfo(IVPlayerInfo * pPlayerInfo);
	IVPlayerInfo		* GetPlayerInfo();

	void				SetPlayerNumber(BYTE bytePlayerNumber);
	BYTE				GetPlayerNumber();

	void				SetPlayerPed(IVPlayerPed * pPlayerPed);
	IVPlayerPed			* GetPlayerPed();

	void				SetName(char * szName);
	char				* GetName();

	void				SetColour(DWORD dwColor);
	DWORD				GetColour();

	void				SetScore(int iScore);
	int					GetScore();

	void				SetDisplayScore(int iScore);
	int					GetDisplayScore();
};

#endif // CIVPlayerInfo_h