//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CSquirrel.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSquirrel_h
#define CSquirrel_h

#include <list>
#include <Common.h>
#include <assert.h>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqobject.h>
#include <Squirrel/sqvm.h>
#include "CSquirrelArgument.h"
#include "CResource.h"
#include "CEvents.h"

class CResource;

class CSquirrel {

private:
	SQVM		* m_pVM;
	CResource	* m_pResource;

public:
	CSquirrel(CResource* pResource);
	~CSquirrel();

	SQVM*		GetVM() { return m_pVM; }
	bool		LoadScript(CString script);
	bool		LoadScripts(std::list<CScript> scripts);

	void		RegisterFunction(const char* szFunctionName, SQFUNCTION pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false);
	bool		Call(SQObjectPtr& pFunction, CSquirrelArguments* pArguments);
	void        Call(SQObjectPtr pFunction, CSquirrelArguments * pArguments = NULL, CSquirrelArgument * pReturn = NULL);

	bool        RegisterClassStart(const char * szClassName, const char * szBaseClassName = NULL);
	void        RegisterClassFinish();
};

#endif // CSquirrel_h