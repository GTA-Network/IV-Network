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

#include "CBlipEntity.h"
#include <Game/EFLC/CScript.h>
#include <CCore.h>

CBlipEntity::CBlipEntity(EFLC::CScript::eBlipSprite icon, CVector3 vecPosition, bool bRange) :
CNetworkEntity(),
m_eIcon(icon),
m_vecPos(vecPosition),
m_bRange(bRange),
m_bRouteBlip(true),
m_bVisible(true)
{
	CNetworkEntity::SetType(BLIP_ENTITY);

	m_uiBlip = EFLC::CScript::AddBlipForCoord(vecPosition.fX, vecPosition.fY, vecPosition.fZ, (unsigned int*)icon);
	EFLC::CScript::SetBlipShortRange(m_uiBlip, bRange);
}

CBlipEntity::~CBlipEntity()
{
}

void CBlipEntity::SetIcon(EFLC::CScript::eBlipSprite icon)
{
	if (!m_uiBlip)
		return;

	EFLC::CScript::ChangeBlipSprite(m_uiBlip, icon);
	m_eIcon = icon;
}

EFLC::CScript::eBlipSprite CBlipEntity::GetIcon()
{
	return m_eIcon;
}

void CBlipEntity::SetPosition(CVector3 vecPosition)
{
	if (!m_uiBlip)
		return;

	EFLC::CScript::RemoveBlip(m_uiBlip);

	if (m_bVisible)
		m_uiBlip = EFLC::CScript::AddBlipForCoord(vecPosition.fX, vecPosition.fY, vecPosition.fZ, (unsigned int*)m_eIcon);

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

	EFLC::CScript::ChangeBlipColour(m_uiBlip, uiColor);
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

	EFLC::CScript::ChangeBlipScale(m_uiBlip, fSize);
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

	EFLC::CScript::SetBlipShortRange(m_uiBlip, bRange);
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

	EFLC::CScript::RemoveBlip(m_uiBlip);

	if (m_bVisible)
		m_uiBlip = EFLC::CScript::AddBlipForCoord(m_vecPos.fX, m_vecPos.fY, m_vecPos.fZ, (unsigned int*)m_eIcon);

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

	EFLC::CScript::ChangeBlipNameFromAscii(m_uiBlip, sName.C_String());
	m_sName = sName;
}

CString CBlipEntity::GetName()
{
	return m_sName;
}