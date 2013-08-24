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
#include	<SharedUtility.h>

extern	CCore	* g_pCore;
IVTask       * ___pTask = NULL;
unsigned int   uiPlayerInfoIndex = 0;
IVPlayerInfo * pReturnedPlayerInfo = NULL;
unsigned int   uiReturnedIndex = 0;
IVPlayerPed  * _pPlayerPed = NULL;
bool           g_bInvalidIndex = false;
IVPool       * g_pIVPool;
BYTE         * g_pPoolAllocatedMemory;
DWORD			dwSub7Jmp;
DWORD			dwSub7BCall;
DWORD			dwSub7BJmp;
char			*szFile;
bool			bInitialiseGame = true;
DWORD			dwJumpGame;
int				iFrameCalls = 0;

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

_declspec(naked) void CEpisodes__IsEpisodeAvaliable_Hook()
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

void StartGame_Loading()
{
	DWORD unk_10F8088 = g_pCore->GetBase() + 0x10F8088;
	DWORD sub_5AF930 = g_pCore->GetBase() + 0x5AF930;
	DWORD dword_10F8078 = g_pCore->GetBase() + 0x10F8078;
	DWORD dword_10F805C = g_pCore->GetBase() + 0x10F805C;
	int * v7 = new int(0);
	_asm
	{
		push v7
		mov ecx, unk_10F8088
		call sub_5AF930
	}
	*(DWORD*)dword_10F8078 = *v7;
	*(DWORD*)dword_10F805C = *v7;
	if ( *v7 > 0 )
	{
		DWORD sub_7B2DF0 = g_pCore->GetBase() + 0x7B2DF0;
		_asm
		{
			call sub_7B2DF0
		}
	}
}

void RemoveInitialLoadingScreens()
{
	StartGame_Loading();

	int iLoadScreens = (g_pCore->GetBase() + 0x18A8258);
	int iLoadScreenType = (g_pCore->GetBase() + 0x18A8F48);
	int iLoadScreenDuration = (g_pCore->GetBase() + 0x18A8F40);

	for(int i = 0; i < *(int *)iLoadScreens; ++i)
	{
		if(i < 4)
		{
			*(DWORD *)(iLoadScreenType + i * 400) = 0;
			*(DWORD *)(iLoadScreenDuration + i * 400) = 0;
		}
	}
	
	if(g_pCore->GetGame() && g_pCore->GetGame()->IsUsingEFLCContent()) {
		*(DWORD *)(iLoadScreenDuration + 400) = 1500; // load directx
		*(DWORD *)(iLoadScreenType + 400) = 0;
		*(DWORD *)(iLoadScreenDuration + 1600) = 4500; // logo screen
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
	_asm	pushad;

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

_declspec(naked) void sub_788F30()
{
	_asm
	{
		sub     esp, 0Ch
		pushad
	}
	
	CLogFile::Printf("CALL sub_788F30");
	dwSub7Jmp = (g_pCore->GetBase() + 0x788F33);
	_asm
	{
		popad
		jmp dwSub7Jmp;
	}
}

_declspec(naked) void Sub_7B2740() //7B27A0
{
	dwSub7BCall = (g_pCore->GetBase() + 0x7B27A0);

	_asm
	{
		call dwSub7BCall

		mov eax, [ebp+4]
		mov szFile, eax
		
		pushad
	}

	dwSub7BJmp = (g_pCore->GetBase() + 0x7B27A6);
	CLogFile::Printf("GTA_FOPEN: %s",szFile);

	_asm
	{
		popad
		pop ebp
		jmp [dwSub7BJmp]
	}
}

_declspec(naked) void CFunctionRetnPatch()
{
	_asm
	{
		xor eax, eax
		retn
	}
}

_declspec(naked) void CRASH_625F15_HOOK()
{
	_asm
	{
		test    eax, eax
		jz              keks
		cmp     eax, 100000h
		jl              keks
		mov     edx, [eax]
		push    1
		mov     ecx, edi
		call    edx

keks_patch:
		mov     al, 1
		pop     edi
		pop     esi
		pop     ebp
		pop     ebx
		add     esp, 0Ch
		retn    4
keks:
		pushad
	}

	g_pCore->GetChat()->Output("Prevent crash at 0x625F15");

	_asm
	{
		popad
			jmp keks_patch
	}
}

_declspec(naked) void CGameProcessHook()
{
	if(!bInitialiseGame && iFrameCalls != 300)
	{
		iFrameCalls++;
		dwJumpGame = (g_pCore->GetBase() + 0x402B03);
		_asm
		{
			mov ebp, esp
			jmp dwJumpGame
		}
	}
	else
	{
		iFrameCalls++;
		bInitialiseGame = false;

		// Don't process game this time, just start it(works ram usage increases up to ~1,2GB)
		dwJumpGame = (g_pCore->GetBase() + 0x402BD3);
		_asm
		{
			mov ebp, esp
			jmp dwJumpGame
		}

		BYTE b1 = *(BYTE*)(g_pCore->GetBase() + 0x10C74E1) = 0;
		BYTE b2 = *(BYTE*)(g_pCore->GetBase() + 0x10C79E4) = 1;
		BYTE b3 = *(BYTE*)(g_pCore->GetBase() + 0x119EB14) = 0;
		
		*(DWORD*)(g_pCore->GetBase()+0x10C7854) = 50;
		

		DWORD keks = *(DWORD *)(g_pCore->GetBase() + 0x10F8078); // keks copyright by xforce
		DWORD g_rgsc = *(DWORD *)(g_pCore->GetBase() + 0x172427C);
		DWORD dwFunctionAddress = g_pCore->GetBase() + 0x4205B0;
		int iTime = timeGetTime();
		_asm
		{   
			push 0
			push 1
			push 0
			mov eax, keks
			mov ecx, g_rgsc
			mov edi, iTime
			call dwFunctionAddress
			add esp, 0Ch
		}
	}
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

	// Hook initial loading screens
	CPatcher::InstallCallPatch(COffsets::FUNC_RemoveInitialLoadingScreens, (DWORD)RemoveInitialLoadingScreens);

	// Always draw vehicle hazzard lights
	CPatcher::InstallNopPatch(COffsets::PATCH_CVehicle__HazzardLightsOn, 2);

	// Disable loading music
	CPatcher::InstallNopPatch(COffsets::CALL_StartLoadingTune, 5);

	// Hook texture select/generate function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GENERATETEXTURE, (DWORD)TextureSelect_Hook);

	// This disables some calculate for modelinfo but it seems this is not necessary
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xCBA1F0), (g_pCore->GetBase() + 0xCBA230));

    // this disables a call to a destructor of a member in rageResourceCache [field_244] 
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x625F15), (DWORD)CRASH_625F15_HOOK /*(GetBase() + 0x625F1D)*/);
}