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

#include "CCheckpointEntity.h"
#include <IV/CIVScript.h>
#include <CCore.h>
extern CCore * g_pCore;

CCheckpointEntity::CCheckpointEntity(CIVScript::eCheckpointType type, CVector3 vecPosition, CVector3 vecTargetPosition, float fRadius) :
	CNetworkEntity(),
	m_eType(type),
	m_vecPosition(vecPosition),
	m_vecTargetPosition(vecTargetPosition),
	m_fRadius(fRadius),
	m_bInCheckpoint(false),
	m_bIsVisible(true),
	m_checkpoint(NULL)
{
	CNetworkEntity::SetType(CHECKPOINT_ENTITY);
}

CCheckpointEntity::~CCheckpointEntity()
{

}

unsigned int CCheckpointEntity::GetCheckpoint()
{
	return m_checkpoint;
}

void CCheckpointEntity::Show()
{
	if (m_checkpoint)
		CIVScript::DeleteCheckpoint(m_checkpoint);

	m_checkpoint = CIVScript::CreateCheckpoint(m_eType, m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ, m_vecTargetPosition.fX, m_vecTargetPosition.fY, m_vecTargetPosition.fZ, m_fRadius);

	m_bIsVisible = true;
}

void CCheckpointEntity::Hide()
{
	if (m_bIsVisible) {
		if (m_checkpoint) {
			CIVScript::DeleteCheckpoint(m_checkpoint);
			m_checkpoint = NULL;
			m_bIsVisible = false;
		}
	}
}

bool CCheckpointEntity::IsVisible()
{
	return m_bIsVisible;
}

void CCheckpointEntity::SetType(CIVScript::eCheckpointType type)
{
	if (type != m_eType) {
		m_eType = type;
		if (m_bIsVisible) {
			Show();
		}
	}
}

CIVScript::eCheckpointType CCheckpointEntity::GetType()
{
	return m_eType;
}

void CCheckpointEntity::SetPosition(CVector3 vecPosition)
{
		m_vecPosition = vecPosition;
		if (m_bIsVisible) {
			Show();
		}
}

void CCheckpointEntity::GetPosition(CVector3& vecPosition)
{
	vecPosition = m_vecPosition;
}

void CCheckpointEntity::SetTargetPosition(const CVector3& vecTargetPosition)
{
		m_vecTargetPosition = vecTargetPosition;
		if (m_bIsVisible) {
			Show();
		}
}

void CCheckpointEntity::GetTargetPosition(CVector3& vecTargetPosition)
{
	vecTargetPosition = m_vecTargetPosition;
}

void CCheckpointEntity::SetRadius(float fRadius)
{
	if (fRadius != m_fRadius) {
		m_fRadius = fRadius;
		if (m_bIsVisible) {
			Show();
		}
	}
}

float CCheckpointEntity::GetRadius()
{
	return m_fRadius;
}

void CCheckpointEntity::Pulse()
{
	if (!m_bIsVisible)
		return;

	CVector3 vecPosition;
	g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPosition);

	CVector3 vecDistance((m_vecPosition.fX - vecPosition.fX), (m_vecPosition.fY - vecPosition.fY), (m_vecPosition.fZ - vecPosition.fZ));

	if (sqrt((vecDistance.fX * vecDistance.fX) + (vecDistance.fY * vecDistance.fY) + (vecDistance.fZ * vecDistance.fZ)) <= (m_fRadius * 5.0f))
	{
		if (!m_bInCheckpoint)
		{
			RakNet::BitStream bitStream;
			bitStream.Write(GetId());
			g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_ENTER_CHECKPOINT), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);

			m_bInCheckpoint = true;
		}
	}
	else
	{
		if (m_bInCheckpoint)
		{
			RakNet::BitStream bitStream;
			bitStream.Write(GetId());
			g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_EXIT_CHECKPOINT), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);

			m_bInCheckpoint = false;
		}
	}
}