//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkEntity.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CNetworkEntity.h"
#include <Network/CBitStream.h>
#include <CLogFile.h>
#include "CPlayerEntity.h"
#include "CVehicleEntity.h"
#include <CCore.h>
extern CCore * g_pCore;

CNetworkEntity::CNetworkEntity() :
	m_vecPosition(CVector3()),
	m_vecRotation(CVector3()),
	m_vecMoveSpeed(CVector3()),
	m_vecTurnSpeed(CVector3()),
	m_vecDirection(CVector3()),
	m_vecRoll(CVector3()),
	m_entityId(INVALID_ENTITY),
	m_eType(UNKNOWN_ENTITY),
	m_pPlayerEntity(NULL)
{

}

CNetworkEntity::~CNetworkEntity()
{
}

void CNetworkEntity::GetPosition(CVector3& vecPos)
{
	vecPos = m_vecPosition;
}

void CNetworkEntity::SetPosition(const CVector3& vecPos)
{
	m_vecPosition = vecPos;
}

void CNetworkEntity::GetRotation(CVector3& vecRot)
{
	vecRot = m_vecRotation;
}

void CNetworkEntity::SetRotation(const CVector3& vecRot)
{
	m_vecRotation = vecRot;
}

void CNetworkEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	vecMoveSpeed = m_vecMoveSpeed;
}

void CNetworkEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	m_vecMoveSpeed = vecMoveSpeed;
}

void CNetworkEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	vecTurnSpeed = m_vecTurnSpeed;
}

void CNetworkEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	m_vecTurnSpeed = vecTurnSpeed;
}

void CNetworkEntity::GetDirectionSpeed(CVector3& vecDirectionSpeed)
{
	vecDirectionSpeed = m_vecDirection;
}

void CNetworkEntity::SetDirectionSpeed(const CVector3& vecDirectionSpeed)
{
	m_vecDirection = vecDirectionSpeed;
}

void CNetworkEntity::GetRollSpeed(CVector3& vecRollSpeed)
{
	vecRollSpeed = m_vecRoll;
}

void CNetworkEntity::SetRollSpeed(const CVector3& vecRollSpeed)
{
	m_vecRoll = vecRollSpeed;
}

bool CNetworkEntity::IsMoving()
{
	if(!(m_vecMoveSpeed.fX == 0 && m_vecMoveSpeed.fY == 0 && (m_vecMoveSpeed.fZ >= -0.000020 && m_vecMoveSpeed.fZ <= 0.000020)))
		return true;

	return false;
}

void CNetworkEntity::StopMoving()
{
	m_vecMoveSpeed = CVector3();
}

/*
 * @ This function handles the current packages from the network entity
 * @ So it stores the current values, which are used in the sync package
*/
void CNetworkEntity::Pulse(CPlayerEntity * pPlayer)
{
	// Check if our player ptr
	if(pPlayer)
	{
		// Update player handle
		if(!m_pPlayerEntity)
			m_pPlayerEntity = pPlayer;

		/*
		 * > First start updating basic entity members(e.g. position, movement etc.)
		*/

		// Get the latest position
		pPlayer->GetPosition(m_vecPosition);

		// Get the latest move speed
		pPlayer->GetMoveSpeed(m_vecMoveSpeed);

		// Get the latest turn speed
		pPlayer->GetTurnSpeed(m_vecTurnSpeed);

		// Get the latest direction speed
		pPlayer->GetPlayerPed()->GetDirection(m_vecDirection);

		// Get the latest roll speed
		pPlayer->GetPlayerPed()->GetRoll(m_vecRoll);

		/*
		 * > Now render specific player parts(e.g. rotation, crouch state etc.)
		*/
		// Get the latest rotation
		m_pPlayerHandle.fHeading = pPlayer->GetRotation();

		// Get the latest crouch state
		m_pPlayerHandle.bDuckState = pPlayer->GetPlayerPed()->IsDucking();

		// Get the control state
		pPlayer->GetControlState(&m_pPlayerHandle.pControlState);

		/*
		 * > At last, fetch the weapon data
		*/

		// Get the arm heading circles
		pPlayer->GetContextData()->GetArmHeading(m_pPlayerHandle.sWeaponData.fArmsHeadingCircle);

		// Get the arm rotation circles
		pPlayer->GetContextData()->GetArmUpDown(m_pPlayerHandle.sWeaponData.fArmsUpDownRotation);

		// Get the aim at coordinates
		pPlayer->GetContextData()->GetWeaponAimTarget(m_pPlayerHandle.sWeaponData.vecAimAtCoordinates);

		// Get the shot at coordinates
		pPlayer->GetContextData()->GetWeaponShotSource(m_pPlayerHandle.sWeaponData.vecShotAtCoordinates);

		// Get the shot at target specific coordinates
		pPlayer->GetContextData()->GetWeaponShotTarget(m_pPlayerHandle.sWeaponData.vecShotAtTarget);

		// Get the look at aiming coordinates
		g_pCore->GetGame()->GetCamera()->GetAimPosition(&m_pPlayerHandle.sWeaponData.vecAimAtCoordinates);
	}
}

/*
 * @ This function handles the current packages from the network entity
 * @ So it stores the current values, which are used in the sync package
*/
void CNetworkEntity::Pulse(CVehicleEntity * pVehicle)
{
	// Check if our player ptr
	if(pVehicle)
	{
		// Get the latest position
		pVehicle->GetPosition(m_vecPosition);

		// Get the latest movespeed
		pVehicle->GetMoveSpeed(m_vecMoveSpeed);

		// Get the latest turnspeed
		pVehicle->GetTurnSpeed(m_vecTurnSpeed);

		// Get the latest direction
		pVehicle->GetGameVehicle()->GetDirection(m_vecDirection);

		// Get the latest roll
		pVehicle->GetGameVehicle()->GetRoll(m_vecRoll);
	}
}

/*
 * @ This function fetches the data and creates the packages, which gets send to the server
*/
void CNetworkEntity::Serialize(ePackageType pType)
{
	// Create Sync package here and send it to the server
	RakNet::BitStream * pBitStream = new BitStream;

	// Backup old sync
	memcpy(&m_pEntityLastSync, &m_pEntitySync, sizeof(CNetworkEntitySync));

	// Create package
	m_pEntitySync = *(new CNetworkEntitySync);

	switch(m_eType)
	{
		case PLAYER_ENTITY:
		{
			// If we already set data for our next sync packet, copy the data
			CNetworkEntitySubPlayer * pSyncPacket = &(m_pEntitySync.pPlayerPacket);

			// Apply entity type to package
			m_pEntitySync.pEntityType = PLAYER_ENTITY;

			// Apply current 3D Position to the sync package
			pSyncPacket->vecPosition = m_vecPosition;

			// Apply current 3D Movement to the sync package
			pSyncPacket->vecMovementSpeed = m_vecMoveSpeed;

			// Apply current 3D Turnspeed to the sync package
			pSyncPacket->vecTurnSpeed = m_vecTurnSpeed;

			// Apply current 3D Directionspeed to the sync package
			pSyncPacket->vecDirection = m_vecDirection;

			// Apply current 3D Rollspeed to the sync package
			pSyncPacket->vecRoll = m_vecRoll;

			// Apply current duckstate to the sync package
			m_pEntitySync.pPlayerPacket.bDuckState = m_pPlayerHandle.bDuckState;

			// Apply current heading to the sync package
			m_pEntitySync.pPlayerPacket.fHeading = m_pPlayerHandle.fHeading;

			// Get the control state
			m_pEntitySync.pPlayerPacket.pControlState = m_pPlayerHandle.pControlState;
			
			// Apply current weapon sync data to the sync package
			m_pEntitySync.pPlayerPacket.sWeaponData.fArmsHeadingCircle = m_pPlayerHandle.sWeaponData.fArmsHeadingCircle;
			m_pEntitySync.pPlayerPacket.sWeaponData.fArmsUpDownRotation = m_pPlayerHandle.sWeaponData.fArmsUpDownRotation;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecAimAtCoordinates = m_pPlayerHandle.sWeaponData.vecAimAtCoordinates;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecShotAtCoordinates = m_pPlayerHandle.sWeaponData.vecShotAtCoordinates;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecShotAtTarget = m_pPlayerHandle.sWeaponData.vecShotAtTarget;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecAimAtCoordinates = m_pPlayerHandle.sWeaponData.vecAimAtCoordinates;

			// Merge EntitySync packet with our packet
			memcpy(&m_pEntitySync.pPlayerPacket, pSyncPacket, sizeof(CNetworkEntitySync));

			// Write player onfoot flag into raknet bitstream
			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_ONFOOT);
			break;

		}

		case VEHICLE_ENTITY:
		{
			// If we already set data for our next sync packet, copy the data
			CNetworkEntitySubVehicle * pSyncPacket = &(m_pEntitySync.pVehiclePacket);

			// Apply entity type to package
			m_pEntitySync.pEntityType = VEHICLE_ENTITY;

			// Apply current 3D Position to the sync package
			pSyncPacket->vecPosition = m_vecPosition;

			// Merge EntitySync packet with our packet
			memcpy(&m_pEntitySync.pVehiclePacket, pSyncPacket, sizeof(CNetworkEntitySubVehicle));

			// Stop current case
			break;
		}

		default:
		{
			CLogFile::Print("Failed to get entity type from current entitiy. Sync canceled..");
			break;
		}
	}

	// Write our Entity-Sync to the bitstream
	pBitStream->Write((char *)&m_pEntitySync, sizeof(CNetworkEntitySync));

	// Send package to network
	g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), pBitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, true);
}

RakNet::BitStream CNetworkEntity::ManualSerialize(ePackageType pType)
{
	// Create Sync package here and send it to the server
	RakNet::BitStream * pBitStream = new BitStream;

	// Backup old sync
	memcpy(&m_pEntityLastSync, &m_pEntitySync, sizeof(CNetworkEntitySync));

	// Create package
	m_pEntitySync = *(new CNetworkEntitySync);

	switch(m_eType)
	{
		case PLAYER_ENTITY:
		{
			// If we already set data for our next sync packet, copy the data
			CNetworkEntitySubPlayer * pSyncPacket = &(m_pEntitySync.pPlayerPacket);

			// Apply entity type to package
			m_pEntitySync.pEntityType = PLAYER_ENTITY;

			// Apply current 3D Position to the sync package
			pSyncPacket->vecPosition = m_vecPosition;

			// Apply current 3D Movement to the sync package
			pSyncPacket->vecMovementSpeed = m_vecMoveSpeed;

			// Apply current 3D Turnspeed to the sync package
			pSyncPacket->vecTurnSpeed = m_vecTurnSpeed;

			// Apply current 3D Directionspeed to the sync package
			pSyncPacket->vecDirection = m_vecDirection;

			// Apply current 3D Rollspeed to the sync package
			pSyncPacket->vecRoll = m_vecRoll;

			// Apply current duckstate to the sync package
			m_pEntitySync.pPlayerPacket.bDuckState = m_pPlayerHandle.bDuckState;

			// Apply current heading to the sync package
			m_pEntitySync.pPlayerPacket.fHeading = m_pPlayerHandle.fHeading;

			// Get control state
			m_pEntitySync.pPlayerPacket.pControlState = m_pPlayerHandle.pControlState;
			
			// Apply current weapon sync data to the sync package
			m_pEntitySync.pPlayerPacket.sWeaponData.fArmsHeadingCircle = m_pPlayerHandle.sWeaponData.fArmsHeadingCircle;
			m_pEntitySync.pPlayerPacket.sWeaponData.fArmsUpDownRotation = m_pPlayerHandle.sWeaponData.fArmsUpDownRotation;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecAimAtCoordinates = m_pPlayerHandle.sWeaponData.vecAimAtCoordinates;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecShotAtCoordinates = m_pPlayerHandle.sWeaponData.vecShotAtCoordinates;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecShotAtTarget = m_pPlayerHandle.sWeaponData.vecShotAtTarget;
			m_pEntitySync.pPlayerPacket.sWeaponData.vecAimAtCoordinates = m_pPlayerHandle.sWeaponData.vecAimAtCoordinates;

			// Merge EntitySync packet with our packet
			memcpy(&m_pEntitySync.pPlayerPacket, pSyncPacket, sizeof(CNetworkEntitySubPlayer));

			// Write player onfoot flag into raknet bitstream
			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_ONFOOT);
			break;

		}

		case VEHICLE_ENTITY:
		{
			// If we already set data for our next sync packet, copy the data
			CNetworkEntitySubVehicle * pSyncPacket = &(m_pEntitySync.pVehiclePacket);

			// Apply entity type to package
			m_pEntitySync.pEntityType = VEHICLE_ENTITY;

			// Apply current 3D Position to the sync package
			pSyncPacket->vecPosition = m_vecPosition;

			// Merge EntitySync packet with our packet
			memcpy(&m_pEntitySync.pVehiclePacket, pSyncPacket, sizeof(CNetworkEntitySubVehicle));

			// Stop current case
			break;
		}

		default:
		{
			CLogFile::Print("Failed to get entity type from current entitiy. Sync canceled..");
			break;
		}
	}

	// Write our Entity-Sync to the bitstream
	pBitStream->Write((char *)&m_pEntitySync, sizeof(CNetworkEntitySync));

	// return bitstream package
	return (pBitStream != NULL);
}


void CNetworkEntity::Deserialize(RakNet::BitStream * pBitStream, ePackageType pType)
{
	// Get Sync package here and recieve it to the server
	
	CNetworkEntitySync * pSyncPackage = new CNetworkEntitySync;
	pBitStream->Read((char *)pSyncPackage, sizeof(CNetworkEntitySync));
	
	switch(pSyncPackage->pEntityType)
	{
		case PLAYER_ENTITY:
		{
			if(!m_pPlayerEntity)
				return;

			// Pack stuff temporary in local variables
			float fAimHeading[2];
			fAimHeading[0] = pSyncPackage->pPlayerPacket.sWeaponData.fArmsHeadingCircle;
			fAimHeading[1] = pSyncPackage->pPlayerPacket.sWeaponData.fArmsUpDownRotation;

			CVector3 vecWeaponData[3];
			vecWeaponData[0] = pSyncPackage->pPlayerPacket.sWeaponData.vecAimAtCoordinates;
			vecWeaponData[1] = pSyncPackage->pPlayerPacket.sWeaponData.vecShotAtCoordinates;
			vecWeaponData[2] = pSyncPackage->pPlayerPacket.sWeaponData.vecShotAtTarget;

			m_pPlayerEntity->ApplySyncData(
				// Apply current 3D Position to the sync package
				pSyncPackage->pPlayerPacket.vecPosition,

				// Apply current 3D Movement to the sync package
				pSyncPackage->pPlayerPacket.vecMovementSpeed,

				// Apply current 3D Turnspeed to the sync package
				pSyncPackage->pPlayerPacket.vecTurnSpeed,

				// Apply current 3D Directionspeed to the sync package
				pSyncPackage->pPlayerPacket.vecDirection,

				// Apply current 3D Rollspeed to the sync package
				pSyncPackage->pPlayerPacket.vecRoll,

				// Apply current duckstate to the sync package
				pSyncPackage->pPlayerPacket.bDuckState,

				// Apply current heading to the sync package
				pSyncPackage->pPlayerPacket.fHeading,

				//Apply current weapon sync data to the sync package
				fAimHeading,

				vecWeaponData);

			m_pPlayerEntity->PreStoreIVSynchronization(false, false, NULL);
			m_pPlayerEntity->SetControlState(&pSyncPackage->pPlayerPacket.pControlState);
			// Finished deserialize, break!
			break;
		}
		default:
		{
			CLogFile::Printf("[%s]: Unkown entity type, process...",__FUNCTION__);
			break;
		}
	}

	// TODO: apply the data from the syncpackage to the vehicles/peds
}