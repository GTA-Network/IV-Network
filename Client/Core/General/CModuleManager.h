//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CModuleManager.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CModuleManager_h
#define CModuleManager_h

#include <Common.h>
#include <list>

class CModule {
public:
	CString	* strModulePath;
	CString * strModuleName;
	bool	  m_bLoaded;
};

class CModuleManager {
private:
	static std::list<CModule *>		m_pModules;
public:
	
	static void			FetchModules();
	static CString		*GetModules();
	static CString		*GetModulePath(CString *strModule);
	static void			LoadModule(CString *strModule, CString *strModulePath, bool bForce);
};

#endif // CModuleManager_h