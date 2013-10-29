//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CWeaponHandler.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CWeaponHandler.h"
#include <CCore.h>
extern CCore * g_pCore;

DWORD      dwFunctionAddress = NULL;
IVPed    * g_pIKPed = NULL;
float      g_fArmHeading = 0.0f;
float      g_fArmUpDown = 0.0f;
IVPed    * g_pWeaponPed = NULL;
CVector3 * g_vecWeaponShotSource = NULL;
CVector3 * g_vecWeaponShotTarget = NULL;
CVector3 * g_vecAimTarget = NULL;

void StoreAimTarget(IVPed * pPed, CVector3 * vecWeaponTarget)
{
	// Do we have a valid ped pointer and target pointer?
	if(pPed && vecWeaponTarget)
	{
		// Get the remote players context data
		CContextData * pContextData = CContextDataManager::GetContextData((IVPlayerPed *)pPed);

		// Do we have a valid context data?
		if(pContextData)
		{
			// Is this the local player?
			if(pContextData->GetPlayerInfo()->GetPlayerNumber() == 0)
			{
				pContextData->SetWeaponAimTarget(*vecWeaponTarget);
			}
			else
			{
				pContextData->GetWeaponAimTarget(*vecWeaponTarget);
			}
		}
		else
			CLogFile::PrintDebugf("StoreAimTarget Warning: Invalid Player Ped");
	}
}
void StoreArmHeadingUpDown(IVPed * pPed, float * fArmHeading, float * fArmUpDown)
{
	// Do we have a valid ped pointer?
	if(pPed)
	{
		// Get the remote players context data
		CContextData * pContextData = CContextDataManager::GetContextData((IVPlayerPed *)pPed);

		// Do we have a valid context data?
		if(pContextData)
		{
			// Is this the local player?
			if(pContextData->GetPlayerInfo()->GetPlayerNumber() == 0)
			{
				pContextData->SetArmHeading(*fArmHeading);
				pContextData->SetArmUpDown(*fArmUpDown);
			}
			else
			{
				pContextData->GetArmHeading(*fArmHeading);
				pContextData->GetArmUpDown(*fArmUpDown);
			}
		}
		else
			CLogFile::PrintDebugf("StoreArmHeadingUpDown Warning: Invalid Player Ped");
	}
}

void StoreShotSourceTarget(IVPed * pPed, CVector3 * pWeaponSource, CVector3 * pWeaponTarget)
{
	// Do we have a valid ped pointer, source pointer and target pointer?
	if(pPed && pWeaponSource && pWeaponTarget)
	{
		// Get the remote players context data
		CContextData * pContextData = CContextDataManager::GetContextData((IVPlayerPed *)pPed);

		// Do we have a valid context data?
		if(pContextData)
		{
			// Is this the local player?
			if(pContextData->GetPlayerInfo()->GetPlayerNumber() == 0)
			{
				pContextData->SetWeaponShotSource(*pWeaponSource);
				pContextData->SetWeaponShotTarget(*pWeaponTarget);
			}
			else
			{
				pContextData->GetWeaponShotSource(*pWeaponSource);
				pContextData->GetWeaponShotTarget(*pWeaponTarget);
			}
		}
		else
			CLogFile::PrintDebugf("StoreShotSourceTarget Warning: Invalid Player Ped");
	}
}

_declspec(naked) void CIKManager__AimWeapon()
{
	_asm	push ebp;
	_asm	mov ebp, esp;
	_asm	mov eax, [ecx+40h]; // CIKManager + 0x40 = CPed * pPed
	_asm	mov g_pIKPed, eax;
	_asm	mov eax, [ebp+8];
	_asm	mov g_vecAimTarget, eax;
	_asm	pop ebp;
	_asm	pushad;

	StoreAimTarget(g_pIKPed, g_vecAimTarget);

	_asm	popad;
	_asm	push ebp;
	_asm	mov ebp, esp;
	_asm	and esp, 0FFFFFFF0h;
	_asm	jmp COffsets::IV_Hook__CIKManager_AimWeapon__JmpBack;
}

// Hook for CIkManager::PointArms func to sync the arm heading and up/down for aim sync
DWORD dwCallFrom;
_declspec(naked) void CIkManager__PointArms_Hook()
{
	// Get the ped pointer from the ik manager
	_asm	mov eax, [ecx+40h] // CIkManager + 0x40 = CPed * pPed
	_asm	mov g_pIKPed, eax
	// Get the function arguments
	_asm	mov eax, [esp+0];
	_asm	mov dwCallFrom, eax;
	_asm	mov eax, [esp+4];
	_asm	mov g_fArmHeading, eax;
	_asm	mov eax, [esp+8];
	_asm	mov g_fArmUpDown, eax;
	_asm	pushad;

	// Store our values
	CLogFile::Printf("Renderingfrom: 0x%p",dwCallFrom);
	StoreArmHeadingUpDown(g_pIKPed, &g_fArmHeading, &g_fArmUpDown);

	_asm	popad;
	// Store our values in case they have been changed
	_asm	mov eax, g_fArmHeading;
	_asm	mov [esp+4], eax;
	_asm	mov eax, g_fArmUpDown;
	_asm	mov [esp+8], eax;
	// Execute original code we overwrote for the hook
	_asm	movss xmm0, [esp+4];
	// Jump back to the original function
	_asm	jmp COffsets::IV_Hook__CIKManager_PointArms__JmpBack;
}

// Hook for CWeapon::Fire func to sync the shot source and target vectors for shot sync
_declspec(naked) void CWeapon__Fire_Hook()
{
	_asm	push ebp;
	_asm	mov ebp, esp;
	// Get the ped pointer and other function arguments
	_asm	mov eax, [ebp+8h];
	_asm	mov g_pWeaponPed, eax;
	// [ebp+0Ch] = pSourceMatrix (Matrix34 *)
	_asm	mov eax, [ebp+10h];
	_asm	mov g_vecWeaponShotSource, eax;
	_asm	mov eax, [ebp+14h];
	_asm	mov g_vecWeaponShotTarget, eax;
	_asm	pop ebp;
	_asm	pushad;

	// Store our values
	StoreShotSourceTarget(g_pWeaponPed, g_vecWeaponShotSource, g_vecWeaponShotTarget);

	_asm	popad;
	// Execute original code we overwrote for the hook
	_asm	push ebp;
	_asm	mov ebp, esp;
	_asm	and esp, 0FFFFFFF0h;
	// Jump back to the original function
	_asm	jmp COffsets::IV_Hook__CIKManager_FireWeapon__JmpBack;
}

void CWeaponHandler::InstallAimSyncHooks()
{
	// Hook for the CIkManager::PointArms function
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__CIKManager_AimWeapon, (DWORD)CIkManager__PointArms_Hook);

	// Hook for the CWeapon::Fire function
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__CIKManager_PointArms, (DWORD)CWeapon__Fire_Hook);

	// Hook for the CIkManager::AimCoords function
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__CIKManager_FireWeapon, (DWORD)CIKManager__AimWeapon);
}
