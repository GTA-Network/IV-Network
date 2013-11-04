//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: EpisodeManager.cpp
// Project: Client.Core
// Author: balika011 <balika011@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include <CCore.h>
#include <Patcher/CPatcher.h>
#include "EpisodeManager.h"

extern CCore* g_pCore;

class EpisodeManagerDummy {
public:
	void __thiscall registerEpisodes();
	char __thiscall loadEpisodes(int id);
};

#define GTA_malloc (*(char *(__cdecl *)(int)) (g_pCore->GetBase() + 0x4011D0))
#define getGameFolderFromRegistry (*(bool(__stdcall *)(char *)) (g_pCore->GetBase() + 0x8B3260))
#define GTA_memcpy (*(int(__cdecl *)(char *, const char *, int)) (g_pCore->GetBase() + 0xD0BC80))
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
	char szPath[MAX_PATH];
	PAD(RegEpisode, pad0, 64);
	char szDevice[16];
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

void EpisodeManagerDummy::registerEpisodes()
{
	if (*(DWORD *) (this + 364) == -1)
	{
		RegEpisodeStruct* ivn = new RegEpisodeStruct;
		GTA_memcpy(ivn->szPath, SharedUtility::GetAppPath(), MAX_PATH);
		GTA_strcat(ivn->szPath, "\\IVN\\", 6);
		ivn->szDevice[0] = '\0';
		ivn->field_154 = 0;
		ivn->field_158 = 1;
		ivn->field_15C = 0;
		ivn->field_160 = 0;
		ivn->field_164 = 0;
		ivn->field_165 = 0;
		ivn->field_167 = 0;
		RegisterFolder(this, ivn);

		*(BYTE *) (this + 361) = 1;
		*(DWORD *) (g_pCore->GetBase() + 0x10619D8) = 1;

		if (*(DWORD *) (g_pCore->GetBase() + 0x10619A4) > 0)
			*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = *(DWORD *) (g_pCore->GetBase() + 0x10619A4);
		else
			*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = 1;

		RegEpisodeStruct* tlad = new RegEpisodeStruct;
		GTA_memcpy(tlad->szPath, SharedUtility::GetExePath(), MAX_PATH);
		GTA_strcat(tlad->szPath, "\\TLAD\\", 6);
		tlad->szDevice[0] = '\0';
		tlad->field_154 = 0;
		tlad->field_158 = 1;
		tlad->field_15C = 0;
		tlad->field_160 = 0;
		tlad->field_164 = 0;
		tlad->field_165 = 0;
		tlad->field_167 = 0;
		RegisterFolder(this, tlad);

		*(BYTE *) (this + 361) = 1;
		*(DWORD *) (g_pCore->GetBase() + 0x10619D8) = 1;

		if (*(DWORD *) (g_pCore->GetBase() + 0x10619A4) > 0)
			*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = *(DWORD *) (g_pCore->GetBase() + 0x10619A4);
		else
			*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = 1;

		RegEpisodeStruct* tbogt = new RegEpisodeStruct;
		GTA_memcpy(tbogt->szPath, SharedUtility::GetExePath(), MAX_PATH);
		GTA_strcat(tbogt->szPath, "\\TBoGT\\", 7);
		tbogt->szDevice[0] = '\0';
		tbogt->field_154 = 0;
		tbogt->field_158 = 1;
		tbogt->field_15C = 0;
		tbogt->field_160 = 0;
		tbogt->field_164 = 0;
		tbogt->field_165 = 0;
		tbogt->field_167 = 0;
		RegisterFolder(this, tbogt);

		*(BYTE *) (this + 361) = 1;
		*(DWORD *) (g_pCore->GetBase() + 0x10619D8) = 1;

		if (*(DWORD *) (g_pCore->GetBase() + 0x10619A4) > 0)
			*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = *(DWORD *) (g_pCore->GetBase() + 0x10619A4);
		else
			*(DWORD *) (g_pCore->GetBase() + 0x10619BC) = 1;
	}

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
struct stXMLData //this name is not correct
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

#define CXML__FindNode ((stXMLNode *(__thiscall*) (stXMLNode *pParent, const char *szNodeName, int a3))(g_pCore->GetBase() + 0x456A80))
#define dword_1924E38 *(DWORD*)(g_pCore->GetBase() + 0x1924E38)
#define CXML__Load ((stXMLNode** (__thiscall*) (void *this_, char *a2, char *a3))(g_pCore->GetBase() + 0x4585C0))
#define sub_8B3620 ((char (__thiscall*) (void*, int a2))(g_pCore->GetBase() + 0x8B3620))
#define CheckDLCs ((char ( __thiscall*)(void*))(g_pCore->GetBase() + 0x8B4210))
#define sub_8B3AE0 ((int (__thiscall*) (void*, stXMLData *pXMLData))(g_pCore->GetBase() + 0x8B3AE0))
#define sub_454D70 ((int (__thiscall*) (stXMLNode**))(g_pCore->GetBase() + 0x454D70))
#define sub_8B34D0 ((char (__thiscall*) (void*, int a2))(g_pCore->GetBase() + 0x8B34D0))

char EpisodeManagerDummy::loadEpisodes(int id)
{
	CheckDLCs(this);
	RegEpisodeStruct* reg = (RegEpisodeStruct*) (*(DWORD *) (this + 332) + sizeof(RegEpisodeStruct) * id);
	sub_8B3620(this, id);

	if (id == 0)
	{
		GTA_memcpy(reg->szDevice, "e0:/", 16);

		stXMLData radio;
		radio.iEpisodeId = id;
		GTA_memcpy(radio.szName, "IV:Network Radio", 64);
		radio.szDatFile[0] = 0;
		radio.szAudioFolder[0] = 0;
		GTA_memcpy(radio.szAudioMetaData, "radio.xml", 64);
		radio.szLoadingScreens[0] = 0;
		radio.szLoadingScreensDat[0] = 0;
		radio.szLoadingScreensIngame[0] = 0;
		radio.szLoadingScreensIngameDat[0] = 0;
		radio.szTexturePath[0] = 0;
		radio.bRequiredForSave = 0;
		radio.bEnabled = 1;
		radio.field_222 = 0;
		radio.networkGame = -1;
		radio.id = 1;
		radio.episode = 0;
		sub_8B3AE0(this, &radio);

		stXMLData episode;
		episode.iEpisodeId = id;
		GTA_memcpy(episode.szName, MOD_NAME, 64);
		GTA_memcpy(episode.szDatFile, "content.dat", 32);
		episode.szAudioFolder[0] = 0;
		GTA_memcpy(episode.szAudioMetaData, "audio.xml", 64);
		GTA_memcpy(episode.szLoadingScreens, "e1:/pc/textures/loadingscreens.wtd", 64);
		GTA_memcpy(episode.szLoadingScreensDat, "e1:/common/data/loadingscreens.dat", 64);
		GTA_memcpy(episode.szLoadingScreensIngame, "e1:/pc/textures/loadingscreens_ingame.wtd", 64);
		GTA_memcpy(episode.szLoadingScreensIngameDat, "e1:/common/data/loadingscreens_ingame.dat", 64);
		GTA_memcpy(episode.szTexturePath, "e1:/pc/textures/", 64);
		episode.bRequiredForSave = 1;
		episode.bEnabled = 0;
		episode.field_222 = 0;
		episode.networkGame = -1;
		episode.id = 2;
		episode.episode = 1;
		sub_8B3AE0(this, &episode);
	}
	else if (id == 1)
	{
		GTA_memcpy(reg->szDevice, "e1:/", 16);

		stXMLData radio;
		radio.iEpisodeId = id;
		GTA_memcpy(radio.szName, "The Lost and Damned Radio", 64);
		radio.szDatFile[0] = 0;
		radio.szAudioFolder[0] = 0;
		GTA_memcpy(radio.szAudioMetaData, "e1_radio.xml", 64);
		radio.szLoadingScreens[0] = 0;
		radio.szLoadingScreensDat[0] = 0;
		radio.szLoadingScreensIngame[0] = 0;
		radio.szLoadingScreensIngameDat[0] = 0;
		radio.szTexturePath[0] = 0;
		radio.bRequiredForSave = 0;
		radio.bEnabled = 1;
		radio.field_222 = 0;
		radio.networkGame = -1;
		radio.id = 3;
		radio.episode = 0;
		sub_8B3AE0(this, &radio);

		stXMLData episode;
		episode.iEpisodeId = id;
		GTA_memcpy(episode.szName, "The Lost and Damned", 64);
		GTA_memcpy(episode.szDatFile, "content.dat", 32);
		episode.szAudioFolder[0] = 0;
		GTA_memcpy(episode.szAudioMetaData, "e1_audio.xml", 64);
		GTA_memcpy(episode.szLoadingScreens, "e1:/pc/textures/loadingscreens.wtd", 64);
		GTA_memcpy(episode.szLoadingScreensDat, "e1:/common/data/loadingscreens.dat", 64);
		GTA_memcpy(episode.szLoadingScreensIngame, "e1:/pc/textures/loadingscreens_ingame.wtd", 64);
		GTA_memcpy(episode.szLoadingScreensIngameDat, "e1:/common/data/loadingscreens_ingame.dat", 64);
		GTA_memcpy(episode.szTexturePath, "e1:/pc/textures/", 64);
		episode.bRequiredForSave = 1;
		episode.bEnabled = 0;
		episode.field_222 = 0;
		episode.networkGame = -1;
		episode.id = 4;
		episode.episode = 2;
		sub_8B3AE0(this, &episode);
	}
	else if (id == 2)
	{
		GTA_memcpy(reg->szDevice, "e2:/", 16);

		stXMLData radio;
		radio.iEpisodeId = id;
		GTA_memcpy(radio.szName, "The Ballad of Gay Tony", 64);
		radio.szDatFile[0] = 0;
		radio.szAudioFolder[0] = 0;
		GTA_memcpy(radio.szAudioMetaData, "e2_radio.xml", 64);
		radio.szLoadingScreens[0] = 0;
		radio.szLoadingScreensDat[0] = 0;
		radio.szLoadingScreensIngame[0] = 0;
		radio.szLoadingScreensIngameDat[0] = 0;
		radio.szTexturePath[0] = 0;
		radio.bRequiredForSave = 0;
		radio.bEnabled = 1;
		radio.field_222 = 0;
		radio.networkGame = -1;
		radio.id = 5;
		radio.episode = 0;
		sub_8B3AE0(this, &radio);

		stXMLData episode;
		episode.iEpisodeId = id;
		GTA_memcpy(episode.szName, "The Ballad of Gay Tony", 64);
		GTA_memcpy(episode.szDatFile, "content.dat", 32);
		episode.szAudioFolder[0] = 0;
		GTA_memcpy(episode.szAudioMetaData, "e2_audio.xml", 64);
		GTA_memcpy(episode.szLoadingScreens, "e2:/pc/textures/loadingscreens.wtd", 64);
		GTA_memcpy(episode.szLoadingScreensDat, "e2:/common/data/loadingscreens.dat", 64);
		GTA_memcpy(episode.szLoadingScreensIngame, "e2:/pc/textures/loadingscreens_ingame.wtd", 64);
		GTA_memcpy(episode.szLoadingScreensIngameDat, "e2:/common/data/loadingscreens_ingame.dat", 64);
		GTA_memcpy(episode.szTexturePath, "e2:/pc/textures/", 64);
		episode.bRequiredForSave = 1;
		episode.bEnabled = 0;
		episode.field_222 = 0;
		episode.networkGame = -1;
		episode.id = 6;
		episode.episode = 3;
		sub_8B3AE0(this, &episode);
	}
	else
	{
		MessageBox(0, "Kill yourself...", "", 0);
		ExitProcess(0);
	}

	reg->field_165 = 1;
	return sub_8B34D0(this, id);
}

void EpisodeManager::Initialize()
{
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x8B3FF0, CPatcher::GetClassMemberAddress(&EpisodeManagerDummy::registerEpisodes));
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x8B49B0, CPatcher::GetClassMemberAddress(&EpisodeManagerDummy::loadEpisodes));
}