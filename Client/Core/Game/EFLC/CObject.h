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

#ifndef CObject_h
#define CObject_h

#include <Common.h>
#include "../GameCommon.h"

#include "CPhysical.h"
#include "CWeapon.h"

_GAME_BEGIN

class IObject : public IPhysical
{
public:
	                           // 000-210
	PAD(IVObject, pad0, 0x4C); // 210-25C
	IWeapon * m_pWeapon;      // 25C-260
	PAD(IVObject, pad1, 0xC0); // 210-320

	virtual ~IObject();
};

class CObject : public CPhysical
{
private:
	IObject  * m_pObject;
	CWeapon * m_pWeapon;

public:
	CObject(IObject * pObject);
	~CObject();

	void        SetObject(IObject * pObject) { m_pObject = pObject; }
	IObject  * GetObject() { return m_pObject; }
	CWeapon * GetWeapon();
};

_GAME_END

#endif // CObject_h
