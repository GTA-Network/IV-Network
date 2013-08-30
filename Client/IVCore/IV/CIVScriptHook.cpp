//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CIVScriptHook.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include <CCore.h>
#include "CIVScriptHook.h"
#include "CIVScript.h"


extern	CCore				* g_pCore;

sRAGETHREAD *	g_pRageScriptThread = NULL;
bool			g_bRageScriptLoaded = false;
int				g_iRageScriptFrames = 0;


__declspec(naked) int GetRunningScriptThread()
{
	_asm mov eax, g_pRageScriptThread;
	_asm retn;
}

void CRageThread_Script_Process()
{
	//GameScriptProcess();
	if(g_iRageScriptFrames < 2)
	{
		g_iRageScriptFrames++;
		CIVScript::DoScreenFadeIn(0);
		g_pCore->OnGameLoad();
	}

	if(!g_bRageScriptLoaded)
	{
		// Mark RageScriptThread as loaded
		g_bRageScriptLoaded = !g_bRageScriptLoaded;

		CRAGETHREAD_Collection<sRAGETHREAD> * pThreads = (CRAGETHREAD_Collection<sRAGETHREAD> *)COffsets::VAR_ScrVM__ThreadPool;
		pThreads->Size = (pThreads->Size)/2;
		pThreads->Count = (pThreads->Count)/2;

		// Create Local-Player
		unsigned uiPlayerIndex;
		DWORD dwCreatePlayer = (g_pCore->GetBase() + 0xB90990);
		CVector3 * pBasePos = new CVector3(0.f, 0.f, 0.f);
		CIVScript::CreatePlayer(0, 0.0f, 0.0f, 0.0f, &uiPlayerIndex);

		g_pCore->SetClientState(GAME_STATE_INGAME);
	}
	else
		g_pCore->GetGame()->RenderRAGEScripts();
}

DWORD dwRageThreadJmpBack = (COffsets::CALL_CScriptVM__Process + 0x8);
_declspec(naked) void CRageThread_Script_Process_After()
{
	_asm add esp, 4;
	_asm pushad;

	CRageThread_Script_Process();

	_asm popad;
	_asm jmp [dwRageThreadJmpBack];
}
void CIVScriptingHook::InstallScriptHooks()
{
	g_pRageScriptThread = new sRAGETHREAD;
	memset(g_pRageScriptThread, NULL, sizeof(sRAGETHREAD));

	// Hook GetRunningScriptThread to return our own script thread structure
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetRunningScriptThread, (DWORD)GetRunningScriptThread, 5);

	// Hook for CScriptVM::Process
	CPatcher::InstallCallPatch(COffsets::CALL_CScriptVM__Process, (DWORD)CRageThread_Script_Process, 5);
	//CPatcher::InstallJmpPatch((COffsets::CALL_CScriptVM__Process + 0x5), (DWORD)CRageThread_Script_Process_After, 3);
}

void CIVScriptingHook::UninstallScriptHooks()
{
	SAFE_DELETE(g_pRageScriptThread);
}