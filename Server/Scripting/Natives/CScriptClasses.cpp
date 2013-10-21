//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CScriptClasses.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptClasses.h"
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include "../../../Server/Scripting/Natives/Natives_Server.h"
#include "Entity/Entities.h"
#include <CServer.h>
#include <Scripting/CScriptClass.h>

int CreateVehicle(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	int vehicleModel;
	pVM->Pop(vehicleModel);
	
	CVector3 vecPosition;
	pVM->Pop(vecPosition);

#if 0
	unsigned int color1;
	pVM->Pop(color1)

		unsigned int color2;
	pVM->Pop(color2)

		unsigned int color3;
	pVM->Pop(color3)

		unsigned int color4;
	pVM->Pop(color4)

		unsigned int color5;
	pVM->Pop(color5)
#endif
	CVehicleEntity * pVehicle = new CVehicleEntity();
	pVehicle->SetId(CServer::GetInstance()->GetVehicleManager()->FindFreeSlot());
	CServer::GetInstance()->GetVehicleManager()->Add(pVehicle->GetId(), pVehicle);

	RakNet::BitStream bitStream;
	bitStream.Write(pVehicle->GetId());
	bitStream.Write(vehicleModel);
	bitStream.Write(vecPosition);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_CREATE_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
	pVehicle->SetPosition(vecPosition);

	CScriptVehicle * pScriptVehicle = new CScriptVehicle();
	pScriptVehicle->SetEntity(pVehicle);
	pVehicle->SetScriptVehicle(pScriptVehicle);
	pVM->PushInstance("CVehicleEntity", pScriptVehicle);
	return 1;
}

void CScriptClasses::Register(CScriptVM * pVM)
{
	pVM->RegisterFunction("createVehicle", CreateVehicle);

	{ // ScriptPlayer
		// TODO: fix memory leak
		(new CScriptClass<CScriptPlayer>("CPlayerEntity"))->
			AddMethod("setPosition", &CScriptPlayer::SetPosition). // Synced
			AddMethod("setRotation", &CScriptPlayer::SetRotation). // Synced
			AddMethod("setMoveSpeed", &CScriptPlayer::SetMoveSpeed). // Synced
			AddMethod("setTurnSpeed", &CScriptPlayer::SetTurnSpeed). // Synced
			AddMethod("getArmour", &CScriptPlayer::GetArmour). // Synced
			AddMethod("setArmour", &CScriptPlayer::SetArmour). // Synced
			AddMethod("getHealth", &CScriptPlayer::GetHealth). // Synced
			AddMethod("setHealth", &CScriptPlayer::SetHealth). // Synced
			AddMethod("getHeading", &CScriptPlayer::GetHeading). // Synced
			AddMethod("setHeading", &CScriptPlayer::SetHeading). // Synced
			AddMethod("getModel", &CScriptPlayer::GetModel). // Synced
			AddMethod("setModel", &CScriptPlayer::SetModel). // Synced
			AddMethod("getDimension", &CScriptPlayer::GetDimension).
			AddMethod("setDimension", &CScriptPlayer::SetDimension).
			AddMethod("getName", &CScriptPlayer::GetName). // Synced
			AddMethod("setName", &CScriptPlayer::SetName). // Synced
			AddMethod("getMoney", &CScriptPlayer::GetMoney). // Synced
			AddMethod("setMoney", &CScriptPlayer::SetMoney). // Synced
			AddMethod("getWantedLevel", &CScriptPlayer::GetWantedLevel). // Synced
			AddMethod("setWantedLevel", &CScriptPlayer::SetWantedLevel). // Synced
			AddMethod("giveWeapon", &CScriptPlayer::GiveWeapon). // Synced
			//AddMethod("sendMessage", &CScriptPlayer::SendMessage).
		Register(pVM);
	}

	{ // ScriptVehicle
		(new CScriptClass<CScriptVehicle>("CVehicleEntity"))->
		AddMethod("setPosition", &CScriptVehicle::SetPosition).
		AddMethod("setRotation", &CScriptVehicle::SetRotation).
		AddMethod("setMoveSpeed", &CScriptVehicle::SetMoveSpeed).
		//AddMethod("getHealth", &CScriptVehicle::GetHealth).
		//AddMethod("setHealth", &CScriptVehicle::SetHealth).
		Register(pVM);
	}


}