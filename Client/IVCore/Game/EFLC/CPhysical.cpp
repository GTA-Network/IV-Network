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

#include "CPhysical.h"
#include <Game/COffsets.h>

_GAME_BEGIN

CPhysical::CPhysical() :
	CDynamicEntity()
{

}

CPhysical::CPhysical(IPhysical * pPhysical) :
	CDynamicEntity(pPhysical)
{

}

CPhysical::~CPhysical()
{

}

void CPhysical::SetPhysical(IPhysical * pPhysical)
{
	SetDynamicEntity(pPhysical);
}

IPhysical * CPhysical::GetPhysical()
{
	return (IPhysical *)GetDynamicEntity();
}

void CPhysical::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__SetMoveSpeed))((IPhysical *) GetEntity(), &vecMoveSpeed);
	}
}

void CPhysical::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__GetMoveSpeed))((IPhysical *) GetEntity(), &vecMoveSpeed);
	}
}

void CPhysical::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__SetTurnSpeed))((IPhysical *) GetEntity(), &vecTurnSpeed);
	}
}

void CPhysical::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IPhysical *, const CVector3 *))(COffsets::FUNC_CPhysical__GetTurnSpeed))((IPhysical *) GetEntity(), &vecTurnSpeed);
	}
}

void CPhysical::SetLastDamageEntity(IEntity * pLastDamageEntity)
{
	if (GetEntity())
	{
		((void(__thiscall *) (IPhysical *, IEntity *))(COffsets::FUNC_CPhysical__GetTurnSpeed))((IPhysical *) GetEntity(), pLastDamageEntity);
	}
}

IEntity * CPhysical::GetLastDamageEntity()
{
	IPhysical * pPhysical = (IPhysical *)GetEntity();

	if(pPhysical)
		return pPhysical->m_pLastDamageEntity;

	return nullptr;
}

void CPhysical::SetHealth(float fHealth)
{
	IPhysical * pPhysical = (IPhysical *) GetEntity();

	if (pPhysical)
		pPhysical->m_fHealth = fHealth;
}

float CPhysical::GetHealth()
{
	IPhysical * pPhysical = (IPhysical *)GetEntity();

	if(pPhysical)
		return pPhysical->GetHealth();

	return 0.0;
}

_GAME_END