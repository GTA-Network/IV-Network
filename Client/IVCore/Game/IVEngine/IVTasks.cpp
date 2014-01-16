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