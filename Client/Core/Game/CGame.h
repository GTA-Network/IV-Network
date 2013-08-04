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

#include <Game/IVEngine/CIVPad.h>
#include <Game/IVEngine/CIVPool.h>
#include "CTaskManager.h"
#include "CPools.h"
#include "IVEngine/CIVCam.h"
#include "CCamera.h"

class CLocalPlayer;

class CGame {
private:
	static CLocalPlayer			*m_pLocalPlayer;
	static CIVPad				*m_pPad;
	static CTaskManager			*m_pTaskManager;
	static CPools				*m_pPool;
	static CCamera				*m_pCamera;

public:
							CGame() { };
							~CGame() { };

	void					Initialise();
	static void				Setup();
	static void				RenderRAGEScripts();
	static void				UnprotectMemory();
	CLocalPlayer			*GetLocalPlayer() { return m_pLocalPlayer; }
	CIVPad					*GetPad() { return m_pPad; }
	CTaskManager			*GetTaskManager() { return m_pTaskManager; }
	CPools					*GetPools() { return m_pPool; }
	CCamera					*GetCamera() { return m_pCamera; }
};

#endif // CGame_h