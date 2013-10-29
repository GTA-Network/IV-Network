//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CGameFuncs.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CGameFuncs_h
#define CGameFuncs_h

#include <Common.h>
#include <Math\CMaths.h>
#include <IV\IVCommon.h>

#ifndef uint32_t
typedef unsigned __int32    uint32_t;
#endif

class CGameFunction {
public:
	static void				SetTimeOfDay(int iHour, int iMinute);
	static DWORD			GetTimeOfDay();
	static void				SetTimeOfDayFormat(DWORD dwTimeOfDay);
	static void				SetDayOfWeek(int iDay);
	static void				LockTime(int iHour, int iMinute);
	static void				GetTime(int * iHour, int * iMinute);
	static void				SetWantedLevel(int iLevel);
	static DWORD			GetWantedLevel();
	static void				SetHudVisible(bool bVisible);
	static bool				IsHudVisible();
	static void				LoadHUD(CString strPath = "common:/DATA/HUD.DAT");
	static void				LoadRadioLogo(CString strPath = "common:/DATA/RadioLogo.DAT");
	static void				SetRadarVisible(bool bVisible);
	static bool				IsRadarVisible();
	static void				SetPlayerNamesVisible(BYTE byteVisible);
	static BYTE				ArePlayerNamesVisible();
	static void				SetAreaNamesEnabled(bool bEnabled);
	static bool				AreAreaNamesEnabled();
	static void				ConvertRotationMatrixToEulerAngles(Matrix &matRotation, CVector3 &vecRotation);
	static void				ConvertEulerAnglesToRotationMatrix(CVector3 &vecRotation, Matrix &matRotation);
	static bool				SetScrollBarText(unsigned char ucScrollbar, const char* szText);
    static void				ResetScrollBars(unsigned char ucScrollbar = 0xFF);
    static void				GetScrollBarText(unsigned char ucScrollbar, char* szReturn);
    static void				SetScrollBarColor(unsigned int uiColor = 0xFF8000FF);
    static unsigned int		GetScrollBarColor();
    static CString			GetCurrentAreaName();
    static CString			GetCurrentStreetName();
    static bool				GetScreenPositionFromWorldPosition(CVector3 &vecWorldPosition, Vector2 &vecScreenPosition);
    static void				CreateExplosion(CVector3& vecPosition, unsigned int uiExplosionType, float fRadius, bool bSound = true, bool bInvisible = false, float fCameraShake = 0.0f);
    static unsigned int		CreateFire(CVector3 vecPosition, unsigned int uiStrength = 1, unsigned char ucAllowedGenerations = 0);
    static bool				DeleteFire(unsigned int uiFire);
    static void				*Alloc(DWORD dwSize);
    static void				Free(void * pMemory);
    static void				ToggleLazlowStation(bool bToggle);
    static void				InitCutscene(char * szCutsceneName, bool bUnknown1 = false, bool bUnknown2 = false);
	static void				StopCutscene(char * szCutsceneName);
	static DWORD            GetNativeAddress(DWORD dwNative);
	static void				LoadWorldAtPosition(CVector3& vecPosition);
	static uint32_t			HashToString(char *szKey, size_t strlength);
	static CString			GetRadioName(BYTE byteRadioIndex);
};

#endif // CGameFuncs_h