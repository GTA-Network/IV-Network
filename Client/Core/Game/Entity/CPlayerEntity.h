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

#include <Math\CMaths.h>
#include <CContextData.h>
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
	} m_vehicleEnterExit;

public:

	CPlayerEntity( bool bLocalPlayer = false );
	~CPlayerEntity();

	virtual bool		IsLocalPlayer() { return m_bLocalPlayer; }
	virtual bool		IsNetworked() { return m_bNetworked; }
	virtual bool		IsSpawned() { return m_bSpawned; }

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

	virtual void		SetPosition(CVector3 vecPosition);
	virtual bool		GetPosition(CVector3 *vecPosition);
	virtual void		Teleport( CVector3 vecPosition );

	virtual void		SetNick( CString strNick ) { m_strNick = strNick; }
	virtual CString		GetNick( ) { return m_strNick; }

	virtual void		SetColor( unsigned int uiColor );
	virtual unsigned	GetColor() { return m_uiColor; }

	virtual unsigned	GetScriptingHandle( );

	virtual void		SetHealth( float fHealth );
	virtual float		GetHealth();

	virtual void		SetModel( int iModelId );

	virtual void		SetRotation( float fAngle );
	virtual float		GetRotation();

	void				Process();

	bool				Create();
	bool				Destroy();

	virtual void		SetControlState( CControls * pControlState );
	virtual void		GetControlState( CControls * pControlState );
	virtual void		GetLastControlState( CControls * pControlState );

	CIVPlayerPed		* GetPlayerPed() { return m_pPlayerPed; }
	CIVPlayerInfo		* GetPlayerInfo() { return m_pPlayerInfo; }

	void				PutInVehicle( CVehicleEntity * pVehicle, BYTE byteSeat );
	void				RemoveFromVehicle( );

	bool				IsOnFoot( ) { return (m_pVehicle == NULL); }
	bool				IsInVehicle( ) { return (m_pVehicle != NULL); }
	bool				IsPassenger( ) { return (m_pVehicle != NULL && m_byteSeat != 0); }

	void				InternalPutInVehicle( CVehicleEntity * pVehicle, BYTE byteSeat );
	void				InternalRemoveFromVehicle( );
	bool				InternalIsInVehicle( );
	CVehicleEntity		* InternalGetVehicle( );

	void				EnterVehicle( CVehicleEntity * pVehicle, BYTE byteSeat );
	void				ExitVehicle( eExitVehicleType exitType );

	void				CheckVehicleEnterExit( );
	void				ProcessVehicleEnterExit( );
	void				ResetVehicleEnterExit( );
	bool				HasVehicleEnterExit( ) { return (m_vehicleEnterExit.bEntering || m_vehicleEnterExit.bExiting); }

	void				ClearVehicleEntryTask( );
	void				ClearVehicleExitTask( );
	bool				GetClosestVehicle( bool bPassenger, CVehicleEntity ** pVehicle, BYTE& byteSeat );
	bool				IsGettingIntoAVehicle( );
	bool				IsGettingOutOfAVehicle( );

};

#endif // CPlayerEntity_h