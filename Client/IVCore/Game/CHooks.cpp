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

#include "CHooks.h"
#include "COffsets.h"
#include <CCore.h>
#include <Patcher/CPatcher.h>
#include <Game/EFLC/CPlayerInfo.h>
#include "CContextData.h"
#include <SharedUtility.h>
#include "CGameFuncs.h"
#include <Game/EFLC/CScript_FunctionInvoke.h>
#include <Game/EFLC/ScriptEnums.h>
#include <Game/EFLC/ScriptFunctions.h>
#include <Game/EFLC/CPedMoveBlend.h>

extern	CCore* g_pCore;

struct thisisafuckingthiscall
{
	// IS. not not like static __thiscalls, don't care about it, this will works. :)
	static void __thiscall IVTask__Destructor(EFLC::ITask * a1);
};

#define sub_B17A90 (*(char *(__cdecl *)(EFLC::ITask *)) (g_pCore->GetBase() + 0xB17A90))
#define sub_B17910 (*(int *(__thiscall *)(char *)) (g_pCore->GetBase() + 0xB17910))
#define sub_A2ABA0 (*(void (__thiscall *)(EFLC::ITask *)) (g_pCore->GetBase() + 0xA2ABA0))

void  thisisafuckingthiscall::IVTask__Destructor(EFLC::ITask * a1)
{
	if (g_pCore->GetGame()->GetTaskManager())
		g_pCore->GetGame()->GetTaskManager()->HandleTaskDelete(a1);

	*(DWORD *) (char*) a1 = *(DWORD *) COffsets::VAR_CTask__VFTable;

	char * v1 = sub_B17A90(a1);
	if (v1)
		sub_B17910(v1);

	return sub_A2ABA0(a1);
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

EFLC::IPlayerInfo * pReturnedPlayerInfo = NULL;
EFLC::IPlayerInfo * GetPlayerInfoFromIndex(unsigned int uiIndex)
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
unsigned int GetIndexFromPlayerInfo(EFLC::IPlayerInfo * pPlayerInfo)
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

EFLC::IPlayerPed  * _pPlayerPed = NULL;
EFLC::IPlayerPed * GetLocalPlayerPed()
{
	// Default to the local player ped (If available)
	EFLC::IPlayerInfo * pPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0);

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

int * physics = 0;
EFLC::IVehicle * pVehicle = 0;
DWORD sub_44A690 = 0;

// Vehicle + 0xE14 == fragInstGta*
struct fragInstGta
{
	DWORD vtable;
	DWORD dw1;
	WORD w1;
	WORD w2;
	EFLC::IEntity *	pEntity;
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
	EFLC::IEntity *	pEntity;
	Matrix34	m_Matrix;
	char pad2[4];
	int	iUnk;
}; // size = 0x60 [96]

#include <Game/EFLC/CScript.h>
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

		EFLC::CScript::RequestModel(pVehicle->m_wModelIndex);
		while (!EFLC::CScript::HasModelLoaded(pVehicle->m_wModelIndex))
			EFLC::CScript::LoadAllObjectsNow(false);

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


EFLC::IPed* gped = nullptr;
DWORD dwJmp = 0;

void _declspec(naked) _hook_9E6480()
{
	_asm
	{
		mov eax, [ecx + 40h]
		mov gped, eax
		pushad
	}

	if (gped->m_bytePlayerNumber && gped->m_byteIsPlayerPed)
	{

		// TODO: set some stuff in the netblender
		/*
		NetBlender* = *(DWORD *)(gped->m_pNetworkObject + 28)
		*/
		if (gped->m_pNetworkObject)
			((int(__stdcall *)(int, EFLC::IPed *))((g_pCore->GetBase() + 0x525C20)))(gped->m_pNetworkObject + 2056, gped);

		_asm
		{
			popad
				retn
		}
	}

	dwJmp = (g_pCore->GetBase() + 0x9E648A);
	_asm
	{
		popad
		push    esi
		push    edi
		mov     edi, ecx
		lea     esi, [edi + 2E0h]
		jmp		dwJmp
	}
}

void _declspec(naked) _hook_9E656F()
{
	_asm
	{
		mov     eax, [ecx + 38h]
		mov		gped, eax
		pushad
	}

	if (gped->m_bytePlayerNumber && gped->m_byteIsPlayerPed)
	{

		gped->m_pPedMoveBlendOnFoot->m_dwFlags |= 0x2000u;
		((void(__thiscall *)(EFLC::IPedMoveBlendOnFoot*, DWORD))((g_pCore->GetBase() + 0xB10C30)))(gped->m_pPedMoveBlendOnFoot, 1);

		// TODO: set the move speed in moveblendonfoot

		gped->m_pPedMoveBlendOnFoot->Function19();
		gped->IPed_pad16[40] |= 2u;
		_asm
		{
			popad
			retn
		}
	}
	dwJmp = (g_pCore->GetBase() + 0x9E3DA0);
	_asm
	{
		popad
		jmp dwJmp
	}
}

void __cdecl renderMenus() //render Main and pause menu
{
	//g_pCore->GetGraphics()->GetChat()->Print("sub_4774A0()");
	//*(DWORD*) (g_pCore->GetBase() + 0x104E130) = 0; // 1 = blink, but i wagt hide it.
	//*(BYTE*) (g_pCore->GetBase() + 0x104E1D8) = 1;
}

void __cdecl sub_47F080()
{
	
	//g_pCore->GetGraphics()->GetChat()->Print("sub_47F080()");
}

void __cdecl sub_47BA60()
{
	//g_pCore->GetGraphics()->GetChat()->Print("sub_47BA60()");
}
#include <Game/CGameMainScript.h>

void __cdecl runStartupScript()
{
	EFLC::AddScriptToThreadCollection(new EFLC::CGameMainScript());
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

sRAGETHREAD* __cdecl GetRunningScriptThread()
{
	return g_pRageScriptThread;
}

#define CovertTextToDrawText (*(void (__cdecl *)(char * in, char* out)) (g_pCore->GetBase() + 0x801BC0)) //First two char is not converted. :(

void __cdecl GetLoadingText(char* buffer)
{
	CovertTextToDrawText("  IV:Network is loading...", buffer); //TODO: make it changeable form client script
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
	CPatcher::InstallJmpPatch(COffsets::FUNC_CTask__Destructor, (DWORD) thisisafuckingthiscall::IVTask__Destructor);
	
	// Hook initial loading screens
	CPatcher::InstallCallPatch(COffsets::FUNC_RemoveInitialLoadingScreens, (DWORD) RemoveLoadingScreens);
	
	// Disable loading music
	CPatcher::InstallNopPatch(COffsets::CALL_StartLoadingTune, 5);

	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x9D180B, (DWORD) PhysicsHook);

#if 1
	// Disable wanted circles on the minimap(we have no cops which are following you atm ^^)
	*(BYTE *) (g_pCore->GetBase() + 0x83C216) = 0xEB;
	*(BYTE *) (g_pCore->GetBase() + 0x83BFE0) = 0xC3;

	//CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x47BFED, (DWORD) renderMenus);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47F080, (DWORD) sub_47F080);

	//CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47BA60, (DWORD) sub_47BA60);
	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x834093, (DWORD)runStartupScript);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x834098, g_pCore->GetBase() + 0x8340F4);
	
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__IncreasePoolSizes, CPatcher::GetClassMemberAddress(&EFLC::IPoolOwns::IVPoolHook));

	//Replace loading text
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x7E2D0E, 2);
	*(BYTE*) (g_pCore->GetBase() + 0x7E2D10) = 0xEB;
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x7E2D24, 8);
	*(BYTE*) (g_pCore->GetBase() + 0x7E2D31) = 0xEB;
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x7E2D77, 2);
	*(BYTE*) (g_pCore->GetBase() + 0x7E2D79) = 0xEB;
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x7E2D9A, 11);
	*(BYTE*) (g_pCore->GetBase() + 0x7E2DA5) = 0xEB;
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x7E2DF2, 5);
	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x7E2DF7, (DWORD) GetLoadingText);
	*(BYTE*) (g_pCore->GetBase() + 0x7E2E0B) = 4;


	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x492D9B, 5); //do not load scrollbars.dat

	char* text = "Welcome to IV:Network. Have fun!"; //scrollbars text

	for (int i = 0; i < 8; ++i) //set scrollbars text
	{
		memcpy((char*)((g_pCore->GetBase() + 0x11B4508) + (1300 * i)), text, strlen(text)); //max len: 1300
		((char*)((g_pCore->GetBase() + 0x11B4508) + (1300 * i)))[strlen(text)] = '\0';
	}


	*(DWORD*)(g_pCore->GetBase() + 0x8DC8FD) = 0xFF38F5D8; //Set scrollbars's color to blue
#endif

#ifdef TASKINFO_TEST
	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x9E656F, (DWORD)_hook_9E656F);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x9E6480, (DWORD)_hook_9E6480);
#endif
	//CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x5138C4, 10);
	//CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x5138F7, 6);
}
