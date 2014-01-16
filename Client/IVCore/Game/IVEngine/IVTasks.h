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

#include "CIVTask.h"
#include "CIVVehicle.h"
#include <Common.h>

class CIVTaskComplexNewGetInVehicle : public CIVTaskComplex
{
public:
	CIVTaskComplexNewGetInVehicle(CIVVehicle * pVehicle, int a3, int a4, unsigned int a5, float a6);
};

class CIVTaskComplexNewExitVehicle : public CIVTaskComplex
{
public:
	CIVTaskComplexNewExitVehicle(CIVVehicle * pVehicle, int iExitMode, int a4, int a5);
};

class CIVTaskComplexDie : public CIVTaskComplex
{
public:
	CIVTaskComplexDie(int a2, int a3, int a4, int a5, float a6, float a7, char a8);
};

class CIVTaskSimpleDead : public CIVTaskSimple
{
public:
	CIVTaskSimpleDead(DWORD dwDeathTime, char a3, char a4);
};

class CIVTaskSimpleCarSetPedInVehicle : public CIVTaskSimple
{
public:
	CIVTaskSimpleCarSetPedInVehicle(CIVVehicle * pVehicle, int a3, char a4, char a5);
};

class CIVTaskSimpleCarSetPedOut : public CIVTaskSimple
{
public:
	CIVTaskSimpleCarSetPedOut(CIVVehicle * pVehicle, int a3, char a4, char a5);
};

class CIVTaskComplexJump : public CIVTaskComplex
{
public:
	// iFlags (0 = Stand still and jump, 0x40 = Move forward and jump)
	CIVTaskComplexJump(WORD wFlags, int a2); // a2 = CVector4 *
};

class CIVTaskSimpleTriggerLookAt : public CIVTaskSimple
{
public:
	CIVTaskSimpleTriggerLookAt(CIVEntity * pEntity, int iTime, int iOffsetBoneTag, CVector3 * pOffsetPos, DWORD dwFlags = 0x20, float fSpeed = 0.25f, int iBlendTime = 1000, int iPriority = 2);
};

class CIVTaskComplexPlayerOnFoot : public CIVTaskComplex
{
public:
	CIVTaskComplexPlayerOnFoot();
};

class CIVTaskSimpleStopWalking : public CIVTaskSimple
{
public:
	CIVTaskSimpleStopWalking(unsigned int uiPlayerIndex, char iType);
};
 	
class CIVTaskSimpleStartWalking : public CIVTaskSimple
{
public:
 	CIVTaskSimpleStartWalking(unsigned int playerIndex, float a1, float a2, float a3, int a4, int a5);
};

class CIVTaskComplexGun : public CIVTaskComplex
{
public:
	CIVTaskComplexGun(char a2, int a3, int a4, int a5, float fX, float fY, float fZ, int a9, int a10);
};

class CIVTaskSimpleFireGun : public CIVTaskSimple
{
public:
	CIVTaskSimpleFireGun(float fX, float fY, float fZ, int a5, int a6, int a7);
};

class CIVTaskSimpleAimGun : public CIVTaskSimple
{
public:
	CIVTaskSimpleAimGun(float fX, float fY, float fZ, int a5, int a6, int a7);
};

class CIVTaskSimpleReloadGun : public CIVTaskSimple
{
public:
	CIVTaskSimpleReloadGun(unsigned int a2, int a3, int a4);
};

#endif // IVTasks_h