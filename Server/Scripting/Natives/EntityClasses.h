#ifndef EntityClasses_h
#define EntityClasses_h

#include <CString.h>
#include "../Server/Entity/Entities.h"

class CScriptEntity
{
	CNetworkEntity* m_pEntity;
public:
	CScriptEntity() { };
	~CScriptEntity() { };

	CNetworkEntity* GetEntity() { return m_pEntity; }
	void SetEntity(CNetworkEntity* pEntity) { m_pEntity = pEntity; }

	void SetPosition(float fX, float fY, float fZ) { m_pEntity->SetPosition(CVector3(fX, fY, fZ)); }
	void SetRotation(float fX, float fY, float fZ) { m_pEntity->SetRotation(CVector3(fX, fY, fZ)); }
	void SetMoveSpeed(float fX, float fY, float fZ) { m_pEntity->SetMoveSpeed(CVector3(fX, fY, fZ)); }
	void SetTurnSpeed(float fX, float fY, float fZ) { m_pEntity->SetTurnSpeed(CVector3(fX, fY, fZ)); }
};

class CScriptVehicle : public CScriptEntity
{
public:
	CScriptVehicle() { SetEntity(new CVehicleEntity); };
	~CScriptVehicle() { delete GetEntity(); };
};

class CScriptPlayer : public CScriptEntity
{
public:
	CScriptPlayer() { };
	~CScriptPlayer() { };

	inline CPlayerEntity* GetEntity() { return (CPlayerEntity*) CScriptEntity::GetEntity(); }

	float GetArmour(void) {
		return GetEntity()->GetArmour();
	}

	void  SetArmour(float fArmour) {
		GetEntity()->SetArmour(fArmour);
	}

	DWORD GetColor(void) {
		return GetEntity()->GetColor();
	}
	void  SetColor(DWORD dwColor) {
		GetEntity()->SetColor(dwColor);
	}

	float GetHeading() {
		return GetEntity()->GetHeading();
	}
	void  SetHeading(float fHeading) {
		GetEntity()->SetHeading(fHeading);
	}

	const char* GetName() {
		return GetEntity()->GetName().C_String();
	}
	void		SetName(const char* szName) {
		GetEntity()->SetName(CString(szName));
		free((void*) szName);
	}

	int	GetMoney() { return 0; }
	void SetMoney(int iMoney) { }

	int GetModel() { return 0; }
	void SetModel(int iModel) { }

	unsigned int GetDimension() { return 0; }
	void		 SetDimension(unsigned int uiDimension) { }

	char GetWantedLevel() { return 0; }
	void SetWantedLevel(char cWantedLevel) { }

	float		GetHealth() { return GetEntity()->GetHealth(); }
	void		SetHealth(float fHealth) { GetEntity()->SetHealth(fHealth); }
};


#endif