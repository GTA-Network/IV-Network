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

#ifndef CCore_h
#define CCore_h

#include <Common.h>
#include <d3d9.h>

#ifdef DrawText
#undef DrawText
#endif

#include <CLogFile.h>
#include <CSettings.h>
#include <SharedUtility.h>
#include <Patcher/CPatcher.h>

#include "Graphics/CChatBox.h"

#include <Game/eGame.h>

#include <Hooks/CXLive.h>
#include <Hooks/CWin32MouseHook.h>

#include "Game/CGame.h"
#include "Graphics/CGraphics.h"
#include "Game/COffsets.h"
#include "Game/CPatches.h"
#include "Game/CHooks.h"
#include "Game/CCrashFixes.h"

#include "Network/CLocalPlayer.h"
#include "Game/Entity/CPlayerEntity.h"
#include "Game/Entity/CNetworkEntity.h"

#include <Network/CNetworkManager.h>
#include <Graphics/CSnapShot.h>

#include <General/CModuleManager.h>

#include <audio/CAudioManager.h>
#include "Game/EpisodeManager.h"
#include <Network/CHttpClient.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include <RakNet/RakNetStatistics.h>

class CGame;
class CCamera;

class CCore 
{
private:
	bool							m_bInitialized = false;
	unsigned						m_uiBaseAddress;
	unsigned						m_uiGameInitializeTime;

	CGame							* m_pGame = nullptr;
	CGraphics						* m_pGraphics = nullptr;
	CNetworkManager					* m_pNetworkManager = nullptr;
	CResourceManager				* m_pResourceManager = nullptr;

	CCamera							* m_pCamera = nullptr;
	CHttpClient						* m_pHttpClient = nullptr;
	CAudioManager					* m_pAudioManager = nullptr;

	CString							m_strServerName;
	BYTE							m_byteLoadingStyle = 0;

public:
									CCore();
									~CCore() { };							

	bool							Initialize();

	void							OnGameLoad();
	void							OnGameUpdate();

	void							OnDeviceCreate(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters);
	void							OnDeviceLost(IDirect3DDevice9 * pDevice);
	void							OnDeviceReset(IDirect3DDevice9 * pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters);
	void							OnDeviceRender(IDirect3DDevice9 * pDevice);

	unsigned						GetBase() { return m_uiBaseAddress; }

	void							SetServerName(CString strServerName) { m_strServerName = strServerName;  }
	CString							GetServerName() { return m_strServerName; }

	unsigned						GetGameLoadInitializeTime() { return m_uiGameInitializeTime; }

	const decltype(m_pGame) GetGame()
	{
		return m_pGame;
	}

	const decltype(m_pGraphics) GetGraphics()
	{
		return m_pGraphics;
	}

	const decltype(m_pAudioManager)	GetAudioManager()
	{
		return m_pAudioManager;
	}

	const decltype(m_pNetworkManager) GetNetworkManager()
	{
		return m_pNetworkManager;
	}

	const decltype(m_pResourceManager) GetResourceManager()
	{
		return m_pResourceManager;
	}

};

#endif // CCore_h