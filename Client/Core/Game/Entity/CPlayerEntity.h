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

enum eExitVehicleType
{
	EXIT_VEHICLE_NORMAL,
	EXIT_VEHICLE_JACKED
};

class CVehicleEntity;
class CPlayerEntity : public CNetworkEntity {
private:
	bool				m_bLocalPlayer;
	bool				m_bNetworked;
	bool				m_bSpawned;
	unsigned short      m_usPlayerId;	
	unsigned short		m_usPing;
	unsigned int		m_uiColor;
	CString				m_strNick;
	CVector3			m_vecPosition;

	CIVPlayerPed		* m_pPlayerPed;
	CIVPlayerInfo		* m_pPlayerInfo;
	CIVModelInfo		* m_pModelInfo;
	BYTE				m_bytePlayerNumber;
	CContextData		* m_pContextData;

	CControls			m_lastControlState;
	CControls			m_ControlState;

	unsigned int		m_uiBlip;

	CVehicleEntity		* m_pVehicle;
	BYTE				m_byteSeat;

	struct
	{
		bool			bEntering;
		CVehicleEntity	* pVehicle;
		BYTE			byteSeat;
		bool			bExiting;
		bool			bRequesting;
	}					m_vehicleEnterExit;

	struct
	{
		struct
		{
			CVector3      vecStart;
			CVector3      vecTarget;
			CVector3      vecError;
			float         fLastAlpha;
			unsigned long ulStartTime;
			unsigned long ulFinishTime;
		} pos;
	}					m_interp;

public:

	CPlayerEntity(bool bLocalPlayer = false);
	~CPlayerEntity();

	bool				IsLocalPlayer() { return m_bLocalPlayer; }
	bool				IsNetworked() { return m_bNetworked; }
	bool				IsSpawned() { return m_bSpawned; }

	bool				IsAnyWeaponUser();

	inline void			Spawn() 
	{
		m_bSpawned = true;
	}

	void				SetNetworked(bool bNetworked) { m_bNetworked = bNetworked; }

	void				SetId(unsigned short usPlayerId) { m_usPlayerId = usPlayerId; }
	unsigned short		GetId() { return !IsNetworked() ? -1 : m_usPlayerId; }

	EntityId			GetPlayerId() { return CNetworkEntity::GetId(); }
	void				SetPlayerId(EntityId playerId) { CNetworkEntity::SetId(playerId); }

	void				SetPing(unsigned short usPing) { m_usPing = usPing; }
	unsigned short		GetPing();

	void				SetPosition(CVector3 &vecPosition);
	void				GetPosition(CVector3 &vecPosition);
	void				Teleport(CVector3 vecPosition);
	void                SetMoveSpeed(const CVector3& vecMoveSpeed);
	void                GetMoveSpeed(CVector3& vecMoveSpeed);

	void                SetTurnSpeed(const CVector3& vecTurnSpeed);
	void                GetTurnSpeed(CVector3& vecTurnSpeed);

	void				SetNick(CString strNick) { m_strNick = strNick; }
	CString				GetNick() { return m_strNick; }

	void				SetColor(unsigned uiColor);
	unsigned			GetColor() { return m_uiColor; }

	unsigned			GetScriptingHandle();

	void				SetHealth(float fHealth);
	float				GetHealth();

	void				SetModel(int iModelId);

	void				SetRotation(float fAngle);
	float				GetRotation();

	void				Process();

	bool				Create();
	bool				Destroy();

	void				SetControlState(CControls * pControlState);
	void				GetControlState(CControls * pControlState);
	void				GetLastControlState(CControls * pControlState);

	CIVPlayerPed		* GetPlayerPed() { return m_pPlayerPed; }
	CIVPlayerInfo		* GetPlayerInfo() { return m_pPlayerInfo; }
	BYTE				GetPlayerGameNumber() { return m_bytePlayerNumber; }

	void				PutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void				RemoveFromVehicle();

	bool				IsOnFoot() { return (m_pVehicle == NULL); }
	bool				IsInVehicle() { return (m_pVehicle != NULL); }
	bool				IsPassenger() { return (m_pVehicle != NULL && m_byteSeat != 0); }

	void				InternalPutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void				InternalRemoveFromVehicle();
	bool				InternalIsInVehicle();
	CVehicleEntity		* InternalGetVehicle();

	void				EnterVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void				ExitVehicle(eExitVehicleType exitType);

	void				CheckVehicleEnterExit();
	void				ProcessVehicleEnterExit();
	void				ResetVehicleEnterExit();
	bool				HasVehicleEnterExit() { return (m_vehicleEnterExit.bEntering || m_vehicleEnterExit.bExiting); }

	void				ClearVehicleEntryTask();
	void				ClearVehicleExitTask();
	bool				GetClosestVehicle(bool bPassenger, CVehicleEntity ** pVehicle, BYTE& byteSeat);
	bool				IsGettingIntoAVehicle();
	bool				IsGettingOutOfAVehicle();

	// Onfoot
	void                UpdateTargetPosition();

	void                Interpolate();
	void                ResetInterpolation();

	void                SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay);
	void                SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, int iMoveType);

	void                RemoveTargetPosition();

	bool                HasTargetPosition() { return (m_interp.pos.ulFinishTime != 0); }
	void				SetCurrentSyncHeading(float fHeading);
};

#endif // CPlayerEntity_h