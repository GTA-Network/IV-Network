//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CServer.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CServer_h
#define CServer_h

#include <limits.h>
#ifndef UINT_MAX
#define UINT_MAX 4294967295
#endif
#include "Common.h"

#include <Scripting/ResourceSystem/CResourceManager.h>

#include <Entity/CEntityManager.h>
#include <Entity/Entities.h>
#include "Network/CNetworkModule.h"

typedef CEntityManager<CPlayerEntity, MAX_PLAYERS> CPlayerManager;
typedef CEntityManager<CVehicleEntity, MAX_VEHICLES> CVehicleManager;
typedef CEntityManager<CActorEntity, MAX_ACTORS> CActorManager;
typedef CEntityManager<CObjectEntity, MAX_OBJECTS> CObjectManager;
typedef CEntityManager<CFireEntity, MAX_FIRE> CFireManager;
typedef CEntityManager<CPickupEntity, MAX_PICKUPS> CPickupManager;
typedef CEntityManager<C3DLabelEntity, MAX_3D_LABELS> C3DLabelManager;
typedef CEntityManager<CBlipEntity, MAX_BLIPS> CBlipManager;
typedef CEntityManager<CCheckpointEntity, MAX_CHECKPOINTS> CCheckpointManager;

class CServer {

private:
	static CServer				* s_pInstance;

	CResourceManager			* m_pResourceManager;

	CPlayerManager				* m_pPlayerManager;
	CVehicleManager				* m_pVehicleManager;
	CActorManager				* m_pActorManager;
	CObjectManager				* m_pObjectManager;
	CFireManager				* m_pFireManager;
	CPickupManager				* m_pPickupManager;
	C3DLabelManager				* m_p3DLabelManager;
	CBlipManager				* m_pBlipManager;
	CCheckpointManager			* m_pCheckpointManager;

	CNetworkModule				* m_pNetworkModule;


	unsigned int                m_uiSyncRate;// Seems VS2013 sometimes does not allow C++11 = 20; /** Describes the maximum number of sync packages sent per second per entity */
    unsigned int                m_uiMaximumFPS;// Seems VS2013 sometimes does not allow C++11 = 100;

    bool                        m_bShowFPS = true;
	unsigned long				m_ulLastFPSUpdateTime;
	unsigned long				m_ulFrameCount;
	unsigned long				m_ulFramesPerSecond;
public:
	CServer();
	~CServer();

	static CServer* GetInstance() { return s_pInstance; }

	bool	Startup();
	void	Process();
	void	Shutdown();

	CResourceManager	*GetResourceManager() { return CResourceManager::GetInstance(); }

	CPlayerManager		*GetPlayerManager() { return m_pPlayerManager; }
	CVehicleManager		*GetVehicleManager() { return m_pVehicleManager; }
	CActorManager		*GetActorManager() { return m_pActorManager; }
	CObjectManager		*GetObjectManager() { return m_pObjectManager; }
	CFireManager		*GetFireManager() { return m_pFireManager; }
	CPickupManager		*GetPickupManager() { return m_pPickupManager; }
	C3DLabelManager		*Get3DLabelManager() { return m_p3DLabelManager; }
	CBlipManager		*GetBlipManager() { return m_pBlipManager; }
	CCheckpointManager	*GetCheckpointManager() { return m_pCheckpointManager; }

	CNetworkModule		*GetNetworkModule() { return m_pNetworkModule; }

	unsigned GetSyncRate() { return m_uiSyncRate; }
	void	 SetSyncRate(unsigned int uiSyncRate = 20) { m_uiSyncRate = uiSyncRate; }

	unsigned int GetMaximumFPS() { return m_uiMaximumFPS; }
	void		 SetMaximumFPS(unsigned int uiMaximumFPS = 100) { m_uiMaximumFPS = uiMaximumFPS; }
};

#endif // CServer_h