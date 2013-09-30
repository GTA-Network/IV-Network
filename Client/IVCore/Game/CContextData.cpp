//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CContextData.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CContextData.h"

std::list< CContextData *>	CContextDataManager::m_contextDataList;

CContextDataManager::~CContextDataManager()
{
	// Loop through the list
	for(std::list< CContextData *>::iterator iter = m_contextDataList.begin(); iter != m_contextDataList.end(); iter++)
	{
		// Delete this context info
		delete *iter;
	}
}

CContextData * CContextDataManager::CreateContextData(CIVPlayerInfo * pPlayerInfo)
{
	// Create the context data
	CContextData * pContextData = new CContextData(pPlayerInfo);

	// Push the context data into the list
	m_contextDataList.push_back(pContextData);

	return pContextData;
}

void CContextDataManager::DestroyContextData(CContextData * pContextData)
{
	// Loop through the list
	for(std::list< CContextData *>::iterator iter = m_contextDataList.begin(); iter != m_contextDataList.end(); iter++)
	{
		// Is this context data the one we're looking for?
		if(*iter == pContextData)
		{
			// Remove this data from the list
			m_contextDataList.remove(pContextData);

			// Break from the loop
			break;
		}
	}

	// Delete the context data
	delete pContextData;
}

CContextData * CContextDataManager::GetContextData(BYTE bytePlayerNumber)
{
	// Loop through the context data list
	for(std::list<CContextData *>::iterator iter = m_contextDataList.begin(); iter != m_contextDataList.end(); iter++)
	{
		// Get the context data pointer
		CContextData * pContextData = *iter;

		// Is this the context data we are looking for?
		if(pContextData->GetPlayerInfo()->GetPlayerNumber() == bytePlayerNumber)
		{
			return pContextData;
		}
	}

	return NULL;
}

CContextData * CContextDataManager::GetContextData(CIVPlayerInfo * pPlayerInfo)
{
	// Loop through the context data list
	for(std::list<CContextData *>::iterator iter = m_contextDataList.begin(); iter != m_contextDataList.end(); iter++)
	{
		// Get the context data pointer
		CContextData * pContextData = *iter;

		// Is this the context data we're looking for?
		if(pContextData->GetPlayerInfo() == pPlayerInfo)
		{
			return pContextData;
		}
	}

	return NULL;
}

CContextData * CContextDataManager::GetContextData(IVPlayerInfo * pPlayerInfo)
{
	// Loop through the context data list
	for(std::list<CContextData *>::iterator iter = m_contextDataList.begin(); iter != m_contextDataList.end(); iter++)
	{
		// Get the context data pointer
		CContextData * pContextData = *iter;

		// Is this the context data we're looking for?
		if(pContextData->GetPlayerInfo()->GetPlayerInfo() == pPlayerInfo)
		{
			return pContextData;
		}
	}

	return NULL;
}

CContextData * CContextDataManager::GetContextData(CIVPlayerPed * pPlayerPed)
{
	// Loop through the context data list
	for(std::list<CContextData *>::iterator iter = m_contextDataList.begin(); iter != m_contextDataList.end(); iter++)
	{
		// Get the context data pointer
		CContextData * pContextData = *iter;

		// Is this the context data we're looking for?
		if(pContextData->GetPlayerPed() == pPlayerPed)
		{
			return pContextData;
		}
	}

	return NULL;
}

CContextData * CContextDataManager::GetContextData(IVPlayerPed * pPlayerPed)
{
	// Loop through the context data list
	for(std::list<CContextData *>::iterator iter = m_contextDataList.begin(); iter != m_contextDataList.end(); iter++)
	{
		// Get the context data
		CContextData * pContextData = *iter;

		// Is this the context data we're looking for?
		if(pContextData->GetPlayerPed()->GetPlayerPed() == pPlayerPed)
		{
			return pContextData;
		}
	}

	return NULL;
}