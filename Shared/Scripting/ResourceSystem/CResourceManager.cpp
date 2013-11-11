//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
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

CResourceManager* CResourceManager::s_pInstance = NULL;

CResourceManager::CResourceManager()
	: m_strResourceDirectory("resources/")
{
	s_pInstance = this;
}

CResourceManager::CResourceManager(CString strResourceDirectory)
	: m_strResourceDirectory(strResourceDirectory)
{
	s_pInstance = this;
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
	assert(std::find(m_resources.begin(), m_resources.end(), pResource) != m_resources.end());

	m_resources.remove(pResource);
}

CResource * CResourceManager::Get(int * pVM) // TODO: change to GetResourceByVM
{ 
	for(auto pResource : m_resources) 
	{ 
		if(pResource)
		{
			if(pResource->GetVM()->GetVMType() == LUA_VM)
			{
				CLuaVM* pLuaVM = (CLuaVM*)pResource->GetVM();
				if(pLuaVM && pLuaVM->GetVM() == (lua_State*)pVM) {
					return pResource;
				}
			} 
			else if(pResource->GetVM()->GetVMType() == SQUIRREL_VM) 
			{
				CSquirrelVM* pLuaVM = (CSquirrelVM*)pResource->GetVM();
				if(pLuaVM && pLuaVM->GetVM() == (SQVM*)pVM) {
					return pResource;
				}
			}
		}
	}
	return 0;
}

bool CResourceManager::Reload(CResource* pResource)
{
	pResource->Reload();

	// Was it loaded successfully?
	if(!pResource->IsLoaded())
	{
		CLogFile::Printf("Reloading of resource '%s' failed\n", pResource->GetName().Get());
		return false;
	}
	CLogFile::Printf("Resource '%s' reloaded\n", pResource->GetName().Get());
	return true;
}

bool CResourceManager::Unload(CResource* pResource)
{
	if (pResource->Unload())
	{
		CLogFile::Printf("Resource '%s' unloaded\n", pResource->GetName().Get());
		return true;
	}
	CLogFile::Printf("Unloading of resource '%s' failed\n", pResource->GetName().Get());
	return false;
}

bool CResourceManager::StartResource(CResource * pResource, std::list<CResource*> * dependents, bool bStartedManually, bool bStartIncludedResources)
{
	// Has resource changed since load?
	if(pResource->HasChanged())
	{
		// Attempt to reload it
		if(Reload(pResource))
		{
			// Start the resource
			return pResource->Start(NULL, bStartedManually, bStartIncludedResources);
		}
		else
			return false;
	}
	else
	{
		// If it's not running yet
		if(!pResource->IsActive())
		{
			CLogFile::Printf("Resource '%s' started\n", pResource->GetName().Get());
			// Start it
			return pResource->Start(dependents, bStartedManually, bStartIncludedResources);
		}
		CLogFile::Printf("Starting resource '%s' failed\n", pResource->GetName().Get());
		return false;
	}

	// Stop it again if it failed starting
	CLogFile::Printf("Starting resource '%s' failed\n", pResource->GetName().Get());
	pResource->Stop();
	return false;
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
	}
	else {
		CLogFile::Printf("Resource '%s' loaded\n", strResourceName.Get());
		loadResource->SetCreateVMCallback(m_fnCreateVM);
		AddResource(loadResource);
		return loadResource;
	}


	return 0;
}