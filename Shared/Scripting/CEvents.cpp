//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CEvents.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CEvents.h"

CEvents* CEvents::s_pInstance = 0;


bool CEvents::Add(CString strName, CEventHandler* pEventHandler)
{
	auto itEvent = m_Events.find(strName);
	if(itEvent == m_Events.end())
	{
		// new - create the event
		auto ret = m_Events.insert(std::pair<CString, std::list<CEventHandler*>>(strName, std::list<CEventHandler*>()));
		itEvent = ret.first;

	} else {
		for(auto pEvent : itEvent->second)
		{
			if(pEventHandler->equals(pEvent))
				return false;
		}
	}

	itEvent->second.push_back(pEventHandler);
	return true;
}

void CEvents::Call(CString strName, CScriptArguments* pArguments, CEventHandler::eEventType EventType, CScriptVM * pVM)
{
	auto itEvent = m_Events.find(strName);
	if(itEvent != m_Events.end())
	{
		for(auto pEvent : itEvent->second)
		{
			if(EventType == CEventHandler::eEventType::GLOBAL_EVENT
				&& pEvent->GetType() == CEventHandler::GLOBAL_EVENT)
				pEvent->Call(pArguments);
			else if(EventType == CEventHandler::eEventType::RESOURCE_EVENT
				&& pEvent->GetType() == CEventHandler::RESOURCE_EVENT
				&& pEvent->GetVM() == pVM)
			{
				pEvent->Call(pArguments);
			}
		}
	}
}

bool CEvents::Remove(CString strName, CEventHandler* pEventHandler)
{
	auto itEvent = m_Events.find(strName);
	if(itEvent != m_Events.end())
	{
		for(auto pEvent = itEvent->second.begin(); pEvent != itEvent->second.end(); pEvent++)
		{
			if(pEventHandler->equals(*pEvent))
			{
				itEvent->second.erase(pEvent);
				if(itEvent->second.size() == 0)
				{
					m_Events.erase(itEvent);
					return true;
				}
			}
		}
	}
	return false;
}