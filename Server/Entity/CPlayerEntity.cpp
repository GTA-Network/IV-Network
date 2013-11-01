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


enum eWeaponType
{
	WEAPON_TYPE_UNARMED,
	WEAPON_TYPE_BASEBALLBAT,
	WEAPON_TYPE_POOLCUE,
	WEAPON_TYPE_KNIFE,
	WEAPON_TYPE_GRENADE,
	WEAPON_TYPE_MOLOTOV,
	WEAPON_TYPE_ROCKET,
	WEAPON_TYPE_PISTOL,
	WEAPON_TYPE_UNUSED0,
	WEAPON_TYPE_DEAGLE,
	WEAPON_TYPE_SHOTGUN,
	WEAPON_TYPE_BARETTA,
	WEAPON_TYPE_MICRO_UZI,
	WEAPON_TYPE_MP5,
	WEAPON_TYPE_AK47,
	WEAPON_TYPE_M4,
	WEAPON_TYPE_SNIPERRIFLE,
	WEAPON_TYPE_M40A1,
	WEAPON_TYPE_RLAUNCHER,
	WEAPON_TYPE_FTHROWER,
	WEAPON_TYPE_MINIGUN,
	WEAPON_TYPE_EPISODIC_1,
	WEAPON_TYPE_EPISODIC_2,
	WEAPON_TYPE_EPISODIC_3,
	WEAPON_TYPE_EPISODIC_4,
	WEAPON_TYPE_EPISODIC_5,
	WEAPON_TYPE_EPISODIC_6,
	WEAPON_TYPE_EPISODIC_7,
	WEAPON_TYPE_EPISODIC_8,
	WEAPON_TYPE_EPISODIC_9,
	WEAPON_TYPE_EPISODIC_10,
	WEAPON_TYPE_EPISODIC_11,
	WEAPON_TYPE_EPISODIC_12,
	WEAPON_TYPE_EPISODIC_13,
	WEAPON_TYPE_EPISODIC_14,
	WEAPON_TYPE_EPISODIC_15,
	WEAPON_TYPE_EPISODIC_16,
	WEAPON_TYPE_EPISODIC_17,
	WEAPON_TYPE_EPISODIC_18,
	WEAPON_TYPE_EPISODIC_19,
	WEAPON_TYPE_EPISODIC_20,
	WEAPON_TYPE_EPISODIC_21,
	WEAPON_TYPE_EPISODIC_22,
	WEAPON_TYPE_EPISODIC_23,
	WEAPON_TYPE_EPISODIC_24,
	WEAPON_TYPE_CAMERA,
	WEAPON_TYPE_OBJECT,
	WEAPON_TYPE_LAST_WEAPONTYPE,
	WEAPON_TYPE_ARMOUR,
	WEAPON_TYPE_RAMMEDBYCAR,
	WEAPON_TYPE_RUNOVERBYCAR,
	WEAPON_TYPE_EXPLOSION,
	WEAPON_TYPE_UZI_DRIVEBY,
	WEAPON_TYPE_DROWNING,
	WEAPON_TYPE_FALL,
	WEAPON_TYPE_UNIDENTIFIED,
	WEAPON_TYPE_ANYMELEE,
	WEAPON_TYPE_ANYWEAPON,
	WEAPON_TYPE_MAX
};

enum eWeaponSlot
{
	WEAPON_SLOT_UNARMED,
	WEAPON_SLOT_MELEE,
	WEAPON_SLOT_HANDGUN,
	WEAPON_SLOT_SHOTGUN,
	WEAPON_SLOT_SMG,
	WEAPON_SLOT_RIFLE,
	WEAPON_SLOT_SNIPER,
	WEAPON_SLOT_HEAVY,
	WEAPON_SLOT_THROWN,
	WEAPON_SLOT_SPECIAL,
	WEAPON_SLOT_PARACHUTE,
	WEAPON_SLOT_MAX
};

int GetWeaponSlotByType(eWeaponType type)
{
	if (type == WEAPON_TYPE_KNIFE
		|| type == WEAPON_TYPE_BASEBALLBAT
		|| type == WEAPON_TYPE_POOLCUE)
	{
		return WEAPON_SLOT_MELEE;
	}

	if (type == WEAPON_TYPE_EPISODIC_9
		|| type == WEAPON_TYPE_PISTOL
		|| type == WEAPON_TYPE_DEAGLE)
	{
		return WEAPON_SLOT_HANDGUN;
	}

	if (type == WEAPON_TYPE_SHOTGUN
		|| type == WEAPON_TYPE_EPISODIC_10
		|| type == WEAPON_TYPE_EPISODIC_11
		|| type == WEAPON_TYPE_BARETTA)
	{
		return WEAPON_SLOT_SHOTGUN;
	}

	if (type == WEAPON_TYPE_EPISODIC_12
		|| type == WEAPON_TYPE_EPISODIC_13
		|| type == WEAPON_TYPE_MICRO_UZI
		|| type == WEAPON_TYPE_MP5)
	{
		return WEAPON_SLOT_SMG;
	}

	if (type == WEAPON_TYPE_AK47
		|| type == WEAPON_TYPE_M4
		|| type == WEAPON_TYPE_EPISODIC_14
		|| type == WEAPON_TYPE_EPISODIC_19)
	{
		return WEAPON_SLOT_RIFLE;
	}

	if (type == WEAPON_TYPE_SNIPERRIFLE
		|| type == WEAPON_TYPE_M40A1
		|| type == WEAPON_TYPE_EPISODIC_15)
	{
		return WEAPON_SLOT_SNIPER;
	}

	if (type == WEAPON_TYPE_RLAUNCHER
		|| type == WEAPON_TYPE_EPISODIC_1
		|| type == WEAPON_TYPE_EPISODIC_17
		|| type == WEAPON_TYPE_EPISODIC_20)
	{
		return WEAPON_SLOT_HEAVY;
	}

	if (type == WEAPON_TYPE_GRENADE
		|| type == WEAPON_TYPE_MOLOTOV
		|| type == WEAPON_TYPE_ROCKET
		|| type == WEAPON_TYPE_EPISODIC_5
		|| type == WEAPON_TYPE_EPISODIC_16
		|| type == WEAPON_TYPE_EPISODIC_18)
	{
		return WEAPON_SLOT_THROWN;
	}

	if (type == WEAPON_TYPE_OBJECT)
	{
		return WEAPON_SLOT_SPECIAL;
	}

	if (type == WEAPON_TYPE_EPISODIC_21)
	{
		return WEAPON_SLOT_PARACHUTE;
	}

	return WEAPON_SLOT_MAX;
}


void CPlayerEntity::GiveWeapon(int id, int uiAmmo)
{
	if (GetWeaponSlotByType((eWeaponType) id) != WEAPON_SLOT_MAX)
	{
		//m_Weapon.weaponSlot = GetWeaponSlotByType((eWeaponType) id);
		m_Weapon.iAmmo = uiAmmo;
		//m_Weapon.iClip = 0;
		m_Weapon.weaponType = id;
	}
}

void CPlayerEntity::Pulse()
{
	// Send the sync only every 50ms to get a nice and smooth sync
	// If sync is crap you can adjust this value
	// Example  
	if (m_ulLastSyncSent + (1000 / CServer::GetInstance()->GetSyncRate()) <= SharedUtility::GetTime())
	{
		RakNet::BitStream bitStream;
		bitStream.Write(GetId());
		bitStream.Write(CServer::GetInstance()->GetNetworkModule()->GetPlayerPing(GetId()));

		Serialize(&bitStream, m_eLastSyncPackageType);
		m_ulLastSyncSent = SharedUtility::GetTime();

		if (m_controlState.IsAiming() || m_controlState.IsFiring())
		{
			Serialize(&bitStream, RPC_PACKAGE_TYPE_PLAYER_WEAPON);
		}

		CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_SYNC_PACKAGE), &bitStream, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, -1, true);
	}
};


CVehicleEntity* CPlayerEntity::GetVehicle()
{
	{ return m_vehicleId == 0xFFFF ? nullptr : CServer::GetInstance()->GetVehicleManager()->GetAt(m_vehicleId); }
}

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
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_PLAYER_SET_ARMOUR), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
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
	GetEntity()->GiveWeapon(id, uiAmmo);

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
			GetMoveSpeed(pSyncPacket.vecMoveSpeed);

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

			pSyncPacket.weapon.iAmmo = m_Weapon.iAmmo;
			pSyncPacket.weapon.weaponType = m_Weapon.weaponType;

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

			WeaponPacket.weapon.iAmmo = m_Weapon.iAmmo;
			WeaponPacket.weapon.weaponType = m_Weapon.weaponType;

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

				VehiclePacket.vehHealth = pVehicle->GetHealth();
				//VehiclePacket.petrol = pVehicle->GetPetrolTankHealth();
				VehiclePacket.bEngineState = pVehicle->GetEngineState();
				VehiclePacket.fHeading = pVehicle->GetHeading();
				VehiclePacket.playerArmor = GetArmour();
				VehiclePacket.playerHealth = GetHealth();

				VehiclePacket.weapon.iAmmo = m_Weapon.iAmmo;
				VehiclePacket.weapon.weaponType = m_Weapon.weaponType;
			}
			GetControlState(VehiclePacket.ControlState);
			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_VEHICLE);
			pBitStream->Write(VehiclePacket);
		}
		break;
	case RPC_PACKAGE_TYPE_PLAYER_PASSENGER:
		{
			CNetworkPlayerPassengerSyncPacket PassengerPacket;

			GetControlState(PassengerPacket.ControlState);
			GetPosition(PassengerPacket.vecPosition);
			PassengerPacket.playerArmor = GetArmour();
			PassengerPacket.playerHealth = GetHealth();

			PassengerPacket.vehicleId = m_vehicleId;
			PassengerPacket.byteSeatId = m_vehicleSeatId;

			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_PASSENGER);
			pBitStream->Write(PassengerPacket);
		}
		break;
	default:
		CLogFile::Printf("Warning: Sync Package type not implemented %i", pType);
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
			SetMoveSpeed(pSyncPlayer.vecMoveSpeed);
			SetTurnSpeed(pSyncPlayer.vecTurnSpeed);
			SetDirection(pSyncPlayer.vecDirection);
			SetRoll(pSyncPlayer.vecRoll);
			SetDucking(pSyncPlayer.bDuckState);
			SetHeading(pSyncPlayer.fHeading);
			SetHealth(pSyncPlayer.fHealth);
			SetArmour(pSyncPlayer.fArmor);

			m_vehicleId = 0xFFFF;

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
			m_vehicleSeatId = 0;

			if (pVehicle)
			{
				pVehicle->SetPosition(VehiclePacket.matrix.vecPosition);
				pVehicle->SetMoveSpeed(VehiclePacket.vecMoveSpeed);
				pVehicle->SetTurnSpeed(VehiclePacket.vecTurnSpeed);
				pVehicle->SetMatrix(VehiclePacket.matrix);
				pVehicle->SetHealth(VehiclePacket.vehHealth);
				//pVehicle->SetPetrolTankHealth(VehiclePacket.petrol);

				pVehicle->SetEngineState(VehiclePacket.bEngineState);
				pVehicle->SetHeading(VehiclePacket.fHeading);

				SetHealth(VehiclePacket.playerHealth);
				SetArmour(VehiclePacket.playerArmor);
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
		}
		break;
	case RPC_PACKAGE_TYPE_PLAYER_PASSENGER:
		{
			CNetworkPlayerPassengerSyncPacket PassengerPacket;

			SetControlState(PassengerPacket.ControlState);
			SetPosition(PassengerPacket.vecPosition);
			SetArmour(PassengerPacket.playerArmor);
			SetHealth(PassengerPacket.playerHealth);

			m_vehicleId = PassengerPacket.vehicleId;
			m_vehicleSeatId = PassengerPacket.byteSeatId;

			m_eLastSyncPackageType = pType;
			m_ulLastSyncReceived = SharedUtility::GetTime();
		}
		break;
	default:
		CLogFile::Printf("Warning: Unknown sync package type");
		break;
	}
}