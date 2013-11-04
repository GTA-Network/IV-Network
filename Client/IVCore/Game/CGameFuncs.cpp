//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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

struct sScrollBarInfo 
{
	unsigned iID;
	CString strLocation;
	CString strDefaultText;
};

struct sRadioInfo
{
	unsigned uiIndex;
	CString strRadioStationName;
};

sScrollBarInfo scrollBarItems[] = {
	{0, "Financial", IV_SCROLLBAR_1_TEXT},
	{1, "Theatre", IV_SCROLLBAR_2_TEXT},
	{2, "Advertising", IV_SCROLLBAR_3_TEXT},
	{3, "Clock", IV_SCROLLBAR_4_TEXT},
	{4, "URIs", IV_SCROLLBAR_5_TEXT},
	{5, "ComedyClub", IV_SCROLLBAR_6_TEXT},
	{6, "Traffic(Tunnel)", IV_SCROLLBAR_7_TEXT},
	{7, "News", IV_SCROLLBAR_8_TEXT},
};


sRadioInfo radioArray[] = {
	{0, "Liberty City Rock"},
	{1, "K 109 The Studio"},
	{2, "WKTT Radio"},
	{3, "LCHC (Where hardcode lives)"},
	{4, "Self Actualization FM" },
	{5, "Vice City FM" },
	{6, "The Beat 102.7" },
	{7, "San Juan Sounds" },
	{8, "Radio Broker" },
	{9, "RamJam FM" },
	{10, "Vladivostok FM" },
	{11, "Electro-CHOC(Dance)" },
	{12, "Independence FM" },
	{254, "Radio initalising.." },
	{255, "Radio turned off.." },
};

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

DWORD CGameFunction::GetTimeOfDay()
{
	return *(DWORD *)COffsets::VAR_TimeOfDay;
}

void CGameFunction::SetTimeOfDayFormat(DWORD dwTimeOfDay)
{
	*(DWORD *)(*(DWORD *)(COffsets::VAR_TimeOfDay)) = dwTimeOfDay;
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
	*(DWORD *)COffsets::IV_Hook__LoadHUD = (DWORD)szPath;
	_asm	call COffsets::IV_Hook__LoadInternalHud;
	*(DWORD *)COffsets::IV_Hook__LoadHUD = (DWORD)COffsets::IV_Hook__LoadHudHook;
}

void CGameFunction::LoadRadioLogo(CString strPath)
{
	const char * szPath = strPath.C_String();
	*(DWORD *)COffsets::IV_Hook__LoadRadioLogo = (DWORD)szPath;
	_asm	call COffsets::IV_Hook__LoadInternalRadioLogo;
	*(DWORD *)COffsets::IV_Hook__LoadRadioLogo = (DWORD)COffsets::IV_Hook__LoadRadioLogoHook;
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
	DWORD dwFunctionAddress = COffsets::FUNC_CMatrix__ConvertFromEulerAngles;

	_asm	push pVecGameRotation;;
	_asm	mov ecx, pMatGameRotation;
	_asm	call dwFunctionAddress;
	
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

	_asm	push pScreenPosition;
	_asm	push 2; // game viewport id(2=map/1=mapicon)
	_asm	push pWorldPosition;
	_asm	call COffsets::FUNC_IVGAME_GETSCREENCOORDSFROM3DCOORDS;
	
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

	_asm	push dwSize;
	_asm	call COffsets::FUNC_IVGAME_ALLOCMEMORY;
	_asm	mov pMemory, eax;
	_asm	add esp, 4;

	return pMemory;
}

void CGameFunction::Free(void * pMemory)
{
	_asm	push pMemory;
	_asm	call COffsets::FUNC_IVGAME_FREEMEMORY;
	_asm	add esp, 4;
}

void CGameFunction::ToggleLazlowStation(bool bToggle)
{
	*(BYTE *)(COffsets::FUNC_IVGAME_TOGGLELAZLOW_1) = (bToggle == false);
	*(BYTE *)(COffsets::FUNC_IVGAME_TOGGLELAZLOW_2) = (bToggle == true);
}

void CGameFunction::InitCutscene(char * szCutsceneName, bool bUnknown1, bool bUnknown2)
{
    _asm	push bUnknown2;
	_asm	push bUnknown1;
	_asm	push szCutsceneName;
	_asm	call COffsets::FUNC_IVGAME_INITCUTSCENE;
	_asm	add esp, 0Ch;
}

void CGameFunction::StopCutscene(char * szCutsceneName)
{
	_asm	push szCutsceneName;
	_asm	call COffsets::FUNC_IVGAME_STOPCUTSCENE;
	_asm	add esp, 4;
}

DWORD CGameFunction::GetNativeAddress(DWORD dwNative)
{
    DWORD dwNativeFunc = NULL;

    _asm	push esi;
    _asm	mov esi, dwNative;
    _asm	call COffsets::FUNC_ScrVM__FindNativeAddress;
    _asm	pop esi;
    _asm	mov dwNativeFunc, eax;

    if(dwNativeFunc != NULL)
		return dwNativeFunc;

    return (DWORD)0xFFFFFE;
}

void CGameFunction::LoadWorldAtPosition(CVector3& vecPosition)
{
	BYTE * pByteUnknown = &(*(BYTE *)COffsets::IV_Hook__LoadWorldAtPosition);
	CVector3 * pVecPosition = &vecPosition;

	_asm	push pVecPosition;
	_asm	mov ecx, pByteUnknown;
	_asm	call COffsets::FUNC_IVGAME_LOADWORLDATPOSITION;
}

uint32_t CGameFunction::HashToString(char *key, size_t len)
{
   uint32_t hash, i;
   for(hash = i = 0; i < len; ++i)
   {
       hash += key[i];
       hash += (hash << 10);
       hash ^= (hash >> 6);
   }
   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);
   return hash;
}

CString CGameFunction::GetRadioName(BYTE byteRadioIndex)
{
	for(size_t i = 0; i < (sizeof(radioArray) / sizeof(sRadioInfo)); i++)
		if(radioArray[i].uiIndex == byteRadioIndex)
			return radioArray[i].strRadioStationName;

	return CString("Unkown radio station.. %d",byteRadioIndex);
}