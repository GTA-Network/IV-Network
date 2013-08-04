//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CGameFuncs.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================
 
#include "CGameFuncs.h"
#include <CCore.h>
#include <IV\IVData.h>
#include <IV\CIVScript.h>
#include <Game\COffsets.h>
#include <CString.h>

extern CCore * g_pCore;

bool CGameFunction::IsMenuActive()
{
	DWORD dwMenuActive1 = (COffsets::VAR_MenuActive_1);

	if(dwMenuActive1 == 2 || dwMenuActive1 == 6)
		return false;

	return *(bool *)(COffsets::VAR_MenuActive_2);
}

void CGameFunction::SetTimeOfDay(int iHour, int iMinute)
{
	_asm	push -1;
    _asm	push 0;
    _asm	push iMinute;
    _asm	push iHour;
    _asm    call COffsets::FUNC_SetTimeOfDay;
    _asm    add esp, 10h;
    
    *(DWORD *)(*(DWORD *)(COffsets::VAR_TimeOfDay) + 0x260) = 2;
}

void CGameFunction::SetDayOfWeek(int iDay) // Format: 1(Sunday), 2(Monday) ... 7((FRi)day)
{
	*(DWORD *)(COffsets::VAR_CClock__DayOfWeek) = iDay;
}

void CGameFunction::LockTime(int iHour, int iMinute)
{
	*(DWORD *)(COffsets::VAR_CClock__LockedHour) = iHour;
	*(DWORD *)(COffsets::VAR_CClock__LockedMinute) = iMinute;
}

void CGameFunction::GetTime(int * iHour, int * iMinute)
{
    *iHour = *(DWORD *)(COffsets::VAR_CClock__LockedHour);

    if(*iHour == -1)
		*iHour = *(DWORD *)(COffsets::VAR_CClock__Hour);

    *iMinute = *(DWORD *)(COffsets::VAR_CClock__LockedMinute);

    if(*iMinute == -1)
		*iMinute = *(DWORD *)(COffsets::VAR_CClock__Minute);
}

void CGameFunction::SetWantedLevel(int iLevel)
{
	*(DWORD *)(COffsets::VAR_CurrentWantedLevel) = (DWORD)iLevel;
}

DWORD CGameFunction::GetWantedLevel()
{
	return *(DWORD *)(COffsets::VAR_CurrentWantedLevel);
}

void CGameFunction::SetHudVisible(bool bVisible)
{
	*(bool *)(COffsets::VAR_HudEnabled) = bVisible;
}

bool CGameFunction::IsHudVisible()
{
	return *(bool *)COffsets::VAR_HudEnabled;
}

void CGameFunction::LoadHUD(CString strPath)
{
	const char * szPath = strPath.C_String();
	*(DWORD *)(g_pCore->GetBase() + 0x84841A) = (DWORD)szPath;

	DWORD FUNC_LoadHUD (g_pCore->GetBase()+ 0x848390);
	_asm call FUNC_LoadHUD;

	*(DWORD *)(g_pCore->GetBase() + 0x84841A) = (DWORD)(g_pCore->GetBase() + 0xD5DCF4);
}

void CGameFunction::LoadRadioLogo(CString strPath)
{
	const char * szPath = strPath.C_String();
	*(DWORD *)(g_pCore->GetBase() + 0x822E76) = (DWORD)szPath;

	DWORD FUNC_LoadRadioLogo = (g_pCore->GetBase() + 0x822E30);
	_asm call FUNC_LoadRadioLogo

	*(DWORD *)(g_pCore->GetBase() + 0x822E76) = (DWORD)(g_pCore->GetBase() + 0xD5B7B8);
}

void CGameFunction::SetRadarVisible(bool bVisible)
{
	*(bool *)(COffsets::VAR_RadarVisible) = bVisible;
}

bool CGameFunction::IsRadarVisible()
{
	return *(bool *)COffsets::VAR_RadarVisible;
}

void CGameFunction::SetPlayerNamesVisible(BYTE byteVisible)
{
	if(byteVisible < 2)
		*(BYTE *)(COffsets::VAR_PlayerNamesVisible) = byteVisible;
	else
		*(BYTE *)(COffsets::VAR_PlayerNamesVisible) = 0;
}

BYTE CGameFunction::ArePlayerNamesVisible()
{
	return *(BYTE *)(COffsets::VAR_PlayerNamesVisible);
}

void CGameFunction::SetAreaNamesEnabled(bool bEnabled)
{
	*(bool *)(COffsets::VAR_AreaNamesDisabled) = !bEnabled;
}

bool CGameFunction::AreAreaNamesEnabled()
{
	return !(*(bool *)COffsets::VAR_AreaNamesDisabled);
}

void CGameFunction::ConvertRotationMatrixToEulerAngles(Matrix& matRotation, CVector3& vecRotation)
{
	if(matRotation.vecRight.fZ < 1.0f)
	{
		if(matRotation.vecRight.fZ > -1.0f)
		{
			vecRotation = CVector3(atan2(-matRotation.vecForward.fZ, matRotation.vecUp.fZ), asin(matRotation.vecRight.fZ), 
			atan2(-matRotation.vecRight.fY, matRotation.vecRight.fX));
		}
		else
		{
			vecRotation = CVector3(-atan2(matRotation.vecForward.fX, matRotation.vecForward.fY), -HALF_PI, 0.0f);
		}
	}
	else
	{
		vecRotation = CVector3(atan2(matRotation.vecForward.fX, matRotation.vecForward.fY), HALF_PI, 0.0f);
	}
}

void CGameFunction::ConvertEulerAnglesToRotationMatrix(CVector3 &vecRotation, Matrix &matRotation)
{
	Matrix34 matGameRotation;
	matGameRotation.FromMatrix(&matRotation);
	Matrix34 * pMatGameRotation = &matGameRotation;
	CVector3 * pVecGameRotation = &vecRotation;
	DWORD dwFunc = COffsets::FUNC_CMatrix__ConvertFromEulerAngles;

	_asm push pVecGameRotation;;
	_asm mov ecx, pMatGameRotation;
	_asm call dwFunc;
	
	matGameRotation.ToMatrix(&matRotation);
}

bool CGameFunction::SetScrollBarText(unsigned char ucScrollbar, const char* szText)
{
	if(ucScrollbar > IV_MAX_SCROLLBARS)
		return false;

	if(strlen(szText) >= IV_MAX_SCROLLBAR_TEXT_LENGTH)
		return false;

    if(strlen(szText) == 0)
		return SetScrollBarText(ucScrollbar, " ");

    strncpy((char *)(COffsets::VAR_ScrollBarText + ucScrollbar * 1300), szText, strlen(szText) + 1);
    return true;
}

void CGameFunction::ResetScrollBars(unsigned char ucScrollbar)
{
	for(size_t i = 0; i < (sizeof(scrollBarItems) / sizeof(sScrollBarInfo)); i++)
	{
        if(ucScrollbar == i || ucScrollbar == 0xFF)
		{
			SetScrollBarText(0, scrollBarItems[i].strDefaultText);
		}
	}
}

void CGameFunction::GetScrollBarText(unsigned char ucScrollbar, char* szReturn)
{
    if(ucScrollbar > 7)
    {
		szReturn[0] = '\0';
		return;
    }

    strcpy(szReturn, (char *)(COffsets::VAR_ScrollBarText + ucScrollbar * 1300));
}

void CGameFunction::SetScrollBarColor(unsigned int uiColor)
{
	*(DWORD *)(COffsets::VAR_ScrollBarColor) = ((uiColor >> 8) & 0xFFFFFF) + ((uiColor << 24) & 0xFF000000);
}

unsigned int CGameFunction::GetScrollBarColor()
{
	unsigned int uiColor = *(DWORD *)(COffsets::VAR_ScrollBarColor);
	return ((uiColor << 8) & 0xFFFFFF00) + ((uiColor >> 24) & 0xFF);
}

CString CGameFunction::GetCurrentAreaName()
{
    CString strAreaName;
    char * szAreaName = (char *)(COffsets::VAR_CurrentAreaName);

    for(int i = 0; i < IV_MAX_AREAS; i += 2)
    {
        char c = szAreaName[i];

        if(c == 0)
			break;

        strAreaName += c;
    }

    return strAreaName;
}

CString CGameFunction::GetCurrentStreetName()
{
    CString strStreetName;
    char * szStreetName = (char *)(COffsets::VAR_CurrentStreetName);

	for(int i = 0; i < IV_MAX_STREETS; i += 2)
    {
		char c = szStreetName[i];

		if(c == 0)
			break;

		strStreetName += c;
    }

    return strStreetName;
}

bool CGameFunction::GetScreenPositionFromWorldPosition(CVector3 &vecWorldPosition, Vector2 &vecScreenPosition)
{
	CVector3 * pWorldPosition = &vecWorldPosition;
	Vector2 * pScreenPosition = &vecScreenPosition;

	_asm push pScreenPosition;
	_asm push 2; // game viewport id(2=map/1=mapicon)
	_asm push pWorldPosition;
	_asm call COffsets::FUNC_IVGAME_GETSCREENCOORDSFROM3DCOORDS;
	
	return false;//return g_pCore->GetCamera()->IsOnScreen(vecWorldPosition);
}

void CGameFunction::CreateExplosion(CVector3& vecPosition, unsigned int uiExplosionType, float fRadius, bool bSound, bool bInvisible, float fCameraShake)
{
	return CIVScript::AddExplosion(vecPosition.fX, vecPosition.fY, vecPosition.fZ, uiExplosionType, fRadius, bSound, bInvisible, fCameraShake);
}

unsigned int CGameFunction::CreateFire(CVector3 vecPosition, unsigned int uiStrength, unsigned char ucAllowedGenerations)
{
    return CIVScript::StartScriptFire(vecPosition.fX, vecPosition.fY, vecPosition.fZ, ucAllowedGenerations, uiStrength);
}

bool CGameFunction::DeleteFire(unsigned int uiFire)
{
	CIVScript::RemoveScriptFire(uiFire);
	return true;
}

void * CGameFunction::Alloc(DWORD dwSize)
{
	void * pMemory = NULL;

	_asm push dwSize;
	_asm call COffsets::FUNC_IVGAME_ALLOCMEMORY;
	_asm mov pMemory, eax;
	_asm add esp, 4;

	return pMemory;
}

void CGameFunction::Free(void * pMemory)
{
	_asm push pMemory;
	_asm call COffsets::FUNC_IVGAME_FREEMEMORY;
	_asm add esp, 4;
}

void CGameFunction::ToggleLazlowStation(bool bToggle)
{
	*(BYTE *)(COffsets::FUNC_IVGAME_TOGGLELAZLOW_1) = (bToggle == false);
	*(BYTE *)(COffsets::FUNC_IVGAME_TOGGLELAZLOW_2) = (bToggle == true);
}

void CGameFunction::InitCutscene(char * szCutsceneName, bool bUnknown1, bool bUnknown2)
{
    _asm push bUnknown2;
	_asm push bUnknown1;
	_asm push szCutsceneName;
	_asm call COffsets::FUNC_IVGAME_INITCUTSCENE;
	_asm add esp, 0Ch;
}

void CGameFunction::StopCutscene(char * szCutsceneName)
{
	_asm push szCutsceneName;
	_asm call COffsets::FUNC_IVGAME_STOPCUTSCENE;
	_asm add esp, 4;
}

DWORD CGameFunction::GetNativeAddress(DWORD dwNative)
{
    DWORD dwFunc = COffsets::FUNC_ScrVM__FindNativeAddress;
    DWORD dwNativeFunc = NULL;
    _asm
    {
            push esi
            mov esi, dwNative
            call dwFunc
            pop esi
            mov dwNativeFunc, eax
    }

    if(dwNativeFunc != NULL)
            return dwNativeFunc;

    return -1;
}