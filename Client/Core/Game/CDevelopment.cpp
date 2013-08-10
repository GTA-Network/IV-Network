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
	

	if(bDebugView && g_pCore->GetGame()->GetLocalPlayer() && g_pCore->GetGraphics())
	{
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("LocalPlayer Debug:").Get());
	
		fCurrentLine += 15;

		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPosition(vecPosition);
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetMoveSpeed(vecMoveSpeed);
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetTurnSpeed(vecTurnSpeed);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponAimTarget(vecAimTarget);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetArmHeading(fArmHeading);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetArmUpDown(fArmDown);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponShotSource(vecShotSource);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponShotTarget(vecShotTarget);
		bCrouch = g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPlayerHandle().bDuckState;
		
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Current Position: %.2f, %.2f ,%.2f", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Move Speed: %.2f, %.2f ,%.2f,", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Turn Speed: %.2f, %.2f ,%.2f,", vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Aim Coords: %.2f, %.2f ,%.2f,", vecAimTarget.fX, vecAimTarget.fY, vecAimTarget.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Shot Coords: %.2f, %.2f ,%.2f,", vecShotTarget.fX, vecShotTarget.fY, vecShotTarget.fZ).Get());
		
	}

	if(bDebugPlayerPresent)
	{
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPosition(vecPosition);
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetMoveSpeed(vecMoveSpeed);
		g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetTurnSpeed(vecTurnSpeed);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponAimTarget(vecAimTarget);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetArmHeading(fArmHeading);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetArmUpDown(fArmDown);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponShotSource(vecShotSource);
		g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetContextData()->GetWeaponShotTarget(vecShotTarget);

		bCrouch = g_pCore->GetGame()->GetLocalPlayer()->CNetworkEntity::GetPlayerHandle().bDuckState;
		float fHeading = g_pCore->GetGame()->GetLocalPlayer()->CPlayerEntity::GetRotation();

		// Set him/her beside us
		vecPosition.fX += 5;

		fCurrentLine += 30;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Debug Ped Position: %.2f, %.2f ,%.2f,", vecPosition.fX, vecPosition.fY, vecPosition.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Debug Move Speed: %.2f, %.2f ,%.2f,", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Debug Turn Speed: %.2f, %.2f ,%.2f,", vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Aim Coords: %.2f, %.2f ,%.2f,", vecAimTarget.fX, vecAimTarget.fY, vecAimTarget.fZ).Get());
		fCurrentLine += 15;
		g_pCore->GetGraphics()->DrawText(5, fCurrentLine, D3DCOLOR_ARGB((unsigned char)255, 255, 255, 255), 1.0f, 1, DT_NOCLIP, (bool)true, CString("Shot Coords: %.2f, %.2f ,%.2f,", vecShotTarget.fX, vecShotTarget.fY, vecShotTarget.fZ).Get());
		
		CControls controlState;
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(controlState);

		m_pDebugPlayer->SetControlState(&controlState);
		if(controlState.IsAiming() || controlState.IsFiring())
			bHasAimSyncData = true;
		else
			bHasAimSyncData = false;

		

		// Simulate Jmp
		if(!m_bStoreOnFootSwitch && vecMoveSpeed.Length() > 1.0 && controlState.IsJumping()) {
			unsigned int uiPlayerIndex = m_pDebugPlayer->GetScriptingHandle();
			char iJumpStyle = 1;
			DWORD dwAddress = (g_pCore->GetBase() + 0xB86A20);
			_asm {
				push iJumpStyle
				push uiPlayerIndex
				call dwAddress
			}
		}

		if(bHasAimSyncData)
		{
			m_pDebugPlayer->GetContextData()->SetWeaponAimTarget(vecAimTarget);
			m_pDebugPlayer->GetContextData()->SetArmHeading(fArmHeading);
			m_pDebugPlayer->GetContextData()->SetArmUpDown(fArmDown);

			if(controlState.IsFiring()) {
				g_pCore->GetChat()->Output("Debug dummy is firing!",false);
				m_pDebugPlayer->GetContextData()->SetWeaponShotSource(vecShotSource);
				m_pDebugPlayer->GetContextData()->SetWeaponShotTarget(vecShotTarget);
			}
			else {
				DWORD dwAddress = (g_pCore->GetBase() + 0x8067A0);
				unsigned int uiPlayerIndex = m_pDebugPlayer->GetScriptingHandle();
				_asm push 36;
				_asm push 0;
				_asm push uiPlayerIndex;
				_asm call dwAddress;
				_asm add esp, 0Ch;
			}
		}

		if(m_pDebugPlayer->CNetworkEntity::GetPlayerHandle().bDuckState != bCrouch)
			m_pDebugPlayer->CPlayerEntity::GetPlayerPed()->SetDucking(bCrouch);
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