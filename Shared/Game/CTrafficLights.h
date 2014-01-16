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

class CTrafficLights
{
public:
	enum eTrafficLightState
	{
		// Cycle
		TRAFFIC_LIGHT_STATE_GREEN_RED,     // green, red
		TRAFFIC_LIGHT_STATE_YELLOW_RED,    // yellow->red, red
		TRAFFIC_LIGHT_STATE_RED_RED_1,     // red, red
		TRAFFIC_LIGHT_STATE_RED_TO_GREEN,  // red, yellow->green
		TRAFFIC_LIGHT_STATE_RED_GREEN,     // red, green
		TRAFFIC_LIGHT_STATE_RED_YELLOW,    // red, yellow->red
		TRAFFIC_LIGHT_STATE_RED_RED_2,     // red, red
		TRAFFIC_LIGHT_STATE_TO_GREEN_RED,  // yellow->green, red

		// flashing, disabled = off
		TRAFFIC_LIGHT_STATE_FLASHING_FLASHING,
		TRAFFIC_LIGHT_STATE_FLASHING_DISABLED,
		TRAFFIC_LIGHT_STATE_DISABLED_FLASHING,
		TRAFFIC_LIGHT_STATE_DISABLED_DISABLED,

		// completely random
		TRAFFIC_LIGHT_STATE_GREEN_GREEN,

		TRAFFIC_LIGHT_STATE_MAX,
	};

	enum eGTATrafficLightState
	{
		GTA_TRAFFIC_LIGHT_STATE_GREEN,
		GTA_TRAFFIC_LIGHT_STATE_YELLOW,
		GTA_TRAFFIC_LIGHT_STATE_RED,
		GTA_TRAFFIC_LIGHT_STATE_DISABLED,
	};

	// Time the green phases last
	static const unsigned int DEFAULT_GREEN_DURATION = 22000;

	// Time the one yellow, one red phases last
	static const unsigned int DEFAULT_YELLOW_DURATION = 3000;

	// Time the traffic lights are both red
	static const unsigned int DEFAULT_RED_DURATION = 2000;

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
