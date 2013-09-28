//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CLibrary.h
// Project: Shared
// Author(s): jenksta
// License: See LICENSE in root directory
//
//==============================================================================

#pragma once

#include "Common.h"

class CLibrary {
private:
	void * m_pLibrary;

public:
	CLibrary();
	~CLibrary();

	bool   Load(const char * szPath);
	bool   Unload();
	void * GetProcedureAddress(const char * szProcedureName);
	void * GetProcedureAddress(unsigned int uiOrdinal);
};
