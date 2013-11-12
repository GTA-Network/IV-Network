//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CCheckpointEntity.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CCheckpointEntity.h"
#include <CServer.h>

CCheckpointEntity::CCheckpointEntity()
{
}

CCheckpointEntity::~CCheckpointEntity()
{

}



void CScriptCheckpoint::ShowForPlayer(EntityId playerId)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_SHOW), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, false);
}

void CScriptCheckpoint::ShowForAll()
{
	GetEntity()->SetVisible(true);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_SHOW), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptCheckpoint::HideForPlayer(EntityId playerId)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_HIDE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, false);
}

void CScriptCheckpoint::HideForAll()
{
	GetEntity()->SetVisible(false);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_HIDE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptCheckpoint::SetPosition(float fX, float fY, float fZ)
{
	GetEntity()->SetPosition(CVector3(fX, fY, fZ));
	CScriptEntity::SetPosition(fX, fY, fZ);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_SET_POSITION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptCheckpoint::SetTargetPosition(float fX, float fY, float fZ)
{
	GetEntity()->SetTargetPosition(CVector3(fX, fY, fZ));

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_SET_TARGET_POSITION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptCheckpoint::SetType(int iType)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iType);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_SET_TYPE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptCheckpoint::SetRadius(float fRadius)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(fRadius);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CHECKPOINT_SET_RADIUS), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}