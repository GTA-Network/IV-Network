//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVVehicle.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVVehicle.h"
#include <Game/COffsets.h>
#include <CCore.h>
extern CCore * g_pCore;

CIVVehicle::CIVVehicle() :
	CIVPhysical()
{

}

CIVVehicle::CIVVehicle(IVVehicle * pVehicle) :
	CIVPhysical(pVehicle)
{

}

CIVVehicle::~CIVVehicle()
{

}

void CIVVehicle::SetVehicle(IVVehicle * pVehicle)
{
	SetPhysical(pVehicle);
}

IVVehicle * CIVVehicle::GetVehicle()
{
	return (IVVehicle *)GetPhysical();
}

void CIVVehicle::SetLoadCollision(bool bLoadCollision)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		bool _bLoadCollision = bLoadCollision;

		_asm	push _bLoadCollision;
		_asm	push pVehicle;
		_asm	call COffsets::FUNC_CVehicle__SetLoadCollision;
		_asm	add esp, 8;
	}
}

void CIVVehicle::SetAlarmDuration(WORD wDuration)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_wAlarm = wDuration;
}

WORD CIVVehicle::GetAlarmDuration()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_wAlarm;

	return 0;
}

void CIVVehicle::SetDriver(IVPed * pPed)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_pDriver = pPed;
}

IVPed * CIVVehicle::GetDriver()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_pDriver;

	return NULL;
}

void CIVVehicle::SetPassenger(BYTE bytePassengerSeatId, IVPed * pPassenger)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		if(bytePassengerSeatId < 8)
			pVehicle->m_pPassengers[bytePassengerSeatId] = pPassenger;
	}
}

IVPed * CIVVehicle::GetPassenger(BYTE bytePassengerSeatId)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		if(bytePassengerSeatId < 8)
			return pVehicle->m_pPassengers[bytePassengerSeatId];
	}

	return NULL;
}

void CIVVehicle::SetColors(unsigned char ucColor1, unsigned char ucColor2, unsigned char ucColor3, unsigned char ucColor4)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		pVehicle->m_byteColors[0] = ucColor1;
		pVehicle->m_byteColors[1] = ucColor2;
		pVehicle->m_byteColors[2] = ucColor3;
		pVehicle->m_byteColors[3] = ucColor4;

		_asm	mov ecx, pVehicle;
		_asm	call COffsets::FUNC_CVehicle__RefreshColours;
	}
}
void CIVVehicle::GetColors(unsigned char * ucColor1, unsigned char * ucColor2, unsigned char * ucColor3, unsigned char * ucColor4)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		*ucColor1 = pVehicle->m_byteColors[0];
		*ucColor2 = pVehicle->m_byteColors[1];
		*ucColor3 = pVehicle->m_byteColors[2];
		*ucColor4 = pVehicle->m_byteColors[3];
	}
}

void CIVVehicle::SetMaxPassengers(BYTE byteMaxPassengers)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_byteMaxPassengers = byteMaxPassengers;
}

BYTE CIVVehicle::GetMaxPasssengers()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_byteMaxPassengers;

	return 0;
}

bool CIVVehicle::HasSiren()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		// Check if the siren flag is set
		return IS_BIT_SET(*(BYTE *)(pVehicle + 0xF6E), 0x20);
	}

	return false;
}

void CIVVehicle::SetSirenState(bool bStatus)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle && HasSiren())
	{
		if(bStatus)
			*(BYTE *)(pVehicle + 0xF69) = *(BYTE *)(pVehicle + 0xF69) & 0x9F | 0x10;
		else
			*(BYTE *)(pVehicle + 0xF69) &= 0x8F;
	}
}

bool CIVVehicle::GetSirenState()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle && HasSiren())
	{
		if(!IS_BIT_SET(*(BYTE *)(pVehicle + 0xF69), 0x10))
			return false;

		if(!IS_BIT_SET(*(BYTE *)(pVehicle + 0xF69), 0x20))
			return false;

		return true;
	}

	return false;
}

void CIVVehicle::SetGasPedal(float fGasPedal)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_fGasPedal = fGasPedal;
}

float CIVVehicle::GetGasPedal()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_fGasPedal;

	return 0.0f;
}

void CIVVehicle::SetBrakePedal(float fBrakePedal)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_fBrakePedal = fBrakePedal;
}

float CIVVehicle::GetBrakePedal()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_fBrakePedal;

	return 0.0f;
}

void CIVVehicle::SetSteerBias(float fSteerBias)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_fSteerBias = fSteerBias;
}

float CIVVehicle::GetSteerBias()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_fSteerBias;

	return 0.0f;
}

void CIVVehicle::SetSteeringAngle(float fSteeringAngle)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_fSteering = fSteeringAngle;
}

float CIVVehicle::GetSteeringAngle()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_fSteering;

	return 0.0f;
}

void CIVVehicle::SetEngineHealth(float fEngineHealth)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_fEngineHealth = fEngineHealth;
}

float CIVVehicle::GetEngineHealth()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_fEngineHealth;

	return 0.0f;
}

void CIVVehicle::SetDirtLevel(float fDirtLevel)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_fDirtLevel = Math::Clamp(0.0f, fDirtLevel, 15.0f);
}

float CIVVehicle::GetDirtLevel()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_fDirtLevel;

	return 0.0f;
}

void CIVVehicle::SetPetrolTankHealth(float fPetrolTankHealth)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_fPetrolTankHealth = fPetrolTankHealth;
}

float CIVVehicle::GetPetrolTankHealth()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_fPetrolTankHealth;

	return 0.0f;
}

void CIVVehicle::SetDoorLockState(DWORD dwDoorLockState)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_dwDoorLockState = dwDoorLockState;
}

DWORD CIVVehicle::GetDoorLockState()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return pVehicle->m_dwDoorLockState;

	return 0;
}

void CIVVehicle::SetEngineStatus(bool bStatus, bool bUnknown)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		if(bStatus) {
			bool bUnknownTrue = true;

			_asm	push bUnknownTrue;
			_asm	mov ecx, pVehicle;
			_asm	call COffsets::FUNC_CVehicle__SetEngineOn;
		}
		else {
			_asm mov ecx, pVehicle;
			_asm call COffsets::FUNC_CVehicle__SetEngineOff;
		}
	}
}

bool CIVVehicle::GetEngineStatus()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(IS_BIT_SET(pVehicle->m_byteFlags1, 8))
		return true;

	return false;
}

void CIVVehicle::SoundHorn(int iDuration)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		pVehicle->m_dwHorn = 30 * iDuration / 1000;
}

void CIVVehicle::SetComponentState(BYTE byteComponent, bool bState)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if (pVehicle && byteComponent >= 0 && byteComponent <= 8)
			((int(__thiscall *)(IVVehicle*, BYTE, bool))COffsets::FUNC_CVehicle__SetComponentDisabled)(pVehicle, byteComponent + 89, !bState);
}

BYTE CIVVehicle::GetTextureVariationCount()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return g_pCore->GetGame()->GetModelInfo(pVehicle->m_wModelIndex)->GetModelInfo()->byteTextureVariationCount;

	return 255;
}

void CIVVehicle::SetTextureVariation(int iVariation)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		// Get the number of texture variations
		BYTE byteTextureVariationCount = GetTextureVariationCount();

		// Do we have no texture variations?
		if(byteTextureVariationCount == 255)
			return;

		// Is the texture variation valid?
		if(iVariation < byteTextureVariationCount)
		{
			DWORD dwTemp = (*(DWORD *)(pVehicle + 0x34) + 4);
			*(DWORD *)(dwTemp + 0xD8) = iVariation;

			_asm	push -1;
			_asm	push pVehicle;
			_asm	mov ecx, dwTemp;
			_asm	call COffsets::FUNC_CVehicle__SetTextureVariation;
		}
	}
}

int CIVVehicle::GetTextureVariation()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		// Get the number of texture variations
		BYTE byteTextureVariationCount = GetTextureVariationCount();

		// Do we have any texture variations?
		if(byteTextureVariationCount)
		{
			DWORD dwTemp = *(DWORD *)(*(DWORD *)(pVehicle + 0x34) + 4);
			return *(DWORD *)(dwTemp + 0xD8);
		}
	}

	return 0;
}

void CIVVehicle::SetCanBeVisiblyDamaged(bool bState)
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
	{
		if(bState)
			SET_BIT(pVehicle->m_byteFlags9, 4);
		else
			UNSET_BIT(pVehicle->m_byteFlags9, 4);
	}
}

bool CIVVehicle::CanBeVisiblyDamaged()
{
	// Do we have a valid vehicle pointer?
	IVVehicle * pVehicle = GetVehicle();

	if(pVehicle)
		return IS_BIT_SET(pVehicle->m_byteFlags9, 4);

	return false;
}

void CIVVehicle::SetGPSState(bool bState)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		*(bool*)(pVehicle + 0xB02) = bState;
}

bool CIVVehicle::GetGPSState()
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		return *(bool*)(pVehicle + 0xB02);
	return false;
}

//TODO: Add Get? *(DWORD *)(pVehicle + 0xFD0); // 4048
void CIVVehicle::BurstCarTyre(int iTyre)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
	{
		_asm	push iTyre;
		_asm	mov ecx, pVehicle;
		_asm	call COffsets::FUNC_CVehicle__BurstCarTyre;
	}
}

void CIVVehicle::GetDeformation(CVector3& vecPos)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		; //vecPos = pVehicle->m_pDamageManager->vecDamage;
}

void CIVVehicle::SetCarCanBeDamaged(bool bDamage)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
	{
		DWORD byteFlagDamage = *(DWORD *)(pVehicle + 0x118); // 280 (flag?)
		if(bDamage)
			*(DWORD *)byteFlagDamage &= 0x400u;
		else
			*(DWORD *)byteFlagDamage |= 0xFFFFFBFFu;
	}
}

void CIVVehicle::RemoveCarWindow(int iWindow)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
	{
		DWORD dwFunctionAddress = COffsets::FUNC_CVehicle__RemoveVehicleWindow;
		
		_asm	push iWindow;
		_asm	mov ecx, pVehicle;
		_asm	call COffsets::FUNC_CVehicle__RemoveVehicleWindow;
	}
}

void CIVVehicle::SetLightsState(int iState)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		iState == 2 ? pVehicle->m_byteLightState ^= (2 ^ pVehicle->m_byteLightState) & 3 : pVehicle->m_byteLightState ^= (1 ^ pVehicle->m_byteLightState) & 3;
}

int CIVVehicle::GetLightsState()
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		return (int)pVehicle->m_byteLightState;

	return 0;
}

void CIVVehicle::RemoveVehicleWindow(CIVScript::eVehicleWindow window)
{
	IVVehicle *pVehicle = GetVehicle();
	if(pVehicle)
	{
		_asm	push window;
		_asm	mov ecx, pVehicle;
		_asm	call COffsets::FUNC_CVehicle__RemoveVehicleWindow;
	}
}

bool CIVVehicle::IsCarInWater()
{
	IVVehicle *pVehicle = GetVehicle();

	bool bInWater = false;
	if(pVehicle)
	{
		if( *(int *)(pVehicle + 0x1354) == 2 )
			bInWater = *(BYTE *)(pVehicle + 0x1360) & 1;   
		else 
		{
			if((*(BYTE *)(pVehicle + 0x118) & 1) || ((*(DWORD *)(pVehicle + 0x6C) != NULL) && *(BYTE *)(pVehicle + 0x141)))
				bInWater = true;
		}
	}
	return  bInWater;
}

void CIVVehicle::SetCarCanBurstTyres(bool bState)
{
	IVVehicle *pVehicle = GetVehicle();
	if(pVehicle)
	{
		if(bState)
			*(BYTE *)(pVehicle + 0xF67) &= 0xEFu;
		else
			*(BYTE *)(pVehicle + 0xF67) |= 0x10u;
	}
}

bool CIVVehicle::GetCarCanBurstTyres()
{
	IVVehicle *pVehicle = GetVehicle();
	if(pVehicle)
		return ((*(BYTE *)(pVehicle + 0xF67) & 0xEFu) != NULL);

	return false;
}

void CIVVehicle::SetHeadlights(bool bSwitch)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		bSwitch ? SET_BIT(pVehicle->m_byteFlags6, 2) : UNSET_BIT(pVehicle->m_byteFlags6, 2);
}

bool CIVVehicle::GetHeadlights()
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		return IS_BIT_SET(pVehicle->m_byteFlags6, 2);

	return 0;
}

void CIVVehicle::SetRadioStation(BYTE byteRadioStation)
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		pVehicle->m_byteRadioStation = byteRadioStation;
}

BYTE CIVVehicle::GetRadioStation()
{
	IVVehicle * pVehicle = GetVehicle();
	if(pVehicle)
		return pVehicle->m_byteRadioStation;

	return 0;
}