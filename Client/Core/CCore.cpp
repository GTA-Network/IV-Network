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
}

bool CCore::Initialise()
{
	// Are we already initialsed?
	if(m_bInitialised)
		return false;

	CLogFile::Printf("CCore::Initialize");

	// Get the application base address
	m_uiBaseAddress = (unsigned int)GetModuleHandle(NULL);

	CLogFile::Printf("Game Base: 0x%p (0x%p)", m_uiBaseAddress, (m_uiBaseAddress - 0x400000));

	// Subtract the image size from the base address
	m_uiBaseAddress -= 0x400000;

	// Open the settings file
	CSettings::Open( SharedUtility::GetAbsolutePath("IVMP-Client.xml"), true, false );

	// Parse the command line
	CSettings::ParseCommandLine(GetCommandLine());

	// Create the game instance
	m_pGame = new CGame;

	// Create the graphics instance
	m_pGraphics = new CGraphics;

	// Create the fps counter instance
	m_pFPSCounter = new CFPSCounter;

	// Create the network manager instance
	m_pNetworkManager = new CNetworkManager;

	// Create the chat instance
	m_pChat = new CChat(30, 30);

	// Unprotect memory before starting addressing
	m_pGame->UnprotectMemory();

	// Intialize the offsets instance
	COffsets::Initialize(m_uiBaseAddress);

	// Apply hook's to game
	CHooks::Intialize();

	// Patch game addresses
	CPatches::Initialize();

	// Install the XLive hook
	CXLiveHook::Install();

	// Install the RAGEScriptThread hook..
	CIVScriptingHook::InstallScriptHooks();

	// Setup the game instance
	m_pGame->Setup();

	CLogFile::Printf("Done!");
	return true;
}

void CCore::OnGameLoad()
{
	// Is the game already loaded?
	if(IsGameLoaded())
		return;

	CLogFile::Print("CCore::OnGameLoad");

	// Initialize game instance & respawn local player
	GetGame()->Initialise();

	// Remove all stuff from directx device(which is drawn)
	m_pGraphics->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0),1.0f,0);

	// Mark the game as loaded
	SetGameLoaded(true);

	// Mark chat as visible & print welcome message
	m_pChat->SetVisible(true);
	m_pChat->Outputf(false, "%s %s started!", MOD_NAME, MOD_VERSION_STRING );

	m_strHost = "127.0.0.1";
	m_usPort = 9999;
	m_strNick = "IVPlayer";

	// Startup the network module
	m_pNetworkManager->Startup();

	// Connect to the network
	m_pNetworkManager->Connect();
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
	CLogFile::Print("CCore::OnDeviceCreate");

	// Setup the chat
	if(m_pChat)
		m_pChat->Setup(pPresentationParameters);
}

void CCore::OnDeviceLost(IDirect3DDevice9 * pDevice)
{
	CLogFile::Print("CCore::OnDeviceReset");

	// Mark as lost device
	g_bDeviceLost = true;
}

void CCore::OnDeviceReset(IDirect3DDevice9 * pDevice)
{
	CLogFile::Print("CCore::OnDeviceReset");

	// Mark as not lost device
	g_bDeviceLost = false;
}

void CCore::OnDevicePreRender()
{
	// Is the scripting manager active?
	if(true)
	{
		// Call the script event
	}
}

void CCore::OnDeviceRender(IDirect3DDevice9 * pDevice)
{
	// Has the device been lost?
	if(g_bDeviceLost || !m_pGraphics)
		return;

#if 0
	if(!g_pCore->GetGame()->GetLocalPlayer())
	{
		m_pGraphics->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0),1.0f,0);

		m_pGraphics->GetSprite()->Begin(0);

		D3DXVECTOR2 spriteCentre = D3DXVECTOR2(960.0f, 540.0f);
	    D3DXVECTOR2 trans=D3DXVECTOR2(0.0f,0.0f);
		
		D3DXMATRIX mat;
		D3DXVECTOR2 scaling2((1920.0f/1440.0f)/2,(1080.0f/900.0f)/3);
		float rotation=0.0f;
		D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling2,&spriteCentre,rotation,&trans);

		m_pGraphics->GetSprite()->SetTransform(&mat);
		m_pGraphics->GetSprite()->Draw(m_pGraphics->pLoadingScreenTexture,NULL, NULL,&D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DCOLOR_ARGB(255,255,255,255));

		m_pGraphics->GetSprite()->Flush();
		m_pGraphics->GetSprite()->End();
	}
	else
	{
#endif
		// Print our IVMultiplayer "Identifier" in the left upper corner
		if(!g_pCore->GetGame()->GetLocalPlayer())
			m_pGraphics->DrawText(5.0f, 5.0f, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("IV:Multiplayer " MOD_VERSION_STRING " - Loading.. Hold on...").Get());
		else
			m_pGraphics->DrawText(5.0f, 5.0f, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("IV:Multiplayer" MOD_VERSION_STRING).Get());

		// Render our chat instance
		if(m_pChat && m_pChat->IsVisible())
			m_pChat->Render();

		// Before rendering FPS-Counter instance, update FPS display
		m_pGraphics->DrawText(5.0f, 25.0f, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("FPS: %d", m_pFPSCounter->GetFPS()).Get());

		// Render our FPS-Counter instance
		if(m_pFPSCounter)
			m_pFPSCounter->Pulse();
	//}
	
	pDevice->Present(NULL,NULL,NULL,NULL);
}