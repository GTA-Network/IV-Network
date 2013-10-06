//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CNetworkEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CNetworkEntity_h
#define CNetworkEntity_h

#include <Common.h>
#include <Math/CMaths.h>
#include <Network/NetCommon.h>


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

	virtual void		Serialize(RakNet::BitStream * bitStream, ePackageType pType);
	virtual void		Deserialize(RakNet::BitStream * bitStream, ePackageType pType);

	virtual void		AddToWorld() { /* Nothing can be done here */ };
	virtual void		RemoveFromWorld(bool bStopMoving = true) { /* Nothing can be done here */ };

	//virtual void		SetInterior(DWORD dwInterior) { m_dwInterior = dwInterior; }
	//virtual DWORD		GetInterior() { return m_dwInterior; }

	eEntityType			GetType() { return m_eType; }
	void				SetType(eEntityType eType) { m_eType = eType; }
};

class CScriptEntity
{
	CNetworkEntity* m_pEntity;
public:
	CScriptEntity() { };
	~CScriptEntity() { };

	virtual const char* GetScriptClassName() { return "Keks"; }

	CNetworkEntity* GetEntity() { return m_pEntity; }
	void SetEntity(CNetworkEntity* pEntity) { m_pEntity = pEntity; }


	virtual void SetPosition(float fX, float fY, float fZ) { m_pEntity->SetPosition(CVector3(fX, fY, fZ)); }
	virtual void SetRotation(float fX, float fY, float fZ) { m_pEntity->SetRotation(CVector3(fX, fY, fZ)); }
	virtual void SetMoveSpeed(float fX, float fY, float fZ) { m_pEntity->SetMoveSpeed(CVector3(fX, fY, fZ)); }
	virtual void SetTurnSpeed(float fX, float fY, float fZ) { m_pEntity->SetTurnSpeed(CVector3(fX, fY, fZ)); }
};

#endif // CNetworkEntity_h