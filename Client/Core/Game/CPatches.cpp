//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CPatches.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CPatches.h"
#include	<CCore.h>
#include	<Patcher\CPatcher.h>

extern	CCore				* g_pCore;

_declspec(naked) void CTaskSimpleStartVehicle__Process()
{
	_asm xor eax, eax;
	_asm retn 4;
}

void CPatches::Initialize()
{
	// Skip main menu
	CPatcher::InstallJmpPatch(COffsets::CGame_Process__Sleep, COffsets::CGame_Process_InitialiseRageGame);

	// Return at start of CTaskSimplePlayRandomAmbients::ProcessPed (Disable random ambient animations)
	*(DWORD *)COffsets::IV_Hook__PatchRandomTasks = 0x900004C2;

	// Make the game think we are not connected to the internet
    *(BYTE *)COffsets::IV_Hook__PatchInternet_1 = 0; // byteInternetConnectionState
    *(DWORD *)COffsets::IV_Hook__PatchInternet_2 = 0x90C3C032; // xor al, al; retn; nop
	
	// Disable(resize to zero) help-message box
	*(DWORD *)(COffsets::IV_Hook__PatchHelpMessageBox + 0x9B8) = 0;

    // Always start a new game
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchStartNewGame, (COffsets::IV_Hook__PatchStartNewGame + 0xA6));
	
	// Always start a new game
	CPatcher::InstallJmpPatch(COffsets::RAGE_LoadGame, COffsets::RAGE_StartNewGame);

	// Disable startup.sco
    *(BYTE *)COffsets::IV_Hook__PatchStartupDOTsco = 0x75;
	CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchStartupDOTsco, 2);

	// Disable automatic vehicle engine turn-on
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchVehicleDriverProcess, (DWORD)CTaskSimpleStartVehicle__Process);

	// === RAGE %% RGSC Stuff
    // Don't initialize error reporting
    CPatcher::InstallRetnPatch(COffsets::IV_Hook__PatchErrorReporting);

    // Certificates check (RETN 8)
    *(DWORD *)COffsets::IV_Hook__PatchCertificatesCheck = 0x900008C2;

    // xor eax, eax - address of the RGSC object
    *(DWORD *)COffsets::IV_Hook__PatchRGSCObject = 0x4AE9C033;

    // Skip RGSC connect and EFC checks (jmp 40289E)
    *(DWORD *)COffsets::IV_Hook__PatchRGSCEFCChecks = 0x90000002;

    // NOP; MOV [g_rgsc], eax
    *(WORD *)COffsets::IV_Hook__PatchFakeRGSCObject= 0xA390;

    // Disable VDS102 error
    CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchVDS102, 42);

    // Last RGSC init check (NOP*6)
    CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchRGSCInitCheck, 6);

    // Skip missing tests
    CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchMissingTests1, 14);
    CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchMissingTests2, 14);

    *(DWORD *)COffsets::IV_Hook__PatchUnkownAddress1 = 0x90CC033; // xor eax, eax; retn
    *(DWORD *)COffsets::IV_Hook__PatchUnkownAddress2 = 0x90CC033; // xor eax, eax; retn

    // Disable securom spot checks (mov al, 1; retn)
    *(DWORD *)COffsets::IV_Hook__PatchSecuromCheck = 0x90C301B0;
    *(DWORD *)(COffsets::IV_Hook__PatchSecuromCheck + 20) = 0x90C301B0;
    *(DWORD *)(COffsets::IV_Hook__PatchSecuromCheck + 30) = 0x90C301B0;
    *(DWORD *)(COffsets::IV_Hook__PatchSecuromCheck + 60) = 0x90C301B0;

    // Fix vehicle crash -> 8 xrefs
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchPreventVehicleCrash, (COffsets::IV_Hook__PatchPreventVehicleCrash + 40));

    // Disables Warning Messages(like "Unkown resource found") -> Disables only the window(and exit code part)...
	// TODO: Replace with own error code function

#ifdef _DEBUG // Disable this function in our debug mode
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchErrorMessageBoxes, (COffsets::IV_Hook__PatchErrorMessageBoxes + 0x6B1));
#endif

    // Disable startup/runtime resource check
    *(BYTE*)COffsets::IV_Hook__DisableStartupResourceCheck_1 = 1;
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_2, (g_pCore->GetBase() + 0x9E2FFB));
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_3, (g_pCore->GetBase() + 0xCA79C9));
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_4, (g_pCore->GetBase() + 0x446AFF));

    // Disable automatic radar turn-on(in vehicle)
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableAutomaticRadarTurnon_1, 7); // initialize or render(seems to be a render func)
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableAutomaticRadarTurnon_2, 5); // from init blip gtaiv func(startup)
        
    // Prevent crashes on player connect(associated with ped intelligence)
    //CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x815380), (g_pCore->GetBase() + 0x8153D4));
    //CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x625F15), (g_pCore->GetBase() + 0x625F1D));
    //CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xB2B24D), (g_pCore->GetBase() + 0xB2B259));

    // Disable weapon when entering vehicle
    CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchWeaponGiveWhenEnterVehicle, 0x30);
	
    // This needs to be disabled due to some crashes and to enable the blocked vehicles such as uranus, hellfury, etc.
    /*	INFO: crash occure exactly when accessing dword_13BEEE0 this is related to ZonesNames, but disabling this function dont destroy anything
		this function checks some flags in modelInfos and loading some models they seems to be not needed
		This seems to be associated to loading models but they are not used!?
    */
    CPatcher::InstallRetnPatch(COffsets::IV_Hook__PatchEnableAndFixVehicleModels);

	//CPatcher::InstallJmpPatch((g_pCore->GetBaseAddress() + 0x8589D3), (g_pCore->GetBaseAddress() + 0x859E25));

	*(BYTE *)COffsets::IV_Hook__PatchUnkownByte1 = 0xE0;
}