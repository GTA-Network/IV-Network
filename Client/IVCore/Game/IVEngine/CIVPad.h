//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPad.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPad_h
#define CIVPad_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVPadData.h"
#include <IV/IVData.h>

class IVPadConfig {
public:
	DWORD dwCount;
	PAD(IVPadConfig, pad0, 0x7B4);
};

class IVPad {
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

class CIVPad {
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

	void			ToControlState(CControls& controlState, bool bCurrent);
	void			FromControlState(CControls controlState, bool bCurrent);

	void			SetCurrentControlState(CControls controlState);
	void			GetCurrentControlState(CControls& controlState);

	void			SetLastControlState(CControls controlState);
	void			GetLastControlState(CControls& controlState);
};

#endif // CIVPad_h