//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
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

	static void AddExplosion(float x, float y, float z, unsigned int p3, float p4, unsigned int p5, unsigned int p6, float p7) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ADD_EXPLOSION, x, y, z, p3, p4, p5, p6, p7); }
	
	static bool IsScriptFireExtinguished(unsigned int fire) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_SCRIPT_FIRE_EXTINGUISHED, fire); }
	static unsigned int StartScriptFire(float x, float y, float z, unsigned char numGenerationsAllowed = 0, unsigned int strength = 1) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_START_SCRIPT_FIRE, x, y, z, numGenerationsAllowed, strength); }
	static void RemoveScriptFire(unsigned int fire) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REMOVE_SCRIPT_FIRE, fire); }

	static void SetPlayerControl(unsigned int playerIndex, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_PLAYER_CONTROL, playerIndex, value); }
	static void SetPlayerControlAdvanced(unsigned int playerIndex, bool unknown1, bool unknown2, bool unknown3) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_PLAYER_CONTROL_ADVANCED, playerIndex, unknown1, unknown2, unknown3); }
	static void SetCameraControlsDisabledWithPlayerControls(bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS, value); }
	
	static void CreateCam(unsigned int camtype_usually14, unsigned int *camera) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_CAM, camtype_usually14, camera); }
    static void DestroyCam(unsigned int camera) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DESTROY_CAM, camera); }
    static bool DoesCamExist(unsigned int camera) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_DOES_CAM_EXIST, camera); }
    static void SetCamActive(unsigned int camera, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_ACTIVE, camera, value); }
	static void ActivateScriptedCams(int unknown1_1, int unknown2_1) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ACTIVATE_SCRIPTED_CAMS, unknown1_1, unknown2_1); }
    static void PointCamAtCoord(unsigned int cam, float pX, float pY, float pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_POINT_CAM_AT_COORD, cam, pX, pY, pZ); }
	static void GetCamPos(unsigned int camera,  float *pX, float *pY, float *pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CAM_POS, camera, pX, pY, pZ); }
	static void SetCamBehindPed(unsigned int ped) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_BEHIND_PED, ped); }
	static void SetCamPos(unsigned int camera, float pX, float pY, float pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_POS, camera, pX, pY, pZ); }
	static void SetCamPropagate(unsigned int camera, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_PROPAGATE, camera, value); }
};

#endif // CIVScript_h
