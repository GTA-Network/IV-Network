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
#include "CResourceServerScript.h"
#include "CResourceClientScript.h"
#include <SharedUtility.h>
#include <CXML.h>

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
	m_bLoaded = true;
	
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
	if(pMetaXML->findNode("info"))
	{
		// Not really important coming soon
		// Well its important to specify the script type so you can use any file ending
	}

	// Reset to root
	pMetaXML->nodeToRoot();

	if(pMetaXML->findNode("include"))
	{
		while(true)
		{
			if(!strcmp(pMetaXML->nodeName(),"include"))
			{
				const char* szIncludeResource = pMetaXML->getAttribute("resource");

				// TODO implement includes
				CLogFile::Printf("\t[TODO] Implement includes");
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
			if(!strcmp(pMetaXML->nodeName(), "script"))
			{
				CScript script;
				// Get the script name
				CString strScript = pMetaXML->getAttribute("src");

				if(!strScript.IsEmpty())
				{
					if (m_resourceScriptType == eResourceScriptType::UNKNOWN)
					{
						// Try to detect the resource script type
						if (strScript.EndsWith(".lua")) {
							m_resourceScriptType = eResourceScriptType::LUA_RESOURCE;
						} else if(strScript.EndsWith(".nut") || strScript.EndsWith(".sq")) {
							m_resourceScriptType = eResourceScriptType::SQUIRREL_RESOURCE;
						} else {
							CLogFile::Printf("Unknown script type");
							return false;
						}
					}

					
					CLogFile::Printf("\t[TODO] Implement scripts");
					//script.SetScriptFilename(strScript);

					CString scriptType = pMetaXML->getAttribute("type");
					if(scriptType == "client")
					{
						//script.SetType(CLIENT_SCRIPT);
						m_resourceFiles.push_back(new CResourceClientScript(this, strScript.Get(), (GetResourceDirectoryPath() + strScript).Get()));
					} else if(scriptType == "server") {
						m_resourceFiles.push_back(new CResourceServerScript(this, strScript.Get(), (GetResourceDirectoryPath() + strScript).Get()));
						//script.SetType(SERVER_SCRIPT);
					} else if(scriptType == "shared") {
						m_resourceFiles.push_back(new CResourceServerScript(this, strScript.Get(), (GetResourceDirectoryPath() + strScript).Get()));
						m_resourceFiles.push_back(new CResourceClientScript(this, strScript.Get(), (GetResourceDirectoryPath() + strScript).Get()));
						//script.SetType(SHARED_SCRIPT);
					} else {
						m_resourceFiles.push_back(new CResourceServerScript(this, strScript.Get(), (GetResourceDirectoryPath() + strScript).Get()));
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
			if(!strcmp(pMetaXML->nodeName(), "file"))
			{
				CString strFile = pMetaXML->getAttribute("src");

				CLogFile::Printf("\t[TODO] Implement client file manager which handles resource client files");
			}
			if(!pMetaXML->nextNode())
				break;
		}
	}

	// Delete the xml instance
	SAFE_DELETE(pMetaXML);

	// LOAD ALL INCLUDED SCRIPT
	// LOADD EVERYTHING LIKE IMAGES etc.
	
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
				return false;
			}

		}

		return true;
	}

	return false;
}

bool CResource::Stop(bool bStopManually)
{

	return true;
}

bool CResource::CreateVM()
{
	if(m_bLoaded && !m_pVM)
	{
		if(GetResourceScriptType() == LUA_RESOURCE)	{
			m_pVM =  new CLuaVM(this);
			CLogFile::Printf("LuaVM created");
			return true;
		} else if(GetResourceScriptType() == SQUIRREL_RESOURCE) {
			m_pVM = new CSquirrelVM(this);
			CLogFile::Printf("SquirrelVM created");
			return true;
		} else {
			CLogFile::Printf("Failed to create VM => Invalid resource script type");
			return false;
		}
	}
	CLogFile::Printf("Failed to create VM => %s", m_bLoaded ? "VM already created" : "Resource is not loaded");
	return false;
}

