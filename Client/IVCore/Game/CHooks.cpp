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

	_asm	push v7;
	_asm	mov ecx, COffsets::IV_Hook__StartGameLoading_1;
	_asm	call COffsets::IV_Hook__StartGameLoading_2;
	
	*(DWORD*) COffsets::IV_Hook__StartGameLoading_3 = *v7;
	*(DWORD*) COffsets::IV_Hook__StartGameLoading_4 = *v7;
	if (*v7 > 0)
		_asm	call COffsets::IV_Hook__StartGameLoading_5;
}

void RemoveLoadingScreens()
{
	StartGame_Loading();

	int iLoadScreens = COffsets::VAR_NumLoadingScreens;
	int iLoadScreenType = COffsets::VAR_FirstLoadingScreenType;
	int iLoadScreenDuration = COffsets::VAR_FirstLoadingScreenDuration;

	for (int i = 0; i < *(int *) iLoadScreens; ++i) {
		*(DWORD *) (iLoadScreenType + i * 400) = 0;
		*(DWORD *) (iLoadScreenDuration + i * 400) = 0;
	}

	//CPatcher::InstallNopPatch(COffsets::FUNC_RemoveInitialLoadingScreens, 5);
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
	_asm	xor eax, eax;
	_asm	retn;
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

#include <IV/CIVScript.h>
void _declspec(naked) PhysicsHook()
{
	_asm	mov physics, ecx;
	_asm	mov pVehicle, esi;
	_asm	pushad;
	_asm	pushfd; //EFLAGS!

	if (*(int*) pVehicle == g_pCore->GetBase() + 0xD9ED74) { // IsBike
		//_asm { int 3 }
		//CLogFile::Printf("%p", physics);
	}

	sub_44A690 = g_pCore->GetBase() + 0x44A690;
	if (*(DWORD *) (physics + 4) == 0) {
		CLogFile::Printf("Fail 0x%p", physics);

		if (pVehicle->GetfragInst()) {
			if (*(DWORD*) (pVehicle->GetfragInst() + 0x64))
				CLogFile::Printf("0x%p", *(DWORD*) ((*(DWORD*) (pVehicle->GetfragInst() + 0x64)) + 0x160));
			else {
				int v2 = (*(int(__thiscall **)(DWORD))(*(DWORD *) pVehicle + 0xA0))((DWORD) pVehicle);
				CLogFile::Printf("0x%p", (*(int(__thiscall **)(DWORD))(*(DWORD *) v2 + 0xE0))(v2));
			}
		}

		CIVScript::RequestModel(pVehicle->m_wModelIndex);
		while (!CIVScript::HasModelLoaded(pVehicle->m_wModelIndex))
			CIVScript::LoadAllObjectsNow(false);

		CLogFile::Printf("Model: %i", pVehicle->m_wModelIndex);

		CLogFile::Printf("PhysicsBefore=>");
		CLogFile::Printf("[0x38] 0x%p || [0xE14] 0x%p || [0x100] 0x%p", pVehicle->m_pPhysics, pVehicle->m_pVehiclePhysics, *(DWORD*) (pVehicle + 0x40));
		CLogFile::Printf("<=");
		pVehicle->CreatePhysics();
		CLogFile::Printf("PhysicsAfter=>");
		CLogFile::Printf("[0x38] 0x%p || [0xE14] 0x%p || [0x100] 0x%p", pVehicle->m_pPhysics, pVehicle->m_pVehiclePhysics, *(DWORD*) (pVehicle + 0x40));
		CLogFile::Printf("<=");

		if (pVehicle->GetfragInst()) {
			if (*(DWORD*) (pVehicle->GetfragInst() + 0x64))
				CLogFile::Printf("0x%p", *(DWORD*) ((*(DWORD*) (pVehicle->GetfragInst() + 0x64)) + 0x160));
			else {
				int v2 = (*(int(__thiscall **)(DWORD))(*(DWORD *) pVehicle + 0xA0))((DWORD) pVehicle);
				CLogFile::Printf("0x%p", (*(int(__thiscall **)(DWORD))(*(DWORD *) v2 + 0xE0))(v2));
			}
		}
		_asm	popfd;
		_asm	popad;
		_asm	retn;
	}
	else {
		_asm	popfd;
		_asm	popad;
		_asm	call sub_44A690;
		_asm	retn;
	}

	_asm	popfd;
	_asm	popad;
	_asm	retn;
}

_declspec(naked) void CTaskSimpleStartVehicle__Process()
{
	_asm xor eax, eax;
	_asm retn 4;
}

void __cdecl renderMenus() //render Main and pause menu
{
	//g_pCore->GetChat()->Print("sub_4774A0()");
	//*(DWORD*) (g_pCore->GetBase() + 0x104E130) = 0; // 1 = blink, but i wagt hide it.
	//*(BYTE*) (g_pCore->GetBase() + 0x104E1D8) = 1;
}

void __cdecl sub_47F080()
{
	g_pCore->OnGameUpdate();
	//g_pCore->GetChat()->Print("sub_47F080()");
}

void __cdecl sub_47BA60()
{
	//g_pCore->GetChat()->Print("sub_47BA60()");
}

void __cdecl runStartupScript()
{
	g_pCore->GetIVStartupScript()->Process();
}

enum eRAGETHREAD_States
{
	ThreadStateIdle,
	ThreadStateRunning,
	ThreadStateKilled,
	ThreadState3,
	ThreadState4,			// Sets opsToExecute to 1100000, and state to Idle in CallNative
};

struct sSRCThread_Content
{
	unsigned int ThreadId;		// 00-04 m_nThreadId dd ?
	unsigned int ScriptHash;	// 04-08 m_dwScriptHash dd ?
	eRAGETHREAD_States State;	// 08-0C m_eThreadState dd ?
	unsigned int IP;			// 0C-10 m_nIP       dd ?
	unsigned int FrameSP;		// 10-14 m_nFrameSP  dd ?
	unsigned int SP;			// 14-18 m_nSP       dd ?
	unsigned int TimerA;		// 18-1C m_nTimerA   dd ?
	unsigned int TimerB;		// 1C-20 m_nTimerB   dd ?
	unsigned int TimerC;		// 20-24 m_nTimerC   dd ?
	float WaitTime;				// 24-28 m_fWaitTime dd ?
	unsigned int _f28;			// 28-2C field_28    dd ?
	unsigned int _f2C;			// 2C-30 field_2C    dd ?
	unsigned int _f30;			// 30-34 field_30    dd ?
	unsigned int _f34;			// 34-38 field_34    dd ?
	unsigned int _f38;			// 38-3C field_38    dd ?
	unsigned int _f3C;			// 3C-40 field_3C    dd ?
	unsigned int _f40;			// 40-44 field_40    dd ?
	unsigned int ExIP;			// 44-48 ExIP        dd ?
	unsigned int ExFrameSP;		// 48-4C ExFrameSP   dd ?
	unsigned int ExSP;			// 4C-50 ExSP        dd ?
	unsigned int _f50;			// 50-54 field_50    dd ?
};

class sSRCThread
{
public:
	DWORD m_dwVFTable;              // 00-04 _vmt        dd ?
	sSRCThread_Content m_Context;		// 04-58 m_Context   scrThreadContext ?
	void * m_pStack;					// 58-5C m_pStack    dd ?
	unsigned int _f5C;				// 5C-60 field_5C    dd ?
	void * m_pXLiveBuffer;				// 60-64 m_pXLiveBuffer dd ?
	unsigned int _f64;				// 64-68 field_64    dd ?
	unsigned int _f68;				// 68-6C field_68    dd ?
	char *m_pszExitMessage;			// 6C-70 m_pszExitMessage dd ?
};

class sRAGETHREAD : public sSRCThread
{
public:
	char m_szProgramName[24];					// 70-88 m_szProgramName db 24 dup(?)
	unsigned int _f88;							// 88-8C field_88    dd ?
	unsigned int _f8C;							// 8C-90 field_8C    dd ?
	unsigned int _f90;							// 90-94 field_90    dd ?
	bool _f94;									// 94-95 field_94    db ?
	bool _f95;									// 95-96 --- db ?									// Check IDA
	bool m_bThisScriptShouldBeSaved;			// 96-97 m_bThisScriptShouldBeSaved db ?
	bool m_bPlayerControlOnInMissionCleanup;	// 97-98 m_bPlayerControlOnInMissionCleanup db ?
	bool m_bClearHelpInMissionCleanup;			// 98-99 m_bClearHelpInMissionCleanup db ?
	bool _f99;									// 99-9A field_99    db ?
	bool m_bAllowNonMinigameTextMessages;		// 9A-9B m_bAllowNonMinigameTextMessages db ?
	bool _f9B;									// 9B-9C field_9B    db ?
	bool _f9C;									// 9C-9D --- db ?									// Check IDA
	bool m_bCanBePaused;						// 9D-9E m_bCanBePaused db ?
	bool _f9E;									// 9E-9F field_9E    db ?
	bool _f9F;									// 9F-A0 field_9F    db ?
	bool _fA0;									// A0-A4 field_A0    dd ?
	bool m_bCanRemoveBlipsCreatedByAnyScript;	// A4-A5 m_bCanRemoveBlipsCreatedByAnyScript db ?
	bool _fA5;									// A5-A6             db ? ; undefined
	bool _fA6;									// A6-A7             db ? ; undefined
	bool _fA7;									// A7-A8             db ? ; undefined
	unsigned int _fA8;							// A8-AC field_A8    dd ?
	unsigned int m_nFlags;						// AC-B0 m_nFlags    dd ?
};

sRAGETHREAD* g_pRageScriptThread = NULL;

__declspec(naked) int GetRunningScriptThread()
{
	_asm	mov eax, g_pRageScriptThread;
	_asm	retn;
}

void CHooks::Intialize()
{
	// Hook GetPlayerInfoFromIndex to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_CPlayer__GetPlayerByNumber, (DWORD) GetPlayerInfoFromIndex_Hook);
	
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

	// Disable wanted circles on the minimap(we have no cops which are following you atm ^^)
	*(BYTE *) (g_pCore->GetBase() + 0x83C216) = 0xEB;
	*(BYTE *) (g_pCore->GetBase() + 0x83BFE0) = 0xC3;

	//CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x47BFED, (DWORD) renderMenus);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47F080, (DWORD) sub_47F080);

	//CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47BA60, (DWORD) sub_47BA60);

	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x834093, (DWORD)runStartupScript);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x834098, g_pCore->GetBase() + 0x8340F4);
	
	// Disable check to invalid threads
	g_pRageScriptThread = new sRAGETHREAD;
	memset(g_pRageScriptThread, NULL, sizeof(sRAGETHREAD));
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x82E7E0), (DWORD) GetRunningScriptThread, 5);

	CPatcher::InstallJmpPatch(COffsets::IV_Hook__IncreasePoolSizes, CPatcher::GetClassMemberAddress(&IVPoolOwns::IVPoolHook));
}
