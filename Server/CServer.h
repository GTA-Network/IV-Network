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

#include "Common.h"
#include "CNetworkServer.h"
#include <Scripting/CResourceManager.h>
#include <Scripting/CEvents.h>

class CServer {

private:
	CNetworkServer				* m_pNetServer;
	CResourceManager			* m_pResourceManager;
	CEvents						* m_pEvents;

public:
	CServer();
	~CServer();

	bool	Startup();
	void	Process();
	void	Shutdown();

	CNetworkServer		*GetNetServer() { return m_pNetServer; }
	CResourceManager	*GetResourceManager() { return m_pResourceManager; }
};

#endif // CServer_h