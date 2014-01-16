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

#include "CTrafficHandler.h"
#include <Patcher/CPatcher.h>
#include <IV/CIVScript.h>
#include <Ptrs.h>

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
    CPatcher::InstallRetnPatch(COffsets::IV_Hook__DisableParkedCars);

    // Disable emergency services and garbage trucks
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableEmergencyAndGarbageTrucks, 5);

    // Disable vehicle entries
    *(DWORD *)(COffsets::IV_Hook__DisableVehicleEntries) = 0x0CC2C033;
    *(BYTE *)(COffsets::IV_Hook__DisableVehicleEntries + 0x4) = 0x00;

    // Disable vehicle exits
    *(BYTE *)(COffsets::IV_Hook__DisableVehicleExists) = 0xEB;

	// Disables some stuff like police helis, ambient planes, emergency services, garbage trucks and random trains
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x49454F, 5);

    // Disable random peds and vehicles
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableRandomPedsAndVehicles_1, 5);

    // Disable scenario peds
    *(BYTE *)(COffsets::IV_Hook__DisableScenarioPeds) = 0xB8; // mov eax,
	*(DWORD *)(COffsets::IV_Hook__DisableScenarioPeds + 0x1) = 0x0; // 0
    *(BYTE *)(COffsets::IV_Hook__DisableScenarioPeds + 0x5) = 0xC3; // retn

    // Disable fake cars
	CPatcher::InstallRetnPatch(COffsets::IV_Hook__DisableFakeCars);
}