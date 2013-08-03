//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
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
	}

	if(!g_bRageScriptLoaded)
	{
		// Mark RageScriptThread as loaded
		g_bRageScriptLoaded = !g_bRageScriptLoaded;

		CRAGETHREAD_Collection<sRAGETHREAD> * pThreads = (CRAGETHREAD_Collection<sRAGETHREAD> *)COffsets::VAR_ScrVM__ThreadPool;
		pThreads->Size = 0;
		pThreads->Count = 0;

		// Create Local-Player
		unsigned uiPlayerIndex = NULL;
		DWORD dwCreatePlayer = (g_pCore->GetBase() + 0xB90990);
		CVector3 * pBasePos = new CVector3(0.f, 0.f, 0.f);

		/*_asm mov edi, pBasePos;
		_asm mov eax, 0;
		_asm push eax;
		_asm push eax;
		_asm call dwCreatePlayer;
		_asm mov uiPlayerIndex, eax;*/
		CIVScript::CreatePlayer(0, 0.0f, 0.0f, 0.0f, &uiPlayerIndex);

		g_pCore->SetClientState(GAME_STATE_INGAME);
	}
	else
		g_pCore->GetGame()->RenderRAGEScripts();
}

void CIVScriptingHook::InstallScriptHooks()
{
	g_pRageScriptThread = new sRAGETHREAD;
	memset(g_pRageScriptThread, NULL, sizeof(sRAGETHREAD));

	// Hook GetRunningScriptThread to return our own script thread structure
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetRunningScriptThread, (DWORD)GetRunningScriptThread, 5);

	// Hook for CScriptVM::Process
	CPatcher::InstallCallPatch(COffsets::CALL_CScriptVM__Process, (DWORD)CRageThread_Script_Process, 5);
}

void CIVScriptingHook::UninstallScriptHooks()
{
	SAFE_DELETE(g_pRageScriptThread);
}