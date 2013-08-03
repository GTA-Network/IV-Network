//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CGameFuncs.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CGameFuncs.h"
#include <CCore.h>

#include <Game\COffsets.h>
#include <CString.h>
#include <Windows.h>


namespace CGameFunction
{
	extern CCore * g_pCore;

	bool IsMenuActive()
	{
		DWORD dwMenuActive1 = (COffsets::VAR_MenuActive_1);

		if(dwMenuActive1 == 2 || dwMenuActive1 == 6)
			return false;

		return *(bool *)(COffsets::VAR_MenuActive_2);
	}

	void SetTimeOfDay(int iHour, int iMinute)
	{
		DWORD dwFunc = COffsets::FUNC_SetTimeOfDay;
        _asm
        {
                push -1
                push 0
                push uMinute
                push uHour
                call dwFunc
                add esp, 10h
        }
        *(DWORD *)(*(DWORD *)(COffsets::VAR_TimeOfDay) + 0x260) = 2;
	}

	void SetDayOfWeek(int iDay) // Format: 1(Sunday), 2(Monday) ... 7((FRi)day)
	{
		*(DWORD *)(COffsets::VAR_CClock__DayOfWeek) = iDay;
	}

	void LockTime(int iHour, int iMinute)
	{
		*(DWORD *)(COffsets::VAR_CClock__LockedHour) = iHour;
		*(DWORD *)(COffsets::VAR_CClock__LockedMinute) = iMinute;
	}

	void GetTime(int * iHour, int * iMinute)
	{
        *iHour = *(DWORD *)(COffsets::VAR_CClock__LockedHour);

        if(*iHour == -1)
			*iHour = *(DWORD *)(COffsets::VAR_CClock__Hour);

        *iMinute = *(DWORD *)(COffsets::VAR_CClock__LockedMinute);

        if(*iMinute == -1)
			*iMinute = *(DWORD *)(COffsets::VAR_CClock__Minute);
	}

	void SetWantedLevel(int iLevel)
	{
		*(DWORD *)(COffsets::VAR_CurrentWantedLevel) = (DWORD)iLevel;
	}

	DWORD GetWantedLevel()
	{
		return *(DWORD *)(COffsets::VAR_CurrentWantedLevel);
	}

	void SetHudVisible(bool bVisible)
	{
		*(bool *)(COffsets::VAR_HudEnabled) = bVisible;
	}

	bool IsHudVisible()
	{
		return *(bool *)COffsets::VAR_HudEnabled;
	}

	void LoadHUD(CString strPath = "common:/DATA/HUD.DAT")
	{
		const char * szPath = strPath.C_String();
		*(DWORD *)(g_pCore->GetBase() + 0x84841A) = (DWORD)szPath;

		DWORD FUNC_LoadHUD (g_pCore->GetBase()+ 0x848390);
		_asm call FUNC_LoadHUD;

		*(DWORD *)(g_pCore->GetBase() + 0x84841A) = (DWORD)(g_pCore->GetBase() + 0xD5DCF4);
	}

	void LoadRadioLogo(CString strPath = "common:/DATA/RadioLogo.DAT")
	{
		const char * szPath = strPath.C_String();
		*(DWORD *)(g_pCore->GetBase() + 0x822E76) = (DWORD)szPath;

		DWORD FUNC_LoadRadioLogo = (g_pCore->GetBase() + 0x822E30);
		_asm call FUNC_LoadRadioLogo

		*(DWORD *)(g_pCore->GetBase() + 0x822E76) = (DWORD)(g_pCore->GetBase() + 0xD5B7B8);
	}

	void SetRadarVisible(bool bVisible)
	{
		*(bool *)(COffsets::VAR_RadarVisible) = bVisible;
	}

	bool IsRadarVisible()
	{
		return *(bool *)COffsets::VAR_RadarVisible;
	}

	void SetPlayerNamesVisible(BYTE byteVisible)
	{
		if(byteVisible < 2)
			*(BYTE *)(COffsets::VAR_PlayerNamesVisible) = byteVisible;
		else
			*(BYTE *)(COffsets::VAR_PlayerNamesVisible) = 0;
	}

	BYTE ArePlayerNamesVisible()
	{
		return *(BYTE *)(COffsets::VAR_PlayerNamesVisible);
	}

	void SetAreaNamesEnabled(bool bEnabled)
	{
		*(bool *)(COffsets::VAR_AreaNamesDisabled) = !bEnabled;
	}

	bool AreAreaNamesEnabled()
	{
		return !(*(bool *)COffsets::VAR_AreaNamesDisabled);
	}
};

#endif // CGameFuncs_h