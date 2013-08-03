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
#include "Game/CGame.h"

#include "Game/COffsets.h"
#include "Game/CPatches.h"
#include "Game/CHooks.h"
#include  <Patcher\CPatcher.h>

#include <d3d9.h>

#include "CLogFile.h"
#include "CSettings.h"
#include "SharedUtility.h"
#include <Game\eGame.h>
#include <Hooks\CDirect3D.h>
#include <Hooks\CDirectInputProxy.h>
#include <Hooks\CXLive.h>

class CCore {

private:

	bool							m_bInitialised;
	bool							m_bGameLoaded;
	unsigned int					m_uiBaseAddress;

	CGame							* m_pGame;

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
	void							OnDeviceRender();

	unsigned int					GetBase() { return m_uiBaseAddress; }
	unsigned int					GetBaseAddress() { return m_uiBaseAddress; }

	CGame							* GetGame() { return m_pGame; }

	void							SetClientState(eGAMEStates pState) { m_eGameState = pState; }
	eGAMEStates						GetClientState() { return m_eGameState; }
};

#endif // CCore_h