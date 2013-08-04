//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVVehicle.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVVehicle_h
#define CIVVehicle_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVPhysical.h"
#include "CIVPed.h"

class IVVehicle : public IVPhysical
{
public:
	PAD(IVVehicle, pad0, 0xB50);
	BYTE m_byteRadioStation;
	PAD(IVVehicle, pad1, 0x37);
	BYTE m_byteSirenWithNoDriver;
	PAD(IVVehicle, pad2, 0x1CB);
	BYTE m_byteFlags1;
	BYTE m_byteFlags2;
	BYTE m_byteFlags3;
	BYTE m_byteFlags4;
	BYTE m_byteFlags5;
	PAD(IVVehicle, pad3, 0x3);
	BYTE m_byteFlags6;
	BYTE m_byteFlags7;
	PAD(IVVehicle, pad4, 0x1);
	BYTE m_byteFlags8;
	BYTE m_byteFlags9;
	PAD(IVVehicle, pad5, 0x3);
	DWORD m_dwTimeOfCreation2;
	PAD(IVVehicle, pad6, 0x20);
	WORD m_wAlaram;
	PAD(IVVehicle, pad7, 0x6);
	IVPed * m_pDriver;
	IVPed * m_pPassengers[8];
	PAD(IVVehicle, pad8, 0x20);
	BYTE m_byteColors[4];
	PAD(IVVehicle, pad9, 0xD8);
	BYTE m_byteMaxPassengers;
	PAD(IVVehicle, pad10, 0x7);
	float m_fGasPedal;
	float m_fBrakePedal;
	PAD(IVVehicle, pad11, 0x4);
	float m_fSteerBias;
	float m_fSteering;
	PAD(IVVehicle, pad12, 0x20);
	float m_fEngineHealth;
	PAD(IVVehicle, pad13, 0x8);
	BYTE m_byteCreatedBy;
	PAD(IVVehicle, pad14, 0xF);
	float m_fDirtLevel;
	PAD(IVVehicle, pad15, 0x4);
	BYTE m_byteSirenHealth[8];
	float m_fPetrolTankHealth;
	PAD(IVVehicle, pad16, 0xC4);
	BYTE m_byteSirenOn[8];
	PAD(IVVehicle, pad17, 0xEC);
	DWORD m_dwTimeOfCreation;
	PAD(IVVehicle, pad18, 0x38);
	DWORD m_dwDoorLockState;
	PAD(IVVehicle, pad19, 0x18);
	DWORD m_dwHorn;
	PAD(IVVehicle, pad20, 0xD90);
};

class CIVVehicle : public CIVPhysical
{

public:

	CIVVehicle( );
	CIVVehicle( IVVehicle * pVehicle );
	~CIVVehicle( );

	void					SetVehicle( IVVehicle * pVehicle );
	IVVehicle				* GetVehicle( );

	void					SetColors( unsigned char ucColor1, unsigned char ucColor2, unsigned char ucColor3, unsigned char ucColor4 );
	void					GetColors( unsigned char * ucColor1, unsigned char * ucColor2, unsigned char * ucColor3, unsigned char * ucColor4 );

	void					SetMaxPassengers( BYTE byteMaxPassengers );
	BYTE					GetMaxPassengers( );

	void					SetDriver( IVPed * pPed );
	IVPed					* GetDriver( );

	void					SetPassenger( BYTE byteSeat, IVPed * pPassenger );
	IVPed					* GetPassenger( BYTE byteSeat );
};

#endif // CIVVehicle_h