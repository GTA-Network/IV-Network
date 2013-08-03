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

#include "Game/CGame.h"
#include "Game/COffsets.h"

typedef int IDirect3DDevice9;
typedef int D3DPRESENT_PARAMETERS;

class CCore {

private:

	bool							m_bInitialised;
	bool							m_bGameLoaded;
	unsigned int					m_uiBaseAddress;

	CGame							* m_pGame;
	COffsets						* m_pOffsets;
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

	unsigned int					GetBaseAddress() { return m_uiBaseAddress; }

	CGame							* GetGame() { return m_pGame; }
	COffsets						* GetOffsets() { return m_pOffsets; }
};

#endif // CCore_h