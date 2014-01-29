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

#ifndef CPlayerEntity_h
#define CPlayerEntity_h

#include <Common.h>
#include "CNetworkEntity.h"

#include <Math/CMaths.h>
#include <Game/CContextData.h>
#include <Game/EFLC/CPlayerPed.h>
#include <Game/EFLC/CModelInfo.h>
#include <Network/CBitStream.h>
#include <Game/eGame.h>
#include "CPlayerWeapons.h"

class CVehicleEntity;
_GAME_BEGIN
class CPlayerPed;
class CPlayerInfo;
_GAME_END

class CContextData;

class CPlayerEntity : public CNetworkEntity 
{
private:
	bool									m_bLocalPlayer;
	bool									m_bNetworked;
	bool									m_bSpawned;
	unsigned short							m_usPlayerId;	
	unsigned short							m_usPing;
	unsigned int							m_uiColor;
	
	unsigned								m_uiBlip;
	CString									m_strNick;

	EFLC::CPlayerPed						* m_pPlayerPed;
	EFLC::CPlayerInfo						* m_pPlayerInfo;
	EFLC::CModelInfo						* m_pModelInfo;
	CPlayerWeapons							* m_pPlayerWeapons;
	BYTE									m_bytePlayerNumber;
	CContextData							* m_pContextData;

	CControlState							m_lastControlState;
	CControlState							m_ControlState;


	CNetworkPlayerSyncPacket		m_LastSyncPacket;

	struct
	{
		struct
		{
			CVector3      vecStart;
			CVector3      vecTarget;
			CVector3      vecError;
			float         fLastAlpha;
			unsigned long ulStartTime;
			unsigned long ulFinishTime;
		}								pos;
		struct
		{
			float      fStart;
			float      fTarget;
			float      fError;
			float         fLastAlpha;
			unsigned long ulStartTime;
			unsigned long ulFinishTime;
		}								rot;
	}			m_interp;

	unsigned long							m_ulLastSyncReceived;

	int										m_iWantedLevel;

	struct 
	{
		unsigned char	ucHead;
		unsigned char	ucUpperBody; // e.g. shirt
		unsigned char	ucLowerBody; // e.g. pants, skirts
		unsigned char	ucSpecial1;
		unsigned char	ucHand;
		unsigned char	ucFeet; // e.g. shoes
		unsigned char	ucJacket;
		unsigned char	ucHair;
		unsigned char	ucSpecial2;
		unsigned char	ucSpecial3;
		unsigned char	ucFace;
	}										m_sClothes;

	inline BYTE									GetClothesValueFromSlot(BYTE bodyPart)
	{
		switch(bodyPart)
		{
			case 0: return m_sClothes.ucHead;
			case 1: return m_sClothes.ucUpperBody;
			case 2: return m_sClothes.ucLowerBody;
			case 3: return m_sClothes.ucSpecial1;
			case 4: return m_sClothes.ucHand;
			case 5: return m_sClothes.ucFeet;
			case 6: return m_sClothes.ucJacket;
			case 7: return m_sClothes.ucHair;
			case 8: return m_sClothes.ucSpecial2;
			case 9: return m_sClothes.ucSpecial3;
			case 10: return m_sClothes.ucFace;
			default: return 0;
		}
	}

	inline void									SetClothesValue(BYTE bodyPart, BYTE byteValue)
	{
		switch(bodyPart)
		{
			case 0: m_sClothes.ucHead = byteValue; break;
			case 1: m_sClothes.ucUpperBody = byteValue; break;
			case 2: m_sClothes.ucLowerBody = byteValue; break;
			case 3: m_sClothes.ucSpecial1 = byteValue; break;
			case 4: m_sClothes.ucHand = byteValue; break;
			case 5: m_sClothes.ucFeet = byteValue; break;
			case 6: m_sClothes.ucJacket = byteValue; break;
			case 7: m_sClothes.ucHair = byteValue; break;
			case 8: m_sClothes.ucSpecial2 = byteValue; break;
			case 9: m_sClothes.ucSpecial3 = byteValue; break;
			case 10: m_sClothes.ucFace = byteValue; break;
			default: break;
		}
	}

public: // Handles "GET" functions

	inline bool						IsLocalPlayer() { return m_bLocalPlayer; }
	inline bool						IsSpawned() { return m_bSpawned; }
	
	bool							IsInVehicle() { return (m_pVehicle != NULL); }
	bool							IsPassenger() { return (m_pVehicle != NULL && m_byteSeat != 0); }
	
	bool							HasTargetPosition() { return (m_interp.pos.ulFinishTime != 0); }
	bool							HasTargetRotation() { return (m_interp.rot.ulFinishTime != 0); }
	
	bool							HasVehicleEnterExit() { return (m_pVehicleEnterExit->bEntering || m_pVehicleEnterExit->bExiting); }
	bool							GetClosestVehicle(bool bPassenger, CVehicleEntity ** pVehicle, BYTE& byteSeat);
	bool							IsGettingIntoAVehicle();
	bool							IsGettingOutOfAVehicle();
	bool							IsJumping();

	void							GiveMoney(int iAmount);
    void							SetMoney(int iAmount);
    void							ResetMoney();
    int								GetMoney();
		
	unsigned short					GetPing();
	EntityId						GetPlayerId() { return CNetworkEntity::GetId(); }
	float							GetHeading();
	
	void							GetMoveSpeed(CVector3& vecMoveSpeed);
	void							GetPosition(CVector3 &vecPosition);
	void							GetRotation(CVector3 &vecRotation);
	void							GetTurnSpeed(CVector3& vecTurnSpeed);
	
	BYTE							GetPlayerGameNumber() { return m_bytePlayerNumber; }

	unsigned						GetColor() { return m_uiColor; }
	float							GetHealth();
	float							GetArmour();
	int								GetWantedLevel();

	CContextData					* GetContextData() { return m_pContextData; }
	EFLC::CPlayerPed				* GetPlayerPed() { return m_pPlayerPed; }
	EFLC::CPlayerInfo				* GetPlayerInfo() { return m_pPlayerInfo; }
	CVehicleEntity					* GetVehicle() { return m_pVehicle; }


public:
									CPlayerEntity(bool bLocalPlayer = false);
									~CPlayerEntity();

	void							SetPing(unsigned short usPing) { m_usPing = usPing; }

	void							SetPosition(CVector3 &vecPosition, bool bForce = false);
	void							SetRotation(CVector3 &vecRotation);
	void							SetHeading(float fAngle);
	void							SetHealth(float fHealth);
	void							SetArmour(float fArmour);
	void							SetModel(int iModelId);
	void							SetWantedLevel(int iWantedLevel);
	void							SetMoveSpeed(const CVector3& vecMoveSpeed);
	void							SetTurnSpeed(const CVector3& vecTurnSpeed);

	void							SetNick(const CString &strNick);
	CString							GetNick() { return m_strNick; }
	void							SetColor(unsigned uiColor);

	unsigned						GetScriptingHandle();

	void							Pulse();

	bool							Create();
	bool							Destroy();

	void							SetControlState(CControlState * pControlState);
	void							GetControlState(CControlState * pControlState);
	void							GetLastControlState(CControlState * pControlState);

	void							PutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void							RemoveFromVehicle();
	void							EnterVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void							ExitVehicle(eExitVehicleType exitType);
	void							ResetVehicleEnterExit();
	void							ClearVehicleEntryTask();
	void							ClearVehicleExitTask();
	
	void							Interpolate();
	void							ResetInterpolation();
	void							UpdateTargetPosition();
	void							RemoveTargetPosition();
	void							SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay);

	void							ClearWeaponAimAtTask();
	void							ClearWeaponShotAtTask();
	void							SetWeaponAimAtTask(const CVector3 &vecAimAt);
	void							SetWeaponShotAtTask(const CVector3 &vecShotAt);

	void							Kill(bool bInstandly);
	bool							IsDying();
	bool							IsDead();
	EFLC::IEntity					* GetLastDamageEntity();
	bool							GetKillInfo(EntityId & playerId, EntityId & vehicleId, EntityId & weaponId);

	void							SetClothes(unsigned short ucBodyLocation, unsigned  char ucClothes);
	unsigned char					GetClothes(unsigned short ucBodyLocation);

	decltype(m_pPlayerWeapons)		GetPlayerWeapons() { return m_pPlayerWeapons; }

	virtual void					Serialize(RakNet::BitStream * pBitStream);
	virtual void					Deserialize(RakNet::BitStream * pBitStream);

	bool							IsOnScreen();

	CNetworkPlayerSyncPacket		GetLastSyncPacket() { return m_LastSyncPacket; }
	void							SetLastSyncPacket(const CNetworkPlayerSyncPacket& Packet) { m_LastSyncPacket = Packet; }

	void							SetLastControlState(const CControlState & controlState) { m_lastControlState = controlState; }

	BYTE							GetSeat() { return m_byteSeat; }

	/* TEST STUFF */
	void SerializeTaskInfo(RakNet::BitStream * pBitStream);
	void DeserializeTaskInfo(RakNet::BitStream* pBitStream);
	
	CString							GetDebugText();

protected:
	sPlayerEntity_VehicleData		* m_pVehicleEnterExit;
	CVehicleEntity					* m_pVehicle;
	BYTE							m_byteSeat;

	void							InternalPutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat);
	void							InternalRemoveFromVehicle();
	bool							InternalIsInVehicle();
	
};

#endif // CPlayerEntity_h