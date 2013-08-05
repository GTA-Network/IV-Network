//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
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

CIVEntity::CIVEntity( )
{
	// Set the entity
	SetEntity( NULL );
}

CIVEntity::CIVEntity( IVEntity * pEntity )
{
	// Set the entity
	SetEntity( pEntity );
}

CIVEntity::~CIVEntity( )
{

}

void CIVEntity::SetMatrix( Matrix matMatrix )
{
	if( m_pEntity && m_pEntity->m_pMatrix )
	{
		memcpy( &m_pEntity->m_pMatrix->vecRight, &matMatrix.vecRight, sizeof(CVector3) );
		memcpy( &m_pEntity->m_pMatrix->vecForward, &matMatrix.vecForward, sizeof(CVector3) );
		memcpy( &m_pEntity->m_pMatrix->vecUp, &matMatrix.vecUp, sizeof(CVector3) );
		memcpy( &m_pEntity->m_pMatrix->vecPosition, &matMatrix.vecPosition, sizeof(CVector3) );
	}
}

void CIVEntity::GetMatrix( Matrix * matMatrix )
{
	if( m_pEntity && m_pEntity->m_pMatrix )
	{
		memcpy( &matMatrix->vecRight, &m_pEntity->m_pMatrix->vecRight, sizeof(CVector3) );
		memcpy( &matMatrix->vecForward, &m_pEntity->m_pMatrix->vecForward, sizeof(CVector3) );
		memcpy( &matMatrix->vecUp, &m_pEntity->m_pMatrix->vecUp, sizeof(CVector3) );
		memcpy( &matMatrix->vecPosition, &m_pEntity->m_pMatrix->vecPosition, sizeof(CVector3) );
	}
}

void CIVEntity::SetPosition( CVector3 vecPosition )
{
	if( m_pEntity )
	{
		if( m_pEntity->m_pMatrix )
			memcpy( &m_pEntity->m_pMatrix->vecPosition, &vecPosition, sizeof(CVector3) );
		else
			memcpy( &m_pEntity->m_vecPosition, &vecPosition, sizeof(CVector3) );
	}
}

void CIVEntity::GetPosition( CVector3 * vecPosition )
{
	if( m_pEntity )
	{
		if( m_pEntity->m_pMatrix )
			memcpy( vecPosition, &m_pEntity->m_pMatrix->vecPosition, sizeof(CVector3) );
		else
			memcpy( vecPosition, &m_pEntity->m_vecPosition, sizeof(CVector3) );
	}
}

void CIVEntity::SetRoll( CVector3 vecRoll )
{
	if( m_pEntity && m_pEntity->m_pMatrix )
		memcpy( &m_pEntity->m_pMatrix->vecRight, &vecRoll, sizeof(CVector3) );
}

void CIVEntity::GetRoll( CVector3 * vecRoll )
{
	if( m_pEntity && m_pEntity->m_pMatrix )
		memcpy( vecRoll, &m_pEntity->m_pMatrix->vecRight, sizeof(CVector3) );
}

void CIVEntity::SetDirection( CVector3 vecDirection )
{
	if( m_pEntity && m_pEntity->m_pMatrix )
		memcpy( &m_pEntity->m_pMatrix->vecForward, &vecDirection, sizeof(CVector3) );
}

void CIVEntity::GetDirection( CVector3 * vecDirection )
{
	if( m_pEntity && m_pEntity->m_pMatrix )
		memcpy( vecDirection, &m_pEntity->m_pMatrix->vecForward, sizeof(CVector3) );
}

void CIVEntity::SetModelIndex( WORD wModelIndex )
{
	if( m_pEntity )
	{
		DWORD dwFunc = m_pEntity->m_VFTable->SetModelIndex;
		int iModelIndex = wModelIndex;
		_asm
		{
			push iModelIndex
			call dwFunc
			add esp, 4
		}
	}
}

WORD CIVEntity::GetModelIndex( )
{
	if( m_pEntity )
		return m_pEntity->m_wModelIndex;

	return 0;
}

void CIVEntity::SetAlpha( BYTE byteAlpha )
{
	if( m_pEntity )
		m_pEntity->m_byteAlpha = byteAlpha;
}

BYTE CIVEntity::GetAlpha( )
{
	if( m_pEntity )
		return m_pEntity->m_byteAlpha;

	return 0;
}

bool CIVEntity::IsTouchingEntity( CIVEntity * pTouchingEntity )
{
	if( m_pEntity )
	{
		IVEntity * pGameEntity = m_pEntity;
		IVEntity * pTouchingGameEntity = pTouchingEntity->GetEntity();
		bool bResult = false;

		_asm
		{
			push pTouchingGameEntity
			push pGameEntity
			call COffsets::FUNC_CEntity__IsTouchingEntity
			mov bResult, al
		}

		return bResult;
	}

	return false;
}

void CIVEntity::AddToWorld( )
{
	if( m_pEntity )
		CIVWorld::AddEntity( this );
}

void CIVEntity::RemoveFromWorld( )
{
	if( m_pEntity )
		CIVWorld::RemoveEntity( this );
}