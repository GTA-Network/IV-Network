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
		g_pCore->GetGame()->ThrowInternalException(COffsets::FUNC_GENERATETEXTURE, 0xC0000005);
	
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

int Thread_a1;
int Thread_a2;
signed int Thread_ThreadId;
int Thread_iPriority;
char *Thread_a5;
char *Thread_a6;
signed int GTA_CreateThreadHook(int a1, int a2, signed int ThreadId, int iPriority, const char *a5, char a6)
{
	signed int v6; // edi@1
	LPVOID v7; // esi@5
	void *v8; // eax@5
	HANDLE v9; // eax@5
	void *v10; // edi@5
	signed int result; // eax@6

	DWORD dwThreadPatchAdd;
	char * hThreadName;
	DWORD dwThreadJmpBack;
	LPVOID lpParameter = *(LPVOID *)(g_pCore->GetBase() + 0x16A9A3C);
	DWORD dword_16A9774 = (g_pCore->GetBase() + 0x16A9774);
	DWORD sub_452030 = (g_pCore->GetBase() + 0x452030);
	void* sub_452350 = *(VOID **)(g_pCore->GetBase() + 0x452350);
	DWORD dword_16A9A38 = (g_pCore->GetBase() + 0x16A9A38);
	void* sub_452170 = *(VOID **)(g_pCore->GetBase() + 0x452170);


	v6 = ThreadId;
	if((unsigned int)ThreadId < 0x4000)
		v6 = 16384;

	_asm push dword_16A9774;
	_asm call sub_452030;

	if(!dword_16A9774)
		*(void **)(sub_452350);

	v7 = lpParameter;

	v8 = *(void **)lpParameter;
	--dword_16A9A38;
	
	lpParameter = v8;
	dword_16A9774 = 0;

	*(DWORD *)v7 = a1;
	*((DWORD *)v7 + 1) = a2;
	*((DWORD *)v7 + 2) = *(DWORD *)(*(DWORD *)__readfsdword(44) + 8);

	ThreadId = 0;
	v9 = CreateThread(0, v6, (LPTHREAD_START_ROUTINE)sub_452170, v7, 4u, (LPDWORD)&ThreadId);

	v10 = v9;
	
	if(v9) {
		SetThreadPriority(v9, iPriority);
		SetThreadPriorityBoost(v10, 1);

		if(a6)
			ResumeThread(v10);
		result = (signed int)v10;
	}
	else
	{
		*(DWORD *)v7 = (DWORD)lpParameter;
		++dword_16A9A38;
		lpParameter = v7;
		result = -1;
	}
	return result;
}

signed int uiResult;
_declspec(naked) signed int GTA_CreateThread()
{
	// Grab function paramenters
	_asm push ebp;
	_asm mov ebp, esp;
	_asm push esi;
	_asm push edi;
	_asm mov eax, [ebp+4];
	_asm mov Thread_a1, eax;
	_asm mov eax, [ebp+8];
	_asm mov Thread_a2, eax;
	_asm mov eax, [ebp+0Ch];
	_asm mov Thread_ThreadId, eax;
	_asm mov eax, [ebp+10h];
	_asm mov Thread_iPriority, eax;
	_asm mov eax, [ebp+18h];
	_asm mov Thread_a5, eax;
	_asm mov eax, [ebp+14h];
	_asm mov Thread_a6, eax;

	CLogFile::Printf("GTA_CreateThread: %d, %d, %d, %d, %s, %s",Thread_a1, Thread_a2, Thread_ThreadId, Thread_iPriority, Thread_a5, Thread_a6);

	uiResult = GTA_CreateThreadHook(Thread_a1, Thread_a2, Thread_ThreadId, Thread_iPriority, Thread_a5, *Thread_a6);
	
	_asm mov eax, uiResult;
	_asm pop esi;
	_asm pop edi;
	_asm retn;
}
void log(const char *a1, ...)
{
	CLogFile::Printf("%s", 1);
}

void GTA_LOG(DWORD a1, int a2, DWORD a3 = NULL, DWORD a4 = NULL, ...)
{
	// Print for a3
	va_list vaArgs;
	char szBuffer[2048];
	va_start(vaArgs, a3);
	vsnprintf_s(szBuffer, sizeof(szBuffer), (char *)a3, vaArgs);
	va_end(vaArgs);

	// Print for a4
	vaArgs;
	szBuffer[2048];
	va_start(vaArgs, a4);
	vsnprintf_s(szBuffer, sizeof(szBuffer), (char *)a4, vaArgs);
	va_end(vaArgs);

	log((const char *)(strlen((char *)a3) != 0 ? a3 : a4));
}

DWORD dwJumpBackChoose;
int iCheck = 0;
_declspec(naked) void Choose()
{
	_asm mov eax, esi;
	_asm mov iCheck, eax;
	_asm pushad;

	if(iCheck > 2)
	{
		_asm popad;
		_asm pop ebx;
		_asm pop edi;
		_asm pop esi;
		_asm pop ebx;
		_asm retn;
	}

	dwJumpBackChoose = (g_pCore->GetBase() + 0x408DC1);
	_asm popad;
	_asm add esi, 1;
	_asm jmp [dwJumpBackChoose];
}

void CHooks::Intialize()
{
	// Hook physics update
	//CPatcher::InstallJmpPatch((g_pCore->)63DD30), (DWORD)IV_GTAPhysicsUpdate, 3);
	
	// Hook CEpisodes::IsEpisodeAvaliable to use our own function
	//CPatcher::InstallJmpPatch(COffsets::FUNC_CEpisodes__IsEpisodeAvaliable, (DWORD)CEpisodes__IsEpisodeAvaliable_Hook);
	
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

	// Hook gta_createthread to use our own function 
	//CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x452210),(DWORD)GTA_CreateThread,1);

	// Hook GTA IV dev log
	//CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xBD6730), (DWORD)GTA_LOG, 1);
}