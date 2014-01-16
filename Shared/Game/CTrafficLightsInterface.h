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

#ifndef CTrafficLightsInterface_h
#define CTrafficLightsInterface_h

#include <Common.h>

class CTrafficLightsInterface {
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

	virtual bool SetState(eTrafficLightState state) = 0;
	virtual eTrafficLightState GetState() = 0;
	virtual eTrafficLightState GetSetState() = 0;

	virtual void SetTimeThisCycle(unsigned int uiTime) = 0;
	virtual void CalculateCycleTime() = 0;
	virtual unsigned int GetTimeThisCylce() = 0;

	virtual bool IsUsingDefaultDurations() = 0;
	virtual void ResetDefaultDurations() = 0;

	virtual void SetGreenDuration(unsigned int uiDuration) = 0;
	virtual void SetYellowDuration(unsigned int uiDuration) = 0;
	virtual void SetRedDuration(unsigned int uiDuration) = 0;

	virtual unsigned int GetGreenDuration() = 0;
	virtual unsigned int GetYellowDuration() = 0;
	virtual unsigned int GetRedDuration() = 0;

	virtual void SetLocked(bool bLocked) = 0;
	virtual bool IsLocked() = 0;
};

#endif // CTrafficLightsInterface_h