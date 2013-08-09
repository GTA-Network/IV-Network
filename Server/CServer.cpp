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

CServer* CServer::s_pInstance = 0;

CServer::CServer()
{
	m_pNetServer = new CNetworkServer();

	m_pRPCHandler = new CServerRPCHandler();
}

CServer::~CServer()
{
	SAFE_DELETE(m_pNetServer);

	SAFE_DELETE(m_pPlayerManager);

	SAFE_DELETE(m_pVehicleManager);

	SAFE_DELETE(m_pActorManager);

	SAFE_DELETE(m_pObjectManager);

	SAFE_DELETE(m_pFireManager);

	SAFE_DELETE(m_pPickupManager);

	SAFE_DELETE(m_p3DLabelManager);

	SAFE_DELETE(m_pBlipManager);

	SAFE_DELETE(m_pCheckpointManager);
}

bool CServer::Startup()
{
	// Register our RPCs before set the NetServer´s rpc handler
	m_pRPCHandler->RegisterRPCs();

	// Set our rpc handler
	m_pNetServer->SetRpcHandler(m_pRPCHandler);

	// Create all the managers
	m_pPlayerManager = new CPlayerManager();
	m_pVehicleManager = new CVehicleManager();
	m_pActorManager = new CActorManager();
	m_pObjectManager = new CObjectManager();
	m_pFireManager = new CFireManager();
	m_pPickupManager = new CPickupManager();
	m_p3DLabelManager = new C3DLabelManager();
	m_pBlipManager = new CBlipManager();
	m_pCheckpointManager = new CCheckpointManager();

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
	// Note: modules not implemented yet coming soon
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
#if 1
	m_pResourceManager = new CResourceManager("resources");

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
			if(CResource* pResource = m_pResourceManager->Load(SharedUtility::GetAbsolutePath(m_pResourceManager->GetResourceDirectory()),strResource))
			{
				m_pResourceManager->StartResource(pResource);
				iResourcesLoaded++;
			} else {
				CLogFile::Printf("Warning: Failed to load resource %s.", strResource.Get());
				iFailedResources++;
			}
		}
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
#endif
	return true;
}

void CServer::Process()
{
	m_pNetServer->Process();

	// Pulse all managers
	// Do not worry about that some managers dont need to be pulsed its just that its complete and all the same structure
	m_pPlayerManager->Pulse();

	m_pVehicleManager->Pulse();

	m_pActorManager->Pulse();

	m_pObjectManager->Pulse();

	m_pFireManager->Pulse();

	m_pPickupManager->Pulse();

	m_p3DLabelManager->Pulse();

	m_pBlipManager->Pulse();

	m_pCheckpointManager->Pulse();
}

void CServer::Shutdown()
{
	m_pNetServer->EnsureStopped();

	// TODO: clear events

	m_pPlayerManager->Reset();

	m_pVehicleManager->Reset();

	m_pActorManager->Reset();

	m_pObjectManager->Reset();

	m_pFireManager->Reset();

	m_pPickupManager->Reset();

	m_p3DLabelManager->Reset();

	m_pBlipManager->Reset();

	m_pCheckpointManager->Reset();
}