//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CCore.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CCore.h"

extern	CCore			* g_pCore;
bool					g_bDeviceLost = false;

DWORD WINAPI WaitForGame(LPVOID lpParam)
{
	return 1;
}

CCore::CCore(void)
{
	// Mark as not initialised
	m_bInitialised = false;

	// Mark the game as not loaded
	SetGameLoaded(false);

	// Reset instances
	m_pGame = NULL;
	m_pGraphics = NULL;
	m_pChat = NULL;
	m_pFPSCounter = NULL;
	m_pNetworkManager = NULL;
	m_pGUI = NULL;
}

bool CCore::Initialise()
{
	// Are we already initialsed?
	if(m_bInitialised)
		return false;
	
	PRINT_FUNCTION
	
	// Get the application base address
	m_uiBaseAddress = reinterpret_cast<unsigned int>(GetModuleHandle(NULL));
	
	CLogFile::Printf("Game Base: 0x%p (0x%p)", m_uiBaseAddress, (m_uiBaseAddress - 0x400000));
	
	// Subtract the image size from the base address
	m_uiBaseAddress -= 0x400000;
	
	// Open the settings file
	CSettings::Open(SharedUtility::GetAbsolutePath(CLIENT_SETTINGS_FILE), true, false, true);
	
	// Parse the command line
	CSettings::ParseCommandLine(GetCommandLine());
	
	// Load RAGE Engine
	m_pRAGELibrary = new CLibrary();

	// Did the module fail to load?
	if(m_pRAGELibrary->Load(SharedUtility::GetAbsolutePath("IVEngine.dll")))
	{
		// Get the module function pointers
		m_pEngine = (GetInterface_t)m_pRAGELibrary->GetProcedureAddress("GetInterface");

		if(m_pEngine) {
			RAGEEngineInterface *pTemp = new RAGEEngineInterface;

			// Get the interface
			m_pEngine(pTemp);

			RAGEEngineInterface *m_pInterface = static_cast<RAGEEngineInterface *>(pTemp);

			// Initialise the interface
			m_pInterface->Initialise();
		}
	}
	else {
		// Delete the library instance
		SAFE_DELETE(m_pRAGELibrary);
	}

	// Create the game instance
	m_pGame = new CGame;

	// Create the time instance
	m_pTimeManagement = new CTime;
	
	// Create the graphics instance
	m_pGraphics = new CGraphics;
	
	// Create the fps counter instance
	m_pFPSCounter = new CFPSCounter;
	
	// Create the network manager instance
	m_pNetworkManager = new CNetworkManager;
	
	// Create the development instance
	m_pDevelopment = new CDevelopment;
	
	// Create the chat instance
	m_pChat = new CChat(30, 80);
	
	// Unprotect memory before starting addressing
	m_pGame->UnprotectMemory();
	
	// Intialize the offsets instance
	COffsets::Initialize(m_uiBaseAddress);
	
	// Install the XLive hook
	CXLiveHook::Install();
	
	// Install the cursor hook
	CCursorHook::Install();
	
	// Setup the game instance
	m_pGame->Setup();
	
	// Apply hook's to game
	CHooks::Intialize();
	
	// Patch game addresses
	CPatches::Initialize();
	
	// Setup the development instance
	m_pDevelopment->SetDebugView(true);
	
	// Get loaded modules from our process
	GetLoadedModulesList();
	
	// Register module manager
	CModuleManager::FetchModules();
	
	CLogFile::Printf("Done!");
	return true;
}

void CCore::OnGameLoad()
{
	// Is the game already loaded?
	if(IsGameLoaded())
		return;

	CLogFile::Print(__FUNCTION__);

	// Initialize game instance & respawn local player
	GetGame()->Initialise();

	// Remove all stuff from directx device(which is drawn)
	m_pGraphics->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0),1.0f,0);

	// Mark the game as loaded
	SetGameLoaded(true);

	// Mark chat as visible & print welcome message
	m_pChat->SetVisible(true);
	m_pChat->Outputf(true, "#ffffff%s  #ff6600%s   #ffffffstarted!", MOD_NAME, MOD_VERSION_STRING );

	m_strHost = "127.0.0.1";
	m_usPort = 9999;
	m_strNick = "IVPlayer";

	// Startup the network module
	m_pNetworkManager->Startup();

	// Connect to the network
	m_pNetworkManager->Connect(GetHost(), (unsigned short)GetPort(), GetPass());

	// Set the initialize time
	m_uiGameInitializeTime = timeGetTime();
}

void CCore::OnGamePreLoad()
{
	// Is the game loaded?
	if(IsGameLoaded())
		return;

	// Create a thread to wait for the game
	CreateThread(0, 0, WaitForGame, 0, 0, 0); // Remove thread ? 
}

void CCore::OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	PRINT_FUNCTION

	// Setup the chat
	if(m_pChat)
		m_pChat->Setup(pPresentationParameters);

	m_pGUI = new CGUI(pDevice);
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

	if (m_pGUI)
	{
		m_pGUI->SetScreenSize(pPresentationParameters->BackBufferWidth, pPresentationParameters->BackBufferHeight);
	}

	// Mark as not lost device
	g_bDeviceLost = false;
}

void CCore::OnDevicePreRender()
{
	;
}

void CCore::OnDeviceRender(IDirect3DDevice9 * pDevice)
{
	// Prerender devices
	OnDevicePreRender();

	// Has the device been lost?
	if(g_bDeviceLost || !m_pGraphics)
		return;

	// Print our IVMultiplayer "Identifier" in the left upper corner
	unsigned short usPing = m_pNetworkManager != NULL ? (m_pNetworkManager->IsConnected() ? (g_pCore->GetGame()->GetLocalPlayer() ? g_pCore->GetGame()->GetLocalPlayer()->GetPing() : -1) : -1) : -1;

	CString strConnection;
	int iConnectTime = (int)((timeGetTime() - GetGameLoadInitializeTime())/1000);

	CString strSeconds;
	if(iConnectTime > 0) {
		int iSeconds = iConnectTime % 60;
		int iMinutes = (iConnectTime / 60) % 60;
		int iHours = (iConnectTime / 60 / 60) % 24;
		int iDays = (iConnectTime / 60 / 60 / 24);

		if(iDays > 0)
		{
			if(iDays > 9)
				strSeconds.AppendF("%d Days,", iDays);
			else
				strSeconds.AppendF("%d Day%s,", iDays, iDays > 1 ? "s" : "");
		}
		if(iHours > 0)
		{
			if(iHours > 9)
				strSeconds.AppendF(" %d Hours,",iHours);
			else
				strSeconds.AppendF(" 0%d Hour%s,",iHours, iHours > 1 ? "s" : "");
		}
		if(iMinutes > 0)
		{
			if(iMinutes > 9)
				strSeconds.AppendF(" %d Minutes,",iMinutes);
			else
				strSeconds.AppendF(" 0%d Minute%s,",iMinutes, iMinutes > 1 ? "s" : "");
		}

		strSeconds.AppendF("%d Second%s",iSeconds, iSeconds > 1 ? "s" : "");
	}

	// Simulate temporary loading symbol
	m_byteLoadingStyle++;
	CString strLoadingInformation;
	if(m_byteLoadingStyle >= 10 && m_byteLoadingStyle < 20)
		strLoadingInformation = CString(MOD_NAME " " VERSION_IDENTIFIER " - Loading.. Hold on /").Get();
	else if(m_byteLoadingStyle >= 20 && m_byteLoadingStyle < 30)
		strLoadingInformation = CString(MOD_NAME " " VERSION_IDENTIFIER " - Loading.. Hold on -").Get();
	else if(m_byteLoadingStyle >= 30 && m_byteLoadingStyle < 40)
		strLoadingInformation = CString(MOD_NAME " " VERSION_IDENTIFIER " - Loading.. Hold on \\").Get();
	else if(m_byteLoadingStyle >= 40 && m_byteLoadingStyle < 50)
		strLoadingInformation = CString(MOD_NAME " " VERSION_IDENTIFIER " - Loading.. Hold on -").Get();
	else if(m_byteLoadingStyle == 50) {
		strLoadingInformation = CString(MOD_NAME " " VERSION_IDENTIFIER " - Loading.. Hold on").Get();
		m_byteLoadingStyle = 9;
	}

	CString strInformation = CString("%s | Running since %s | Ping %hu", VERSION_IDENTIFIER, strSeconds.Get(), usPing);
	
	if(!g_pCore->GetGame()->GetLocalPlayer())
		m_pGraphics->DrawText(55.0f, 5.0f, D3DCOLOR_ARGB(255, 0, 195, 255), 1.0f, 5, DT_NOCLIP, (bool)true, strLoadingInformation.Get());
	else
		m_pGraphics->DrawText(55.0f, 5.0f, D3DCOLOR_ARGB(255, 0, 195, 255), 1.0f, 5, DT_NOCLIP, (bool)true, strInformation.Get());
	
	strSeconds.Clear();
	strInformation.Clear();

	// Render our chat instance
	if(m_pChat && m_pChat->IsVisible())
		m_pChat->Render();

	// Before rendering FPS-Counter instance, update FPS display
	m_pGraphics->DrawText(5.0f, 5.0f, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("FPS: %d", m_pFPSCounter->GetFPS()).Get());

	// Render our FPS-Counter instance
	if(m_pFPSCounter)
		m_pFPSCounter->Pulse();

	// Render our development instance
	if(m_pDevelopment)
		m_pDevelopment->Process();

	// Render our time management
	m_pTimeManagement->Pulse();

	// Render ingame environment
	m_pGame->ProcessEnvironment();

	// Render ingame ui elements
	m_pGame->RenderUIElements();

	// Check if our snap shot write failed
	if(CSnapShot::IsDone())
	{
		if(CSnapShot::HasSucceeded())
			m_pChat->Outputf(false, "Screen shot written (%s).", CSnapShot::GetWriteName().Get());
		else
			m_pChat->Outputf(false, "Screen shot write failed (%s).", CSnapShot::GetError().Get());

		CSnapShot::Reset();
	}
	
	#define CAM1 g_pCore->GetGame()->GetCamera()->GetGameCam()->GetCam()->m_data1
	#define CAM2 g_pCore->GetGame()->GetCamera()->GetGameCam()->GetCam()->m_data1
	#define CAM3 g_pCore->GetGame()->GetCamera()->GetGameCam()->GetCam()->m_data1

	if(g_pCore->GetGame()->GetCamera()) {
		/*
		CAM1.m_fFar = CAM1.m_fFar*2;
		CAM1.m_fFarDOF = CAM1.m_fFarDOF*2;
		CAM1.m_fFOV = CAM1.m_fFOV*2;
		CAM1.m_fMotionBlur = CAM1.m_fMotionBlur*2;
		CAM1.m_fNear = CAM1.m_fNear*2;
		CAM1.m_fNearDOF = CAM1.m_fNearDOF*2;
		CAM1.m_fUnknown = CAM1.m_fUnknown*2;
		CAM1.m_fUnknown2 = CAM1.m_fUnknown2*2;
		CAM1.m_fUnknown3 = CAM1.m_fUnknown3*2;

		CAM2.m_fFar = CAM2.m_fFar*2;
		CAM2.m_fFarDOF = CAM2.m_fFarDOF*2;
		CAM2.m_fFOV = CAM2.m_fFOV*2;
		CAM2.m_fMotionBlur = CAM2.m_fMotionBlur*2;
		CAM2.m_fNear = CAM2.m_fNear*2;
		CAM2.m_fNearDOF = CAM2.m_fNearDOF*2;
		CAM2.m_fUnknown = CAM2.m_fUnknown*2;
		CAM2.m_fUnknown2 = CAM2.m_fUnknown2*2;
		CAM2.m_fUnknown3 = CAM2.m_fUnknown3*2;
		
		CAM3.m_fFOV = CAM3.m_fFOV*2;
		CAM3.m_fFar = CAM3.m_fFar*2;
		CAM3.m_fFarDOF = CAM3.m_fFarDOF*2;
		CAM3.m_fMotionBlur = CAM3.m_fMotionBlur*2;
		CAM3.m_fNear = CAM3.m_fNear*2;
		CAM3.m_fNearDOF = CAM3.m_fNearDOF*2;
		CAM3.m_fUnknown = CAM3.m_fUnknown*2;
		CAM3.m_fUnknown2 = CAM3.m_fUnknown2*2;
		CAM3.m_fUnknown3 = CAM3.m_fUnknown3*2;*/
	}

	if (m_pGUI)
	{
		m_pGUI->Render();
	}

	pDevice->Present(NULL,NULL,NULL,NULL);
}

void CCore::GetLoadedModulesList()
{
	DWORD aProcesses[1024]; 
    DWORD cbNeeded; 
    DWORD cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return;

    cProcesses = cbNeeded / sizeof(DWORD);

    for ( i = 0; i < cProcesses; i++ )
    {
		if(aProcesses[i] == GetProcessId(GetCurrentProcess()))
			GetLoadedModule( aProcesses[i] );
    }
}

void CCore::GetLoadedModule(DWORD dwProcessId)
{
	HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,
                            FALSE, dwProcessId );
    if (NULL == hProcess)
        return;

    if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ ) {
            TCHAR szModName[MAX_PATH];
            if ( GetModuleFileNameExA(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
			  CString strModule;

			  std::string strModulee;
			  strModulee.append(szModName);
			  std::size_t found = strModulee.find("SYSTEM32",10);
			  std::size_t found2 = strModulee.find("system32",10);
			  std::size_t found3 = strModulee.find("AppPatch",10);
			  std::size_t found4 = strModulee.find("WinSxS", 10);

			  if(found!=std::string::npos || found2!=std::string::npos || found3!=std::string::npos || found4!=std::string::npos)
			  {
				//strModule.AppendF("--> %s", szModName);
				//CLogFile::Printf("  %s (0x%08X)",strModule.Get(), hMods[i] ); 
			  }//;//strModule.AppendF("%i, %s",found, szModName);
			  else {
				strModule.AppendF("--> IVModules: %s", szModName);
				CLogFile::Printf("  %s (0x%08X)",strModule.Get(), hMods[i] );
			  }
            }
        }
    }
    CloseHandle(hProcess);
    return;
}

void CCore::OnNetworkShutDown()
{
	// Call destructor of cgame
	g_pCore->GetGame()->~CGame();
}

void CCore::OnNetworkTimeout()
{
	// Call reinitialise cgame
	g_pCore->GetGame()->Reset();
}

void CCore::DumpVFTable(DWORD dwAddress, int iFunctionCount)
{
	CLogFile::Printf("Dumping Virtual Function Table at 0x%p...",dwAddress);

	for(int i = 0; i < iFunctionCount; i++)
		CLogFile::Printf("VFTable Offset: %d, Function: 0x%p (At Address: 0x%p)", (i * 4), *(PDWORD)(dwAddress + (i * 4)), (dwAddress + (i * 4)));
}