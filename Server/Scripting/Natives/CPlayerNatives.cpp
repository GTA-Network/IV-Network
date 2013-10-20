//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPlayerNatives.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CServer.h"
#include "CPlayerNatives.h"
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include <CLogFile.h>

void CPlayerNatives::Register(CScriptVM * pVM)
{
	pVM->RegisterFunction("isPlayerConnected", IsConnected, 1, "i");
	pVM->RegisterFunction("getPlayerName", GetName, 1, "i");
	pVM->RegisterFunction("setPlayerName", SetName, 2, "is");
}

int CPlayerNatives::IsConnected(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	int playerId;
	pVM->Pop(playerId);

	pVM->Push(CServer::GetInstance()->GetPlayerManager()->DoesExists((EntityId)playerId));

	return 1;
}

int CPlayerNatives::GetName(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	int playerId;
	pVM->Pop(playerId);

	auto pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt((EntityId)playerId);

	if (pPlayer) {
		pVM->Push(pPlayer->GetName());
	}
	else {
		pVM->Push(false);
	}

	return 1;
}

int CPlayerNatives::SetName(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	int playerId;
	pVM->Pop(playerId);

	CString pName;
	pVM->Pop(pName);

	auto pPlayer = CServer::GetInstance()->GetPlayerManager()->GetAt((EntityId)playerId);

	if (pPlayer) {
		pVM->Push(pPlayer->SetName(pName));
	}
	else {
		pVM->Push(false);
	}
	return 1;
}

int CPlayerNatives::GetArmour(int * VM)
{

	return 1;
}

int CPlayerNatives::SetArmour(int * VM)
{

	return 1;
}


int CPlayerNatives::GetClothes(int * VM)
{

	return 1;
}

int CPlayerNatives::SetClothes(int * VM)
{

	return 1;
}


int CPlayerNatives::GetColor(int * VM)
{

	return 1;
}

int CPlayerNatives::SetColor(int * VM)
{

	return 1;
}


int CPlayerNatives::GetDimension(int * VM)
{

	return 1;
}

int CPlayerNatives::SetDimension(int * VM)
{

	return 1;
}


int CPlayerNatives::GetHeading(int * VM)
{

	return 1;
}

int CPlayerNatives::SetHeading(int * VM)
{

	return 1;
}


int CPlayerNatives::GetHealth(int * VM)
{

	return 1;
}

int CPlayerNatives::SetHealth(int * VM)
{

	return 1;
}


int CPlayerNatives::GetModel(int * VM)
{
	
	return 1;
}

int CPlayerNatives::SetModel(int * VM)
{

	return 1;
}