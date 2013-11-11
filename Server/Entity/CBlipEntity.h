//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CBlipEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CBlipEntity_h
#define CBlipEntity_h

#include "CNetworkEntity.h"

class CScriptBlip;

class CBlipEntity : public CNetworkEntity {
private:
	CScriptBlip*	m_pScriptBlip;

	CVector3		m_vecPos;
	unsigned		m_iBlipIcon;
	unsigned int	m_uiColor;
	float			m_fSize;
	bool			m_bRange;
	bool			m_bVisible;
	CString			m_sName;
public:
	CBlipEntity();
	~CBlipEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}

	void				SetScriptBlip(CScriptBlip* pScriptBlip) { m_pScriptBlip = pScriptBlip; }
	CScriptBlip*		GetScriptBlip() { return m_pScriptBlip; }

	void				SetIcon(unsigned int iIcon) { m_iBlipIcon = iIcon; }
	int					GetIcon() { return m_iBlipIcon; }

	void				SetColor(unsigned int uiColor) { m_uiColor = uiColor; }
	int					GetColor() { return m_uiColor; }

	void				SetSize(float fSize) { m_fSize = fSize; }
	float				GetSize() { return m_fSize; }

	void				SetRange(bool bRange) { m_bRange = bRange; }
	bool				GetRange() { return m_bRange; }

	void				SetVisible(bool bVisible) { m_bVisible = bVisible; }
	bool				GetVisible() { return m_bVisible; }

	void				SetName(CString sName) { m_sName = sName; }
	CString				GetName() { return m_sName; }
};

class CScriptBlip : public CScriptEntity
{
public:
	CScriptBlip() { };
	~CScriptBlip() { };

	CBlipEntity *		GetEntity() { return (CBlipEntity*)CScriptEntity::GetEntity(); }

	const char *		GetScriptClassName() { return "CBlipEntity"; }

	void				SetPosition(float fX, float fY, float fZ);
	CVector3			GetPosition() { CVector3 vecPos; GetEntity()->GetPosition(vecPos); return vecPos; }

	void				SetIcon(unsigned int iIcon);
	int					GetIcon() { return GetEntity()->GetIcon(); }

	void				SetColor(unsigned int uiColor);
	unsigned int		GetColor() { return GetEntity()->GetColor(); }

	void				SetSize(float fSize);
	float				GetSize() { return GetEntity()->GetSize(); }

	void				SetRange(bool bRange);
	bool				GetRange() { return GetEntity()->GetRange(); }

	void				SetVisible(bool bVisible);
	bool				GetVisible() { return GetEntity()->GetVisible(); }

	void				SetName(CString sName);
	CString				GetName() { return GetEntity()->GetName(); }
};

#endif // CBlipEntity_h