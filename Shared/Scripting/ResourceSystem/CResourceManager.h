//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResourceManager.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResourceManager_h
#define CResourceManager_h

#include "CResource.h"
#include "../CLuaVM.h"

class CResourceManager {

private:
	CString					m_strResourceDirectory;
	std::list<CResource*>	m_resources;
	static CResourceManager*s_pInstance;
public:
	CResourceManager();
	CResourceManager(CString strResourceDirectory);
	~CResourceManager();

	static CResourceManager * GetInstance() { return s_pInstance; }

	CString		GetResourceDirectory() { return m_strResourceDirectory; }

	CResource	*Load(CString strAbsPath, CString strResourceName);
	void		Unload(CResource* pResource);

	bool		StartResource(CResource* pResource, std::list<CResource*> * dependents = NULL, bool bStartedManually = false, bool bStartIncludedResources = true);
	bool		Reload(CResource* pResource);
	void		StopAllResources();

	void		AddResource(CResource* pResource);
	void		RemoveResource(CResource* pResource);

	CResource				*GetResource(CString strResourceName);
	std::list<CResource*>	GetResources() { m_resources; }

	CResource *Get(int * pVM);
};

#endif // CResourceManager_h