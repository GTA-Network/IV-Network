//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
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
#include <Patcher\CPatcher.h>

#include <Game\eGame.h>
#include <IV\CIVScriptHook.h>

#include <Hooks\CXLive.h>

#include "Game/CGame.h"
#include "Graphics/CGraphics.h"
#include "Graphics/CChat.h"
#include "Game/COffsets.h"
#include "Game/CPatches.h"
#include "Game/CHooks.h"

#include "Network/CLocalPlayer.h"


class CCore {

private:

	bool							m_bInitialised;
	bool							m_bGameLoaded;
	unsigned int					m_uiBaseAddress;

	CGame							* m_pGame;
	CGraphics						* m_pGraphics;
	CChat							* m_pChat;

	eGAMEStates						m_eGameState;
public:

									CCore();
									~CCore();

	bool							Initialise();

	void							OnGameLoad();
	void							OnGamePreLoad();

	void							OnGameProcess();

	void							SetGameLoaded(bool bLoaded) { m_bGameLoaded = bLoaded; }
	bool							IsGameLoaded() { return m_bGameLoaded; }

	void							OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters);
	void							OnDeviceLost(IDirect3DDevice9 * pDevice);
	void							OnDeviceReset(IDirect3DDevice9 * pDevice);
	void							OnDevicePreRender();
	void							OnDeviceRender(IDirect3DDevice9 * pDevice);

	unsigned int					GetBase() { return m_uiBaseAddress; }
	unsigned int					GetBaseAddress() { return m_uiBaseAddress; }

	CGame							* GetGame() { return m_pGame; }
	CGraphics						* GetGraphics() { return m_pGraphics; }
	CChat							* GetChat() { return m_pChat; }

	void							SetClientState(eGAMEStates pState) { m_eGameState = pState; }
	eGAMEStates						GetClientState() { return m_eGameState; }
};

#endif // CCore_h