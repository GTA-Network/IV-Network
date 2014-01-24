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

#include "CEntity.h"
#include <Game/COffsets.h>
#include "CWorld.h"

_GAME_BEGIN

CEntity::CEntity() :
	m_pEntity(nullptr)
{
}

CEntity::CEntity(IEntity * pEntity) :
	m_pEntity(pEntity)
{
}

CEntity::~CEntity()
{
}

void CEntity::SetEntity(IEntity * pEntity)
{
	m_pEntity = pEntity;
}

IEntity * CEntity::GetEntity()
{
	return m_pEntity;
}

void CEntity::SetMatrix(const Matrix& matMatrix)
{
	if(m_pEntity && m_pEntity->m_pMatrix) 
	{
		memcpy(&m_pEntity->m_pMatrix->vecRight, &matMatrix.vecRight, sizeof(CVector3));
		memcpy(&m_pEntity->m_pMatrix->vecForward, &matMatrix.vecForward, sizeof(CVector3));
		memcpy(&m_pEntity->m_pMatrix->vecUp, &matMatrix.vecUp, sizeof(CVector3));
		memcpy(&m_pEntity->m_pMatrix->vecPosition, &matMatrix.vecPosition, sizeof(CVector3));
	}
}

void CEntity::GetMatrix(Matrix& matMatrix)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
	{
		memcpy(&matMatrix.vecRight, &m_pEntity->m_pMatrix->vecRight, sizeof(CVector3));
		memcpy(&matMatrix.vecForward, &m_pEntity->m_pMatrix->vecForward, sizeof(CVector3));
		memcpy(&matMatrix.vecUp, &m_pEntity->m_pMatrix->vecUp, sizeof(CVector3));
		memcpy(&matMatrix.vecPosition, &m_pEntity->m_pMatrix->vecPosition, sizeof(CVector3));
	}
}

void CEntity::SetPosition(const CVector3& vecPosition)
{
	if(m_pEntity) 
	{
		if(m_pEntity->m_pMatrix)
			memcpy(&m_pEntity->m_pMatrix->vecPosition, &vecPosition, sizeof(CVector3));
		else
			memcpy(&m_pEntity->m_vecPosition, &vecPosition, sizeof(CVector3));

	}
}

unsigned long lastLoaded = 0;

void CEntity::GetPosition(CVector3& vecPosition)
{
	if(m_pEntity)
	{
		if(m_pEntity->m_pMatrix)
			memcpy(&vecPosition, &m_pEntity->m_pMatrix->vecPosition, sizeof(CVector3));
		else
			memcpy(&vecPosition, &m_pEntity->m_vecPosition, sizeof(CVector3));
	}
}

void CEntity::SetHeading(float fHeading)
{
	if(m_pEntity)   
		m_pEntity->SetHeading(fHeading);
}       

void CEntity::SetRoll(const CVector3& vecRoll)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&m_pEntity->m_pMatrix->vecRight, &vecRoll, sizeof(CVector3));
}

void CEntity::GetRoll(CVector3& vecRoll)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&vecRoll, &m_pEntity->m_pMatrix->vecRight, sizeof(CVector3));
}

void CEntity::SetDirection(const CVector3& vecDirection)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&m_pEntity->m_pMatrix->vecForward, &vecDirection, sizeof(CVector3));
}

void CEntity::GetDirection(CVector3& vecDirection)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&vecDirection, &m_pEntity->m_pMatrix->vecForward, sizeof(CVector3));
}

void CEntity::SetModelIndex(WORD wModelIndex)
{
	if(m_pEntity)
		m_pEntity->SetModelIndex(wModelIndex);
}

WORD CEntity::GetModelIndex()
{
	if(m_pEntity)
		return m_pEntity->m_wModelIndex;

	return 0;
}

void CEntity::SetAlpha(BYTE byteAlpha)
{
	if(m_pEntity)
		m_pEntity->m_byteAlpha = byteAlpha;
}

BYTE CEntity::GetAlpha()
{
	if(m_pEntity)
		return m_pEntity->m_byteAlpha;

	return 0;
}

void  CEntity::AddToWorld()
{
	if(m_pEntity)
		CWorld::AddEntity(this);
}

void CEntity::RemoveFromWorld()
{
	if(m_pEntity)
		CWorld::RemoveEntity(this);
}

_GAME_END