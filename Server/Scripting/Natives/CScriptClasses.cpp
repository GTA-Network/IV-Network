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
			AddMethod("setRotation", &CScriptPlayer::SetRotation).
			AddMethod("setMoveSpeed", &CScriptPlayer::SetMoveSpeed).
			AddMethod("setTurnSpeed", &CScriptPlayer::SetTurnSpeed).
			AddMethod("getArmour", &CScriptPlayer::GetArmour).
			AddMethod("setArmour", &CScriptPlayer::SetArmour).
			AddMethod("getHealth", &CScriptPlayer::GetHealth).
			AddMethod("setHealth", &CScriptPlayer::SetHealth). // Synced
			AddMethod("getHeading", &CScriptPlayer::GetHeading).
			AddMethod("setHeading", &CScriptPlayer::SetHeading).
			AddMethod("getModel", &CScriptPlayer::GetModel).
			AddMethod("setModel", &CScriptPlayer::SetModel).
			AddMethod("getDimension", &CScriptPlayer::GetDimension).
			AddMethod("setDimension", &CScriptPlayer::SetDimension).
			AddMethod("getName", &CScriptPlayer::GetName).
			AddMethod("setName", &CScriptPlayer::SetName).
			AddMethod("getMoney", &CScriptPlayer::GetMoney).
			AddMethod("setMoney", &CScriptPlayer::SetMoney).
			AddMethod("getWantedLevel", &CScriptPlayer::GetWantedLevel).
			AddMethod("setWantedLevel", &CScriptPlayer::SetWantedLevel).
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