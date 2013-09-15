//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CEFLCSupport.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CEFLCSupport.h"
#include <CCore.h>
#include <Ptrs.h>
#include <IV/IVParachute_Manager.h>
#include <IV/IVParachute_Process.h>
#include <algorithm> 
#include <string> 
#pragma warning(disable:4305)

extern unsigned int l_U40;
extern CCore * g_pCore;
extern bool g_bLoading;

bool CEFLCSupport::m_bVehicles = false;
bool CEFLCSupport::m_bPeds = false;
bool CEFLCSupport::m_bWeapons = false;
bool CEFLCSupport::m_bMaps = false;
bool CEFLCSupport::m_bParachute = false;

DWORD sub_5B4F60;
DWORD dwJmp2;
char *file = new char[255];
char *file_ptr;


bool CEFLCSupport::OpenFile_Decision(char* j)
{
	CString strCheckFile = CString("%s",j).ToLower();
	if(strcmp(strCheckFile.Get(), "e2:/common/data/hud.dat") == 0) // identical
	{
		CLogFile::Printf("[%s]: Setting hud.dat to hud_eflc.dat",__FUNCTION__);
		sprintf(j, "e2:/common/data/hud_eflc.dat");
		
		// Set the loading screen to false;
		g_bLoading = false;
	}
	return false;
}

_declspec(naked) void _stdcall RAGE_AssetManager__OpenFile()
{
	_asm	mov file_ptr, edx;
	_asm	pushad;

	dwJmp2 = COffsets::RAGE_AssetManager__OpenFile;
	sub_5B4F60 = COffsets::RAGE_AssetManager__OpenFileJmpBack;

	if(CEFLCSupport::OpenFile_Decision(file_ptr)) {
		_asm	mov eax, file;
		_asm	mov file_ptr, eax;
		_asm	;mov edx, [eax];
		_asm	popad;
		_asm	push file;
	}
	else {
		_asm	popad;
		_asm	push edx;
	}

	_asm	call sub_5B4F60;
	_asm	add esi, 1;
	_asm	add esp, 8;
	_asm	jmp dwJmp2;
}

HANDLE hFile;
LPVOID lpBuffer;
DWORD dwRFile;
CString strFile;
void TransformLoadingScreen(CString * strPtr) {
	
	if(strPtr->Find("common:/") != std::string::npos)
		return;

	*strPtr = strPtr->Substring(0, strPtr->GetLength()-4); //loadingscreens[.dat]
	strPtr->AppendF("_pc_eflc_v2.dat");
}

void _declspec(naked) RAGE_OpenFile()
{
	_asm	mov eax, [esp+4];
	_asm	mov hFile, eax;
	_asm	mov eax, [esp+8];
	_asm	mov lpBuffer, eax;
	_asm	pushad;

	strFile.AppendF("%s",hFile);
	TransformLoadingScreen(&strFile);

	strcpy((char *)hFile, strFile.Get());
	dwRFile = COffsets::RAGE_OpenFile;

	strFile.Clear();

	_asm	popad;
	_asm	push lpBuffer;
	_asm	push hFile;
	_asm	call dwRFile;
	_asm	add esp, 8;
	_asm	retn;
}

void CEFLCSupport::InstallSupport()
{
	// If our user wants to load the EFLC map, don't hook the function
	if(!g_pCore->GetGame()->IsUsingEFLCContent())
		return;

#ifndef CHEAP_RELEASE
	// Hook loading files
	CPatcher::InstallJmpPatch((COffsets::RAGE_AssetManager__OpenFile - 0xC), (DWORD)RAGE_AssetManager__OpenFile);

	// Hook loading screen
	CPatcher::InstallHookCall(COffsets::IV_HookLoadingScreen__DAT, (DWORD)RAGE_OpenFile);

	// Hook loading tune
	char *szLoadingTune = "LOADINGTUNE";
	CPatcher::InstallPushPatch(COffsets::IV_HookLoadingTune, (DWORD)szLoadingTune);
#endif
}

void CEFLCSupport::InstallPreGameLoad()
{
	// If our user wants to load the EFLC map, don't hook the function
	if(!g_pCore->GetGame()->IsUsingEFLCContent())
		return;

	// Install parachute if needed
	if(m_bParachute) {
		int iAnimIndex = g_pCore->GetGame()->GetStreaming()->GetAnimIndexFromName("PARACHUTE");
		g_pCore->GetGame()->GetStreaming()->RequestResource(RESOURCE_TYPE_WAD, iAnimIndex);
	}
}