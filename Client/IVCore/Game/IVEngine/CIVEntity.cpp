//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVEntity.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVEntity.h"
#include <Game/COffsets.h>
#include "CIVWorld.h"

CIVEntity::CIVEntity() :
	m_pEntity(NULL)
{
}

CIVEntity::CIVEntity(IVEntity * pEntity) :
	m_pEntity(pEntity)
{
}

CIVEntity::~CIVEntity()
{
}

void CIVEntity::SetEntity(IVEntity * pEntity)
{
	m_pEntity = pEntity;
}

IVEntity * CIVEntity::GetEntity()
{
	return m_pEntity;
}

void CIVEntity::SetMatrix(const Matrix& matMatrix)
{
	if(m_pEntity && m_pEntity->m_pMatrix) 
	{
		memcpy(&m_pEntity->m_pMatrix->vecRight, &matMatrix.vecRight, sizeof(CVector3));
		memcpy(&m_pEntity->m_pMatrix->vecForward, &matMatrix.vecForward, sizeof(CVector3));
		memcpy(&m_pEntity->m_pMatrix->vecUp, &matMatrix.vecUp, sizeof(CVector3));
		memcpy(&m_pEntity->m_pMatrix->vecPosition, &matMatrix.vecPosition, sizeof(CVector3));
	}
}

void CIVEntity::GetMatrix(Matrix& matMatrix)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
	{
		memcpy(&matMatrix.vecRight, &m_pEntity->m_pMatrix->vecRight, sizeof(CVector3));
		memcpy(&matMatrix.vecForward, &m_pEntity->m_pMatrix->vecForward, sizeof(CVector3));
		memcpy(&matMatrix.vecUp, &m_pEntity->m_pMatrix->vecUp, sizeof(CVector3));
		memcpy(&matMatrix.vecPosition, &m_pEntity->m_pMatrix->vecPosition, sizeof(CVector3));
	}
}

void CIVEntity::SetPosition(const CVector3& vecPosition)
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

void CIVEntity::GetPosition(CVector3& vecPosition)
{
	if(m_pEntity)
	{
		if(m_pEntity->m_pMatrix)
			memcpy(&vecPosition, &m_pEntity->m_pMatrix->vecPosition, sizeof(CVector3));
		else
			memcpy(&vecPosition, &m_pEntity->m_vecPosition, sizeof(CVector3));
	}
}

void CIVEntity::SetHeading(float fHeading)
{
	if(m_pEntity)   
		m_pEntity->SetHeading(fHeading);
}       

void CIVEntity::SetRoll(const CVector3& vecRoll)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&m_pEntity->m_pMatrix->vecRight, &vecRoll, sizeof(CVector3));
}

void CIVEntity::GetRoll(CVector3& vecRoll)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&vecRoll, &m_pEntity->m_pMatrix->vecRight, sizeof(CVector3));
}

void CIVEntity::SetDirection(const CVector3& vecDirection)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&m_pEntity->m_pMatrix->vecForward, &vecDirection, sizeof(CVector3));
}

void CIVEntity::GetDirection(CVector3& vecDirection)
{
	if(m_pEntity && m_pEntity->m_pMatrix)
		memcpy(&vecDirection, &m_pEntity->m_pMatrix->vecForward, sizeof(CVector3));
}

void CIVEntity::SetModelIndex(WORD wModelIndex)
{
	if(m_pEntity)
		m_pEntity->SetModelIndex(wModelIndex);
}

WORD CIVEntity::GetModelIndex()
{
	if(m_pEntity)
		return m_pEntity->m_wModelIndex;

	return 0;
}

void CIVEntity::SetAlpha(BYTE byteAlpha)
{
	if(m_pEntity)
		m_pEntity->m_byteAlpha = byteAlpha;
}

BYTE CIVEntity::GetAlpha()
{
	if(m_pEntity)
		return m_pEntity->m_byteAlpha;

	return 0;
}

void  CIVEntity::AddToWorld()
{
	if(m_pEntity)
		CIVWorld::AddEntity(this);
}

void CIVEntity::RemoveFromWorld()
{
	if(m_pEntity)
		CIVWorld::RemoveEntity(this);
}
