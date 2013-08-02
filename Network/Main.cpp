//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: Main.cpp
// Project: Network.Core
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#include <StdInc.h>

EXPORT bool VerifyVersion(unsigned char ucVersion)
{
	if(ucVersion == NETWORK_MODULE_VERSION)
		return true;

	return false;
}

EXPORT CNetServerInterface * GetNetServerInterface()
{
	CNetServerInterface * pNetServer = new CNetServer();
	return pNetServer;
}

EXPORT void DestroyNetServerInterface(CNetServerInterface * pNetServer)
{
	delete pNetServer;
}

EXPORT CNetClientInterface * GetNetClientInterface()
{
	CNetClientInterface * pNetClient = new CNetClient();
	return pNetClient;
}

EXPORT void DestroyNetClientInterface(CNetClientInterface * pNetClient)
{
	delete pNetClient;
}

#ifndef _LINUX
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, void *)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		// Disable thread calls
		DisableThreadLibraryCalls(hModule);
	}

	return TRUE;
}
#endif
