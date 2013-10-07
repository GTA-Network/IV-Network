//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
	//CLogFile::Printf("%s",__FUNCTION__);
	_asm mov eax, g_pRageScriptThread;
	_asm retn;
}

#define GetScriptName (*(char* (__thiscall *)(sRAGETHREAD *)) (g_pCore->GetBase() + 0x4CF650))

int sOUR_RAGETHREAD::Process_Hook(int a1)
{
#if 0
	FILE* f;
	fopen_s(&f, "script.log", "a+");
	fprintf(f, "%s\n", GetScriptName(this));
	fclose(f);
#endif

	/*
	Disable a script:
	if (strcmp(GetScriptName(this), "drunkcontroller") == 0) //This stolen by XForce x)
	return 2;
	*/

	if (strcmp(GetScriptName(this), "main") == 0)
	{
		if (!g_bRageScriptLoaded)
		{
			// Mark RageScriptThread as loaded
			g_bRageScriptLoaded = !g_bRageScriptLoaded;

			g_pCore->OnGameLoad();
			g_pCore->SetClientState(GAME_STATE_INGAME);
		}
		else
			g_pCore->GetGame()->RenderRAGEScripts();
		return 2;
	}

	memcpy(m_szProgramName, GetScriptName(this), 24);
	m_szProgramName[24] = '\0';

	if (this->_f9C != 0 || (*(bool(*)()) (g_pCore->GetBase() + 0x7D50B0))())
	{
		return m_Context.State; //maybe not correct?!
	}
	else
	{
		(*(void(__thiscall *)(sRAGETHREAD *)) (g_pCore->GetBase() + 0xC2B530))(this);
		*(DWORD *) (g_pCore->GetBase() + 0x10A53B0) = *(DWORD *) (*(DWORD *) (g_pCore->GetBase() + 0x105A014) + 1344);
		*(DWORD *) (g_pCore->GetBase() + 0x10B415C) = 0;
		*(BYTE *) (g_pCore->GetBase() + 0x10B418C) = 0;
		return (*(int(__thiscall *)(sRAGETHREAD *, int)) (g_pCore->GetBase() + 0x4CE060))(this, a1);
	}
};

void CIVScriptingHook::InstallScriptHooks()
{
	g_pRageScriptThread = new sRAGETHREAD;
	memset(g_pRageScriptThread, NULL, sizeof(sRAGETHREAD));

	*(BYTE*) (g_pCore->GetBase() + 0x4CE0BE) = 0x57; //push edi
	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x4CE0BF, CPatcher::GetClassMemberAddress(&sOUR_RAGETHREAD::Process_Hook));
	*(WORD*) (g_pCore->GetBase() + 0x4CE0C4) = 0x9090; //nop; nop

	// Disable check to invalid threads
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x82E7E0), (DWORD) GetRunningScriptThread, 5);
	//CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x830DE1), 39);
	//CPatcher::InstallNopPatch((g_pCore->GetBase() + 0830E64), 22);
}

void CIVScriptingHook::UninstallScriptHooks()
{
	SAFE_DELETE(g_pRageScriptThread);
}