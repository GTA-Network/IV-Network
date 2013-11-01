//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CClientCommands.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CClientCommands.h"

#include <Game/IVEngine/CIVModelManager.h>
#include <Game/IVEngine/CIVHud.h>
#include <IV/CIVScript.h>
#include <IV/CIVScriptEnums.h>
#include <Game/IVEngine/CIVWeather.h>
#include <IV/CIVScript_FunctionInvoke.h>
#include <Ptrs.h>
#include <Game/IVEngine/CIVTrain.h>

extern unsigned int l_U40;
unsigned int pObj;
CIVTrain * pTrain;

bool CClientCommands::HandleUserInput(CString strCommand, CString strParameters)
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
	else if (strCommand == "saveposition" || strCommand == "save")
	{
		FILE * file = fopen(SharedUtility::GetAbsolutePath("multiplayer//SavePositions.log"), "a");
		if (!file)
		{
			g_pCore->GetChat()->Print("Failed to open 'SavePositions.log'");
			return true;
		}

		CVector3 vecPosition;

		// Get our local player
		CLocalPlayer * pLocalPlayer = g_pCore->GetGame()->GetLocalPlayer();

		if (pLocalPlayer->IsInVehicle())
		{
			CVehicleEntity * pVehicle = pLocalPlayer->GetVehicleEntity();

			if (pVehicle)
			{
				pVehicle->GetPosition(vecPosition);
				CVector3 vecRotation;
				pVehicle->GetRotation(vecRotation);
				DWORD dwColors[5];
				pVehicle->GetColors(dwColors[0], dwColors[1], dwColors[2], dwColors[3], dwColors[4]);
				fprintf_s(file, "createVehicle(%d, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d, %d);%s%s\n", CIVModelManager::ModelHashToVehicleId(pVehicle->GetModelInfo()->GetHash()), vecPosition.fX, vecPosition.fY, vecPosition.fZ, vecRotation.fX, vecRotation.fY, vecRotation.fZ, dwColors[0], dwColors[1], dwColors[2], dwColors[3], dwColors[4], strParameters.GetLength() > 0 ? " // " : "", strParameters.GetLength() > 0 ? strParameters.Get() : "");
			}
		}
		else
		{
			pLocalPlayer->GetPosition(vecPosition);
			int iModelId = pLocalPlayer->GetPlayerPed()->GetModelIndex();
			fprintf_s(file, "PlayerData(%d, %f, %f, %f, %f);%s%s\n", iModelId, vecPosition.fX, vecPosition.fY, vecPosition.fZ, pLocalPlayer->GetHeading(), strParameters.GetLength() > 0 ? " // " : "", strParameters.GetLength() > 0 ? strParameters.Get() : "");
		}

		fclose(file);
		g_pCore->GetChat()->Print("Position data saved to 'SavePositions.log'");
		return true;
	}
#ifdef _DEBUG
	else if(strCommand == "cv")
	{
		CVector3 vecCreatePos; 
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecCreatePos);
		vecCreatePos.fX += 4;

		CVehicleEntity * pVehicle = new CVehicleEntity(atoi(strParameters.Get()), vecCreatePos, 0.0f, 0x000000, 0x000000, 0x000000, 0x000000, 0xFFFFFF);
		if(pVehicle) {
			// Add our vehicle
			pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->Add(pVehicle));
			pVehicle->Create();
			g_pCore->GetGame()->GetLocalPlayer()->WarpIntoVehicle(pVehicle);
		}
		return true;
	}
	else if(strCommand == "respawn")
	{
		g_pCore->GetGame()->GetLocalPlayer()->Respawn();
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
	else if(strCommand == "giveweapon")
	{
		CIVScript::GiveWeaponToChar(g_pCore->GetGame()->GetLocalPlayer()->GetScriptingHandle(), (CIVScript::eWeapon)atoi(strParameters.Get()), 100, true);
		return true;
	}
	else if(strCommand == "xaxis")
	{
		CVector3 vecPositon;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPositon);

		vecPositon.fX += atoi(strParameters.Get());
		g_pCore->GetGame()->GetLocalPlayer()->SetPosition(vecPositon);
		return true;
	}
	else if(strCommand == "yaxis")
	{
		CVector3 vecPositon;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPositon);

		vecPositon.fY += atoi(strParameters.Get());
		g_pCore->GetGame()->GetLocalPlayer()->SetPosition(vecPositon);
		return true;
	}
	else if(strCommand == "zaxis")
	{
		CVector3 vecPositon;
		g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecPositon);

		vecPositon.fZ += atoi(strParameters.Get());
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
		g_pCore->GetTimeManagementInstance()->SetTime(atoi(strParameters.Get()), 0);
		CGameFunction::SetTimeOfDay(atoi(strParameters.Get()), 0);
		return true;
	}
	else if(strCommand == "setmodel")
	{
		g_pCore->GetGame()->GetLocalPlayer()->SetModel(atoi(strParameters.Get()));
		return true;
	}
	else if(strCommand == "setclothes")
	{
		CString strParameter = CString("%s", strParameters.Get());
		g_pCore->GetChat()->Print(strParameter.Get());

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

		g_pCore->GetChat()->Print(CString("Setting clothes part %d to %d", atoi(strCommand2.c_str()), atoi(strParams.c_str())));
		g_pCore->GetGame()->GetLocalPlayer()->SetPedClothes(atoi(strCommand2.c_str()), atoi(strParams.c_str()));

		return true;
	}
	else if(strCommand == "bahama")
	{
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::SetPosition(CVector3(-15.9453f, -13.5865f, -11.7456f));
		return true;
	}
	else if(strCommand == "spawnvehs")
	{
		CVector3 vecPos;
		PTR_LOCALPLAYER->GetPosition(vecPos);

		for (int i = 0; i < 179; i++)
		{
			vecPos.fX += 5;
			CVehicleEntity * pVehicle = new CVehicleEntity(i, vecPos, 0.0f, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF);
			if(pVehicle)
			{
				// Add our vehicle
				g_pCore->GetGame()->GetVehicleManager()->Add(pVehicle);
				pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->FindFreeSlot());
				pVehicle->Create();
				pVehicle->SetPosition(vecPos, true);
			}
		}
		return true;
	}
	else if(strCommand == "getvehpos")
	{
		int iVehicle = atoi(strParameters.Get());

		if(g_pCore->GetGame()->GetVehicleManager()->DoesExists(iVehicle)) {
			CVector3 vecPosition;
			g_pCore->GetGame()->GetVehicleManager()->GetAt(iVehicle)->GetPosition(vecPosition);
			PTR_CHAT->Print(CString("Position of vehicle %d: %f, %f,%f", iVehicle, vecPosition.fX, vecPosition.fY, vecPosition.fZ));
		}
		return true;
	}
	else if(strCommand == "ivhelp")
	{
		PTR_CHAT->Print("List of Default IV:N Commands...");
		PTR_CHAT->Print("** /cv /respawn /debug /weapon /cp /spawn /engine /save /giveweapon /xaxis /time");
		PTR_CHAT->Print("** /setmodel /testweapon /ready /parachute /bahama /spawnvehicles /getvehpos");
		return true;
	}
	else if(strCommand == "createtrain")
	{
		g_pCore->GetGame()->GetIVManagement()->CreateTrain(g_pCore->GetGame()->GetLocalPlayer()->GetPosition(), 3, 20.0f, 0);
		return true;
	}
	else if(strCommand == "blip")
	{
		unsigned int uiBlip;
		CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_ADD_BLIP_FOR_COORD, 0, 0, 0,&uiBlip); 
		CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_CHANGE_BLIP_SPRITE, 10);
		return true;
	}
	else if(strCommand == "sethealth")
	{
		g_pCore->GetGame()->GetLocalPlayer()->SetHealth(atoi(strParameters.Get()));
		return true;
	}
	else if (strCommand == "setarmour")
	{
		g_pCore->GetGame()->GetLocalPlayer()->SetArmour(atoi(strParameters.Get()));
		return true;
	}
#endif
	return false;
}