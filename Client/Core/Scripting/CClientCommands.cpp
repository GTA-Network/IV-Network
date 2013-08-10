//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
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

#include <Common.h>
#include <CCore.h>
extern CCore * g_pCore;

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
		int iVehicleType = 91;

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
			pPlayer->Create();

			pPlayer->Teleport(vecCreatePos);
		}
		return true;
	}
	else if(strCommand == "spawn")
	{
		g_pCore->GetChat()->Output("Spawning local player ...",false);
		g_pCore->GetGame()->OnClientReadyToGamePlay();
		g_pCore->GetGame()->GetLocalPlayer()->SetModel(21);

		int iVehicleType = 91;

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
	else if(strCommand == "engine")
	{
		if(g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity() != NULL)
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->SetEngineState(true);
		
		return true;
	}
	
	return false;
}