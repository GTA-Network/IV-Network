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
#include "..\EFLC\ScriptEnums.h"

class CCheckpointEntity : public CNetworkEntity
{
private:
	EntityId             m_checkpointId;
	EFLC::CScript::eCheckpointType      m_eType;
	CVector3             m_vecPosition;
	CVector3             m_vecTargetPosition;
	float                m_fRadius;
	bool                 m_bInCheckpoint;
	bool                 m_bIsVisible;
	unsigned int		 m_checkpoint;
public:
	CCheckpointEntity(EFLC::CScript::eCheckpointType type, CVector3 vecPosition, CVector3 vecTargetPosition, float fRadius);
	~CCheckpointEntity();

	bool Create() { return true; }
	bool Destroy() { return true; }

	void		SetId(EntityId checkpointId) { m_checkpointId = checkpointId; }
	EntityId	GetId() { return m_checkpointId; }

	unsigned int GetCheckpoint();

	void            Show();
	void            Hide();

	bool            IsVisible();

	void            SetType(EFLC::CScript::eCheckpointType type);
	EFLC::CScript::eCheckpointType GetType();

	void            SetPosition(CVector3 vecPosition);
	void            GetPosition(CVector3& vecPosition);

	void            SetTargetPosition(const CVector3& vecTargetPosition);
	void            GetTargetPosition(CVector3& vecTargetPosition);

	void            SetRadius(float fRadius);
	float           GetRadius();

	void            Pulse();
};

#endif // CCheckpointEntity_h