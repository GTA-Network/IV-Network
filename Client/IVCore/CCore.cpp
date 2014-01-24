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

#include	"CCore.h"
#include    <Game/EFLC/CScript.h>
#include	<Scripting/CEvents.h>

extern	CCore			* g_pCore;
bool					g_bDeviceLost = false;

CCore::CCore()
{

}

void OnCreateVM(CScriptVM * pVM)
{
	// Register dat natives
	/*CScriptClasses::Register(pVM);*/
}

bool CCore::Initialize()
{
	// Are we already initialsed?
	if (m_bInitialized)
		return false;
	
	// Log our function call
	PRINT_FUNCTION
	
	// Get the application base address
	m_uiBaseAddress = reinterpret_cast<unsigned int>(GetModuleHandle(NULL));
	
	CLogFile::Printf("Game Base: 0x%p (0x%p)", m_uiBaseAddress, (m_uiBaseAddress - 0x400000));
	
	// Subtract the image size from the base address
	m_uiBaseAddress -= 0x400000;
	
	// Open the settings file
	CSettings::Open(SharedUtility::GetAbsolutePath(CLIENT_SETTINGS_FILE), true, true, true);
	
	// Parse the command line
	CSettings::ParseCommandLine(GetCommandLine());
	
	// Create the game instance
	m_pGame = new CGame;
	
	// Create the graphics instance
	m_pGraphics = new CGraphics;
	
	// Create the network manager instance
	m_pNetworkManager = new CNetworkManager;
	
	// Create the event systems instance
	if (!CEvents::GetInstance())
		new CEvents;

	// Create the resource manager instance
	m_pResourceManager = new CResourceManager("client_resources/resources");
	m_pResourceManager->SetCreateVMCallback(OnCreateVM);

	// Unprotect memory before starting addressing
	m_pGame->UnprotectMemory();
	
	// Intialize the offsets instance
	COffsets::Initialize(m_uiBaseAddress);
	
	// Install the XLive hook
	CXLiveHook::Install();
	
	// Install the cursor hook
	//CCursorHook::Install();
	
	// Setup the game instance
	m_pGame->Setup();
	
	// Apply hook's to game
	CHooks::Intialize();
	
	// Patch game addresses
	CPatches::Initialize();

	// Install crash fixes
	CCrashFixes::Initialize();
	
	// Register module manager
	CModuleManager::FetchModules();
	
	// Initialize the episodes hook
	EpisodeManager::Initialize();

	// Initialize our HTTP connection
	m_pHttpClient = new CHttpClient;
	m_pHttpClient->SetRequestTimeout(10000);
	m_pHttpClient->SetHost(MASTERLIST_URL);

	m_bInitialized = true;

	CLogFile::Printf("Done!");
	return true;
}

void CCore::OnGameLoad()
{
	CLogFile::Print(__FUNCTION__);

	// Initialize game instance & respawn local player
	m_pGame->Initialize();

	// Startup the network module
	m_pNetworkManager->Startup();

	// Set the loading screen not visible
	m_pGraphics->GetLoadingScreen()->SetVisible(false);

	// Set the main menu visible
	m_pGraphics->GetMainMenu()->SetVisible(true);

	// Set the initialize time
	m_uiGameInitializeTime = timeGetTime(); 
}

void CCore::OnGameUpdate()
{
	// Pulse network connection
	if(GetNetworkManager())
		GetNetworkManager()->Pulse();

	// Pulse our IV environment
	if(GetGame())
		GetGame()->Process();
}

void test()
{
	Sleep(500);

	CAudio  *pAudio = new CAudio(g_pCore->GetAudioManager()->GetYoutubeStreamURL("http://www.youtube.com/watch?v=52RP9mGwF1A").Get(), false, true);
	if (pAudio && pAudio->Load())
	{
		g_pCore->GetAudioManager()->Add(pAudio);
		pAudio->Play();
	}

}

void CCore::OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	PRINT_FUNCTION

	// Create our audio manager instance
	m_pAudioManager = new CAudioManager;

	// Initialize our audio manager
	if (!m_pAudioManager->Initialize())
		CLogFile::Printf("CAudioManager::Initialize failed");

	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) test, NULL, 0, NULL);
}

void CCore::OnDeviceLost(IDirect3DDevice9 * pDevice)
{
	PRINT_FUNCTION

	// Mark as lost device
	g_bDeviceLost = true;
}

void CCore::OnDeviceReset(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	PRINT_FUNCTION

	// Mark as not lost device
	g_bDeviceLost = false;
}

void CCore::OnDeviceRender(IDirect3DDevice9 * pDevice)
{
	assert(m_pGraphics);

#ifdef _DEBUG
	char szNetworkStats[10000];
	memset(szNetworkStats, 0, sizeof(szNetworkStats));
	RakNet::StatisticsToString(m_pNetworkManager->GetRakPeer()->GetStatistics(RakNet::UNASSIGNED_SYSTEM_ADDRESS), szNetworkStats, 2);
	m_pGraphics->DrawText(26.0f, 500.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, DT_NOCLIP, true, szNetworkStats);
#endif

	// Print our IVNetwork "Identifier" in the left upper corner
	unsigned short usPing = m_pNetworkManager ? (m_pNetworkManager->IsConnected() ? (GetGame()->GetLocalPlayer() ? GetGame()->GetLocalPlayer()->GetPing() : -1) : -1) : -1;

	CString strConnection;
	int iConnectTime = GetGameLoadInitializeTime() != 0 ? (int)((timeGetTime() - GetGameLoadInitializeTime()) / 1000) : 0;

	CString strSeconds;
	if (iConnectTime > 0) {
		strSeconds.AppendF(" | Running since ");

		int iSeconds = iConnectTime % 60;
		int iMinutes = (iConnectTime / 60) % 60;
		int iHours = (iConnectTime / 60 / 60) % 24;
		int iDays = (iConnectTime / 60 / 60 / 24);

		if(iDays > 0)
		{
			if(iDays > 9)
				strSeconds.AppendF("%d Days, ", iDays);
			else
				strSeconds.AppendF("%d Day%s, ", iDays, iDays > 1 ? "s" : "");
		}
		if(iHours > 0)
		{
			if(iHours > 9)
				strSeconds.AppendF("%d Hours, ",iHours);
			else
				strSeconds.AppendF("0%d Hour%s, ",iHours, iHours > 1 ? "s" : "");
		}
		if(iMinutes > 0)
		{
			if(iMinutes > 9)
				strSeconds.AppendF("%d Minutes, ",iMinutes);
			else
				strSeconds.AppendF("0%d Minute%s, ",iMinutes, iMinutes > 1 ? "s" : "");
		}

		if (iSeconds > 9)
			strSeconds.AppendF("%d Seconds", iSeconds);
		else
			strSeconds.AppendF("0%d Second%s", iSeconds, iSeconds > 1 ? "s" : "");
	}

#ifdef _DEBUG
	/*if(GetGame()->GetLocalPlayer())
		CDevelopment::DrawPedTasks(GetGame()->GetLocalPlayer()->GetPlayerPed());

	if (GetGame()->GetPlayerManager())
	if (GetGame()->GetPlayerManager()->DoesExists(1))
	{
		CDevelopment::DrawPedTasks(GetGame()->GetPlayerManager()->GetAt(1)->GetPlayerPed(), 600);
	}*/

	if (GetGame()->GetLocalPlayer())
		g_pCore->GetGraphics()->DrawText(600.0f + 0, 26.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, DT_NOCLIP, true, GetGame()->GetLocalPlayer()->GetDebugText().Get());
	
	if (GetGame()->GetPlayerManager())
		if (GetGame()->GetPlayerManager()->DoesExists(1))
			g_pCore->GetGraphics()->DrawText(600.0f + 600, 26.0f, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, DT_NOCLIP, true, GetGame()->GetPlayerManager()->GetAt(1)->GetDebugText().Get());
#endif

	CString strInformation = usPing == 0xFFFF ? CString("%s%s", MOD_NAME " " VERSION_IDENTIFIER, strSeconds.Get()) : CString("%s%s | Ping %hu", MOD_NAME " " VERSION_IDENTIFIER, strSeconds.Get(), usPing);
	
	if(GetGame()->GetLocalPlayer())
		m_pGraphics->DrawText(60.0f, 5.0f, D3DCOLOR_ARGB(255, 0, 195, 255), 1.0f, DT_NOCLIP, true, strInformation.Get());

	// Check if our snap shot write failed
	if(CSnapShot::IsDone()) 
	{
		if(CSnapShot::HasSucceeded())
			GetGraphics()->GetChat()->Print(CString("Screenshot written (%s).", CSnapShot::GetWriteName().Get()));
		else
			GetGraphics()->GetChat()->Print(CString("Screenshot write failed (%s).", CSnapShot::GetError().Get()));

		CSnapShot::Reset();
	}

	GetGraphics()->Render();
}