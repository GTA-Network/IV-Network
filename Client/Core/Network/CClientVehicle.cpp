//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CClientVehicle.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CClientVehicle.h"
#include "CClientPlayer.h"
#include <Game/IVEngine/CIVModelManager.h>
#include <IV/CIVScript.h>
#include <CCore.h>
extern CCore * g_pCore;

CClientVehicle::CClientVehicle( int iVehicleModel, CVector3 vecPos, float fAngle, BYTE color1, BYTE color2, BYTE color3, BYTE color4 )
{
	m_pVehicle = NULL;
	m_vehicleId = INVALID_ENTITY_ID;
	m_pDriver = NULL;

	// Get the model hash from the model id
	DWORD dwModelHash = CIVModelManager::VehicleIdToModelHash( iVehicleModel );

	// Get the model index
	int iVehicleModelIndex = CIVModelManager::GetModelIndexFromHash( dwModelHash );

	// Set the model info
	m_pModelInfo = g_pCore->GetGame()->GetModelInfo( iVehicleModelIndex );

	// Set the color
	m_byteColor[0] = color1;
	m_byteColor[1] = color2;
	m_byteColor[2] = color3;
	m_byteColor[3] = color4;

	// Set the rotation
	m_fSpawnAngle = fAngle;

	// Set the spawn position
	memcpy(&m_vecSpawnPosition,&vecPos,sizeof(CVector3));

	// Mark as not spawned
	m_bSpawned = false;
}

CClientVehicle::~CClientVehicle( )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
	{
		// Destroy the vehicle
		Destroy( );
	}
}

bool CClientVehicle::Create( )
{
	// Is the vehicle already spawned?
	if( IsSpawned() )
		return false;

	// Load the model
	m_pModelInfo->Load( );

	// Get the model hash
	DWORD dwModelHash = m_pModelInfo->GetHash();

	// Create the vehicle
	CIVScript::CreateCar( dwModelHash, 0.0f, 0.0f, 0.0f, &m_uiVehicleHandle, true );

	// Create the vehicle instance
	m_pVehicle = new CIVVehicle( g_pCore->GetGame()->GetPools()->GetVehiclePool()->AtHandle( m_uiVehicleHandle ) );

	// Add the vehicle to the world
	m_pVehicle->AddToWorld();

	// Disable damage(until we have synced the damage)
	CIVScript::SetCarCanBeDamaged( GetScriptingHandle(), false);
	CIVScript::SetCarCanBeVisiblyDamaged( GetScriptingHandle(), false);

	// Mark as spawned
	m_bSpawned = true;

	CLogFile::Printf( "Created vehicle! (Id: %d, Handle: %d)", m_vehicleId, m_uiVehicleHandle );

	return true;
}

void CClientVehicle::Destroy( )
{
	// Is the vehicle not spawned?
	if( !IsSpawned() )
		return;

	// Remove the vehicle from the world
	m_pVehicle->RemoveFromWorld( );

	// Destroy the vehicle
	CIVScript::DeleteCar( &m_uiVehicleHandle );

	// Delete the vehicle instance
	SAFE_DELETE( m_pVehicle );

	// Mark as not spawned
	m_bSpawned = false;
}

void CClientVehicle::Respawn( )
{
	CIVScript::SetCarCoordinates( GetScriptingHandle(), m_vecSpawnPosition.fX, m_vecSpawnPosition.fY, m_vecSpawnPosition.fZ );
	CIVScript::FixCar( GetScriptingHandle() );
}

void CClientVehicle::SetSpawnPosition(CVector3 vecPos)
{
	if(IsSpawned())
		memcpy(&m_vecSpawnPosition,&vecPos,sizeof(CVector3));
}

void CClientVehicle::SetPosition( CVector3 vecPosition )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		CIVScript::SetCarCoordinates( GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ );
}

void CClientVehicle::GetPosition( CVector3 * vecPosition )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		m_pVehicle->GetPosition( vecPosition );
}

void CClientVehicle::GetMoveSpeed( CVector3 * vecMoveSpeed )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		m_pVehicle->GetMoveSpeed( vecMoveSpeed );
}

void CClientVehicle::GetTurnSpeed( CVector3 * vecTurnSpeed )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		m_pVehicle->GetTurnSpeed( vecTurnSpeed );
}

void CClientVehicle::SetColors( BYTE color1, BYTE color2, BYTE color3, BYTE color4 )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
	{
		m_byteColor[0] = color1;
		m_byteColor[1] = color2;
		m_byteColor[2] = color3;
		m_byteColor[3] = color4;

		// Set the colors
		m_pVehicle->SetColors( color1, color2, color3, color4 );
	}
}

void CClientVehicle::SetHeading(float fAngle)
{
	if(IsSpawned())
		CIVScript::SetCarHeading( GetScriptingHandle(), fAngle );
}

BYTE CClientVehicle::GetMaxPassengers( )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		return m_pVehicle->GetMaxPassengers();

	return 0;
}

void CClientVehicle::SetOccupant( BYTE byteSeat, CClientPlayer * pPlayer )
{
	// Is the player pointer valid?
	if( pPlayer )
	{
		// Is this the driver?
		if( byteSeat == 0 )
			m_pVehicle->SetDriver( pPlayer->GetPlayerPed()->GetPed() );
		else
			m_pVehicle->SetPassenger( (byteSeat - 1), pPlayer->GetPlayerPed()->GetPed() );
	}
	else
	{
		// Is this the driver?
		if( byteSeat == 0 )
			m_pVehicle->SetDriver( NULL );
		else
			m_pVehicle->SetPassenger( (byteSeat - 1), NULL );
	}
}

CClientPlayer * CClientVehicle::GetOccupant( BYTE byteSeat )
{
	// Is this the driver?
	if( byteSeat == 0 )
		return m_pDriver;

	if(m_pPassengers[byteSeat - 1] != NULL)
		return m_pPassengers[ byteSeat - 1 ];
	else
		return NULL;
}

void CClientVehicle::Serialize( CBitStream * bitStream )
{
	
}

void CClientVehicle::Deserialize( CBitStream * bitStream )
{

}