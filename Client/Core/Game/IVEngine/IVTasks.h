//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: IVTasks.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef IVTasks_h
#define IVTasks_h

#include "CIVTask.h"
#include "CIVVehicle.h"
#include <Common.h>

class CIVTaskComplexNewGetInVehicle : public CIVTaskComplex {
public:
	CIVTaskComplexNewGetInVehicle(CIVVehicle * pVehicle, int a2, int a3, unsigned int a4, float a5);
};

class CIVTaskComplexNewExitVehicle : public CIVTaskComplex {
public:
	CIVTaskComplexNewExitVehicle(CIVVehicle * pVehicle, int iExitType, int a3, int a4);
};

class CIVTaskSimpleCarSetPedOut : public CIVTaskSimple {
public:
	CIVTaskSimpleCarSetPedOut(CIVVehicle * pVehicle, int a2, char a3, char a4);
};

class CIVTaskComplexGun : public CIVTaskComplex {
public:
	CIVTaskComplexGun(char a2, int a3, int a4, int a5, float fX, float fY, float fZ, int a9, int a10);
};

class CIVTaskSimpleFireGun : public CIVTaskSimple {
public:
	CIVTaskSimpleFireGun(float fX, float fY, float fZ, int a5, int a6, int a7);
};

class CIVTaskSimpleAimGun : public CIVTaskSimple {
public:
	CIVTaskSimpleAimGun(float fX, float fY, float fZ, int a5, int a6, int a7);
};

class CIVTaskSimpleReloadGun : public CIVTaskSimple {
public:
	CIVTaskSimpleReloadGun(unsigned int a2, int a3, int a4);
};

#endif // IVTasks_h