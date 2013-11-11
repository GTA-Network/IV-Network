//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CBlipEntity.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CBlipEntity.h"
#include <IV/CIVScript.h>
#include <CCore.h>

CBlipEntity::CBlipEntity(CIVScript::eBlipSprite icon, CVector3 vecPosition, bool bRange) :
CNetworkEntity(),
m_eIcon(icon),
m_vecPos(vecPosition),
m_bRange(bRange),
m_bRouteBlip(true),
m_bVisible(true)
{
	CNetworkEntity::SetType(BLIP_ENTITY);

	m_uiBlip = CIVScript::AddBlipForCoord(vecPosition.fX, vecPosition.fY, vecPosition.fZ, (unsigned int*)icon);
	CIVScript::SetBlipShortRange(m_uiBlip, bRange);
}

CBlipEntity::~CBlipEntity()
{
}

void CBlipEntity::SetIcon(CIVScript::eBlipSprite icon)
{
	if (!m_uiBlip)
		return;

	CIVScript::ChangeBlipSprite(m_uiBlip, icon);
	m_eIcon = icon;
}

CIVScript::eBlipSprite CBlipEntity::GetIcon()
{
	return m_eIcon;
}

void CBlipEntity::SetPosition(CVector3 vecPosition)
{
	if (!m_uiBlip)
		return;

	CIVScript::RemoveBlip(m_uiBlip);

	if (m_bVisible)
		m_uiBlip = CIVScript::AddBlipForCoord(vecPosition.fX, vecPosition.fY, vecPosition.fZ, (unsigned int*)m_eIcon);

	m_vecPos = vecPosition;
}

CVector3 CBlipEntity::GetPosition()
{
	return m_vecPos;

}

void CBlipEntity::SetColor(unsigned int uiColor)
{
	if (!m_uiBlip)
		return;

	CIVScript::ChangeBlipColour(m_uiBlip, uiColor);
	m_uiColor = uiColor;
}

unsigned int CBlipEntity::GetColor()
{
	return m_uiColor;
}

void CBlipEntity::SetSize(float fSize)
{
	if (!m_uiBlip)
		return;

	CIVScript::ChangeBlipScale(m_uiBlip, fSize);
	m_fSize = fSize;
}

float CBlipEntity::GetSize()
{
	return m_fSize;
}

void CBlipEntity::SetRange(bool bRange)
{
	if (!m_uiBlip)
		return;

	CIVScript::SetBlipShortRange(m_uiBlip, bRange);
	m_bRange = bRange;
}

bool CBlipEntity::GetRange()
{
	return m_bRange;
}

void CBlipEntity::SetVisible(bool bVisible)
{
	if (!m_uiBlip)
		return;

	CIVScript::RemoveBlip(m_uiBlip);

	if (m_bVisible)
		m_uiBlip = CIVScript::AddBlipForCoord(m_vecPos.fX, m_vecPos.fY, m_vecPos.fZ, (unsigned int*)m_eIcon);

	m_bVisible = bVisible;
}

bool CBlipEntity::GetVisible()
{
	return m_bVisible;
}

void CBlipEntity::SetName(CString sName)
{
	if (!m_uiBlip)
		return;

	CIVScript::ChangeBlipNameFromAscii(m_uiBlip, sName.C_String());
	m_sName = sName;
}

CString CBlipEntity::GetName()
{
	return m_sName;
}