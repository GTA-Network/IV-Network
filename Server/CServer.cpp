//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CServer.cpp
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CServer.h"

CServer::CServer()
{
	m_pNetServer = new CNetworkServer();
}

CServer::~CServer()
{
	SAFE_DELETE(m_pNetServer);
}


bool CServer::Startup(string& outStrError)
{
	if(!m_pNetServer->EnsureStarted(7890, 1, NULL))
	{
		outStrError = "Failed to start network port.";
		return false;
	}

	return true;
}

void CServer::Process()
{
	m_pNetServer->Process();
}

void CServer::Shutdown()
{
	m_pNetServer->EnsureStopped(10);
}