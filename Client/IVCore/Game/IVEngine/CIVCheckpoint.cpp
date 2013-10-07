//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVCheckPoint.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVCheckPoint.h"
#include <Common.h>
#include <CLogFile.h>

CIVCheckpoint::CIVCheckpoint() :
	m_bCreatedByUs(true), m_pCheckpoint(new IVCheckpoint)
{
	memset(m_pCheckpoint, 0, sizeof(IVCheckpoint));
}

CIVCheckpoint::CIVCheckpoint(IVCheckpoint * pCheckpoint) :
	m_bCreatedByUs(false), m_pCheckpoint(pCheckpoint)
{
}

CIVCheckpoint::~CIVCheckpoint()
{
	if(m_bCreatedByUs)
		SAFE_DELETE(m_pCheckpoint);
}

void CIVCheckpoint::SetCheckpoint(IVCheckpoint * pCheckpoint)
{
	m_pCheckpoint = pCheckpoint;
}

IVCheckpoint * CIVCheckpoint::GetCheckpoint()
{
	return m_pCheckpoint;
}

void CIVCheckpoint::SetActiveState(BYTE byteActive)
{
	if(m_pCheckpoint)
		m_pCheckpoint->m_byteActive = byteActive;
}

BYTE CIVCheckpoint::GetActiveState()
{
	if(m_pCheckpoint)
		return m_pCheckpoint->m_byteActive;

	return 0;
}

void CIVCheckpoint::SetType(WORD wType)
{
	if(m_pCheckpoint)
		m_pCheckpoint->m_wType = wType;
}

WORD CIVCheckpoint::GetType()
{
	if(m_pCheckpoint)
		return m_pCheckpoint->m_wType;

	return 0;
}

void CIVCheckpoint::SetRadius(float fRadius)
{
	if(m_pCheckpoint)
		m_pCheckpoint->m_fRadius = fRadius;
}

float CIVCheckpoint::GetRadius()
{
	if(m_pCheckpoint)
		return m_pCheckpoint->m_fRadius;

	return 0.0f;
}

void CIVCheckpoint::SetPosition(const CVector3& vecPosition)
{
	if(m_pCheckpoint)
		memcpy(&m_pCheckpoint->m_vecPosition, &vecPosition, sizeof(CVector3));
}

void CIVCheckpoint::GetPosition(CVector3& vecPosition)
{
	if(m_pCheckpoint)
		memcpy(&vecPosition, &m_pCheckpoint->m_vecPosition, sizeof(CVector3));
}

void CIVCheckpoint::SetTargetPosition(const CVector3& vecTargetPosition)
{
	if(m_pCheckpoint)
		memcpy(&m_pCheckpoint->m_vecTargetPosition, &vecTargetPosition, sizeof(CVector3));
}

void CIVCheckpoint::GetTargetPosition(CVector3& vecTargetPosition)
{
	if(m_pCheckpoint)
		memcpy(&vecTargetPosition, &m_pCheckpoint->m_vecTargetPosition, sizeof(CVector3));
}