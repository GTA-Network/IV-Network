//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPool.h
// Project: Client.Core
// Author: Balika011 <balika011@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include <CCore.h>
#include "CIVPool.h"
#include <Game/CGameFuncs.h>

IVPool* IVPoolOwns::IVPoolHook(int maxElements, const char* Name, int elementSize)
{
	if (strcmp(Name, "VehicleStruct") == 0)
		maxElements = 140;

	CLogFile::Printf("IVPoolHook(%i, %s, %i)", maxElements, Name, elementSize);

	m_dwElementSize = elementSize;
	m_pElements = (BYTE*) CGameFunction::Alloc(elementSize * maxElements);
	m_pFlags = (BYTE*) CGameFunction::Alloc(maxElements);

	m_bAllocated = 1;
	m_dwCount = maxElements;
	m_nTop = -1;

	m_dwUsed = 0;

	for (int i = 0; i < maxElements; ++i)
		*(m_pFlags + i) |= 0x80;

	return this;
}