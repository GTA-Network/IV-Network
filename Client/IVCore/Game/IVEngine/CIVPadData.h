//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPadData.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPadData_h
#define CIVPadData_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include <IV/IVData.h>

class IVPadDataHistoryItem {
public:
	BYTE m_byteValue;
	PAD(IVPadDataHistoryItem, pad0, 3);
	DWORD m_dwLastUpdate;
};

class IVPadDataHistory {
public:
	IVPadDataHistoryItem	m_historyItems[64];
};

class IVPadData {
public:
	DWORD m_dwVFTable;
	BYTE m_byteUnknown4;
	BYTE m_byteContext;
	BYTE m_byteCurrentValue;
	BYTE m_byteLastValue;
	BYTE m_byteHistoryIndex;
	PAD(IVPadData, pad0, 3);
	IVPadDataHistory * m_pHistory;
};

#endif // CIVPadData_h