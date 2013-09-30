//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CModule.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

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
	m_moduleFunctions.pfnInitialiseModule = (InitialiseModule_t)m_pLibrary->GetProcedureAddress("InitModule");
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
	if(!m_moduleFunctions.pfnSetupFunctions || !m_moduleFunctions.pfnInitialiseModule)
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
	// Initialise the module
	char szModuleName[64];
	strcpy(szModuleName, m_strName.Get());

	if(m_moduleFunctions.pfnInitialiseModule(szModuleName))
		CLogFile::Printf("Loaded module '%s'", szModuleName);
}