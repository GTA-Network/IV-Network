//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CTrafficHandler.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CTrafficHandler_h
#define CTrafficHandler_h

#include <Game/CTrafficLights.h>

class CTrafficHandler {

private:
	CTrafficLights	*m_pTrafficLights;
public:
					CTrafficHandler();
					~CTrafficHandler();

	static void		InstallTrafficLightsHook();
	static void		InstallTrafficHook();
};

#endif // CTrafficHandler_h