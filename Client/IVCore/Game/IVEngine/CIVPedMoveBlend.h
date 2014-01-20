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

#ifndef CIVPedMoveBlend_h
#define CIVPedMoveBlend_h

#include <IV/IVCommon.h>

#pragma pack(push, 1)
class IVPedMoveBlendBase
{
public:
	float fX;
	float fY;
	float destX;
	float destY;
	DWORD field_14;
	float field_18;
	DWORD field_1C;
	DWORD field_20;
	IVPed * m_pPed;
	float field_28;
	float field_2C;
	DWORD field_30;
	DWORD field_34;
	DWORD field_38;
	DWORD m_dwAnimGroup;
	DWORD field_40;
	DWORD field_44;
	float field_48;
	DWORD field_4C;
	DWORD m_dwFlags;

	virtual ~IVPedMoveBlendBase();
	virtual void Function1();
	virtual void Function2(); // sets flag
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void* CreateDefaultTask(); //returns whit CTask*
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();

};

class IVPedMoveBlendOnFoot : public IVPedMoveBlendBase
{
public:
	DWORD field_54; //float?
	DWORD field_58;
	DWORD field_5C;
	DWORD field_60;
	DWORD field_64;
	DWORD field_68; //Missed form the reset	
	DWORD field_6C; //float?
	DWORD field_70; //float?
	DWORD field_74;
	DWORD field_78;
	DWORD field_7C;
	DWORD field_80;
	DWORD field_84;
	DWORD field_88;
	DWORD field_8C;
	DWORD field_90;
	DWORD field_94; //Missed form the reset	
	DWORD field_98;
	DWORD field_9C;
	DWORD field_A0;
	DWORD field_A4;
	WORD field_A8; //flag
	WORD field_AA;
	DWORD field_AC;
	DWORD field_B0;
	DWORD field_B4;
	DWORD field_B8;
	DWORD field_BC;
	DWORD field_C0;
	DWORD field_C4;
	DWORD field_C8;
	DWORD field_CC;

	virtual ~IVPedMoveBlendOnFoot();
};
#pragma pack(pop)
class CIVPedMoveBlendOnFoot
{
public:
	CIVPedMoveBlendOnFoot();
	~CIVPedMoveBlendOnFoot();
};

#endif // CIVPedMoveBlend_h
