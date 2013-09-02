//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
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

CIVTrain::CIVTrain() : CVehicleEntity(126, CVector3(), 0, 0, 0 , 0, 0)
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
	CVehicleEntity * pVehicle = new CVehicleEntity(126, CVector3(), 0.0f, 0, 0, 0, 0);
	
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
		CVehicleEntity * pVehicle = new CVehicleEntity(127, CVector3(), 0.0f, 0, 0, 0, 0);
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
	CIVScript::SetTrainCuriseSpeed(uiHandle ? uiHandle : m_pVehicle->GetScriptingHandle(), fSpeed);
	CIVScript::SetTrainSpeed(uiHandle ? uiHandle : m_pVehicle->GetScriptingHandle(), fSpeed);
	return;

	//int __cdecl sub_995410(m_pVehicle, fSpeed)

	/*

	v2 = (signed int)ffloor(fSpeed);
	*(_BYTE *)(a1 + 0xEBF) = v2;

	result = (IVTrain *)GetIVTrainClassFromVehicle(m_pVehicle); // A5F910
	if ( result )
		result->byte27 = v2;

	*/

	signed int v2; // ebx@1
	int result; // eax@1

	v2 = (signed int)floor(fSpeed);
	*(BYTE *)(m_pVehicle + 0xEBF) = v2;

	DWORD GETTRAINHANDLE = (g_pCore->GetBase() + 0xA5F910);

	_asm mov ecx, m_pVehicle;
	_asm mov eax, ecx;
	_asm push eax;
	_asm call GETTRAINHANDLE;
	_asm add esp, 4;
	_asm mov ecx, [eax];
	//_asm mov dword ptr m_pTrain, ecx;
	_asm retn;

	// Update the train speed
	if(m_pTrain)
		m_pTrain->byte27 = v2;
}