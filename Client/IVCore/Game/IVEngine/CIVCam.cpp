//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVCam.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVCam.h"

CIVCam::CIVCam() :
	m_pCam(NULL)
{
}

CIVCam::CIVCam(IVCam * pCam) :
	m_pCam(pCam)
{
}

CIVCam::~CIVCam()
{
}

void CIVCam::SetPosition(const CVector3& vecPosition)
{
	if(m_pCam)
		memcpy(&m_pCam->m_data1.m_matMatrix.vecPosition, &vecPosition, sizeof(CVector3));
}

void CIVCam::GetPosition(CVector3& vecPosition)
{
	if(m_pCam)
		memcpy(&vecPosition, &m_pCam->m_data1.m_matMatrix.vecPosition, sizeof(CVector3));
}