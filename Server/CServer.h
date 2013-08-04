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
#include "Scripting/CSquirrelScriptingManager.h"

class CServer {

private:
	CNetworkServer				* m_pNetServer;
	CSquirrelScriptingManager	* m_pScriptingManager;

public:
	CServer();
	~CServer();

	bool	Startup(string& outStrError);
	void	Process();
	void	Shutdown();
};

#endif // CServer_h