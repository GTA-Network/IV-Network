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

class CPlayerEntity;
class CVehicleEntity;

class CNetworkEntityType {
public:
	static CString		ConverEntityTypeStringToEntityId(eEntityType eEntityType)
	{
		switch(eEntityType)
		{
		case PLAYER_ENTITY:
			{
				return CString("PLAYER_ENTITY");
			}
		case VEHICLE_ENTITY:
			{
				return CString("VEHICLE_ENTITY");
			}
		case OBJECT_ENTITY:
			{
				return CString("OBJECT_ENTITY");
			}
		case PICKUP_ENTITY:
			{
				return CString("PICKUP_ENTITY");
			}
		case LABEL_ENTITY:
			{
				return CString("LABEL_ENTITY");
			}
		case FIRE_ENTITY:
			{
				return CString("FIRE_ENTITY");
			}
		case CHECKPOINT_ENTITY:
			{
				return CString("CHECKPOINT_ENTITY");
			}
		case BLIP_ENTITY:
			{
				return CString("BLIP_ENTITY");
			}
		case ACTOR_ENTITY:
			{
				return CString("ACTOR_ENTITY");
			}
		case UNKNOWN_ENTITY:
			{
				return CString("UNKNOWN_ENTITY");
			}
		case INVALID_ENTITY:
			{
				return CString("INVALID_ENTITY");
			}
		default:
			{
				return CString("Wrong entity type..");
			}
		}

		return CString("Some shit happened. Please restart the client");
	}

	static BYTE			ConvertEntityTypeToEntityTypeString(CString strEntityType)
	{
		if(strEntityType.Find("PLAYER_ENTITY") != std::string::npos)
			return 0;
		if(strEntityType.Find("VEHICLE_ENTITY") != std::string::npos)
			return 1;
		if(strEntityType.Find("OBJECT_ENTITY") != std::string::npos)
			return 2;
		if(strEntityType.Find("PICKUP_ENTITY") != std::string::npos)
			return 3;
		if(strEntityType.Find("LABEL_ENTITY") != std::string::npos)
			return 4;
		if(strEntityType.Find("FIRE_ENTITY") != std::string::npos)
			return 5;
		if(strEntityType.Find("CHECKPOINT_ENTITY") != std::string::npos)
			return 6;
		if(strEntityType.Find("BLIP_ENTITY") != std::string::npos)
			return 7;
		if(strEntityType.Find("ACTOR_ENTITY") != std::string::npos)
			return 8;
		if(strEntityType.Find("UNKNOWN_ENTITY") != std::string::npos)
			return 9;
		if(strEntityType.Find("INVALID_ENTITY") != std::string::npos)
			return 10;

		// Return invalid
		return 10;
	}
};

class CNetworkEntity {
private:
	eEntityType						m_eType;
	EntityId						m_entityId;
	CVector3						m_vecPosition;
	CVector3						m_vecRotation;
	CVector3						m_vecMoveSpeed;
	CVector3						m_vecTurnSpeed;
	CVector3						m_vecDirection;
	CVector3						m_vecRoll;
public:
									CNetworkEntity();
									CNetworkEntity(eEntityType eType);
									CNetworkEntity(eEntityType eType, EntityId entityId);
									~CNetworkEntity();

	virtual bool					Create() = 0;
	virtual bool					Destroy() = 0;

	virtual void					Pulse() {};
	
	virtual void					GetPosition(CVector3& vecPos);
	virtual void					SetPosition(const CVector3& vecPos);

	virtual void					GetRotation(CVector3& vecRot);
	virtual void					SetRotation(const CVector3& vecRot);

	virtual void					GetMoveSpeed(CVector3& vecMoveSpeed);
	virtual void					SetMoveSpeed(const CVector3& vecMoveSpeed);

	virtual void					GetTurnSpeed(CVector3& vecTurnSpeed);
	virtual void					SetTurnSpeed(const CVector3& vecTurnSpeed);

	virtual void					GetDirectionSpeed(CVector3& vecDirectionSpeed);
	virtual void					SetDirectionSpeed(const CVector3& vecDirectionSpeed);

	virtual void					GetRollSpeed(CVector3& vecRollSpeed);
	virtual void					SetRollSpeed(const CVector3& vecRollSpeed);

	virtual EntityId				GetId() { return m_entityId; }
	virtual void					SetId(EntityId entityId) { m_entityId = entityId; }

	bool							IsOnScreen();

	virtual	bool					IsMoving();
	virtual void					StopMoving();

	virtual void					Serialize(RakNet::BitStream * pBitStream) {};
	virtual void					Deserialize(RakNet::BitStream * pBitStream) {};

	virtual void					AddToWorld() { /* Nothing can be done here */ };
	virtual void					RemoveFromWorld(bool bStopMoving = true) { /* Nothing can be done here */ };

	//virtual void					SetInterior(DWORD dwInterior) { m_dwInterior = dwInterior; }
	//virtual DWORD					GetInterior() { return m_dwInterior; }

	eEntityType						GetType() { return m_eType; }
	void							SetType(eEntityType eType) { m_eType = eType; }
};

#endif // CNetworkEntity_h