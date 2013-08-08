//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CEvents.cpp
// Project: Shared
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CEvents.h"

CEvents * CEvents::m_pInstance = NULL;

CEvents::CEvents()
{
	m_pInstance = this;
}

CEvents::~CEvents()
{
	m_Events.clear();
}

bool CEvents::Add(CString strName, CEventHandler* pEventHandler)
{
	// Any events with that name?
	auto iter =  m_Events.find(strName);
	if(iter !=  m_Events.end())
	{
		// Event exists, check if the function is registered already
		for(std::list< CEventHandler* >::iterator iter2 = (*iter).second.begin(); iter2 != (*iter).second.end(); ++ iter2)
		{
			if(pEventHandler->equals(*iter2))
				return false;
		}
	}
	else
	{
		// new - create the event
		std::pair<std::map<CString, std::list<CEventHandler*>>::iterator, bool> ret;
		ret =  m_Events.insert(std::pair<CString, std::list<CEventHandler*>>(strName, std::list< CEventHandler* >()));

		iter = ret.first;
	}

	// insert the handler
	(*iter).second.push_back(pEventHandler);
	return true;
}

bool CEvents::Remove(CString strName, CEventHandler* pEventHandler)
{
	// Any events with that name?
	auto iter =  m_Events.find(strName);
	if(iter !=  m_Events.end())
	{
		// Check if it exists, if so remove it
		bool bRemoved = false;
		for(std::list<CEventHandler*>::iterator iter2 = (*iter).second.begin(); iter2 != (*iter).second.end(); )
		{
			if(pEventHandler->equals(*iter2))
			{
				(*iter).second.erase(iter2++);
				bRemoved = true;
				break;
			}
			else
				iter2 ++;
		}

		if(bRemoved)
		{
			// remove the event list if it is empty
			if((*iter).second.size() == 0)
			{
				m_Events.erase(iter);
			}
		}

		return bRemoved;
	}

	// no such event - can't remove handlers
	return false;
}

bool CEvents::IsEventRegistered(CString eventName)
{
	auto iter = m_Events.find(eventName);
	return iter !=  m_Events.end();
}


CSquirrelArgument CEvents::Call(CString strName, CSquirrel* pScript)
{
	CSquirrelArgument pReturn((int)1);
	Call(strName, &CSquirrelArguments(), &pReturn, pScript);
	return pReturn;
}

CSquirrelArgument CEvents::Call(CString strName, CSquirrelArguments* pArguments, CSquirrel* pScript)
{
	CSquirrelArgument pReturn((int)1);
	Call(strName, pArguments, &pReturn, pScript);
	return pReturn;
}

void CEvents::Call(CString strName, CSquirrelArguments* pArguments, CSquirrelArgument* pReturn, CSquirrel* pScript)
{
	//currentEventName = strName;
	SQVM* pVM = pScript ? pScript->GetVM() : 0;

	// Any events with that name?
	auto Event = m_Events.find(strName);
	if(Event != m_Events.end())
	{
		// loop through all handlers
		for(auto pEventHandler : (*Event).second)
		{
			// not for a specific script; or that script is the one we want
			if(!pVM || pVM == pEventHandler->GetScript())
			{
				pEventHandler->Call(pArguments, pReturn);
			}
		}
	}
}
