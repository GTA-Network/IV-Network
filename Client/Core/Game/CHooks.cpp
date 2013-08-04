//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CHooks.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include	"CHooks.h"
#include	"COffsets.h"
#include	<CCore.h>
#include	<Patcher\CPatcher.h>

// Temp typedef(until we're added this classes)
typedef DWORD IVTask;
typedef DWORD IVPlayerInfo;
typedef DWORD IVPool;
typedef DWORD IVPlayerPed;

extern	CCore				* g_pCore;
IVTask       * ___pTask = NULL;
unsigned int   uiPlayerInfoIndex = 0;
IVPlayerInfo * pReturnedPlayerInfo = NULL;
unsigned int   uiReturnedIndex = 0;
IVPlayerPed  * _pPlayerPed = NULL;
bool           bInvalidIndex = false;
IVPool       * g_pIVPool;
BYTE         * g_pPoolAllocatedMemory;

void RemoveInitialLoadingScreens()
{
        // Legal, Legal 2, R*, R*N, GTA:IV, ...
        for(int i = 0; i < *(int *)(COffsets::VAR_NumLoadingScreens); ++i)
        {
                *(DWORD *)(COffsets::VAR_FirstLoadingScreenType + i * 400) = ((i <= 4) ? 4 : i);

                if(i <= 4)
                        *(DWORD *)(COffsets::VAR_FirstLoadingScreenDuration + i * 400) = 0;
        }
}

void _declspec(naked) CTask__Destructor_Hook()
{
        _asm
        {
                mov ___pTask, ecx
                pushad
        }

		/*
        // Do we have a client task manager?
        if(g_pClient->GetClientTaskManager())
        {
                // Let the client task manager handle this task deletion
                g_pClient->GetClientTaskManager()->HandleTaskDelete(___pTask);
        }
		*/
        _asm
        {
                popad
                push esi
                mov esi, ecx
                push esi
                mov dword ptr [esi], offset COffsets::VAR_CTask__VFTable
                jmp COffsets::RETURN_CTask__Destructor
        }
}

void _declspec(naked) CEpisodes__IsEpisodeAvaliable_Hook()
{
        _asm
        {
                mov eax, [esp+4]
                test eax, eax
                jnz it_not
                mov al, 1
                retn 4
it_not:
                xor al, al
                retn 4
        }
}

IVPlayerInfo * GetPlayerInfoFromIndex(unsigned int uiIndex)
{
	/*
        // Default to the local player info just incase the index is invalid
        pReturnedPlayerInfo = CGame::GetPools()->GetPlayerInfoFromIndex(0);

        // Is this not the local player info?
        if(uiIndex != 0)
        {
                CContextData * pContextInfo = CContextDataManager::GetContextData(uiIndex);

                if(pContextInfo)
                        pReturnedPlayerInfo = pContextInfo->GetPlayerInfo()->GetPlayerInfo();
        }
	*/
        return pReturnedPlayerInfo;
}

void _declspec(naked) GetPlayerInfoFromIndex_Hook()
{
        _asm
        {
                mov eax, [esp+4]
                mov uiPlayerInfoIndex, eax
                pushad
        }

        GetPlayerInfoFromIndex(uiPlayerInfoIndex);

        _asm
        {
                popad
                mov eax, pReturnedPlayerInfo
                retn
        }
}

unsigned int GetIndexFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
        // Default to the local player info just incase the player info is invalid
        uiReturnedIndex = 0;

        // Is this not the local player info?
       /* if(pPlayerInfo != CGame::GetPools()->GetPlayerInfoFromIndex(0))
        {
                CContextData * pContextInfo = CContextDataManager::GetContextData(pPlayerInfo);

                if(pContextInfo)
                        uiReturnedIndex = pContextInfo->GetPlayerInfo()->GetPlayerNumber();
        }*/

        return uiReturnedIndex;
}

void _declspec(naked) GetIndexFromPlayerInfo_Hook()
{
        _asm
        {
                mov eax, [esp+4]
                mov pReturnedPlayerInfo, eax
                pushad
        }

        GetIndexFromPlayerInfo(pReturnedPlayerInfo);

        _asm
        {
                popad
                mov eax, uiReturnedIndex
                retn
        }
}

IVPlayerPed * GetLocalPlayerPed()
{
        // Default to the local player ped (If available)
        /*IVPlayerInfo * pPlayerInfo = CGame::GetPools()->GetPlayerInfoFromIndex(0);

        if(pPlayerInfo)
                _pPlayerPed = pPlayerInfo->m_pPlayerPed;
        else
                _pPlayerPed = NULL;

        // Is the local player id valid?
        if(CGame::GetPools()->GetLocalPlayerIndex() != -1)
        {
                // Is the player index not the local player?
                if(CGame::GetPools()->GetLocalPlayerIndex() != 0)
                {
                        // Get the context info for the player index
                        CContextData * pContextInfo = CContextDataManager::GetContextData((BYTE)CGame::GetPools()->GetLocalPlayerIndex());

                        // Is the context info valid?
                        if(pContextInfo)
                        {
                                // Set the player ped to the remote player
                                _pPlayerPed = pContextInfo->GetPlayerPed()->GetPlayerPed();
                        }
                }
        }

        // Some code to test a theory
        if(_pPlayerPed == NULL)
        {
                if(!bInvalidIndex)
                {
                        CLogFile::Printf("GetLocalPlayerPed Return Is Invalid (Index is %d)", CGame::GetPools()->GetLocalPlayerIndex());
                        bInvalidIndex = true;
                }
        }
        else
        {
                if(bInvalidIndex)
                {
                        CLogFile::Printf("GetLocalPlayerPed Return Is Now Valid");
                        bInvalidIndex = false;
                }
        }
		*/
        return _pPlayerPed;
}

void _declspec(naked) GetLocalPlayerPed_Hook()
{
        _asm
        {
                pushad
        }

        GetLocalPlayerPed();

        _asm
        {
                popad
                mov eax, _pPlayerPed
                retn
        }
}

IVPlayerPed * GetPlayerPedFromPlayerInfo(IVPlayerInfo * pPlayerInfo)
{
        // Is the player info pointer valid?
        if(pPlayerInfo)
              ;  // _pPlayerPed = pPlayerInfo->m_pPlayerPed;
        else
        {
                // Player info pointer is invalid, use the local player ped
                //_pPlayerPed = GetLocalPlayerPed();
        }

        return _pPlayerPed;
}

void _declspec(naked) GetPlayerPedFromPlayerInfo_Hook()
{
        _asm
        {
                mov eax, [esp+4]
                mov pReturnedPlayerInfo, eax
                pushad
        }

        GetPlayerPedFromPlayerInfo(pReturnedPlayerInfo);

        _asm
        {
                popad
                mov eax, _pPlayerPed
                retn
        }
}

int hFile2;
HANDLE iTexture;
int v2;// edi@1
signed int v3;// esi@1
int v4;// ecx@2
int v5;// eax@3
int result;// eax@5
DWORD dwJump;
void _declspec(naked) TextureSelect_Hook()
{   
        _asm
        {
                mov eax, [esp+4]
        mov iTexture, eax
        mov eax, [esp+8]
        mov hFile2, eax  
        pushad
        }

        if(hFile2 < 10000000) 
        {
                CLogFile::Printf("WARNING! TextureSelect has an invalid pointer((Pointer)%p/(File/Type)%s!", hFile2, iTexture);
                /*_asm
                {
                        popad
                        retn 4
                }*/
        }
        else    
                ;//CLogFile::Printf("TextureSelect_Hook: (Pointer)%p/(File/Type)%s", hFile2, iTexture);

		dwJump = (g_pCore->GetBase() + 0x639715);
        _asm
        {
                popad
                push ebx
                push esi
                push edi
                mov edi, ecx
                jmp dwJump
        }
}

void CHooks::Intialize()
{
	// Hook CEpisodes::IsEpisodeAvaliable to use our own function
	/*CPatcher::InstallJmpPatch(COffsets::FUNC_CEpisodes__IsEpisodeAvaliable, (DWORD)CEpisodes__IsEpisodeAvaliable_Hook);

	// Hook GetPlayerInfoFromIndex to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetPlayerInfoFromIndex, (DWORD)GetPlayerInfoFromIndex_Hook);

	// Hook GetIndexFromPlayerInfo to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetIndexFromPlayerInfo, (DWORD)GetIndexFromPlayerInfo_Hook);

	// Hook GetLocalPlayerPed to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_GetLocalPlayerPed, (DWORD)GetLocalPlayerPed_Hook);

	// Hook CTask::~CTask to use our own function
	CPatcher::InstallJmpPatch(COffsets::FUNC_CTask__Destructor, (DWORD)CTask__Destructor_Hook);*/

	// Disable initial loading screens
	CPatcher::InstallCallPatch(COffsets::FUNC_RemoveInitialLoadingScreens, (DWORD)RemoveInitialLoadingScreens);

    // Always draw vehicle hazzard lights
	CPatcher::InstallNopPatch(COffsets::PATCH_CVehicle__HazzardLightsOn, 2);

	// Disable loading music
	CPatcher::InstallNopPatch(COffsets::CALL_StartLoadingTune, 5);

    // Hook texture select/generate function
    CPatcher::InstallJmpPatch(COffsets::FUNC_GENERATETEXTURE, (DWORD)TextureSelect_Hook);
}