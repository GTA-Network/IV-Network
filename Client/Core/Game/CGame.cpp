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

#include "CGame.h"
#include <CCore.h>

#include <Game/EFLC/CHud.h>
#include <Game/EFLC/CWeather.h>
#include <Game/EFLC/CModelInfo.h>
#include <General/CException.h>
#include <Game/EFLC/CScript.h>

extern	CCore				* g_pCore;

CGame::CGame() : 
	m_pLocalPlayer(nullptr),
	m_pPad(nullptr),
	m_pTaskManager(nullptr),
	m_pPool(nullptr),
	m_pCamera(nullptr),
	m_pPlayerManager(nullptr),
	m_pVehicleManager(nullptr),
	m_pActorManager(nullptr),
	m_pObjectManager(nullptr),
	m_pFireManager(nullptr),
	m_pPickupManager(nullptr),
	m_p3DLabelManager(nullptr),
	m_pBlipManager(nullptr),
	m_pCheckpointManager(nullptr),
	m_pTrafficLights(nullptr)
{

}

CGame::~CGame()
{

}

void CGame::Setup()
{
	// Create new civpad instance
	m_pPad = new EFLC::CPad((EFLC::IPad *)COffsets::VAR_Pads);
	
	// Create task manager instance
	m_pTaskManager = new CTaskManager;
	
	// Create new pool instance
	m_pPool = new CPools;
	
	// Create new traffic lights instance
	m_pTrafficLights = new CTrafficLights;
	
#ifndef TASKINFO_TEST
	// Install our switches/patches
	CContextSwitch::InstallKeySyncHooks();
#endif

	// Setup the weapon handle hook
	//CWeaponHandler::InstallAimSyncHooks();

	// Setup the traffic handle hook
	CTrafficHandler::InstallTrafficHook();
	CTrafficHandler::InstallTrafficLightsHook();
	
	// Initialize our model info array
	for(int i = 0; i < NUM_ModelInfos; i++)
		m_modelInfos[i].SetIndex(i);
	
	// Initialize our weapon info array
	for(int i = 0; i < NUM_WeaponInfos; i++)
	{
		m_weaponInfos[i].SetType((EFLC::eWeaponType)i);
		m_weaponInfos[i].SetWeaponInfo((EFLC::IWeaponInfo *)((g_pCore->GetBase() + ARRAY_WeaponInfos) + (i * sizeof(EFLC::IWeaponInfo))));
		m_weaponInfos[i].GetWeaponInfo()->m_wAmmoMax = 0xFFFF;
	}
	
	// Hide the chat
	g_pCore->GetGraphics()->GetChat()->SetVisible(false);
}

void CGame::Initialize()
{
	// Initialize/Patch our pools(IPed,IVehicle,IVTask)
	m_pPool->Initialize();

	if(!m_pCamera)
		m_pCamera = new CCamera;

	if(!m_pPlayerManager)
		m_pPlayerManager = new CPlayerManager;

	if(!m_pVehicleManager)
		m_pVehicleManager = new CVehicleManager;

	if(!m_pActorManager)
		m_pActorManager = new CActorManager;

	if(!m_pObjectManager)
		m_pObjectManager = new CObjectManager;

	if(!m_pFireManager)
		m_pFireManager = new CFireManager;

	if(!m_pPickupManager)
		m_pPickupManager = new CPickupManager;

	if(!m_p3DLabelManager)
		m_p3DLabelManager = new C3DLabelManager;

	if(!m_pBlipManager)
		m_pBlipManager = new CBlipManager;

	if(!m_pCheckpointManager)
		m_pCheckpointManager = new CCheckpointManager;
	
	if (m_pLocalPlayer)
		SAFE_DELETE(m_pLocalPlayer);

	if (!m_pLocalPlayer)
		m_pLocalPlayer = new CLocalPlayer;

	Reset();
}

void CGame::Reset()
{
	// Disconnect from network
	g_pCore->GetNetworkManager()->Disconnect();

	if (m_pCamera)
		m_pCamera->Reset();

	if (m_pPlayerManager)
		m_pPlayerManager->Reset();

	if (m_pVehicleManager)
		m_pVehicleManager->Reset();

	if (m_pActorManager)
		m_pActorManager->Reset();

	if (m_pObjectManager)
		m_pObjectManager->Reset();

	if (m_pFireManager)
		m_pFireManager->Reset();

	if (m_pPickupManager)
		m_pPickupManager->Reset();

	if (m_p3DLabelManager)
		m_p3DLabelManager->Reset();

	if (m_pBlipManager)
		m_pBlipManager->Reset();

	if (m_pCheckpointManager)
		m_pCheckpointManager->Reset();

	EFLC::CWeather::SetWeather(WEATHER_SUNNY);
	m_pTrafficLights->Reset();

	// Make our local player ready to port to the default spawn position
	m_pLocalPlayer->Respawn();
	m_pCamera->SetCamBehindPed(m_pLocalPlayer->GetScriptingHandle());
	m_pLocalPlayer->SetPlayerControlAdvanced(true, true, true);

	// Enable UI elements to be visible
	EFLC::CHud::SetHudVisible(true);
	EFLC::CHud::SetRadarVisible(true);
	EFLC::CHud::SetAreaNamesEnabled(true);
	EFLC::CHud::SetPlayerNamesVisible(true);
	// Update our environment settings and set default timemanagement data
	//g_pCore->GetTimeManagementInstance()->SetTime(7,0);
	//g_pCore->GetTimeManagementInstance()->SetMinuteDuration(60000); // 60 seconds, default
}

void CGame::UnprotectMemory()
{
	BYTE								   *pImageBase = (BYTE *)(g_pCore->GetBase() + 0x400000);
	PIMAGE_DOS_HEADER						pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	PIMAGE_NT_HEADERS						pNtHeader  = (PIMAGE_NT_HEADERS)(pImageBase + pDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER					pSection = IMAGE_FIRST_SECTION(pNtHeader);
	char								   *pszSectionName; 

	for(int iSection = 0; iSection < pNtHeader->FileHeader.NumberOfSections; iSection++, pSection++) {
		// Set value for compare
		pszSectionName = (char *)pSection->Name;

		// Compare and check if the given memory segment identifier compares with our given segments
		if(!strcmp(pszSectionName, ".text") || !strcmp(pszSectionName, ".rdata"))
			CPatcher::Unprotect((DWORD)(pImageBase + pSection->VirtualAddress), ((pSection->Misc.VirtualSize + 4095) & ~4095));
	}

}

EFLC::CModelInfo * CGame::GetModelInfo(int iModelIndex)
{
	// Loop through all ModelInfo array indexes and return if a match was found
	if(iModelIndex < NUM_ModelInfos && iModelIndex >= 0 && m_modelInfos[iModelIndex].IsValid())
		return &m_modelInfos[iModelIndex];

	return nullptr;
}

EFLC::CWeaponInfo * CGame::GetWeaponInfo(EFLC::eWeaponType weaponType)
{
    if(weaponType < NUM_WeaponInfos && weaponType >= 0)
            return &m_weaponInfos[weaponType];

	return nullptr;
}

HWND CGame::GetGameWindow()
{
	return (*(HWND *)(g_pCore->GetBase() + 0x1849DD4));
}

void CGame::ThrowInternalException(DWORD dwAddress, DWORD dwExceptionType)
{
	CLogFile::Printf("Warning: Exception 0x%p at 0x%p", dwExceptionType, dwAddress);
}

void CGame::Process()
{
	if(!GetLocalPlayer())
		return;

	if (m_pPlayerManager)
		m_pPlayerManager->Pulse();

	if (m_pVehicleManager)
		m_pVehicleManager->Pulse();

	if (m_pCheckpointManager)
		m_pCheckpointManager->Pulse();

	// LocalPlayer should be in playermanager! Remove this?
	if (m_pLocalPlayer)
		m_pLocalPlayer->Pulse();

	/*unsigned char ucHour = 0, ucMinute = 0; // deleted by jmpback from func
	int uGameHour = 0, uGameMinute = 0; // deleted by jmpback from func

	// Grab the latest time from our time interface
	g_pCore->GetTimeManagementInstance()->GetTime(&ucHour, &ucMinute);

	// Check if our time has changed
	CGameFunction::GetTime(&uGameHour, &uGameMinute);

	// Check if the game time is not the same as the given CTime
	if((uGameHour-ucHour < -1 || ucHour-uGameHour < -1)|| (uGameMinute-ucMinute < -10 || ucMinute-uGameHour < -10)) {
		// Force game to update the time to the latest given data
		CGameFunction::SetTimeOfDay(ucHour, ucMinute);
	}
	else if(uGameHour == ucHour || uGameMinute == ucHour) {
		// Update time to latest
		CGameFunction::SetTimeOfDay(uGameHour, uGameMinute);
	}
	else {
		// Let the game render the time by itself(so it's not so buggy when updating the time)
		;
	}*/
}