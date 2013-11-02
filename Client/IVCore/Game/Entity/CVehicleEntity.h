//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CVehicleEntity.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CVehicleEntity_h
#define CVehicleEntity_h

#include <Common.h>
#include "CNetworkEntity.h"
#include <Game/IVEngine/CIVVehicle.h>
#include <Game/IVEngine/CIVModelInfo.h>

class CPlayerEntity;
class CVehicleEntity : public CNetworkEntity {
private:

	CIVVehicle							*m_pVehicle;
	EntityId							m_vehicleId;
	CIVModelInfo						*m_pModelInfo;
	bool								m_bSpawned;
	CVector3							m_vecSpawnPosition;
	CVector3							m_vecPosition;
	CVector3							m_vecRotation;
    CVector3							m_vecMoveSpeed;
    CVector3							m_vecTurnSpeed;
	float								m_fSpawnAngle;
	float								m_uiHealth;
	float								m_fPetrolTankHealth;
	DWORD								m_dwColor[5];
	bool								m_bIndicatorState[4];
	float								m_fDoor[6];
    bool								m_bSirenState;
	unsigned char						m_ucVariation;
	bool								m_bComponents[9];
	bool								m_bEngineStatus;
    bool								m_bTaxiLights;
    bool								m_bLights;
	float								m_fDirtLevel;
	DWORD								m_dwDoorLockState;

	CPlayerEntity						*m_pDriver;
	CPlayerEntity						*m_pPassengers[8]; // Max passenger per vehicle = 8(GTA LIMIT)

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
		}								pos;
		struct
		{
			CVector3      vecStart;
			CVector3      vecTarget;
			CVector3      vecError;
			float         fLastAlpha;
			unsigned long ulStartTime;
			unsigned long ulFinishTime;
		}								rot;
	}									m_interp;

public:

	CVehicleEntity(int iVehicleModel, CVector3 vecPos, float fAngle, DWORD bColor1, DWORD bColor2, DWORD bColor3, DWORD bColor4, DWORD bColor5);
	~CVehicleEntity();

	bool								Create();
	bool								Destroy();

	void								SetId(EntityId vehicleId) { m_vehicleId = vehicleId; }
	EntityId							GetId() { return m_vehicleId; }

	virtual bool						IsSpawned() { return m_bSpawned; }
	virtual void						Reset();

	unsigned							GetScriptingHandle();

	bool								IsMoving();
    void								StopMoving();

    void								SetModel(DWORD dwModelHash);

	void								SetColors(DWORD dwColor1, DWORD dwColor2, DWORD dwColor3, DWORD dwColor4, DWORD dwColor5);
	void								GetColors(DWORD &dwColor1, DWORD &dwColor2, DWORD &dwColor3, DWORD &dwColor4, DWORD &dwColor5);

    void								SetPosition(const CVector3& vecPosition, bool bDontCancelTasks = false, bool bResetInterpolation = true);
    void								GetPosition(CVector3& vecPosition);
	CVector3							GetPosition();

    void								SetRotation(const CVector3& vecRotation, bool bResetInterpolation = true);
    void								GetRotation(CVector3& vecRotation);

    void								SetHealth(float uiHealth);
    float								GetHealth();

    void								SetPetrolTankHealth(float fHealth);
    float								GetPetrolTankHealth();

    void								SetMoveSpeed(const CVector3& vecMoveSpeed);
    void								GetMoveSpeed(CVector3& vecMoveSpeed);

    void								SetQuaternion(float * quat);
    void								GetQuaternion(float * quat);

    void								SetTurnSpeed(const CVector3& vecTurnSpeed);
    void								GetTurnSpeed(CVector3& vecTurnSpeed);

    void								SetSirenState(bool bSirenState);
    bool								GetSirenState();

    void								SetDirtLevel(float fDirtLevel);
    float								GetDirtLevel();
    
	BYTE								GetMaxPassengers();

    void								SetDoorLockState(DWORD dwDoorLockState);
    DWORD								GetDoorLockState();

    void								SoundHorn(int iDuration);

    void								Interpolate();
    void								ResetInterpolation();

	void								Pulse();

    void								UpdateInterior(bool bHasDriver = false);

    void								UpdateTargetPosition();
    void								UpdateTargetRotation();
        
    void								SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay);
    void								SetTargetRotation(const CVector3& vecRotation, unsigned long ulDelay);
    void								RemoveTargetPosition();
    void								RemoveTargetRotation();
        
    bool								HasTargetPosition() { return (m_interp.pos.ulFinishTime != 0); }
    bool								HasTargetRotation() { return (m_interp.rot.ulFinishTime != 0); }

    void								SetInterior(unsigned int uiInterior);
    unsigned							GetInterior();

    void								SetIndicatorState(bool bFrontLeft, bool bFrontRight, bool bBackLeft, bool bBackRight);
    bool								GetIndicatorState(unsigned char ucSlot);

    void								SetComponentState(unsigned char ucSlot, bool bState);
    bool								GetComponentState(unsigned char ucSlot);

    void								SetVariation(unsigned char ucVariation);
    unsigned char						GetVariation();

    bool								IsOnScreen();

    void								SetSteeringAngle(float fSteeringAngle);
    float								GetSteeringAngle();

    void								SetEngineState(bool bState);
    bool								GetEngineState();

    void								SetTaxiLightsState(bool bState);
    bool								GetTaxiLightsState();

    void								SetCarDoorAngle(int iDoor, bool bClose, float fAngle);
    float								GetCarDoorAngle(int iDoor);

    void								SetLightsState(bool bLights);
    bool								GetLightsState();

    bool								GetWindowState(int iWindow);
    void								SetWindowState(int iWindow, bool bBroken);

    void								SetDeformation(CVector3 vecPos, CVector3 vecDeformation);
    CVector3							GetDeformation(CVector3 vecPos);

    void								SetDamageable(bool bToggle);

    void								SetVehicleGPSState(bool bState);
    bool								GetVehicleGPSState();

    void								Fix();

	void								SetOccupant(BYTE byteSeatId, CPlayerEntity * pOccupant);
	CPlayerEntity						*GetOccupant(BYTE byteSeatId);

	void								SetDriver(CPlayerEntity * pDriver) { m_pDriver = pDriver; }
	virtual CPlayerEntity				*GetDriver() { return m_pDriver; }

	virtual CIVVehicle					*GetGameVehicle() { return m_pVehicle; }
	virtual CIVModelInfo				*GetModelInfo() { return m_pModelInfo; }
};

#endif // CVehicleEntity_h