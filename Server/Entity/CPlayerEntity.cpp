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
		if (m_eLastSyncPackageType == RPC_PACKAGE_TYPE_PLAYER_ONFOOT)
		{
			RakNet::BitStream bitStream;
			bitStream.Write(GetId());
			bitStream.Write(CServer::GetInstance()->GetNetworkModule()->GetPlayerPing(GetId()));
			Serialize(&bitStream, m_eLastSyncPackageType);
			CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, -1, true);

			m_ulLastSyncSent = SharedUtility::GetTime();
		}

		if (m_eLastSyncPackageType == RPC_PACKAGE_TYPE_PLAYER_VEHICLE)
		{
			RakNet::BitStream bitStream;
			bitStream.Write(GetId());
			bitStream.Write(CServer::GetInstance()->GetNetworkModule()->GetPlayerPing(GetId()));
			Serialize(&bitStream, m_eLastSyncPackageType);
			CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, -1, true);

			m_ulLastSyncSent = SharedUtility::GetTime();
		}

		if (m_controlState.IsAiming() || m_controlState.IsFiring())
		{
			RakNet::BitStream bitStream;
			CNetworkPlayerWeaponSyncPacket WeaponPacket;
			bitStream.Write(GetId());
			bitStream.Write(CServer::GetInstance()->GetNetworkModule()->GetPlayerPing(GetId()));
			Serialize(&bitStream, RPC_PACKAGE_TYPE_PLAYER_WEAPON);
			CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, -1, true);
		}
	}
};


void CPlayerEntity::SetPosition(const CVector3& vecPosition)
{
	{
		CNetworkEntity::SetPosition(vecPosition);
	}
}


void CScriptPlayer::SetPosition(float fX, float fY, float fZ)
{
	CScriptEntity::SetPosition(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_POSITION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SetRotation(float fX, float fY, float fZ)
{
	CScriptEntity::SetRotation(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_ROTATION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SetMoveSpeed(float fX, float fY, float fZ)
{
	CScriptEntity::SetMoveSpeed(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_MOVE_SPEED), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SetTurnSpeed(float fX, float fY, float fZ)
{
	CScriptEntity::SetTurnSpeed(fX, fY, fZ);
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(CVector3(fX, fY, fZ));
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_TURN_SPEED), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}


void CScriptPlayer::SetHealth(float fHealth)
{
	GetEntity()->SetHealth(fHealth);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(fHealth);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_HEALTH), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SetName(const char* szName)
{
		GetEntity()->SetName(CString(szName));
		free((void*)szName);

		RakNet::BitStream bitStream;
		bitStream.Write(GetEntity()->GetId());
		bitStream.Write(szName);
		CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_NAME_CHANGE), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, INVALID_ENTITY_ID, true);
}

void CScriptPlayer::GiveWeapon(int id, int uiAmmo)
{
	//GetEntity()->GiveWeapon(id, uiAmmo);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(id);
	bitStream.Write(uiAmmo);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_GIVE_WEAPON), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CPlayerEntity::Serialize(RakNet::BitStream * pBitStream, ePackageType pType)
{
	switch (pType)
	{
	case RPC_PACKAGE_TYPE_PLAYER_ONFOOT:
		{
			CNetworkPlayerSyncPacket pSyncPacket;

			GetControlState(pSyncPacket.pControlState);

			// Apply current 3D Position to the sync package
			GetPosition(pSyncPacket.vecPosition);

			// Apply current 3D Movement to the sync package
			GetMoveSpeed(pSyncPacket.vecMovementSpeed);

			// Apply current 3D Turnspeed to the sync package
			GetTurnSpeed(pSyncPacket.vecTurnSpeed);

			//CLogFile::Printf("[%i] %f %f %f", GetId(), pSyncPacket->vecTurnSpeed.fX, pSyncPacket->vecTurnSpeed.fY, pSyncPacket->vecTurnSpeed.fZ);

			// Apply current 3D Directionspeed to the sync package
			pSyncPacket.vecDirection = m_vecDirection;

			// Apply current 3D Rollspeed to the sync package
			pSyncPacket.vecRoll = m_vecRoll;

			// Apply current duckstate to the sync package
			pSyncPacket.bDuckState = m_bDuckState;

			// Apply current heading to the sync package
			pSyncPacket.fHeading = m_fHeading;

			// Apply current weapon sync data to the sync package
			/*pSyncPacket.sWeaponData.fArmsHeadingCircle = m_weaponData.fArmsHeadingCircle;
			pSyncPacket.sWeaponData.fArmsUpDownRotation = m_weaponData.fArmsUpDownRotation;
			pSyncPacket.sWeaponData.vecAimAtCoordinates = m_weaponData.vecAimAtCoordinates;
			pSyncPacket.sWeaponData.vecShotAtCoordinates = m_weaponData.vecShotAtCoordinates;
			pSyncPacket.sWeaponData.vecShotAtTarget = m_weaponData.vecShotAtTarget;
			pSyncPacket.sWeaponData.vecAimAtCoordinates = m_weaponData.vecAimAtCoordinates;*/

			// Merge EntitySync packet with our packet
			//memcpy(&m_pEntitySync.pPlayerPacket, pSyncPacket, sizeof(sNetwork_Sync_Entity_Player));

			// Write player onfoot flag into raknet bitstream
			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_ONFOOT);

			// Write our Entity-Sync to the bitstream
			pBitStream->Write(pSyncPacket);
		}
		break;
	case RPC_PACKAGE_TYPE_PLAYER_WEAPON:
		{
			CNetworkPlayerWeaponSyncPacket WeaponPacket;

			if (m_controlState.IsFiring())
			{
				WeaponPacket.vecAimShotAtCoordinates = GetWeaponShotTarget();
			}
			else
			{
				WeaponPacket.vecAimShotAtCoordinates = GetWeaponAimTarget();
			}

			WeaponPacket.vecShotSource = GetWeaponShotSource();
			WeaponPacket.fArmsHeadingCircle = GetArmHeading();
			WeaponPacket.fArmsUpDownRotation = GetArmUpDown();

			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_WEAPON);
			pBitStream->Write(WeaponPacket);
		}
		break;
	case RPC_PACKAGE_TYPE_PLAYER_VEHICLE:
		{
			CNetworkPlayerVehicleSyncPacket VehiclePacket;
			CVehicleEntity * pVehicle = CServer::GetInstance()->GetVehicleManager()->GetAt(m_vehicleId);
			if (pVehicle)
			{
				VehiclePacket.vehicleId = pVehicle->GetId();
				pVehicle->GetPosition(VehiclePacket.vecPosition);
				pVehicle->GetMoveSpeed(VehiclePacket.vecMoveSpeed);
				pVehicle->GetTurnSpeed(VehiclePacket.vecTurnSpeed);
				pVehicle->GetRotation(VehiclePacket.vecRotation);
				
			}
			GetControlState(VehiclePacket.ControlState);
			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_VEHICLE);
			pBitStream->Write(VehiclePacket);
		}
		break;
	default:
		CLogFile::Printf("Warning: Sync Package type not implemented");
		break;
	}
}

void CPlayerEntity::Deserialize(RakNet::BitStream * pBitStream, ePackageType pType)
{
	switch (pType)
	{
	case RPC_PACKAGE_TYPE_PLAYER_ONFOOT:
		{
			CNetworkPlayerSyncPacket pSyncPlayer;
			pBitStream->Read(pSyncPlayer);

			SetControlState(pSyncPlayer.pControlState);
			SetPosition(pSyncPlayer.vecPosition);

			SetMoveSpeed(pSyncPlayer.vecMovementSpeed);
			SetTurnSpeed(pSyncPlayer.vecTurnSpeed);
			SetDirection(pSyncPlayer.vecDirection);
			SetRoll(pSyncPlayer.vecRoll);
			SetDucking(pSyncPlayer.bDuckState);
			SetHeading(pSyncPlayer.fHeading);

			m_eLastSyncPackageType = pType;
			m_ulLastSyncReceived = SharedUtility::GetTime();
		}
		break;
	case RPC_PACKAGE_TYPE_PLAYER_VEHICLE:
		{
			CNetworkPlayerVehicleSyncPacket VehiclePacket;
			pBitStream->Read(VehiclePacket);
			SetControlState(VehiclePacket.ControlState);
			CVehicleEntity* pVehicle = CServer::GetInstance()->GetVehicleManager()->GetAt(VehiclePacket.vehicleId);
			m_vehicleId = VehiclePacket.vehicleId;
			if (pVehicle)
			{

				pVehicle->SetPosition(VehiclePacket.vecPosition);
				pVehicle->SetMoveSpeed(VehiclePacket.vecMoveSpeed);
				pVehicle->SetTurnSpeed(VehiclePacket.vecTurnSpeed);
				pVehicle->SetRotation(VehiclePacket.vecRotation);
			}
			m_eLastSyncPackageType = pType;
			m_ulLastSyncReceived = SharedUtility::GetTime();
		}
		break;
	case RPC_PACKAGE_TYPE_PLAYER_WEAPON:
		{
			CNetworkPlayerWeaponSyncPacket WeaponPacket;

			pBitStream->Read(WeaponPacket);

			SetWeaponShotTarget(WeaponPacket.vecAimShotAtCoordinates);
			SetWeaponAimTarget(WeaponPacket.vecAimShotAtCoordinates);
			SetWeaponShotSource(WeaponPacket.vecShotSource);
			SetArmHeading(WeaponPacket.fArmsHeadingCircle);
			SetArmUpDown(WeaponPacket.fArmsUpDownRotation);
		}
		break;
	default:
		CLogFile::Printf("Warning: Unknown sync package type");
		break;
	}
}

