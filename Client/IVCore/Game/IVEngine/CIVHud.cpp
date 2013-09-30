//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVHud.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVHud.h"
#include <Game/COffsets.h>

void CIVHud::SetHudVisible( bool bVisible )
{
	*(bool *)COffsets::VAR_HudEnabled = bVisible;
}

bool CIVHud::IsHudVisible( )
{
	return *(bool *)COffsets::VAR_HudEnabled;
}

void CIVHud::SetRadarVisible( bool bVisible )
{
	*(bool *)COffsets::VAR_RadarVisible = bVisible;
}

bool CIVHud::IsRadarVisible( )
{
	return *(bool *)COffsets::VAR_RadarVisible;
}

void CIVHud::SetPlayerNamesVisible( BYTE byteVisible )
{
	if( byteVisible < 2 )
		*(BYTE *)COffsets::VAR_PlayerNamesVisible = byteVisible;
	else
		*(BYTE *)COffsets::VAR_PlayerNamesVisible = 0;
}

BYTE CIVHud::ArePlayerNamesVisible( )
{
	return *(BYTE *)COffsets::VAR_PlayerNamesVisible;
}

void CIVHud::SetAreaNamesEnabled( bool bEnabled )
{
	*(bool *)COffsets::VAR_AreaNamesDisabled = !bEnabled;
}

bool CIVHud::AreAreaNamesEnabled( )
{
	return !(*(bool *)COffsets::VAR_AreaNamesDisabled);
}