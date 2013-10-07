//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVPlayerPed.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPlayerPed.h"

CIVPlayerPed::CIVPlayerPed( ) :
	CIVPed( )
{

}

CIVPlayerPed::CIVPlayerPed( IVPlayerPed * pPlayerPed ) :
	CIVPed( pPlayerPed )
{

}

CIVPlayerPed::~CIVPlayerPed( )
{
	// Call the CIVPed deconstructor
	CIVPed::~CIVPed( );
}

void CIVPlayerPed::SetPlayerPed( IVPlayerPed * pPlayerPed )
{
	// Set the ped
	SetPed( pPlayerPed );
}

IVPlayerPed * CIVPlayerPed::GetPlayerPed( )
{
	// Get the ped
	return (IVPlayerPed *)GetPed( );
}