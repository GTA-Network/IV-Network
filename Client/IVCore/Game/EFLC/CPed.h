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

#ifndef CPed_h
#define CPed_h

#include <Common.h>
#include "../GameCommon.h"

#include "CPhysical.h"
#include "CPedTaskManager.h"
#include "CPedWeapons.h"
#include "TaskInfo/CTaskInfo.h"

_GAME_BEGIN

enum ePedType
{
	PED_TYPE_PLAYER,
	PED_TYPE_CMALE,
	PED_TYPE_CFEMALE,
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

class IEntityScanner
{
public:
	virtual ~IEntityScanner();
	PAD(IEntityScanner, pad1, 0x58); // 04-5C
};

class IVehicleScanner : public IEntityScanner
{ };

class IPedScanner : public IEntityScanner
{ };

class IObjectScanner : public IEntityScanner
{ };

class IEventGroup
{
public:
	virtual ~IEventGroup();
	PAD(IVEventGroup, pad1, 0x48);
};

class IEventHandler
{
public:
	PAD(IVEventHandler, pad0, 0x40); // 00-40
};

class IEventScanner
{
public:
	PAD(IVEventHandler, pad0, 0x130); // 000-130
};


class IPedIntelligence
{
public:
	PAD(IPedIntelligence, pad1, 0x40);               // 04 - 44
	IPedTaskManager         m_pedTaskManager;        // 44 - 84
	IEventGroup             m_EventGroup;            // 84 - D0
	PAD(IPedIntelligence, pad2, 0x24);              // D0 - F4
	IVehicleScanner         m_VehicleScanner;        // F4 -150
	IPedScanner             m_PedScanner;            // 150-1AC
	IObjectScanner          m_ObjectScanner;         // 1AC-208
	PAD(IPedIntelligence, pad3, 0xD8);
	ITaskInfo               *m_pTaskInfo;
	ITaskInfo               *m_pAmbientsInfo;
	DWORD                   unkPtr3;
	DWORD                   unkPtr4;

	virtual ~IPedIntelligence();
	virtual IEventHandler*        GetEventScanner();
	virtual IEventHandler*        GetEventScanner0();
	virtual ITask*                CreateMedicTask(int a1);
	virtual ITask*                CreateMedicTaskDrive(int a1);
	virtual ITask*                Function5(int a1);
	virtual bool                  Function6(int a1, int a2);
	virtual IEventHandler*        GetEventHandler();
	virtual IEventHandler*        GetEventHandler0();
}; // size = 0x460

class IPedIntelligenceNY : public IPedIntelligence
{
public:
	IEventHandler                 m_eventHandler;                // 2F0-330
	IEventScanner                m_eventScanner;                // 330-460

	virtual ~IPedIntelligenceNY();
};

class IPedBase
{
public:
	PAD(IPedBase, pad0, 0x5C);
	BYTE                m_bDrawableVariations[10];
	PAD(IPedBase, pad1, 0xC6);
	ePedType m_type;
};

class IPed;
class IPedData
{
public:
	DWORD dword4;
	PAD(IPedData, pad0, 0x58); // 04-60

	virtual					~IPedData();
	virtual void            Function1();
	virtual void            Function2();
	virtual ITask*         CreateWanderTask(IPed* pPed);
	virtual ITask*         CreateDriveTask(IPed *pPed, int a2, int a3);
	virtual ITask*         CreateTaskForCurrentState(IPed* pPed);
};

class IPedMoveBlendOnFoot;
class IPlayerInfo;
class IVehicle;

#pragma pack(push, 1)
class IPed : public IPhysical
{
public:
	PAD(IPed, pad0, 0x8);                  // 210-218
	BYTE m_bytePlayerNumber;                // 218-219
	BYTE m_byteIsPlayerPed;                 // 219-21A
	PAD(IPed, pad1, 0x2);                  // 210-21C
	IPedBase * m_pPedBase;                 // 21C-220
	PAD(IPed, pad2, 0x4);                  // 220-224
	IPedIntelligenceNY* m_pPedIntelligence;// 224-228 (Should be IPedIntelligenceNY)
	IPlayerInfo * m_pPlayerInfo;           // 228-22C
	IPedData * m_pPedData;                 // 22C-230
	PAD(IPed, pad3, 0x3C);                 // 230-26C
	BYTE m_byteUnknown;                     // 26C-26D - Bits 4: in vehicle
	PAD(IPed, pad4, 0x43);                 // 26D-2B0
	IPedWeapons m_weapons;                 // 2B0-3CA
	// 0x3A8 - IEntity * pTargetEntity;
	// 0x3D0 - audPedAudioEntity
	// 0x580 - audSpeechAudioEntity
	// 0x790 - audPlaceableTracker
	PAD(IPed, pad5, 0x1B6);                // 3CA-580
	void * m_pPedAudio;                     // 580-584 // (CPedAudio (audSpeechAudioEntity))
	PAD(IPed, pad6, 0x98);                 // 584-61C
	DWORD m_dwVoiceHash;                    // 61C-620
	PAD(IPed, pad7, 0x1A8);                // 620-7C8
	// 0x780 - BYTE m_byteIsDrunk; (Possibly m_byteVoiceIsDrunk)
	DWORD m_dwRagdollStatus;                // 7C8-7CC
	DWORD m_dwRagdollTime;                  // 7CC-7D0
	PAD(IPed, pad8, 0x21);                 // 7D0-7F1
	BYTE m_byteWeaponObjectVisible;         // 7F1-7F2
	PAD(IPed, pad9, 0x8);                  // 7F2-7FA
	IEntity * m_pTargetVehicle;            // 7FA-7FE
	PAD(IPed, pad10, 0x272);               // 3CA-A70
	BYTE m_byteCreatedBy;                   // A70-A71 - See eCharCreator
	PAD(IPed, pad11, 0xF);                 // A71-A80
	DWORD m_dwArrestState;                  // A80-A84
	DWORD m_dwDeathState;                   // A84-A88
	PAD(IPed, pad12, 0x8);                 // A88-A90
	IPedMoveBlendOnFoot* m_pPedMoveBlendOnFoot;            // A90-A94
	float m_fMaxHealth;                     // A94-A98
	PAD(IPed, pad13, 0x18);                // A98-AB0
	float m_fCurrentHeading;                // AB0-AB4
	float m_fDesiredHeading;                // AB4-AB8
	PAD(IPed, pad14, 0x88);                // AB8-B40
	IVehicle * m_pCurrentVehicle;          // B40-B44
	PAD(IPed, pad15, 0x7C);                // B44-BC0
	void * m_pPedIKManager;                 // BC0-BC4 // +0x40 = pPed (CIKManager)
	PAD(IPed, pad16, 0x17C);               // BC4-D40
	BYTE m_byteRingState;                   // D40-D41
	PAD(IPed, pad17, 0x17);                // D41-D58
	float m_fHeadingLimit[2];               // D58-D60
	PAD(IPed, pad18, 0x1A0);               // BC4-F00

	virtual					~IPed();
	virtual void            Function72(); // something with death and maybe respawn
	virtual void            Function73(); // something with player info
	virtual void            Function74(); // return 0;
	virtual int             Function75(); // return dword_12308B0;
	virtual int             Function76(); // return dword_F21F10;
	virtual int             Function77(); // return dword_F21F20;
	virtual void            Function78(); // nullsub
	virtual void            Function79(); // nullsub
	virtual void            Function80(); // nullsub

};
#pragma pack(pop)

class CPed : public CPhysical
{
private:
	CPedTaskManager	* m_pPedTaskManager;
	CPedWeapons		* m_pPedWeapons;

public:
	CPed();
	CPed(IPed * pPed);
	~CPed();

	void                SetPed(IPed * pPed);
	IPed               * GetPed();

	void                SetPlayerInfo(IPlayerInfo * pPlayerInfo);
	IPlayerInfo        * GetPlayerInfo();

	CPedTaskManager   * GetPedTaskManager() { return m_pPedTaskManager; }
	CPedWeapons       * GetPedWeapons() { return m_pPedWeapons; }

	void                SetCurrentHeading(float m_fCurrentHeading);
	float               GetCurrentHeading();

	void                SetDucking(bool bDucking);
	bool                IsDucking();

	bool                IsInVehicle();

	void                SetCurrentVehicle(IVehicle * pVehicle);
	IVehicle           * GetCurrentVehicle();

	unsigned int        GetNumberOfCharDrawableVariations(unsigned int ucBodyLocation);
	unsigned int        GetNumberOfCharTextureVariations(unsigned int ucBodyLocation, unsigned int uiPart);
	void                SetClothes(unsigned int ucBodyLocation, unsigned int uiVariation, unsigned int uiTexture);

};

template <class T>
class CPool;
typedef CPool<IPed> CPedPool;

_GAME_END

#endif // CPed_h
