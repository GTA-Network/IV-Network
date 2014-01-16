/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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