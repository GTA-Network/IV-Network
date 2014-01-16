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
