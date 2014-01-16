/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
		m_pWagonEntity[i] = nullptr;

	// Reset train
	m_pTrain = nullptr;
	CIVTrain::m_pVehicle = nullptr;
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
	IVTrain * pTrain = nullptr;
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
				return nullptr;
		}
		return nullptr;
	}
	return nullptr;
}