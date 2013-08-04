//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CFPSCounter.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CFPSCounter.h"
#include <SharedUtility.h>

CFPSCounter::CFPSCounter(void)
{
	m_ulLastTimeDrop = 0;
	m_uiCurrentFrames = 0;
	m_uiFramesPerSecond = 0;
}

CFPSCounter::~CFPSCounter(void)
{

}

// Frame render
void CFPSCounter::Frame(void)
{
	// Increase the current frame count on this second
	m_uiCurrentFrames++;
}

// Pulse (for drop value if needed)
void CFPSCounter::Pulse(void)
{
	// Get the current time
	unsigned long ulCurrentTime = SharedUtility::GetTime( );

	// Has 1 second passed?
	if( (ulCurrentTime - m_ulLastTimeDrop) >= 1000 )
	{
		// Set the total FPS count
		m_uiFramesPerSecond = m_uiCurrentFrames;

		// Reset the current frame count
		m_uiCurrentFrames = 0;

		// Set the last time
		m_ulLastTimeDrop = ulCurrentTime;
	}
}