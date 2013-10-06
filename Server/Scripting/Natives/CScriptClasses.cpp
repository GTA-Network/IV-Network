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

void CScriptClasses::Register(CScriptVM * pVM)
{
	{ // ScriptPlayer
		(new CScriptClass<CScriptPlayer>("CPlayerEntity"))->
			AddMethod("setPosition", &CScriptPlayer::SetPosition).
			AddMethod("setRotation", &CScriptPlayer::SetRotation).
			AddMethod("setMoveSpeed", &CScriptPlayer::SetMoveSpeed).
			AddMethod("setTurnSpeed", &CScriptPlayer::SetTurnSpeed).
			AddMethod("getArmour", &CScriptPlayer::GetArmour).
			AddMethod("setArmour", &CScriptPlayer::SetArmour).
			AddMethod("getHealth", &CScriptPlayer::GetHealth).
			AddMethod("setHealth", &CScriptPlayer::SetHealth).
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
		Register(pVM);
	}

	{ // ScriptVehicle
		(new CScriptClass<CScriptVehicle>("CVehicleEntity"))->
		AddMethod("setPosition", &CScriptVehicle::SetPosition).
		AddMethod("setRotation", &CScriptVehicle::SetRotation).
		AddMethod("setMoveSpeed", &CScriptVehicle::SetMoveSpeed).
		AddMethod("setTurnSpeed", &CScriptVehicle::SetTurnSpeed).
		//AddMethod("getHealth", &CScriptVehicle::GetHealth).
		//AddMethod("setHealth", &CScriptVehicle::SetHealth).
		Register(pVM);
	}
}


int CScriptClasses::CreateEntity(int * VM)
{
	CResource* pResource = CResourceManager::GetInstance()->Get(VM);
	
	if(pResource)
	{
		CScriptVM* pVM = pResource->GetVM();
		
		CString strEntity = "HJHKJ";
		/*pVM->Pop(strEntity);
		pVM->ResetStackIndex();*/
		if(strEntity == "3DLABEL")
		{
			C3DLabelEntity* p3DLabel = new C3DLabelEntity();
			pVM->SetClassInstance("C3DLabelEntity", (void*)p3DLabel);
			CEntityNatives::Register(pVM);
			C3DLabelNatives::Register(pVM);
		} else if(strEntity == "ACTOR") {
			CActorEntity* pActor = new CActorEntity();
			pVM->SetClassInstance("CActorEntity", (void*)pActor);
			CEntityNatives::Register(pVM);
			CActorNatives::Register(pVM);
		} else if(strEntity == "BLIP") {
			CBlipEntity * pBlip = new CBlipEntity();
			pVM->SetClassInstance("CBlipEntity", (void*)pBlip);
			CEntityNatives::Register(pVM);
			CBlipNatives::Register(pVM);
		} else if(strEntity == "CHECKPOINT") {
			CCheckpointEntity* pCheckpoint = new CCheckpointEntity();
			pVM->SetClassInstance("CCheckpointEntity", (void*)pCheckpoint);
			CEntityNatives::Register(pVM);
			CCheckpointNatives::Register(pVM);
		} else if(strEntity == "FIRE") {
			CFireEntity* pFire = new CFireEntity();
			pVM->SetClassInstance("CFireEntity", (void*)pFire);
			CEntityNatives::Register(pVM);
			CFireNatives::Register(pVM);
		} else if(strEntity == "OBJECT") {
			CObjectEntity* pObject = new CObjectEntity();
			pVM->SetClassInstance("CObjectEntity", (void*)pObject);
			CEntityNatives::Register(pVM);
			CObjectNatives::Register(pVM);
		} else if(strEntity == "PICKUP") {
			CPickupEntity* pPickup = new CPickupEntity();
			pVM->SetClassInstance("CPickupEntity", (void*)pPickup);
			CEntityNatives::Register(pVM);
			CPickupNatives::Register(pVM);
		} else if(strEntity == "PLAYER") {
			CPlayerEntity* pPlayer = new CPlayerEntity();
			pVM->SetClassInstance("CPlayerEntity", (void*)pPlayer);
			CEntityNatives::Register(pVM);
			CPlayerNatives::Register(pVM);
		} else /*if(strEntity == "VEHICLE")*/ {
			CVehicleEntity* pVehicle = new CVehicleEntity();

			/* now read the additional params for vehicle spawning */

			// Memo: add params count check in VM Pop methods
			// Merge the pop events so we use only Pop instead of PopVector
			//CVector3 vecPos;
			//CVector3 vecRot;
			//pVM->Pop(vecPos);
			//pVM->Pop(vecRot);

			//// Do we need the id; maybe internal for easier sync but definetly not public to the scripting engine
			pVehicle->SetId(CServer::GetInstance()->GetVehicleManager()->Add(pVehicle));
			//
			pVM->SetClassInstance("CVehicleEntity", (void*)pVehicle);
			//CEntityNatives::Register(pVM);
			//CVehicleNatives::Register(pVM);

			//pVehicle->Spawn();
		}
	}
	return 1;
}