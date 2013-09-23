//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CHooks.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CHooks.h"
#include "COffsets.h"
#include <CCore.h>
#include <Patcher/CPatcher.h>
#include <Game/IVEngine/CIVPlayerInfo.h>
#include "CContextData.h"
#include <SharedUtility.h>
#include "CGameFuncs.h"
#include <IV/CIVScript_FunctionInvoke.h>
#include <IV/CIVScriptEnums.h>
#include <IV/CIVScript_FunctionList.h>

extern	CCore	* g_pCore;
IVTask       * ___pTask = NULL;
unsigned int   uiPlayerInfoIndex = 0;
IVPlayerInfo * pReturnedPlayerInfo = NULL;
unsigned int   uiReturnedIndex = 0;
IVPlayerPed  * _pPlayerPed = NULL;
bool           g_bInvalidIndex = false;

_declspec(naked) void CTask__Destructor_Hook()
{
	_asm	mov ___pTask, ecx;
	_asm	pushad;

	if(g_pCore->GetGame()->GetTaskManager())
		g_pCore->GetGame()->GetTaskManager()->HandleTaskDelete(___pTask);

	_asm	popad;
	_asm	push esi;
	_asm	mov esi, ecx;
	_asm	push esi;
	_asm	mov dword ptr [esi], offset COffsets::VAR_CTask__VFTable;
	_asm	jmp COffsets::RETURN_CTask__Destructor;
}

void StartGame_Loading()
{
	int * v7 = new int(0);
	_asm
	{
		push v7
		mov ecx, COffsets::IV_Hook__StartGameLoading_1
		call COffsets::IV_Hook__StartGameLoading_2
	}
	*(DWORD*)COffsets::IV_Hook__StartGameLoading_3 = *v7;
	*(DWORD*)COffsets::IV_Hook__StartGameLoading_4 = *v7;
	if ( *v7 > 0 )
		_asm call COffsets::IV_Hook__StartGameLoading_5;
}

void RemoveInitialLoadingScreens()
{
	StartGame_Loading();

	int iLoadScreens = COffsets::VAR_NumLoadingScreens;
	int iLoadScreenType = COffsets::VAR_FirstLoadingScreenType;
	int iLoadScreenDuration = COffsets::VAR_FirstLoadingScreenDuration;

	for(int i = 0; i < *(int *)iLoadScreens; ++i)
	{
		if(i < 4)
		{
			*(DWORD *)(iLoadScreenType + i * 400) = 0;
			*(DWORD *)(iLoadScreenDuration + i * 400) = 0;
		}
	}

	*(DWORD *)(iLoadScreenDuration + 400) = 5000; // load directx
	*(DWORD *)(iLoadScreenDuration + 1600) = 5000; // logo screen

	/*
	(0)0x0 - 5B - [ - 0xE37048
	(1)0x1 - 31 - 1
	(2)0x2 - 36 - 6
	(3)0x3 - 3A - :
	(4)0x4 - 39 - 9
	(5)0x5 - 5D - ]
	(6)0x6 - 00 - placeholder
	(7)0x7 - 00 - placeholder
	(8)0x8 - 5B - [
	(9)0x9 - 31 - 1
	(10)0xA - 36 - 6
	(11)0xB - 3A - :
	(12)0xC - 39 - 9
	(13)0xD - 5D - ]
	(14)0xE - 00 - placeholder
	(15)0xF - 00 - placeholder
	*/

	/*
	CPatcher::Unprotect(g_pCore->GetBase() + 0xE37048,15);
	*(DWORD *)(g_pCore->GetBase() + (0xE37048 + 0x1)) = 0x31363A39; // 16:9
	*(DWORD *)(g_pCore->GetBase() + (0xE37048 + 0x5)) = 0x5D00005B; // ]*PAD**PAD*[
	*(DWORD *)(g_pCore->GetBase() + (0xE37048 + 0x9)) = 0x31363A39; // 16:9
	*(WORD *)(g_pCore->GetBase() + (0xE37048 + 0x13)) = 0x5D00; // ]*PAD*
	*/
}

IVPlayerInfo * GetPlayerInfoFromIndex(unsigned int uiIndex)
{
	pReturnedPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0);

	if(uiIndex != 0)
	{
		CContextData * pContextInfo = CContextDataManager::GetContextData(uiIndex);

		if(pContextInfo)
			pReturnedPlayerInfo = pContextInfo->GetPlayerInfo()->GetPlayerInfo();
	}

	return pReturnedPlayerInfo;
}

unsigned int GetIndexFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	uiReturnedIndex = 0;

	if(pPlayerInfo != g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0))
	{
		CContextData * pContextInfo = CContextDataManager::GetContextData(pPlayerInfo);

		if(pContextInfo)
			uiReturnedIndex = pContextInfo->GetPlayerInfo()->GetPlayerNumber();
	}

	return uiReturnedIndex;
}

IVPlayerPed * GetLocalPlayerPed()
{
	// Default to the local player ped (If available)
	IVPlayerInfo * pPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0);

	if(pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else
		_pPlayerPed = NULL;

	// Is the local player id valid?
	if(g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex() != -1)
	{
		// Is the player index not the local player?
		if(g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex() != 0)
		{
			// Get the context info for the player index
			CContextData * pContextInfo = CContextDataManager::GetContextData((BYTE)g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex());

			// Is the context info valid?
			if(pContextInfo)
			{
				// Set the player ped to the remote player
				_pPlayerPed = pContextInfo->GetPlayerPed()->GetPlayerPed();
			}
		}
	}

	// Some code to test a theory
	if(_pPlayerPed == NULL)
	{
		if(!g_bInvalidIndex)
		{
			CLogFile::Printf("GetLocalPlayerPed Return Is Invalid (Index is %d)", g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex());
			g_bInvalidIndex = true;
		}
	}
	else
	{
		if(g_bInvalidIndex)
		{
			CLogFile::Printf("GetLocalPlayerPed Return Is Now Valid");
			g_bInvalidIndex = false;
		}
	}

	return _pPlayerPed;
}

_declspec(naked) void GetPlayerInfoFromIndex_Hook()
{
	_asm	mov eax, [esp+4];
	_asm	mov uiPlayerInfoIndex, eax;
	_asm	pushad;

	GetPlayerInfoFromIndex(uiPlayerInfoIndex);

	_asm	popad;
	_asm	mov eax, pReturnedPlayerInfo;
	_asm	retn;
}

_declspec(naked) void GetIndexFromPlayerInfo_Hook()
{
	_asm	mov eax, [esp+4];
	_asm	mov pReturnedPlayerInfo, eax;
	_asm	pushad;

	GetIndexFromPlayerInfo(pReturnedPlayerInfo);

	_asm	popad;
	_asm	mov eax, uiReturnedIndex;
	_asm	retn;
}

_declspec(naked) void GetLocalPlayerPed_Hook()
{
	_asm	pushad;

	GetLocalPlayerPed();

	_asm	popad;
	_asm	mov eax, _pPlayerPed;
	_asm	retn;
}

static int mulPoolSize = 1;
int __stdcall  CPool_hook_chunk(void* this_, int maxObjects, const char* Name, int entrySize);
__declspec(naked) void __stdcall CPool_hook()
{
	_asm	pop eax
	_asm	push ecx
	_asm	push eax
	_asm	jmp CPool_hook_chunk
}

int __stdcall  CPool_hook_chunk(void* this_, int maxObjects, const char* Name, int entrySize)
{
	IVPool *pPool = (IVPool*)this_;

	if(pPool)
	{

		if(!strcmp("PtrNode Double", (const char*)Name)
			|| !strcmp("EntryInfoNodes", Name)
			|| !strcmp("PtrNode Single", Name)
			|| !strcmp("Vehicles", (const char*)Name)
			|| !strcmp("VehicleStruct", Name))
		{
			CLogFile::Printf("Increaing %sPool from %i Objects to %i Objects", Name, maxObjects, maxObjects*mulPoolSize);
			maxObjects *= mulPoolSize;

			pPool->m_dwEntrySize = entrySize;
			pPool->m_pObjects = (BYTE*)CGameFunction::Alloc(entrySize * maxObjects);
			pPool->m_pFlags = (BYTE*)CGameFunction::Alloc(maxObjects);

			pPool->m_bAllocated = 1;
			pPool->m_dwCount = maxObjects;
			pPool->m_nTop = -1;

			int n = 0;
			char flag;
			int v5 = 0;
			BYTE* v8;
			BYTE v7;
			BYTE* v6;
			for(pPool->m_dwUsed = 0; v5 < maxObjects; *v8 = v7 & 0x81 | 1)
			{
				*(pPool->m_pFlags + v5) |= 0x80;
				v6 = pPool->m_pFlags;
				v7 = *(v6 + v5);
				v8 = v5++ +v6;
			}

			CLogFile::Printf("Increased %sPool to %i Objects", Name, maxObjects);
		}
		else
		{
			pPool->m_dwEntrySize = entrySize;
			pPool->m_pObjects = (BYTE*)CGameFunction::Alloc(entrySize * maxObjects);
			pPool->m_pFlags = (BYTE*)CGameFunction::Alloc(maxObjects);

			pPool->m_bAllocated = 1;
			pPool->m_dwCount = maxObjects;
			pPool->m_nTop = -1;

			int n = 0;
			char flag;
			int v5 = 0;
			BYTE* v8;
			BYTE v7;
			BYTE* v6;
			for(pPool->m_dwUsed = 0; v5 < maxObjects; *v8 = v7 & 0x81 | 1)
			{
				*(pPool->m_pFlags + v5) |= 0x80;
				v6 = pPool->m_pFlags;
				v7 = *(v6 + v5);
				v8 = v5++ +v6;
			}
		}
		return (int)pPool;
	}

	return 0;
}

/*
This will multiply the size of the given pools by the value in multi [default: 4]
*/
void CHooks::IncreasePoolSizes(int multi)
{
	mulPoolSize = multi;
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__IncreasePoolSizes, (DWORD)CPool_hook);
}

void CHooks::Intialize()
{
	// Hook GetPlayerInfoFromIndex to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetPlayerInfoFromIndex, (DWORD)GetPlayerInfoFromIndex_Hook);
	
	// Hook GetIndexFromPlayerInfo to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetIndexFromPlayerInfo, (DWORD)GetIndexFromPlayerInfo_Hook);
	
	// Hook GetLocalPlayerPed to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetLocalPlayerPed, (DWORD)GetLocalPlayerPed_Hook);
	
	// Hook CTask::~CTask to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_CTask__Destructor, (DWORD)CTask__Destructor_Hook);
	
	// Hook initial loading screens
	CPatcher::InstallCallPatch(COffsets::FUNC_RemoveInitialLoadingScreens, (DWORD)RemoveInitialLoadingScreens);
	
	// Always draw vehicle hazzard lights
	CPatcher::InstallNopPatch(COffsets::PATCH_CVehicle__HazzardLightsOn, 2);
	
	// Disable loading music
	CPatcher::InstallNopPatch(COffsets::CALL_StartLoadingTune, 5);
}