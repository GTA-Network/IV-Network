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

#ifndef CModule_h
#define CModule_h

#include <CLibrary.h>
#include <CLogFile.h>

static void * FunctionContainer[] = {
	(void *)CLogFile::Printf
};

static	void	* InterfacesContainer[2];

typedef void (* SetupFunctions_t)(void *);
typedef void (* SetupInterfaces_t)(void *);
typedef void (* SetupNewInterfaces_t)(void *);
typedef bool (* InitializeModule_t)(char *);
typedef void (* Pulse_t)(void);

struct SModuleFunctions
{
	SetupFunctions_t pfnSetupFunctions;
	SetupInterfaces_t pfnSetupInterfaces;
	SetupNewInterfaces_t pfnSetupNewInterfaces;
	InitializeModule_t pfnInitializeModule;
	Pulse_t pfnPulse;
};

class CModule
{

private:
	CLibrary						* m_pLibrary;
	SModuleFunctions				m_moduleFunctions;
	CString							m_strPath;
	CString							m_strName;

public:

									CModule(CString strName);
									~CModule();

	bool							IsValid();
	void							Pulse();
	void							Load();
	void							SetPath(CString strPath) { m_strPath = strPath; }
	CString							GetPath() { return m_strPath; }
	CString							GetName() { return m_strName; }

};
#endif // CModule_h