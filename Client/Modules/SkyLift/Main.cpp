//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: Main.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef _MODULE
#define _MODULE

#include <Common.h>
#include <CString.cpp>
DWORD dwFunctionInvokeOffset;

// HACKY
#include "../../IVCore/IV/CIVScript.h"
#include "../../IVCore/IV/CIVScript_FunctionContext.h"
#include "../../IVCore/IV/CIVScript_FunctionInvoke.h"
#include "../../IVCore/IV/CIVScript_FunctionInvoke.cpp"
#include "../../IVCore/IV/CIVScript_FunctionList.h"
#include "../../IVCore/IV/CIVScriptEnums.h"
#include "../../IVCore/IV/CIVScriptHook.h"

#endif // _MODULE


EXPORT void SetOffset(DWORD dwOffset)
{
	dwFunctionInvokeOffset = dwOffset;
	CIVScript_NativeInvoke::InitialiseOffset(dwFunctionInvokeOffset);
}
/*
============================================================== MODULE =====================================================================
																																				*/

#define BUTTON_STICK_LEFT 0x12

unsigned int_attach ;
void LocateVehicle(float warp_x, float warp_y, float warp_z)
{
	int_attach = CIVScript::GetClosestCar(warp_x, warp_y, warp_z, 15.00000000, 0, 70);
	if (!CIVScript::DoesVehicleExist(int_attach))
	{
		int_attach = CIVScript::GetClosestCar(warp_x, warp_y, warp_z, 15.00000000, 0, 69);
	}
	if (!CIVScript::DoesVehicleExist(int_attach))
	{
		int_attach = CIVScript::GetClosestCar(warp_x, warp_y, warp_z, 15.00000000, 0, 71);
	}
}

void pickupVehicle(void)
{
	float locate_x, locate_y, locate_z;
	CIVScript::GetCharCoordinates(0, &locate_x, &locate_y, &locate_z);
	LocateVehicle(locate_x, locate_y, locate_z);
	if (CIVScript::DoesVehicleExist(int_attach))
	{
		
	}
}
void Module_Initialise()
{
	return;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, void * pReserved)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			dwFunctionInvokeOffset = NULL;
			Module_Initialise();
			break;
		}

	case DLL_PROCESS_DETACH:
		{

			break;
		}
	}
}