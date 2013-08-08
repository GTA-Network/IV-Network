//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CEvents.h
// Project: Shared
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEvents_h
#define CEvents_h

#include <Common.h>
#include <map>
#include "CSquirrel.h"
#include "CSquirrelEventHandler.h"

class CSquirrel;

class CEvents
{
private:
	static CEvents	*m_pInstance;
	std::map<CString, std::list<CEventHandler*>> m_Events;
public:
	CEvents();
	~CEvents();

	static CEvents				* GetInstance() { return m_pInstance; }

	bool				Add(CString strName, CEventHandler* pEventHandler);
	bool				Remove(CString strName, CEventHandler* pEventHandler);
	bool				IsEventRegistered(CString eventName);

	CSquirrelArgument	Call(CString strName, CSquirrel* pScript = NULL);
	CSquirrelArgument	Call(CString strName, CSquirrelArguments* pArguments, CSquirrel* pScript = NULL);
	void				Call(CString strName, CSquirrelArguments* pArguments, CSquirrelArgument* pReturn, CSquirrel* pScript = NULL);
};

#endif // CEvents_h