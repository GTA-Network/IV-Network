//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CVehicleEntity.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CVehicleEntity.h"


CVehicleEntity::CVehicleEntity() : 
	CNetworkEntity()
{
}

CVehicleEntity::~CVehicleEntity()
{

}

bool CVehicleEntity::Create()
{
	//
	return true;
}

bool CVehicleEntity::Destroy()
{
	//
	return true;
}
void CVehicleEntity::GetPosition(CVector3& vecPos)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerPosition(vecPos);
	// else
	CNetworkEntity::GetPosition(vecPos);
}

void CVehicleEntity::SetPosition(const CVector3& vecPos)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerPosition(vecPos);
	CNetworkEntity::SetPosition(vecPos);
}


void CVehicleEntity::GetRotation(CVector3& vecRot)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerRotation(vecRot);
	// else
	CNetworkEntity::GetRotation(vecRot);
}

void CVehicleEntity::SetRotation(const CVector3& vecRot)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerRotation(vecRot);
	CNetworkEntity::SetRotation(vecRot);
}

void CVehicleEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerMoveSpeed(vecMoveSpeed);
	// else
	CNetworkEntity::GetMoveSpeed(vecMoveSpeed);
}

void CVehicleEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerMoveSpeed(vecMoveSpeed);
	CNetworkEntity::SetMoveSpeed(vecMoveSpeed);
}

void CVehicleEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerTurnSpeed(vecTurnSpeed);
	// else
	CNetworkEntity::GetTurnSpeed(vecTurnSpeed);
}

void CVehicleEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerTurnSpeed(vecTurnSpeed);
	CNetworkEntity::SetTurnSpeed(vecTurnSpeed);
}