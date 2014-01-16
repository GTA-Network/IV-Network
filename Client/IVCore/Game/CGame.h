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

#ifndef CGame_h
#define CGame_h

#include <Common.h>

#include <Network/CLocalPlayer.h>

#include <Game/Entity/CEntityManager.h>
#include <Game/Entity/CNetworkEntity.h>

#include <Game/Entity/CPlayerEntity.h>
#include <Game/Entity/CVehicleEntity.h>
#include <Game/Entity/CActorEntity.h>
#include <Game/Entity/CObjectEntity.h>
#include <Game/Entity/CFireEntity.h>
#include <Game/Entity/CPickupEntity.h>
#include <Game/Entity/C3DLabelEntity.h>
#include <Game/Entity/CBlipEntity.h>
#include <Game/Entity/CCheckpointEntity.h>

#include <Game/IVEngine/CIVModelInfo.h>
#include <Game/IVEngine/CIVPad.h>
#include <Game/IVEngine/CIVPool.h>
#include <Game/IVEngine/CIVCam.h>
#include <Game/IVEngine/CIVWeaponInfo.h>

#include "CTaskManager.h"
#include "CPools.h"
#include "CCamera.h"
#include "CGameFuncs.h"
#include "CCharacterManager.h"
#include "CContextSwitch.h"
#include <Game/CTrafficLights.h>
#include <Game/CTrafficHandler.h>

typedef CEntityManager<CPlayerEntity, MAX_PLAYERS> CPlayerManager;
typedef CEntityManager<CVehicleEntity, MAX_VEHICLES> CVehicleManager;
typedef CEntityManager<CActorEntity, MAX_ACTORS> CActorManager;
typedef CEntityManager<CObjectEntity, MAX_OBJECTS> CObjectManager;
typedef CEntityManager<CFireEntity, MAX_FIRE> CFireManager;
typedef CEntityManager<CPickupEntity, MAX_PICKUPS> CPickupManager;
typedef CEntityManager<C3DLabelEntity, 0xFFFE> C3DLabelManager;
typedef CEntityManager<CBlipEntity, MAX_BLIPS> CBlipManager;
typedef CEntityManager<CCheckpointEntity, MAX_CHECKPOINTS> CCheckpointManager;

class CLocalPlayer;

class CGame
{
private:
	CLocalPlayer					*m_pLocalPlayer;
	CIVPad							*m_pPad;
	CTaskManager					*m_pTaskManager;
	CPools							*m_pPool;
	CCamera							*m_pCamera;
	CIVModelInfo					m_modelInfos[NUM_ModelInfos];
	CIVWeaponInfo					m_weaponInfos[NUM_WeaponInfos];
	bool							m_LocalPlayerInitialized;

	CPlayerManager					*m_pPlayerManager;
	CVehicleManager					*m_pVehicleManager;
	CActorManager					*m_pActorManager;
	CObjectManager					*m_pObjectManager;
	CFireManager					*m_pFireManager;
	CPickupManager					*m_pPickupManager;
	C3DLabelManager					*m_p3DLabelManager;
	CBlipManager					*m_pBlipManager;
	CCheckpointManager				*m_pCheckpointManager;
	CTrafficLights					*m_pTrafficLights;

	HWND							m_hwndGameWindow;

public:
										CGame();
										~CGame();

	void								Initialize();
	void								PrepareWorld();
	void								OnEnvironmentStartUp(bool bForce = false);
	void								OnClientReadyToGamePlay();
	void								OnClientPastGameJoin();
	void								Setup();
	void								RenderRAGEScripts();
	void								ProcessEnvironment();
	void								UnprotectMemory();
	void								Reset();
	CLocalPlayer						*GetLocalPlayer() { return m_pLocalPlayer; }
	CIVPad								*GetPad() { return m_pPad; }
	CTaskManager						*GetTaskManager() { return m_pTaskManager; }
	CPools								*GetPools() { return m_pPool; }
	CCamera								*GetCamera() { return m_pCamera; }

	CIVModelInfo						*GetModelInfo(int iModelIndex);
	CIVWeaponInfo						*GetWeaponInfo(eWeaponType weaponType);

	CPlayerManager						*GetPlayerManager() { return m_pPlayerManager; }
	CVehicleManager						*GetVehicleManager() { return m_pVehicleManager; }
	CActorManager						*GetActorManager() { return m_pActorManager; }
	CObjectManager						*GetObjectManager() { return m_pObjectManager; }
	CFireManager						*GetFireManager() { return m_pFireManager; }
	CPickupManager						*GetPickupManager() { return m_pPickupManager; }
	C3DLabelManager						*Get3DLabelManager() { return m_p3DLabelManager; }
	CBlipManager						*GetBlipManager() { return m_pBlipManager; }
	CCheckpointManager					*GetCheckpointManager() { return m_pCheckpointManager; }
	CTrafficLights						*GetTrafficLights() { return m_pTrafficLights; }

	HWND								GetGameWindow();
	void								ThrowInternalException(DWORD dwAddress, DWORD dwExcetionType);
	void								SetupGame();
};

#endif // CGame_h