//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CDevelopment.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CDevelopment.h"
#include <Ptrs.h>

float fCurrentLine = 325;
CVector3 vecPosition, vecMoveSpeed, vecTurnSpeed, vecAimTarget, vecShotSource, vecShotTarget;
float fArmHeading, fArmDown, fHeading;
bool bDuckingState;

CDevelopment::CDevelopment() : bDebugView(false),
	bDebugPlayerPresent(false),
	m_pDebugPlayer(0),
	bHasAimSyncData(false),
	m_bStoreOnFootSwitch(false),
	m_iOldMoveStyle(0)
{

}

void CDevelopment::DumpTask(CString strName, CIVTask * pTask)
{
	if(!pTask)
		return;

	fCurrentLine += 15;
	g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("%s: %s (%d)", strName.Get(), pTask->GetName(), pTask->GetType()).Get());

	/*if(!pTask->IsSimple())
	{
		CIVTask * pSubTask = ((CIVTaskComplex *)pTask)->GetSubTask();
		DumpTask(strName, pSubTask);
	}*/
}


void CDevelopment::DumpTasks(CIVPedTaskManager * pPedTaskManager, int iType)
{
	if(iType == 0)
	{
		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Priority Tasks: ").Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("").Get());
		DumpTask("PhysicalResponse",     pPedTaskManager->GetTask(TASK_PRIORITY_PHYSICAL_RESPONSE));
		DumpTask("EventResponseTemp",    pPedTaskManager->GetTask(TASK_PRIORITY_EVENT_RESPONSE_TEMP));
		DumpTask("EventResponseNonTemp", pPedTaskManager->GetTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP));
		DumpTask("Primary",              pPedTaskManager->GetTask(TASK_PRIORITY_PRIMARY));
		DumpTask("Default",              pPedTaskManager->GetTask(TASK_PRIORITY_DEFAULT));
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("").Get());
	}
	else if(iType == 1)
	{
		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Secondary Tasks: ").Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("").Get());
		DumpTask("Attack",        pPedTaskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK));
		DumpTask("Duck",          pPedTaskManager->GetTaskSecondary(TASK_SECONDARY_DUCK));
		DumpTask("Say",           pPedTaskManager->GetTaskSecondary(TASK_SECONDARY_SAY));
		DumpTask("FacialComplex", pPedTaskManager->GetTaskSecondary(TASK_SECONDARY_FACIAL_COMPLEX));
		DumpTask("PartialAnim",   pPedTaskManager->GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM));
		DumpTask("IK",            pPedTaskManager->GetTaskSecondary(TASK_SECONDARY_IK));
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("").Get());

	}
	else if(iType == 2)
	{
		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Movement Tasks: ").Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("").Get());
		DumpTask("MovementTask0", pPedTaskManager->GetTaskMovement(TASK_MOVEMENT_UNKNOWN0));
		DumpTask("MovementTask1", pPedTaskManager->GetTaskMovement(TASK_MOVEMENT_UNKNOWN1));
		DumpTask("MovementTask2", pPedTaskManager->GetTaskMovement(TASK_MOVEMENT_UNKNOWN2));
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("").Get());
	}
}

void CDevelopment::Process()
{
	fCurrentLine = 325;

	if(bDebugView && g_pCore->GetGame()->GetLocalPlayer() && g_pCore->GetGraphics()) {
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("LocalPlayer Debug:").Get());

		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPosition(vecPosition);
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetMoveSpeed(vecMoveSpeed);
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetTurnSpeed(vecTurnSpeed);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponAimTarget(vecAimTarget);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetArmHeading(fArmHeading);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetArmUpDown(fArmDown);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponShotSource(vecShotSource);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponShotTarget(vecShotTarget);
		bool fHealth = g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetHealth();
		bDuckingState = g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPlayerHandle().bDuckState;
		fHeading = g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetRotation();
		CVector3 vecDirection;
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetPlayerPed()->GetDirection(vecDirection);
		CVector3 vecRoll;
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetPlayerPed()->GetRoll(vecRoll);

		// Exclusive for weapon sync
		Matrix34 pCamA = g_pCore->GetGame()->GetCamera()->GetGameCam()->GetCam()->m_data1.m_matMatrix;
		Matrix34 pCamB = g_pCore->GetGame()->GetCamera()->GetGameCam()->GetCam()->m_data2.m_matMatrix;
		Matrix34 pCamC = g_pCore->GetGame()->GetCamera()->GetGameCam()->GetCam()->m_data3.m_matMatrix;
		CVector3 vecLookAt;
		g_pCore->GetGame()->GetCamera()->GetAimPosition(&vecLookAt);
		float fArmHeading, fArmUpDown;
		g_pCore->GetGame()->GetLocalPlayer()->GetContextData()->GetArmHeading(fArmHeading);
		g_pCore->GetGame()->GetLocalPlayer()->GetContextData()->GetArmUpDown(fArmUpDown);

		if(PTR_LOCALPLAYER->IsOnFoot()) {
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Current Position: %.2f, %.2f ,%.2f", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Move Speed: %.2f, %.2f ,%.2f", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Turn Speed: %.2f, %.2f ,%.2f", vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Direction: %.2f, %.2f ,%.2f", vecDirection.fX, vecDirection.fY, vecDirection.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Roll: %.2f, %.2f ,%.2f", vecRoll.fX, vecRoll.fY, vecRoll.fZ).Get());
			
			DumpTasks(g_pCore->GetGame()->GetLocalPlayer()->GetPlayerPed()->GetPedTaskManager(),0);
			DumpTasks(g_pCore->GetGame()->GetLocalPlayer()->GetPlayerPed()->GetPedTaskManager(),1);
			DumpTasks(g_pCore->GetGame()->GetLocalPlayer()->GetPlayerPed()->GetPedTaskManager(),2);
		}
		else if(PTR_LOCALPLAYER->IsInVehicle()) {
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetPosition(vecPosition);
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetMoveSpeed(vecMoveSpeed);
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetTurnSpeed(vecTurnSpeed);
			bool bEngineStatus = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetEngineStatus();
			bool bHeadLightsStatus = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetHeadlights();
			int iLightsState = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetLightsState();
			BYTE byteRadioIndex = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetRadioStation();
			float fVehicleEngineHealth = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetEngineHealth();
			float fPetrolHealth = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetPetrolTankHealth();
			float fGasPressure = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetGasPedal();
			float fBreakPressure = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetBrakePedal();
			float fSteeringBias = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetSteerBias();
			float fSteering = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetSteeringAngle();
			float fDirtLevel = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetDirtLevel();
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetDirection(vecDirection);
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetRoll(vecRoll);

			// Controls
			CControls * pControls = new CControls;
			g_pCore->GetGame()->GetLocalPlayer()->GetControlState(pControls);

			fCurrentLine += 30;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Current Position: %.2f, %.2f ,%.2f", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Move Speed: %.2f, %.2f ,%.2f", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Turn Speed: %.2f, %.2f ,%.2f", vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Direction: %.2f, %.2f ,%.2f", vecDirection.fX, vecDirection.fY, vecDirection.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Roll: %.2f, %.2f ,%.2f", vecRoll.fX, vecRoll.fY, vecRoll.fZ).Get());
			
			fCurrentLine += 30;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input RIGHT: %d", (pControls->ucInVehicleMove[0])).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input LEFT: %d", (pControls->ucInVehicleMove[1])).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input UP: %d", (pControls->ucInVehicleMove[2])).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input DOWN: %d", (pControls->ucInVehicleMove[3])).Get());

			fCurrentLine += 30;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Engine Health: %f", fVehicleEngineHealth).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Petrol Health: %f", fPetrolHealth).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Gas pressure: %f", fGasPressure).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Break Pressure: %f", fBreakPressure).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Steering Bias: %f", fSteeringBias).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Steering: %f", fSteering).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Dirt Level: %f", fDirtLevel).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Indicators: %d, %d, %d, %d", 0, 0, 0, 0).Get());

			fCurrentLine += 30;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Engine State: %d", bEngineStatus).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Lights State: %d", iLightsState).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Headlights State: %d", bHeadLightsStatus).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Radio Station Index: [%d] %s", byteRadioIndex, CGameFunction::GetRadioName(byteRadioIndex).Get()).Get());
		}

		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Aim Coords: %.2f, %.2f ,%.2f", vecAimTarget.fX, vecAimTarget.fY, vecAimTarget.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Arm Heading: %.2f | Arm UpDown: %.2f", fArmHeading, fArmUpDown).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Shot Coords: %.2f, %.2f ,%.2f", vecShotTarget.fX, vecShotTarget.fY, vecShotTarget.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Game Cam: %.2f, %.2f ,%.2f", vecLookAt.fX, vecLookAt.fY, vecLookAt.fZ).Get());

		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Ducking: %d", bDuckingState).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Health: %f", fHealth).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Rotation: %.2f", fHeading).Get());
		
	}

	CHECK_PTR_VOID(bDebugPlayerPresent);

	CControls controlState;
	g_pCore->GetGame()->GetPad()->GetCurrentControlState(controlState);

	m_pDebugPlayer->SetControlState(&controlState);
	if(controlState.IsAiming() || controlState.IsFiring())
		bHasAimSyncData = true;
	else
		bHasAimSyncData = false;
		
	m_pDebugPlayer->PreStoreIVSynchronization(bHasAimSyncData,true,g_pCore->GetGame()->GetLocalPlayer());
}

void CDevelopment::CreateDebugPlayer()
{
	CVector3 vecCreatePos = g_pCore->GetGame()->GetLocalPlayer()->GetPosition();
	m_pDebugPlayer = new CPlayerEntity(false);

	m_pDebugPlayer->SetModel(0);
	m_pDebugPlayer->Create();
	m_pDebugPlayer->Teleport(vecCreatePos);
	m_pDebugPlayer->SetPedClothes(0, 0);
	m_pDebugPlayer->SetPedClothes(1, 1);
	m_pDebugPlayer->SetPedClothes(2, 1);
	m_pDebugPlayer->SetPedClothes(3, 0);
	PTR_LOCALPLAYER->SetPedClothes(0, 0);
	PTR_LOCALPLAYER->SetPedClothes(1, 1);
	PTR_LOCALPLAYER->SetPedClothes(2, 1);
	PTR_LOCALPLAYER->SetPedClothes(3, 0);

	bDebugPlayerPresent = true;
}