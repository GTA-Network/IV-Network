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

#include "CFPSCounter.h"
#include <SharedUtility.h>

CFPSCounter::CFPSCounter() :
	m_ulLastTime(0), 
	m_uiCurrentFrames(0), 
	m_uiFramesPerSecond(0)
{
}

void CFPSCounter::Pulse()
{
	// Increase the current frame count
	m_uiCurrentFrames++;

	// Get the current time
	unsigned long ulCurrentTime = SharedUtility::GetTime();

	// Has 1 second passed?
	if((ulCurrentTime - m_ulLastTime) >= 1000)
	{
		// Set the total FPS count
		m_uiFramesPerSecond = m_uiCurrentFrames;

		// Reset the current frame count
		m_uiCurrentFrames = 0;

		// Set the last time 
		m_ulLastTime = ulCurrentTime;
	}
}

void CFPSCounter::Reset()
{
	m_ulLastTime = 0;
	m_uiCurrentFrames = 0;
	m_uiFramesPerSecond = 0;
}