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
	s_pInstance = this;

	m_pNetworkModule = new CNetworkModule();
}

CServer::~CServer()
{
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

#include <Scripting/CEvents.h>

bool CServer::Startup()
{
	// Register our RPCs before set the NetServer´s rpc handler
	CEvents* pEvents = new CEvents();

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
	CLogFile::Print(" Copyright (C) 2013 GTA-Network Team");
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

	m_pNetworkModule->Startup();

	return true;
}


unsigned long m_ulLastProcess = 0;
void CServer::Process()
{
	m_pNetworkModule->Pulse();


	// Pulse all managers
	// Seems like this slows the server extremely down (we process over 264000 entities) optimize compile?!
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

	// Get the current time
	unsigned long ulTime = SharedUtility::GetTime();

	// Is show fps enabled?
	if (m_bShowFPS)
	{
		// Get the amount of time elapsed since the last fps update
		unsigned long ulTimeElapsed = (ulTime - m_ulLastFPSUpdateTime);

		// Update the fps if a second or more has passed
		if (ulTimeElapsed >= 1000)
		{
			// Set the fps
			m_ulFramesPerSecond = m_ulFrameCount;

			// Set the server title
#ifdef _WIN32
			CString strTitle(" " VERSION_IDENTIFIER " Server"" - FPS: %d", m_ulFramesPerSecond);
			SetConsoleTitle(strTitle.Get());

#endif

			/// Calculate the delay to receive the maximum FPS set in server

			// Reset the frame count
			m_ulFrameCount = 0;

			// Set the last fps update tick count
			m_ulLastFPSUpdateTime = ulTime;
		}

		// Increment the frame count
		m_ulFrameCount++;
	}

	int delay = 1000.0f / m_uiMaximumFPS - (float) (ulTime - m_ulLastProcess);
	if (delay > 0)
		Sleep(delay);

	

	m_ulLastProcess = SharedUtility::GetTime();
}

void CServer::Shutdown()
{
	// TODO: clear events
	CEvents::GetInstance()->Clear();

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