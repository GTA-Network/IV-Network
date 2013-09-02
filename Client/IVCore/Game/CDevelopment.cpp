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
	bHasAimSyncData(false),
	m_bStoreOnFootSwitch(false),
	m_iOldMoveStyle(0)
{

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
		bDuckingState = g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPlayerHandle().bDuckState;
		fHeading = g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetRotation();

		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Current Position: %.2f, %.2f ,%.2f", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Move Speed: %.2f, %.2f ,%.2f,", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Turn Speed: %.2f, %.2f ,%.2f,", vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ).Get());

		if(PTR_LOCALPLAYER->IsInVehicle()) {
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetPosition(vecPosition);
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetMoveSpeed(vecMoveSpeed);
			g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetTurnSpeed(vecTurnSpeed);
			bool bEngineStatus = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetEngineStatus();
			bool bHeadLightsStatus = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetHeadlights();
			int iLightsState = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetLightsState();
			BYTE byteRadioIndex = g_pCore->GetGame()->GetLocalPlayer()->GetVehicleEntity()->GetGameVehicle()->GetRadioStation();

			// Controls
			CControls * pControls = new CControls;
			g_pCore->GetGame()->GetLocalPlayer()->GetControlState(pControls);

			fCurrentLine += 30;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Current Position: %.2f, %.2f ,%.2f", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Move Speed: %.2f, %.2f ,%.2f", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Turn Speed: %.2f, %.2f ,%.2f", vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ).Get());
			
			fCurrentLine += 30;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input RIGHT: %d", (pControls->ucInVehicleMove[0])).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input LEFT: %d", (pControls->ucInVehicleMove[1])).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input UP: %d", (pControls->ucInVehicleMove[2])).Get());
			fCurrentLine += 15;
			g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Vehicle Key-Input DOWN: %d", (pControls->ucInVehicleMove[3])).Get());

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
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Aim Coords: %.2f, %.2f ,%.2f,", vecAimTarget.fX, vecAimTarget.fY, vecAimTarget.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Shot Coords: %.2f, %.2f ,%.2f,", vecShotTarget.fX, vecShotTarget.fY, vecShotTarget.fZ).Get());

		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Ducking: %d,", bDuckingState).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 5, DT_NOCLIP, (bool)true, CString("Rotation: %.2f,", fHeading).Get());
		
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

	bDebugPlayerPresent = true;
}