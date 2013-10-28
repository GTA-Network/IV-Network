//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CVehicleEntity.h
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CVehicleEntity_h
#define CVehicleEntity_h

#include "CNetworkEntity.h"

class CScriptVehicle;

class CVehicleEntity : public CNetworkEntity
{
private:
	CScriptVehicle*	m_pScriptVehicle;
	Matrix			m_Matrix;
	unsigned int	m_uiHealth;
	float			m_fPetrolHealth;
	float			m_fSteeringAngle;
	bool			m_bEngineState;
public:
	CVehicleEntity();
	~CVehicleEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}

	void SetMatrix(Matrix &matrix) { m_Matrix = matrix; }
	void GetMatrix(Matrix &matrix) { matrix = m_Matrix; }

	void								SetHealth(unsigned int uiHealth) { m_uiHealth = uiHealth; }
	unsigned int						GetHealth() { return m_uiHealth; }

	void								SetPetrolTankHealth(float fHealth) { m_fPetrolHealth = fHealth; }
	float								GetPetrolTankHealth() { return m_fPetrolHealth; }

	void								SetEngineState(bool bEngineState) { m_bEngineState = bEngineState; }
	bool								GetEngineState() { return m_bEngineState; }

	void								SetSteeringAngle(float fAngle) { m_fSteeringAngle = fAngle; }
	float								GetSteeringAngle() { return m_fSteeringAngle; }

	CScriptVehicle*  GetScriptVehicle() { return m_pScriptVehicle; }
	void			SetScriptVehicle(CScriptVehicle* pScriptVehicle) { m_pScriptVehicle = pScriptVehicle; }
};

class CScriptVehicle : public CScriptEntity
{
public:
	CScriptVehicle() { SetEntity(new CVehicleEntity); };
	~CScriptVehicle() { delete GetEntity(); };

	CVehicleEntity * GetEntity() { return (CVehicleEntity*)CScriptEntity::GetEntity(); }

	const char* GetScriptClassName() { return "CVehicleEntity"; }
	
	void SetPosition(float fX, float fY, float fZ);
	void SetRotation(float fX, float fY, float fZ);
	void SetMoveSpeed(float fX, float fY, float fZ);
	void SetTurnSpeed(float fX, float fY, float fZ);
	void SetHealth(int iHealth);
	int  GetHealth() { return GetEntity()->GetHealth(); };
};

#endif // CVehicleEntity_h