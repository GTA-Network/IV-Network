//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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

#include <Game/IVManagement.h>

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

class CGame {
private:
	static CLocalPlayer					*m_pLocalPlayer;
	static CIVPad						*m_pPad;
	static CTaskManager					*m_pTaskManager;
	static CPools						*m_pPool;
	static CCamera						*m_pCamera;
	static CIVModelInfo					m_modelInfos[NUM_ModelInfos];
	static CIVWeaponInfo				m_weaponInfos[NUM_WeaponInfos];
	static bool							m_LocalPlayerInitialised;

	static CPlayerManager				*m_pPlayerManager;
	static CVehicleManager				*m_pVehicleManager;
	static CActorManager				*m_pActorManager;
	static CObjectManager				*m_pObjectManager;
	static CFireManager					*m_pFireManager;
	static CPickupManager				*m_pPickupManager;
	static C3DLabelManager				*m_p3DLabelManager;
	static CBlipManager					*m_pBlipManager;
	static CCheckpointManager			*m_pCheckpointManager;
	static CCharacterManager			*m_pCharacterManager;
	static CTrafficLights				*m_pTrafficLights;

	static CString						m_strEFLCDirectory;
	bool								m_bUsingEFLCContent;
	static HWND							m_hwndGameWindow;
	static IVManagement					*m_pManagement;

	static InternalThread				m_Threads[254];
	static bool							m_bRadarVisibility;

public:
										CGame() { };
										~CGame() { };

	void								Initialise();
	void								PrepareWorld();
	static void							OnEnvironmentStartUp(bool bForce = false);
	static void							OnClientReadyToGamePlay();
	static void							OnClientPastGameJoin();
	static void							Setup();
	static void							RenderRAGEScripts();
	static void							ProcessEnvironment();
	static void							UnprotectMemory();
	static bool							CheckInstances(bool bInitialised = false);
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
	CCharacterManager					*GetCharacterManager() { return m_pCharacterManager; }
	CTrafficLights						*GetTrafficLights() { return m_pTrafficLights; }
	IVManagement						*GetIVManagement() { return m_pManagement; }

	CString								GetEFLCDirectory() { return m_strEFLCDirectory; }
	inline bool							IsUsingEFLCContent()
	{
		return m_bUsingEFLCContent;
	}

	HWND								GetGameWindow();
	void								ThrowInternalException(DWORD dwAddress, DWORD dwExcetionType);
	static void							SetupGame();

	static BYTE							CreateInternalThread(DWORD dwStartAddress, LPVOID lpvoidParameters, signed int ThreadId, int iPriority, const char * ThreadName, const char * szComment);
	static void							DestroyInternalThread(BYTE byteThreadId);

	static void							SetRadarVisible(bool bVisible) { m_bRadarVisibility = bVisible; }
	static bool							GetRadarVisibility() { return m_bRadarVisibility; }
};

#endif // CGame_h