#include "CCrashFixes.h"
#include <CCore.h>

extern CCore* g_pCore;

int				hFile2;
_declspec(naked) void TextureSelect_Hook()
{
	_asm	mov eax, [esp + 4];
	//_asm	mov iTexture, eax;
	_asm	mov eax, [esp + 8];
	_asm	mov hFile2, eax;
	_asm	pushad;

	if (hFile2 < 10000000)
		g_pCore->GetGame()->ThrowInternalException(COffsets::FUNC_GENERATETEXTURE, 0xC0000005);

	_asm	popad;
	_asm	push ebx;
	_asm	push esi;
	_asm	push edi;
	_asm	mov edi, ecx;
	_asm	jmp COffsets::IV_Hook__TextureSelect__JmpBack;
}

_declspec(naked) void CRASH_625F15_HOOK()
{
	_asm
	{
		test    eax, eax
		jz      keks
		cmp     eax, 100000h
		jl      keks
		mov     edx, [eax]
		push    1
		mov     ecx, edi
		call    edx

keks_patch :
		mov     al, 1
		pop     edi
		pop     esi
		pop     ebp
		pop     ebx
		add     esp, 0Ch
		retn    4
keks:
		pushad
	}

	g_pCore->GetGame()->ThrowInternalException(COffsets::IV_Hook__UnkownPatch2, 0xC0000005);

	_asm
	{
		popad
		jmp keks_patch
	}
}

void CCrashFixes::Initialize()
{
	// Hook texture select/generate function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GENERATETEXTURE, (DWORD) TextureSelect_Hook);

	// Fix vehicle crash -> 8 xrefs
	//CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchPreventVehicleCrash, (COffsets::IV_Hook__PatchPreventVehicleCrash + 40));

	// this disables a call to a destructor of a member in rageResourceCache [field_244] 
	//CPatcher::InstallJmpPatch(COffsets::IV_Hook__UnkownPatch2, (DWORD)CRASH_625F15_HOOK);

	// Disables zone population calcs fixes crash with some vehicles
	CPatcher::InstallRetnPatch(COffsets::IV_Hook__PatchEnableAndFixVehicleModels);
}