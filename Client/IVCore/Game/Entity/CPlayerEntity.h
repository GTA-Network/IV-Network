//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPlayerEntity.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CPlayerEntity_h
#define CPlayerEntity_h

#include <Common.h>
#include "CNetworkEntity.h"

#include <Math/CMaths.h>
#include <Game/CContextData.h>
#include <Game/IVEngine/CIVPlayerPed.h>
#include <Game/IVEngine/CIVModelInfo.h>
#include <Network/CBitStream.h>
#include <Game/eGame.h>

class CVehicleEntity;
class CPlayerEntity : public CNetworkEntity {
	friend class CLocalPlayer;
private:
	bool									m_bLocalPlayer;
	bool									m_bNetworked;
	bool									m_bSpawned;
	unsigned short							m_usPlayerId;	
	unsigned short							m_usPing;
	unsigned int							m_uiColor;
	
	unsigned								m_uiBlip;
	CString									m_strNick;
	CVector3								m_vecPosition;
	CVector3								m_vecRotation;
	CVector3								m_vecMoveSpeed;
	CVector3								m_vecTurnSpeed;
	CVector3								m_vecDirection;
	CVector3								m_vecRoll;

	CIVPlayerPed							* m_pPlayerPed;
	CIVPlayerInfo							* m_pPlayerInfo;
	CIVModelInfo							* m_pModelInfo;
	BYTE									m_bytePlayerNumber;
	CContextData							* m_pContextData;

	CControls								m_lastControlState;
	CControls								m_ControlState;

	CVehicleEntity							* m_pVehicle;
	BYTE									m_byteSeat;

	sPlayerEntity_VehicleData				* m_pVehicleEnterExit;
	sPlayerEntity_InterpolationData			* m_pInterpolationData;

	sWeaponStructure						m_aimData;
	sWeaponStructure						m_shotData;

	unsigned long							m_ulLastSyncReceived;

	int										m_iWantedLevel;

	struct 
	{
		unsigned char	ucHead;
		unsigned char	ucUpperBody; // e.g. shirt
		unsigned char	ucLowerBody; // e.g. pants, skirts
		unsigned char	ucSpecial1;
		unsigned char	ucHand;
		unsigned char	ucFeet; // e.g. shoes
		unsigned char	ucJacket;
		unsigned char	ucHair;
		unsigned char	ucSpecial2;
		unsigned char	ucSpecial3;
		unsigned char	ucFace;
	}										m_sClothes;

	inline BYTE									GetClothesValueFromSlot(BYTE bodyPart)
	{
		switch(bodyPart)
		{
			case 0: return m_sClothes.ucHead;
			case 1: return m_sClothes.ucUpperBody;
			case 2: return m_sClothes.ucLowerBody;
			case 3: return m_sClothes.ucSpecial1;
			case 4: return m_sClothes.ucHand;
			case 5: return m_sClothes.ucFeet;
			case 6: return m_sClothes.ucJacket;
			case 7: return m_sClothes.ucHair;
			case 8: return m_sClothes.ucSpecial2;
			case 9: return m_sClothes.ucSpecial3;
			case 10: return m_sClothes.ucFace;
			default: return 0;
		}
	}

	inline void									SetClothesValue(BYTE bodyPart, BYTE byteValue)
	{
		switch(bodyPart)
		{
			case 0: m_sClothes.ucHead = byteValue; break;
			case 1: m_sClothes.ucUpperBody = byteValue; break;
			case 2: m_sClothes.ucLowerBody = byteValue; break;
			case 3: m_sClothes.ucSpecial1 = byteValue; break;
			case 4: m_sClothes.ucHand = byteValue; break;
			case 5: m_sClothes.ucFeet = byteValue; break;
			case 6: m_sClothes.ucJacket = byteValue; break;
			case 7: m_sClothes.ucHair = byteValue; break;
			case 8: m_sClothes.ucSpecial2 = byteValue; break;
			case 9: m_sClothes.ucSpecial3 = byteValue; break;
			case 10: m_sClothes.ucFace = byteValue; break;
			default: break;
		}
	}

public: // Handles "GET" functions

	inline bool						IsLocalPlayer() { return m_bLocalPlayer; }
	inline bool						IsNetworked() { return m_bNetworked; }
	inline bool						IsSpawned() { return m_bSpawned; }
	
	bool							IsOnFoot() { return (m_pVehicle == NULL); }
	bool							IsInVehicle() { return (m_pVehicle != NULL); }
	bool							IsPassenger() { return (m_pVehicle != NULL && m_byteSeat != 0); }
	
	bool							HasTargetPosition() { return (m_pInterpolationData->pPosition.ulFinishTime != 0); }
	bool							HasTargetRotation() { return (m_pInterpolationData->pRotation.ulFinishTime != 0); }
	
	bool							IsAnyWeaponUser();
	bool							InternalIsInVehicle();
	bool							HasVehicleEnterExit() { return (m_pVehicleEnterExit->bEntering || m_pVehicleEnterExit->bExiting); }
	bool							GetClosestVehicle(bool bPassenger, CVehicleEntity ** pVehicle, BYTE& byteSeat);
	bool							IsGettingIntoAVehicle();
	bool							IsGettingOutOfAVehicle();
	bool							IsJumping();

	void							GiveMoney(int iAmount);
    void							SetMoney(int iAmount);
    void							ResetMoney();
    int								GetMoney();
		
	unsigned short					GetPing();
	EntityId						GetPlayerId() { return CNetworkEntity::GetId(); }
	float							GetHeading();
	
	void							GetMoveSpeed(CVector3& vecMoveSpeed);
	void							GetPosition(CVector3 &vecPosition);
	void							GetRotation(CVector3 &vecRotation);
	CVector3						GetPosition();
	void							GetTurnSpeed(CVector3& vecTurnSpeed);
	
	BYTE							GetPlayerGameNumber() { return m_bytePlayerNumber; }

	unsigned short					GetId() { return !IsNetworked() ? -1 : m_usPlayerId; }
	unsigned						GetColor() { return m_uiColor; }
	float							GetHealth();
	float							GetArmour();
	int								GetWantedLevel();

	CContextData					* GetContextData() { return m_pContextData; }
	CVehicleEntity					* InternalGetVehicle();
	CIVPlayerPed					* GetPlayerPed() { return m_pPlayerPed; }
	CIVPlayerInfo					* GetPlayerInfo() { return m_pPlayerInfo; }
	CVehicleEntity					* GetVehicleEntity() { return m_pVehicle; }
	
	sWeaponStructure				GetAimData() { return m_aimData; }
	sWeaponStructure				GetShotData() { return m_shotData; }					

public: // Handles call functions
									CPlayerEntity(bool bLocalPlayer = false);
									~CPlayerEntity();

	void							SetNetworked(bool bNetworked) { m_bNetworked = bNetworked; }
	void							SetId(unsigned short usPlayerId) { m_usPlayerId = usPlayerId; }
	void							SetPlayerId(EntityId playerId) { CNetworkEntity::SetId(playerId); }
	void							SetPing(unsigned short usPing) { m_usPing = usPing; }

	void							ApplySyncData(CVector3 vecPosition, CVector3 vecMovement, CVector3 vecTurnSpeed, CVector3 vecRoll, CVector3 vecDirection, bool bDuck, float fHeading);
	void							SetPosition(CVector3 &vecPosition, bool bForce = false);
	void							SetRotation(CVector3 &vecRotation);
	void							SetHeading(float fAngle);
	void							SetHealth(float fHealth);
	void							SetArmour(float fArmour);
	void							SetModel(int iModelId);
	void							SetWantedLevel(int iWantedLevel);
	void							Teleport(CVector3 vecPosition);
	void							SetMoveSpeed(const CVector3& vecMoveSpeed);
	void							SetTurnSpeed(const CVector3& vecTurnSpeed);

	void							SetNick(CString strNick);
	CString							GetNick() { return m_strNick; }
	void							SetColor(unsigned uiColor);

	unsigned						GetScriptingHandle();

	void							Pulse();
	void							PreStoreIVSynchronization(bool bHasWeaponData = false, bool bCopyLocalPlayer = false, CPlayerEntity * pCopy = NULL);
	void							StoreIVSynchronization(bool bHasWeaponData = false, bool bCopyLocalPlayer = false, CPlayerEntity * pCopy = NULL);
	void							StoreIVContextSynchronization(bool bHasWeaponData = false, bool bCopyLocalPlayer = false, CPlayerEntity * pCopy = NULL);

	bool							Create();
	bool							Destroy();

	void							SetControlState(CControls * pControlState);
	void							GetControlState(CControls * pControlState);
	void							GetLastControlState(CControls * pControlState);

	void							PutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void							RemoveFromVehicle();
	void							InternalPutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void							InternalRemoveFromVehicle();
	void							EnterVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void							ExitVehicle(eExitVehicleType exitType);
	void							CheckVehicleEnterExit();
	void							ProcessVehicleEnterExit();
	void							ResetVehicleEnterExit();
	void							ClearVehicleEntryTask();
	void							ClearVehicleExitTask();
	void							SetExitFlag(bool bFlag) { m_pVehicleEnterExit->bExiting = true; }
	
	void							Interpolate();
	void							ResetInterpolation();
	void							UpdateTargetPosition();
	void							UpdateTargetRotation();
	void							RemoveTargetPosition();
	void							SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay);
	void							SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, int iMoveType);

	void							ClearWeaponAimAtTask();
	void							ClearWeaponShotAtTask();
	void							SetWeaponAimAtTask(CVector3 vecAimAt);
	void							SetWeaponShotAtTask(CVector3 vecShotAt);

	void							KillPed(bool bInstandly);
	bool							IsDying();
	bool							IsDead();
	IVEntity						*GetLastDamageEntity();
	bool							GetKillInfo(EntityId * playerId, EntityId * vehicleId, EntityId * weaponId);

	void							SetAimData(bool bSwitch, CVector3 vecPos);
	void							SetShotData(bool bSwitch, CVector3 vecPos);

	void							SetPedClothes(unsigned short ucBodyLocation, unsigned  char ucClothes);
	unsigned char					GetPedClothes(unsigned short ucBodyLocation);

	void							GiveWeapon(unsigned uiWeaponId, unsigned uiAmmunation);
	void							RemoveWeapon(unsigned uiWeaponId);
	void							RemoveAllWeapons();
	void							SetCurrentWeapon(unsigned uiWeaponId);
	unsigned						GetCurrentWeapon();
	void							SetAmmunation(unsigned uiWeaponId, unsigned uiAmmunation);
	unsigned						GetAmmunation(unsigned uiWeapnId);
	void							GetWeaponInSlot(unsigned uiWeaponSlot, unsigned &uiWeaponId, unsigned &uiAmmunation, unsigned &uiUnkown);
	unsigned						GetAmmunationInClip(unsigned uiWeapon);
	void							SetAmmunationInClip(unsigned uiAmmunationInClip);
	unsigned						GetMaxAmmunationInClip(unsigned uiWeapon);

	virtual void					Serialize(RakNet::BitStream * pBitStream);
	virtual void					Deserialize(RakNet::BitStream * pBitStream);

	void							WarpIntoVehicle(CVehicleEntity * pVehicle, BYTE seat = 0);

	bool							IsOnScreen();
};

#endif // CPlayerEntity_h