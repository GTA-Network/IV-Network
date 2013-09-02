//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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

_declspec(naked) void CTaskSimpleStartVehicle__Process()
{
	_asm xor eax, eax;
	_asm retn 4;
}

#include <CXML.h>

const char TLAD[] = "<ini><device>e1</device><content><name>The Lost and Damned Radio</name><id>1</id><audiometadata>e1_radio.xml</audiometadata><enabled /></content>	<content><name>The Lost and Damned</name><id>2</id>" 
		"<episode>2</episode><datfile>content.dat</datfile><audiometadata>e1_audio.xml</audiometadata><loadingscreens>pc/textures/loadingscreens.wtd</loadingscreens><loadingscreensdat>common\\data\\loadingscreens.dat</loadingscreensdat>"
		"<loadingscreensingame>pc/textures/loadingscreens_ingame.wtd</loadingscreensingame>"
		"<loadingscreensingamedat>common\\data\\loadingscreens_ingame.dat</loadingscreensingamedat>"
		"<texturepath>pc/textures/</texturepath>"
		"<!-- <enabled /> -->"
		"</content>	"
		"</ini>";

const char TBOGT[] = "<ini>"
	"<device>e2</device>"	
	"<content>"
		"<name>The Ballad of Gay Tony</name>"
		"<id>3</id>"
		"<audiometadata>e2_radio.xml</audiometadata> "
		"<enabled />"
	"</content>"
	"<content>"
		"<name>The Ballad of Gay Tony</name>"
		"<id>4</id>"
		"<episode>1</episode>"
		"<datfile>content.dat</datfile>"
		"<audiometadata>e2_audio.xml</audiometadata>"
		"<loadingscreens>pc/textures/loadingscreens.wtd</loadingscreens>"
		"<loadingscreensdat>common\\data\\loadingscreens.dat</loadingscreensdat>"
		"<loadingscreensingame>pc/textures/loadingscreens_ingame.wtd</loadingscreensingame>"
		"<loadingscreensingamedat>common\\data\\loadingscreens_ingame.dat</loadingscreensingamedat>"
		"<texturepath>pc/textures/</texturepath>"
		"<!-- <enabled /> -->"
	"</content>"
"</ini>";

const char setu[] = "setup3.xml";
void CPatches::Initialize()
{

	//CXML * pXML = new CXML();
	//pXML->load(CString("%s\TBoGT\setup.xml", SharedUtility::GetAppPath()));
	//pXML->newNode("ini");
	//pXML->newNode("device");
	//pXML->

	char szInstallDirectory[MAX_PATH];

	if(SharedUtility::ReadRegistryString(HKEY_CURRENT_USER, "Software\\IVMP", "gtaivdir", NULL,
		szInstallDirectory, sizeof(szInstallDirectory)) ||
		SharedUtility::Exists(szInstallDirectory))
	{

		ofstream myfile;
		myfile.open(CString("%s\\TBoGT\\setup3.xml", szInstallDirectory).Get());
		myfile << TBOGT;
		myfile.close();

		myfile.open(CString("%s\\TLAD\\setup3.xml", szInstallDirectory).Get());
		myfile << TLAD;
		myfile.close();

	}

	CPatcher::InstallPushPatch(g_pCore->GetBase() + 0x8B3DAC, (DWORD)setu);
	CPatcher::InstallPushPatch(g_pCore->GetBase() + 0x8B4A0E, (DWORD)setu);
	//*(DWORD*)(g_pCore->GetBase() + 0x182197C) = 1;

	// Skip main menu #1
	*(BYTE *)COffsets::IV_Hook__PatchUnkownByte1 = 0xE0;

	// Skip main menu #2
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
    //*(BYTE *)COffsets::IV_Hook__PatchStartupDOTsco = 0x75;
	//CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchStartupDOTsco, 2);

	// Disable automatic vehicle engine turn-on
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchVehicleDriverProcess, (DWORD)CTaskSimpleStartVehicle__Process);

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
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_2, (COffsets::IV_Hook__DisableStartupResourceCheck_2 + 0x1CB));
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_3, (COffsets::IV_Hook__DisableStartupResourceCheck_3 + 0x2E9));
    CPatcher::InstallJmpPatch(COffsets::IV_Hook__DisableStartupResourceCheck_4, (COffsets::IV_Hook__DisableStartupResourceCheck_4 + 0x18F));

    // Disable automatic radar turn-on(in vehicle)
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableAutomaticRadarTurnon_1, 7); // initialize or render(seems to be a render func)
    CPatcher::InstallNopPatch(COffsets::IV_Hook__DisableAutomaticRadarTurnon_2, 5); // from init blip gtaiv func(startup)

    // Disable weapon when entering vehicle
    CPatcher::InstallNopPatch(COffsets::IV_Hook__PatchWeaponGiveWhenEnterVehicle, 0x30);
	
    // This needs to be disabled due to some crashes and to enable the blocked vehicles such as uranus, hellfury, etc.
    /*	INFO: crash occure exactly when accessing dword_13BEEE0 this is related to ZonesNames, but disabling this function dont destroy anything
		this function checks some flags in modelInfos and loading some models they seems to be not needed
		This seems to be associated to loading models but they are not used!?
    */
    CPatcher::InstallRetnPatch(COffsets::IV_Hook__PatchEnableAndFixVehicleModels);

	*(BYTE *)COffsets::IV_Hook__PatchUnkownByte1 = 0xE0;

	// Allow remote desktop connections pff
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x405D67), (g_pCore->GetBase() + 0x405D6E), 1);
}