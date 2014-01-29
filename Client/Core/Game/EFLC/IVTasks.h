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

#ifndef IVTasks_h
#define IVTasks_h

#include <Common.h>
#include "../GameCommon.h"

#include "CTask.h"
#include "CVehicle.h"


_GAME_BEGIN

class CTaskComplexNewGetInVehicle : public CTaskComplex
{
public:
	CTaskComplexNewGetInVehicle(CVehicle * pVehicle, int a3, int a4, unsigned int a5, float a6);
};

class CTaskComplexNewExitVehicle : public CTaskComplex
{
public:
	CTaskComplexNewExitVehicle(CVehicle * pVehicle, int iExitMode, int a4, int a5);
};

class CTaskComplexDie : public CTaskComplex
{
public:
	CTaskComplexDie(int a2, int a3, int a4, int a5, float a6, float a7, char a8);
};

class CTaskSimpleDead : public CTaskSimple
{
public:
	CTaskSimpleDead(DWORD dwDeathTime, char a3, char a4);
};

class CTaskSimpleCarSetPedInVehicle : public CTaskSimple
{
public:
	CTaskSimpleCarSetPedInVehicle(CVehicle * pVehicle, int a3, char a4, char a5);
};

class CTaskSimpleCarSetPedOut : public CTaskSimple
{
public:
	CTaskSimpleCarSetPedOut(CVehicle * pVehicle, int a3, char a4, char a5);
};

class CTaskComplexJump : public CTaskComplex
{
public:
	// iFlags (0 = Stand still and jump, 0x40 = Move forward and jump)
	CTaskComplexJump(WORD wFlags, int a2); // a2 = CVector4 *
};

class CTaskSimpleTriggerLookAt : public CTaskSimple
{
public:
	CTaskSimpleTriggerLookAt(CEntity * pEntity, int iTime, int iOffsetBoneTag, CVector3 * pOffsetPos, DWORD dwFlags = 0x20, float fSpeed = 0.25f, int iBlendTime = 1000, int iPriority = 2);
};

class CTaskComplexPlayerOnFoot : public CTaskComplex
{
public:
	CTaskComplexPlayerOnFoot();
};

class CTaskSimpleStopWalking : public CTaskSimple
{
public:
	CTaskSimpleStopWalking(unsigned int uiPlayerIndex, char iType);
};
 	
class CTaskSimpleStartWalking : public CTaskSimple
{
public:
 	CTaskSimpleStartWalking(unsigned int playerIndex, float a1, float a2, float a3, int a4, int a5);
};

class CTaskComplexGun : public CTaskComplex
{
public:
	CTaskComplexGun(char a2, int a3, int a4, int a5, float fX, float fY, float fZ, int a9, int a10);
};

class CTaskSimpleFireGun : public CTaskSimple
{
public:
	CTaskSimpleFireGun(float fX, float fY, float fZ, int a5, int a6, int a7);
};

class CTaskSimpleAimGun : public CTaskSimple
{
public:
	CTaskSimpleAimGun(float fX, float fY, float fZ, int a5, int a6, int a7);
};

class CTaskSimpleReloadGun : public CTaskSimple
{
public:
	CTaskSimpleReloadGun(unsigned int a2, int a3, int a4);
};

_GAME_END

#endif // IVTasks_h