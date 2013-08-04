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

	// Get the first script node
	if(pXML->findNode("script"))
	{
		while(true)
		{
			// Get the script name
			CString strScript = pXML->nodeContent();

			// Make sure the name is valid and attempt to load the script
			if(strScript && !strScript.IsEmpty())
				m_Scripts.push_back(strScript);

			// Attempt to load the next script node (if any)
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
	if( GetState() != STATE_LOADED )
		return false;

	// create a squirrel VM
	m_pVM = new CSquirrel(this);
	if( !m_pVM )
	{
		CLogFile::Printf("[%s] Failed to create Squirrel VM.", GetName().Get());
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
	CLogFile::Printf("[%s] Started resource.", GetName().Get());
	m_eState = STATE_RUNNING;

	// load all scripts, if at least one fails cancel the startup
	if( !m_pVM->LoadScripts( m_Scripts ) )
	{
		m_eState = STATE_STARTUP_CANCELLED;
		Stop();
		return false;
	}

	// call 'resourceStart' event, if it fails then cancel the startup
	/*if(!CallEvent( "resourceStart", NULL, true, false))
	{
		m_eState = STATE_STARTUP_CANCELLED;
		Stop();
		return false;
	}*/
	return true;
}

bool CResource::Stop()
{
	// if it's not a valid resource, we can't stop it
	if( GetState() != STATE_RUNNING && GetState() != STATE_STARTUP_CANCELLED )
		return false;

	//if( GetState() == STATE_RUNNING )
	//	CallEvent("resourceStop", NULL, true, false);

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
	if( GetState() == STATE_RUNNING )
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
