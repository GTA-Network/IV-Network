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

#ifndef CIVPad_h
#define CIVPad_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVPadData.h"
#include <IV/IVData.h>

class IVPadConfig
{
public:
	DWORD dwCount;
	PAD(IVPadConfig, pad0, 0x7B4);
};

class IVPad
{
public:
	IVPadConfig m_padConfig[5];
	IVPadData m_padData[INPUT_COUNT];
	IVPadData m_otherPadData0;
	IVPadData m_otherPadData1;
	IVPadData m_otherPadData2;
	IVPadData m_otherPadData3;
	PAD(IVPad, pad0, 0x4);
	bool m_bIsUsingController;
	PAD(IVPad, pad1, 0x3);
	IVPadData m_otherPadData4;
	PAD(IVPad, pad2, 0xC);
	IVPadConfig m_textPadConfig;
	PAD(IVPad, pad3, 0x8);
	DWORD m_dwLastUpdateTime;
	PAD(IVPad, pad4, 0x14);
};

class CIVPad 
{
private:
	bool			m_bCreatedByUs;
	IVPad			* m_pPad;

public:
	CIVPad();
	CIVPad(IVPad * pPad);
	~CIVPad();

	void			SetPad(IVPad * pPad) { m_pPad = pPad; }
	IVPad			* GetPad() { return m_pPad; }

	bool			IsAnalogInput(eInput input);

	void			ToControlState(CControlState& controlState, bool bCurrent);
	void			FromControlState(CControlState controlState, bool bCurrent);

	void			SetCurrentControlState(CControlState controlState);
	void			GetCurrentControlState(CControlState& controlState);

	void			SetLastControlState(CControlState controlState);
	void			GetLastControlState(CControlState& controlState);
};

#endif // CIVPad_h