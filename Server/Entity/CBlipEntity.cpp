//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CBlipEntity.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CBlipEntity.h"
#include <CServer.h>

CBlipEntity::CBlipEntity()
{

}

CBlipEntity::~CBlipEntity()
{

}

void CScriptBlip::SetPosition(float fX, float fY, float fZ)
{
	GetEntity()->SetPosition(CVector3(fX, fY, fZ));
	CScriptEntity::SetPosition(fX, fY, fZ);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_POSITION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetIcon(int iIcon)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iIcon);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_ICON), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetColor(unsigned int uiColor)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(uiColor);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_COLOR), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetSize(float fSize)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(fSize);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_SIZE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetRange(bool bRange)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(bRange);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_RANGE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetVisible(bool bVisible)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(bVisible);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_VISIBLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetName(CString sName)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(RakNet::RakString(sName.C_String()));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_NAME), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}