//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CResourceServerScript.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CResourceServerScript.h"

#include "CResource.h"

CResourceServerScript::CResourceServerScript(CResource * resource, const char * szShortName, const char * szResourceFileName)
	: CResourceScriptFile(resource, szShortName, szResourceFileName)
{
	m_type = RESOURCE_FILE_TYPE_SERVER_SCRIPT;
}

CResourceServerScript::~CResourceServerScript()
{

}

bool CResourceServerScript::Start()
{
	m_resource->GetVM()->LoadScript(m_strShortName);
	return true;
}

bool CResourceServerScript::Stop()
{

	return true;
}