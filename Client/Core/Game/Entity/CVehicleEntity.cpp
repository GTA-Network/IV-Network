//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CVehicleEntity.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CVehicleEntity.h"
#include "CPlayerEntity.h"

#include <Game/IVEngine/CIVModelManager.h>
#include <Game/Entity/CVehicleEntity.h>
#include <IV/CIVScript.h>

#include <CCore.h>
extern CCore * g_pCore;

CVehicleEntity::CVehicleEntity( int iVehicleModel, CVector3 vecPos, float fAngle, BYTE color1, BYTE color2, BYTE color3, BYTE color4 )
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

CVehicleEntity::~CVehicleEntity( )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
	{
		// Destroy the vehicle
		Destroy( );
	}
}

bool CVehicleEntity::Create( )
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

bool CVehicleEntity::Destroy( )
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

void CVehicleEntity::Respawn( )
{
	CIVScript::SetCarCoordinates( GetScriptingHandle(), m_vecSpawnPosition.fX, m_vecSpawnPosition.fY, m_vecSpawnPosition.fZ );
	CIVScript::FixCar( GetScriptingHandle() );
}

void CVehicleEntity::SetSpawnPosition(CVector3 vecPos)
{
	if(IsSpawned())
		memcpy(&m_vecSpawnPosition,&vecPos,sizeof(CVector3));
}

void CVehicleEntity::SetPosition( CVector3 vecPosition )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		CIVScript::SetCarCoordinates( GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ );
}

void CVehicleEntity::GetPosition( CVector3 * vecPosition )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		m_pVehicle->GetPosition( vecPosition );
}

void CVehicleEntity::GetMoveSpeed( CVector3 * vecMoveSpeed )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		m_pVehicle->GetMoveSpeed( vecMoveSpeed );
}

void CVehicleEntity::GetTurnSpeed( CVector3 * vecTurnSpeed )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		m_pVehicle->GetTurnSpeed( vecTurnSpeed );
}

void CVehicleEntity::SetColors( BYTE color1, BYTE color2, BYTE color3, BYTE color4 )
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

void CVehicleEntity::SetHeading(float fAngle)
{
	if(IsSpawned())
		CIVScript::SetCarHeading( GetScriptingHandle(), fAngle );
}

BYTE CVehicleEntity::GetMaxPassengers( )
{
	// Is the vehicle spawned?
	if( IsSpawned() )
		return m_pVehicle->GetMaxPassengers();

	return 0;
}

void CVehicleEntity::SetOccupant( BYTE byteSeat, CPlayerEntity * pPlayer )
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

CPlayerEntity * CVehicleEntity::GetOccupant( BYTE byteSeat )
{
	// Is this the driver?
	if( byteSeat == 0 )
		return m_pDriver;

	if(m_pPassengers[byteSeat - 1] != NULL)
		return m_pPassengers[ byteSeat - 1 ];
	else
		return NULL;
}

void CVehicleEntity::Serialize( CBitStream * bitStream )
{
	
}

void CVehicleEntity::Deserialize( CBitStream * bitStream )
{

}