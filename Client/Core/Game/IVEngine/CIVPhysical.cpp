//========== IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ==========
//
// File: CIVPhysical.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPhysical.h"
#include <Game/COffsets.h>

CIVPhysical::CIVPhysical( ) : CIVDynamicEntity( )
{

}

CIVPhysical::CIVPhysical( IVPhysical * pPhysical ) : CIVDynamicEntity( pPhysical )
{

}

CIVPhysical::~CIVPhysical( )
{

}

void CIVPhysical::SetPhysical( IVPhysical * pPhysical )
{
	SetDynamicEntity( pPhysical );
}

IVPhysical * CIVPhysical::GetPhysical( )
{
	return (IVPhysical *)GetDynamicEntity( );
}

void CIVPhysical::SetMoveSpeed( CVector3 vecMoveSpeed )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );

	if( pPhysical )
	{
		const CVector3 * pMoveSpeed = &vecMoveSpeed;
		_asm
		{
			push pMoveSpeed
			mov ecx, pPhysical
			call COffsets::FUNC_CPhysical__SetMoveSpeed
		}
	}
}

void CIVPhysical::GetMoveSpeed( CVector3 * vecMoveSpeed )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );

	if( pPhysical )
	{
		CVector3 * pMoveSpeed = vecMoveSpeed;
		_asm
		{
			push pMoveSpeed
			mov ecx, pPhysical
			call COffsets::FUNC_CPhysical__GetMoveSpeed
		}
	}
}

void CIVPhysical::SetTurnSpeed( CVector3 vecTurnSpeed )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );

	if( pPhysical )
	{
		CVector3* pTurnSpeed = &vecTurnSpeed;
		_asm
		{
			push pTurnSpeed
			mov ecx, pPhysical
			call COffsets::FUNC_CPhysical__SetTurnSpeed
		}
	}
}

void CIVPhysical::GetTurnSpeed( CVector3 * vecTurnSpeed )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );

	if( pPhysical )
	{
		CVector3 * pTurnSpeed = vecTurnSpeed;
		_asm
		{
			push pTurnSpeed
			mov ecx, pPhysical
			call COffsets::FUNC_CPhysical__GetTurnSpeed
		}
	}
}

void CIVPhysical::SetLastDamageEntity( IVEntity * pLastDamageEntity )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );

	if( pPhysical )
		pPhysical->m_pLastDamageEntity = pLastDamageEntity;
}

IVEntity * CIVPhysical::GetLastDamageEntity( )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );

	if( pPhysical )
		return pPhysical->m_pLastDamageEntity;

	return NULL;
}

void CIVPhysical::SetHealth( float fHealth )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );

	if( pPhysical )
	{
		DWORD dwFunc = ((IVPhysicalVFTable *)pPhysical->m_VFTable)->SetHealth;

		_asm
		{
			push 1
			push fHealth
			mov ecx, pPhysical
			call dwFunc
		}
	}
}

float CIVPhysical::GetHealth( )
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity( );
	float fHealth = 0.0f;

	if( pPhysical )
	{
		DWORD dwFunc = ((IVPhysicalVFTable *)pPhysical->m_VFTable)->GetHealth;

		_asm
		{
			mov ecx, pPhysical
			call dwFunc
			mov fHealth, eax
		}
	}
	
	return fHealth;
}