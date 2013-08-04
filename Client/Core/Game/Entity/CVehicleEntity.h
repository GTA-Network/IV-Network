//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
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
	unsigned int						m_uiVehicleHandle;
	CVector3							m_vecSpawnPosition;
	float								m_fSpawnAngle;
	BYTE								m_byteColor[4];

	CPlayerEntity						*m_pDriver;
	CPlayerEntity						*m_pPassengers[8]; // Max passenger per vehicle = 8(GTA LIMIT)

public:

	CVehicleEntity( int iVehicleModel, CVector3 vecPos, float fAngle, BYTE color1, BYTE color2, BYTE color3, BYTE color4 );
	~CVehicleEntity( );

	bool								Create();
	bool								Destroy();

	void								SetId( EntityId vehicleId ) { m_vehicleId = vehicleId; }
	EntityId							GetId( ) { return m_vehicleId; }

	virtual bool						IsSpawned() { return m_bSpawned; }

	unsigned int						GetScriptingHandle( ) { return m_uiVehicleHandle; }

	virtual void						Respawn( );
	virtual void						Process();

	virtual void						SetSpawnPosition(CVector3 vecPos);

	virtual void						SetPosition( CVector3 vecPosition );
	virtual void						GetPosition( CVector3 * vecPosition );

	virtual void						SetMoveSpeed(CVector3 vecPosition);
	virtual void						GetMoveSpeed( CVector3 * vecMoveSpeed );

	virtual void						SetTurnSpeed(CVector3 vecPosition);
	virtual void						GetTurnSpeed( CVector3 * vecTurnSpeed );

	virtual void						SetColors(BYTE color1, BYTE color2, BYTE color3, BYTE color4);
	virtual void						SetHeading(float fAngle);

	virtual BYTE						GetMaxPassengers( );

	virtual void						SetOccupant( BYTE byteSeat, CPlayerEntity * pPlayer );
	virtual CPlayerEntity				*GetOccupant( BYTE byteSeat );

	virtual CIVVehicle					*GetGameVehicle() { return m_pVehicle; }
	virtual CIVModelInfo				*GetModelInfo() { return m_pModelInfo; }
};

#endif // CVehicleEntity_h