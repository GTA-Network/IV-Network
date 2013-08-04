//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CIVVehicle.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVVehicle.h"
#include <Game/COffsets.h>

CIVVehicle::CIVVehicle( ) : CIVPhysical( )
{

}

CIVVehicle::CIVVehicle( IVVehicle * pVehicle ) : CIVPhysical( pVehicle )
{

}

CIVVehicle::~CIVVehicle( )
{

}

void CIVVehicle::SetVehicle( IVVehicle * pVehicle )
{
	SetPhysical( pVehicle );
}

IVVehicle * CIVVehicle::GetVehicle( )
{
	return (IVVehicle *)GetPhysical( );
}

void CIVVehicle::SetColors( unsigned char ucColor1, unsigned char ucColor2, unsigned char ucColor3, unsigned char ucColor4 )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
	{
		// Set the colours
		pVehicle->m_byteColors[0] = ucColor1;
		pVehicle->m_byteColors[1] = ucColor2;
		pVehicle->m_byteColors[2] = ucColor3;
		pVehicle->m_byteColors[3] = ucColor4;

		// Refresh the vehicle colors
		_asm mov ecx, pVehicle;
		_asm call COffsets::FUNC_CVehicle__RefreshColours;
	}
}

void CIVVehicle::GetColors( unsigned char * ucColor1, unsigned char * ucColor2, unsigned char * ucColor3, unsigned char * ucColor4 )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
	{
		// Get the colours
		*ucColor1 = pVehicle->m_byteColors[0];
		*ucColor2 = pVehicle->m_byteColors[1];
		*ucColor3 = pVehicle->m_byteColors[2];
		*ucColor4 = pVehicle->m_byteColors[3];
	}
}

void CIVVehicle::SetMaxPassengers( BYTE byteMaxPassengers )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
		pVehicle->m_byteMaxPassengers = byteMaxPassengers;
}

BYTE CIVVehicle::GetMaxPassengers( )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
		return pVehicle->m_byteMaxPassengers;

	return 0;
}

void CIVVehicle::SetDriver( IVPed * pPed )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
		pVehicle->m_pDriver = pPed;
}

IVPed * CIVVehicle::GetDriver( )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
		return pVehicle->m_pDriver;

	return NULL;
}

void CIVVehicle::SetPassenger( BYTE byteSeat, IVPed * pPassenger )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
		if( byteSeat < 8 )
			pVehicle->m_pPassengers[ byteSeat ] = pPassenger;
}

IVPed * CIVVehicle::GetPassenger( BYTE byteSeat )
{
	// Get the vehicle pointer
	IVVehicle * pVehicle = GetVehicle( );

	// Is the pointer valid?
	if( pVehicle )
		if( byteSeat < 8 )
			return pVehicle->m_pPassengers[ byteSeat ];

	return NULL;
}