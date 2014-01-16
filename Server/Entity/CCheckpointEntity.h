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

#ifndef CCheckpointEntity_h
#define CCheckpointEntity_h

#include "CNetworkEntity.h"

class CScriptCheckpoint;

class CCheckpointEntity : public CNetworkEntity 
{
private:
	CScriptCheckpoint*		m_pScriptCheckpoint;
	int						m_wType;
	CVector3				m_vecTargetPosition;
	float					m_fRadius;
	bool					m_bVisible;
public:
	CCheckpointEntity();
	~CCheckpointEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}

	void					SetScriptCheckpoint(CScriptCheckpoint* pScriptCheckpoint) { m_pScriptCheckpoint = pScriptCheckpoint; }
	CScriptCheckpoint*		GetScriptCheckpoint() { return m_pScriptCheckpoint; }

	void					SetType(int wType) { m_wType = wType; }
	int						GetType() { return m_wType; }

	void					SetTargetPosition(CVector3 vecTargetPosition) { m_vecTargetPosition = vecTargetPosition; }
	void					GetTargetPosition(CVector3& vecTargetPosition) { vecTargetPosition = m_vecTargetPosition; }

	void					SetVisible(bool bVisible) { m_bVisible = bVisible; }
	bool					GetVisible() { return m_bVisible; }

	void					SetRadius(float fRadius) { m_fRadius = fRadius; }
	float					GetRadius() { return m_fRadius; }
};

class CScriptCheckpoint : public CScriptEntity
{
public:
	CScriptCheckpoint() { };
	~CScriptCheckpoint() { };

	CCheckpointEntity *		GetEntity() { return (CCheckpointEntity*)CScriptEntity::GetEntity(); }

	const char *			GetScriptClassName() { return "CCheckpointEntity"; }

	void					DeleteCheckpoint();

	void					ShowForPlayer(EntityId playerId);
	void					HideForPlayer(EntityId playerId);

	void					ShowForAll();
	void					HideForAll();

	void					SetType(int iType);
	int						GetType() { return GetEntity()->GetType(); }

	void					SetPosition(float fX, float fY, float fZ);
	CVector3				GetPosition() { CVector3 vecPos; GetEntity()->GetPosition(vecPos); return vecPos; }

	void					SetTargetPosition(float fX, float fY, float fZ);
	CVector3				GetTargetPosition() { CVector3 vecNextPos; GetEntity()->GetTargetPosition(vecNextPos); return vecNextPos; }

	void					SetRadius(float fRadius);
	float					GetRadius() { return GetEntity()->GetRadius(); }
};

#endif // CCheckpointEntity_h