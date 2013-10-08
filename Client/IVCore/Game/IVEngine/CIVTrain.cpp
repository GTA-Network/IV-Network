//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVTrain.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVTrain.h"

// NOTE: WORK IN PROGRESS; DO NOT CHANGE THIS FILE!!
// Question: do we get the scripting handle or the ivtrain class pointer back?

#include <IV/CIVScript.h>

#include <CCore.h>
extern CCore * g_pCore;

// Disable C4748 warning...
#pragma warning( disable : 4748 )

CIVTrain::CIVTrain() :
	CVehicleEntity(126, CVector3(), 0, 0, 0, 0, 0, 0xFFFFFF)
{
	CVehicleEntity::Destroy();

	// Reset Wagons
	for(BYTE i = 0; i < ARRAY_LENGTH(m_pWagonEntity); i++)
		m_pWagonEntity[i] = NULL;

	// Reset train
	m_pTrain = NULL;
	CIVTrain::m_pVehicle = NULL;
}
void CIVTrain::CreateTrain()
{
	CVehicleEntity * pVehicle = new CVehicleEntity(126, CVector3(), 0.0f, 0, 0, 0, 0, 0xFFFFFF);
	
	m_eTrainType = TYPE_MAIN;
	pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->FindFreeSlot());
	pVehicle->Create();
	
	CLogFile::Printf("[%s] %d",__FUNCTION__, pVehicle->GetScriptingHandle());
	CIVTrain::m_pVehicle = pVehicle;
}

void CIVTrain::CreateWagons(BYTE iWagons)
{
	// Check if we're a wagon
	if(m_eTrainType == TYPE_WAGON)
		return;

	int iWagonCount = 0;
	while(iWagonCount < iWagons)
	{
		CVehicleEntity * pVehicle = new CVehicleEntity(127, CVector3(), 0.0f, 0, 0, 0, 0, 0xFFFFFF);
		m_pWagonEntity[iWagonCount] = new CIVTrain;
		m_pWagonEntity[iWagonCount]->m_eTrainType = TYPE_WAGON;
		m_pWagonEntity[iWagonCount]->m_pVehicle = pVehicle;
		m_pWagonEntity[iWagonCount]->m_pVehicle->SetId(g_pCore->GetGame()->GetVehicleManager()->FindFreeSlot());
		m_pWagonEntity[iWagonCount]->m_pVehicle->Create();
		g_pCore->GetGame()->GetVehicleManager()->Add(m_pWagonEntity[iWagonCount]->m_pVehicle);
		iWagonCount++;
	}
}

bool CIVTrain::IsTrain()
{
	if(m_pVehicle)
		return (bool)((BYTE)(m_pVehicle + 0x1354) == 3);

	return false;
}

void CIVTrain::SetTrainCuriseSpeed(float fSpeed, unsigned int uiHandle)
{
	IVTrain * pTrain = NULL;
	pTrain = GetIVTrain();
	g_pCore->DumpVFTable(*(DWORD *)pTrain,11);

	CIVScript::SetTrainCuriseSpeed(uiHandle ? uiHandle : m_pVehicle->GetScriptingHandle(), fSpeed);
	CIVScript::SetTrainSpeed(uiHandle ? uiHandle : m_pVehicle->GetScriptingHandle(), fSpeed);
	return;
}

IVTrain * CIVTrain::GetIVTrain()
{
	IVVehicle * pVehicle = CVehicleEntity::GetGameVehicle()->GetVehicle();
	if(pVehicle) {
		// Check if our vehicle is a train
		if(*(DWORD *)(pVehicle + 4948) == 3) {
			int result; // eax@1
			int i; // ecx@1

			for (i = *(DWORD *)(pVehicle + 5408); i; i = *(DWORD *)(i + 5408))
				result = i;

			if ((*(DWORD **)result + 324) || (*(DWORD **)result) && *(*(DWORD **)result + 3824))
				IVTrain * pTrain = *(IVTrain **)(*(DWORD **)result + 0xEF4);
			else 
				return NULL;
		}
		return NULL;
	}
	return NULL;
}