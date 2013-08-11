//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CIVPed.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVPed_h
#define CIVPed_h

#include <Common.h>
#include <Math/CMaths.h>
#include <IV/IVCommon.h>
#include <Game/eGame.h>
#include "CIVPhysical.h"
#include "CIVEntity.h"
#include "CIVPedTaskManager.h"

enum ePedType
{
	PED_TYPE_PLAYER,
	PED_TYPE_CIVMALE,
	PED_TYPE_CIVFEMALE,
	PED_TYPE_COP,
	PED_TYPE_GANG_ALBANIAN,
	PED_TYPE_GANG_BIKER_1,
	PED_TYPE_GANG_BIKER_2,
	PED_TYPE_GANG_ITALIAN,
	PED_TYPE_GANG_RUSSIAN,
	PED_TYPE_GANG_RUSSIAN_2,
	PED_TYPE_GANG_IRISH,
	PED_TYPE_GANG_JAMAICAN,
	PED_TYPE_GANG_AFRICAN_AMERICAN,
	PED_TYPE_GANG_KOREAN,
	PED_TYPE_GANG_CHINESE_JAPANESE,
	PED_TYPE_GANG_PUERTO_RICAN,
	PED_TYPE_DEALER,
	PED_TYPE_MEDIC,
	PED_TYPE_FIREMAN,
	PED_TYPE_CRIMINAL,
	PED_TYPE_BUM,
	PED_TYPE_PROSTITUTE,
	PED_TYPE_SPECIAL
};

class IVPlayerInfo;
class IVVehicle;

class IVEventHandler
{
	PAD(IVEventHandler, pad0, 0x40); // 00-40
};

class IVEventScanner
{
	PAD(IVEventHandler, pad0, 0x130); // 000-130
};


class CIVPedTaskManager;
class IVPedTaskManager;
class IVTask;

class IVPedIntelligence {
public:
	PAD(IVPedIntelligence, pad0, 0x40);   // 000-044
	IVPedTaskManager m_pedTaskManager;    // 044-084
	// 0x84 = CEventGroup m_eventGroup; (size is 0x48 or 0x4C) (4C probs extra CEventGlobalGroup member)
	// 0xF0 = BYTE m_byteEventId;
	// 0xF1 = BYTE m_byteEventPriority;
	// 0xF4 = CVehicleScanner m_vehicleScanner; (CEntityScanner (Size 0x5C))
	// 0x150 = CPedScanner m_pedScanner;
	// 0x1AC = CObjectScanner m_objectScanner;
	PAD(IVPedIntelligence, pad1, 0x26C);  // 084-2F0

	virtual ~IVPedIntelligence();
	virtual IVEventHandler*	GetEventScanner();
	virtual IVEventHandler*	GetEventScanner0();
	virtual IVTask*			CreateMedicTask(int a1); 
	virtual IVTask*			CreateMedicTaskDrive(int a1); 
	virtual IVTask*			Function5(int a1);
	virtual bool			Function6(int a1, int a2);
	virtual IVEventHandler*	GetEventHandler();
	virtual IVEventHandler*	GetEventHandler0();
};

class IVPedIntelligenceNY : public IVPedIntelligence {
public:
	IVEventHandler m_eventHandler; // 2F0-330 (CEventHandlerNY)
	IVEventScanner m_eventScanner; // 330-460 (CEventScannerNY)

	virtual ~IVPedIntelligenceNY();
};

class IVPedBase {
public:
	PAD(IVPedBase, pad0, 0x12C);
	ePedType m_type;
};

#pragma pack(1)
class IVPed : public IVPhysical {
public:
	PAD(IVPed, pad0, 0x8);
	BYTE m_bytePlayerNumber;
	BYTE m_byteIsPlayerPed;
	PAD(IVPed, pad1, 0x2);
	IVPedBase * m_pPedBase;
	PAD(IVPed, pad2, 0x4);
	IVPedIntelligence * m_pPedIntelligence;
	IVPlayerInfo * m_pPlayerInfo;
	DWORD m_pPedData;
	PAD(IVPed, pad3, 0x3C);
	BYTE m_byteUnknown;
	PAD(IVPed, pad4, 0x43);
	PAD(IVPed, pad19, 0x11A); //todo: IVPedWeapons m_weapons;
	PAD(IVPed, pad5, 0x1B6);
	void * m_pPedAudio;
	PAD(IVPed, pad6, 0x98);
	DWORD m_dwVoiceHash;
	PAD(IVPed, pad7, 0x1A8);
	DWORD m_dwRagdollStatus;
	DWORD m_dwRagdollTime;
	PAD(IVPed, pad8, 0x21);
	BYTE m_byteWeaponObjectVisible;
	PAD(IVPed, pad9, 0x8);
	IVEntity * m_pTargetVehicle;
	PAD(IVPed, pad10, 0x272);
	BYTE m_byteCreatedBy;
	PAD(IVPed, pad11, 0xF);
	DWORD m_dwArrestState;
	DWORD m_dwDeathState;
	PAD(IVPed, pad12, 0x8);
	DWORD m_pPedMoveBlendOnFoot;
	float m_fMaxHealth;
	PAD(IVPed, pad13, 0x18);
	float m_fCurrentHeading;
	float m_fDesiredHeading;
	PAD(IVPed, pad14, 0x88);
	IVVehicle * m_pCurrentVehicle;
	PAD(IVPed, pad15, 0x7C);
	void * m_pPedIKManager;
	PAD(IVPed, pad16, 0x17C);
	BYTE m_byteRingState;
	PAD(IVPed, pad17, 0x17);
	float m_fHeadingLimit[2];
	PAD(IVPed, pad18, 0x1A0);
};
#pragma pack()

class CIVPed : public CIVPhysical {
private:
	CIVPedTaskManager	* m_pPedTaskManager;
	
public:
	CIVPed();
	CIVPed(IVPed * pPed);
	~CIVPed();

	void				SetPed(IVPed * pPed);
	IVPed				* GetPed();

	void				SetPlayerInfo(IVPlayerInfo * pPlayerInfo);
	IVPlayerInfo		* GetPlayerInfo();

	CIVPedTaskManager	* GetPedTaskManager() { return m_pPedTaskManager; }

	void				SetCurrentHeading(float m_fCurrentHeading);
	float				GetCurrentHeading();

	void				SetDucking(bool bDucking);
	bool				IsDucking();

	bool				IsInVehicle();

	void				SetCurrentVehicle(IVVehicle * pVehicle);
	IVVehicle			* GetCurrentVehicle();
};

#endif // CIVPed_h