//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CPlayerEntity.h
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPlayerEntity_h
#define CPlayerEntity_h

#include "CNetworkEntity.h"

#include <Common.h>
#include "Game/eInput.h"

class CScriptPlayer;

class CPlayerEntity : public CNetworkEntity {
public:


private:
	unsigned long m_ulLastSyncReceived;
	unsigned long m_ulLastSyncSent;
	ePackageType m_eLastSyncPackageType;

	
	CVector3	m_vecDirection;
	CVector3	m_vecRoll;
	bool		m_bDuckState;
	float		m_fHeading;
	CControls m_controlState;

	float		m_fHealth;
	float		m_fArmour;

	DWORD		m_dwColor;

	int			m_iModel;
	int			m_iMoney;
	int			m_iWantedLevel;
	int			m_iDimension;

	struct {
		CVector3		vecAimAtCoordinates;
		float			fArmsHeadingCircle;
		float			fArmsUpDownRotation;
		CVector3		vecShotAtCoordinates;
		CVector3		vecShotAtTarget;
		CVector3		vecLookAtCoordinates;
	} m_weaponData;

	CScriptPlayer*	m_pScriptPlayer;
	EntityId		m_vehicleId;
public:
	CString		m_strName;
	CPlayerEntity();
	~CPlayerEntity();

	bool Create() { return true; }
	bool Destroy() { return true; }

	void		Pulse();

	CScriptPlayer*  GetScriptPlayer() { return m_pScriptPlayer; }
	void			SetScriptPlayer(CScriptPlayer* pScriptPlayer) { m_pScriptPlayer = pScriptPlayer; }

	float		GetHealth() { return m_fHealth; }
	void		SetHealth(float fHealth) { m_fHealth = fHealth; }

	float		GetArmour() { return m_fArmour; }
	void		SetArmour(float fArmour) { m_fArmour = fArmour; }

	DWORD		GetColor() { return m_dwColor; }
	void		SetColor(DWORD dwColor) { m_dwColor = dwColor; }

	void		SetName(const CString& strName) { m_strName = strName; }
	CString		GetName() { return m_strName; }

	void		SetDirection(const CVector3& vecDirection) { m_vecDirection = vecDirection; }
	CVector3	GetDirection() { return m_vecDirection; }

	void		SetRoll(const CVector3& vecRoll) { m_vecRoll = vecRoll; }
	CVector3	GetRoll() { return m_vecRoll; }

	void		SetDucking(bool bDucking) { m_bDuckState = bDucking; }
	bool		IsDucking() { return m_bDuckState; }

	void		SetHeading(float fHeading) { m_fHeading = fHeading; }
	float		GetHeading() { return m_fHeading; }

	void		SetModel(int iModel) { m_iModel = iModel; }
	int			GetModel() { return m_iModel; }

	void		SetMoney(int iMoney) { m_iMoney = iMoney; }
	int			GetMoney() { return m_iMoney; }

	void		SetWantedLevel(int iWantedLevel) { m_iWantedLevel = iWantedLevel; }
	int			GetWantedLevel() { return m_iWantedLevel; }

	void		SetDimension(int iDimension) { m_iDimension = iDimension; }
	int			GetDimension() { return m_iDimension; }

	void		SetArmHeading(float fArmHeading) { m_weaponData.fArmsHeadingCircle = fArmHeading; }
	float		GetArmHeading() { return m_weaponData.fArmsHeadingCircle; }

	void		SetArmUpDown(float fArmUpDown) { m_weaponData.fArmsUpDownRotation = fArmUpDown; }
	float		GetArmUpDown() { return m_weaponData.fArmsUpDownRotation; }

	void		SetWeaponAimTarget(const CVector3& vecAimTarget) { m_weaponData.vecAimAtCoordinates = vecAimTarget; }
	CVector3	GetWeaponAimTarget() { return m_weaponData.vecAimAtCoordinates; }

	void		SetWeaponShotSource(const CVector3& vecShotSource) { m_weaponData.vecShotAtCoordinates = vecShotSource; }
	CVector3	GetWeaponShotSource() { return m_weaponData.vecShotAtCoordinates; }

	void		SetWeaponShotTarget(const CVector3& vecShotTarget) { m_weaponData.vecShotAtTarget = vecShotTarget; }
	CVector3	GetWeaponShotTarget() { return m_weaponData.vecShotAtTarget; }

	void		SetControlState(const CControls& controlState) { m_controlState = controlState; }
	void		GetControlState(CControls& controlState) { controlState = m_controlState; }

	void		SetPosition(const CVector3& vecPosition);

	void		Serialize(RakNet::BitStream * bitStream, ePackageType pType);
	void		Deserialize(RakNet::BitStream * bitStream, ePackageType pType);
};


class CScriptPlayer : public CScriptEntity
{
public:
	CScriptPlayer() { /*SetEntity(new CPlayerEntity);*/ };
	~CScriptPlayer() { /*delete GetEntity();*/ };

	inline CPlayerEntity* GetEntity() { return (CPlayerEntity*) CScriptEntity::GetEntity(); }

	virtual const char* GetScriptClassName() { return "CPlayerEntity"; }

	void  SetArmour(float fArmour);

	float GetArmour(void) {
		return GetEntity()->GetArmour();
	}

	void  SetColor(DWORD dwColor);

	DWORD GetColor(void) {
		return GetEntity()->GetColor();
	}

	void  SetHeading(float fHeading);

	float GetHeading() {
		return GetEntity()->GetHeading();
	}

	void		SetName(CString szName);

	CString GetName() {
		return GetEntity()->m_strName;
	}

	void SetModel(int iModel);

	int GetModel() {
		return GetEntity()->GetModel();
	}

	void SetMoney(int iMoney);

	int	GetMoney() {
		return GetEntity()->GetMoney();
	}

	void GiveMoney(int iMoney);

	void		 SetDimension(int iDimension);

	unsigned int GetDimension() {
		return GetEntity()->GetDimension();
	}

	void		SetWantedLevel(int iWantedLevel);

	int GetWantedLevel() {
		return GetEntity()->GetWantedLevel();
	}

	float		 GetHealth() { return GetEntity()->GetHealth(); }
	void		 SetHealth(float fHealth);

	void		SetPosition(float fX, float fY, float fZ);
	CVector3	GetPosition() { CVector3 vecPos; GetEntity()->GetPosition(vecPos); return vecPos; }

	void		SetRotation(float fX, float fY, float fZ);
	CVector3	GetRotation() { CVector3 vecRot; GetEntity()->GetRotation(vecRot); return vecRot; }

	void		SetMoveSpeed(float fX, float fY, float fZ);
	CVector3	GetMoveSpeed() { CVector3 vecMoveSpeed; GetEntity()->GetMoveSpeed(vecMoveSpeed); return vecMoveSpeed; }

	void		SetTurnSpeed(float fX, float fY, float fZ);
	CVector3	GetTurnSpeed() { CVector3 vecTurnSpeed; GetEntity()->GetTurnSpeed(vecTurnSpeed); return vecTurnSpeed; }

	void		SendPlayerMessage(CString sMessage, DWORD dwColor, bool bAllowFormatting);

	int			GetId() { return GetEntity()->GetId(); }

	bool		IsOnFoot() { return true; }
	void		SetSpawnLocation(float fX, float fY, float fZ);
	void		GiveWeapon(int id, int uiAmmo);
};

#endif // CPlayerEntity_h