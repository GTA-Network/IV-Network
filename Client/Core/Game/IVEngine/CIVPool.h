//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVPool.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPool_h
#define CIVPool_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

class IVPool {
public:
	BYTE *  m_pObjects;
	BYTE *  m_pFlags;
	DWORD   m_dwCount;
	DWORD   m_dwEntrySize;
	int     m_nTop;
	DWORD   m_dwUsed;
	BYTE    m_bAllocated;
	BYTE    _f19;
	BYTE    _f1A;
	BYTE    _f1B;
};

template <class T>
class CIVPool {
private:
	IVPool		* m_pPool;

public:
	CIVPool() { m_pPool = NULL; }
	CIVPool(IVPool * pPool) { m_pPool = pPool; }
	~CIVPool(){ }
	void		SetPool(IVPool * pPool) { m_pPool = pPool; }
	IVPool		* GetPool() { return m_pPool; }

	T * Allocate()
	{
		T * pObject = NULL;

		if (m_pPool)
		{
			IVPool * pPool = m_pPool;
			_asm
			{
				mov ecx, pPool
				call COffsets::FUNC_CPool__Allocate
				mov pObject, eax
			}
		}

		return pObject;
	}

	DWORD		GetCount()
	{
		if(m_pPool)
			return m_pPool->m_dwCount;

		return 0;
	}

	DWORD		GetEntrySize()
	{
		if(m_pPool)
			return m_pPool->m_dwEntrySize;

		return 0;
	}

	DWORD		GetUsed()
	{
		if(m_pPool)
			return m_pPool->m_dwUsed;

		return 0;
	}

	unsigned int HandleOf(T * pObject)
	{
		unsigned int uiHandle = 0;

		if(m_pPool)
		{
			T * _pObject = pObject;
			IVPool * pPool = m_pPool;
			_asm
			{
				push _pObject
				mov ecx, pPool
				call COffsets::FUNC_CPool__HandleOf
				mov uiHandle, eax
			}
		}

		return uiHandle;
	}

	T * AtHandle(unsigned int uiHandle)
	{
		T * pObject = NULL;

		if(m_pPool)
		{
			IVPool * pPool = m_pPool;
			_asm
			{
				mov ecx, pPool
				push uiHandle
				call COffsets::FUNC_CPool__AtHandle
				mov pObject, eax
			}
		}

		return pObject;
	}

	void Release(T * pObject)
	{
		if(m_pPool)
		{
			IVPool * pPool = m_pPool;
			_asm
			{
				mov ecx, pPool
				push pObject
				call COffsets::FUNC_CPool__Release
			}
		}
	}
};

#endif // CIVPool_h