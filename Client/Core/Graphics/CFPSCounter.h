//================ IV:Multiplayer - https://github.com/XForce/ivmultiplayer ================
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
	unsigned int		m_uiCurrentFrames;
	unsigned int		m_uiFramesPerSecond;

public:
	CFPSCounter( void );
	~CFPSCounter( void );

	void		Pulse( void );

	unsigned int		GetFPS( void ) { return m_uiFramesPerSecond; }

};

#endif // CFPSCounter_h