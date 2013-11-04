//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPatches.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CPatches.h"
#include <Patcher\CPatcher.h>
#include <fstream>
#include <Ptrs.h>
#include <CXML.h>

void CPatches::Initialize()
{
	// Skip main menu #1
	*(BYTE *)COffsets::IV_Hook__PatchUnkownByte1 = 0xE0;

	// Skip main menu #2
	CPatcher::InstallJmpPatch(COffsets::CGame_Process__Sleep, COffsets::CGame_Process_InitialiseRageGame);
	//CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x9D180B, 5);
	
	// Return at start of CTaskSimplePlayRandomAmbients::ProcessPed (Disable random ambient animations)
	//*(DWORD *)COffsets::IV_Hook__PatchRandomTasks = 0x900004C2;

	// Make the game think we are not connected to the internet - Balika011: faster game load
    *(BYTE *)COffsets::IV_Hook__PatchInternet_1 = 0; // byteInternetConnectionState
    *(DWORD *)COffsets::IV_Hook__PatchInternet_2 = 0x90C3C032; // xor al, al; retn; nop
	
	// Disable(resize to zero) help-message box
	//*(DWORD *)(COffsets::IV_Hook__PatchHelpMessageBox + 0x9B8) = 0;

    // Always start a new game
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchStartNewGame, (COffsets::IV_Hook__PatchStartNewGame + 0xA6));
	
	// Always start a new game
	CPatcher::InstallJmpPatch(COffsets::RAGE_LoadGame, COffsets::RAGE_StartNewGame);

	/**(BYTE *)(g_pCore->GetBase() + 0xA66B40) = 0xB8; // mov eax,
	*(DWORD *)(g_pCore->GetBase() + 0xA66B40 + 0x1) = 0x0; // 0
	*(BYTE *)(g_pCore->GetBase() + 0xA66B40 + 0x5) = 0xC3; // retn*/

	//CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x83468C, 5);
#if 0
#ifndef CHEAP_RELEASE
	// Replace I Luv "L.C." with "IVMP"
	CPatcher::Unprotect((g_pCore->GetBase() + 0x19DB0E9),4);
	*(BYTE *)(g_pCore->GetBase() + 0x19DB0E6) = 0x49; // L -> I
	*(BYTE *)(g_pCore->GetBase() + 0x19DB0E7) = 0x56; // . -> V
	*(BYTE *)(g_pCore->GetBase() + 0x19DB0E8) = 0x4D; // C -> M
	*(BYTE *)(g_pCore->GetBase() + 0x19DB0E9) = 0x50; // . -> P

	// Replace the "loading..." crap with "Busy, hold on...";
	char *szLoadingText = "BUSY.. HOLD ON";
	*(DWORD *)(g_pCore->GetBase() + (0x7E2DF2 + 0x1)) = (DWORD)szLoadingText; // Replace for chargment...
 	*(DWORD *)(g_pCore->GetBase() + (0x7E2DE3 + 0x1)) = (DWORD)szLoadingText; // Replace for beladung...
	*(DWORD *)(g_pCore->GetBase() + (0x7E2DD4 + 0x1)) = (DWORD)szLoadingText; // Replace for caricamento...
	*(DWORD *)(g_pCore->GetBase() + (0x7E2DC5 + 0x1)) = (DWORD)szLoadingText; // Replace for carga...
	*(DWORD *)(g_pCore->GetBase() + (0x7E2DB6 + 0x1)) = (DWORD)szLoadingText; // Replace for loading...
#endif
#endif
	// === RAGE %% RGSC Stuff

    // Don't initialize error reporting
    //CPatcher::InstallRetnPatch(COffsets::IV_Hook__PatchErrorReporting);

	*(WORD *) (g_pCore->GetBase() + 0x472EF1) = 0xC033; //xor eax, eax
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x472EF3, g_pCore->GetBase() + 0x47316E);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x473207, g_pCore->GetBase() + 0x473213);

	// Skip missing tests
	CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchMissingTests1, 14);
	CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchMissingTests2, 14);
	CPatcher::InstallNopPatch(g_pCore->GetBase() + 0x493D4C, 24);

	*(DWORD *) COffsets::IV_Hook__PatchUnkownAddress1 = 0x90CC033; // xor eax, eax; retn
	*(DWORD *) COffsets::IV_Hook__PatchUnkownAddress2 = 0x90CC033; // xor eax, eax; retn

    // Disable securom spot checks (mov al, 1; retn)
	*(DWORD *) COffsets::IV_Hook__PatchSecuromCheck = 0x90C301B0;
	*(DWORD *) (COffsets::IV_Hook__PatchSecuromCheck + 0x20) = 0x90C301B0;
	*(DWORD *) (COffsets::IV_Hook__PatchSecuromCheck + 0x30) = 0x90C301B0;
	*(DWORD *) (COffsets::IV_Hook__PatchSecuromCheck + 0x60) = 0x90C301B0;

	*(BYTE *) (g_pCore->GetBase() + 0x15C3398) = 1; //fix random drunk cam

    // Disables Warning Messages(like "Unkown resource found") -> Disables only the window(and exit code part)...
	// TODO: Replace with own error code function

#ifdef _DEV // Disable this function in our debug mode
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchErrorMessageBoxes, (COffsets::IV_Hook__PatchErrorMessageBoxes + 0x6B1));
#endif

    // Disable startup/runtime resource check
    //*(BYTE*)COffsets::IV_Hook__DisableStartupResourceCheck_1 = 1;
    //CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_2, (COffsets::IV_Hook__DisableStartupResourceCheck_2 + 0x1CB));
    //CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_3, (COffsets::IV_Hook__DisableStartupResourceCheck_3 + 0x2E9));
    //CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_4, (COffsets::IV_Hook__DisableStartupResourceCheck_4 + 0x18F));

    // Disable automatic radar turn-on(in vehicle)
    /*CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableAutomaticRadarTurnon_1, 7); // initialize or render(seems to be a render func)
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableAutomaticRadarTurnon_2, 5); // from init blip gtaiv func(startup)*/

    // Disable weapon when entering vehicle
    //CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchWeaponGiveWhenEnterVehicle, 0x30);

	*(BYTE *)COffsets::IV_Hook__PatchUnkownByte1 = 0xE0;

	// Allow remote desktop connections pff
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x405D67), (g_pCore->GetBase() + 0x405D6E), 1);

	// Set the window text
	*(DWORD *) (g_pCore->GetBase() + 0x47316F) = (DWORD)MOD_NAME;
}