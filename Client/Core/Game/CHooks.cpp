//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CHooks.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CHooks.h"
#include	"COffsets.h"
#include	<CCore.h>
#include	<Patcher\CPatcher.h>
#include	<Game/IVEngine/CIVPlayerInfo.h>
#include	"CContextData.h"

extern	CCore	* g_pCore;
IVTask       * ___pTask = NULL;
unsigned int   uiPlayerInfoIndex = 0;
IVPlayerInfo * pReturnedPlayerInfo = NULL;
unsigned int   uiReturnedIndex = 0;
IVPlayerPed  * _pPlayerPed = NULL;
bool           bInvalidIndex = false;
IVPool       * g_pIVPool;
BYTE         * g_pPoolAllocatedMemory;

int				hFile2;
HANDLE			iTexture;
int				v2;// edi@1
signed int		v3;// esi@1
int				v4;// ecx@2
int				v5;// eax@3
int				result;// eax@5
DWORD			dwJump;

_declspec(naked) void TextureSelect_Hook()
{   
	_asm	mov eax, [esp+4];
	_asm	mov iTexture, eax;
	_asm	mov eax, [esp+8];
	_asm	mov hFile2, eax;
	_asm	pushad;

	if(hFile2 < 10000000) 
		CLogFile::Printf("WARNING! TextureSelect has an invalid pointer((Pointer)%p/(File/Type)%s!", hFile2, iTexture);
	else    
		;//CLogFile::Printf("TextureSelect_Hook: (Pointer)%p/(File/Type)%s", hFile2, iTexture);

	dwJump = (g_pCore->GetBase() + 0x639715);

	_asm	popad;
	_asm	push ebx;
	_asm	push esi;
	_asm	push edi;
	_asm	mov edi, ecx;
	_asm	jmp dwJump;
}


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

_declspec(naked) int CEpisodes__IsEpisodeAvaliable_Hook()
{
	_asm	mov eax, [esp+4];
	_asm	test eax, eax;
	_asm	jnz it_not;
	_asm	mov al, 1;
	_asm	retn 4;
	_asm	it_not:;
	_asm	xor al, al;
	_asm	retn 4;
}

void RemoveInitialLoadingScreens()
{
	// Legal, Legal 2, R*, R*N, GTA:IV, ...
	for(int i = 0; i < *(int *)(COffsets::VAR_NumLoadingScreens); ++i)
	{
		if(i <= 4) 
		{
			*(DWORD *)(COffsets::VAR_FirstLoadingScreenDuration + i * 400) = 0;
			*(DWORD *)(COffsets::VAR_FirstLoadingScreenType + i * 400) = 4;
		}
	}
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
		if(!bInvalidIndex)
		{
			CLogFile::Printf("GetLocalPlayerPed Return Is Invalid (Index is %d)", g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex());
			bInvalidIndex = true;
		}
	}
	else
	{
		if(bInvalidIndex)
		{
			CLogFile::Printf("GetLocalPlayerPed Return Is Now Valid");
			bInvalidIndex = false;
		}
	}
	
	return _pPlayerPed;
}


IVPlayerPed * GetPlayerPedFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	// Is the player info pointer valid?
	if(pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else // Player info pointer is invalid, use the local player ped
		_pPlayerPed = GetLocalPlayerPed();

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
	_asm pushad;

	GetLocalPlayerPed();

	_asm	popad;
	_asm	mov eax, _pPlayerPed;
	_asm	retn;
}

_declspec(naked) void GetPlayerPedFromPlayerInfo_Hook()
{
	_asm	mov eax, [esp+4];
	_asm	mov pReturnedPlayerInfo, eax;
	_asm	pushad;

	GetPlayerPedFromPlayerInfo(pReturnedPlayerInfo);

	_asm	popad;
	_asm	mov eax, _pPlayerPed;
	_asm	retn;
}


void CHooks::Intialize()
{
	// Hook CEpisodes::IsEpisodeAvaliable to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_CEpisodes__IsEpisodeAvaliable, (DWORD)CEpisodes__IsEpisodeAvaliable_Hook);

	// Hook GetPlayerInfoFromIndex to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetPlayerInfoFromIndex, (DWORD)GetPlayerInfoFromIndex_Hook);

	// Hook GetIndexFromPlayerInfo to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetIndexFromPlayerInfo, (DWORD)GetIndexFromPlayerInfo_Hook);

	// Hook GetLocalPlayerPed to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetLocalPlayerPed, (DWORD)GetLocalPlayerPed_Hook);

	// Hook CTask::~CTask to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_CTask__Destructor, (DWORD)CTask__Destructor_Hook);

	// Disable initial loading screens
	CPatcher::InstallCallPatch(COffsets::FUNC_RemoveInitialLoadingScreens, (DWORD)RemoveInitialLoadingScreens);

	// Always draw vehicle hazzard lights
	CPatcher::InstallNopPatch(COffsets::PATCH_CVehicle__HazzardLightsOn, 2);

	// Disable loading music
	CPatcher::InstallNopPatch(COffsets::CALL_StartLoadingTune, 5);

	// Hook texture select/generate function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GENERATETEXTURE, (DWORD)TextureSelect_Hook);
}