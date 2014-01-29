/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CContextData.h"
#include "CPools.h"

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

CContextData * CContextDataManager::CreateContextData(EFLC::CPlayerInfo * pPlayerInfo)
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

	return nullptr;
}

CContextData * CContextDataManager::GetContextData(EFLC::CPlayerInfo * pPlayerInfo)
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

	return nullptr;
}

CContextData * CContextDataManager::GetContextData(EFLC::IPlayerInfo * pPlayerInfo)
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

	return nullptr;
}

CContextData * CContextDataManager::GetContextData(EFLC::CPlayerPed * pPlayerPed)
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

	return nullptr;
}

CContextData * CContextDataManager::GetContextData(EFLC::IPlayerPed * pPlayerPed)
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

	return nullptr;
}