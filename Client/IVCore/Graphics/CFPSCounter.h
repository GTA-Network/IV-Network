//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CFPSCounter.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CFPSCounter_h
#define CFPSCounter_h

class CFPSCounter{
private:
	unsigned long		m_ulLastTime;
	unsigned			m_uiCurrentFrames;
	unsigned			m_uiFramesPerSecond;

public:
						CFPSCounter();
						~CFPSCounter() { };

	void				Pulse();
	void				Reset();

	unsigned			GetFPS() { return m_uiFramesPerSecond; }

};

#endif // CFPSCounter_h