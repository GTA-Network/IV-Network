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

#ifndef CDynamicEntity_h
#define CDynamicEntity_h

#include <Common.h>
#include "../GameCommon.h"

#include "CEntity.h"

_GAME_BEGIN

#pragma pack(push, 1)
class IDynamicEntity : public IEntity
{
public:
	DWORD m_pPtrNodeDouble;                                // PtrNodeDouble
	DWORD m_pAnim;                                                // 078-07C
	// 0x80 - 0xCC = CPortalTracker m_portalTracker; (+0x30 = CDynamicEntity * m_pDynamicEntity)
	PAD(IVDynamicEntity, pad1, 0x90);        // 07C-10C

	virtual        ~IDynamicEntity();
	virtual void   Function51(); // idk
	virtual void   Function52(); // return 0;
	virtual void   Function53(); // return 0;
	virtual void   Function54(); // CPortalTracker
};
#pragma pack(pop)

class CDynamicEntity : public CEntity
{
public:
	CDynamicEntity();
	CDynamicEntity(IDynamicEntity * pDynamicEntity);
	~CDynamicEntity();

	void	 SetDynamicEntity(IDynamicEntity * pDynamicEntity);
	IDynamicEntity	 * GetDynamicEntity();
};

_GAME_END

#endif // CDynamicEntity_h
