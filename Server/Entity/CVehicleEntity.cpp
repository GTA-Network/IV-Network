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

CVehicleEntity::CVehicleEntity() :
	m_pScriptVehicle(nullptr), m_Matrix(Matrix()), m_fHealth(100),
	m_fPetrolHealth(100.0f), m_fSteeringAngle(0.0f), m_bEngineState(false),
	m_iLockedState(0), m_iDirtLevel(0), m_fHeading(0.0f),
	m_iModelId(0)
{

}

CVehicleEntity::~CVehicleEntity()
{

}

void CScriptVehicle::SetPosition(float fX, float fY, float fZ)
{
	GetEntity()->SetPosition(CVector3(fX, fY, fZ));

	CScriptEntity::SetPosition(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_POSITION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptVehicle::SetRotation(float fX, float fY, float fZ)
{
	GetEntity()->SetRotation(CVector3(fX, fY, fZ));

	CScriptEntity::SetRotation(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_ROTATION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptVehicle::SetMoveSpeed(float fX, float fY, float fZ)
{
	GetEntity()->SetMoveSpeed(CVector3(fX, fY, fZ));

	CScriptEntity::SetMoveSpeed(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_MOVE_SPEED), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptVehicle::SetTurnSpeed(float fX, float fY, float fZ)
{
	GetEntity()->SetTurnSpeed(CVector3(fX, fY, fZ));

	CScriptEntity::SetTurnSpeed(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_TURN_SPEED), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptVehicle::SetHealth(float fHealth)
{
	GetEntity()->SetHealth(fHealth);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(fHealth);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_HEALTH), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptVehicle::SetLocked(int iLocked)
{
	GetEntity()->SetLockedState(iLocked);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iLocked);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_LOCKED), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptVehicle::SetEngine(bool bEngineState)
{
	GetEntity()->SetEngineState(bEngineState);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(bEngineState);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_ENGINE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptVehicle::SetDirtLevel(int iDirtLevel)
{
	GetEntity()->SetDirtLevel(iDirtLevel);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iDirtLevel);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_VEHICLE_SET_DIRT_LEVEL), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}
