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

CPlayerEntity::CPlayerEntity() :
	m_ulLastSyncSent(0)
{
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

void CScriptPlayer::SetArmour(float fArmour)
{
	GetEntity()->SetArmour(fArmour);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(fArmour);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_ARMOR), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SetWantedLevel(int iWantedLevel)
{
	GetEntity()->SetWantedLevel(iWantedLevel);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iWantedLevel);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_WANTED_LEVEL), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, INVALID_ENTITY_ID, true);
}

void CScriptPlayer::SetHeading(float fHeading)
{
	GetEntity()->SetHeading(fHeading);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(fHeading);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_HEADING), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SetModel(int iModel)
{
	GetEntity()->SetModel(iModel);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iModel);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_MODEL), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, INVALID_ENTITY_ID, true);
}

void CScriptPlayer::SetMoney(int iMoney)
{
	GetEntity()->SetMoney(iMoney);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iMoney);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_MONEY), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, INVALID_ENTITY_ID, true);
}

void CScriptPlayer::SetDimension(int iDimension)
{
	GetEntity()->SetDimension(iDimension);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iDimension);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_DIMENSION), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, INVALID_ENTITY_ID, true);
}

void CScriptPlayer::SetName(CString szName)
{
	GetEntity()->SetName(szName);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(RakNet::RakString(szName.C_String()));
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

void CScriptPlayer::GiveMoney(int iMoney)
{
	GetEntity()->SetMoney(GetEntity()->GetMoney() + iMoney);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(iMoney);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_GIVE_MONEY), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SetColor(DWORD dwColor)
{
	GetEntity()->SetColor(dwColor);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(dwColor);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_COLOR), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptPlayer::SendPlayerMessage(CString sMessage, DWORD dwColor, bool bAllowFormatting)
{
	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(RakNet::RakString(sMessage.C_String()));
	bitStream.Write(dwColor);
	bitStream.Write(bAllowFormatting);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_MESSAGE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, GetEntity()->GetId(), false);
}

void CScriptPlayer::Spawn(float fX, float fY, float fZ, float fA)
{
	RakNet::BitStream bitStream;
	bitStream.Write(CVector3(fX, fY, fZ)); //spawnPos
	bitStream.Write(0.0f); //fHeading
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SPAWN), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, GetEntity()->GetId(), false);
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


			pSyncPacket.fHealth = GetHealth();
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
			//WeaponPacket.fArmsHeadingCircle = GetArmHeading();
			//WeaponPacket.fArmsUpDownRotation = GetArmUpDown();

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
				pVehicle->GetMoveSpeed(VehiclePacket.vecMoveSpeed);
				pVehicle->GetTurnSpeed(VehiclePacket.vecTurnSpeed);
				pVehicle->GetMatrix(VehiclePacket.matrix);

				VehiclePacket.health = pVehicle->GetHealth();
				VehiclePacket.petrol = pVehicle->GetPetrolTankHealth();
				VehiclePacket.bEngineState = pVehicle->GetEngineState();
				VehiclePacket.steeringAngle = pVehicle->GetSteeringAngle();
				VehiclePacket.fHeading = pVehicle->GetHeading();
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
			SetHealth(pSyncPlayer.fHealth);

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

				pVehicle->SetPosition(VehiclePacket.matrix.vecPosition);
				pVehicle->SetMoveSpeed(VehiclePacket.vecMoveSpeed);
				pVehicle->SetTurnSpeed(VehiclePacket.vecTurnSpeed);
				pVehicle->SetMatrix(VehiclePacket.matrix);
				pVehicle->SetHealth(VehiclePacket.health);
				pVehicle->SetPetrolTankHealth(VehiclePacket.petrol);
				pVehicle->SetEngineState(VehiclePacket.bEngineState);
				pVehicle->SetHeading(VehiclePacket.fHeading);

#ifdef _DEBUG
				//CLogFile::Printf("%f %f %f", VehiclePacket.matrix.vecPosition.fX, VehiclePacket.matrix.vecPosition.fY, VehiclePacket.matrix.vecPosition.fZ);
#endif

				
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
			//SetArmHeading(WeaponPacket.fArmsHeadingCircle);
			//SetArmUpDown(WeaponPacket.fArmsUpDownRotation);
		}
		break;
	default:
		CLogFile::Printf("Warning: Unknown sync package type");
		break;
	}
}