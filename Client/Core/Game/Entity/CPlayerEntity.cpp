//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CPlayerEntity.cpp
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CPlayerEntity.h"


void CPlayerEntity::GetPosition(CVector3& vecPos)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerPosition(vecPos);
	// else
	CNetworkEntity::GetPosition(vecPos);
}

void CPlayerEntity::SetPosition(const CVector3& vecPos)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerPosition(vecPos);
	CNetworkEntity::SetPosition(vecPos);
}


void CPlayerEntity::GetRotation(CVector3& vecRot)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerRotation(vecRot);
	// else
	CNetworkEntity::GetRotation(vecRot);
}

void CPlayerEntity::SetRotation(const CVector3& vecRot)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerRotation(vecRot);
	CNetworkEntity::SetRotation(vecRot);
}

void CPlayerEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerMoveSpeed(vecMoveSpeed);
	// else
	CNetworkEntity::GetMoveSpeed(vecMoveSpeed);
}

void CPlayerEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerMoveSpeed(vecMoveSpeed);
	CNetworkEntity::SetMoveSpeed(vecMoveSpeed);
}

void CPlayerEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		GetPlayerTurnSpeed(vecTurnSpeed);
	// else
	CNetworkEntity::GetTurnSpeed(vecTurnSpeed);
}

void CPlayerEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	// Check if player is spawned
	// if(IsSpawned())
	//		SetPlayerTurnSpeed(vecTurnSpeed);
	CNetworkEntity::SetTurnSpeed(vecTurnSpeed);
}