//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVHud.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVHud_h
#define CIVHud_h

#include <Common.h>
#include <Math\CMaths.h>
#include <IV\IVCommon.h>

class CIVHud {
public:

	static	void	SetHudVisible(bool bVisible);
	static	bool	IsHudVisible(void);

	static	void	SetRadarVisible(bool bVisible);
	static	bool	IsRadarVisible(void);

	static	void	SetPlayerNamesVisible(BYTE byteVisible);
	static	BYTE	ArePlayerNamesVisible(void);

	static	void	SetAreaNamesEnabled(bool bEnabled);
	static	bool	AreAreaNamesEnabled();
};

#endif // CIVHud_h