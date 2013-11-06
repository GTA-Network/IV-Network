//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CCheckpointEntity.cpp
// Project: Client.Core
// Author: Knight
// License: See LICENSE in root directory
//
//==============================================================================

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
	// Are we not visible?
	if (!m_bIsVisible)
		return;

	CVector3 vecPosition;
	g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPosition);

	CVector3 vecDistance((m_vecPosition.fX - vecPosition.fX), (m_vecPosition.fY - vecPosition.fY), (m_vecPosition.fZ - vecPosition.fZ));

	// The actual radius of a checkpoint is bigger than its visible entity so we'll add a factor of 5.0
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