//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVWeather.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVWeather_h
#define CIVWeather_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>

class CIVWeather {
public:
	static	void		SetWeather(eWeather weather);
	static	eWeather	GetWeather(void);
};

#endif // CIVWeather_h