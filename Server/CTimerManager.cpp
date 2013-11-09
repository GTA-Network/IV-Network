//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTimerManager.cpp
// Project: Server.Core
// Author: 
// License: See LICENSE in root directory
//
//==============================================================================

#include "CTimerManager.h"

CTimerManager::CTimerManager()
{
}

CTimerManager::~CTimerManager()
{
}


bool CTimerManager::DoesExist(CTimer* pTimer)
{
	for (iterator iter = begin(); iter != end(); ++iter)
	if ((*iter) == pTimer)
		return true;

	return false;
}

void CTimerManager::Pulse()
{
	for (iterator iter = begin(); iter != end();)
	{
		if (!(*iter)->Pulse())
		{
			delete *iter;
			iter = erase(iter);
		}
		else
			++iter;
	}
}
