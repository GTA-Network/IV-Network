//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVWeather.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVWeather.h"
#include <Game/COffsets.h>

void CIVWeather::SetWeather( eWeather weather )
{
	if( weather >= WEATHER_EXTRA_SUNNY && weather <= WEATHER_SUNNY_WINDY_2 )
	{
		_asm	push weather;
		_asm	call COffsets::FUNC_SetWeather;
		_asm	add esp, 4;
	}
}

eWeather CIVWeather::GetWeather( void )
{
	return *(eWeather *)COffsets::VAR_CurrentWeather;
}