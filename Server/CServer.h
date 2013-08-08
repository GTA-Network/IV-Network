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
#define UINT_MAX 4294967295
#include "Common.h"

#include <CNetworkServer.h>

#include <Network/CServerRPCHandler.h>

#include <Scripting/ResourceSystem/CResourceManager.h>

#include <Entity/CEntityManager.h>
#include <Entity/Entities.h>

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
	CNetworkServer				* m_pNetServer;
	CServerRPCHandler			* m_pRPCHandler;

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

public:
	CServer();
	~CServer();

	bool	Startup();
	void	Process();
	void	Shutdown();

	CNetworkServer		*GetNetServer() { return m_pNetServer; }
	CServerRPCHandler	*GetRPCHandler() { return m_pRPCHandler; }

	CResourceManager	*GetResourceManager() { return m_pResourceManager; }

	CPlayerManager		*GetPlayerManager() { return m_pPlayerManager; }
	CVehicleManager		*GetVehicleManager() { return m_pVehicleManager; }
	CActorManager		*GetActorManager() { return m_pActorManager; }
	CObjectManager		*GetObjectManager() { return m_pObjectManager; }
	CFireManager		*GetFireManager() { return m_pFireManager; }
	CPickupManager		*GetPickupManager() { return m_pPickupManager; }
	C3DLabelManager		*Get3DLabelManager() { return m_p3DLabelManager; }
	CBlipManager		*GetBlipManager() { return m_pBlipManager; }
	CCheckpointManager	*GetCheckpointManager() { return m_pCheckpointManager; }
};

#endif // CServer_h