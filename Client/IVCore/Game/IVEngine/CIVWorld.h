//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVWorld.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVWorld_h
#define CIVWorld_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVEntity.h"

class CIVWorld {
public:
	static	void		AddEntity(CIVEntity * pEntity);
	static	void		RemoveEntity(CIVEntity * pEntity);
};

#endif // CIVWorld_h