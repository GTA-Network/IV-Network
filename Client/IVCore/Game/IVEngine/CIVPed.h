//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
#include "CIVPedWeapons.h"

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
	PAD(IVPedBase, pad0, 0x5C);
	BYTE		m_bDrawableVariations[10];
	PAD(IVPedBase, pad1, 0xC6);
	ePedType m_type;
};


class IVPedData
{
public:
	DWORD dword4;
	PAD(IVPedData, pad0, 0x58); // 04-60

	virtual					~IVPedData();
	virtual void            Function1();
	virtual void            Function2();
	virtual IVTask*         CreateWanderTask(IVPed* pPed);
	virtual IVTask*         CreateDriveTask(IVPed *pPed, int a2, int a3);
	virtual IVTask*         CreateTaskForCurrentState(IVPed* pPed);
};

class IVPedMoveBlendOnFoot;

class IVPed : public IVPhysical {
public:
	PAD(IVPed, pad0, 0x8);                  // 210-218
	BYTE m_bytePlayerNumber;                // 218-219
	BYTE m_byteIsPlayerPed;                 // 219-21A
	PAD(IVPed, pad1, 0x2);                  // 210-21C
	IVPedBase * m_pPedBase;                 // 21C-220
	PAD(IVPed, pad2, 0x4);                  // 220-224
	IVPedIntelligenceNY* m_pPedIntelligence;// 224-228 (Should be IVPedIntelligenceNY)
	IVPlayerInfo * m_pPlayerInfo;           // 228-22C
	IVPedData * m_pPedData;                 // 22C-230
	PAD(IVPed, pad3, 0x3C);                 // 230-26C
	BYTE m_byteUnknown;                     // 26C-26D - Bits 4: in vehicle
	PAD(IVPed, pad4, 0x43);                 // 26D-2B0
	IVPedWeapons m_weapons;                 // 2B0-3CA
	// 0x3A8 - IVEntity * pTargetEntity;
	// 0x3D0 - audPedAudioEntity
	// 0x580 - audSpeechAudioEntity
	// 0x790 - audPlaceableTracker
	PAD(IVPed, pad5, 0x1B6);                // 3CA-580
	void * m_pPedAudio;                     // 580-584 // (CPedAudio (audSpeechAudioEntity))
	PAD(IVPed, pad6, 0x98);                 // 584-61C
	DWORD m_dwVoiceHash;                    // 61C-620
	PAD(IVPed, pad7, 0x1A8);                // 620-7C8
	// 0x780 - BYTE m_byteIsDrunk; (Possibly m_byteVoiceIsDrunk)
	DWORD m_dwRagdollStatus;                // 7C8-7CC
	DWORD m_dwRagdollTime;                  // 7CC-7D0
	PAD(IVPed, pad8, 0x21);                 // 7D0-7F1
	BYTE m_byteWeaponObjectVisible;         // 7F1-7F2
	PAD(IVPed, pad9, 0x8);                  // 7F2-7FA
	IVEntity * m_pTargetVehicle;            // 7FA-7FE
	PAD(IVPed, pad10, 0x272);               // 3CA-A70
	BYTE m_byteCreatedBy;                   // A70-A71 - See eCharCreator
	PAD(IVPed, pad11, 0xF);                 // A71-A80
	DWORD m_dwArrestState;                  // A80-A84
	DWORD m_dwDeathState;                   // A84-A88
	PAD(IVPed, pad12, 0x8);                 // A88-A90
	IVPedMoveBlendOnFoot* m_pPedMoveBlendOnFoot;            // A90-A94
	float m_fMaxHealth;                     // A94-A98
	PAD(IVPed, pad13, 0x18);                // A98-AB0
	float m_fCurrentHeading;                // AB0-AB4
	float m_fDesiredHeading;                // AB4-AB8
	PAD(IVPed, pad14, 0x88);                // AB8-B40
	IVVehicle * m_pCurrentVehicle;          // B40-B44
	PAD(IVPed, pad15, 0x7C);                // B44-BC0
	void * m_pPedIKManager;                 // BC0-BC4 // +0x40 = pPed (CIKManager)
	PAD(IVPed, pad16, 0x17C);               // BC4-D40
	BYTE m_byteRingState;                   // D40-D41
	PAD(IVPed, pad17, 0x17);                // D41-D58
	float m_fHeadingLimit[2];               // D58-D60
	PAD(IVPed, pad18, 0x1A0);               // BC4-F00

	virtual					~IVPed();
	virtual void			Function72(); // something with death and maybe respawn
	virtual void			Function73(); // something with player info
	virtual void			Function74(); // return 0;
	virtual int				Function75(); // return dword_12308B0;
	virtual int				Function76(); // return dword_F21F10;
	virtual int				Function77(); // return dword_F21F20;
	virtual void			Function78(); // nullsub
	virtual void			Function79(); // nullsub
	virtual void			Function80(); // nullsub

};

class CIVPed : public CIVPhysical {
private:
	CIVPedTaskManager	* m_pPedTaskManager;
	CIVPedWeapons		* m_pPedWeapons;
	
public:
	CIVPed();
	CIVPed(IVPed * pPed);
	~CIVPed();

	void				SetPed(IVPed * pPed);
	IVPed				* GetPed();

	void				SetPlayerInfo(IVPlayerInfo * pPlayerInfo);
	IVPlayerInfo		* GetPlayerInfo();

	CIVPedTaskManager	* GetPedTaskManager() { return m_pPedTaskManager; }
	CIVPedWeapons		* GetPedWeapons() { return m_pPedWeapons; }

	void				SetCurrentHeading(float m_fCurrentHeading);
	float				GetCurrentHeading();

	void				SetDucking(bool bDucking);
	bool				IsDucking();

	bool				IsInVehicle();

	void				SetCurrentVehicle(IVVehicle * pVehicle);
	IVVehicle			* GetCurrentVehicle();

	unsigned int		GetNumberOfCharDrawableVariations(unsigned int ucBodyLocation);
	unsigned int		GetNumberOfCharTextureVariations(unsigned int ucBodyLocation, unsigned int uiPart);
	void				SetClothes(unsigned int ucBodyLocation, unsigned int uiVariation, unsigned int uiTexture);

};

#endif // CIVPed_h