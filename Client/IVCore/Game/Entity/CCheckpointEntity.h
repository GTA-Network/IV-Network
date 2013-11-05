//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CCheckpointEntity.cpp
// Project: Client.Core
// Author: Knight
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CCheckpointEntity_h
#define CCheckpointEntity_h

#include "CNetworkEntity.h"
#include "..\..\IV\CIVScriptEnums.h"

class CCheckpointEntity : public CNetworkEntity {
private:
	EntityId             m_checkpointId;
	CIVScript::eCheckpointType      m_eType;
	CVector3             m_vecPosition;
	CVector3             m_vecTargetPosition;
	float                m_fRadius;
	bool                 m_bInCheckpoint;
	bool                 m_bIsVisible;
public:
	CCheckpointEntity(CIVScript::eCheckpointType type, CVector3 vecPosition, CVector3 vecTargetPosition, float fRadius);
	~CCheckpointEntity();

	bool Create() { return true; }
	bool Destroy() { return true; }

	void								SetId(EntityId checkpointId) { m_checkpointId = checkpointId; }
	EntityId							GetId() { return m_checkpointId; }

	unsigned int GetCheckpoint();

	void            Show();
	void            Hide();

	bool            IsVisible();

	void            SetType(CIVScript::eCheckpointType type);
	CIVScript::eCheckpointType GetType();

	void            SetPosition(const CVector3& vecPosition);
	void            GetPosition(CVector3& vecPosition);

	void            SetTargetPosition(const CVector3& vecTargetPosition);
	void            GetTargetPosition(CVector3& vecTargetPosition);

	void            SetRadius(float fRadius);
	float           GetRadius();

	void            Pulse();
};

#endif // CCheckpointEntity_h