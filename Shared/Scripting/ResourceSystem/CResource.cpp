//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
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
#include "CResourceServerScript.h"
#include "CResourceClientScript.h"
#include <SharedUtility.h>
#include <CXML.h>
#include <Scripting/Natives/Natives.h>
#include <Scripting/CEvents.h>
#include <algorithm>

#ifdef _CLIENT
#else
#include "../../Server/Scripting/Natives/Natives_Server.h"
#endif

CResource::CResource()
	: m_pVM(0),
	m_strAbsPath(""),
	m_strResourceName(""),
	m_bLoaded(false),
	m_bActive(false),
	m_resourceScriptType(eResourceScriptType::UNKNOWN)
{


	Load();
}

CResource::CResource(CString strAbsPath, CString strResourceName)
	: m_pVM(0),
	m_strAbsPath(strAbsPath),
	m_strResourceName(strResourceName),
	m_bLoaded(false),
	m_bActive(false),
	m_resourceScriptType(eResourceScriptType::UNKNOWN)
{

	Load();
}

CResource::~CResource()
{

}

bool CResource::Load()
{
	m_strResourceDirectoryPath = m_strAbsPath + "/" + m_strResourceName;

	CString strMetaFile = m_strResourceDirectoryPath + "/" + "meta.xml";
	if(!SharedUtility::Exists(strMetaFile.Get()))
	{
		CLogFile::Printf("%s failed to load %s: No such file or directory", __FUNCTION__, strMetaFile.Get());
		return false;
	}

	CXML *pMetaXML = new CXML();
	if(!pMetaXML->load(strMetaFile))
	{
		CLogFile::Printf("%s failed to load meta.xml", __FUNCTION__);
		return false;
	}
	pMetaXML->nodeToRoot();
	if (pMetaXML->findNode("info"))
	{
		// Not really important coming soon
		// Well its important to specify the script type so you can use any file ending
		CString strScriptType = pMetaXML->getAttribute("scriptType");
		/*if(strScriptType == "Lua")
			m_resourceScriptType = eResourceScriptType::LUA_RESOURCE;
		else*/ if(strScriptType == "Squirrel")
			m_resourceScriptType = eResourceScriptType::SQUIRREL_RESOURCE;
		else 
			m_resourceScriptType = eResourceScriptType::UNKNOWN;
	}

	// Reset to root
	pMetaXML->nodeToRoot();

	if(pMetaXML->findNode("include"))
	{
		while(true)
		{
			if (pMetaXML->nodeName() && !strcmp(pMetaXML->nodeName(), "include"))
			{
				CLogFile::Printf("\t[WIP] Implement includes");

				CString strIncludedResource = pMetaXML->getAttribute("resource");
				if(!strIncludedResource.IsEmpty())
					m_includedResources.push_back(new CIncludedResource()); // TODO PARAMS
				else
					CLogFile::Printf("[WARNING] Emtpy 'resource' attribute from 'include' node of 'meta.xml' for resource %s", m_strResourceName.Get());
			}
			// Attempt to load the next include node (if any)
			if(!pMetaXML->nextNode())
				break;
		}
	}

	// Reset to root
	pMetaXML->nodeToRoot();

	// Get the first script node
	if(pMetaXML->findNode("script"))
	{
		while(true)
		{
			if(pMetaXML->nodeName() && !strcmp(pMetaXML->nodeName(), "script"))
			{
				CScript script;
				// Get the script name
				CString strScript = pMetaXML->getAttribute("src");

				if(!strScript.IsEmpty())
				{
					if (m_resourceScriptType == eResourceScriptType::UNKNOWN)
					{
						// Try to detect the resource script type
						/*if (strScript.EndsWith(".lua")) {
							m_resourceScriptType = eResourceScriptType::LUA_RESOURCE;
						} else*/ if(strScript.EndsWith(".nut") || strScript.EndsWith(".sq")) {
							m_resourceScriptType = eResourceScriptType::SQUIRREL_RESOURCE;
						} else {
							CLogFile::Printf("Unknown script type! Please specify the script type you use!");
							return false;
						}
					}

					CString scriptType = pMetaXML->getAttribute("type");
					if(scriptType == "client") {
						m_resourceFiles.push_back(new CResourceClientScript(this, strScript.Get(), (GetResourceDirectoryPath() + "/" + strScript).Get()));
					} else if(scriptType == "server") {
						m_resourceFiles.push_back(new CResourceServerScript(this, strScript.Get(), (GetResourceDirectoryPath() + "/" + strScript).Get()));
					} else if(scriptType == "shared") {
						m_resourceFiles.push_back(new CResourceServerScript(this, strScript.Get(), (GetResourceDirectoryPath() + "/" + strScript).Get()));
						m_resourceFiles.push_back(new CResourceClientScript(this, strScript.Get(), (GetResourceDirectoryPath() + "/" + strScript).Get()));
					} else {
						m_resourceFiles.push_back(new CResourceServerScript(this, strScript.Get(), (GetResourceDirectoryPath() + "/" + strScript).Get()));
					}
				}
			}
			// Attempt to load the next script node (if any)
			if(!pMetaXML->nextNode())
				break;
		}
	}

		// Reset to root
	pMetaXML->nodeToRoot();

	// Get the first script node
	if(pMetaXML->findNode("file"))
	{
		while(true)
		{
			if (pMetaXML->nodeName() && !strcmp(pMetaXML->nodeName(), "file"))
			{
				CString strFile = pMetaXML->getAttribute("src");

				CLogFile::Printf("\t[TODO] Implement client file manager which handles resource client files and then the loading stuff");
			}
			if(!pMetaXML->nextNode())
				break;
		}
	}

	// Delete the xml instance
	SAFE_DELETE(pMetaXML);

	// LOAD ALL INCLUDED SCRIPT
	// LOADD EVERYTHING LIKE IMAGES etc.
	m_bLoaded = true;
	return true;
}

bool CResource::Start(std::list<CResource*> * dependents, bool bStartManually, bool bStartIncludedResources)
{
	if(IsLoaded())
	{
		
		CreateVM();

		for(auto pResourceFile : m_resourceFiles)
		{
			if(!pResourceFile->Start())
			{
				// Stop all the resource items without any warnings
				//StopAllResourceFiles();
				DestroyVM();

				m_bActive = false;
				//m_bStarting = false;
				return false;
			}

		}

		if(bStartIncludedResources)
		{
			for(auto pIncludedResource : m_includedResources)
			{
				auto pResource = pIncludedResource->GetResource();
				if(pResource)
				{
					if(pResource->HasChanged())
                    {
                        // Reload it if it's not already started
                        if(!pResource->IsActive())
                        {
							pResource->Reload();
                        }
                        else
                        {
                            CLogFile::Printf("WARNING: Included resource %s has changed but unable to reload due to resource already being in use\n", pResource->GetName ().Get());
                        }
                    }

                    // Make us dependant of it
                    pResource->AddDependent(this);
				}
			}
		}

		// Call the scripting event
		CScriptArguments args;
		args.push(m_strResourceName);
		CEvents::GetInstance()->Call("resourceStarted", &args, CEventHandler::eEventType::NATIVE_EVENT, 0);
		return true;
	}

	return false;
}

bool CResource::Stop(bool bStopManually)
{
	CLogFile::Printf("[TODO] Implement %s", __FUNCTION__);
	return true;
}

bool CResource::Unload()
{
	Stop(true);

	m_bLoaded = false;

	return false;
}

void CResource::Reload()
{
	Unload();
	Load();
}

bool CResource::CreateVM()
{
	if(m_bLoaded && !m_pVM)
	{
		if(GetResourceScriptType() == LUA_RESOURCE)	{
			m_pVM =  new CLuaVM(this);
		} else if(GetResourceScriptType() == SQUIRREL_RESOURCE) {
			m_pVM = new CSquirrelVM(this);
		} else {
			CLogFile::Printf("Failed to create VM => Invalid resource script type");
			return false;
		}
		
		// Register Server/Client natives
		if (m_fnCreateVM)
			m_fnCreateVM(m_pVM);

		// Default shared natives
		CEventNatives::Register(m_pVM);
		CSystemNatives::Register(m_pVM);
		CMathNatives::Register(m_pVM); 

		return true;
	}
	CLogFile::Printf("Failed to create VM => %s", m_bLoaded ? "VM already created" : "Resource is not loaded");
	return false;
}

void CResource::DestroyVM()
{
	CLogFile::Printf("[TODO] Implement %s", __FUNCTION__);
}

void CResource::AddDependent(CResource* pResource)
{
	if(std::find(m_dependents.begin(), m_dependents.end(), pResource) != m_dependents.end())
		m_dependents.push_back(pResource);
}