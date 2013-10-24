//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPhysical.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPhysical.h"
#include <Game/COffsets.h>

CIVPhysical::CIVPhysical() :
	CIVDynamicEntity()
{

}

CIVPhysical::CIVPhysical(IVPhysical * pPhysical) :
	CIVDynamicEntity(pPhysical)
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
	if (GetEntity())
	{
		((void(__thiscall *) (IVPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__SetMoveSpeed))((IVPhysical *) GetEntity(), &vecMoveSpeed);
	}
}

void CIVPhysical::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IVPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__GetMoveSpeed))((IVPhysical *) GetEntity(), &vecMoveSpeed);
	}
}

void CIVPhysical::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IVPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__SetTurnSpeed))((IVPhysical *) GetEntity(), &vecTurnSpeed);
	}
}

void CIVPhysical::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IVPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__GetTurnSpeed))((IVPhysical *) GetEntity(), &vecTurnSpeed);
	}
}

void CIVPhysical::SetLastDamageEntity(IVEntity * pLastDamageEntity)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IVPhysical *, IVEntity *))(COffsets::FUNC_CPhysical__GetTurnSpeed))((IVPhysical *) GetEntity(), pLastDamageEntity);
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
	IVPhysical * pPhysical = (IVPhysical *) GetEntity();

	if (pPhysical)
		pPhysical->m_fHealth = fHealth;
}

float CIVPhysical::GetHealth()
{
	IVPhysical * pPhysical = (IVPhysical *)GetEntity();

	if(pPhysical)
		return pPhysical->GetHealth();

	return 0.0;
}
