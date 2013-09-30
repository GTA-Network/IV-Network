//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkEntity.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkEntity.h"
#include <Network/CBitStream.h>
#include <CLogFile.h>

CNetworkEntity::CNetworkEntity()
	: m_vecPosition(CVector3()),
	m_vecRotation(CVector3()),
	m_vecMoveSpeed(CVector3()),
	m_vecTurnSpeed(CVector3()),
	m_entityId(INVALID_ENTITY),
	m_eType(UNKNOWN_ENTITY)
{

}

CNetworkEntity::~CNetworkEntity()
{

}

void CNetworkEntity::GetPosition(CVector3& vecPos)
{
	vecPos = m_vecPosition;
}

void CNetworkEntity::SetPosition(const CVector3& vecPos)
{
	m_vecPosition = vecPos;
}

void CNetworkEntity::GetRotation(CVector3& vecRot)
{
	vecRot = m_vecRotation;
}

void CNetworkEntity::SetRotation(const CVector3& vecRot)
{
	m_vecRotation = vecRot;
}

void CNetworkEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	vecMoveSpeed = m_vecMoveSpeed;
}

void CNetworkEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	m_vecMoveSpeed = vecMoveSpeed;
}

void CNetworkEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	vecTurnSpeed = m_vecTurnSpeed;
}

void CNetworkEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	m_vecTurnSpeed = vecTurnSpeed;
}

bool CNetworkEntity::IsMoving()
{
	if(!(m_vecMoveSpeed.fX == 0 && m_vecMoveSpeed.fY == 0 && (m_vecMoveSpeed.fZ >= -0.000020 && m_vecMoveSpeed.fZ <= 0.000020)))
		return true;

	return false;
}

void CNetworkEntity::StopMoving()
{
	m_vecMoveSpeed = CVector3();
}

void CNetworkEntity::Serialize(RakNet::BitStream * bitStream, ePackageType pType)
{
	// Create Sync package here and send it to the server
	CBitStream * pBitStream = new CBitStream();
	pBitStream->Write0();
}

void CNetworkEntity::Deserialize(RakNet::BitStream * bitStream, ePackageType pType)
{
	// Get Sync package here and recieve it to the server
	CBitStream * pBitStream = new CBitStream();
	pBitStream->Write0();
}