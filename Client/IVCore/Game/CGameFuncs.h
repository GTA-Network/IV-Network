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