//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CGame.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CGame_h
#define CGame_h

#include "CGameFuncs.h"
#include <Network\CLocalPlayer.h>

class CGame {
private:
	CLocalPlayer			*m_pLocalPlayer;

public:
							CGame() { };
							~CGame() { };

	void					Initialise();
	static void				Setup();
	static void				RenderRAGEScripts();
	static void				UnprotectMemory();
	CLocalPlayer			*GetLocalPlayer() { return m_pLocalPlayer; }
};

#endif // CGame_h