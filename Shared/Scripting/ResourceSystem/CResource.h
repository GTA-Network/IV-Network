//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResource.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResource_h
#define CResource_h

#include <list>
#include "CIncludedResource.h"
#include "../CScriptVM.h"


class CResource {

private:
	CScriptVM	*m_pVM;

	std::list<CResource*>			m_dependents;
	std::list<CIncludedResource*>	m_includedResources;
public:
	CResource();
	~CResource();

	CScriptVM*	GetVM() { return m_pVM; };
	bool		CreateVM();
	void		DestroyVM();

	bool		Load();
	bool		Unload();
	void		Reload();

	 bool		Start(std::list<CResource *> * dependents = NULL, bool bStartManually = false, bool bStartIncludedResources = true);
	 bool		Stop(bool bStopManually = false);

	 std::list<CResource*> *		GetDependents() { return &m_dependents; }
	 int							GetDependentCount() { return m_dependents.size(); }
	 std::list<CIncludedResource*>*	GetIncludedResources() { return &m_includedResources; }
	 int							GetIncludedResourcesCount() { return m_includedResources.size(); }

	 void		AddDependent(CResource* pResource);
	 void		RemoveDependet(CResource* pResource);
	 bool		IsDependentResource(CResource* pResource);
	 bool		IsDependentResource(const char* szResourceName);
	 bool		IsDependentResourceRecursive(CResource* pResource);
	 bool		IsDependentResourceRecursive(const char* szResourceName);
};

#endif // CResource_h