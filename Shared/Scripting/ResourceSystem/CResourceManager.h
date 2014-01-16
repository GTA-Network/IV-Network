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

#ifndef CResourceManager_h
#define CResourceManager_h

#include "CResource.h"
#include "../CLuaVM.h"

class CResourceManager {

private:
	CString					m_strResourceDirectory;
	std::list<CResource*>	m_resources;
	static CResourceManager*s_pInstance;

	typedef void(*CreateVM_t)(CScriptVM*);
	CreateVM_t						m_fnCreateVM = nullptr;

public:
	CResourceManager();
	CResourceManager(CString strResourceDirectory);
	~CResourceManager();

	void				SetCreateVMCallback(CreateVM_t fnCreateVM) {
		m_fnCreateVM = fnCreateVM;
	}

	static CResourceManager * GetInstance() { return s_pInstance; }

	void		SetResourceDirectory(CString strResourceDirectory) { m_strResourceDirectory = strResourceDirectory; }
	CString		GetResourceDirectory() { return m_strResourceDirectory; }

	CResource	*Load(CString strAbsPath, CString strResourceName);
	void		Unload(CResource* pResource);

	bool		StartResource(CResource* pResource, std::list<CResource*> * dependents = NULL, bool bStartedManually = false, bool bStartIncludedResources = true);
	bool		Reload(CResource* pResource);
	void		StopAllResources();

	void		AddResource(CResource* pResource);
	void		RemoveResource(CResource* pResource);

	CResource				*GetResource(CString strResourceName);
	std::list<CResource*>	GetResources() { return m_resources; }

	CResource *Get(int * pVM);
};

#endif // CResourceManager_h