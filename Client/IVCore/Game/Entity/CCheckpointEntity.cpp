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
	m_bIsVisible(true)
{
	CNetworkEntity::SetType(CHECKPOINT_ENTITY);
}

CCheckpointEntity::~CCheckpointEntity()
{

}

unsigned int CCheckpointEntity::GetCheckpoint()
{
	return 0;
}

void CCheckpointEntity::Show()
{
	CIVScript::CreateCheckpoint(m_eType, m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ, m_vecTargetPosition.fX, m_vecTargetPosition.fY, m_vecTargetPosition.fZ, 1.0);
}

void CCheckpointEntity::Hide()
{
	m_bIsVisible = false;
}

bool CCheckpointEntity::IsVisible()
{
	return m_bIsVisible;
}

void CCheckpointEntity::SetType(CIVScript::eCheckpointType type)
{
	m_eType = type;
}

CIVScript::eCheckpointType CCheckpointEntity::GetType()
{
	return m_eType;
}

void CCheckpointEntity::SetPosition(const CVector3& vecPosition)
{
	m_vecPosition = vecPosition;
}

void CCheckpointEntity::GetPosition(CVector3& vecPosition)
{
	vecPosition = m_vecPosition;
}

void CCheckpointEntity::SetTargetPosition(const CVector3& vecTargetPosition)
{
	m_vecTargetPosition = vecTargetPosition;
}

void CCheckpointEntity::GetTargetPosition(CVector3& vecTargetPosition)
{
	vecTargetPosition = m_vecTargetPosition;
}

void CCheckpointEntity::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
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
	/*		CBitStream  bsSend;
			bsSend.Write(m_checkpointId);
			g_pCore->GetNetworkManager()->RPC(RPC_CheckpointEntered, &bsSend, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED);*/
			m_bInCheckpoint = true;
		}
	}
	else
	{
		if (m_bInCheckpoint)
		{
			//CBitStream  bsSend;
			//bsSend.Write(m_checkpointId);
			//g_pCore->GetNetworkManager()->RPC(RPC_CheckpointLeft, &bsSend, PRIORITY_HIGH, RELIABILITY_RELIABLE_ORDERED);
			m_bInCheckpoint = false;
		}
	}
}