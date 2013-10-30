//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVStartupScript.cpp
// Project: Client.Core
// Author: balika011 <balika011@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include <CCore.h>
#include "CIVStartupScript.h"
#include "CIVScript.h"

extern	CCore				* g_pCore;

void CIVStartupScript::Process()
{
	unsigned int pid = 0;
	CIVScript::CreatePlayer(0, DEFAULT_SPAWN_POSITION, &pid);

	//disable police
	CIVScript::SetMaxWantedLevel(0);
	CIVScript::SetWantedMultiplier(0.0f);

	g_pCore->OnGameLoad();
	g_pCore->SetClientState(GAME_STATE_INGAME);
}