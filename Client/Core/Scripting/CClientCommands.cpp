//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CClientCommands.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CClientCommands.h"

#include <IV/IVParachute_Manager.h>
#include <IV/IVParachute_Process.h>
#include <Game/IVEngine/CIVModelManager.h>
#include <Game/IVEngine/CIVHud.h>
#include <IV/CIVScript.h>
#include <IV/CIVScriptEnums.h>
#include <Game/IVEngine/CIVWeather.h>
#include <IV/CIVScript_FunctionInvoke.h>
#include <Game/IVEngine/CIVStreaming.h>
#include <Ptrs.h>
#include <Game/CEFLCSupport.h>

extern unsigned int l_U40;
unsigned int pObj;

bool CClientCommands::HandleUserInput(std::string strCommand, std::string strParameters)
{
	if(strCommand == "q"  || strCommand == "quit" || strCommand == "exit")
	{
		// Are we connected to the network?
		if(g_pCore->GetNetworkManager()->IsConnected())
		{
			// Disconnect and shutdown RakNet
			g_pCore->GetNetworkManager()->ShutDown();
		}
		
		TerminateProcess(GetCurrentProcess(), 0);
		return true;
	}
	else if(strCommand == "qq" || strCommand == "quickquit")
	{
		TerminateProcess(GetCurrentProcess(), 0);
		return true;
	}

	else if(strCommand == "cv")
	{
		int iVehicleType = atoi(strParameters.c_str());

		CVector3 vecCreatePos; 
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecCreatePos);
		vecCreatePos.fX += 4;
		vecCreatePos.fY += 1;

		CVehicleEntity * pVehicle = new CVehicleEntity(iVehicleType,vecCreatePos,0.0f,0,0,0,0);
		if(pVehicle)
		{
			// Add our vehicle
			g_pCore->GetGame()->GetVehicleManager()->Add(pVehicle);

			pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->FindFreeSlot());

			pVehicle->Create();

			pVehicle->SetPosition(vecCreatePos);
		}
		return true;
	}
	else if(strCommand == "respawn")
	{
		g_pCore->GetGame()->GetLocalPlayer()->Respawn();
		return true;
	}
	else if(strCommand == "debug")
	{
		g_pCore->GetDevelopmentInstance()->CreateDebugPlayer();
		return true;
	}
	else if(strCommand == "weapon")
	{
		if(g_pCore->GetDevelopmentInstance()->GetDebugPlayerPed())
			CIVScript::GiveWeaponToChar(g_pCore->GetDevelopmentInstance()->GetDebugPlayerPed()->GetScriptingHandle(),(CIVScript::eWeapon)CIVScript::WEAPON_SHOTGUN,50,true);
		
		CIVScript::GiveWeaponToChar(g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle(),(CIVScript::eWeapon)CIVScript::WEAPON_SHOTGUN,50,true);
		return true;
	}
	else if(strCommand == "cp")
	{
		CVector3 vecCreatePos; 
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecCreatePos);

		CPlayerEntity * pPlayer = new CPlayerEntity(false);
		if(pPlayer)
		{
			pPlayer->SetModel(7);
			pPlayer->Create();
			pPlayer->Teleport(vecCreatePos);
		}
		return true;
	}
	else if(strCommand == "spawn")
	{
		g_pCore->GetChat()->Output("Spawning local player ...",false);
		g_pCore->GetGame()->OnClientReadyToGamePlay();
		g_pCore->GetGame()->GetLocalPlayer()->SetModel(7);

		int iVehicleType = g_pCore->GetGame()->IsUsingEFLCContent() ? 128 : 91;

		CVector3 vecCreatePos; 
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecCreatePos);
		vecCreatePos.fX += 4;
		vecCreatePos.fY += 1;

		CVehicleEntity * pVehicle = new CVehicleEntity(iVehicleType,vecCreatePos,0.0f,0,0,0,0);
		if(pVehicle)
		{
			// Add our vehicle
			g_pCore->GetGame()->GetVehicleManager()->Add(pVehicle);

			pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->FindFreeSlot());

			pVehicle->Create();

			pVehicle->SetPosition(vecCreatePos);
		}

		PTR_CHAT->Output("Type \"/ready\" and seconds later \"/parachute\" to create a parachute!",false);
		return true;
	}
	else if(strCommand == "engine")
	{
		if(g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity() != NULL)
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->SetEngineState(!g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetEngineState());
		
		return true;
	}
	else if(strCommand == "saveposition")
	{
		FILE * file = fopen(SharedUtility::GetAbsolutePath("multiplayer//SavePositions.log"), "a");
		if(!file)
		{
			g_pCore->GetChat()->Output("Failed to open 'SavedData.log'");
			return true;
		}

		CVector3 vecPosition;

		// Get our local player
		CLocalPlayer * pLocalPlayer = g_pCore->GetGame()->GetLocalPlayer();

		if(pLocalPlayer->IsInVehicle())
		{
			CVehicleEntity * pVehicle = pLocalPlayer->GetVehicleEntity();

			if(pVehicle)
			{
				pVehicle->GetPosition(vecPosition);
				CVector3 vecRotation;
				pVehicle->GetRotation(vecRotation);
				BYTE byteColors[4];
				pVehicle->GetColors(byteColors[0], byteColors[1], byteColors[2], byteColors[3]);
				fprintf_s(file, "createVehicle(%d, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d);%s%s\n", CIVModelManager::ModelHashToVehicleId(pVehicle->GetModelInfo()->GetHash()), vecPosition.fX, vecPosition.fY, vecPosition.fZ, vecRotation.fX, vecRotation.fY, vecRotation.fZ, byteColors[0], byteColors[1], byteColors[2], byteColors[3], strParameters.size() > 0 ? " // " : "", strParameters.size() > 0 ? strParameters.c_str() : "");
			}
		}
		else
		{
			pLocalPlayer->GetPosition(vecPosition);
			int iModelId = pLocalPlayer->GetPlayerPed()->GetModelIndex();
			fprintf_s(file, "PlayerData(%d, %f, %f, %f, %f);%s%s\n", iModelId, vecPosition.fX, vecPosition.fY, vecPosition.fZ, pLocalPlayer->GetRotation() ,strParameters.size() > 0 ? " // " : "", strParameters.size() > 0 ? strParameters.c_str() : "");
		}

		fclose(file);
		g_pCore->GetChat()->Output("Position data saved to 'SavePositions.log'");
		return true;
	}
	else if(strCommand == "giveweapon")
	{
		int iWeapon = atoi(strParameters.c_str());
		CIVScript::GiveWeaponToChar(g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle(),(CIVScript::eWeapon)iWeapon, 100, true);
		return true;
	}
	else if(strCommand == "xaxis")
	{
		CVector3 vecPositon;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPositon);

		vecPositon.fX += atoi(strParameters.c_str());
		g_pCore->GetGame()->GetLocalPlayer()->SetPosition(vecPositon);
		return true;
	}
	else if(strCommand == "time")
	{
		CIVWeather::SetTime(atoi(strParameters.c_str()),0);
		return true;
	}
	else if(strCommand == "setmodel")
	{
		g_pCore->GetGame()->GetLocalPlayer()->SetModel(atoi(strParameters.c_str()));
		return true;
	}
	else if(strCommand == "testweapon")
	{
		CIVScript::GiveWeaponToChar(g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle(),CIVScript::WEAPON_EPISODIC_11,99,false);
		return true;
	}
	else if(strCommand == "ready")
	{
		PTR_CHAT->Output("Installing prachute...");
		CEFLCSupport::InstallPreGameLoad();
		return true;
	}
	else if(strCommand == "parachute")
	{
		PTR_CHAT->Output("Adding prachute...");

		CVector3 vecPosition;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPosition);
		unsigned int uiPlayerIndex = g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle();

		DWORD dwParachute = 0x58D6A0A0;
		
		//CIVScript::GiveWeaponToChar(uiPlayerIndex, 41, 1, false);
		//CIVScript::CreateObject(dwParachute, vecPosition.fX, vecPosition.fY, vecPosition.fZ + 2, &pObj, 1);
		//CIVScript::AttachObjectToPed(pObj, uiPlayerIndex, 0, 0.02500000, -0.12500000, 5.45000000, 0.00000000, 0.00000000, 0.00000000, 1);

		if(pObj != NULL)
			CIVScript::DeleteObject(&pObj);

		dwParachute = 0x4C19FE43; //0x402B7648;
		CIVScript::CreateObject(dwParachute, vecPosition.fX, vecPosition.fY, -25.0 , &pObj, 1);
		l_U40 = pObj;

		CIVScript::SetObjectDynamic(pObj, 0);
		CIVScript::SetObjectCollision(pObj, 0);
		CIVScript::SetObjectVisible(pObj, 0);
		CIVScript::SetActivateObjectPhysicsAsSoonAsItIsUnfrozen(pObj, 1);

		CIVScript::SetObjectDynamic( pObj, 1 );
        CIVScript::SetObjectCollision( pObj, 1 );
        CIVScript::SetObjectVisible( pObj, 1 );
		CIVScript::AttachObjectToPed( pObj, uiPlayerIndex, 1202, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 1 );
		CIVScript::PlayObjectAnim( pObj, "obj_chute_off", "PARACHUTE", 1000.00000000, 0, 1 );
		CIVScript::TaskPlayAnimWithFlags( uiPlayerIndex, "chute_off", "PARACHUTE", 3.00000000, 0, 1280 );
		return true;
	}
	else if(strCommand == "bahama")
	{
		CVector3 vecPos = CVector3(-15.9453f, -13.5865f, -11.7456f);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::Teleport(vecPos);
		return true;
	}
	return false;
}