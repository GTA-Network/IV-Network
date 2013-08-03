//========== IV:Multiplayer - https://github.com/XForce/ivmultiplayer ==========
//
// File: CIVScript.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CIVScript_h
#define CIVScript_h

#include "CIVScript_FunctionInvoke.h"
#include "CIVScriptEnums.h"
#include "CIVScript_FunctionList.h"

namespace CIVScript
{
	static void RequestModel(eModel model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REQUEST_MODEL, model); }
	static void ChangePlayerModel(unsigned int playerIndex, eModel model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CHANGE_PLAYER_MODEL, playerIndex, model); }
	static bool LocalPlayerIsReadyToStartPlaying() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_LOCAL_PLAYER_IS_READY_TO_START_PLAYING); }
	static void CreatePlayer(unsigned int playerId, float x, float y, float z, unsigned int *pPlayerIndex) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_PLAYER, playerId, x, y, z, pPlayerIndex); }
	
	static void DoScreenFadeIn(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_IN, timeMS); }
	static void DoScreenFadeInUnhacked(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_IN_UNHACKED, timeMS); }
	static void DoScreenFadeOut(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_OUT, timeMS); }
	static void DoScreenFadeOutUnhacked(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_OUT_UNHACKED, timeMS); }
};

#endif // CIVScript_h
