//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResource.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CResource.h"
#include <SharedUtility.h>
#include <CLogFile.h>
#include <CXML.h>

CResource::CResource(CString strDirectory, CString strName)
{
	m_bValidMeta = false;
	m_eState = STATE_ERROR;
	m_strName = strName;
	m_pVM = NULL;
	//m_pTimers = NULL;

	// place all files are located in
	m_strResourcePath = CString("%s%s%s", SharedUtility::GetAppPath(), strDirectory.Get(), strName.Get());

	// load the meta.xml
	if(!Reload())
		return;

	// it's valid after all and could be started
	m_bValidMeta = true;
	m_eState = STATE_LOADED;
}

CResource::~CResource()
{
	//SAFE_DELETE(m_pTimers);
	SAFE_DELETE(m_pVM);
}

// Reloads the meta.xml
bool CResource::Reload()
{
	// it's now invalid
	m_bValidMeta = false;

	// clear our saved stuff
	m_Scripts.clear();

	// Load all scripts in the meta.xml, create the xml instance
	CXML * pXML = new CXML();

	// Load the meta.xml file
	if(!pXML || !pXML->load(CString( "%s/meta.xml", m_strResourcePath.Get())))
	{
		CLogFile::Printf("Unable to load resource %s - no meta.xml", GetName().Get());
		return false;
	}

	// Reset to root
	pXML->nodeToRoot();

	if(pXML->findNode("info"))
	{
		// Get the resource author
		const char* szAuthor = pXML->getAttribute("author");

		if(szAuthor)
			m_strAuthor = szAuthor;

		// Get the resource version
		const char* szVersion = pXML->getAttribute("version");
		if(szVersion)
			m_iVersion = atoi(szVersion);
	}

	// Reset to root
	pXML->nodeToRoot();

	if(pXML->findNode("include"))
	{
		while(true)
		{
			if(!strcmp(pXML->nodeName(),"include"))
			{
				const char* szIncludeResource = pXML->getAttribute("resource");

				// TODO implement includes
				CLogFile::Printf("\t[TODO] Implement includes");
			}
			// Attempt to load the next include node (if any)
			if(!pXML->nextNode())
				break;
		}
	}

	// Reset to root
	pXML->nodeToRoot();

	// Get the first script node
	if(pXML->findNode("script"))
	{
		while(true)
		{
			if(!strcmp(pXML->nodeName(), "script"))
			{
				CScript script;
				// Get the script name
				CString strScript = pXML->getAttribute("src");

				// Make sure the name is valid and attempt to load the script
				if(strScript && !strScript.IsEmpty())
				{
					script.SetScriptFilename(strScript);

					CString scriptType = pXML->getAttribute("type");
					if(scriptType == "client")
					{
						script.SetType(CLIENT_SCRIPT);
					} else if(scriptType == "server") {
						script.SetType(SERVER_SCRIPT);
					} else if(scriptType == "shared") {
						script.SetType(SHARED_SCRIPT);
					}

					m_Scripts.push_back(script);
				}
			}
			// Attempt to load the next script node (if any)
			if(!pXML->nextNode())
				break;
		}
	}

		// Reset to root
	pXML->nodeToRoot();

	// Get the first script node
	if(pXML->findNode("file"))
	{
		while(true)
		{
			if(!strcmp(pXML->nodeName(), "file"))
			{
				CString strFile = pXML->getAttribute("src");

				CLogFile::Printf("\t[TODO] Implement client file manager which handles resource client files");
			}
			if(!pXML->nextNode())
				break;
		}
	}

	// Delete the xml instance
	SAFE_DELETE(pXML);

	// it's now valid
	m_bValidMeta = true;
	return true;
}

bool CResource::Start()
{
	// if it's not a loaded, ignore it
	if(GetState() != STATE_LOADED)
		return false;

	// create a squirrel VM
	m_pVM = new CSquirrel(this);
	if(!m_pVM)
	{
		CLogFile::Printf("\t[%s] Failed to create Squirrel VM.", GetName().Get());
		return false;
	}

	// create the timers manager
	/*m_pTimers = new CTimers(this);
	if( !m_pTimers )
	{
		CLogFile::Printf("[%s] Failed to create timers.", GetName().Get());
		return false;
	}*/

	// show a message
	CLogFile::Printf("\t[%s] Started resource.", GetName().Get());
	m_eState = STATE_RUNNING;

	// load all scripts, if at least one fails cancel the startup
	if(!m_pVM->LoadScripts(m_Scripts))
	{
		m_eState = STATE_STARTUP_CANCELLED;
		Stop();
		return false;
	}

	// call 'resourceStart' event,
	CSquirrelArgument argument = CEvents::GetInstance()->Call("resourceStart", m_pVM);

	// If resourceStart has failed cancel startup
	if(argument.GetType() == OT_BOOL && !argument.data.b)
	{
		m_eState = STATE_STARTUP_CANCELLED;
		Stop();
		return false;
	}
	return true;
}

bool CResource::Stop()
{
	// if it's not a valid resource, we can't stop it
	if(GetState() != STATE_RUNNING && GetState() != STATE_STARTUP_CANCELLED)
		return false;

	if(GetState() == STATE_RUNNING)
		CEvents::GetInstance()->Call("resourceStop", m_pVM);

	// kill all timers
	//SAFE_DELETE(m_pTimers);

	// delete the VM
	SAFE_DELETE(m_pVM);

	// Show a message
	CLogFile::Printf("[%s] Stopped Resource.", GetName().Get());
	m_eState = STATE_LOADED;
	return true;
}

bool CResource::IsValidMeta()
{
	return m_bValidMeta;
}

void CResource::Process(unsigned long ulTime)
{
	if(GetState() == STATE_RUNNING)
	{
		// Execute all outstanding timers
		//m_pTimers->Process(ulTime);
	}
}

CResource::eResourceState CResource::GetState()
{
	return m_eState;
}

CString CResource::GetName()
{
	return m_strName;
}

CString CResource::GetPath()
{
	return m_strResourcePath;
}

CSquirrel* CResource::GetVM()
{
	return m_pVM;
}

//CTimers* CResource::GetTimers()
//{
//	return m_pTimers;
//}
