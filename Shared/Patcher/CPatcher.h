//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPatcher.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CPatcher_h
#define CPatcher_h

#include <Common.h>

#define X86_NOP 0x90
#define X86_RETN 0xC3
#define X86_CALL 0xE8
#define X86_JMP 0xE9

struct ProtectionInfo
{
	DWORD dwAddress;
	DWORD dwOldProtection;
	int   iSize;
};

class CPatcher {
public:
	static ProtectionInfo	Unprotect(DWORD dwAddress, int iSize);
	static void				Reprotect(ProtectionInfo protectionInfo);
	static void				InstallNopPatch(DWORD dwAddress, int iSize = 1);
	static void				InstallPadPatch(DWORD dwAddress, int iSize = 1);
	static void				* InstallDetourPatchInternal(DWORD dwAddress, DWORD dwDetourAddress, BYTE byteType, int iSize = 5);
	static void				UninstallDetourPatchInternal(DWORD dwAddress, void * pTrampoline, int iSize = 5);
	static void				* InstallJmpPatch(DWORD dwAddress, DWORD dwJmpAddress, int iSize = 5);
	static void				* InstallCallPatch(DWORD dwAddress, DWORD dwCallAddress, int iSize = 5);
	static void				InstallRetnPatch(DWORD dwAddress);
	static void				InstallStringPatch(DWORD dwAddress, char * szString, int iSize);
	static void				InstallMethodPatch(DWORD dwHookAddress, DWORD dwFunctionAddress);
	static DWORD			GetFunctionAddress(char * szLibrary, char * szFunction);
	static DWORD			GetFunctionAddress(char * szLibrary, unsigned int uOrdinal);
	static void				* InstallDetourPatch(char * szLibrary, char * szFunction, DWORD dwFunctionAddress);
	static void				* InstallDetourPatch(char * szLibrary, unsigned int uOrdinal, DWORD dwFunctionAddress);
	static BYTE				InstallDetourPatchWithData(char * szLibrary, unsigned int uOrdinal, DWORD dwFunctionAddress);
	static void				UninstallDetourPatch(void * pTrampoline, DWORD dwFunctionAddress);
	static void				InstallPushPatch(DWORD dwAddress, DWORD dwFunctionAddress);
	static void				InstallHookCall(DWORD dwAddr, DWORD dwFunc);
	template <typename _Ret, typename _Class, typename... _Args>
	static DWORD				GetClassMemberAddress(_Ret(_Class::*Function)(_Args...)) { return (DWORD) (void*&) Function; }
};	

#endif // CPatcher_h