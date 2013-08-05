//========== IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ==========
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

CIVTaskComplexNewGetInVehicle::CIVTaskComplexNewGetInVehicle( CIVVehicle * pVehicle, int a2, int a3, unsigned int a4, float a5 ) : CIVTaskComplex()
{
	// Create the task
	Create( );

	// Call the task constructor
	IVVehicle * pGameVehicle = pVehicle->GetVehicle( );
	IVTask * pGameTask = GetTask( );

	_asm	push a5;
	_asm	push a4
	_asm 	push a3;
	_asm 	push a2;
	_asm 	push pGameVehicle;
	_asm 	mov ecx, pGameTask;
	_asm 	call COffsets::FUNC_CTaskComplexNewGetInVehicle__Constructor;
}

CIVTaskComplexNewExitVehicle::CIVTaskComplexNewExitVehicle( CIVVehicle * pVehicle, int iExitType, int a3, int a4 ) : CIVTaskComplex()
{
	// Create the task
	Create( );

	// Call the task constructor
	IVVehicle * pGameVehicle = pVehicle->GetVehicle( );
	IVTask * pGameTask = GetTask( );

	_asm
	{
		push a4
		push a3
		push iExitType
		push pGameVehicle
		mov ecx, pGameTask
		call COffsets::FUNC_CTaskComplexNewExitVehicle__Constructor
	}
}

CIVTaskSimpleCarSetPedOut::CIVTaskSimpleCarSetPedOut( CIVVehicle * pVehicle, int a2, char a3, char a4 ) : CIVTaskSimple()
{
	// Create the task
	Create( );

	// Call the task constructor
	IVVehicle * pGameVehicle = pVehicle->GetVehicle( );
	IVTask * pGameTask = GetTask( );

	_asm 
	{
		push a4
		push a3
		push a2
		push pGameVehicle
		mov ecx, pGameTask
		call COffsets::FUNC_CTaskSimpleCarSetPedOut__Constructor
	}
}

CIVTaskComplexGun::CIVTaskComplexGun(char a2, int a3, int a4, int a5, float fX, float fY, float fZ, int a9, int a10) : CIVTaskComplex()
{
	Create();

	IVTask *pTask = GetTask();
	_asm
	{
		push a10
		push a9
		push fY
		push fX
		push fX
		push a5
		push a4
		push a3
		push a2
		mov ecx, pTask
		call COffsets::FUNC_CTaskComplexGun__Constructor
	}
}

CIVTaskSimpleFireGun::CIVTaskSimpleFireGun(float fX, float fY, float fZ, int a5, int a6, int a7) : CIVTaskSimple()
{
	Create();

	IVTask *pTask = GetTask();
	_asm
	{
		push a7
		push a6
		push a5
		push fZ
		push fY
		push fX
		mov ecx, pTask
		call COffsets::FUNC_CTaskSimpleFireGun__Counstructor
	}
}

CIVTaskSimpleAimGun::CIVTaskSimpleAimGun(float fX, float fY, float fZ, int a5, int a6, int a7) : CIVTaskSimple()
{
	Create();

	IVTask *pTask = GetTask();
	_asm
	{
		push a7
		push a6
		push a5
		push fZ
		push fY
		push fX
		mov ecx, pTask
		call COffsets::FUNC_CTaskSimpleAimGun__Constructor
	}
}

CIVTaskSimpleReloadGun::CIVTaskSimpleReloadGun(unsigned int a2, int a3, int a4) : CIVTaskSimple()
{ 
	Create();

	IVTask *pTask = GetTask();
	_asm
	{
		push a4
		push a3
		push a2
		mov ecx, pTask
		call COffsets::FUNC_CTaskSimpleReloadGun__Constructor
	}
}