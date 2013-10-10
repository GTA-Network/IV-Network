//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CHooks.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "CHooks.h"
#include "COffsets.h"
#include <CCore.h>
#include <Patcher/CPatcher.h>
#include <Game/IVEngine/CIVPlayerInfo.h>
#include "CContextData.h"
#include <SharedUtility.h>
#include "CGameFuncs.h"
#include <IV/CIVScript_FunctionInvoke.h>
#include <IV/CIVScriptEnums.h>
#include <IV/CIVScript_FunctionList.h>

class CHookDummy
{
public:
	void __thiscall registerEpisodes();
	char __thiscall loadEpisodes(int id);
};

extern	CCore* g_pCore;

IVTask       * ___pTask = NULL;
_declspec(naked) void CTask__Destructor_Hook()
{
	_asm	mov ___pTask, ecx;
	_asm	pushad;

	if (g_pCore->GetGame()->GetTaskManager())
		g_pCore->GetGame()->GetTaskManager()->HandleTaskDelete(___pTask);

	_asm	popad;
	_asm	push esi;
	_asm	mov esi, ecx;
	_asm	push esi;
	_asm	push eax;
	_asm	mov eax, COffsets::VAR_CTask__VFTable;
	_asm	mov dword ptr[esi], eax;
	_asm	pop eax;
	_asm	jmp COffsets::RETURN_CTask__Destructor;
}

void StartGame_Loading()
{
	int * v7 = new int(0);
	_asm
	{
		push v7
		mov ecx, COffsets::IV_Hook__StartGameLoading_1
		call COffsets::IV_Hook__StartGameLoading_2
	}
	*(DWORD*) COffsets::IV_Hook__StartGameLoading_3 = *v7;
	*(DWORD*) COffsets::IV_Hook__StartGameLoading_4 = *v7;
	if (*v7 > 0)
		_asm call COffsets::IV_Hook__StartGameLoading_5;
}

void RemoveLoadingScreens()
{
	StartGame_Loading();

	int iLoadScreens = COffsets::VAR_NumLoadingScreens;
	int iLoadScreenType = COffsets::VAR_FirstLoadingScreenType;
	int iLoadScreenDuration = COffsets::VAR_FirstLoadingScreenDuration;

	for (int i = 0; i < *(int *) iLoadScreens; ++i)
	{
		*(DWORD *) (iLoadScreenType + i * 400) = 0;
		*(DWORD *) (iLoadScreenDuration + i * 400) = 0;
	}
}

IVPlayerInfo * pReturnedPlayerInfo = NULL;
IVPlayerInfo * GetPlayerInfoFromIndex(unsigned int uiIndex)
{
	pReturnedPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0);

	if (uiIndex != 0)
	{
		CContextData * pContextInfo = CContextDataManager::GetContextData(uiIndex);

		if (pContextInfo)
			pReturnedPlayerInfo = pContextInfo->GetPlayerInfo()->GetPlayerInfo();
	}

	return pReturnedPlayerInfo;
}

unsigned int   uiReturnedIndex = 0;
unsigned int GetIndexFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	uiReturnedIndex = 0;

	if (pPlayerInfo != g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0))
	{
		CContextData * pContextInfo = CContextDataManager::GetContextData(pPlayerInfo);

		if (pContextInfo)
			uiReturnedIndex = pContextInfo->GetPlayerInfo()->GetPlayerNumber();
	}

	return uiReturnedIndex;
}

IVPlayerPed  * _pPlayerPed = NULL;
IVPlayerPed * GetLocalPlayerPed()
{
	// Default to the local player ped (If available)
	IVPlayerInfo * pPlayerInfo = g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(0);

	if (pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else
		_pPlayerPed = NULL;

	// Is the local player id valid?
	if (g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex() != -1)
	{
		// Is the player index not the local player?
		if (g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex() != 0)
		{
			// Get the context info for the player index
			CContextData * pContextInfo = CContextDataManager::GetContextData((BYTE) g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex());

			// Is the context info valid?
			if (pContextInfo)
			{
				// Set the player ped to the remote player
				_pPlayerPed = pContextInfo->GetPlayerPed()->GetPlayerPed();
			}
		}
	}

	return _pPlayerPed;
}

IVPlayerPed * GetPlayerPedFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
	// Is the player info pointer valid?
	if (pPlayerInfo)
		_pPlayerPed = pPlayerInfo->m_pPlayerPed;
	else // Player info pointer is invalid, use the local player ped
		_pPlayerPed = GetLocalPlayerPed();

	return _pPlayerPed;
}


unsigned int   uiPlayerInfoIndex = 0;
_declspec(naked) void GetPlayerInfoFromIndex_Hook()
{
	_asm	mov eax, [esp + 4];
	_asm	mov uiPlayerInfoIndex, eax;
	_asm	pushad;

	GetPlayerInfoFromIndex(uiPlayerInfoIndex);

	_asm	popad;
	_asm	mov eax, pReturnedPlayerInfo;
	_asm	retn;
}

_declspec(naked) void GetIndexFromPlayerInfo_Hook()
{
	_asm	mov eax, [esp + 4];
	_asm	mov pReturnedPlayerInfo, eax;
	_asm	pushad;

	GetIndexFromPlayerInfo(pReturnedPlayerInfo);

	_asm	popad;
	_asm	mov eax, uiReturnedIndex;
	_asm	retn;
}

_declspec(naked) void GetLocalPlayerPed_Hook()
{
	_asm	pushad;

	GetLocalPlayerPed();

	_asm	popad;
	_asm	mov eax, _pPlayerPed;
	_asm	retn;
}

_declspec(naked) void GetPlayerPedFromPlayerInfo_Hook()
{
	_asm	mov eax, [esp + 4];
	_asm	mov pReturnedPlayerInfo, eax;
	_asm	pushad;

	GetPlayerPedFromPlayerInfo(pReturnedPlayerInfo);

	_asm	popad;
	_asm	mov eax, _pPlayerPed;
	_asm	retn;
}

_declspec(naked) void CFunctionRetnPatch()
{
	_asm
	{
		xor eax, eax
			retn
	}
}

bool			bInitialiseGame = true;
int				iFrameCalls = 0;
_declspec(naked) void CGameProcessHook()
{
	if (!bInitialiseGame && iFrameCalls != 300)
	{
		iFrameCalls++;
		_asm	mov ebp, esp;
		_asm	jmp COffsets::IV_Hook__GameProcess_1;
	}
	else
	{
		iFrameCalls++;
		bInitialiseGame = false;

		// Don't process game this time, just start it(works ram usage increases up to ~1,2GB)
		_asm	mov ebp, esp;
		_asm	jmp COffsets::IV_Hook__GameProcess_2;

		*(BYTE*) COffsets::IV_Hook__GameProcess_3 = 0;
		*(BYTE*) COffsets::IV_Hook__GameProcess_4 = 1;
		*(BYTE*) COffsets::IV_Hook__GameProcess_5 = 0;

		*(DWORD*) (g_pCore->GetBase() + 0x10C7854) = 50;


		DWORD keks = *(DWORD *) COffsets::IV_Hook__GameProcess_6; // keks copyright by xforce
		DWORD g_rgsc = *(DWORD *) COffsets::IV_Hook__GameProcess_7;
		int iTime = timeGetTime();

		_asm	push 0;
		_asm	push 1;
		_asm	push 0;
		_asm	mov eax, keks;
		_asm	mov ecx, g_rgsc;
		_asm	mov edi, iTime;
		_asm	call COffsets::IV_Hook__GameProcess_8;
		_asm	add esp, 0Ch;
	}
}

#ifdef GTAV_MAP
Vector2 * v12;
Vector2 * pViewportSize = new Vector2();
float center;
int bAbsolut;

#define MIN_X 0.025f
#define MAX_X 0.975f
#define MIN_Y 0.025f
#define MAX_Y 0.975f
#define ZERO 0.0f
float fOriginalX;
float fOriginalY;

void _declspec(naked) Keks()
{
	_asm	mov v12, edx;
	_asm	push eax; get absolute flag
	_asm	mov eax, [ebp + 14h]; 3th parameter
	_asm	mov bAbsolut, eax;
	_asm	pop eax;

	fOriginalX = v12->fX;
	fOriginalY = v12->fY;

	// Calculate and check our coordinates 
	if (!bAbsolut) {

		if (v12->fX < MAX_X && v12->fX > MIN_X) { // Check if the X axis is smaller than 1, but still positive
			if (v12->fY < MAX_Y && v12->fY > MIN_Y) // Check if the Y Acis is smaller than 1, but still positive
			{
				goto out; // Let GTA calc the position on itself
			}
			else {
				if (v12->fY > MAX_Y) // Check if the Y Axis is bigger than 1 (set it -0.05 so it's not cutted of)
					v12->fY = MAX_Y;

				if (v12->fY < MIN_Y) // Check if the Y Axis is smaller than 0 (set it +0.05 so it's not cutted of)
					v12->fY = MIN_Y;
			}

			goto out;
		}
		else
		{
			if (v12->fX > MAX_X)
				v12->fX = MAX_X; // Check if the X Axis is bigger than 1 (set it -0.05 so it's not cutted of)

			if (v12->fX < MIN_X)
				v12->fX = MIN_X; // Check if the X Axis is smaller than 0 (set it +0.05 so it's not cutted of)
		}

		if (v12->fY < MAX_Y && v12->fY > MIN_Y) { // Check if the Y Acis is smaller than 1, but still positive
			if (v12->fX < MAX_X && v12->fX > MIN_X)// Check if the X axis is smaller than 1, but still positive
			{
				goto out;
			}
			else
			{
				if (v12->fX > MAX_X) // Check if the X Axis is bigger than 1 (set it -0.05 so it's not cutted of)
					v12->fX = MAX_X;

				if (v12->fX < 0) // Check if the X Axis is smaller than 0 (set it +0.05 so it's not cutted of)
					v12->fX = MIN_X;
			}

			goto out;
		}
		else {
			if (v12->fY > MAX_Y) // Check if the Y Axis is bigger than 1 (set it -0.05 so it's not cutted of)
				v12->fY = MAX_Y;

			if (v12->fY < MIN_Y) // Check if the Y Axis is smaller than 0 (set it +0.05 so it's not cutted of)
				v12->fY = MIN_Y;
		}
		goto out;
	}

out:

	_asm    mov esp, ebp;
	_asm    pop ebp;
	_asm    retn;
}

DWORD ResizeMapJmpBack;
int a1, a2, a3;

_declspec(naked) signed int ResizeMap()
{
	_asm push eax;
	_asm mov eax, [ebp + 4];
	_asm mov a1, eax;
	_asm mov eax, [ebp + 8];
	_asm mov a2, eax;
	_asm mov eax, [ebp + 0Ch];
	_asm mov a3, eax;
	_asm pushad;

	ResizeMapJmpBack = (g_pCore->GetBase() + 0x8364D7);

	_asm popad;
	_asm pop eax;
	_asm jmp ResizeMapJmpBack;
}

DWORD sub_849BC0;
_declspec(naked) void RenderMap()
{
	sub_849BC0 = (g_pCore->GetBase() + 0x849BC0);
	_asm	call sub_849BC0;
	_asm	add esp, 4;
	_asm	popad;

	//g_pCore->GetGame()->SetRadarVisible(true);

	_asm	pushad;
	_asm	retn;
}
#endif

int * physics = 0;
IVVehicle * pVehicle = 0;
DWORD sub_44A690 = 0;

// Vehicle + 0xE14 == fragInstGta*
struct fragInstGta
{
	DWORD vtable;
	DWORD dw1;
	WORD w1;
	WORD w2;
	IVEntity *	pEntity;
	Matrix34 m_Matrix; // 16-72
	char pad1[8]; // 72-80
	DWORD vtable_destruct; // 80-84
	char pad2[44]; // 84-128
	Vector3 m_vecPos; // 128-140
	char pad3[20]; // 140-160
	DWORD unkSize; // A0-A4
	DWORD unk; // A4-A8;
}; // size = 0xB0 [176]

// Vehicle + 0x1480 == phInstGta*
struct phInstGta
{
	DWORD vtable;
	DWORD dw1;
	WORD w1;
	WORD w2;
	IVEntity *	pEntity;
	Matrix34	m_Matrix;
	char pad2[4];
	int	iUnk;
}; // size = 0x60 [96]

void _declspec(naked) PhysicsHook()
{
	_asm
	{
		mov physics, ecx
		mov pVehicle, esi
		pushad
	}

	if (*(int*) pVehicle == g_pCore->GetBase() + 0xD9ED74) // IsBike
	{
		//_asm { int 3 }
		//CLogFile::Printf("%p", physics);
	}

	sub_44A690 = g_pCore->GetBase() + 0x44A690;
	if (*(DWORD *) (physics + 4) == 0)
	{
		CLogFile::Printf("Fail 0x%p", physics);

		if (pVehicle->GetfragInst())
		{
			if (*(DWORD*) (pVehicle->GetfragInst() + 0x64))
				CLogFile::Printf("0x%p", *(DWORD*) ((*(DWORD*) (pVehicle->GetfragInst() + 0x64)) + 0x160));
			else
			{
				int v2 = (*(int(__thiscall **)(DWORD))(*(DWORD *) pVehicle + 0xA0))((DWORD) pVehicle);
				CLogFile::Printf("0x%p", (*(int(__thiscall **)(DWORD))(*(DWORD *) v2 + 0xE0))(v2));
			}
		}

		g_pCore->GetGame()->GetStreaming()->RequestResource(eResourceType::RESOURCE_TYPE_WDR, pVehicle->m_wModelIndex);
		while (!g_pCore->GetGame()->GetStreaming()->HasResourceLoaded(eResourceType::RESOURCE_TYPE_WDR, pVehicle->m_wModelIndex))
		{
			g_pCore->GetGame()->GetStreaming()->LoadAllResources();
			Sleep(10);
		}

		CLogFile::Printf("Model: %i", pVehicle->m_wModelIndex);

		CLogFile::Printf("PhysicsBefore=>");
		CLogFile::Printf("[0x38] 0x%p || [0xE14] 0x%p || [0x100] 0x%p", pVehicle->m_pPhysics, pVehicle->m_pVehiclePhysics, *(DWORD*) (pVehicle + 0x40));
		CLogFile::Printf("<=");
		pVehicle->CreatePhysics();
		CLogFile::Printf("PhysicsAfter=>");
		CLogFile::Printf("[0x38] 0x%p || [0xE14] 0x%p || [0x100] 0x%p", pVehicle->m_pPhysics, pVehicle->m_pVehiclePhysics, *(DWORD*) (pVehicle + 0x40));
		CLogFile::Printf("<=");

		if (pVehicle->GetfragInst())
		{
			if (*(DWORD*) (pVehicle->GetfragInst() + 0x64))
				CLogFile::Printf("0x%p", *(DWORD*) ((*(DWORD*) (pVehicle->GetfragInst() + 0x64)) + 0x160));
			else
			{
				int v2 = (*(int(__thiscall **)(DWORD))(*(DWORD *) pVehicle + 0xA0))((DWORD) pVehicle);
				CLogFile::Printf("0x%p", (*(int(__thiscall **)(DWORD))(*(DWORD *) v2 + 0xE0))(v2));
			}
		}
		_asm popad;
		_asm retn;
	}
	else
	{
		_asm popad;
		_asm call sub_44A690;
		_asm retn;
	}


	_asm
	{
		_asm popad;
		_asm retn;
	}
}

_declspec(naked) void CTaskSimpleStartVehicle__Process()
{
	_asm xor eax, eax;
	_asm retn 4;
}

#define GTA_malloc (*(char *(__cdecl *)(int)) (g_pCore->GetBase() + 0x4011D0))
#define getGameFolderFromRegistry (*(bool(__stdcall *)(char *)) (g_pCore->GetBase() + 0x8B3260))
#define GTA_memcpy (*(int(__cdecl *)(char *, char *, int)) (g_pCore->GetBase() + 0xD0BC80))
#define GTA_strcat (*(int(__cdecl *)(char*, char*, int)) (g_pCore->GetBase() + 0xD0C2B0))
#define SetGTAWorkdir (*(int(__thiscall *)(void *, char *)) (g_pCore->GetBase() + 0x45AEF0))
#define GTAWorkdirUknownPVOID (void *) (g_pCore->GetBase() + 0x1003C10)
#define IsFileExistInWorkdir (*(bool(__thiscall *)(void *, char *, int)) (g_pCore->GetBase() + 0x45B070))
#define WorkdirUnknownFunc (*(void(__thiscall *)(void *)) (g_pCore->GetBase() + 0x45AFB0))
#define UnknownFuncWhitGameDir (*(int(__cdecl *)(char *)) (g_pCore->GetBase() + 0x401210)) //Maybe delete the char*?
#define RegisterFolder (*(int(__thiscall *)(void *, RegEpisodeStruct*)) (g_pCore->GetBase() + 0x8B3BB0))

#pragma pack(push, 1)
struct RegEpisodeStruct
{
	char path[MAX_PATH];
	PAD(RegEpisode, pad0, 64);
	BYTE field_144;
	PAD(RegEpisode, pad1, 15);
	DWORD field_154;
	DWORD field_158;
	DWORD field_15C;
	DWORD field_160;
	BYTE field_164;
	BYTE field_165;
	PAD(RegEpisode, pad3, 1);
	BYTE field_167;
};
#pragma pack(pop)

void CHookDummy::registerEpisodes()
{
	
	char* GameFolder = GTA_malloc(MAX_PATH);
	getGameFolderFromRegistry(GameFolder);

	if (*(DWORD *) (this + 364) == -1)
	{
		int pointer = 0;

		char* TLADFolder = new char[MAX_PATH];
		GTA_memcpy(TLADFolder, GameFolder, strlen(GameFolder) + 1 > MAX_PATH ? MAX_PATH : strlen(GameFolder) + 1);
		GTA_strcat(TLADFolder, "\\TLAD\\", 6);

		SetGTAWorkdir(GTAWorkdirUknownPVOID, TLADFolder);

		if (IsFileExistInWorkdir(GTAWorkdirUknownPVOID, "setup2.xml", NULL))
		{
			RegEpisodeStruct* reg = new RegEpisodeStruct;
			memset(reg->path, 0, MAX_PATH);
			strcpy(reg->path, TLADFolder);
			reg->field_144 = 0;
			reg->field_154 = 0;
			reg->field_158 = 1;
			reg->field_15C = 0;
			reg->field_160 = 0;
			reg->field_164 = 0;
			reg->field_165 = 0;
			reg->field_167 = 0;

			*(DWORD *) (this + 364 + pointer) = RegisterFolder(this, reg);
			pointer += 4;

			*(BYTE *) (this + 361) = 1;
			*(DWORD *) (g_pCore->GetBase() + 0x10619D8) = 1;

			if (*(DWORD *) (g_pCore->GetBase() + 0x10619A4) > 0)
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = *(DWORD *) (g_pCore->GetBase() + 0x10619A4);
			else
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = 1;
		}

		char* TBoGTFolder = new char[MAX_PATH];
		GTA_memcpy(TBoGTFolder, GameFolder, strlen(GameFolder) + 1 > MAX_PATH ? MAX_PATH : strlen(GameFolder) + 1);
		GTA_strcat(TBoGTFolder, "\\TBoGT\\", 7);

		SetGTAWorkdir(GTAWorkdirUknownPVOID, TBoGTFolder);

		if (IsFileExistInWorkdir(GTAWorkdirUknownPVOID, "setup2.xml", NULL))
		{
			RegEpisodeStruct* reg = new RegEpisodeStruct;
			memset(reg->path, 0, MAX_PATH);
			strcpy(reg->path, TBoGTFolder);
			reg->field_144 = 0;
			reg->field_154 = 0;
			reg->field_158 = 1;
			reg->field_15C = 0;
			reg->field_160 = 0;
			reg->field_164 = 0;
			reg->field_165 = 0;
			reg->field_167 = 0;

			*(DWORD *) (this + 364 + pointer) = RegisterFolder(this, reg);
			pointer += 4;

			*(BYTE *) (this + 361) = 1;
			*(DWORD *) (g_pCore->GetBase() + 0x10619D8) = 1;

			if (*(DWORD *) (g_pCore->GetBase() + 0x10619A4) > 0)
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = *(DWORD *) (g_pCore->GetBase() + 0x10619A4);
			else
				*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = 1;
		}
	}

	WorkdirUnknownFunc(GTAWorkdirUknownPVOID);
	if (GameFolder)
		UnknownFuncWhitGameDir(GameFolder);


	*(BYTE *) (this + 358) = 0;
}

/*   69 */
#pragma pack(push, 1)
struct stXMLNode
{
	char field_0[32];
	char *pData;
	int bFound;
};
#pragma pack(pop)

/*   70 */
#pragma pack(push, 1)
struct stXMLData
{
	int iEpisodeId;
	char szName[64];
	char szDatFile[32];
	char szAudioFolder[64];
	char szAudioMetaData[64];
	char szLoadingScreens[64];
	char szLoadingScreensDat[64];
	char szLoadingScreensIngame[64];
	char szLoadingScreensIngameDat[64];
	char szTexturePath[64];
	char bRequiredForSave;
	char bEnabled;
	char field_222;
	char networkGame;
	char id;
	char episode;
};
#pragma pack(pop)

#define _DWORD DWORD
#define _BYTE BYTE
#define CXML__FindNode ((stXMLNode *(__thiscall*)(stXMLNode *pParent, const char *szNodeName, int a3))(g_pCore->GetBase() + 0x456A80))
#define dword_1924E38 *(DWORD*)(g_pCore->GetBase() + 0x1924E38)
#define CXML__Load ((stXMLNode** (__thiscall*) (void *this_, char *a2, char *a3))(g_pCore->GetBase() + 0x4585C0))
#define sub_8B3620 ((char (__thiscall*) (int, int a2))(g_pCore->GetBase() + 0x8B3620))
#define CheckDLCs ((char ( __thiscall*)(void*))(g_pCore->GetBase() + 0x8B4210))
#define sub_8B3AE0 ((int (__thiscall*) (int, stXMLData *pXMLData))(g_pCore->GetBase() + 0x8B3AE0))
#define sub_454D70 ((int (__thiscall*) (int ))(g_pCore->GetBase() + 0x454D70))
#define sub_401210 ((int (__cdecl*) (int a1))(g_pCore->GetBase() + 0x401210))
#define sub_45AFB0 ((void (__thiscall*)(int ))(g_pCore->GetBase() + 0x45AFB0))
#define sub_8B34D0 ((char (__thiscall*) (int, int a2))(g_pCore->GetBase() + 0x8B34D0))

char CHookDummy::loadEpisodes(int id)
{
	int v2; // ebp@1
	int v3; // esi@1
	stXMLNode **v4; // eax@1
	int v5; // edi@1
	stXMLNode *v6; // eax@3
	char *v7; // eax@4
	int v8; // ebp@6
	stXMLNode *pContentNode; // edi@6
	stXMLNode *pNameNode; // eax@7
	char *pName; // eax@8
	stXMLNode *pIdNode; // eax@10
	char *pId; // eax@12
	stXMLNode *pNetworkGameNode; // eax@18
	char *pNetworkGame; // eax@20
	stXMLNode *pEpisodeNode; // eax@24
	char *pEpisode; // eax@26
	stXMLNode *pDatFileNode; // eax@30
	char *pDatFile; // eax@32
	stXMLNode *pLoadingScreenNode; // eax@36
	int v21; // ecx@37
	char v22; // dl@38
	char *pLoadingScreens; // eax@40
	stXMLNode *pLoadingScreenDatNode; // eax@43
	int v25; // ecx@44
	char v26; // dl@45
	char *pLoadingScreensDat; // eax@47
	stXMLNode *pLoadingScreensIngameNode; // eax@50
	int v29; // ecx@51
	char v30; // dl@52
	char *pLoadingScreensIngame; // eax@54
	stXMLNode *pLoadingScreensIngameDatNode; // eax@57
	int v33; // ecx@58
	char v34; // dl@59
	char *pLoadingScreensIngameDat; // eax@61
	stXMLNode *pTexturePathNode; // eax@64
	int v37; // ecx@65
	char v38; // dl@66
	char *pTexturePath; // eax@68
	stXMLNode *pAudioFolderNode; // eax@71
	char *pAudioFolder; // eax@73
	stXMLNode *pAudioMetaDataNode; // eax@76
	char *pAudioMetaData; // eax@78
	char result; // al@87
	int v45; // [sp+10h] [bp-240h]@1
	int v46; // [sp+14h] [bp-23Ch]@1
	stXMLNode *thisa; // [sp+18h] [bp-238h]@2
	int v48; // [sp+1Ch] [bp-234h]@1
	stXMLData xmlData; // [sp+20h] [bp-230h]@7

	v2 = (int)this;
	v45 = (int)this;
	CheckDLCs(this);
	v3 = *(_DWORD *) (v2 + 332) + 360 * id;
	v48 = *(_DWORD *) (v2 + 332) + 360 * id;
	sub_8B3620(v2, id);
	SetGTAWorkdir((void*)(g_pCore->GetBase() + 0x1003C10), "extra:/");
	v4 = (stXMLNode **)CXML__Load((void *) dword_1924E38, "setup2.xml", "xml");
	v5 = (int) v4;
	v46 = (int) v4;
	if (v4)
	{
		thisa = *v4;
		if (!CXML__FindNode(*v4, "testmarketplace", 0))
		{
			v6 = CXML__FindNode(thisa, "device", 0);
			if (v6->bFound)
				v7 = v6->pData;
			else
				v7 = 0;
			v8 = v3 + 324;
			GTA_memcpy((char *) (v3 + 324), v7, 0x10u);
			GTA_strcat((char *) (v3 + 324), ":/", 0x10u);
			pContentNode = CXML__FindNode(thisa, "content", 0);
			if (pContentNode)
			{
				do
				{
					xmlData.bRequiredForSave = 0;
					xmlData.bEnabled = 0;
					xmlData.field_222 = 0;
					xmlData.id = 0;
					xmlData.episode = 0;
					xmlData.szName[0] = 0;
					xmlData.szDatFile[0] = 0;
					xmlData.szAudioMetaData[0] = 0;
					xmlData.szAudioFolder[0] = 0;
					xmlData.szLoadingScreens[0] = 0;
					xmlData.szLoadingScreensDat[0] = 0;
					xmlData.szLoadingScreensIngame[0] = 0;
					xmlData.szLoadingScreensIngameDat[0] = 0;
					xmlData.networkGame = -1;
					xmlData.szTexturePath[0] = 0;
					xmlData.iEpisodeId = id;
					pNameNode = CXML__FindNode(pContentNode, "name", 0);
					if (pNameNode->bFound)
						pName = pNameNode->pData;
					else
						pName = 0;
					GTA_memcpy(xmlData.szName, pName, 64u);
					pIdNode = CXML__FindNode(pContentNode, "id", 0);
					if (pIdNode)
					{
						if (pIdNode->bFound)
							pId = pIdNode->pData;
						else
							pId = 0;
						xmlData.id = atoi(pId);
					}
					else
					{
						xmlData.id = 0;
					}
					if (CXML__FindNode(pContentNode, "requiredForSave", 0))
						xmlData.bRequiredForSave = 1;
					pNetworkGameNode = CXML__FindNode(pContentNode, "networkgame", 0);
					if (pNetworkGameNode)
					{
						if (pNetworkGameNode->bFound)
							pNetworkGame = pNetworkGameNode->pData;
						else
							pNetworkGame = 0;
						xmlData.networkGame = atoi(pNetworkGame);
					}
					else
					{
						xmlData.networkGame = -1;
					}
					pEpisodeNode = CXML__FindNode(pContentNode, "episode", 0);
					if (pEpisodeNode)
					{
						if (pEpisodeNode->bFound)
							pEpisode = pEpisodeNode->pData;
						else
							pEpisode = 0;
						xmlData.episode = atoi(pEpisode);
						xmlData.bRequiredForSave = 1;
					}
					else
					{
						xmlData.episode = 0;
					}
					pDatFileNode = CXML__FindNode(pContentNode, "datfile", 0);
					if (pDatFileNode)
					{
						if (pDatFileNode->bFound)
							pDatFile = pDatFileNode->pData;
						else
							pDatFile = 0;
						GTA_memcpy(xmlData.szDatFile, pDatFile, 32u);
					}
					else
					{
						xmlData.szDatFile[0] = 0;
					}
					pLoadingScreenNode = CXML__FindNode(pContentNode, "loadingscreens", 0);
					if (pLoadingScreenNode)
					{
						v21 = v3 + 324;
						do
						{
							v22 = *(_BYTE *) v21;
							*(&xmlData.szLoadingScreens[v21] - v8) = *(_BYTE *) v21;
							++v21;
						} while (v22);
						if (pLoadingScreenNode->bFound)
							pLoadingScreens = pLoadingScreenNode->pData;
						else
							pLoadingScreens = 0;
						GTA_strcat(xmlData.szLoadingScreens, pLoadingScreens, 64u);
					}
					pLoadingScreenDatNode = CXML__FindNode(pContentNode, "loadingscreensdat", 0);
					if (pLoadingScreenDatNode)
					{
						v25 = v3 + 324;
						do
						{
							v26 = *(_BYTE *) v25;
							*(&xmlData.szLoadingScreensDat[v25] - v8) = *(_BYTE *) v25;
							++v25;
						} while (v26);
						if (pLoadingScreenDatNode->bFound)
							pLoadingScreensDat = pLoadingScreenDatNode->pData;
						else
							pLoadingScreensDat = 0;
						GTA_strcat(xmlData.szLoadingScreensDat, pLoadingScreensDat, 64u);
					}
					pLoadingScreensIngameNode = CXML__FindNode(pContentNode, "loadingscreensingame", 0);
					if (pLoadingScreensIngameNode)
					{
						v29 = v3 + 324;
						do
						{
							v30 = *(_BYTE *) v29;
							*(&xmlData.szLoadingScreensIngame[v29] - v8) = *(_BYTE *) v29;
							++v29;
						} while (v30);
						if (pLoadingScreensIngameNode->bFound)
							pLoadingScreensIngame = pLoadingScreensIngameNode->pData;
						else
							pLoadingScreensIngame = 0;
						GTA_strcat(xmlData.szLoadingScreensIngame, pLoadingScreensIngame, 0x40u);
					}
					pLoadingScreensIngameDatNode = CXML__FindNode(pContentNode, "loadingscreensingamedat", 0);
					if (pLoadingScreensIngameDatNode)
					{
						v33 = v3 + 324;
						do
						{
							v34 = *(_BYTE *) v33;
							*(&xmlData.szLoadingScreensIngameDat[v33] - v8) = *(_BYTE *) v33;
							++v33;
						} while (v34);
						if (pLoadingScreensIngameDatNode->bFound)
							pLoadingScreensIngameDat = pLoadingScreensIngameDatNode->pData;
						else
							pLoadingScreensIngameDat = 0;
						GTA_strcat(xmlData.szLoadingScreensIngameDat, pLoadingScreensIngameDat, 0x40u);
					}
					pTexturePathNode = CXML__FindNode(pContentNode, "texturepath", 0);
					if (pTexturePathNode)
					{
						v37 = v3 + 324;
						do
						{
							v38 = *(_BYTE *) v37;
							*(&xmlData.szTexturePath[v37] - v8) = *(_BYTE *) v37;
							++v37;
						} while (v38);
						if (pTexturePathNode->bFound)
							pTexturePath = pTexturePathNode->pData;
						else
							pTexturePath = 0;
						GTA_strcat(xmlData.szTexturePath, pTexturePath, 0x40u);
					}
					pAudioFolderNode = CXML__FindNode(pContentNode, "audiofolder", 0);
					if (pAudioFolderNode)
					{
						if (pAudioFolderNode->bFound)
							pAudioFolder = pAudioFolderNode->pData;
						else
							pAudioFolder = 0;
						GTA_memcpy(xmlData.szAudioFolder, pAudioFolder, 64u);
					}
					pAudioMetaDataNode = CXML__FindNode(pContentNode, "audiometadata", 0);
					if (pAudioMetaDataNode)
					{
						if (pAudioMetaDataNode->bFound)
							pAudioMetaData = pAudioMetaDataNode->pData;
						else
							pAudioMetaData = 0;
						GTA_memcpy(xmlData.szAudioMetaData, pAudioMetaData, 0x40u);
					}
					if (CXML__FindNode(pContentNode, "enabled", 0))
						xmlData.bEnabled = 1;
					sub_8B3AE0(v45, &xmlData);
					pContentNode = CXML__FindNode(thisa, "content", (int) pContentNode);
				} while (pContentNode);
				v3 = v48;
			}
			v5 = v46;
			v2 = v45;
		}
		sub_454D70(v5);
		sub_401210(v5);
	}
	sub_45AFB0((int) (g_pCore->GetBase() + 0x1003C10));
	result = sub_8B34D0(v2, id);
	*(_BYTE *) (v3 + 357) = 1;
	return result;
}

void __cdecl renderMenus() //render Main and pause menu
{
	//g_pCore->GetChat()->Outputf(false, "sub_4774A0()");
	//*(DWORD*) (g_pCore->GetBase() + 0x104E130) = 0; // 1 = blink, but i wagt hide it.
	//*(BYTE*) (g_pCore->GetBase() + 0x104E1D8) = 1;
}

void __cdecl sub_47F080()
{
	if (g_pCore->GetNetworkManager())
		g_pCore->GetNetworkManager()->Pulse();
		//g_pCore->GetChat()->Outputf(false, "sub_47F080()");
}

void __cdecl sub_47BA60()
{
	//g_pCore->GetChat()->Outputf(false, "sub_47BA60()");
}

void __cdecl runStartupScript()
{
	g_pCore->GetIVStartupScript()->Process();
}

enum eRAGETHREAD_States
{
	ThreadStateIdle,
	ThreadStateRunning,
	ThreadStateKilled,
	ThreadState3,
	ThreadState4,			// Sets opsToExecute to 1100000, and state to Idle in CallNative
};

struct sSRCThread_Content
{
	unsigned int ThreadId;		// 00-04 m_nThreadId dd ?
	unsigned int ScriptHash;	// 04-08 m_dwScriptHash dd ?
	eRAGETHREAD_States State;	// 08-0C m_eThreadState dd ?
	unsigned int IP;			// 0C-10 m_nIP       dd ?
	unsigned int FrameSP;		// 10-14 m_nFrameSP  dd ?
	unsigned int SP;			// 14-18 m_nSP       dd ?
	unsigned int TimerA;		// 18-1C m_nTimerA   dd ?
	unsigned int TimerB;		// 1C-20 m_nTimerB   dd ?
	unsigned int TimerC;		// 20-24 m_nTimerC   dd ?
	float WaitTime;				// 24-28 m_fWaitTime dd ?
	unsigned int _f28;			// 28-2C field_28    dd ?
	unsigned int _f2C;			// 2C-30 field_2C    dd ?
	unsigned int _f30;			// 30-34 field_30    dd ?
	unsigned int _f34;			// 34-38 field_34    dd ?
	unsigned int _f38;			// 38-3C field_38    dd ?
	unsigned int _f3C;			// 3C-40 field_3C    dd ?
	unsigned int _f40;			// 40-44 field_40    dd ?
	unsigned int ExIP;			// 44-48 ExIP        dd ?
	unsigned int ExFrameSP;		// 48-4C ExFrameSP   dd ?
	unsigned int ExSP;			// 4C-50 ExSP        dd ?
	unsigned int _f50;			// 50-54 field_50    dd ?
};

class sSRCThread
{
public:
	DWORD m_dwVFTable;              // 00-04 _vmt        dd ?
	sSRCThread_Content m_Context;		// 04-58 m_Context   scrThreadContext ?
	void * m_pStack;					// 58-5C m_pStack    dd ?
	unsigned int _f5C;				// 5C-60 field_5C    dd ?
	void * m_pXLiveBuffer;				// 60-64 m_pXLiveBuffer dd ?
	unsigned int _f64;				// 64-68 field_64    dd ?
	unsigned int _f68;				// 68-6C field_68    dd ?
	char *m_pszExitMessage;			// 6C-70 m_pszExitMessage dd ?
};

class sRAGETHREAD : public sSRCThread
{
public:
	char m_szProgramName[24];					// 70-88 m_szProgramName db 24 dup(?)
	unsigned int _f88;							// 88-8C field_88    dd ?
	unsigned int _f8C;							// 8C-90 field_8C    dd ?
	unsigned int _f90;							// 90-94 field_90    dd ?
	bool _f94;									// 94-95 field_94    db ?
	bool _f95;									// 95-96 --- db ?									// Check IDA
	bool m_bThisScriptShouldBeSaved;			// 96-97 m_bThisScriptShouldBeSaved db ?
	bool m_bPlayerControlOnInMissionCleanup;	// 97-98 m_bPlayerControlOnInMissionCleanup db ?
	bool m_bClearHelpInMissionCleanup;			// 98-99 m_bClearHelpInMissionCleanup db ?
	bool _f99;									// 99-9A field_99    db ?
	bool m_bAllowNonMinigameTextMessages;		// 9A-9B m_bAllowNonMinigameTextMessages db ?
	bool _f9B;									// 9B-9C field_9B    db ?
	bool _f9C;									// 9C-9D --- db ?									// Check IDA
	bool m_bCanBePaused;						// 9D-9E m_bCanBePaused db ?
	bool _f9E;									// 9E-9F field_9E    db ?
	bool _f9F;									// 9F-A0 field_9F    db ?
	bool _fA0;									// A0-A4 field_A0    dd ?
	bool m_bCanRemoveBlipsCreatedByAnyScript;	// A4-A5 m_bCanRemoveBlipsCreatedByAnyScript db ?
	bool _fA5;									// A5-A6             db ? ; undefined
	bool _fA6;									// A6-A7             db ? ; undefined
	bool _fA7;									// A7-A8             db ? ; undefined
	unsigned int _fA8;							// A8-AC field_A8    dd ?
	unsigned int m_nFlags;						// AC-B0 m_nFlags    dd ?
};

sRAGETHREAD* g_pRageScriptThread = NULL;

__declspec(naked) int GetRunningScriptThread()
{
	_asm mov eax, g_pRageScriptThread;
	_asm retn;
}

void CHooks::Intialize()
{
	// Hook GetPlayerInfoFromIndex to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetPlayerInfoFromIndex, (DWORD)GetPlayerInfoFromIndex_Hook);
	
	// Hook GetIndexFromPlayerInfo to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetIndexFromPlayerInfo, (DWORD)GetIndexFromPlayerInfo_Hook);
	
	// Hook GetLocalPlayerPed to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetLocalPlayerPed, (DWORD)GetLocalPlayerPed_Hook);
	
	// Hook CTask::~CTask to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_CTask__Destructor, (DWORD)CTask__Destructor_Hook);
	
	// Hook initial loading screens
	CPatcher::InstallCallPatch(COffsets::FUNC_RemoveInitialLoadingScreens, (DWORD) RemoveLoadingScreens);
	
	// Always draw vehicle hazzard lights
	CPatcher::InstallNopPatch(COffsets::PATCH_CVehicle__HazzardLightsOn, 2);
	
	// Disable loading music
	CPatcher::InstallNopPatch(COffsets::CALL_StartLoadingTune, 5);

	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x9D180B, (DWORD) PhysicsHook);

	// Disable automatic vehicle engine turn-on
	CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchVehicleDriverProcess, (DWORD) CTaskSimpleStartVehicle__Process);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x8B3FF0, CPatcher::GetClassMemberAddress(&CHookDummy::registerEpisodes));
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x8B49B0, CPatcher::GetClassMemberAddress(&CHookDummy::loadEpisodes));

	// Disable wanted circles on the minimap(we have no cops which are following you atm ^^)
	*(BYTE *) (g_pCore->GetBase() + 0x83C216) = 0xEB;
	*(BYTE *) (g_pCore->GetBase() + 0x83BFE0) = 0xC3;

	//CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x47BFED, (DWORD) renderMenus);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47F080, (DWORD) sub_47F080);

	//CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x47BA60, (DWORD) sub_47BA60);

	CPatcher::InstallCallPatch(g_pCore->GetBase() + 0x834093, (DWORD)runStartupScript);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x834098, g_pCore->GetBase() + 0x8340F4);
	
	// Disable check to invalid threads
	g_pRageScriptThread = new sRAGETHREAD;
	memset(g_pRageScriptThread, NULL, sizeof(sRAGETHREAD));
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x82E7E0), (DWORD) GetRunningScriptThread, 5);

	CPatcher::InstallJmpPatch(COffsets::IV_Hook__IncreasePoolSizes, CPatcher::GetClassMemberAddress(&IVPoolOwns::IVPoolHook));

#ifdef GTAV_MAP
	// Patch crosshair
	CPatcher::Unprotect((g_pCore->GetBase() + 0xE35790), 13);
	*(DWORD *) (g_pCore->GetBase() + 0xE35790) = 0x73706172;
	*(DWORD *) (g_pCore->GetBase() + 0xE35790 + 0x4) = 0x6B6C6500;
	*(DWORD *) (g_pCore->GetBase() + 0xE35790 + 0x8) = 0x00000000;
	*(BYTE*) (g_pCore->GetBase() + 0xE35790 + 0x12) = 0x0;

	// Patch icons to star
	CPatcher::Unprotect((g_pCore->GetBase() + 0xFEA8E4), 20);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8E4) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8E8) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8EC) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8F0) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);
	*(DWORD *) (g_pCore->GetBase() + 0xFEA8F4) = *(DWORD *) (g_pCore->GetBase() + 0xC9654C + 0x1);

	// Change calc from circle to square(blips)
	*(BYTE*) (g_pCore->GetBase() + 0x8385E7 + 0x6) = 0x1;
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x8386AB, (DWORD) Keks);

	// Enable square map(instead of circle map)
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0xA22C53, g_pCore->GetBase() + 0xA22EF3);

	// Enable big radar
	*(BYTE *) (g_pCore->GetBase() + 0x08364D0 + 0x6) = 0x1;

	// Hook resize map function
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x8364D0), (DWORD) ResizeMap, 5);
	*(WORD *) (g_pCore->GetBase() + 0x8364D0 + 0x5) = 0x9090;

	// Make blip small
	*(BYTE *) (g_pCore->GetBase() + 0x4B516F + 0x6) = 0x1; // cmp VAR_DEVMODE, 1
	*(BYTE *) (g_pCore->GetBase() + 0x4B516F + 0x6) = 0x1; // cmp VAR_DEVMODE, 1

	// Hook render map function
	CPatcher::InstallCallPatch((g_pCore->GetBase() + 0xA22E71), (DWORD) RenderMap, 5);
#endif
}
