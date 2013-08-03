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

class CServer {

private:

public:
	CServer();
	~CServer();

	bool	Startup();
	void	Process();
	void	Shutdown();

};

#endif // CServer_h