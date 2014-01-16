/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CBlipEntity.h"
#include <CServer.h>

CBlipEntity::CBlipEntity()
{
	m_bVisible = true;
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

void CScriptBlip::SetIcon(unsigned int iIcon)
{
	GetEntity()->SetIcon(iIcon);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iIcon);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_ICON), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetColor(unsigned int uiColor)
{
	GetEntity()->SetColor(uiColor);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(uiColor);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_COLOR), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetSize(float fSize)
{
	GetEntity()->SetSize(fSize);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(fSize);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_SIZE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetRange(bool bRange)
{
	GetEntity()->SetRange(bRange);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(bRange);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_RANGE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetVisible(bool bVisible)
{
	GetEntity()->SetVisible(bVisible);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(bVisible);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_VISIBLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptBlip::SetName(CString sName)
{
	GetEntity()->SetName(sName);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(RakNet::RakString(sName.C_String()));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_BLIP_SET_NAME), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}