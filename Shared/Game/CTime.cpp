//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTime.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CTime.h"
#include <SharedUtility.h>

CTime            * CTime::m_pInstance = NULL;
const unsigned int CTime::DEFAULT_MINUTE_DURATION = 2000;

CTime::CTime() :
	m_ulTimeSet(SharedUtility::GetTime()),
	m_ucHour(12),
	m_ucMinute(0),
	m_ucDayOfWeek(0),
	m_uiMinuteDuration(DEFAULT_MINUTE_DURATION)
{
	// Set our instance
	m_pInstance = this;
}

CTime::~CTime()
{
	// Reset our instance
	m_pInstance = NULL;
}

void CTime::SetTime(const unsigned char ucHour, const unsigned char ucMinute)
{
	if(ucHour >= 24)
		SetDayOfWeek(((ucHour) / 24) - 1);
	m_ulTimeSet = SharedUtility::GetTime();
	m_ucHour = ucHour;
	m_ucMinute = ucMinute;
}

void CTime::GetTime(unsigned char *ucHour, unsigned char *ucMinute)
{
	if(m_uiMinuteDuration == 0)
	{
		*ucHour = m_ucHour;
		*ucMinute = m_ucMinute;
	}
	else
	{
		unsigned long ulCurrentTime = SharedUtility::GetTime();
		unsigned int uiMinutesPassed = ( ( ulCurrentTime - m_ulTimeSet ) / m_uiMinuteDuration );
		unsigned int uiHoursPassed = ( m_ucMinute + uiMinutesPassed ) / 60;

		*ucHour = ( uiHoursPassed + m_ucHour ) % 24;
		*ucMinute = ( uiMinutesPassed + m_ucMinute ) % 60;
	}
}

void CTime::SetMinuteDuration(const unsigned int uiMinuteDuration)
{
	// Make sure we're calculating future times from ours
	unsigned char ucHour = 0, ucMinute = 0;
	GetTime(&ucHour, &ucMinute);

	if(uiMinuteDuration > 0)
		m_uiMinuteDuration = uiMinuteDuration;

	SetTime(ucHour, ucMinute);
}

unsigned int CTime::GetMinuteDuration()
{
	return m_uiMinuteDuration;
}

void CTime::SetDayOfWeek(const unsigned char ucDayOfWeek)
{
	unsigned char ucHour = 0, ucMinute = 0;
	GetTime(&ucHour, &ucMinute);

	m_ucDayOfWeek = ucDayOfWeek;

	SetTime(ucHour, ucMinute);
}

unsigned char CTime::GetDayOfWeek()
{
	if(m_uiMinuteDuration == 0)
		return m_ucDayOfWeek;

	else
	{
		unsigned long ulCurrentTime = SharedUtility::GetTime();
		unsigned int uiMinutesPassed = ( ( ulCurrentTime - m_ulTimeSet ) / m_uiMinuteDuration ) + m_ucHour * 60 + m_ucMinute;
		return ( ( ( uiMinutesPassed ) / ( 24 * 60 ) ) + m_ucDayOfWeek ) % 7;
	}
}

void CTime::Pulse()
{
	;
}