//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: Scripting.h
// Project: Client.Core
// Author(s): aru
//            jenksta
//            Einstein
// License: See LICENSE in root directory
//          Contains zlib licensed code from ScriptHook by aru
//
//==============================================================================

#pragma once

#include "CIVScript_FunctionInvoke.h"
#include "CIVScriptEnums.h"
#include "CIVScript_FunctionList.h"

namespace CIVScript
{
	static void RequestModel(eModel model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REQUEST_MODEL, model); }
	static void ChangePlayerModel(unsigned int playerIndex, eModel model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CHANGE_PLAYER_MODEL, playerIndex, model); }
	static bool LocalPlayerIsReadyToStartPlaying() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_LOCAL_PLAYER_IS_READY_TO_START_PLAYING); }
	static void CreatePlayer(unsigned int playerId, float x, float y, float z, unsigned int *pPlayerIndex) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_PLAYER, playerId, x, y, z, pPlayerIndex); }
}
