//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CResourceServerScript.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CResourceServerScript.h"

#include "CResource.h"
#include <Scripting/CEvents.h>

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

	// Call the scripting event
	CScriptArguments args;
	args.push(m_strShortName.Get());
	CEvents::GetInstance()->Call("scriptLoaded", &args, CEventHandler::eEventType::RESOURCE_EVENT, m_resource->GetVM());
	return true;
}

bool CResourceServerScript::Stop()
{
	// Nothing can be done here
	return true;
}