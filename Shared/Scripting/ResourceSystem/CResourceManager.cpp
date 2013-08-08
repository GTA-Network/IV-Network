//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CResourceManager.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CResourceManager.h"
#include "../CLuaVM.h"
#include "../CSquirrelVM.h"

CResource * CResourceManager::Get(int * pVM)
{ 
	for(auto pResource : m_resources) 
	{ 
		if(pResource->GetVM()->GetVMType() == LUA_VM)
		{
			if(((CLuaVM*)pResource->GetVM())->GetVM() == (lua_State*)pVM)
				return pResource;
		} else if(pResource->GetVM()->GetVMType() == SQUIRREL_VM) {
			if(((CSquirrelVM*)pResource->GetVM())->GetVM() == (SQVM*)pVM)
				return pResource;
		}
	}
	return NULL;
}