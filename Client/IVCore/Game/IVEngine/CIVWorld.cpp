//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVWorld.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVWorld.h"
#include <Game/COffsets.h>

void CIVWorld::AddEntity( CIVEntity * pEntity )
{
	IVEntity * pGameEntity = pEntity->GetEntity();

	_asm	push 0;
	_asm	push pGameEntity;
	_asm	call COffsets::FUNC_CWorld__AddEntity;
	_asm	add esp, 8;
}

void CIVWorld::RemoveEntity( CIVEntity * pEntity )
{
	IVEntity * pGameEntity = pEntity->GetEntity();

	_asm	push 0;
	_asm	push pGameEntity;
	_asm	call COffsets::FUNC_CWorld__RemoveEntity;
	_asm	add esp, 8;
}