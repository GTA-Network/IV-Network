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

#ifndef CContextData_h
#define CContextData_h

#include <Common.h>
#include "EFLC/CPlayerInfo.h"
#include "EFLC/CPlayerPed.h"
#include "EFLC/CPad.h"

struct sWeaponHandlerData
{
	CVector3	m_vecAimPosition;
	float		m_ArmUp;
	float		m_ArmDown;
	CVector3	m_vecShotSource;
	CVector3	m_vecShotTarget;
};

class CContextData
{
private:
	EFLC::CPlayerInfo			* m_pPlayerInfo;
	EFLC::CPlayerPed			* m_pPlayerPed;
	EFLC::CPad					* m_pPad;

	sWeaponHandlerData		  m_WeaponHandle;

public:

	CContextData(EFLC::CPlayerInfo * pPlayerInfo)
	{
		// Set the player info
		SetPlayerInfo(pPlayerInfo);

		// Set the player ped
		SetPlayerPed(NULL);

		// Create the pad
		m_pPad = new EFLC::CPad();

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

	void              SetPlayerPed(EFLC::CPlayerPed * pPlayerPed) { m_pPlayerPed = pPlayerPed; }
	EFLC::CPlayerPed    * GetPlayerPed() { return m_pPlayerPed; }

	void              SetPlayerInfo(EFLC::CPlayerInfo * pPlayerInfo) { m_pPlayerInfo = pPlayerInfo; }
	EFLC::CPlayerInfo   * GetPlayerInfo() { return m_pPlayerInfo; }

	EFLC::CPad			* GetPad() { return m_pPad; }


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

class CContextDataManager
{
private:
	static std::list< CContextData *>	m_contextDataList;

public:

									CContextDataManager() { };
									~CContextDataManager();

									static	CContextData			* CreateContextData(EFLC::CPlayerInfo * pPlayerInfo);
	static	void					DestroyContextData(CContextData * pContextData);

	static CContextData				* GetContextData(BYTE bytePlayerNumber);
	static CContextData				* GetContextData(EFLC::CPlayerInfo * pPlayerInfo);
	static CContextData				* GetContextData(EFLC::IPlayerInfo * pPlayerInfo);
	static CContextData				* GetContextData(EFLC::CPlayerPed * pPlayerPed);
	static CContextData				* GetContextData(EFLC::IPlayerPed * pPlayerPed);

};


#endif // CContextData_h