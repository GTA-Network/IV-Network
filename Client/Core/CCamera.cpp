//========== IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ==========
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
#include <CCore.h>

extern CCore * g_pCore;

CCamera::CCamera()
{
	// Grab camera pointer.
	IVCam *pCamera = NULL;
	void * pUnknow = (void **)(g_pCore->GetBase() + 0xF21A6C);
	_asm
	{
		mov ecx, pUnknow
        mov eax, [ecx+0Ch]
		mov pCamera, eax
	}

	IVCamPool *pPool = *(IVCamPool **)(g_pCore->GetBase() + 0x1618020);
	DWORD dwAddress = (g_pCore->GetBase() + 0x447230);
	unsigned int uiHandle = 0;
	_asm
	{
		push pCamera
		mov ecx, pPool
		call dwAddress
		mov uiHandle, eax
	}
	m_uiGameCamIndex = uiHandle;

	m_pGameCam = new CIVCam();
	m_pGameCam->SetCam(pCamera);

	// Create scripting camera
	CIVScript::CreateCam( 14, &m_uiScriptingIndex );
	CIVScript::SetCamPropagate( m_uiScriptingIndex, true );

	m_bUsingScriptingCam = false;
}

CCamera::~CCamera()
{
	CIVScript::DestroyCam(m_uiScriptingIndex);
}

void CCamera::SetCameraPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		CIVScript::SetCamActive( m_uiScriptingIndex, true );
		CIVScript::ActivateScriptedCams( true, true );
		CIVScript::SetCamActive( m_uiGameCamIndex, false );
		m_bUsingScriptingCam = true;
	}

	CIVScript::SetCamPos( m_uiScriptingIndex, vecPosition.fX, vecPosition.fY, vecPosition.fZ );
}

void CCamera::GetCameraPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		CIVScript::SetCamActive( m_uiScriptingIndex, true );
		CIVScript::ActivateScriptedCams( true, true );
		CIVScript::SetCamActive( m_uiGameCamIndex, false );
		m_bUsingScriptingCam = true;
	}

	CIVScript::GetCamPos( m_uiScriptingIndex, &vecPosition.fX, &vecPosition.fY, &vecPosition.fZ );
}

void CCamera::SetLookAtPosition(CVector3 &vecPosition)
{
	if(!m_bUsingScriptingCam)
	{
		CIVScript::SetCamActive( m_uiScriptingIndex, true );
		CIVScript::ActivateScriptedCams( true, true );
		CIVScript::SetCamActive( m_uiGameCamIndex, false );
		m_bUsingScriptingCam = true;
	}

	CGameFunction::LoadWorldAtPosition(vecPosition);

	CIVScript::PointCamAtCoord( m_uiScriptingIndex, vecPosition.fX, vecPosition.fY, vecPosition.fZ );
}

void CCamera::SetCamBehindPed(unsigned int uiPed)
{
	if(m_bUsingScriptingCam)
	{
		CIVScript::SetCamActive( m_uiScriptingIndex, false );
		CIVScript::ActivateScriptedCams( false, false );
		CIVScript::SetCamActive( m_uiGameCamIndex, true );
		m_bUsingScriptingCam = false;
	}

	CIVScript::SetCamBehindPed( uiPed );
}

void CCamera::GetAimPosition(CVector3 *vecPosition)
{
	if(m_bUsingScriptingCam)
	{
		CIVScript::SetCamActive( m_uiScriptingIndex, false );
		CIVScript::ActivateScriptedCams( false, false );
		CIVScript::SetCamActive( m_uiGameCamIndex, true );
		m_bUsingScriptingCam = false;
	}

	// Define all vectors.
	CVector3 vecCamPosition;
	CVector3 vecCamForward;

	// Get all data from game camera.
	CIVScript::GetCamPos(m_uiGameCamIndex, &vecCamPosition.fX, &vecCamPosition.fY, &vecCamPosition.fZ);

	// Get cam forward.
	vecCamForward = CVector3(m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fX,m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fY,m_pGameCam->GetCam()->m_data1.m_matMatrix.vecForward.fZ);

	// Scale calc.
	float fScale = 10.0f;
	vecPosition->fX = (vecCamPosition.fX + ( vecCamForward.fX * fScale ));
	vecPosition->fY = (vecCamPosition.fY + ( vecCamForward.fY * fScale ));
	vecPosition->fZ = (vecCamPosition.fZ + ( vecCamForward.fZ * fScale ));
}

bool CCamera::IsOnScreen(const CVector3& vecPosition)
{
    CVector3 vecCamPos;
    m_pGameCam->GetPosition(vecCamPos);

    CVector3 vecCamLookAt;
    GetAimPosition(&vecCamLookAt);

    D3DXMATRIX matView;
    D3DXMatrixLookAtLH(&matView, CVEC_TO_D3DVEC(vecCamPos), CVEC_TO_D3DVEC(vecCamLookAt), &D3DXVECTOR3(0, 0, 1));

    D3DVIEWPORT9 viewport;
    g_pCore->GetGraphics()->GetDevice()->GetViewport(&viewport);

    DWORD dwLenX = viewport.Width;
    DWORD dwLenY = viewport.Height;

    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, m_pGameCam->GetCam()->m_data1.m_fFOV, (float)dwLenX / (float)dwLenY, m_pGameCam->GetCam()->m_data1.m_fNear, m_pGameCam->GetCam()->m_data1.m_fFar); 

    D3DXMATRIX matWorld;
    D3DXMatrixIdentity(&matWorld);

    D3DXVECTOR3 vecSPos;
    D3DXVec3Project(&vecSPos, CVEC_TO_D3DVEC(vecPosition), &viewport, &matProj, &matView, &matWorld);

    return ( vecSPos.z < 1.f );
}
