//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
	BYTE *  m_pElements;
	BYTE *  m_pFlags;
	DWORD   m_dwCount;
	DWORD   m_dwElementSize;
	int     m_nTop;
	DWORD   m_dwUsed;
	BYTE    m_bAllocated;
	BYTE    _f19;
	BYTE    _f1A;
	BYTE    _f1B;
};

class IVPoolOwns : IVPool
{
public:
	IVPool* __thiscall IVPoolHook(int maxElements, const char* Name, int elementSize);
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
		if (m_pPool)
			return (*(T*(__thiscall *)(IVPool *)) (COffsets::FUNC_CPool__Allocate))(m_pPool);

		return NULL;
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
		if(m_pPool)
			return (*(unsigned int(__thiscall *)(IVPool *, T*)) (COffsets::FUNC_CPool__HandleOf))(m_pPool, pObject);

		return 0;
	}

	T * AtHandle(unsigned int uiHandle)
	{
		if(m_pPool)
			return (*(T*(__thiscall *)(IVPool *, unsigned int)) (COffsets::FUNC_CPool__AtHandle))(m_pPool, uiHandle);

		return 0;
	}

	void Release(T * pObject)
	{
		if(m_pPool)
			return (*(void(__thiscall *)(IVPool *, T*)) (COffsets::FUNC_CPool__Release))(m_pPool, pObject);
	}
};

#endif // CIVPool_h