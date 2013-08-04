//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CGame.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CGame_h
#define CGame_h

#include <Common.h>
#include "CGameFuncs.h"

#include "Network/CLocalPlayer.h"
#include "Game/Entity/CPlayerEntity.h"
#include "Game/Entity/CNetworkEntity.h"
class CLocalPlayer;

class CGame {
private:
	static CLocalPlayer			*m_pLocalPlayer;

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