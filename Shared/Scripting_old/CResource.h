//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResource.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResource_h
#define CResource_h

#include "CScript.h"
#include "CSquirrel.h"

class CSquirrel;

class CResource {

public:
	enum eResourceState
	{
		STATE_ERROR,
		STATE_LOADED,
		STATE_RUNNING,
		STATE_STARTUP_CANCELLED
	};

private:
	CSquirrel * m_pVM;

	bool			m_bValidMeta;
	CString			m_strName;
	CString			m_strResourcePath;
	eResourceState	m_eState;

	CString			m_strAuthor;
	CString			m_strType;
	CString			m_strInfoName;
	int				m_iVersion;
	
	std::list<CScript> m_Scripts;
public:
	CResource();
	CResource(CString strDirectory, CString strName);
	~CResource();

	eResourceState	GetState();
	CString			GetName();
	CString			GetPath();
	CSquirrel*		GetVM();

	bool			Reload();
	bool			Start();
	bool			Stop();
	bool			IsValidMeta();
	void			Process(unsigned long ulTime);
};

#endif // CResource_h