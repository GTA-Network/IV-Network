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

	return nullptr;
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
