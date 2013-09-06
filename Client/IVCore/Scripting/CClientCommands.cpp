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
#include <Game/IVEngine/CIVTrain.h>

extern unsigned int l_U40;
unsigned int pObj;
CIVTrain * pTrain;

bool CClientCommands::HandleUserInput(std::string strCommand, std::string strParameters)
{
	if(strCommand == "q"  || strCommand == "quit")
	{
		// Are we connected to the network?
		if(g_pCore->GetNetworkManager()->IsConnected())
		{
			// Disconnect and shutdown RakNet
			g_pCore->GetNetworkManager()->Shutdown(500, true);
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
		if(pVehicle) {
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
		int iWeapon = atoi(strParameters.c_str());

		if(g_pCore->GetDevelopmentInstance()->GetDebugPlayerPed())
			CIVScript::GiveWeaponToChar(g_pCore->GetDevelopmentInstance()->GetDebugPlayerPed()->GetScriptingHandle(),(CIVScript::eWeapon)iWeapon,50,true);
		
		CIVScript::GiveWeaponToChar(g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle(),(CIVScript::eWeapon)iWeapon,50,true);
		return true;
	}
	else if(strCommand == "cp")
	{
		CVector3 vecCreatePos; 
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecCreatePos);

		CPlayerEntity * pPlayer = new CPlayerEntity(false);
		if(pPlayer) {
			pPlayer->SetModel(7);
			pPlayer->Create();
			pPlayer->Teleport(vecCreatePos);
		}
		return true;
	}
	else if(strCommand == "engine") 
	{
		if(g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity() != NULL)
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->SetEngineState(!g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetEngineState());
		
		return true;
	}
	else if(strCommand == "saveposition" || strCommand == "save")
	{
		FILE * file = fopen(SharedUtility::GetAbsolutePath("multiplayer//SavePositions.log"), "a");
		if(!file)
		{
			g_pCore->GetChat()->Output("Failed to open 'SavePositions.log'");
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
	else if(strCommand == "yaxis")
	{
		CVector3 vecPositon;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPositon);

		vecPositon.fY += atoi(strParameters.c_str());
		g_pCore->GetGame()->GetLocalPlayer()->SetPosition(vecPositon);
		return true;
	}
	else if(strCommand == "zaxis")
	{
		CVector3 vecPositon;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPositon);

		vecPositon.fZ += atoi(strParameters.c_str());
		g_pCore->GetGame()->GetLocalPlayer()->SetPosition(vecPositon);
		return true;
	}
	else if(strCommand == "port")
	{
		CVector3 vecPositon;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPositon);
		vecPositon.fX = 900;
		vecPositon.fY = -71;
		vecPositon.fZ += 20;
		g_pCore->GetGame()->GetLocalPlayer()->SetPosition(vecPositon);
		return true;
	}
	else if(strCommand == "time")
	{
		g_pCore->GetTimeManagementInstance()->SetTime(atoi(strParameters.c_str()),0);
		CIVWeather::SetTime(atoi(strParameters.c_str()),0);
		return true;
	}
	else if(strCommand == "setmodel")
	{
		g_pCore->GetGame()->GetLocalPlayer()->SetModel(atoi(strParameters.c_str()));
		return true;
	}
	else if(strCommand == "setclothes")
	{
		CString strParameter = CString("%s",strParameters.c_str());
		g_pCore->GetChat()->Outputf(false, strParameter.Get());

		// Get the end of the command
		size_t sCommandEnd = strParameter.Find(" "); 

		// If we don't have a valid end use the end of the string
		if (sCommandEnd == std::string::npos)
		{
			sCommandEnd = strParameter.GetLength();
		}

		// Get the command name
		std::string strCommand2 = strParameter.Substring(0, (sCommandEnd));

		// Get the command parameters
		std::string strParams;

		// Do we have any parameters?
		if(sCommandEnd < strParameter.GetLength())
		{
			strParams = strParameter.Substring((sCommandEnd + 1), strParameter.GetLength());
		}

		g_pCore->GetChat()->Outputf(false, "Setting clothes part %d to %d",atoi(strCommand2.c_str()), atoi(strParams.c_str()));
		g_pCore->GetGame()->GetLocalPlayer()->SetPedClothes(atoi(strCommand2.c_str()), atoi(strParams.c_str()));

		return true;
	}
	else if(strCommand == "bahama")
	{
		CVector3 vecPos = CVector3(-15.9453f, -13.5865f, -11.7456f);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::SetPosition(vecPos);
		return true;
	}
	else if(strCommand == "spawnvehicles")
	{
		CVector3 vecPos;
		PTR_LOCALPLAYER->GetPosition(vecPos);

		for(int i = 0; i < 179; i++) {
			vecPos.fX += 5;
			CVehicleEntity * pVehicle = new CVehicleEntity(i,vecPos,0.0f,0,0,0,0);
			if(pVehicle)
			{
				// Add our vehicle
				g_pCore->GetGame()->GetVehicleManager()->Add(pVehicle);
				pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->FindFreeSlot());
				pVehicle->Create();
				pVehicle->SetPosition(vecPos);
			}
		}
		return true;
	}
	else if(strCommand == "getvehpos")
	{
		int iVehicle = atoi(strParameters.c_str());

		if(g_pCore->GetGame()->GetVehicleManager()->DoesExists(iVehicle)) {
			CVector3 vecPosition;
			g_pCore->GetGame()->GetVehicleManager()->GetAt(iVehicle)->GetPosition(vecPosition);
			PTR_CHAT->Outputf(false,"Position of vehicle %d: %f, %f,%f",iVehicle, vecPosition.fX, vecPosition.fY, vecPosition.fZ);
		}
		return true;
	}
	else if(strCommand == "ivhelp")
	{
		PTR_CHAT->Output(false, "List of Default IV:MP Commands...");
		PTR_CHAT->Output(false, "** /cv /respawn /debug /weapon /cp /spawn /engine /save /giveweapon /xaxis /time");
		PTR_CHAT->Output(false, "** /setmodel /testweapon /ready /parachute /bahama /spawnvehicles /getvehpos");
		return true;
	}
	else if(strCommand == "createtrain")
	{
		g_pCore->GetGame()->GetIVManagement()->CreateTrain(g_pCore->GetGame()->GetLocalPlayer()->GetPosition(), 3, 20.0f, 0);
	}
	else if(strCommand == "blip")
	{
		unsigned int uiBlip;
		CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_ADD_BLIP_FOR_COORD, 0, 0, 0,&uiBlip); 
		CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_CHANGE_BLIP_SPRITE, 10);
	}
	else if(strCommand == "numberplate")
	{
		g_pCore->GetChat()->Output("FAIL");
	}
	return false;
}