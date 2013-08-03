//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CServer.cpp
// Project: Client.Core
// Author: xForce
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

}

CServer::~CServer()
{

}


bool CServer::Startup()
{
	// Open the settings file
	if(!CSettings::Open(SharedUtility::GetAbsolutePath("settings.xml"), false, false))
	{
		CLogFile::Print("Failed to open settings.xml, server will shut down in 3 seconds..");
		Sleep(3000);
		return false;
	}

	CLogFile::Print("");
	CLogFile::Print("====================================================================");


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

	CLogFile::Print("====================================================================");

	return true;
}

void CServer::Process()
{

}

void CServer::Shutdown()
{

}