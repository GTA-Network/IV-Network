//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CCamera.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include <Common.h>

#include "CCamera.h"
#include "IV/CIVScript.h"
#include <Ptrs.h>

CCamera::CCamera() :
	m_bUsingScriptingCam(false)
{
	// Create the game cam instance
	m_pGameCam = new CIVCam(*(IVCam**) ((unsigned char*) COffsets::RAGE_Camera__UnkownVoidPtr + 12));

	// Create the script cam
	unsigned int uiScriptCam;
	CIVScript::CreateCam(14, &uiScriptCam);
	CIVScript::SetCamPropagate(uiScriptCam, true);

	// Create the script cam instance
	m_pScriptCam = new CIVCam(g_pCore->GetGame()->GetPools()->GetCamPool()->AtHandle(uiScriptCam));
}

CCamera::~CCamera()
{
	// Remove the camera
	CIVScript::DestroyCam(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()));
}

void CCamera::SetCameraPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		CIVScript::ActivateScriptedCams(true, true);
		CIVScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = true;
	}

	CIVScript::SetCamPos(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
}

void CCamera::GetCameraPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		CIVScript::ActivateScriptedCams(true, true);
		CIVScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = true;
	}

	CIVScript::GetCamPos(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), &vecPosition.fX, &vecPosition.fY, &vecPosition.fZ);
}

void CCamera::SetLookAtPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		CIVScript::ActivateScriptedCams(true, true);
		CIVScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = true;
	}

	CGameFunction::LoadWorldAtPosition(vecPosition);

	CIVScript::PointCamAtCoord(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
}

void CCamera::SetCamBehindPed(unsigned int uiPed)
{
	if(m_bUsingScriptingCam)
	{
		CIVScript::ActivateScriptedCams(false, false);
		CIVScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = false;
	}

	CIVScript::SetCamBehindPed(uiPed);
}

void CCamera::GetAimPosition(CVector3 *vecPosition)
{
	if(m_bUsingScriptingCam)
	{
		CIVScript::ActivateScriptedCams(false, false);
		CIVScript::SetCamActive(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), true);
		m_bUsingScriptingCam = false;
	}

	// Define all vectors.
	CVector3 vecCamPosition;
	CVector3 vecCamForward;

	// Get all data from game camera.
	CIVScript::GetCamPos(g_pCore->GetGame()->GetPools()->GetCamPool()->HandleOf(m_pScriptCam->GetCam()), &vecCamPosition.fX, &vecCamPosition.fY, &vecCamPosition.fZ);

	// Get cam forward.
	vecCamForward = CVector3(m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fX,m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fY,m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fZ);

	// Scale calc.
	CVector3 vecFinalCamLookAt = Math::GetOffsetDegrees(vecCamPosition,vecCamForward);
	float fScale = (vecFinalCamLookAt.Length()/2);

	vecPosition->fX = (vecCamPosition.fX + (vecCamForward.fX * fScale));
	vecPosition->fY = (vecCamPosition.fY + (vecCamForward.fY * fScale));
	vecPosition->fZ = (vecCamPosition.fZ + (vecCamForward.fZ * fScale));
}

void CCamera::GetLookAt(CVector3& vecLookAt)
{
	CIVCam * pGameCam = GetGameCam();
	CVector3 vecCamPosition;
	CVector3 vecCamForward;
	CVector3 vecCamLookAt;

	pGameCam->GetPosition(vecCamPosition);
	pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.ToVector3(vecCamForward);
	vecCamLookAt.fX = vecCamPosition.fX + vecCamForward.fX;
	vecCamLookAt.fY = vecCamPosition.fY + vecCamForward.fY;
	vecCamLookAt.fZ = vecCamPosition.fZ + vecCamForward.fZ;

	CVector3 vecFinalCamLookAt = Math::GetOffsetDegrees(vecCamPosition, vecCamForward);
	float fScale = (vecFinalCamLookAt.Length() / 2);

	vecCamLookAt.fX = vecCamPosition.fX + (vecCamForward.fX * fScale);
	vecCamLookAt.fY = vecCamPosition.fY + (vecCamForward.fY * fScale);
	vecCamLookAt.fZ = vecCamPosition.fZ + (vecCamForward.fZ * fScale);

	memcpy(&vecLookAt, &vecCamLookAt, sizeof(CVector3));
}

bool CCamera::IsOnScreen(const CVector3& vecPosition)
{
	CVector3 vecCamPos;
	GetGameCam()->GetPosition(vecCamPos);

	CVector3 vecCamLookAt;
	GetLookAt(vecCamLookAt);

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, CVEC_TO_D3DVEC(vecCamPos), CVEC_TO_D3DVEC(vecCamLookAt), CVEC_TO_D3DVEC(CVector3(0, 0, 1)));

	D3DVIEWPORT9 viewport;
	g_pCore->GetGraphics()->GetDevice()->GetViewport(&viewport);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, GetGameCam()->GetCam()->m_data1.m_fFOV, (float) viewport.Width / (float) viewport.Height, GetGameCam()->GetCam()->m_data1.m_fNear, GetGameCam()->GetCam()->m_data1.m_fFar);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXVECTOR3 vecSPos;
	D3DXVec3Project(&vecSPos, CVEC_TO_D3DVEC(vecPosition), &viewport, &matProj, &matView, &matWorld);

	return (vecSPos.z < 1.f);
}
