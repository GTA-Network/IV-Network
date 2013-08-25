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
#include "CGameFuncs.h"

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

	_asm	popad;
	_asm	push ebx;
	_asm	push esi;
	_asm	push edi;
	_asm	mov edi, ecx;
	_asm	jmp COffsets::IV_Hook__TextureSelect__JmpBack;
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
		_asm	mov ebp, esp;
		_asm	jmp COffsets::IV_Hook__GameProcess_1;
	}
	else
	{
		iFrameCalls++;
		bInitialiseGame = false;

		// Don't process game this time, just start it(works ram usage increases up to ~1,2GB)
		_asm	mov ebp, esp;
		_asm	jmp COffsets::IV_Hook__GameProcess_2;

		BYTE b1 = *(BYTE*)COffsets::IV_Hook__GameProcess_3 = 0;
		BYTE b2 = *(BYTE*)COffsets::IV_Hook__GameProcess_4 = 1;
		BYTE b3 = *(BYTE*)COffsets::IV_Hook__GameProcess_5 = 0;

		*(DWORD*)(g_pCore->GetBase()+0x10C7854) = 50;


		DWORD keks = *(DWORD *)COffsets::IV_Hook__GameProcess_6; // keks copyright by xforce
		DWORD g_rgsc = *(DWORD *)COffsets::IV_Hook__GameProcess_7;
		int iTime = timeGetTime();

		_asm	push 0;
		_asm	push 1;
		_asm	push 0;
		_asm	mov eax, keks;
		_asm	mov ecx, g_rgsc;
		_asm	mov edi, iTime;
		_asm	call COffsets::IV_Hook__GameProcess_8;
		_asm	add esp, 0Ch;
	}
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

_declspec(naked) void __stdcall SetupPool_Hook()
{
	IVPool *pPool;

	_asm	mov pPool, esi;
	_asm	pushad;

	int entrySize;
	int maxObjects;
	maxObjects = pPool->m_dwCount;
	entrySize = pPool->m_dwEntrySize;
	maxObjects *= mulPoolSize;

	pPool->m_dwEntrySize = entrySize;

	CGameFunction::Free(pPool->m_pObjects);
	CGameFunction::Free(pPool->m_pFlags);

	pPool->m_pObjects = (BYTE*)CGameFunction::Alloc(entrySize * maxObjects);
	pPool->m_pFlags = (BYTE*)CGameFunction::Alloc(maxObjects);

	pPool->m_bAllocated = 1;
	pPool->m_dwCount = maxObjects;
	pPool->m_nTop = -1;

	int n;
	n = 0;
	char flag;
	int v5;
	v5 = 0;
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

	_asm	popad;
	_asm	mov eax, pPool;
	_asm	retn;
}


/*
This will multiply the size of the given pools by the value in multi [default: 4]
*/
void CHooks::IncreasePoolSizes(int multi)
{
	mulPoolSize = multi;
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__IncreasePoolSizes, (DWORD)CPool_hook);
}

DWORD PhysicsEAXHandle;
DWORD IV_GTAPhysicsUpdate;
__declspec(naked) void __stdcall GTAPhysicsUpdate()
{
	_asm mov PhysicsEAXHandle, eax;
	_asm pushad;

	// Check PhysicsUpdate
	if(PhysicsEAXHandle == NULL || (DWORD *)PhysicsEAXHandle == NULL) {
		
		// Failed to get any eax value, exit.
		_asm popad;
		_asm mov eax, [ecx+4];
		_asm push ebx;
		_asm mov ebx, [eax+14h];
		_asm mov PhysicsEAXHandle, ebx;
		_asm pop ebx;
		_asm pushad;

		if(PhysicsEAXHandle == NULL || (WORD)PhysicsEAXHandle == NULL)
		{
			_asm popad;
			_asm push ebx;
			_asm push ebp;
			_asm mov edi, [eax+4];
			_asm mov eax, [ecx+0Ch];
			_asm mov edx, eax;
			_asm mov ebx, esi;
			_asm mov ecx, ebp
			_asm add eax, 50h
			_asm add edx, 40h;
			_asm add edi, 4;
			_asm add ebp, 1
			_asm pop edi;
			_asm pop esi;
			_asm pop esp;
			_asm pop ebx;
			_asm xor eax, eax;
			_asm retn 8;
		}
		else {
			IV_GTAPhysicsUpdate = (g_pCore->GetBase() + 0x0063DD40);

			_asm popad;
			_asm mov eax, [ecx+14h];
			_asm mov edx, [ecx+8];
			_asm push eax;
			_asm push edx;
			_asm call IV_GTAPhysicsUpdate;
			_asm retn;
		}
	}
	else {
		IV_GTAPhysicsUpdate = (g_pCore->GetBase() + 0x0063DD40);

		_asm popad;
		_asm mov eax, [ecx+14h];
		_asm mov edx, [ecx+8];
		_asm push eax;
		_asm push edx;
		_asm call IV_GTAPhysicsUpdate;
		_asm retn;
	}
}

void CHooks::Intialize()
{
	// Hook physics update
	//CPatcher::InstallJmpPatch((g_pCore->)63DD30), (DWORD)IV_GTAPhysicsUpdate, 3);

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
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__UnkownPatch1, (COffsets::IV_Hook__UnkownPatch1 + 0x40));

	// this disables a call to a destructor of a member in rageResourceCache [field_244] 
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__UnkownPatch2, (DWORD)CRASH_625F15_HOOK);
}