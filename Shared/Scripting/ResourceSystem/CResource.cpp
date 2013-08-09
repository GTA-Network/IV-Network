//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CResource.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================


#include "CResource.h"
#include <CLogFile.h>
#include "../CLuaVM.h"
#include "../CSquirrelVM.h"

CResource::CResource()
	: m_pVM(0)
{

}

CResource::~CResource()
{

}

bool CResource::Load()
{
	m_bLoaded = true;

	return true;
}

bool CResource::CreateVM()
{
	if(m_bLoaded && !m_pVM)
	{
		if(GetResourceScriptType() == LUA_RESOURCE)	{
			m_pVM =  new CLuaVM(this);
			return true;
		} else if(GetResourceScriptType() == SQUIRREL_RESOURCE) {
			m_pVM = new CSquirrelVM(this);
			return true;
		} else {
			CLogFile::Printf("Failed to create VM => Invalid resource script type");
			return false;
		}
	}
	CLogFile::Printf("Failed to create VM => %s", m_bLoaded ? "VM already created" : "Resource is not loaded");
	return false;
}

