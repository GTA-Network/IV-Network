//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CTrafficHandler.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CTrafficHandler.h"
#include <Patcher/CPatcher.h>
#include <CCore.h>
extern CCore * g_pCore;

CTrafficLights::eGTATrafficLightState dwTrafficLightState;

void __declspec(naked) GetTrafficLightState1()
{
	_asm	pushad;

	dwTrafficLightState = g_pCore->GetGame()->GetTrafficLights()->GetTrafficLightState();

	_asm	popad;
	_asm	mov eax, dwTrafficLightState;
	_asm	retn;
}

void __declspec(naked) GetTrafficLightState2()
{
	_asm	pushad;

	dwTrafficLightState = g_pCore->GetGame()->GetTrafficLights()->GetTrafficLightAltState();

	_asm	popad;
	_asm	mov eax, dwTrafficLightState;
	_asm	retn;
}

CTrafficHandler::CTrafficHandler()
{
	m_pTrafficLights = new CTrafficLights;
}

CTrafficHandler::~CTrafficHandler()
{
	SAFE_DELETE(m_pTrafficLights);
}

void CTrafficHandler::InstallTrafficLightsHook()
{
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetTrafficLightState1, (DWORD)GetTrafficLightState1);
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetTrafficLightState2, (DWORD)GetTrafficLightState2);
}

void CTrafficHandler::InstallTrafficHook()
{
	// Disable parked cars
    CPatcher::InstallRetnPatch(g_pCore->GetBase() + 0xB3EDF0);

    // Disable emergency services and garbage trucks
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x4215CF), 5);

    // Disable vehicle entries
    *(DWORD *)(g_pCore->GetBase() + 0x9B1ED0) = 0x0CC2C033;
    *(BYTE *)(g_pCore->GetBase() + 0x9B1ED4) = 0x00;

    // Disable vehicle exits
    *(BYTE *)(g_pCore->GetBase() + 0x9BBBFC) = 0xEB;

    // Disable random peds and vehicles
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x8ACD64), 5);
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x421610), 5);
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x81B22E), 5);

    // Disable scenario peds
    *(BYTE *)(g_pCore->GetBase() + 0x9F72C0) = 0xB8; // mov eax,
    *(DWORD *)(g_pCore->GetBase() + 0x9F72C1) = 0x0; // 0
    *(BYTE *)(g_pCore->GetBase() + 0x9F72C5) = 0xC3; // retn

    // Disable fake cars
    CPatcher::InstallRetnPatch(g_pCore->GetBase() + 0x9055D0);
}