/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CResource_h
#define CResource_h

#include <list>
#include "CIncludedResource.h"
#include "../IScriptVM.h"
#include "CResourceFile.h"

class IScriptVM;
class CIncludedResource;

enum eResourceScriptType {
	LUA_RESOURCE,
	SQUIRREL_RESOURCE,
	UNKNOWN,
};

class CResource
{
private:
	IScriptVM	*m_pVM;

	std::list<CResource*>			m_dependents;
	std::list<CIncludedResource*>	m_includedResources;
	std::list<CResourceFile *>		m_resourceFiles;

	eResourceScriptType				m_resourceScriptType;
	bool							m_bLoaded;
	bool							m_bActive;

	unsigned int					m_uiVersionMajor;
	unsigned int					m_uiVersionMinor;

	CString							m_strResourceName;
	CString							m_strAbsPath;
	CString							m_strResourceDirectoryPath;

	typedef void (*CreateVM_t)(IScriptVM*);
	CreateVM_t						m_fnCreateVM = nullptr;
public:
	CResource();
	CResource(CString strAbsPath, CString strResourceName);
	~CResource();

	void				SetCreateVMCallback(CreateVM_t fnCreateVM) {
		m_fnCreateVM = fnCreateVM;
	}

	eResourceScriptType	GetResourceScriptType() { return m_resourceScriptType; }
	bool				IsLoaded() { return m_bLoaded; }
	bool				IsActive() { return m_bActive; }

	CString		GetName() { return m_strResourceName; }
	CString		GetResourceDirectoryPath() { return m_strResourceDirectoryPath;  }
	bool		HasChanged() { return false; }

	IScriptVM*	GetVM() { return m_pVM; };
	bool		CreateVM();
	void		DestroyVM();

	bool		Load();
	bool		Unload();
	void		Reload();

	bool		Start(std::list<CResource *> * dependents = NULL, bool bStartManually = false, bool bStartIncludedResources = true);
	bool		Stop(bool bStopManually = false);

	std::list<CResource*> *			GetDependents() { return &m_dependents; }
	int								GetDependentCount() { return m_dependents.size(); }
	std::list<CIncludedResource*>*	GetIncludedResources() { return &m_includedResources; }
	int								GetIncludedResourcesCount() { return m_includedResources.size(); }
	std::list<CResourceFile *>*		GetResourceFiles() { return &m_resourceFiles; }

	void		AddDependent(CResource* pResource);
	void		RemoveDependet(CResource* pResource);
	bool		IsDependentResource(CResource* pResource);
	bool		IsDependentResource(const char* szResourceName);
	bool		IsDependentResourceRecursive(CResource* pResource);
	bool		IsDependentResourceRecursive(const char* szResourceName);
};

#endif // CResource_h