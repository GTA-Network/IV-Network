//================ IV:Multiplayer - http://github.com/IVMultiplayer/Ivmultiplayer ================
//
// File: CIVPed.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVPed.h"
#include <CCore.h>
#include "CIVPedTaskManager.h"
extern CCore * g_pCore;

CIVPed::CIVPed( ) : CIVPhysical( )
{

}

CIVPed::CIVPed( IVPed * pPed ) : CIVPhysical( pPed )
{
	// Reset the task manager
	m_pPedTaskManager = NULL;

	// Set the ped
	SetPed( pPed );
}

CIVPed::~CIVPed( )
{
	// Set the ped
	SetPed( NULL );
}

void CIVPed::SetPed( IVPed * pPed )
{
	SetPhysical( pPed );

	// Do we have a valid task manager?
	if( m_pPedTaskManager )
	{
		// Delete the ped task manager
		SAFE_DELETE( m_pPedTaskManager );
	}

	// Do we have a valid ped pointer?
	if( pPed )
	{
		// Create the ped task manager
		m_pPedTaskManager = new CIVPedTaskManager( (IVPedTaskManager *)&(pPed->m_pPedIntelligence->m_pPedTaskManager), this );
	}
}

IVPed * CIVPed::GetPed( )
{
	return (IVPed *)GetPhysical( );
}

void CIVPed::SetPlayerInfo( IVPlayerInfo * pPlayerInfo )
{
	// Get the ped
	IVPed * pPed = GetPed( );

	// Set the player info
	if( pPed )
		pPed->m_pPlayerInfo = pPlayerInfo;
}

IVPlayerInfo * CIVPed::GetPlayerInfo( )
{
	// Get the ped
	IVPed * pPed = GetPed( );

	// Get the player info
	if( pPed )
		return pPed->m_pPlayerInfo;

	return NULL;
}

void CIVPed::SetCurrentHeading( float fCurrentHeading )
{
	// Get the ped
	IVPed * pPed = GetPed( );

	// Set the current heading
	if( pPed )
		pPed->m_fCurrentHeading = fCurrentHeading;
}

float CIVPed::GetCurrentHeading( )
{
	// Get the ped
	IVPed * pPed = GetPed( );

	// Get the current heading
	if( pPed )
		return pPed->m_fCurrentHeading;

	return 0.0f;
}

void CIVPed::SetDucking( bool bDucking )
{
	// Get the ped
	IVPed * pPed = GetPed( );

	if( pPed )
	{
		int iDuck = (int)bDucking;

		_asm	push -1;
		_asm	push iDuck;
		_asm	mov ecx, pPed;
		_asm	call COffsets::FUNC_CPed__SetDucking;
	}
}

bool CIVPed::IsDucking( )
{
	// Get the ped
	IVPed * pPed = GetPed( );

	if( pPed )
	{
		bool bDucking = false;

		_asm	mov ecx, pPed;
		_asm	call COffsets::FUNC_CPed__IsDucking;
		_asm	mov bDucking, al;

		return bDucking;
	}

	return false;
}

bool CIVPed::IsInVehicle( )
{
	// Get the ped pointer
	IVPed * pPed = GetPed( );

	// Is the ped pointer valid?
	if( pPed )
		return ((pPed->m_byteUnknown & 4) != 0);

	return false;
}

void CIVPed::SetCurrentVehicle( IVVehicle * pVehicle )
{
	// Get the ped pointer
	IVPed * pPed = GetPed( );

	// Is the ped pointer valid?
	if( pPed )
		pPed->m_pCurrentVehicle = pVehicle;
}

IVVehicle * CIVPed::GetCurrentVehicle( )	
{
	// Get the ped pointer
	IVPed * pPed = GetPed( );

	// Is the ped pointer valid?
	if( pPed )
		return pPed->m_pCurrentVehicle;

	return NULL;
}