//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: IVManagement.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "IVManagement.h"
#include <Ptrs.h>
#include <IV/CIVScript.h>

IVManagement::IVManagement()
{
	// Reset trains
	memset(m_pTrains,NULL,sizeof(InternalTrainHandle));
}

void IVManagement::CreateTrain(CVector3 vecPosition, BYTE iWagons, float fSpeed, bool bDirection)
{
	// Find free slot for our train
	BYTE iTrainSlot = GetFreeTrainSlot();

	// Max trains reached
	if(iTrainSlot == 255)
		return;

	// Create the train
	m_pTrains[iTrainSlot].pCIVTrain = new CIVTrain;
	m_pTrains[iTrainSlot].pCIVTrain->CreateTrain();
	m_pTrains[iTrainSlot].pTrain = m_pTrains[iTrainSlot].pCIVTrain->CIVTrain::m_pTrain;
	m_pTrains[iTrainSlot].pVehicle = m_pTrains[iTrainSlot].pCIVTrain->CIVTrain::m_pVehicle;
	m_pTrains[iTrainSlot].pCIVTrain->CreateWagons(iWagons);
	m_pTrains[iTrainSlot].m_uiScriptingHandle = m_pTrains[iTrainSlot].pVehicle->GetScriptingHandle();

	// Mark train as used
	g_pCore->GetGame()->GetVehicleManager()->Add(m_pTrains[iTrainSlot].pCIVTrain->GetVehicleEntity());
	m_pTrains[iTrainSlot].m_bInitialised = true;

	// Create ProcessThread
	g_pCore->GetGame()->CreateInternalThread(reinterpret_cast<DWORD>((LPTHREAD_START_ROUTINE)ProcessTrain), &m_pTrains[iTrainSlot], NULL, 0, CString("IVManagement::ProcessTrain_%d",iTrainSlot).Get(), "Processing Thread..");
}

void IVManagement::ProcessTrain(LPVOID lpParameter) 
{
	InternalTrainHandle *pTrainHandle = reinterpret_cast<InternalTrainHandle *>(lpParameter); 
	float fSpeed = 20.0f;
	
	// Wait until the train finished initialise
	Sleep(3000);

	PTR_CHAT->Print("Train starting driving away..");
	CLogFile::Printf("Train starting driving away..");

	// Update train speed
	pTrainHandle->pCIVTrain->SetTrainCuriseSpeed(fSpeed,pTrainHandle->pCIVTrain->m_pVehicle->GetScriptingHandle());

	// Now process the wagons
	int iWagonProcess = 0;
	while(iWagonProcess < pTrainHandle->pCIVTrain->GetMaxWagonCount())
	{
		// Leave this wagon(because it's not created yet
		if(!pTrainHandle->pCIVTrain->GetVehicleWagon(iWagonProcess))
			continue;

		PTR_CHAT->Print(CString("Train Wagon %d starting driving away", iWagonProcess));
		CLogFile::Printf("Train Wagon %d starting driving away",iWagonProcess);

		// Let the drive start driving forward
		Sleep(50*fSpeed);

		// Let the wagon start drive away..
		pTrainHandle->pCIVTrain->GetVehicleWagon(iWagonProcess)->SetTrainCuriseSpeed(fSpeed);

		// Add
		iWagonProcess++;
	}

	// TODO: to be continued...
	while(true)
		Sleep(100);
}

BYTE IVManagement::GetFreeTrainSlot()
{
	for(BYTE i = 0; i < MAX_TRAINS; i++)
		if(!m_pTrains[i].m_bInitialised || !&m_pTrains[i])
			return i;

	return 255;
}

BYTE IVManagement::GetTrainCount()
{
	BYTE byteCount = 0;
	for(BYTE i = 0; i < MAX_TRAINS; i++)
		if(&m_pTrains[i] && m_pTrains[i].m_bInitialised)
			byteCount++;

	return byteCount;
}

void IVManagement::Pulse()
{
	if(g_pCore->GetGame()->GetLocalPlayer())
	{
		//float fHealth = PTR_LOCALPLAYER->GetHealth();

		//CIVScript::DrawRect(20, 20, (fHealth * (500)) / 100, 200, 0, 0, 0, 255);
	}
}