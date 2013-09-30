//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTrafficLights.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CTrafficLights_h
#define CTrafficLights_h

#include "CTrafficLightsInterface.h"
#include <Common.h>

class CTrafficLights : public CTrafficLightsInterface {
private:
	static CTrafficLights * m_pInstance;
	unsigned long           m_ulTimeSet;
	bool                    m_bIsLocked;
	eTrafficLightState      m_eStateSet;
	unsigned int            m_uiGreenDuration;
	unsigned int            m_uiYellowDuration;
	unsigned int            m_uiRedDuration;
	unsigned int            m_uiTotalDuration;

public:
	CTrafficLights();
	~CTrafficLights();

	static CTrafficLights * GetInstance() { return m_pInstance; }

	void Reset();

	bool SetState(eTrafficLightState state);
	eTrafficLightState GetState();
	eTrafficLightState GetSetState();

	void SetTimeThisCycle(unsigned int uiTime);
	void CalculateCycleTime();
	unsigned int GetTimeThisCylce();

	bool IsUsingDefaultDurations();
	void ResetDefaultDurations();

	void SetGreenDuration(unsigned int uiDuration);
	void SetYellowDuration(unsigned int uiDuration);
	void SetRedDuration(unsigned int uiDuration);

	unsigned int GetGreenDuration();
	unsigned int GetYellowDuration();
	unsigned int GetRedDuration();

	void SetLocked(bool bLocked);
	bool IsLocked();

#ifdef _SERVER
	void SyncState();
#else
	eGTATrafficLightState GetTrafficLightState();
	eGTATrafficLightState GetTrafficLightAltState();
#endif
};


#endif // CTrafficLights_h
