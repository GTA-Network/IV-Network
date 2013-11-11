//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CBlipEntity.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CBlipEntity_h
#define CBlipEntity_h

#include "CNetworkEntity.h"
#include "..\..\IV\CIVScriptEnums.h"

class CBlipEntity : public CNetworkEntity {
private:
	EntityId				 m_blipId;
	CIVScript::eBlipSprite   m_eIcon;
	CVector3				 m_vecPos;
	unsigned int			 m_uiColor;
	float					 m_fSize;
	bool					 m_bRange;
	bool					 m_bRouteBlip;
	bool					 m_bVisible;
	CString					 m_sName;
	unsigned int			 m_uiBlip;
public:
	CBlipEntity(CIVScript::eBlipSprite icon, CVector3 vecPosition, bool bVisible);
	~CBlipEntity();

	bool							Create() { return true; }
	bool							Destroy() { return true; }

	void							SetId(EntityId blipId) { m_blipId = blipId; }
	EntityId						GetId() { return m_blipId; }

	void							SetIcon(CIVScript::eBlipSprite icon);
	CIVScript::eBlipSprite			GetIcon();

	void							SetPosition(CVector3 vecPosition);
	CVector3						GetPosition();

	void							SetColor(unsigned int uiColor);
	unsigned int					GetColor();

	void							SetSize(float fSize);
	float							GetSize();

	void							SetRange(bool bRange);
	bool							GetRange();

	void							SetVisible(bool bVisible);
	bool							GetVisible();

	void							SetName(CString sName);
	CString							GetName();
};

#endif // CBlipEntity_h