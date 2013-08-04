//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetworkEntity.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CNetworkEntity_h
#define CNetworkEntity_h

#include <Common.h>
#include <Math/CMaths.h>

enum eEntityType
{
	PLAYER_ENTITY,
	VEHICLE_ENTITY,
	OBJECT_ENTITY,
	PICKUP_ENTITY,
	LABEL_ENTITY,
	FIRE_ENTITY,
	CHECKPOINT_ENTITY,
	BLIP_ENTITY,
	ACTOR_ENTITY,
	UNKNOWN_ENTITY, // MAX_ENTITY
	INVALID_ENTITY,
};

class CNetworkEntity {
private:
	eEntityType			m_eType;
	EntityId			m_entityId;
	CVector3			m_vecPosition;
	CVector3			m_vecRotation;
	CVector3			m_vecMoveSpeed;
	CVector3			m_vecTurnSpeed;

public:
	CNetworkEntity();
	CNetworkEntity(eEntityType eType);
	CNetworkEntity(eEntityType eType, EntityId entityId);
	~CNetworkEntity();

	virtual bool		Create() = 0;
	virtual bool		Destroy() = 0;

	virtual void		Pulse() { /* Nothing can be done here */ };

	virtual void		GetPosition(CVector3& vecPos);
	virtual void		SetPosition(const CVector3& vecPos);

	virtual void		GetRotation(CVector3& vecRot);
	virtual void		SetRotation(const CVector3& vecRot);

	virtual void		GetMoveSpeed(CVector3& vecMoveSpeed);
	virtual void		SetMoveSpeed(const CVector3& vecMoveSpeed);

	virtual void		GetTurnSpeed(CVector3& vecTurnSpeed);
	virtual void		SetTurnSpeed(const CVector3& vecTurnSpeed);

	virtual EntityId	GetId() { return m_entityId; }
	virtual void		SetId(EntityId entityId) { m_entityId = entityId; }

	bool				IsOnScreen();

	virtual	bool		IsMoving();
	virtual void		StopMoving();

	virtual void		Serialize(ePackageType pType);
	virtual void		Deserialize(ePackageType pType);

	virtual void		AddToWorld() { /* Nothing can be done here */ };
	virtual void		RemoveFromWorld(bool bStopMoving = true) { /* Nothing can be done here */ };

	//virtual void		SetInterior(DWORD dwInterior) { m_dwInterior = dwInterior; }
	//virtual DWORD		GetInterior() { return m_dwInterior; }

	eEntityType			GetType() { return m_eType; }
	void				SetType(eEntityType eType) { m_eType = eType; }
};

#endif // CNetworkEntity_h