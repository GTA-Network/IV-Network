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

#ifndef CScript_FunctionContext_h
#define CScript_FunctionContext_h

#include <Common.h>
#include "../GameCommon.h"

_GAME_BEGIN

class INativeCallContext
{
protected:
	void * m_pReturn;              // 00-04
	unsigned int m_nArgCount;      // 04-08
	void * m_pArgs;                // 08-0C
	unsigned int m_nDataCount;     // 0C-10
	CVector3 * m_pOriginalData[4]; // 10-20
	Vector4 m_TemporaryData[4];    // 20-60
};

class NativeContext : public INativeCallContext
{
private:
	// Configuration
	enum
	{
		MaxNativeParams = 16,
		ArgSize = 4,
	};
	
	// Anything temporary that we need
	unsigned char m_TempStack[MaxNativeParams * ArgSize];

public:
	inline NativeContext()
	{
		// It's okay to point both args and return at
		// the same pointer as the game will handle this
		m_pArgs = &m_TempStack;
		m_pReturn = &m_TempStack;
		m_nArgCount = 0;
		m_nDataCount = 0;
	}

	template <typename T>
	inline void Push(T value)
	{
		// Have we reached our argument count?
		if(m_nArgCount == MaxNativeParams)
		{
			// We can only store 16 arguments
			return;
		}

		// Is the argument too big?
		if(sizeof(T) > ArgSize)
		{
			// We only accept 4 byte or less arguments
			return;
		}
		else if(sizeof(T) < ArgSize) // Is the argument too small?
		{
			// Reset the argument data
			*(unsigned int *)(m_TempStack + ArgSize * m_nArgCount) = 0;
		}

		// Add to argument to the argument stack
		*(T *)(m_TempStack + ArgSize * m_nArgCount) = value;

		// Increment the total argument count
		m_nArgCount++;
	}

	template <typename T>
	inline T GetResult()
	{
		// Copy back any vector results
		while(m_nDataCount > 0)
		{
			m_nDataCount--;
			CVector3 * pVec3 = m_pOriginalData[m_nDataCount];
			Vector4 * pVec4 = &m_TemporaryData[m_nDataCount];
			pVec3->fX = pVec4->fX;
			pVec3->fY = pVec4->fY;
			pVec3->fZ = pVec4->fZ;
		}

		return *(T *)m_TempStack;
	}
};

_GAME_END

#endif // CScript_FunctionContext_h
