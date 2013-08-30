//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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
	PAD(IVPlayerInfo, pad0, 0x4C);
	char m_szName[20];
	PAD(IVPlayerInfo, pad1, 0x434);
	DWORD m_dwLastHitPedTime;
	DWORD m_dwLastHitBuildingTime;
	DWORD m_dwLastHitObjectTime;
	DWORD m_dwLastDroveOnPavementTime;
	DWORD m_dwLastRanLightTime;
	DWORD m_dwLastDroveAgainstTrafficTime;
	PAD(IVPlayerInfo, pad2, 0x2E);
	BYTE m_bytePlayerNumber;
	PAD(IVPlayerInfo, pad3, 0x1);
	DWORD m_dwState;
	PAD(IVPlayerInfo, pad4, 0x66);
	BYTE m_byteNeverGetsTired;
	BYTE m_byteFastReload;
	BYTE m_byteFireProof;
	PAD(IVPlayerInfo, pad6, 0x1);
	WORD m_wMaxHealth;
	WORD m_wMaxArmour;
	PAD(IVPlayerInfo, pad7, 0x1);
	BYTE m_byteFreeHealthCareset;
	BYTE m_byteCanDoDriveBy;
	BYTE m_byteCanBeHassledByGangs;
	PAD(IVPlayerInfo, pad8, 0x2);
	DWORD dwFlags1;
	PAD(IVPlayerInfo, pad9, 0x4);
	DWORD m_dwPlayerMood;
	PAD(IVPlayerInfo, pad10, 0x10);
	DWORD m_dwColour;
	DWORD m_dwTeam;
	PAD(IVPlayerInfo, pad11, 0x8);
	BYTE m_byteNetworkHasDiedRecently;
	PAD(IVPlayerInfo, pad12, 0xB);
	IVPlayerPed * m_pPlayerPed;
	PAD(IVPlayerInfo, pad13, 0x4);
	void * m_pMayOnlyEnterThisVehicle;
	PAD(IVPlayerINfo, pad14, 0x20);
	CIVPlayerInfo_FakeProtectedBuffer * m_pScore;
	CIVPlayerInfo_FakeProtectedBuffer * m_pDisplayScore;
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
};

#endif // CIVPlayerInfo_h