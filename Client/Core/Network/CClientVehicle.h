//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CClientVehicle.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CClientVehicle_h
#define CClientVehicle_h

#include <Common.h>

#include <Game/Entity/CVehicleEntity.h>
#include <Game/IVEngine/CIVVehicle.h>
#include <Game/IVEngine/CIVModelInfo.h>

class CClientPlayer;
class CClientVehicle : public CVehicleEntity {
private:
	CIVVehicle				* m_pVehicle;
	EntityId				m_vehicleId;
	CIVModelInfo			* m_pModelInfo;
	bool					m_bSpawned;
	unsigned int			m_uiVehicleHandle;
	CVector3				m_vecSpawnPosition;
	float					m_fSpawnAngle;
	BYTE					m_byteColor[4];

	CClientPlayer			* m_pDriver;
	CClientPlayer			* m_pPassengers[8]; // Max passenger per vehicle = 8(GTA LIMIT)

public:

	CClientVehicle( int iVehicleModel, CVector3 vecPos, float fAngle, BYTE color1, BYTE color2, BYTE color3, BYTE color4 );
	~CClientVehicle( );

	bool					Spawn( );
	void					DeSpawn( );

	void					SetId( EntityId vehicleId ) { m_vehicleId = vehicleId; }
	EntityId				GetId( ) { return m_vehicleId; }

	bool					IsSpawned() { return m_bSpawned; }

	unsigned int			GetScriptingHandle( ) { return m_uiVehicleHandle; }

	void					Respawn( );

	void					SetSpawnPosition(CVector3 vecPos);

	void					SetPosition( CVector3 vecPosition );
	void					GetPosition( CVector3 * vecPosition );

	void					GetMoveSpeed( CVector3 * vecMoveSpeed );
	void					GetTurnSpeed( CVector3 * vecTurnSpeed );

	void					SetColors(BYTE color1, BYTE color2, BYTE color3, BYTE color4);
	void					SetHeading(float fAngle);

	BYTE					GetMaxPassengers( );

	void					SetOccupant( BYTE byteSeat, CClientPlayer * pPlayer );
	CClientPlayer			* GetOccupant( BYTE byteSeat );

	void					Serialize( CBitStream * bitStream );
	void					Deserialize( CBitStream * bitStream );

	CIVVehicle				* GetGameVehicle() { return m_pVehicle; }
	CIVModelInfo			* GetModelInfo() { return m_pModelInfo; }
};

#endif // CClientVehicle_h