//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CCheckpointEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CCheckpointEntity_h
#define CCheckpointEntity_h

#include "CNetworkEntity.h"

class CScriptCheckpoint;

class CCheckpointEntity : public CNetworkEntity 
{
private:
	CScriptCheckpoint*		m_pScriptCheckpoint;
	int						m_wType;
	CVector3				m_vecTargetPosition;
	float					m_fRadius;
	bool					m_bVisible;
public:
	CCheckpointEntity();
	~CCheckpointEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}

	void					SetScriptCheckpoint(CScriptCheckpoint* pScriptCheckpoint) { m_pScriptCheckpoint = pScriptCheckpoint; }
	CScriptCheckpoint*		GetScriptCheckpoint() { return m_pScriptCheckpoint; }

	void					SetType(int wType) { m_wType = wType; }
	int						GetType() { return m_wType; }

	void					SetTargetPosition(CVector3 vecTargetPosition) { m_vecTargetPosition = vecTargetPosition; }
	void					GetTargetPosition(CVector3& vecTargetPosition) { vecTargetPosition = m_vecTargetPosition; }

	void					SetVisible(bool bVisible) { m_bVisible = bVisible; }
	bool					GetVisible() { return m_bVisible; }

	void					SetRadius(float fRadius) { m_fRadius = fRadius; }
	float					GetRadius() { return m_fRadius; }
};

class CScriptCheckpoint : public CScriptEntity
{
public:
	CScriptCheckpoint() { };
	~CScriptCheckpoint() { };

	CCheckpointEntity *		GetEntity() { return (CCheckpointEntity*)CScriptEntity::GetEntity(); }

	const char *			GetScriptClassName() { return "CCheckpointEntity"; }

	void					DeleteCheckpoint();

	void					ShowForPlayer(EntityId playerId);
	void					HideForPlayer(EntityId playerId);

	void					ShowForAll();
	void					HideForAll();

	void					SetType(int iType);
	int						GetType() { return GetEntity()->GetType(); }

	void					SetPosition(float fX, float fY, float fZ);
	CVector3				GetPosition() { CVector3 vecPos; GetEntity()->GetPosition(vecPos); return vecPos; }

	void					SetTargetPosition(float fX, float fY, float fZ);
	CVector3				GetTargetPosition() { CVector3 vecNextPos; GetEntity()->GetTargetPosition(vecNextPos); return vecNextPos; }

	void					SetRadius(float fRadius);
	float					GetRadius() { return GetEntity()->GetRadius(); }
};

#endif // CCheckpointEntity_h