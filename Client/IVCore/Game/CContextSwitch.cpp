//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CContextSwitch.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CContextSwitch.h"
#include "CContextData.h"
#include <Game/COffsets.h>
#include <Patcher/CPatcher.h>
#include <Game/IVEngine/CIVPad.h>
#include <Game/IVEngine/CIVVehicle.h>
#include "CPools.h"
#include <CLogFile.h>
#include <CCore.h>

IVPed      * g_pPed = NULL;
IVVehicle  * g_pKeySyncIVVehicle = NULL;
unsigned int g_uiLocalPlayerIndex = 0;
IVPad        g_localPad;
bool         g_bInLocalContext = true;
extern CCore *g_pCore;
IVPlayerInfo* g_pLocalPlayerInfo = NULL;

void ContextSwitch(IVPed * pPed, bool bPost) 
{
	// Do we have a valid ped pointer?
	if(pPed) {
		// Get the remote players context data
		CContextData * pContextData = CContextDataManager::GetContextData((IVPlayerPed *)pPed);

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
				CIVPad * pPad = g_pCore->GetGame()->GetPad();

				if(!bPost) {
					// Store the local players index
					g_uiLocalPlayerIndex = g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex();

					// Store the local players pad
					memcpy(&g_localPad, pPad->GetPad(), sizeof(IVPad));

					g_pLocalPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(g_uiLocalPlayerIndex);

					g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex(g_uiLocalPlayerIndex, pContextData->GetPlayerInfo()->GetPlayerInfo());

					// Set the history values
					for(int i = 0; i < INPUT_COUNT; i++) {
						IVPadData * pPadData = &pContextData->GetPad()->GetPad()->m_padData[i];

						if(pPadData->m_pHistory) {
							pPadData->m_byteHistoryIndex++;

							if(pPadData->m_byteHistoryIndex >= MAX_HISTORY_ITEMS)
								pPadData->m_byteHistoryIndex = 0;

							pPadData->m_pHistory->m_historyItems[pPadData->m_byteHistoryIndex].m_byteValue = pPadData->m_byteLastValue;
							pPadData->m_pHistory->m_historyItems[pPadData->m_byteHistoryIndex].m_dwLastUpdate = CGameFunction::GetTimeOfDay();
						}
					}

					// Swap the local players pad with the remote players pad
					memcpy(pPad->GetPad(), pContextData->GetPad()->GetPad(), sizeof(IVPad));

					// Flag ourselves as no longer in local context
					g_bInLocalContext = false;
				}
				else {
					// Restore the local players pad
					memcpy(pPad->GetPad(), &g_localPad, sizeof(IVPad));

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

_declspec(naked) void __stdcall CPlayerPed__ProcessInput_Hook()
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
	_asm	mov g_pKeySyncIVVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CAutomobile__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CBike_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CBike__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CBoat_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CBoat__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CTrain_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CTrain__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CHeli_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, false);

	_asm	popad;
	_asm	call COffsets::FUNC_CHeli__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

void _declspec(naked) CPlane_ProcessInput_Hook()
{
	_asm	mov g_pKeySyncIVVehicle, ecx;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, false);
	
	_asm	popad;
	_asm	call COffsets::FUNC_CPlane__ProcessInput;
	_asm	pushad;

	ContextSwitch(g_pKeySyncIVVehicle->m_pDriver, true);

	_asm	popad;
	_asm	ret;
}

IVPed* g_pPadFromPed_Ped = nullptr;
IVPad* syncPad = nullptr;

IVPad* GetPadFromPlayerPed(IVPed* pPed)
{
	if (pPed && pPed->m_bytePlayerNumber == 0 && pPed->m_byteIsPlayerPed) {
		// return the local player pad
		CLogFile::Printf("Return local pad");
		return ((IVPad*(__cdecl*)())(g_pCore->GetBase() + 0x7FD960))();
	}
	else if (pPed->m_byteIsPlayerPed) {
		// Do we have a valid ped pointer?
		if (pPed) {
			// Get the remote players context data
			CContextData * pContextData = CContextDataManager::GetContextData((IVPlayerPed *) pPed);

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

				CLogFile::Printf("Return remote pad");
				// return our sync pad
				return pContextData->GetPad()->GetPad();
			}
		}
	}
	return nullptr;
}

_declspec(naked) void GetPadFromPed()
{
	_asm	mov g_pPadFromPed_Ped, ecx;
	_asm	pushad;

	syncPad = GetPadFromPlayerPed(g_pPadFromPed_Ped);

	_asm	popad;
	_asm	mov eax, syncPad;
	_asm	retn;
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

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0xA15320, (DWORD) GetPadFromPed);
}