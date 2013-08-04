//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
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
	_asm
	{
		push 0
		push pGameEntity
		call COffsets::FUNC_CWorld__AddEntity
		add esp, 8
	}
}

void CIVWorld::RemoveEntity( CIVEntity * pEntity )
{
	IVEntity * pGameEntity = pEntity->GetEntity();
	_asm
	{
		push 0
		push pGameEntity
		call COffsets::FUNC_CWorld__RemoveEntity
		add esp, 8
	}
}