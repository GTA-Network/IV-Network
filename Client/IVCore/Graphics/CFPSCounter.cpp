//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CFPSCounter.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CFPSCounter.h"
#include <SharedUtility.h>

CFPSCounter::CFPSCounter() :
	m_ulLastTime(0), m_uiCurrentFrames(0), m_uiFramesPerSecond(0)
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