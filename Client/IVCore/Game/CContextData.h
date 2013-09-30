//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CContextData.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CContextData_h
#define CContextData_h

#include <Common.h>
#include <Game/IVEngine/CIVPlayerInfo.h>
#include <Game/IVEngine/CIVPlayerPed.h>
#include <Game/IVEngine/CIVPad.h>

struct sWeaponHandlerData
{
	CVector3	m_vecAimPosition;
	float		m_ArmUp;
	float		m_ArmDown;
	CVector3	m_vecShotSource;
	CVector3	m_vecShotTarget;
};

class CContextData {
private:
	CIVPlayerInfo			* m_pPlayerInfo;
	CIVPlayerPed			* m_pPlayerPed;
	CIVPad					* m_pPad;

	sWeaponHandlerData		  m_WeaponHandle;

public:

	CContextData(CIVPlayerInfo * pPlayerInfo)
	{
		// Set the player info
		SetPlayerInfo(pPlayerInfo);

		// Set the player ped
		SetPlayerPed(NULL);

		// Create the pad
		m_pPad = new CIVPad();

		m_WeaponHandle.m_ArmUp = 0.0f;
		m_WeaponHandle.m_ArmDown = 0.0f;
	}

	~CContextData()
	{
		// Delete the pad
		SAFE_DELETE(m_pPad);

		m_WeaponHandle.m_ArmUp = 0.0f;
		m_WeaponHandle.m_ArmDown = 0.0f;
	}

	void              SetPlayerPed(CIVPlayerPed * pPlayerPed) { m_pPlayerPed = pPlayerPed; }
	CIVPlayerPed    * GetPlayerPed() { return m_pPlayerPed; }

	void              SetPlayerInfo(CIVPlayerInfo * pPlayerInfo) { m_pPlayerInfo = pPlayerInfo; }
	CIVPlayerInfo   * GetPlayerInfo() { return m_pPlayerInfo; }

	CIVPad			* GetPad() { return m_pPad; }


	void			SetWeaponAimTarget(const CVector3& vecAimTargetPosition) { m_WeaponHandle.m_vecAimPosition = vecAimTargetPosition; }
	void			GetWeaponAimTarget(CVector3& vecAimTargetPosition) { vecAimTargetPosition = m_WeaponHandle.m_vecAimPosition; }
	void            SetArmHeading(const float fArmHeading) { m_WeaponHandle.m_ArmUp = fArmHeading; }
    void            GetArmHeading(float& fArmHeading) { fArmHeading = m_WeaponHandle.m_ArmUp; }
    void            SetArmUpDown(const float fArmUpDown) { m_WeaponHandle.m_ArmDown = fArmUpDown; }
	void            GetArmUpDown(float& fArmUpDown) { fArmUpDown = m_WeaponHandle.m_ArmDown; }
	void            SetWeaponShotSource(const CVector3& vecWeaponShotSource) { m_WeaponHandle.m_vecShotSource = vecWeaponShotSource; }
	void            GetWeaponShotSource(CVector3& vecWeaponShotSource) { vecWeaponShotSource = m_WeaponHandle.m_vecShotSource; }
	void            SetWeaponShotTarget(const CVector3& vecWeaponShotTarget) { m_WeaponHandle.m_vecShotTarget = vecWeaponShotTarget; }
	void            GetWeaponShotTarget(CVector3& vecWeaponShotTarget) { vecWeaponShotTarget = m_WeaponHandle.m_vecShotTarget; }
};

class CContextDataManager {
private:
	static std::list< CContextData *>	m_contextDataList;

public:

									CContextDataManager() { };
									~CContextDataManager();

	static	CContextData			* CreateContextData(CIVPlayerInfo * pPlayerInfo);
	static	void					DestroyContextData(CContextData * pContextData);

	static CContextData				* GetContextData(BYTE bytePlayerNumber);
	static CContextData				* GetContextData(CIVPlayerInfo * pPlayerInfo);
	static CContextData				* GetContextData(IVPlayerInfo * pPlayerInfo);
	static CContextData				* GetContextData(CIVPlayerPed * pPlayerPed);
	static CContextData				* GetContextData(IVPlayerPed * pPlayerPed);

};


#endif // CContextData_h