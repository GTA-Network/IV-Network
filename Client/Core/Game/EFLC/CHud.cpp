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

#include "CHud.h"
#include <Game/COffsets.h>

_GAME_BEGIN

void CHud::SetHudVisible( bool bVisible )
{
	*(bool *)COffsets::VAR_HudEnabled = bVisible;
}

bool CHud::IsHudVisible( )
{
	return *(bool *)COffsets::VAR_HudEnabled;
}

void CHud::SetRadarVisible( bool bVisible )
{
	*(bool *)COffsets::VAR_RadarVisible = bVisible;
}

bool CHud::IsRadarVisible( )
{
	return *(bool *)COffsets::VAR_RadarVisible;
}

void CHud::SetPlayerNamesVisible( BYTE byteVisible )
{
	if( byteVisible < 2 )
		*(BYTE *)COffsets::VAR_PlayerNamesVisible = byteVisible;
	else
		*(BYTE *)COffsets::VAR_PlayerNamesVisible = 0;
}

BYTE CHud::ArePlayerNamesVisible( )
{
	return *(BYTE *)COffsets::VAR_PlayerNamesVisible;
}

void CHud::SetAreaNamesEnabled( bool bEnabled )
{
	*(bool *)COffsets::VAR_AreaNamesDisabled = !bEnabled;
}

bool CHud::AreAreaNamesEnabled( )
{
	return !(*(bool *)COffsets::VAR_AreaNamesDisabled);
}

_GAME_END