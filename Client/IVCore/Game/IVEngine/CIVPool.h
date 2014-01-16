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

#ifndef CIVPool_h
#define CIVPool_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

class IVPool
{
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
class CIVPool
{
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