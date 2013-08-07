//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
//
// File: IVTask.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "IVTasks.h"
#include <CCore.h>

extern	CCore * g_pCore;

CIVTaskComplexNewGetInVehicle::CIVTaskComplexNewGetInVehicle(CIVVehicle * pVehicle, int a3, int a4, unsigned int a5, float a6) : CIVTaskComplex()
{
	if(pVehicle)
	{

		// Create the task
		Create();

		// Call the task constructor
		IVVehicle * pGameVehicle = pVehicle->GetVehicle();
		IVTask * pTask = GetTask();
		_asm
		{
			push a6
			push a5
			push a4
			push a3
			push pGameVehicle
			mov ecx, pTask
			call COffsets::FUNC_CTaskComplexNewGetInVehicle__Constructor
		}
	}
}

CIVTaskComplexNewExitVehicle::CIVTaskComplexNewExitVehicle(CIVVehicle * pVehicle, int iExitMode, int a4, int a5) : CIVTaskComplex()
{
	if(pVehicle)
	{
		// Create the task
		Create();

		// Call the task constructor
		IVVehicle * pGameVehicle = pVehicle->GetVehicle();
		IVTask * pTask = GetTask();
		_asm
		{
			push a5
			push a4
			push iExitMode
			push pGameVehicle
			mov ecx, pTask
			call COffsets::FUNC_CTaskComplexNewExitVehicle__Constructor
		}
	}
	/*
	    {
    if ( v16 )
        v26 = (int)"GET_OUT_OF_CAR";
    else
        v26 = (int)"GET_OUT_OF_CAR_SHOUT";
    sub_4483E0(v26, 0, 0, 0, -1, 0, 0, 1.0, 0);

			
	*/
}

CIVTaskComplexDie::CIVTaskComplexDie(int a2, int a3, int a4, int a5, float a6, float a7, char a8) : CIVTaskComplex()
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();
	_asm
	{
		push a8
		push a7
		push a6
		push a5
		push a4
		push a3
		push a2
		mov ecx, pTask
		call COffsets::FUNC_CTaskComplexDie__Constructor
	}
}

CIVTaskSimpleDead::CIVTaskSimpleDead(DWORD dwDeathTime, char a3, char a4) : CIVTaskSimple()
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();
	_asm
	{
		push a4
		push a3
		push dwDeathTime
		mov ecx, pTask
		call COffsets::FUNC_CTaskSimpleDead__Constructor
	}
}

CIVTaskSimpleCarSetPedInVehicle::CIVTaskSimpleCarSetPedInVehicle(CIVVehicle * pVehicle, int a3, char a4, char a5) : CIVTaskSimple()
{
	if(pVehicle)
	{
		// Create the task
		Create();

		// Call the task constructor
		IVVehicle * pGameVehicle = pVehicle->GetVehicle();
		IVTask * pTask = GetTask();
		_asm
		{
			push a5
			push a4
			push a3
			push pGameVehicle
			mov ecx, pTask
			call COffsets::FUNC_CTaskSimpleCarSetPedInVehicle__Constructor
		}
	}
}

CIVTaskSimpleCarSetPedOut::CIVTaskSimpleCarSetPedOut(CIVVehicle * pVehicle, int a3, char a4, char a5) : CIVTaskSimple()
{
	if(pVehicle)
	{
		// Create the task
		Create();

		// Call the task constructor
		IVVehicle * pGameVehicle = pVehicle->GetVehicle();
		IVTask * pTask = GetTask();
		_asm
		{
			push a5
			push a4
			push a3
			push pGameVehicle
			mov ecx, pTask
			call COffsets::FUNC_CTaskSimpleCarSetPedOut__Constructor
		}
	}
}

CIVTaskComplexJump::CIVTaskComplexJump(WORD wFlags, int a2)
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();
	_asm
	{
		push a2
		push wFlags
		mov ecx, pTask
		call COffsets::FUNC_CTaskComplexJump__Constructor
	}
}

CIVTaskSimpleTriggerLookAt::CIVTaskSimpleTriggerLookAt(CIVEntity * pEntity, int iTime, int iOffsetBoneTag, CVector3 * pOffsetPos, DWORD dwFlags, float fSpeed, int iBlendTime, int iPriority)
{
	if(pEntity)
	{
		// Create the task
		Create();

		// Call the task constructor
		IVTask * pTask = GetTask();
		_asm
		{
			push iPriority
			push iBlendTime
			push fSpeed
			push dwFlags
			push pOffsetPos
			push iOffsetBoneTag
			push iTime
			push pEntity
			mov ecx, pTask
			call COffsets::FUNC_CTaskSimpleTriggerLookAt__Constructor
		}
	}
}

CIVTaskComplexPlayerOnFoot::CIVTaskComplexPlayerOnFoot()
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();
	_asm
	{
		mov ecx, pTask
		call COffsets::FUNC_CTaskComplexPlayerOnFoot__Constructor
	}
}

CIVTaskSimpleStartWalking::CIVTaskSimpleStartWalking(unsigned int playerIndex, float a1, float a2, float a3, int a4, int a5)
{
	 
	// Create the task
	Create();

	IVTask * pTask = GetTask();
	_asm
	{
		push 50
		push a3
		push a2
		push a1
		push a4
		mov ecx, pTask
		call COffsets::FUNC_CTaskSimpleStartWalking__Constructor
	}
}

CIVTaskSimpleStopWalking::CIVTaskSimpleStopWalking(unsigned int uiPlayerIndex, char iType)
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();
	int fUnkown = (int)8.0; // maybe speed?
	_asm
	{
		push fUnkown
		push 0
		push 0
		push iType
		mov ecx, pTask
		call COffsets::FUNC_CTaskSimpleStopWalking__Constructor
	}
}