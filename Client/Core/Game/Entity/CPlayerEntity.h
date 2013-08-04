//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CPlayerEntity.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPlayerEntity_h
#define CPlayerEntity_h

#include "CNetworkEntity.h"

class CPlayerEntity : public CNetworkEntity
{
private:

public:
	CPlayerEntity();
	~CPlayerEntity();

	bool				IsSpawned();

	virtual bool		Create();
	virtual bool		Destroy();

	EntityId			GetPlayerId() { return CNetworkEntity::GetId(); }
	void				SetPlayerId(EntityId playerId) { CNetworkEntity::SetId(playerId); }

	// Override funtion here
	virtual void		GetPosition(CVector3& vecPos);
	virtual void		SetPosition(const CVector3& vecPos);

	virtual void		GetRotation(CVector3& vecRot);
	virtual void		SetRotation(const CVector3& vecRot);

	virtual void		GetMoveSpeed(CVector3& vecMoveSpeed);
	virtual void		SetMoveSpeed(const CVector3& vecMoveSpeed);

	virtual void		GetTurnSpeed(CVector3& vecTurnSpeed);
	virtual void		SetTurnSpeed(const CVector3& vecTurnSpeed);
};

#endif // CPlayerEntity_h