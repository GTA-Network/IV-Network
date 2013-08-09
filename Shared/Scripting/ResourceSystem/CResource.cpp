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
#include <SharedUtility.h>
#include <CXML.h>

CResource::CResource()
	: m_pVM(0)
{


	Load();
}

CResource::CResource(CString strAbsPath, CString strResourceName)
	: m_pVM(0),
	m_strAbsPath(strAbsPath),
	m_strResourceName(strResourceName)
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

				// Make sure the name is valid and attempt to load the script
				if(strScript && !strScript.IsEmpty())
				{
#if 0
					// TODO: rewirte this shit
					script.SetScriptFilename(strScript);

					CString scriptType = pMetaXML->getAttribute("type");
					if(scriptType == "client")
					{
						script.SetType(CLIENT_SCRIPT);
					} else if(scriptType == "server") {
						script.SetType(SERVER_SCRIPT);
					} else if(scriptType == "shared") {
						script.SetType(SHARED_SCRIPT);
					}

					m_Scripts.push_back(script);
#endif
					CLogFile::Printf("\t[TODO] Implement scripts");
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

