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

    // Disable long sleep in CGame::Run
    // *(DWORD *)(g_pCore->GetBase() + 0x401835) = 1;

	// Return at start of CTaskSimplePlayRandomAmbients::ProcessPed (Disable random ambient animations)
	*(DWORD *)(g_pCore->GetBaseAddress() + 0x9849F0) = 0x900004C2;

	// Disable some startup functions (gtaiv internal)
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xD549DC), (g_pCore->GetBase() + 0xD549C0));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xD549EC), (g_pCore->GetBase() + 0xD549D0));

	// Make the game think we are not connected to the internet
    *(BYTE *)(g_pCore->GetBase() + 0x10F1390) = 0; // byteInternetConnectionState
    *(DWORD *)(g_pCore->GetBase() + 0x7AF1A0) = 0x90C3C032; // xor al, al; retn; nop
	
	// Disable(resize to zero) help-message box
	*(DWORD *)((g_pCore->GetBase() + 0xF1DC40) + 0x9B8) = 0;

    // Always start a new game
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x5B0311), (g_pCore->GetBase() + 0x5B03BF));
	
	// Always start a new game
	CPatcher::InstallJmpPatch(COffsets::RAGE_LoadGame, COffsets::RAGE_StartNewGame);

	// Disable startup.sco
	//*(BYTE *)(g_pCore->GetBaseAddress() + 0x809A8A) = 0x75;
	CPatcher::InstallNopPatch((g_pCore->GetBaseAddress() + 0x809A8A), 2);

	// Disable automatic vehicle engine turn-on
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xA9F300), (DWORD)CTaskSimpleStartVehicle__Process);

	// === RAGE %% RGSC Stuff
    // Don't initialize error reporting
    CPatcher::InstallRetnPatch(g_pCore->GetBase() + 0xD356D0);

    // Certificates check (RETN 8)
    *(DWORD *)(g_pCore->GetBase() + 0x403F10) = 0x900008C2;

    // xor eax, eax - address of the RGSC object
    *(DWORD *)(g_pCore->GetBase() + 0x40262D) = 0x4AE9C033;

    // Skip RGSC connect and EFC checks (jmp 40289E)
    *(DWORD *)(g_pCore->GetBase() + 0x402631) = 0x90000002;

    // NOP; MOV [g_rgsc], eax
    *(WORD *)(g_pCore->GetBase() + 0x402883) = 0xA390;

    // Disable VDS102 error
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x4028ED), 42);

    // Last RGSC init check (NOP*6)
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x40291D), 6);

    // Skip missing tests
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x402B12), 14);
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x402D17), 14);

    *(DWORD *)(g_pCore->GetBase() + 0x403870) = 0x90CC033; // xor eax, eax; retn
    *(DWORD *)(g_pCore->GetBase() + 0x404250) = 0x90CC033; // xor eax, eax; retn

    // Disable securom spot checks (mov al, 1; retn)
    *(DWORD *)(g_pCore->GetBase() + 0xBAC160) = 0x90C301B0;
    *(DWORD *)(g_pCore->GetBase() + 0xBAC180) = 0x90C301B0;
    *(DWORD *)(g_pCore->GetBase() + 0xBAC190) = 0x90C301B0;
    *(DWORD *)(g_pCore->GetBase() + 0xBAC1C0) = 0x90C301B0;

    // Fix vehicle crash -> 8 xrefs
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xCBA1F0), (g_pCore->GetBase() + 0xCBA230));

    // Disables Warning Messages(like "Unkown resource found") -> Disables only the window(and exit code part)...
	// TODO: Replace with own error code function

#ifdef _DEBUG // Disable this function in our debug mode
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + /*0x5A932D*/0x5A8CB0), (g_pCore->GetBase() + 0x5A9361));
#endif

    // Disable startup/runtime resource check
    *(BYTE*)(g_pCore->GetBase() + 0x119DB14) = 1;
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x9E2E30), (g_pCore->GetBase() + 0x9E2FFB));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xCA76E0), (g_pCore->GetBase() + 0xCA79C9));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x446970), (g_pCore->GetBase() + 0x446AFF));

    // Disable automatic radar turn-on(in vehicle)
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x42D3D1), 7); // initialize or render(seems to be a render func)
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x811B6E), 5); // from init blip gtaiv func(startup)
        
    // Prevent crashes on player connect(associated with ped intelligence)
    //CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x815380), (g_pCore->GetBase() + 0x8153D4));
    //CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x625F15), (g_pCore->GetBase() + 0x625F1D));
    //CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xB2B24D), (g_pCore->GetBase() + 0xB2B259));

    // Disable weapon when entering vehicle
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x9C5994), 0x30);
	
    // This needs to be disabled due to some crashes and to enable the blocked vehicles such as uranus, hellfury, etc.
    /*	INFO: crash occure exactly when accessing dword_13BEEE0 this is related to ZonesNames, but disabling this function dont destroy anything
		this function checks some flags in modelInfos and loading some models they seems to be not needed
		This seems to be associated to loading models but they are not used!?
    */
    CPatcher::InstallRetnPatch(g_pCore->GetBase() + 0x8F2F40);

	//CPatcher::InstallJmpPatch((g_pCore->GetBaseAddress() + 0x8589D3), (g_pCore->GetBaseAddress() + 0x859E25));

	*(BYTE *)(g_pCore->GetBase() + 0x857133) = 0xE0;
}