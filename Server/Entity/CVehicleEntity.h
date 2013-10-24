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

public:
	CVehicleEntity();
	~CVehicleEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}

	CScriptVehicle*  GetScriptVehicle() { return m_pScriptVehicle; }
	void			SetScriptVehicle(CScriptVehicle* pScriptVehicle) { m_pScriptVehicle = pScriptVehicle; }
};

class CScriptVehicle : public CScriptEntity
{
public:
	CScriptVehicle() { SetEntity(new CVehicleEntity); };
	~CScriptVehicle() { delete GetEntity(); };

	const char* GetScriptClassName() { return "CVehicleEntity"; }
	
	void SetPosition(float fX, float fY, float fZ) { GetEntity()->SetPosition(CVector3(fX, fY, fZ)); }
	void SetRotation(float fX, float fY, float fZ) { GetEntity()->SetRotation(CVector3(fX, fY, fZ)); }
	void SetMoveSpeed(float fX, float fY, float fZ) { GetEntity()->SetMoveSpeed(CVector3(fX, fY, fZ)); }
	void SetTurnSpeed(float fX, float fY, float fZ) { GetEntity()->SetTurnSpeed(CVector3(fX, fY, fZ)); }
};

#endif // CVehicleEntity_h