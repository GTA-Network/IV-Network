//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CResourceClientScript.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CResourceClientScript.h"


CResourceClientScript::CResourceClientScript(CResource * resource, const char * szShortName, const char * szResourceFileName)
	: CResourceScriptFile(resource, szShortName, szResourceFileName)
{
	m_type = RESOURCE_FILE_TYPE_CLIENT_SCRIPT;
}

CResourceClientScript::~CResourceClientScript()
{

}


bool CResourceClientScript::Start()
{

	return true;
}

bool CResourceClientScript::Stop()
{
	
	return true;
}