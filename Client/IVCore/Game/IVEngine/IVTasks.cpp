//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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

CIVTaskComplexNewGetInVehicle::CIVTaskComplexNewGetInVehicle(CIVVehicle * pVehicle, int a3, int a4, unsigned int a5, float a6) :
	CIVTaskComplex()
{
	if(pVehicle)
	{
		// Create the task
		Create();

		// Call the task constructor
		IVVehicle * pGameVehicle = pVehicle->GetVehicle();
		IVTask * pTask = GetTask();

		_asm	push a6;
		_asm	push a5;
		_asm	push a4;
		_asm	push a3;
		_asm	push pGameVehicle;
		_asm	mov ecx, pTask;
		_asm	call COffsets::FUNC_CTaskComplexNewGetInVehicle__Constructor;
	}
}

CIVTaskComplexNewExitVehicle::CIVTaskComplexNewExitVehicle(CIVVehicle * pVehicle, int iExitMode, int a4, int a5) :
	CIVTaskComplex()
{
	if(pVehicle)
	{
		// Create the task
		Create();

		// Call the task constructor
		IVVehicle * pGameVehicle = pVehicle->GetVehicle();
		IVTask * pTask = GetTask();
		_asm	push a5;
		_asm	push a4;
		_asm	push iExitMode;
		_asm	push pGameVehicle;
		_asm	mov ecx, pTask;
		_asm	call COffsets::FUNC_CTaskComplexNewExitVehicle__Constructor;
	}
}

CIVTaskComplexDie::CIVTaskComplexDie(int a2, int a3, int a4, int a5, float a6, float a7, char a8) : CIVTaskComplex()
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();

	_asm	push a8;
	_asm	push a7;
	_asm	push a6;
	_asm	push a5;
	_asm	push a4;
	_asm	push a3;
	_asm	push a2;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskComplexDie__Constructor;
}

CIVTaskSimpleDead::CIVTaskSimpleDead(DWORD dwDeathTime, char a3, char a4) : CIVTaskSimple()
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();

	_asm	push a4;
	_asm	push a3;
	_asm	push dwDeathTime;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskSimpleDead__Constructor;
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

		_asm	push a5
		_asm	push a4
		_asm	push a3
		_asm	push pGameVehicle
		_asm	mov ecx, pTask
		_asm	call COffsets::FUNC_CTaskSimpleCarSetPedInVehicle__Constructor
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

		_asm	push a5;
		_asm	push a4;
		_asm	push a3;
		_asm	push pGameVehicle;
		_asm	mov ecx, pTask;
		_asm	call COffsets::FUNC_CTaskSimpleCarSetPedOut__Constructor;
	}
}

CIVTaskComplexJump::CIVTaskComplexJump(WORD wFlags, int a2)
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();

	_asm	push a2;
	_asm	push wFlags;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskComplexJump__Constructor;
}

CIVTaskSimpleTriggerLookAt::CIVTaskSimpleTriggerLookAt(CIVEntity * pEntity, int iTime, int iOffsetBoneTag, CVector3 * pOffsetPos, DWORD dwFlags, float fSpeed, int iBlendTime, int iPriority)
{
	if(pEntity)
	{
		// Create the task
		Create();

		// Call the task constructor
		IVTask * pTask = GetTask();

		_asm	push iPriority;
		_asm	push iBlendTime;
		_asm	push fSpeed;
		_asm	push dwFlags;
		_asm	push pOffsetPos;
		_asm	push iOffsetBoneTag;
		_asm	push iTime;
		_asm	push pEntity;
		_asm	mov ecx, pTask;
		_asm	call COffsets::FUNC_CTaskSimpleTriggerLookAt__Constructor;
	}
}

CIVTaskComplexPlayerOnFoot::CIVTaskComplexPlayerOnFoot()
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();

	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskComplexPlayerOnFoot__Constructor;
}

CIVTaskSimpleStartWalking::CIVTaskSimpleStartWalking(unsigned int playerIndex, float a1, float a2, float a3, int a4, int a5)
{
	// Create the task
	Create();

	IVTask * pTask = GetTask();

	_asm	push 50;
	_asm	push a3;
	_asm	push a2;
	_asm	push a1;
	_asm	push a4;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskSimpleStartWalking__Constructor;
}

CIVTaskSimpleStopWalking::CIVTaskSimpleStopWalking(unsigned int uiPlayerIndex, char iType)
{
	// Create the task
	Create();

	// Call the task constructor
	IVTask * pTask = GetTask();
	int fUnkown = (int)8.0;

	_asm	push fUnkown;
	_asm	push 0;
	_asm	push 0;
	_asm	push iType;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskSimpleStopWalking__Constructor;
}

CIVTaskComplexGun::CIVTaskComplexGun(char a2, int a3, int a4, int a5, float fX, float fY, float fZ, int a9, int a10) : CIVTaskComplex()
{
	Create();

	IVTask *pTask = GetTask();

	_asm	push a10;
	_asm	push a9;
	_asm	push fY;
	_asm	push fX;
	_asm	push fX;
	_asm	push a5;
	_asm	push a4;
	_asm	push a3;
	_asm	push a2;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskComplexGun__Constructor;
}

CIVTaskSimpleFireGun::CIVTaskSimpleFireGun(float fX, float fY, float fZ, int a5, int a6, int a7) : CIVTaskSimple()
{
	Create();

	IVTask *pTask = GetTask();

	_asm	push a7;
	_asm	push a6;
	_asm	push a5;
	_asm	push fZ;
	_asm	push fY;
	_asm	push fX;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskSimpleFireGun__Counstructor; 
}

CIVTaskSimpleAimGun::CIVTaskSimpleAimGun(float fX, float fY, float fZ, int a5, int a6, int a7) : CIVTaskSimple()
{
	Create();

	IVTask *pTask = GetTask();

	_asm	push a7;
	_asm	push a6;
	_asm	push a5;
	_asm	push fZ;
	_asm	push fY;
	_asm	push fX;
	_asm	mov ecx, pTask;
	_asm	call COffsets::FUNC_CTaskSimpleAimGun__Constructor;
}

CIVTaskSimpleReloadGun::CIVTaskSimpleReloadGun(unsigned int a2, int a3, int a4) : CIVTaskSimple()
{ 
	Create();

	IVTask *pTask = GetTask();

	_asm	push a4
	_asm	push a3
	_asm	push a2
	_asm	mov ecx, pTask
	_asm	call COffsets::FUNC_CTaskSimpleReloadGun__Constructor
}