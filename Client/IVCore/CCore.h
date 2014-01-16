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

#ifndef CCore_h
#define CCore_h

#include <Common.h>
#include <d3d9.h>

#ifdef DrawText
#undef DrawText
#endif

#include <CLogFile.h>
#include <CSettings.h>
#include <SharedUtility.h>
#include <Patcher/CPatcher.h>

#include "Graphics/CChatBox.h"

#include <Game/eGame.h>

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
#include <Graphics/CSnapShot.h>

#include <General/CModuleManager.h>
#include <Game/CTime.h>

#ifdef _DEV
#include <CDEV.h>
#endif

#include <Graphics/CGUI.h>
#include <Graphics/CMainMenu.h>
#include <Graphics/CLoadingScreen.h>
#include <Graphics/CTags.h>

#include <audio/CAudioManager.h>

#include <IV/CIVStartupScript.h>

#include "Game/EpisodeManager.h"

#include <Network/CHttpClient.h>

#include <Scripting/ResourceSystem/CResourceManager.h>

#include <RakNet/RakNetStatistics.h>

class CCore 
{
private:

	bool							m_bInitialized;
	bool							m_bGameLoaded;
	unsigned						m_uiBaseAddress;
	unsigned						m_uiGameInitializeTime;

	CGame							* m_pGame;
	CGraphics						* m_pGraphics;
	CChat							* m_pChat;
	CFPSCounter						* m_pFPSCounter;
	CNetworkManager					* m_pNetworkManager;
	CGUI                  			* m_pGUI;			
	CTags							* m_pTags;


	CChatBox						* m_pChatBox;


	CResourceManager				* m_pResourceManager;

	eGAMEStates						m_eGameState;

	CString							m_strNick;
	CString							m_strHost;
	unsigned short					m_usPort;
	CString							m_strPass;
	CString							m_strServerName;

	CTime							*m_pTimeManagement;

	bool							m_hwndFocused;
	BYTE							m_byteLoadingStyle;

	CMainMenu						*m_pMainMenu;
	CCamera							*m_pCamera;

	CHttpClient						* m_pHttpClient;

	CAudioManager					*m_pAudioManager;

	CLoadingScreen					*m_pLoadingScreen;

	CIVStartupScript				*m_pIVStartupScript;

public:
									CCore();
									~CCore() { };							

	bool							Initialize();

	void							OnGameLoad();
	void							OnGameUpdate();

	void							SetGameLoaded(bool bLoaded) { m_bGameLoaded = bLoaded; }
	bool							IsGameLoaded() { return m_bGameLoaded; }

	void							OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters);
	void							OnDeviceLost(IDirect3DDevice9 * pDevice);
	void							OnDeviceReset(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters);
	void							OnDeviceRender(IDirect3DDevice9 * pDevice);
	
	void							OnNetworkShutDown();
	void							OnNetworkTimeout();

	unsigned						GetBase() { return m_uiBaseAddress; }
	unsigned						GetBaseAddress() { return m_uiBaseAddress; }

	CGame							* GetGame() { return m_pGame; }
	CGraphics						* GetGraphics() { return m_pGraphics; }
	CAudioManager					* GetAudioManager() { return m_pAudioManager; }
	CChat							* GetChat() { return m_pChat; }
	CFPSCounter						* GetFPSCounter() { return m_pFPSCounter; }
	CNetworkManager					* GetNetworkManager() { return m_pNetworkManager; }
	CTime							* GetTimeManagementInstance() { return m_pTimeManagement; }
	CGUI                 		 	* GetGUI() { return m_pGUI; }
	CMainMenu						* GetMainMenu() { return m_pMainMenu;  }
	CTags							* GetTags() { return m_pTags; }
	
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

	inline void						SetHWNDFocused(bool bFocus)
	{
		m_hwndFocused = bFocus;
	}
	bool							GetHWNDFocused() { return m_hwndFocused; }
	void							DumpVFTable(DWORD dwAddress, int iFunctionCount);
	
	bool              				m_bLoadingVisibility;
	void              				SetLoadingVisible(bool bVisible) { m_bLoadingVisibility = bVisible; }
	bool              				GetLoadingVisibility() { return m_bLoadingVisibility; }

	void							ConnectToServer(CString strHost, unsigned short usPort, CString strPass = "");

	CIVStartupScript				*GetIVStartupScript() { return m_pIVStartupScript; };

	CResourceManager*				GetResourceManager() { return m_pResourceManager; }

	CChatBox*						GetChatBox() { return m_pChatBox; }
};

#endif // CCore_h