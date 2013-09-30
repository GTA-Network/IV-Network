//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CModule.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CModule_h
#define CModule_h

#include <CLibrary.h>
#include <CLogFile.h>

static void * FunctionContainer[] = {
	(void *)CLogFile::Printf
};

static	void	* InterfacesContainer[2];

typedef void (* SetupFunctions_t)(void *);
typedef void (* SetupInterfaces_t)(void *);
typedef void (* SetupNewInterfaces_t)(void *);
typedef bool (* InitialiseModule_t)(char *);
typedef void (* Pulse_t)(void);

struct SModuleFunctions
{
	SetupFunctions_t pfnSetupFunctions;
	SetupInterfaces_t pfnSetupInterfaces;
	SetupNewInterfaces_t pfnSetupNewInterfaces;
	InitialiseModule_t pfnInitialiseModule;
	Pulse_t pfnPulse;
};

class CModule
{

private:
	CLibrary						* m_pLibrary;
	SModuleFunctions				m_moduleFunctions;
	CString							m_strPath;
	CString							m_strName;

public:

									CModule(CString strName);
									~CModule();

	bool							IsValid();
	void							Pulse();
	void							Load();
	void							SetPath(CString strPath) { m_strPath = strPath; }
	CString							GetPath() { return m_strPath; }
	CString							GetName() { return m_strName; }

};
#endif // CModule_h