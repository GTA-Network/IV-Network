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

#include <CCore.h>
#include "CPool.h"
#include <Game/CGameFuncs.h>

_GAME_BEGIN

IPool* IPoolOwns::IVPoolHook(int maxElements, const char* Name, int elementSize)
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

_GAME_END