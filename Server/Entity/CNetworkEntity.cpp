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