//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPlayerInfo.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPlayerInfo.h"
#include <CCore.h>
extern CCore * g_pCore;

CIVPlayerInfo::CIVPlayerInfo() :
	m_bCreatedByUs(false), m_pPlayerInfo(NULL)
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
	SetPlayerInfo(NULL);
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

	return NULL;
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