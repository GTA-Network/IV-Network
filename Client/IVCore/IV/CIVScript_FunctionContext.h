//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVScript_FunctionContext.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: Contains zlib licensed code from ScriptHook by aru
//
//==============================================================================

#ifndef CIVScript_FunctionContext_h
#define CIVScript_FunctionContext_h

#include <Math\CMaths.h>
#include "IVCommon.h"

class IVNativeCallContext
{
protected:
	void * m_pReturn;              // 00-04
	unsigned int m_nArgCount;      // 04-08
	void * m_pArgs;                // 08-0C
	unsigned int m_nDataCount;     // 0C-10
	CVector3 * m_pOriginalData[4]; // 10-20
	Vector4 m_TemporaryData[4];    // 20-60
};

class NativeContext : public IVNativeCallContext
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

#endif // CIVScript_FunctionContext_h