//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
//
// File: CIVPhysical.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPhysical.h"
#include <Game/COffsets.h>

CIVPhysical::CIVPhysical() : CIVDynamicEntity()
{

}

CIVPhysical::CIVPhysical(IVPhysical * pPhysical) : CIVDynamicEntity(pPhysical)
{

}

CIVPhysical::~CIVPhysical()
{

}

void CIVPhysical::SetPhysical(IVPhysical * pPhysical)
{
	SetDynamicEntity(pPhysical);
}

IVPhysical * CIVPhysical::GetPhysical()
{
	return (IVPhysical *)GetDynamicEntity();
}

void CIVPhysical::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		const CVector3 * pVecMoveSpeed = &vecMoveSpeed;
		_asm
		{
			push pVecMoveSpeed
				mov ecx, pPhysical
				call COffsets::FUNC_CPhysical__SetMoveSpeed
		}
	}
}

void CIVPhysical::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		CVector3 * pVecMoveSpeed = &vecMoveSpeed;
		_asm
		{
			push pVecMoveSpeed
				mov ecx, pPhysical
				call COffsets::FUNC_CPhysical__GetMoveSpeed
		}
	}
}

void CIVPhysical::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		const CVector3 * pVecTurnSpeed = &vecTurnSpeed;
		_asm
		{
			push pVecTurnSpeed
				mov ecx, pPhysical
				call COffsets::FUNC_CPhysical__SetTurnSpeed
		}
	}
}

void CIVPhysical::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		CVector3 * pVecTurnSpeed = &vecTurnSpeed;
		_asm
		{
			push pVecTurnSpeed
				mov ecx, pPhysical
				call COffsets::FUNC_CPhysical__GetTurnSpeed
		}
	}
}

void CIVPhysical::SetLastDamageEntity(IVEntity * pLastDamageEntity)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		IVEntity * _pLastDamageEntity = pLastDamageEntity;
		_asm
		{
			push _pLastDamageEntity
				mov ecx, pPhysical
				call COffsets::FUNC_CPhysical__SetLastDamageEntity
		}
	}
}

IVEntity * CIVPhysical::GetLastDamageEntity()
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
		return pPhysical->m_pLastDamageEntity;

	return NULL;
}

void CIVPhysical::SetHealth(float fHealth)
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
	{
		pPhysical->SetHealth(fHealth, 1);
	}
}

float CIVPhysical::GetHealth()
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
		return pPhysical->GetHealth();

	return 0.0;
}
