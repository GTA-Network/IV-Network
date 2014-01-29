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

#ifndef CPad_h
#define CPad_h

#include <Common.h>
#include "../GameCommon.h"

#include "CPadData.h"

_GAME_BEGIN

class IPadConfig
{
public:
	DWORD dwCount;
	PAD(IVPadConfig, pad0, 0x7B4);
};

class IPad
{
public:
	IPadConfig m_padConfig[5];
	IPadData m_padData[INPUT_COUNT];
	IPadData m_otherPadData0;
	IPadData m_otherPadData1;
	IPadData m_otherPadData2;
	IPadData m_otherPadData3;
	PAD(IVPad, pad0, 0x4);
	bool m_bIsUsingController;
	PAD(IVPad, pad1, 0x3);
	IPadData m_otherPadData4;
	PAD(IVPad, pad2, 0xC);
	IPadConfig m_textPadConfig;
	PAD(IVPad, pad3, 0x8);
	DWORD m_dwLastUpdateTime;
	PAD(IVPad, pad4, 0x14);
};

class CPad 
{
private:
	bool			m_bCreatedByUs;
	IPad			* m_pPad;

public:
	CPad();
	CPad(IPad * pPad);
	~CPad();

	void			SetPad(IPad * pPad) { m_pPad = pPad; }
	IPad			* GetPad() { return m_pPad; }

	bool			IsAnalogInput(eInput input);

	void			ToControlState(CControlState& controlState, bool bCurrent);
	void			FromControlState(CControlState controlState, bool bCurrent);

	void			SetCurrentControlState(CControlState controlState);
	void			GetCurrentControlState(CControlState& controlState);

	void			SetLastControlState(CControlState controlState);
	void			GetLastControlState(CControlState& controlState);
};

_GAME_END

#endif // CPad_h
