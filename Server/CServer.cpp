//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CServer.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CServer.h"
#include <Common.h>
#include <CSettings.h>
#include <SharedUtility.h>
#include <CLogFile.h>

CServer::CServer()
{
	m_pNetServer = new CNetworkServer();
}

CServer::~CServer()
{
	SAFE_DELETE(m_pNetServer);
}

bool CServer::Startup()
{
	m_pEvents = new CEvents();

	// Open the settings file
	if(!CSettings::Open(SharedUtility::GetAbsolutePath("settings.xml"), true, false))
	{
		CLogFile::Print("Failed to open settings.xml..");
#ifdef _WIN32
		Sleep(3000);
#else
		sleep(3);
#endif
		return false;
	}

#ifdef _WIN32
		 // Color stuff
        CONSOLE_SCREEN_BUFFER_INFO csbiScreen;
        WORD wOldColAttr;       // For input process.

        GetConsoleScreenBufferInfo((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), &csbiScreen);
        wOldColAttr = csbiScreen.wAttributes;

        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), wOldColAttr | FOREGROUND_INTENSITY);

        // Print message to console.
        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);

#endif
	CLogFile::Print("");
	CLogFile::Print("====================================================================");

#ifdef _WIN32
	SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), wOldColAttr | FOREGROUND_INTENSITY);
#endif


	CLogFile::Print(" " VERSION_IDENTIFIER " " OS_STRING " Server");
	CLogFile::Print(" Copyright (C) 2009-2013 IV:MP Team");
	CLogFile::Printf(" Port: %d", CVAR_GET_INTEGER("port"));
	CLogFile::Printf(" HTTP Port: %d", CVAR_GET_INTEGER("httpport"));
	CLogFile::Printf(" Query Port: %d", (CVAR_GET_INTEGER("queryport")));

	if(CVAR_GET_STRING("hostaddress").IsNotEmpty())
		CLogFile::Printf(" Host Address: %s", CVAR_GET_STRING("hostaddress").Get());

	if(CVAR_GET_STRING("httpserver").IsNotEmpty())
		CLogFile::Printf(" HTTP Server: %s", CVAR_GET_STRING("httpserver").Get());

	CLogFile::Printf(" Max Players: %d", CVAR_GET_INTEGER("maxplayers"));

#ifdef _WIN32
        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        CLogFile::Print("====================================================================");
        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), wOldColAttr | FOREGROUND_INTENSITY);
#else
        CLogFile::Print("====================================================================");
#endif


	RakNet::StartupResult startResult;
	startResult = m_pNetServer->Start(CVAR_GET_INTEGER("port"), CVAR_GET_INTEGER("maxplayers"), CVAR_GET_STRING("hostaddress"));
	if(PEER_IS_STARTED(startResult) == false)
	{
		CLogFile::Print("Failed to initialize network component.");
		CLogFile::Print(Network::GetErrorMessage(startResult));
		return false;
	}
	
	// Load modules
	auto modules = CVAR_GET_LIST("module");
	if(modules.size() > 0)
	{
		CLogFile::Print("");
		CLogFile::Print("========================== Loading Modules =========================");

		for(auto strModule : modules)
		{
			CLogFile::Printf("Loading module %s.", strModule.Get());
			if(!strModule.ToLower().EndsWith(".so") && !strModule.ToLower().EndsWith(".dll"))
			{
				// If no extension specified in module name string, load SO for linux and DLL for Win
#ifdef _WIN32
				strModule.Append(".dll");
#else
				strModule.Append(".so");
#endif		
			}
			//CModule * pModule = g_pModuleManager->LoadModule(strModule);

			//if(!pModule)
				CLogFile::Printf("Warning: Failed to load module %s.", strModule.Get());
		}

		CLogFile::Print("");
	}

	m_pResourceManager = new CResourceManager("resources/");

	// Loading resources
#ifdef _WIN32
        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        CLogFile::Print("");
        CLogFile::Print("============ Loading Resources ===========");
		CLogFile::Print("");
        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), wOldColAttr | FOREGROUND_INTENSITY);
#else
        CLogFile::Print("");
        CLogFile::Print("============ Loading Resources ===========");
		CLogFile::Print("");
#endif


	auto resources = CVAR_GET_LIST("resource");

	int iResourcesLoaded = 0;
	int iFailedResources = 0;

	for(auto strResource : resources)
	{
		if(!strResource.IsEmpty())
		{
			CLogFile::Printf("Loading resource (%s)", strResource.C_String());
			if(!m_pResourceManager->Load(strResource))
			{
				CLogFile::Printf("Warning: Failed to load resource %s.", strResource.Get());
				iFailedResources++;
			}
			else
				iResourcesLoaded++;
		}
	}

	auto clientresources = CVAR_GET_LIST("clientresource");
	for(auto strClientResource : clientresources)
	{	
		//if(!g_pClientResourceFileManager->Start(strClientResource))
		{
			CLogFile::Printf("Warning: Failed to load client resource %s.", strClientResource.Get());
			iFailedResources++;
		}
		/*else
			iResourcesLoaded++;*/
	}

	CLogFile::Printf("Successfully loaded %d resources (%d failed).", iResourcesLoaded, iFailedResources);

#ifdef _WIN32
        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        CLogFile::Print("");
        CLogFile::Print("====================================================================");
        CLogFile::Print("");
        SetConsoleTextAttribute((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE), wOldColAttr | FOREGROUND_INTENSITY);
#else
        CLogFile::Print("");
        CLogFile::Print("====================================================================");
        CLogFile::Print("");
#endif

	return true;
}

void CServer::Process()
{
	m_pNetServer->Process();
}

void CServer::Shutdown()
{
	m_pNetServer->EnsureStopped();
}