//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CPlayerEntity.cpp
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CPlayerEntity.h"
#include <CLogFile.h>
#include <SharedUtility.h>
#include "../CServer.h"

CPlayerEntity::CPlayerEntity()
{
	m_ulLastSyncSent = 0;
}

CPlayerEntity::~CPlayerEntity()
{

}


void CPlayerEntity::Pulse()
{
	// Send the sync only every 50ms to get a nice and smooth sync
	// If sync is crap you can adjust this value
	// TODO: add a value to the server to set this at runtime
	// Example  
	if (m_ulLastSyncSent + (1000 / CServer::GetInstance()->GetSyncRate()) <= SharedUtility::GetTime())
	{
		RakNet::BitStream bitStream;
		bitStream.Write(GetId());
		bitStream.Write(CServer::GetInstance()->GetNetworkModule()->GetPlayerPing(GetId()));
		CServer::GetInstance()->GetPlayerManager()->GetAt(GetId())->Serialize(&bitStream, m_eLastSyncPackageType);

		CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, -1, true);

		m_ulLastSyncSent = SharedUtility::GetTime();
	}
};


void CPlayerEntity::Serialize(RakNet::BitStream * pBitStream, ePackageType pType)
{
	switch (pType)
	{
	case RPC_PACKAGE_TYPE_PLAYER_ONFOOT:
		{
			CNetworkEntitySync m_pEntitySync;

			CNetworkEntitySubPlayer * pSyncPacket = &(m_pEntitySync.pPlayerPacket);

			// Apply entity type to package
			m_pEntitySync.pEntityType = PLAYER_ENTITY;

			GetControlState(pSyncPacket->pControlState);

			// Apply current 3D Position to the sync package
			GetPosition(pSyncPacket->vecPosition);

			// Apply current 3D Movement to the sync package
			GetMoveSpeed(pSyncPacket->vecMovementSpeed);

			// Apply current 3D Turnspeed to the sync package
			GetTurnSpeed(pSyncPacket->vecTurnSpeed);

			CLogFile::Printf("[%i] %f %f %f", GetId(), pSyncPacket->vecTurnSpeed.fX, pSyncPacket->vecTurnSpeed.fY, pSyncPacket->vecTurnSpeed.fZ);

			// Apply current 3D Directionspeed to the sync package
			pSyncPacket->vecDirection = m_vecDirection;

			// Apply current 3D Rollspeed to the sync package
			pSyncPacket->vecRoll = m_vecRoll;

			// Apply current duckstate to the sync package
			pSyncPacket->bDuckState = m_bDuckState;

			// Apply current heading to the sync package
			pSyncPacket->fHeading = m_fHeading;

			// Apply current weapon sync data to the sync package
			pSyncPacket->sWeaponData.fArmsHeadingCircle = m_weaponData.fArmsHeadingCircle;
			pSyncPacket->sWeaponData.fArmsUpDownRotation = m_weaponData.fArmsUpDownRotation;
			pSyncPacket->sWeaponData.vecAimAtCoordinates = m_weaponData.vecAimAtCoordinates;
			pSyncPacket->sWeaponData.vecShotAtCoordinates = m_weaponData.vecShotAtCoordinates;
			pSyncPacket->sWeaponData.vecShotAtTarget = m_weaponData.vecShotAtTarget;
			pSyncPacket->sWeaponData.vecAimAtCoordinates = m_weaponData.vecAimAtCoordinates;

			// Merge EntitySync packet with our packet
			//memcpy(&m_pEntitySync.pPlayerPacket, pSyncPacket, sizeof(sNetwork_Sync_Entity_Player));

			// Write player onfoot flag into raknet bitstream
			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_ONFOOT);

			// Write our Entity-Sync to the bitstream
			pBitStream->Write((char *) &m_pEntitySync, sizeof(CNetworkEntitySync));
		}
		break;
	default:
		CLogFile::Printf("Warning: Sync Package type not implemented");
		break;
	}
}

void CPlayerEntity::Deserialize(RakNet::BitStream * pBitStream, ePackageType pType)
{
	CNetworkEntitySync * pSyncPackage = new CNetworkEntitySync;
	pBitStream->Read((char *) pSyncPackage, sizeof(CNetworkEntitySync));

	switch (pType)
	{
	case RPC_PACKAGE_TYPE_PLAYER_ONFOOT:
		{
			CNetworkEntitySubPlayer * pSyncPlayer = &pSyncPackage->pPlayerPacket;

			SetControlState(pSyncPlayer->pControlState);
			SetPosition(pSyncPlayer->vecPosition);

			SetMoveSpeed(pSyncPlayer->vecMovementSpeed);
			SetTurnSpeed(pSyncPlayer->vecTurnSpeed);
			SetDirection(pSyncPlayer->vecDirection);
			SetRoll(pSyncPlayer->vecRoll);
			SetDucking(pSyncPlayer->bDuckState);
			SetHeading(pSyncPlayer->fHeading);

			// Save weapon sync
			SetArmHeading(pSyncPlayer->sWeaponData.fArmsHeadingCircle);
			SetArmUpDown(pSyncPlayer->sWeaponData.fArmsUpDownRotation);
			SetWeaponAimTarget(pSyncPlayer->sWeaponData.vecAimAtCoordinates);
			SetWeaponShotSource(pSyncPlayer->sWeaponData.vecShotAtCoordinates);
			SetWeaponShotTarget(pSyncPlayer->sWeaponData.vecShotAtTarget);

			m_eLastSyncPackageType = pType;
			m_ulLastSyncReceived = SharedUtility::GetTime();
		}
		break;
	default:
		CLogFile::Printf("Warning: Unknown sync package type");
		break;
	}
}

