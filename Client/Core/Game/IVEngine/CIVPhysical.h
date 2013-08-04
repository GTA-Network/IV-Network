//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVPhysical.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPhysical_h
#define CIVPhysical_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVDynamicEntity.h"

class IVPhysicalVFTable : public IVDynamicEntityVFTable
{
public:
	DWORD mDC;
	DWORD mE0;
	DWORD mE4;
	DWORD mE8;
	DWORD GetMoveSpeed;
	DWORD mF0;
	DWORD SetHealth;
	DWORD mF8;
	DWORD GetHealth;
	DWORD m100;
	DWORD m104;
	DWORD m108;
	DWORD m10C;
	DWORD m110;
	DWORD m114;
	DWORD m118;
	DWORD m11C;
};

class IVPhysical : public IVDynamicEntity
{
public:
	PAD(IVPhysical, pad0, 0xD8);
	IVEntity * m_pLastDamageEntity;
	PAD(IVPhysical, pad1, 0x4);
	PAD(IVPhysical, pad2, 0x4); // todo - eWeaponType m_lastDamageWeapon;
	float m_fHealth;
	PAD(IVPhysical, pad3, 0x1C);
};

class CIVPhysical : public CIVDynamicEntity
{
	
public:

	CIVPhysical( );
	CIVPhysical( IVPhysical * pPhysical );
	~CIVPhysical( );

	void			SetPhysical( IVPhysical * pPhysical );
	IVPhysical		* GetPhysical( );

	void			SetMoveSpeed( CVector3 vecMoveSpeed );
	void			GetMoveSpeed( CVector3 * vecMoveSpeed );

	void			SetTurnSpeed( CVector3 vecTurnSpeed );
	void			GetTurnSpeed( CVector3 * vecTurnSpeed );

	void			SetLastDamageEntity( IVEntity * pLastDamageEntity );
	IVEntity		* GetLastDamageEntity( );

	void			SetHealth( float fHealth );
	float			GetHealth( );

};

#endif // CIVPhysical_h