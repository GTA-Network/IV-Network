//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CEvents.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEvents_h
#define CEvents_h

#include <Common.h>
#include <map>
#include "CScriptVM.h"
#include "CEventHandler.h"

class CEvents {

private:
	static CEvents* s_pInstance;

	std::map<CString, std::list<CEventHandler*>> m_Events;
public:
	CEvents()
	{
		s_pInstance = this;
	}
	~CEvents();
	
	static CEvents* GetInstance() { return s_pInstance; }

	bool Add(CString strName, CEventHandler* pEventHandler);

	bool Remove(CString strName, CEventHandler* pEventHandler);

	bool RemoveScript(CScriptVM* pVM);
	bool IsEventRegistered(CString eventName);

	void Clear();

	CScriptArguments Call(CString strName, CScriptArguments* pArguments, CEventHandler::eEventType EventType, CScriptVM * pVM);
};

#endif // CEvents_h