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