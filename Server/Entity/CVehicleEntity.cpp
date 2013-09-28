//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
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