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
#include <assert.h>
#include <CLogFile.h>
#include <algorithm>

CResourceManager::CResourceManager()
	: m_strResourceDirectory("resources/")
{

}

CResourceManager::CResourceManager(CString strResourceDirectory)
	: m_strResourceDirectory(strResourceDirectory)
{

}

CResourceManager::~CResourceManager()
{

}


void CResourceManager::AddResource(CResource * pResource)
{
	assert(std::find(m_resources.begin(), m_resources.end(), pResource) == m_resources.end());
	
	m_resources.push_back(pResource);

	CScriptVM* pVM = pResource->GetVM();
	assert(!pVM);
}

void CResourceManager::RemoveResource(CResource * pResource)
{

	m_resources.remove(pResource);

}

CResource * CResourceManager::Get(int * pVM) // TODO: change to GetByVM
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
	return 0;
}


bool CResourceManager::StartResource(CResource * pResource, std::list<CResource*> * dependents, bool bStartedManually, bool bStartIncludedResources)
{
	CLogFile::Printf("Resource started");
	return true;
}

CResource* CResourceManager::Load(CString strAbsPath, CString strResourceName)
{
	for(auto pResource : m_resources)
	{
		if(pResource->GetName() == strResourceName)
		{
			if(pResource->HasChanged())
			{
				pResource->Stop();
				RemoveResource(pResource);
				delete pResource;
				break;
			}
			else
				return pResource;
		}
	}


	CResource* loadResource = new CResource(strAbsPath, strResourceName);
	if(!loadResource->IsLoaded())
    {
        CLogFile::Printf("Loading of resource '%s' failed\n", strResourceName.Get());
        SAFE_DELETE(loadResource);
    } else {
		CLogFile::Printf("Resource loaded (%s)", strResourceName.Get());
		AddResource(loadResource);
		return loadResource;
	}

	return 0;
}