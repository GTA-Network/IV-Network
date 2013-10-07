//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTrafficLights.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CTrafficLights.h"
#include <SharedUtility.h>

CTrafficLights * CTrafficLights::m_pInstance;

CTrafficLights::CTrafficLights() :
	m_ulTimeSet(SharedUtility::GetTime()),
	m_bIsLocked(false),
	m_eStateSet(TRAFFIC_LIGHT_STATE_GREEN_RED),
	m_uiGreenDuration(DEFAULT_GREEN_DURATION),
	m_uiYellowDuration(DEFAULT_YELLOW_DURATION),
	m_uiRedDuration(DEFAULT_RED_DURATION)
{
	// Set our instance
	m_pInstance = this;
}

CTrafficLights::~CTrafficLights()
{
	// Reset our instance
	m_pInstance = NULL;
}

void CTrafficLights::Reset()
{
	m_ulTimeSet = SharedUtility::GetTime();
	m_bIsLocked = false;
	m_eStateSet = TRAFFIC_LIGHT_STATE_GREEN_RED;
	m_uiGreenDuration = DEFAULT_GREEN_DURATION;
	m_uiYellowDuration = DEFAULT_YELLOW_DURATION;
	m_uiRedDuration = DEFAULT_RED_DURATION;
	CalculateCycleTime();
}

bool CTrafficLights::SetState(eTrafficLightState state)
{
	if(state < TRAFFIC_LIGHT_STATE_MAX)
	{
		m_eStateSet = state;
		m_ulTimeSet = SharedUtility::GetTime();

#ifdef _SERVER
		SyncState();
#endif
		return true;
	}
	return false;
}

CTrafficLights::eTrafficLightState CTrafficLights::GetState()
{
	if(IsLocked())
		return m_eStateSet;

	if(m_eStateSet >= TRAFFIC_LIGHT_STATE_FLASHING_FLASHING)
		return m_eStateSet;

	if(m_uiTotalDuration == 0)
		return TRAFFIC_LIGHT_STATE_DISABLED_DISABLED;


	// Get the state based on the time elapsed in that cycle
	unsigned int uiTimePassed = GetTimeThisCylce();
	if(uiTimePassed < m_uiGreenDuration)
		return TRAFFIC_LIGHT_STATE_GREEN_RED;

	else if(uiTimePassed < m_uiGreenDuration + m_uiYellowDuration)
		return TRAFFIC_LIGHT_STATE_YELLOW_RED;
	
	else if(uiTimePassed < m_uiGreenDuration + m_uiYellowDuration + m_uiRedDuration)
		return TRAFFIC_LIGHT_STATE_RED_RED_1;
	
	else if(uiTimePassed < m_uiGreenDuration + 2 * m_uiYellowDuration + m_uiRedDuration)
		return TRAFFIC_LIGHT_STATE_RED_TO_GREEN;
	
	else if(uiTimePassed < 2 * m_uiGreenDuration + 2 * m_uiYellowDuration + m_uiRedDuration)
		return TRAFFIC_LIGHT_STATE_RED_GREEN;
	
	else if(uiTimePassed < 2 * m_uiGreenDuration + 3 * m_uiYellowDuration + m_uiRedDuration)
		return TRAFFIC_LIGHT_STATE_RED_YELLOW;
	
	else if(uiTimePassed < 2 * m_uiGreenDuration + 3 * m_uiYellowDuration + 2 * m_uiRedDuration)
		return TRAFFIC_LIGHT_STATE_RED_RED_2;

	else
		return TRAFFIC_LIGHT_STATE_TO_GREEN_RED;
}

CTrafficLights::eTrafficLightState CTrafficLights::GetSetState()
{
	return m_eStateSet;
}

unsigned int CTrafficLights::GetTimeThisCylce()
{
	if(m_uiTotalDuration == 0)
		return 0;

	unsigned int uiTimePassed = SharedUtility::GetTime() - m_ulTimeSet;
	return uiTimePassed % m_uiTotalDuration;
}

void CTrafficLights::SetTimeThisCycle(unsigned int uiTime)
{
	m_ulTimeSet = SharedUtility::GetTime() - uiTime;
}

void CTrafficLights::CalculateCycleTime()
{
	if(m_eStateSet >= TRAFFIC_LIGHT_STATE_FLASHING_FLASHING && m_eStateSet <= TRAFFIC_LIGHT_STATE_DISABLED_FLASHING)
		m_uiTotalDuration = 2 * m_uiYellowDuration;
	else
		m_uiTotalDuration = 2 * ( m_uiGreenDuration + 2 * m_uiYellowDuration + m_uiRedDuration );
}

void CTrafficLights::SetLocked(bool bLocked)
{
	m_bIsLocked = bLocked;
}

bool CTrafficLights::IsLocked()
{
	return m_bIsLocked || m_eStateSet >= TRAFFIC_LIGHT_STATE_FLASHING_FLASHING;
}

bool CTrafficLights::IsUsingDefaultDurations()
{
	// always using default durations when all lights are off
	if(m_eStateSet == TRAFFIC_LIGHT_STATE_DISABLED_DISABLED)
		return true;

	// some lights are flashing, thus only the yellow light is relevant
	if(m_eStateSet >= TRAFFIC_LIGHT_STATE_FLASHING_FLASHING)
		return m_uiYellowDuration == DEFAULT_YELLOW_DURATION;
	
	// Check all lights
	return m_uiGreenDuration == DEFAULT_GREEN_DURATION && m_uiYellowDuration == DEFAULT_YELLOW_DURATION && m_uiRedDuration == DEFAULT_RED_DURATION;
}

void CTrafficLights::ResetDefaultDurations()
{
	// save the old state
	eTrafficLightState eState = GetState();

	// Update the durations
	m_uiGreenDuration = DEFAULT_GREEN_DURATION;
	m_uiYellowDuration = DEFAULT_YELLOW_DURATION;
	m_uiRedDuration = DEFAULT_RED_DURATION;
	CalculateCycleTime();

	// Total duration is 0, thus we can't possibly work
	if(m_uiTotalDuration == 0)
		SetState(TRAFFIC_LIGHT_STATE_DISABLED_DISABLED);

	// relevant to the current light state, thus update it
	else if(eState != TRAFFIC_LIGHT_STATE_DISABLED_DISABLED)
		SetState(eState);
}

void CTrafficLights::SetGreenDuration(unsigned int uiDuration)
{
	if(uiDuration > 0)
	{
		// save the old state
		eTrafficLightState eState = GetState();
		
		// Update the durations
		m_uiGreenDuration = uiDuration;
		CalculateCycleTime();

		// Total duration is 0, thus we can't possibly work
		if(m_uiTotalDuration == 0)
			SetState(TRAFFIC_LIGHT_STATE_DISABLED_DISABLED);

		// relevant to the current light state, thus update it
		else if(eState <= TRAFFIC_LIGHT_STATE_TO_GREEN_RED || eState == TRAFFIC_LIGHT_STATE_GREEN_GREEN)
			SetState(eState);
	}
}

void CTrafficLights::SetYellowDuration(unsigned int uiDuration)
{	
	if(uiDuration > 0)
	{
		// save the old state
		eTrafficLightState eState = GetState();

		// Update the durations
		m_uiYellowDuration = uiDuration;
		CalculateCycleTime();

		// Total duration is 0, thus we can't possibly work
		if(m_uiTotalDuration == 0)
			SetState(TRAFFIC_LIGHT_STATE_DISABLED_DISABLED);

		// relevant to the current light state, thus update it
		else if(eState < TRAFFIC_LIGHT_STATE_DISABLED_DISABLED)
			SetState(eState);
	}
}

void CTrafficLights::SetRedDuration(unsigned int uiDuration)
{
	if(uiDuration > 0)
	{
	// save the old state
		eTrafficLightState eState = GetState();

		// Update the durations
		m_uiRedDuration = uiDuration;
		CalculateCycleTime();

		// Total duration is 0, thus we can't possibly work
		if(m_uiTotalDuration == 0)
			SetState(TRAFFIC_LIGHT_STATE_DISABLED_DISABLED);

		// relevant to the current light state, thus update it
		else if(eState <= TRAFFIC_LIGHT_STATE_TO_GREEN_RED)
			SetState(eState);
	}
}

unsigned int CTrafficLights::GetGreenDuration()
{
	return m_uiGreenDuration;
}

unsigned int CTrafficLights::GetYellowDuration()
{
	return m_uiYellowDuration;
}

unsigned int CTrafficLights::GetRedDuration()
{
	return m_uiRedDuration;
}

CTrafficLights::eGTATrafficLightState CTrafficLights::GetTrafficLightState()
{
	switch(GetState())
	{
		case TRAFFIC_LIGHT_STATE_GREEN_GREEN:
		case TRAFFIC_LIGHT_STATE_GREEN_RED:
			return GTA_TRAFFIC_LIGHT_STATE_GREEN;

		case TRAFFIC_LIGHT_STATE_YELLOW_RED:
		case TRAFFIC_LIGHT_STATE_TO_GREEN_RED:
			return GTA_TRAFFIC_LIGHT_STATE_YELLOW;

		case TRAFFIC_LIGHT_STATE_RED_RED_1:
		case TRAFFIC_LIGHT_STATE_RED_TO_GREEN:
		case TRAFFIC_LIGHT_STATE_RED_GREEN:
		case TRAFFIC_LIGHT_STATE_RED_YELLOW:
		case TRAFFIC_LIGHT_STATE_RED_RED_2:
			return GTA_TRAFFIC_LIGHT_STATE_RED;

		case TRAFFIC_LIGHT_STATE_FLASHING_FLASHING:
		case TRAFFIC_LIGHT_STATE_FLASHING_DISABLED:
			if(GetTimeThisCylce() > m_uiYellowDuration || IsLocked())
				return GTA_TRAFFIC_LIGHT_STATE_YELLOW;
	}
	return GTA_TRAFFIC_LIGHT_STATE_DISABLED;
}

CTrafficLights::eGTATrafficLightState CTrafficLights::GetTrafficLightAltState()
{
	switch(GetState())
	{
		case TRAFFIC_LIGHT_STATE_GREEN_RED:
		case TRAFFIC_LIGHT_STATE_YELLOW_RED:
		case TRAFFIC_LIGHT_STATE_RED_RED_1:
			return GTA_TRAFFIC_LIGHT_STATE_RED;

		case TRAFFIC_LIGHT_STATE_GREEN_GREEN:
		case TRAFFIC_LIGHT_STATE_RED_GREEN:
			return GTA_TRAFFIC_LIGHT_STATE_GREEN;

		case TRAFFIC_LIGHT_STATE_RED_YELLOW:
		case TRAFFIC_LIGHT_STATE_RED_TO_GREEN:
			return GTA_TRAFFIC_LIGHT_STATE_YELLOW;

		case TRAFFIC_LIGHT_STATE_RED_RED_2:
		case TRAFFIC_LIGHT_STATE_TO_GREEN_RED:
			return GTA_TRAFFIC_LIGHT_STATE_RED;

		case TRAFFIC_LIGHT_STATE_FLASHING_FLASHING:
		case TRAFFIC_LIGHT_STATE_DISABLED_FLASHING:
			if(GetTimeThisCylce() > m_uiYellowDuration || IsLocked())
				return GTA_TRAFFIC_LIGHT_STATE_YELLOW;
	}
	return GTA_TRAFFIC_LIGHT_STATE_DISABLED;
}