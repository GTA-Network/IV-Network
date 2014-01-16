/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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

class CPatcher
{
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