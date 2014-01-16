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

#include "CIVPlayerInfo.h"
#include <CCore.h>
extern CCore * g_pCore;

CIVPlayerInfo::CIVPlayerInfo() :
	m_bCreatedByUs(false), 
	m_pPlayerInfo(nullptr)
{
}

CIVPlayerInfo::CIVPlayerInfo(BYTE bytePlayerNumber) :
	m_bCreatedByUs(true)
{
	unsigned char * pPlayerInfo = (unsigned char *) CGameFunction::Alloc(sizeof(IVPlayerInfo));

	if(!pPlayerInfo)
		CLogFile::Print("ERROR: CIVPlayerInfo::CIVPlayerInfo - Alloc fail!");

	((IVPlayerInfo *(__thiscall *) (IVPlayerInfo *))(COffsets::FUNC_CPlayerInfo__Constructor))((IVPlayerInfo *) pPlayerInfo);

	((IVPlayerInfo *)pPlayerInfo)->m_bytePlayerNumber = bytePlayerNumber;

	*(BYTE *)(pPlayerInfo + 0x15B) = 0;
	*(BYTE *)(pPlayerInfo + 0x15C) = 0;
	*(BYTE *)(pPlayerInfo + 0x15D) = 0;
	*(DWORD *)(pPlayerInfo + 0x137) = 2;

	m_pPlayerInfo = (IVPlayerInfo *) pPlayerInfo;
}

CIVPlayerInfo::CIVPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	// Mark as not created by us
	m_bCreatedByUs = false;

	// Set the player info
	SetPlayerInfo(pPlayerInfo);
}

CIVPlayerInfo::~CIVPlayerInfo()
{
	// Set the player info
	SetPlayerInfo(nullptr);
}

void CIVPlayerInfo::SetPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	// Was this created by us?
	if(m_bCreatedByUs)
	{
		((void(__thiscall *) (IVPlayerInfo *))(COffsets::FUNC_CPlayerInfo__Deconstructor))(m_pPlayerInfo);

		CGameFunction::Free(pPlayerInfo);
	}

	// Copy the player info
	m_pPlayerInfo = pPlayerInfo;
}

IVPlayerInfo * CIVPlayerInfo::GetPlayerInfo()
{
	return m_pPlayerInfo;
}

void CIVPlayerInfo::SetPlayerNumber(BYTE bytePlayerNumber)
{
	if(m_pPlayerInfo)
		m_pPlayerInfo->m_bytePlayerNumber = bytePlayerNumber;
}

BYTE CIVPlayerInfo::GetPlayerNumber()
{
	if(m_pPlayerInfo)
		return m_pPlayerInfo->m_bytePlayerNumber;

	return INVALID_PLAYER_PED;
}

void CIVPlayerInfo::SetPlayerPed(IVPlayerPed * pPlayerPed)
{
	if(m_pPlayerInfo)
		m_pPlayerInfo->m_pPlayerPed = pPlayerPed;
}

IVPlayerPed * CIVPlayerInfo::GetPlayerPed()
{
	if(m_pPlayerInfo)
		return m_pPlayerInfo->m_pPlayerPed;

	return nullptr;
}

void CIVPlayerInfo::SetName(char * szName)
{
	if(m_pPlayerInfo)
		strncpy(m_pPlayerInfo->m_szName, szName, 20);
}

char * CIVPlayerInfo::GetName()
{
	if(m_pPlayerInfo)
		return m_pPlayerInfo->m_szName;

	return 0;
}

void CIVPlayerInfo::SetColour(DWORD dwColour)
{
	if(m_pPlayerInfo)
		m_pPlayerInfo->m_dwColour = dwColour;
}

DWORD CIVPlayerInfo::GetColour()
{
	if(m_pPlayerInfo)
		return m_pPlayerInfo->m_dwColour;

	return 0;
}

void CIVPlayerInfo::SetScore(int iScore)
{
	if(m_pPlayerInfo)
		XLivePBufferSetDWORD((FakeProtectedBuffer *)m_pPlayerInfo->m_pScore, 0, (DWORD)iScore);
}

int CIVPlayerInfo::GetScore()
{
	if(m_pPlayerInfo)
	{
		int iScore;
		XLivePBufferGetDWORD((FakeProtectedBuffer *)m_pPlayerInfo->m_pScore, 0, (DWORD *)&iScore);
		return iScore;
	}

	return 0;
}

int CIVPlayerInfo::GetDisplayScore()
{
	if(m_pPlayerInfo)
	{
		int iScore;
		XLivePBufferGetDWORD((FakeProtectedBuffer *)m_pPlayerInfo->m_pDisplayScore, 0, (DWORD *)&iScore);
		return iScore;
	}

	return 0;
}

void CIVPlayerInfo::SetDisplayScore(int iScore)
{
	if(m_pPlayerInfo)
		XLivePBufferSetDWORD((FakeProtectedBuffer *)m_pPlayerInfo->m_pDisplayScore, 0, (DWORD)iScore);
}