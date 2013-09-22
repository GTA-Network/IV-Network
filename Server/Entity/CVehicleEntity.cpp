//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CVehicleEntity.cpp
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CVehicleEntity.h"


#include <CServer.h>

CVehicleEntity::CVehicleEntity()
{
	// Add the vehicle to the vehicle manager and set its id
	SetId(CServer::GetInstance()->GetVehicleManager()->Add(this));
}

CVehicleEntity::~CVehicleEntity()
{

}