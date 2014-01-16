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

#include "CModule.h"

#include <Common.h>
#include <CCore.h>
extern CCore * g_pCore;

CModule::CModule(CString strName)
{
	// Remove any illegal characters from the module name
	SharedUtility::RemoveIllegalCharacters(strName);

	// Get the module path string
	CString strModulePath(SharedUtility::GetAbsolutePath("multiplayer/modules/%s", strName.Get()));

	// Replace '/' with '\\'
	strModulePath.Substitute("/", "\\");

	// Create the libray instance
	m_pLibrary = new CLibrary();

	// Is the library instance invalid?
	if(!m_pLibrary)
		return;

	// Did the module fail to load?
	if(!m_pLibrary->Load(strModulePath.Get()))
	{
		// Delete the library instance
		SAFE_DELETE(m_pLibrary);

		return;
	}

	// Assign module name
	m_strName = strName;

	// Get the module function pointers
	m_moduleFunctions.pfnSetupFunctions = (SetupFunctions_t)m_pLibrary->GetProcedureAddress("SetupFunctions");
	m_moduleFunctions.pfnSetupInterfaces = (SetupInterfaces_t)m_pLibrary->GetProcedureAddress("SetupInterfaces");
	m_moduleFunctions.pfnSetupNewInterfaces = (SetupNewInterfaces_t)m_pLibrary->GetProcedureAddress("SetupNewInterfaces");
	m_moduleFunctions.pfnInitializeModule = (InitializeModule_t)m_pLibrary->GetProcedureAddress("InitModule");
	m_moduleFunctions.pfnPulse = (Pulse_t)m_pLibrary->GetProcedureAddress("Pulse");

	// Are the pointers invalid?
	if(!IsValid())
	{
		// Delete the library instance
		SAFE_DELETE(m_pLibrary);

		return;
	}

	// Setup the functions
	m_moduleFunctions.pfnSetupFunctions(FunctionContainer);

	// Setup the pointers
	InterfacesContainer[0] = (void *)g_pCore->GetNetworkManager();
	InterfacesContainer[1] = (void *)g_pCore->GetGame()->GetPlayerManager();
	InterfacesContainer[2] = (void *)g_pCore->GetGame()->GetVehicleManager();

	// Setup the container functions with the module
	m_moduleFunctions.pfnSetupInterfaces(InterfacesContainer);
}

CModule::~CModule(void)
{
	// Is the library instance valid?
	if(m_pLibrary)
	{
		// Unload the library
		m_pLibrary->Unload();

		// Delete the library instance
		SAFE_DELETE(m_pLibrary);
	}
}

bool CModule::IsValid(void)
{
	// Is the library instance invalid?
	if(!m_pLibrary)
		return false;

	// Are the library function pointers invalid?
	if(!m_moduleFunctions.pfnSetupFunctions || !m_moduleFunctions.pfnInitializeModule)
		return false;

	return true;
}

void CModule::Pulse(void)
{
	// Is the library instance invalid or pulse pointer invalid?
	if(!m_pLibrary || !m_moduleFunctions.pfnPulse)
		return;

	return m_moduleFunctions.pfnPulse();
}

void CModule::Load()
{
	// Initialize the module
	char szModuleName[64];
	strcpy(szModuleName, m_strName.Get());

	if(m_moduleFunctions.pfnInitializeModule(szModuleName))
		CLogFile::Printf("Loaded module '%s'", szModuleName);
}