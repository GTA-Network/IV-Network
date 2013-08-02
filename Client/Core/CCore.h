//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CCore.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CCore_h
#define CCore_h
#include "CGame.h"

typedef int IDirect3DDevice9;
typedef int D3DPRESENT_PARAMETERS;

class CCore {

private:

	bool							m_bInitialised;
	bool							m_bGameLoaded;
	unsigned int					m_uiBaseAddress;

	CGame							* m_pGame;
public:

									CCore( void );
									~CCore( void );

	bool							Initialise( void );

	void							OnGameLoad( void );
	void							OnGamePreLoad( void );

	void							OnGameProcess( void );

	void							SetGameLoaded( bool bLoaded ) { m_bGameLoaded = bLoaded; }
	bool							IsGameLoaded( void ) { return m_bGameLoaded; }

	void							OnDeviceCreate( IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters );
	void							OnDeviceLost( IDirect3DDevice9 * pDevice );
	void							OnDeviceReset( IDirect3DDevice9 * pDevice );
	void							OnDevicePreRender( void );
	void							OnDeviceRender( void );

	unsigned int					GetBaseAddress( void ) { return m_uiBaseAddress; }

	CGame							* GetGame( void ) { return m_pGame; }
};

#endif // CCore_h