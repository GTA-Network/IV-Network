//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CDevelopment.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CDevelopment.h"
#include <CCore.h>
extern CCore * g_pCore;

CDevelopment::CDevelopment()
{
	bDebugView = false;
	bDebugPlayerPresent = false;
	bHasAimSyncData = false;

	m_bStoreOnFootSwitch = false;
	m_iOldMoveStyle = 0;
}

CDevelopment::~CDevelopment()
{

}

void CDevelopment::Process()
{
	float fCurrentLine = 325;
	CVector3 vecPosition, vecMoveSpeed, vecTurnSpeed, vecAimTarget, vecShotSource, vecShotTarget;
	float fArmHeading, fArmDown, fHeading;
	bool bDuckingState;

	if(bDebugView && g_pCore->GetGame()->GetLocalPlayer() && g_pCore->GetGraphics())
	{
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("LocalPlayer Debug:").Get());

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
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Current Position: %.2f, %.2f ,%.2f", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Move Speed: %.2f, %.2f ,%.2f,", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Turn Speed: %.2f, %.2f ,%.2f,", vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ).Get());
		
		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Aim Coords: %.2f, %.2f ,%.2f,", vecAimTarget.fX, vecAimTarget.fY, vecAimTarget.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Shot Coords: %.2f, %.2f ,%.2f,", vecShotTarget.fX, vecShotTarget.fY, vecShotTarget.fZ).Get());

		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Ducking: %d,", bDuckingState).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Rotation: %.2f,", fHeading).Get());
		
	}

	if(bDebugPlayerPresent)
	{
		CControls controlState;
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(controlState);

		m_pDebugPlayer->SetControlState(&controlState);
		if(controlState.IsAiming() || controlState.IsFiring())
			bHasAimSyncData = true;
		else
			bHasAimSyncData = false;
		
		m_pDebugPlayer->StoreIVSynchronization(bHasAimSyncData,true,g_pCore->GetGame()->GetLocalPlayer());
	}
}

void CDevelopment::CreateDebugPlayer()
{
	CVector3 vecCreatePos; 
	g_pCore->GetGame()->GetLocalPlayer()->GetPosition(vecCreatePos);

	m_pDebugPlayer = new CPlayerEntity(false);
	if(m_pDebugPlayer)
	{
		m_pDebugPlayer->Create();
		m_pDebugPlayer->Teleport(vecCreatePos);
		m_pDebugPlayer->SetModel(21);
	}

	bDebugPlayerPresent = true;
}