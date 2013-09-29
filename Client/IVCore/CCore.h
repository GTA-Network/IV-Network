//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CCore.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CCore_h
#define CCore_h

#include <Common.h>
#include <d3d9.h>

#include <CLogFile.h>
#include <CSettings.h>
#include <SharedUtility.h>
#include <Patcher/CPatcher.h>

#include <Game/eGame.h>
#include <IV/CIVScriptHook.h>

#include <Hooks/CXLive.h>
#include <Hooks/CWin32MouseHook.h>

#include "Game/CGame.h"
#include "Graphics/CGraphics.h"
#include "Graphics/CChat.h"
#include "Game/COffsets.h"
#include "Game/CPatches.h"
#include "Game/CHooks.h"
#include "Game/CCrashFixes.h"
#include "Graphics/CFPSCounter.h"

#include "Network/CLocalPlayer.h"
#include "Game/Entity/CPlayerEntity.h"
#include "Game/Entity/CNetworkEntity.h"

#include <Network/CNetworkManager.h>
#include <Game/CDevelopment.h>
#include <Game/CWeaponHandler.h>
#include <Graphics/CSnapShot.h>

#include <General/CModuleManager.h>
#include <Game/CTime.h>

#include <Graphics/CGUI.h>
#include <Graphics/CMainMenu.h>

#include <RAGEEngine/RAGEInterface.h>
typedef void (* GetInterface_t)(RAGEEngineInterface *);

class CCore {
private:

	bool							m_bInitialised;
	bool							m_bGameLoaded;
	unsigned						m_uiBaseAddress;
	unsigned						m_uiGameInitializeTime;

	CGame							* m_pGame;
	CGraphics						* m_pGraphics;
	CChat							* m_pChat;
	CFPSCounter						* m_pFPSCounter;
	CNetworkManager					* m_pNetworkManager;
	CDevelopment					* m_pDevelopment;
	CGUI                  			* m_pGUI;					

	eGAMEStates						m_eGameState;

	CString							m_strNick;
	CString							m_strHost;
	unsigned short					m_usPort;
	CString							m_strPass;
	CString							m_strServerName;

	CLibrary						*m_pRAGELibrary;
	GetInterface_t					m_pEngine;
	RAGEEngineInterface				*m_pInterface;
	CTime							*m_pTimeManagement;

	bool							m_hwndFocused;
	BYTE							m_byteLoadingStyle;

	CMainMenu						* m_pMainMenu;

public:
									CCore();
									~CCore() { };							

	bool							Initialise();

	void							OnGameLoad();
	void							OnGamePreLoad();

	void							SetGameLoaded(bool bLoaded) { m_bGameLoaded = bLoaded; }
	bool							IsGameLoaded() { return m_bGameLoaded; }

	void							OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters);
	void							OnDeviceLost(IDirect3DDevice9 * pDevice);
	void							OnDeviceReset(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters);
	void							OnDevicePreRender();
	void							OnDeviceRender(IDirect3DDevice9 * pDevice);
	
	void							OnNetworkShutDown();
	void							OnNetworkTimeout();

	unsigned						GetBase() { return m_uiBaseAddress; }
	unsigned						GetBaseAddress() { return m_uiBaseAddress; }

	CGame							* GetGame() { return m_pGame; }
	CGraphics						* GetGraphics() { return m_pGraphics; }
	CChat							* GetChat() { return m_pChat; }
	CFPSCounter						* GetFPSCounter() { return m_pFPSCounter; }
	CNetworkManager					* GetNetworkManager() { return m_pNetworkManager; }
	CDevelopment					* GetDevelopmentInstance() { return m_pDevelopment; }
	CTime							* GetTimeManagementInstance() { return m_pTimeManagement; }
	CGUI                 		 	* GetGUI() { return m_pGUI; }
	
	void							SetClientState(eGAMEStates pState) { m_eGameState = pState; }
	eGAMEStates						GetClientState() { return m_eGameState; }

	void							SetNick( CString strNick ) { m_strNick = strNick; }
	CString							GetNick( ) { return m_strNick; }
	void							SetHost( CString strHost ) { m_strHost = strHost; }
	CString							GetHost( ) { return m_strHost; }
	void							SetClientPort( unsigned short usPort ) { m_usPort = usPort; }
	unsigned short					GetPort( ) { return m_usPort; }
	void							SetPass( CString strPass ) { m_strPass = strPass; }
	CString							GetPass( ) { return m_strPass; }

	void							SetServerName(CString strServerName) { m_strServerName = strServerName;  }
	CString							GetServerName() { return m_strServerName; }

	unsigned						GetGameLoadInitializeTime() { return m_uiGameInitializeTime; }
	DWORD							SubStractAddressFromBase(DWORD dwAddress) { return (dwAddress-m_uiBaseAddress); }

	void							GetLoadedModulesList();
	void							GetLoadedModule(DWORD dwProcessId);

	RAGEEngineInterface				*GetRAGEInterface() { return m_pInterface; }

	inline void						SetHWNDFocused(bool bFocus)
	{
		m_hwndFocused = bFocus;
	}
	bool							GetHWNDFocused() { return m_hwndFocused; }
	void							DumpVFTable(DWORD dwAddress, int iFunctionCount);
	
	bool              				m_bLoadingVisibility;
	void              				RenderLoadingScreen();
	void              				SetLoadingVisible(bool bVisible) { m_bLoadingVisibility = bVisible; }
	bool              				GetLoadingVisibility() { return m_bLoadingVisibility; }
	void							ConnectToServer();
};

#endif // CCore_h