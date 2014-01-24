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

#ifndef CBlipEntity_h
#define CBlipEntity_h

#include "CNetworkEntity.h"
#include "..\EFLC\ScriptEnums.h"

class CBlipEntity : public CNetworkEntity
{
private:
	EntityId				 m_blipId;
	EFLC::CScript::eBlipSprite   m_eIcon;
	CVector3				 m_vecPos;
	unsigned int			 m_uiColor;
	float					 m_fSize;
	bool					 m_bRange;
	bool					 m_bRouteBlip;
	bool					 m_bVisible;
	CString					 m_sName;
	unsigned int			 m_uiBlip;
public:
	CBlipEntity(EFLC::CScript::eBlipSprite icon, CVector3 vecPosition, bool bVisible);
	~CBlipEntity();

	bool							Create() { return true; }
	bool							Destroy() { return true; }

	void							SetId(EntityId blipId) { m_blipId = blipId; }
	EntityId						GetId() { return m_blipId; }

	void							SetIcon(EFLC::CScript::eBlipSprite icon);
	EFLC::CScript::eBlipSprite			GetIcon();

	void							SetPosition(CVector3 vecPosition);
	CVector3						GetPosition();

	void							SetColor(unsigned int uiColor);
	unsigned int					GetColor();

	void							SetSize(float fSize);
	float							GetSize();

	void							SetRange(bool bRange);
	bool							GetRange();

	void							SetVisible(bool bVisible);
	bool							GetVisible();

	void							SetName(CString sName);
	CString							GetName();
};

#endif // CBlipEntity_h