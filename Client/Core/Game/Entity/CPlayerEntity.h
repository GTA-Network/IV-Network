//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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
	CVector3								m_vecMoveSpeed;
	CVector3								m_vecTurnSpeed;

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

	CControlState							m_previousControlState;
    CControlState							m_currentControlState;

	sIVSynchronization						* m_pIVSync;

	sPlayerEntity_StoreIVSynchronization	* m_pIVSyncHandle;
	CPlayerEntity							* m_pPlayerEntity;

public: // Handles "GET" functions

	bool							IsLocalPlayer() { return m_bLocalPlayer; }
	bool							IsNetworked() { return m_bNetworked; }
	bool							IsSpawned() { return m_bSpawned; }
	
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

	unsigned short					GetPing();
	EntityId						GetPlayerId() { return CNetworkEntity::GetId(); }
	float							GetRotation();
	
	void							GetMoveSpeed(CVector3& vecMoveSpeed);
	void							GetPosition(CVector3 &vecPosition);
	void							GetTurnSpeed(CVector3& vecTurnSpeed);
	
	BYTE							GetPlayerGameNumber() { return m_bytePlayerNumber; }

	unsigned short					GetId() { return !IsNetworked() ? -1 : m_usPlayerId; }
	CString							GetNick() { return m_strNick; }
	unsigned						GetColor() { return m_uiColor; }
	float							GetHealth();

	CContextData					* GetContextData() { return m_pContextData; }
	CVehicleEntity					* InternalGetVehicle();
	CIVPlayerPed					* GetPlayerPed() { return m_pPlayerPed; }
	CIVPlayerInfo					* GetPlayerInfo() { return m_pPlayerInfo; }
	
	sWeaponStructure				GetAimData() { return m_aimData; }
	sWeaponStructure				GetShotData() { return m_shotData; }

public: // Handles call functions
									CPlayerEntity(bool bLocalPlayer = false);
									~CPlayerEntity();

	inline void						Spawn() 
	{
		m_bSpawned = true;
	}

	void							SetNetworked(bool bNetworked) { m_bNetworked = bNetworked; }
	void							SetId(unsigned short usPlayerId) { m_usPlayerId = usPlayerId; }
	void							SetPlayerId(EntityId playerId) { CNetworkEntity::SetId(playerId); }
	void							SetPing(unsigned short usPing) { m_usPing = usPing; }

	void							SetPosition(CVector3 &vecPosition);
	void							SetRotation(float fAngle);
	void							SetHealth(float fHealth);
	void							SetModel(int iModelId);
	void							Teleport(CVector3 vecPosition);
	void							SetMoveSpeed(const CVector3& vecMoveSpeed);
	void							SetTurnSpeed(const CVector3& vecTurnSpeed);

	void							SetNick(CString strNick) { m_strNick = strNick; }
	void							SetColor(unsigned uiColor);

	unsigned						GetScriptingHandle();

	void							Process();
	void							PreStoreIVSynchronization(bool bHasWeaponData = false, bool bCopyLocalPlayer = false, CPlayerEntity * pCopy = NULL);
	void							StoreIVSynchronization(bool bHasWeaponData = false, bool bCopyLocalPlayer = false, CPlayerEntity * pCopy = NULL);

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
	
	void							Interpolate();
	void							ResetInterpolation();
	void							UpdateTargetPosition();
	void							UpdateTargetRotation();
	void							RemoveTargetPosition();
	void							SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay);
	void							SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, int iMoveType);
	void							SetCurrentSyncHeading(float fHeading);


	void							SetAimData(bool bSwitch, CVector3 vecPos);
	void							SetShotData(bool bSwitch, CVector3 vecPos);

};

#endif // CPlayerEntity_h