//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CGame.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//=================================================================================================

#include "CGame.h"
#include <CCore.h>

#include <Game/IVEngine/CIVHud.h>
#include <Game/IVEngine/CIVWeather.h>
#include <Game/IVEngine/CIVModelInfo.h>
#include <General/CException.h>
#include <Game/CGameFiles.h>
#include <IV/CIVScript.h>

extern	CCore				* g_pCore;
bool bHudImageInitialized	= false;

CLocalPlayer				*CGame::m_pLocalPlayer = 0;
CIVPad						*CGame::m_pPad = 0;
CTaskManager				*CGame::m_pTaskManager = 0;
CPools						*CGame::m_pPool = 0;
CCamera						*CGame::m_pCamera = 0;
CPlayerManager				*CGame::m_pPlayerManager = 0;
CVehicleManager				*CGame::m_pVehicleManager = 0;
CActorManager				*CGame::m_pActorManager = 0;
CObjectManager				*CGame::m_pObjectManager = 0;
CFireManager				*CGame::m_pFireManager = 0;
CPickupManager				*CGame::m_pPickupManager = 0;
C3DLabelManager				*CGame::m_p3DLabelManager = 0;
CBlipManager				*CGame::m_pBlipManager = 0;
CCheckpointManager			*CGame::m_pCheckpointManager = 0;
CCharacterManager			*CGame::m_pCharacterManager = 0;
bool						CGame::m_LocalPlayerInitialised = 0;
CIVModelInfo				CGame::m_modelInfos[NUM_ModelInfos];
CIVWeaponInfo				CGame::m_weaponInfos[NUM_WeaponInfos];
CTrafficLights				*CGame::m_pTrafficLights = 0;
CString						CGame::m_strEFLCDirectory = 0;
IVManagement				*CGame::m_pManagement = 0;
InternalThread				CGame::m_Threads[254];
bool						CGame::m_bRadarVisibility = 0;

void CGame::Setup()
{
	// Mark client-state as world-game loading
	g_pCore->SetClientState(GAME_STATE_LOADING);
	
	// Create new civpad instance
	m_pPad = new CIVPad((IVPad *)COffsets::VAR_Pads);
	
	// Create task manager instance
	m_pTaskManager = new CTaskManager;
	
	// Create the character manager instance
	m_pCharacterManager = new CCharacterManager;
	
	// Create new pool instance
	m_pPool = new CPools;

	// Create new ivmanagement instance
	m_pManagement = new IVManagement;
	
	// Create new traffic lights instance
	m_pTrafficLights = new CTrafficLights;
	
	// Install our switches/patches
	CContextSwitch::InstallKeySyncHooks();

	// Setup the weapon handle hook
	//CWeaponHandler::InstallAimSyncHooks();

	// Setup the traffic handle hook
	CTrafficHandler::InstallTrafficHook();
	CTrafficHandler::InstallTrafficLightsHook();
	
	// Initialise our model info array
	for(int i = 0; i < NUM_ModelInfos; i++)
		m_modelInfos[i].SetIndex(i);
	
	// Initialize our weapon info array
	for(int i = 0; i < NUM_WeaponInfos; i++)
	{
		m_weaponInfos[i].SetType((eWeaponType)i);
		m_weaponInfos[i].SetWeaponInfo((IVWeaponInfo *)((g_pCore->GetBase() + ARRAY_WeaponInfos) + (i * sizeof(IVWeaponInfo))));
		m_weaponInfos[i].GetWeaponInfo()->m_wAmmoMax = 0xFFFF;
	}
	
	// Hide the chat
	g_pCore->GetChat()->SetVisible(false);
}

void CGame::Initialise()
{
	// Update client state to state ingame
	g_pCore->SetClientState(GAME_STATE_INGAME);

	// Initialise/Patch our pools(IVPed,IVVehicle,IVTask)
	m_pPool->Initialize();

	// Create our camera instance if it doesn't exist/isn't created yet
	if(!m_pCamera)
		m_pCamera = new CCamera;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pPlayerManager)
		m_pPlayerManager = new CPlayerManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pVehicleManager)
		m_pVehicleManager = new CVehicleManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pActorManager)
		m_pActorManager = new CActorManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pObjectManager)
		m_pObjectManager = new CObjectManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pFireManager)
		m_pFireManager = new CFireManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pPickupManager)
		m_pPickupManager = new CPickupManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_p3DLabelManager)
		m_p3DLabelManager = new C3DLabelManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pBlipManager)
		m_pBlipManager = new CBlipManager;

	// Create our manager instance if it doesn't exist/isn't created yet
	if(!m_pCheckpointManager)
		m_pCheckpointManager = new CCheckpointManager;
	
	OnEnvironmentStartUp(false);

	PrepareWorld();
}

void CGame::OnEnvironmentStartUp(bool bForce)
{
	// Grab the PlayerInfo array index 0 from the PedPool
	IVPlayerInfo * pPlayerInfo = m_pPool->GetPlayerInfoFromIndex(0);
	IVPlayerPed  * _pPlayerPed = NULL;

	// Check if we got an index from PedPool - index 0
	if(pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else
		_pPlayerPed = NULL;

	// If no index was found and the param bForce isn't given, return
	if(m_pPool->GetLocalPlayerIndex() == -1) {
		if(!bForce)
			return;
	}

	// We should force to create the localplayer so continue.. Setting initialise pointer to opposit value(false->true)
	m_LocalPlayerInitialised = !m_LocalPlayerInitialised;

	CLogFile::Printf("[%s] Creating Player..",__FUNCTION__);

	// Check if our local player class not existing, otherwise create it
	if(!m_pLocalPlayer)
		m_pLocalPlayer = new CLocalPlayer;

	CLogFile::Printf("[%s] Successfully create local player instance..",__FUNCTION__);
}

void CGame::Reset()
{
	// Disconnect from network
	g_pCore->GetNetworkManager()->Disconnect();

	// Delte our instance if it exists/is created
	if(m_pCamera)
		SAFE_DELETE(m_pCamera);

	// Delte our instance if it exists/is created
	if(m_pPlayerManager)
		SAFE_DELETE(m_pPlayerManager);

	// Delte our instance if it exists/is created
	if(m_pVehicleManager)
		SAFE_DELETE(m_pVehicleManager);

	// Delte our instance if it exists/is created
	if(!m_pActorManager)
		SAFE_DELETE(m_pActorManager);

	// Delte our instance if it exists/is created
	if(!m_pObjectManager)
		SAFE_DELETE(m_pObjectManager);

	// Delte our instance if it exists/is created
	if(!m_pFireManager)
		SAFE_DELETE(m_pFireManager);

	// Delte our instance if it exists/is created
	if(!m_pPickupManager)
		SAFE_DELETE(m_pPickupManager);

	// Delte our instance if it exists/is created
	if(!m_p3DLabelManager)
		SAFE_DELETE(m_p3DLabelManager);

	// Delte our instance if it exists/is created
	if(!m_pBlipManager)
		SAFE_DELETE(m_pBlipManager);

	// Delte our instance if it exists/is created
	if(!m_pCheckpointManager)
		SAFE_DELETE(m_pCheckpointManager);

	// Re-initialse our client
	Initialise();

	// Prepare our world
	PrepareWorld();
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

void CGame::RenderRAGEScripts()
{
	// If our loacl player isn't create, try to create it
	if(!m_LocalPlayerInitialised)
		OnEnvironmentStartUp(true);
}

void CGame::PrepareWorld()
{
	// Disable(hide) UI elements to be visible
	CIVHud::SetHudVisible(false);
	CIVHud::SetRadarVisible(false);
	CIVHud::SetAreaNamesEnabled(false);
	CIVHud::SetPlayerNamesVisible(0);

	// Update environment settings and set default
	CIVWeather::SetWeather(WEATHER_SUNNY);
	g_pCore->GetTimeManagementInstance()->SetTime(6,45);
	g_pCore->GetTimeManagementInstance()->SetMinuteDuration(60000); // 60 seconds, default
	m_pTrafficLights->Reset();

	SAFE_DELETE(m_pCamera);
	m_pCamera = new CCamera;
}

void CGame::OnClientReadyToGamePlay()
{
	// Make our local player ready to port to the default spawn position
	m_pLocalPlayer->Respawn();
	m_pCamera->SetCamBehindPed(m_pLocalPlayer->GetScriptingHandle());
	m_pLocalPlayer->SetPlayerControlAdvanced(true, true, true);

	// Enable UI elements to be visible
	CIVHud::SetHudVisible(true);
	CIVHud::SetRadarVisible(true);
	CIVHud::SetAreaNamesEnabled(true);
	CIVHud::SetPlayerNamesVisible(true);
	// Update our environment settings and set default timemanagement data
	//g_pCore->GetTimeManagementInstance()->SetTime(7,0);
	//g_pCore->GetTimeManagementInstance()->SetMinuteDuration(60000); // 60 seconds, default
}

void CGame::OnClientPastGameJoin()
{
	// Preload world stuff
}

CIVModelInfo * CGame::GetModelInfo(int iModelIndex)
{
	// Loop through all ModelInfo array indexes and return if a match was found
	if(iModelIndex < NUM_ModelInfos && iModelIndex >= 0 && m_modelInfos[iModelIndex].IsValid())
		return &m_modelInfos[iModelIndex];

	return NULL;
}

CIVWeaponInfo * CGame::GetWeaponInfo(eWeaponType weaponType)
{
    if(weaponType < NUM_WeaponInfos && weaponType >= 0)
            return &m_weaponInfos[weaponType];

    return NULL;
}

bool CGame::CheckInstances(bool bInitialised)
{
	// Check private class pointers to be valid(prevent game crashes)
	if(!bInitialised)
	{
		CHECK_VALID(m_pPool);
		CHECK_VALID(m_pPad);
		CHECK_VALID(m_pTaskManager);
		CHECK_VALID(m_pCharacterManager);
		CHECK_VALID(m_pCamera);
	}
	else if(bInitialised)
	{
		CHECK_VALID(m_pPool);
		CHECK_VALID(m_pPad);
		CHECK_VALID(m_pTaskManager);
		CHECK_VALID(m_pCharacterManager);
		CHECK_VALID(m_pCamera);
		CHECK_VALID(m_pLocalPlayer);

		CHECK_VALID(m_pPlayerManager);
		CHECK_VALID(m_pVehicleManager);
		CHECK_VALID(m_pActorManager);
		CHECK_VALID(m_pObjectManager);
		CHECK_VALID(m_pFireManager);
		CHECK_VALID(m_pPickupManager);
		CHECK_VALID(m_p3DLabelManager);
		CHECK_VALID(m_pBlipManager);
		CHECK_VALID(m_pCheckpointManager);
		CHECK_VALID(m_pCharacterManager);
	}

	return true;
}

HWND CGame::GetGameWindow()
{
	return (*(HWND *)(g_pCore->GetBase() + 0x1849DD4));
}

void CGame::ThrowInternalException(DWORD dwAddress, DWORD dwExceptionType)
{
	CLogFile::Printf("Warning: Exception 0x%p at 0x%p", dwExceptionType, dwAddress);
}

void CGame::ProcessEnvironment()
{
	if(!g_pCore->GetGame()->GetLocalPlayer())
		return;

	// If our iv management exists, process it
	if (m_pManagement)
		m_pManagement->Pulse();

	// If our player manager exists, process it
	if (m_pPlayerManager)
		m_pPlayerManager->Pulse();

	if (m_pVehicleManager)
		m_pVehicleManager->Pulse();

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

void CGame::SetupGame()
{
	//g_pCore->GetGame()->PrepareWorld();
}

BYTE CGame::CreateInternalThread(DWORD dwStartAddress, LPVOID lpvoidParameters, signed int siThreadId, int iPriority, const char * szThreadName, const char *szComment)
{
	CLogFile::Printf("[%s]: 0x%p, %s, %s", __FUNCTION__, dwStartAddress, szThreadName, szComment);
	g_pCore->GetChat()->Print(CString("[%s]: 0x%p, %s, %s", __FUNCTION__, dwStartAddress, szThreadName, szComment));

	signed int EBP_iThreadId;
	if(siThreadId < 0x4000)
		EBP_iThreadId = 16384;
	else
		EBP_iThreadId = siThreadId;

	BYTE iThreadOffset;
	for(BYTE i = 0; i < ARRAY_LENGTH(m_Threads); i++)
		if(!m_Threads[i].bInitialised) {
			iThreadOffset = i;
			break;
		}

	m_Threads[iThreadOffset].bInitialised = true;
	m_Threads[iThreadOffset].szComment =  szComment;
	m_Threads[iThreadOffset].szThreadTitle = szThreadName;
	m_Threads[iThreadOffset].dwStartAddress = (DWORD)dwStartAddress;
	m_Threads[iThreadOffset].hThreadHandle = CreateThread(0, EBP_iThreadId, (LPTHREAD_START_ROUTINE)dwStartAddress, lpvoidParameters, 0, (LPDWORD)&m_Threads[iThreadOffset].hThreadId);

	if(m_Threads[iThreadOffset].hThreadId) {
		SetThreadPriority(m_Threads[iThreadOffset].hThreadId, iPriority);
		SetThreadPriorityBoost(m_Threads[iThreadOffset].hThreadId, 1);

		ResumeThread(m_Threads[iThreadOffset].hThreadId);
	}

	return iThreadOffset;
}

void CGame::DestroyInternalThread(BYTE byteThreadId)
{
	if(!m_Threads[byteThreadId].bInitialised)
		return;

	TerminateThread(m_Threads[byteThreadId].hThreadHandle, 0);
	m_Threads[byteThreadId].hThreadHandle = NULL;
	m_Threads[byteThreadId].dwStartAddress = NULL;
	m_Threads[byteThreadId].hThreadId = NULL;
	m_Threads[byteThreadId].szComment = "";
	m_Threads[byteThreadId].szThreadTitle = "";
	m_Threads[byteThreadId].bInitialised = false;
}