//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
//
// File: CPatches.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, XForce
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CPatches.h"
#include	<CCore.h>
#include	<Patcher\CPatcher.h>

extern	CCore				* g_pCore;

void CPatches::Initialize()
{
	// Return at start of CTaskSimplePlayRandomAmbients::ProcessPed (Disable random ambient animations)
	*(DWORD *)(g_pCore->GetBaseAddress() + 0x9849F0) = 0x900004C2;

	// Disable some startup functions (gtaiv internal)
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xD549DC), (g_pCore->GetBase() + 0xD549C0));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xD549EC), (g_pCore->GetBase() + 0xD549D0));

	// Make the game think we are not connected to the internet
    *(BYTE *)(g_pCore->GetBase() + 0x10F1390) = 0; // byteInternetConnectionState
    *(DWORD *)(g_pCore->GetBase() + 0x7AF1A0) = 0x90C3C032; // xor al, al; retn; nop

	// Disable resouce-loading script "main.sco"
    *(BYTE *)(g_pCore->GetBase() + 0x809A8A) = 0x75;
		
    // Always start a new game
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x5B0311), (g_pCore->GetBase() + 0x5B03BF));

    // Disable parked cars
    CPatcher::InstallRetnPatch(g_pCore->GetBase() + 0xB3EDF0);

    // Disable emergency services and garbage trucks
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x4215CF), 5);

    // Disable vehicle entries
    *(DWORD *)(g_pCore->GetBase() + 0x9B1ED0) = 0x0CC2C033;
    *(BYTE *)(g_pCore->GetBase() + 0x9B1ED4) = 0x00;

    // Disable vehicle exits
    *(BYTE *)(g_pCore->GetBase() + 0x9BBBFC) = 0xEB;

    // Disable random peds and vehicles
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x8ACD64), 5);
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x421610), 5);
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x81B22E), 5);

    // Disable scenario peds
    *(BYTE *)(g_pCore->GetBase() + 0x9F72C0) = 0xB8; // mov eax,
    *(DWORD *)(g_pCore->GetBase() + 0x9F72C1) = 0x0; // 0
    *(BYTE *)(g_pCore->GetBase() + 0x9F72C5) = 0xC3; // retn

    // Disable fake cars
    CPatcher::InstallRetnPatch(g_pCore->GetBase() + 0x9055D0);

    // Disable long sleep in CGame::Run
    *(DWORD *)(g_pCore->GetBase() + 0x401835) = 1;

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
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + /*0x5A932D*/0x5A8CB0), (g_pCore->GetBase() + 0x5A9361));

    // Disable startup/runtime resource check
    *(BYTE*)(g_pCore->GetBase() + 0x119DB14) = 1;
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x9E2E30), (g_pCore->GetBase() + 0x9E2FFB));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xCA76E0), (g_pCore->GetBase() + 0xCA79C9));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x446970), (g_pCore->GetBase() + 0x446AFF));

    // Disable automatic radar turn-on(in vehicle)
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x42D3D1), 7); // initialize or render(seems to be a render func)
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x811B6E), 5); // from init blip gtaiv func(startup)
        
    // Prevent crashes on player connect(associated with ped intelligence)
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x815380), (g_pCore->GetBase() + 0x8153D4));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x625F15), (g_pCore->GetBase() + 0x625F1D));
    CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0xB2B24D), (g_pCore->GetBase() + 0xB2B259));

    // Disable weapon when entering vehicle
    CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x9C5994), 0x30);
}