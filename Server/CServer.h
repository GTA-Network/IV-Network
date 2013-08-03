//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CServer.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CServer_h
#define CServer_h

#include "Common.h"
#include "CNetworkServer.h"

class CServer {

private:
	CNetworkServer * m_pNetServer;

public:
	CServer();
	~CServer();

	bool	Startup(string& outStrError);
	void	Process();
	void	Shutdown();
};

#endif // CServer_h