//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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

class CHookDummy
{
public:
	void __thiscall loadEbisodes();
};

extern	CCore* g_pCore;

IVTask       * ___pTask = NULL;
_declspec(naked) void CTask__Destructor_Hook()
{
	_asm	mov ___pTask, ecx;
	_asm	pushad;

	if (g_pCore->GetGame()->GetTaskManager())
		g_pCore->GetGame()->GetTaskManager()->HandleTaskDelete(___pTask);

	_asm	popad;
	_asm	push esi;
	_asm	mov esi, ecx;
	_asm	push esi;
	_asm	push eax;
	_asm	mov eax, COffsets::VAR_CTask__VFTable;
	_asm	mov dword ptr[esi], eax;
	_asm	pop eax;
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
	*(DWORD*) COffsets::IV_Hook__StartGameLoading_3 = *v7;
	*(DWORD*) COffsets::IV_Hook__StartGameLoading_4 = *v7;
	if (*v7 > 0)
		_asm call COffsets::IV_Hook__StartGameLoading_5;
}

void RemoveLoadingScreens()
{
	StartGame_Loading();

	int iLoadScreens = COffsets::VAR_NumLoadingScreens;
	int iLoadScreenType = COffsets::VAR_FirstLoadingScreenType;
	int iLoadScreenDuration = COffsets::VAR_FirstLoadingScreenDuration;

	for (int i = 0; i < *(int *) iLoadScreens; ++i)
	{
		*(DWORD *) (iLoadScreenType + i * 400) = 0;
		*(DWORD *) (iLoadScreenDuration + i * 400) = 0;
	}
}

IVPlayerInfo * pReturnedPlayerInfo = NULL;
IVPlayerInfo * GetPlayerInfoFromIndex(unsigned int uiIndex)
{
	pReturnedPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0);

	if (uiIndex != 0)
	{
		CContextData * pContextInfo = CContextDataManager::GetContextData(uiIndex);

		if (pContextInfo)
			pReturnedPlayerInfo = pContextInfo->GetPlayerInfo()->GetPlayerInfo();
	}

	return pReturnedPlayerInfo;
}

unsigned int   uiReturnedIndex = 0;
unsigned int GetIndexFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	uiReturnedIndex = 0;

	if (pPlayerInfo != g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0))
	{
		CContextData * pContextInfo = CContextDataManager::GetContextData(pPlayerInfo);

		if (pContextInfo)
			uiReturnedIndex = pContextInfo->GetPlayerInfo()->GetPlayerNumber();
	}

	return uiReturnedIndex;
}

IVPlayerPed  * _pPlayerPed = NULL;
IVPlayerPed * GetLocalPlayerPed()
{
	// Default to the local player ped (If available)
	IVPlayerInfo * pPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0);

	if (pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else
		_pPlayerPed = NULL;

	// Is the local player id valid?
	if (g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex() != -1)
	{
		// Is the player index not the local player?
		if (g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex() != 0)
		{
			// Get the context info for the player index
			CContextData * pContextInfo = CContextDataManager::GetContextData((BYTE) g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex());

			// Is the context info valid?
			if (pContextInfo)
			{
				// Set the player ped to the remote player
				_pPlayerPed = pContextInfo->GetPlayerPed()->GetPlayerPed();
			}
		}
	}

	return _pPlayerPed;
}

IVPlayerPed * GetPlayerPedFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	// Is the player info pointer valid?
	if (pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else // Player info pointer is invalid, use the local player ped
		_pPlayerPed = GetLocalPlayerPed();

	return _pPlayerPed;
}


unsigned int   uiPlayerInfoIndex = 0;
_declspec(naked) void GetPlayerInfoFromIndex_Hook()
{
	_asm	mov eax, [esp + 4];
	_asm	mov uiPlayerInfoIndex, eax;
	_asm	pushad;

	GetPlayerInfoFromIndex(uiPlayerInfoIndex);

	_asm	popad;
	_asm	mov eax, pReturnedPlayerInfo;
	_asm	retn;
}

_declspec(naked) void GetIndexFromPlayerInfo_Hook()
{
	_asm	mov eax, [esp + 4];
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
	_asm	mov eax, [esp + 4];
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

bool			bInitialiseGame = true;
int				iFrameCalls = 0;
_declspec(naked) void CGameProcessHook()
{
	if (!bInitialiseGame && iFrameCalls != 300)
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

		*(BYTE*) COffsets::IV_Hook__GameProcess_3 = 0;
		*(BYTE*) COffsets::IV_Hook__GameProcess_4 = 1;
		*(BYTE*) COffsets::IV_Hook__GameProcess_5 = 0;

		*(DWORD*) (g_pCore->GetBase() + 0x10C7854) = 50;


		DWORD keks = *(DWORD *) COffsets::IV_Hook__GameProcess_6; // keks copyright by xforce
		DWORD g_rgsc = *(DWORD *) COffsets::IV_Hook__GameProcess_7;
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
	IVPool *pPool = (IVPool*) this_;

	if (pPool)
	{

		if (!strcmp("PtrNode Double", (const char*) Name)
			|| !strcmp("EntryInfoNodes", Name)
			|| !strcmp("PtrNode Single", Name)
			|| !strcmp("Vehicles", (const char*) Name)
			|| !strcmp("VehicleStruct", Name))
		{
			CLogFile::Printf("Increaing %sPool from %i Objects to %i Objects", Name, maxObjects, maxObjects*mulPoolSize);
			maxObjects *= mulPoolSize;

			pPool->m_dwEntrySize = entrySize;
			pPool->m_pObjects = (BYTE*) CGameFunction::Alloc(entrySize * maxObjects);
			pPool->m_pFlags = (BYTE*) CGameFunction::Alloc(maxObjects);

			pPool->m_bAllocated = 1;
			pPool->m_dwCount = maxObjects;
			pPool->m_nTop = -1;

			int n = 0;
			int v5 = 0;
			BYTE* v8;
			BYTE v7;
			BYTE* v6;
			for (pPool->m_dwUsed = 0; v5 < maxObjects; *v8 = v7 & 0x81 | 1)
			{
				*(pPool->m_pFlags + v5) |= 0x80;
				v6 = pPool->m_pFlags;
				v7 = *(v6 + v5);
				v8 = v5++ + v6;
			}

			CLogFile::Printf("Increased %sPool to %i Objects", Name, maxObjects);
		}
		else
		{
			pPool->m_dwEntrySize = entrySize;
			pPool->m_pObjects = (BYTE*) CGameFunction::Alloc(entrySize * maxObjects);
			pPool->m_pFlags = (BYTE*) CGameFunction::Alloc(maxObjects);

			pPool->m_bAllocated = 1;
			pPool->m_dwCount = maxObjects;
			pPool->m_nTop = -1;

			int n = 0;
			int v5 = 0;
			BYTE* v8;
			BYTE v7;
			BYTE* v6;
			for (pPool->m_dwUsed = 0; v5 < maxObjects; *v8 = v7 & 0x81 | 1)
			{
				*(pPool->m_pFlags + v5) |= 0x80;
				v6 = pPool->m_pFlags;
				v7 = *(v6 + v5);
				v8 = v5++ + v6;
			}
		}
		return (int) pPool;
	}

	return 0;
}

/*
This will multiply the size of the given pools by the value in multi [default: 4]
*/
void CHooks::IncreasePoolSizes(int multi)
{
	mulPoolSize = multi;
	//CPatcher::InstallJmpPatch(COffsets::IV_Hook__IncreasePoolSizes, (DWORD)CPool_hook); Balika011: this is why outlined?
}

#ifdef GTAV_MAP
Vector2 * v12;
Vector2 * pViewportSize = new Vector2();
float center;
int bAbsolut;

#define MIN_X 0.025f
#define MAX_X 0.975f
#define MIN_Y 0.025f
#define MAX_Y 0.975f
#define ZERO 0.0f
float fOriginalX;
float fOriginalY;

void _declspec(naked) Keks()
{
	_asm	mov v12, edx;
	_asm	push eax; get absolute flag
	_asm	mov eax, [ebp + 14h]; 3th parameter
	_asm	mov bAbsolut, eax;
	_asm	pop eax;

	fOriginalX = v12->fX;
	fOriginalY = v12->fY;

	// Calculate and check our coordinates 
	if (!bAbsolut) {

		if (v12->fX < MAX_X && v12->fX > MIN_X) { // Check if the X axis is smaller than 1, but still positive
			if (v12->fY < MAX_Y && v12->fY > MIN_Y) // Check if the Y Acis is smaller than 1, but still positive
			{
				goto out; // Let GTA calc the position on itself
			}
			else {
				if (v12->fY > MAX_Y) // Check if the Y Axis is bigger than 1 (set it -0.05 so it's not cutted of)
					v12->fY = MAX_Y;

				if (v12->fY < MIN_Y) // Check if the Y Axis is smaller than 0 (set it +0.05 so it's not cutted of)
					v12->fY = MIN_Y;
			}

			goto out;
		}
		else
		{
			if (v12->fX > MAX_X)
				v12->fX = MAX_X; // Check if the X Axis is bigger than 1 (set it -0.05 so it's not cutted of)

			if (v12->fX < MIN_X)
				v12->fX = MIN_X; // Check if the X Axis is smaller than 0 (set it +0.05 so it's not cutted of)
		}

		if (v12->fY < MAX_Y && v12->fY > MIN_Y) { // Check if the Y Acis is smaller than 1, but still positive
			if (v12->fX < MAX_X && v12->fX > MIN_X)// Check if the X axis is smaller than 1, but still positive
			{
				goto out;
			}
			else
			{
				if (v12->fX > MAX_X) // Check if the X Axis is bigger than 1 (set it -0.05 so it's not cutted of)
					v12->fX = MAX_X;

				if (v12->fX < 0) // Check if the X Axis is smaller than 0 (set it +0.05 so it's not cutted of)
					v12->fX = MIN_X;
			}

			goto out;
		}
		else {
			if (v12->fY > MAX_Y) // Check if the Y Axis is bigger than 1 (set it -0.05 so it's not cutted of)
				v12->fY = MAX_Y;

			if (v12->fY < MIN_Y) // Check if the Y Axis is smaller than 0 (set it +0.05 so it's not cutted of)
				v12->fY = MIN_Y;
		}
		goto out;
	}

out:

	_asm    mov esp, ebp;
	_asm    pop ebp;
	_asm    retn;
}

DWORD ResizeMapJmpBack;
int a1, a2, a3;

_declspec(naked) signed int ResizeMap()
{
	_asm push eax;
	_asm mov eax, [ebp + 4];
	_asm mov a1, eax;
	_asm mov eax, [ebp + 8];
	_asm mov a2, eax;
	_asm mov eax, [ebp + 0Ch];
	_asm mov a3, eax;
	_asm pushad;

	ResizeMapJmpBack = (g_pCore->GetBase() + 0x8364D7);

	_asm popad;
	_asm pop eax;
	_asm jmp ResizeMapJmpBack;
}

DWORD sub_849BC0;
_declspec(naked) void RenderMap()
{
	sub_849BC0 = (g_pCore->GetBase() + 0x849BC0);
	_asm	call sub_849BC0;
	_asm	add esp, 4;
	_asm	popad;

	//g_pCore->GetGame()->SetRadarVisible(true);

	_asm	pushad;
	_asm	retn;
}
#endif

int * physics = 0;
IVVehicle * pVehicle = 0;
DWORD sub_44A690 = 0;

// Vehicle + 0xE14 == fragInstGta*
struct fragInstGta
{
	DWORD vtable;
	DWORD dw1;
	WORD w1;
	WORD w2;
	IVEntity *	pEntity;
	Matrix34 m_Matrix; // 16-72
	char pad1[8]; // 72-80
	DWORD vtable_destruct; // 80-84
	char pad2[44]; // 84-128
	Vector3 m_vecPos; // 128-140
	char pad3[20]; // 140-160
	DWORD unkSize; // A0-A4
	DWORD unk; // A4-A8;
}; // size = 0xB0 [176]

// Vehicle + 0x1480 == phInstGta*
struct phInstGta
{
	DWORD vtable;
	DWORD dw1;
	WORD w1;
	WORD w2;
	IVEntity *	pEntity;
	Matrix34	m_Matrix;
	char pad2[4];
	int	iUnk;
}; // size = 0x60 [96]

void _declspec(naked) PhysicsHook()
{
	_asm
	{
		mov physics, ecx
		mov pVehicle, esi
		pushad
	}

	if (*(int*) pVehicle == g_pCore->GetBase() + 0xD9ED74) // IsBike
	{
		//_asm { int 3 }
		//CLogFile::Printf("%p", physics);
	}

	sub_44A690 = g_pCore->GetBase() + 0x44A690;
	if (*(DWORD *) (physics + 4) == 0)
	{
		CLogFile::Printf("Fail 0x%p", physics);

		if (pVehicle->GetfragInst())
		{
			if (*(DWORD*) (pVehicle->GetfragInst() + 0x64))
				CLogFile::Printf("0x%p", *(DWORD*) ((*(DWORD*) (pVehicle->GetfragInst() + 0x64)) + 0x160));
			else
			{
				int v2 = (*(int(__thiscall **)(DWORD))(*(DWORD *) pVehicle + 0xA0))((DWORD) pVehicle);
				CLogFile::Printf("0x%p", (*(int(__thiscall **)(DWORD))(*(DWORD *) v2 + 0xE0))(v2));
			}
		}

		g_pCore->GetGame()->GetStreaming()->RequestResource(eResourceType::RESOURCE_TYPE_WDR, pVehicle->m_wModelIndex);
		while (!g_pCore->GetGame()->GetStreaming()->HasResourceLoaded(eResourceType::RESOURCE_TYPE_WDR, pVehicle->m_wModelIndex))
		{
			g_pCore->GetGame()->GetStreaming()->LoadAllResources();
			Sleep(10);
		}

		CLogFile::Printf("Model: %i", pVehicle->m_wModelIndex);

		CLogFile::Printf("PhysicsBefore=>");
		CLogFile::Printf("[0x38] 0x%p || [0xE14] 0x%p || [0x100] 0x%p", pVehicle->m_pPhysics, pVehicle->m_pVehiclePhysics, *(DWORD*) (pVehicle + 0x40));
		CLogFile::Printf("<=");
		pVehicle->CreatePhysics();
		CLogFile::Printf("PhysicsAfter=>");
		CLogFile::Printf("[0x38] 0x%p || [0xE14] 0x%p || [0x100] 0x%p", pVehicle->m_pPhysics, pVehicle->m_pVehiclePhysics, *(DWORD*) (pVehicle + 0x40));
		CLogFile::Printf("<=");

		if (pVehicle->GetfragInst())
		{
			if (*(DWORD*) (pVehicle->GetfragInst() + 0x64))
				CLogFile::Printf("0x%p", *(DWORD*) ((*(DWORD*) (pVehicle->GetfragInst() + 0x64)) + 0x160));
			else
			{
				int v2 = (*(int(__thiscall **)(DWORD))(*(DWORD *) pVehicle + 0xA0))((DWORD) pVehicle);
				CLogFile::Printf("0x%p", (*(int(__thiscall **)(DWORD))(*(DWORD *) v2 + 0xE0))(v2));
			}
		}
		_asm popad;
		_asm retn;
	}
	else
	{
		_asm popad;
		_asm call sub_44A690;
		_asm retn;
	}


	_asm
	{
		_asm popad;
		_asm retn;
	}
}

_declspec(naked) void CTaskSimpleStartVehicle__Process()
{
	_asm xor eax, eax;
	_asm retn 4;
}

#define GTA_malloc (*(char *(__cdecl *)(int)) (g_pCore->GetBase() + 0x4011D0))
#define getGameFolderFromRegistry (*(bool(__stdcall *)(char *)) (g_pCore->GetBase() + 0x8B3260))
#define GTA_memcpy (*(int(__cdecl *)(char *, char *, int)) (g_pCore->GetBase() + 0xD0BC80))
#define GTA_strcat (*(int(__cdecl *)(char*, char*, int)) (g_pCore->GetBase() + 0xD0C2B0))
#define SetGTAWorkdir (*(int(__thiscall *)(void *, char *)) (g_pCore->GetBase() + 0x45AEF0))
#define GTAWorkdirUknownPVOID (void *) (g_pCore->GetBase() + 0x1003C10)
#define IsFileExistInWorkdir (*(bool(__thiscall *)(void *, char *, int)) (g_pCore->GetBase() + 0x45B070))
#define WorkdirUnknownFunc (*(void(__thiscall *)(void *)) (g_pCore->GetBase() + 0x45AFB0))
#define UnknownFuncWhitGameDir (*(int(__cdecl *)(char *)) (g_pCore->GetBase() + 0x401210)) //Maybe delete the char*?
#define RegisterFolder (*(int(__thiscall *)(void *, char *)) (g_pCore->GetBase() + 0x8B3BB0))

void CHookDummy::loadEbisodes()
{
	
	char* GameFolder = GTA_malloc(MAX_PATH);
	getGameFolderFromRegistry(GameFolder);

	if (*(DWORD *) (this + 364) == -1)
	{
		int pointer = 0;

		char* TLADFolder = new char[MAX_PATH];
		GTA_memcpy(TLADFolder, GameFolder, strlen(GameFolder) + 1 > MAX_PATH ? MAX_PATH : strlen(GameFolder) + 1);
		GTA_strcat(TLADFolder, "\\TLAD\\", 6);

		SetGTAWorkdir(GTAWorkdirUknownPVOID, TLADFolder);

		if (IsFileExistInWorkdir(GTAWorkdirUknownPVOID, "setup2.xml", NULL))
		{
			char reg[360];
			memset(reg, 0, MAX_PATH);
			strcpy(reg, TLADFolder);
			*(BYTE *) (reg + 260) = 0;
			*(BYTE *) (reg + 324) = 0;
			*(DWORD *) (reg + 340) = 0;
			*(DWORD *) (reg + 344) = 1;
			*(DWORD *) (reg + 348) = 0;
			*(DWORD *) (reg + 352) = 0;
			*(BYTE *) (reg + 356) = 0;
			*(BYTE *) (reg + 357) = 0;
			*(BYTE *) (reg + 359) = 0;

			*(DWORD *) (this + 364 + pointer) = RegisterFolder(this, reg);
			pointer += 4;

			*(BYTE *) (this + 361) = 1;
			*(DWORD *) (g_pCore->GetBase() + 0x10619D8) = 1;

			if (*(DWORD *) (g_pCore->GetBase() + 0x10619A4) > 0)
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = *(DWORD *) (g_pCore->GetBase() + 0x10619A4);
			else
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = 1;
		}

		char* TBoGTFolder = new char[MAX_PATH];
		GTA_memcpy(TBoGTFolder, GameFolder, strlen(GameFolder) + 1 > MAX_PATH ? MAX_PATH : strlen(GameFolder) + 1);
		GTA_strcat(TBoGTFolder, "\\TBoGT\\", 7);

		SetGTAWorkdir(GTAWorkdirUknownPVOID, TBoGTFolder);

		if (IsFileExistInWorkdir(GTAWorkdirUknownPVOID, "setup2.xml", NULL))
		{
			char reg[360];
			memset(reg, 0, MAX_PATH);
			strcpy(reg, TBoGTFolder);
			*(BYTE *) (reg + 260) = 0;
			*(BYTE *) (reg + 324) = 0;
			*(DWORD *) (reg + 340) = 0;
			*(DWORD *) (reg + 344) = 1;
			*(DWORD *) (reg + 348) = 0;
			*(DWORD *) (reg + 352) = 0;
			*(BYTE *) (reg + 356) = 0;
			*(BYTE *) (reg + 357) = 0;
			*(BYTE *) (reg + 359) = 0;

			*(DWORD *) (this + 364 + pointer) = RegisterFolder(this, reg);
			pointer += 4;

			*(BYTE *) (this + 361) = 1;
			*(DWORD *) (g_pCore->GetBase() + 0x10619D8) = 1;

			if (*(DWORD *) (g_pCore->GetBase() + 0x10619A4) > 0)
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = *(DWORD *) (g_pCore->GetBase() + 0x10619A4);
			else
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = 1;
		}
	}

	WorkdirUnknownFunc(GTAWorkdirUknownPVOID);
	if (GameFolder)
		UnknownFuncWhitGameDir(GameFolder);


	*(BYTE *) (this + 358) = 0;
}

void __cdecl renderMenus() //render Main and pause menu
{
	//g_pCore->GetChat()->Outputf(false, "sub_4774A0()");
	//*(DWORD*) (g_pCore->GetBase() + 0x104E130) = 0; // 1 = blink, but i wagt hide it.
	//*(BYTE*) (g_pCore->GetBase() + 0x104E1D8) = 1;
}

void __cdecl sub_47F080()
{
	//g_pCore->GetChat()->Outputf(false, "sub_47F080()");
}

void __cdecl sub_47BA60()
{
	//g_pCore->GetChat()->Outputf(false, "sub_47BA60()");
}

#include <IV/CIVScript.h>

void __cdecl runStartupScript()
{
	unsigned int pid = 0;
	CIVScript::CreatePlayer(0, 1498.8f, -1661.3f,  12.5f, &pid);

	g_pCore->OnGameLoad();
	g_pCore->SetClientState(GAME_STATE_INGAME);
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
	CPatcher::InstallCallPatch(COffsets::FUNC_RemoveInitialLoadingScreens, (DWORD) RemoveLoadingScreens);
	
	// Always draw vehicle hazzard lights
	CPatcher::InstallNopPatch(COffsets::PATCH_CVehicle__HazzardLightsOn, 2);
	
	// Disable loading music
	CPatcher::InstallNopPatch(COffsets::CALL_StartLoadingTune, 5);

	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x9D180B, (DWORD) PhysicsHook);

	// Disable automatic vehicle engine turn-on
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchVehicleDriverProcess, (DWORD) CTaskSimpleStartVehicle__Process);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x8B3FF0, CPatcher::GetClassMemberAddress(&CHookDummy::loadEbisodes));

	// Disable wanted circles on the minimap(we have no cops which are following you atm ^^)
	*(BYTE *) (g_pCore->GetBase() + 0x83C216) = 0xEB;
	*(BYTE *) (g_pCore->GetBase() + 0x83BFE0) = 0xC3;

	//CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x47BFED, (DWORD) renderMenus);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47F080, (DWORD) sub_47F080);

	//CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47BA60, (DWORD) sub_47BA60);

	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x834093, (DWORD)runStartupScript);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x834098, g_pCore->GetBase() + 0x8340F4);

#ifdef GTAV_MAP
	// Patch crosshair
	CPatcher::Unprotect((g_pCore->GetBase() + 0xE35790), 13);
	*(DWORD *) (g_pCore->GetBase() + 0xE35790) = 0x73706172;
	*(DWORD *) (g_pCore->GetBase() + 0xE35790 + 0x4) = 0x6B6C6500;
	*(DWORD *) (g_pCore->GetBase() + 0xE35790 + 0x8) = 0x00000000;
	*(BYTE*) (g_pCore->GetBase() + 0xE35790 + 0x12) = 0x0;

	// Patch icons to star
	CPatcher::Unprotect((g_pCore->GetBase() + 0xFEA8E4), 20);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8E4) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8E8) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8EC) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8F0) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8F4) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);

	// Change calc from circle to square(blips)
	*(BYTE*) (g_pCore->GetBase() + 0x8385E7 + 0x6) = 0x1;
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x8386AB, (DWORD) Keks);

	// Enable square map(instead of circle map)
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0xA22C53, g_pCore->GetBase() + 0xA22EF3);

	// Enable big radar
	*(BYTE *) (g_pCore->GetBase() + 0x08364D0 + 0x6) = 0x1;

	// Hook resize map function
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x8364D0), (DWORD) ResizeMap, 5);
	*(WORD *) (g_pCore->GetBase() + 0x8364D0 + 0x5) = 0x9090;

	// Make blip small
	*(BYTE *) (g_pCore->GetBase() + 0x4B516F + 0x6) = 0x1; // cmp VAR_DEVMODE, 1
	*(BYTE *) (g_pCore->GetBase() + 0x4B516F + 0x6) = 0x1; // cmp VAR_DEVMODE, 1

	// Hook render map function
	CPatcher::InstallCallPatch((g_pCore->GetBase() + 0xA22E71), (DWORD) RenderMap, 5);
#endif
}
