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

#include "CContextSwitch.h"
#include "CContextData.h"
#include <Game/COffsets.h>
#include <Patcher/CPatcher.h>
#include <Game/EFLC/CPad.h>
#include <Game/EFLC/CVehicle.h>
#include <CLogFile.h>
#include <CCore.h>

EFLC::IPed      * g_pPed = NULL;
EFLC::IVehicle  * g_pKeySyncIVehicle = NULL;
unsigned int g_uiLocalPlayerIndex = 0;
EFLC::IPad        g_localPad;
bool         g_bInLocalContext = true;
extern CCore *g_pCore;
EFLC::IPlayerInfo* g_pLocalPlayerInfo = NULL;

void ContextSwitch(EFLC::IPed * pPed, bool bPost)
{
	// Do we have a valid ped pointer?
	if(pPed) {
		// Get the remote players context data
		const auto pContextData = CContextDataManager::GetContextData((EFLC::IPlayerPed *)pPed);

		// Do we have a valid context data?
		if(pContextData) {
			// Is this not the local player?
			if(pContextData->GetPlayerInfo()->GetPlayerNumber() != 0) {
				if(!bPost && !g_bInLocalContext) {
					CLogFile::Printf("Not switching due to not being in local context!");
					return;
				}

				if(bPost && g_bInLocalContext) {
					CLogFile::Printf("Not switching due to being in local context!");
					return;
				}

				// Get the game pad
				auto * pPad = g_pCore->GetGame()->GetPad();

				if(!bPost) {
					// Store the local players index
					g_uiLocalPlayerIndex = g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex();

					// Store the local players pad
					memcpy(&g_localPad, pPad->GetPad(), sizeof(EFLC::IPad));

					g_pLocalPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(g_uiLocalPlayerIndex);

					g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex(g_uiLocalPlayerIndex, pContextData->GetPlayerInfo()->GetPlayerInfo());

					// Set the history values
					for(int i = 0; i < INPUT_COUNT; i++) {
						auto pPadData = &pContextData->GetPad()->GetPad()->m_padData[i];

						if(pPadData->m_pHistory) {
							pPadData->m_byteHistoryIndex++;

							if (pPadData->m_byteHistoryIndex >= MAX_HISTORY_ITEMS)
								pPadData->m_byteHistoryIndex = 0;

							pPadData->m_pHistory->m_historyItems[pPadData->m_byteHistoryIndex].m_byteValue = pPadData->m_byteLastValue;
							pPadData->m_pHistory->m_historyItems[pPadData->m_byteHistoryIndex].m_dwLastUpdate = CGameFunction::GetTimeOfDay();
						}
					}

					// Swap the local players pad with the remote players pad
					memcpy(pPad->GetPad(), pContextData->GetPad()->GetPad(), sizeof(EFLC::IPad));

					// Flag ourselves as no longer in local context
					g_bInLocalContext = false;
				}
				else {
					// Restore the local players pad
					memcpy(pPad->GetPad(), &g_localPad, sizeof(EFLC::IPad));

					g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex(g_uiLocalPlayerIndex, g_pLocalPlayerInfo);

					// Flag ourselves as back in local context
					g_bInLocalContext = true;
				}
			}
		}
		else
			CLogFile::Printf("ContextSwitch Warning: Invalid Player Ped");
	}
}

void _declspec(naked) CPlayerPed__ProcessInput_Hook()
{
	_asm	mov g_pPed, ecx;
	_asm	pushad;

	ContextSwitch(g_pPed, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CPlayerPed__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pPed, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CAutomobile_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CAutomobile__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CBike_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CBike__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CBoat_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CBoat__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CTrain_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CTrain__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CHeli_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CHeli__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CPlane_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, false);
	
	_asm	popad;
	_asm	call COffsets::FUNC_CPlane__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

struct thisisathiscall
{
	static EFLC::IPad* __thiscall GetPadFromPlayerPed(EFLC::IPed* pPed);
};

EFLC::IPad* thisisathiscall::GetPadFromPlayerPed(EFLC::IPed* pPed)
{
	if (pPed && pPed->m_pPlayerInfo && pPed->m_pPlayerInfo->m_bytePlayerNumber == 0 && pPed->m_byteIsPlayerPed) {
		// return the local player pad
		//CLogFile::Printf("Return local pad");
		return ((EFLC::IPad*(__cdecl*)())(g_pCore->GetBase() + 0x7FD960))();
	}
	else if (pPed->m_byteIsPlayerPed) {
		// Do we have a valid ped pointer?
		if (pPed) {
			// Get the remote players context data
			CContextData * pContextData = CContextDataManager::GetContextData((EFLC::IPlayerPed *) pPed);

			// Do we have a valid context data?
			if (pContextData) {
#if 0 // Disabled maybe not needed
				for (int i = 0; i < INPUT_COUNT; i++)
				{
					IVPadData * pPadData = &pContextData->GetPad()->GetPad()->m_padData[i];

					if (pPadData->m_pHistory)
					{
						pPadData->m_byteHistoryIndex++;

						if (pPadData->m_byteHistoryIndex >= MAX_HISTORY_ITEMS)
							pPadData->m_byteHistoryIndex = 0;

						pPadData->m_pHistory->m_historyItems[pPadData->m_byteHistoryIndex].m_byteValue = pPadData->m_byteLastValue;
						pPadData->m_pHistory->m_historyItems[pPadData->m_byteHistoryIndex].m_dwLastUpdate = CGameFunction::GetTimeOfDay();
					}
				}
#endif

				//CLogFile::Printf("Return remote pad");
				// return our sync pad
				return pContextData->GetPad()->GetPad();
			}
		}
	}
	return nullptr;
}

void CContextSwitch::InstallKeySyncHooks()
{
	// CPlayerPed::ProcessInput
	CPatcher::InstallMethodPatch((COffsets::VAR_CPlayerPed__VFTable + 0x74), (DWORD)CPlayerPed__ProcessInput_Hook);
	
	// CAutomobile::ProcessInput
	CPatcher::InstallMethodPatch((COffsets::VAR_CAutomobile__VFTable + 0x74), (DWORD)CAutomobile_ProcessInput_Hook);
	
	// CBike::ProcessInput
	CPatcher::InstallMethodPatch((COffsets::VAR_CBike__VFTable + 0x74), (DWORD)CBike_ProcessInput_Hook);
	
	// CBoat::ProcessInput
	CPatcher::InstallMethodPatch((COffsets::VAR_CBoat__VFTable + 0x74), (DWORD)CBoat_ProcessInput_Hook);
	
	// CTrain::ProcessInput
	CPatcher::InstallMethodPatch((COffsets::VAR_CTrain__VFTable + 0x74), (DWORD)CTrain_ProcessInput_Hook);
	
	// CHeli::ProcessInput
	CPatcher::InstallMethodPatch((COffsets::VAR_CHeli__VFTable + 0x74), (DWORD)CHeli_ProcessInput_Hook);
	
	// CPlane::ProcessInput
	CPatcher::InstallMethodPatch((COffsets::VAR_CPlane__VFTable + 0x74), (DWORD)CPlane_ProcessInput_Hook);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0xA15320, (DWORD) thisisathiscall::GetPadFromPlayerPed);
}