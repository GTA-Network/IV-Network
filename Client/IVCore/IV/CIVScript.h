//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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
	static void RequestModel(unsigned int model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REQUEST_MODEL, model); }
	static void ChangePlayerModel(unsigned int playerIndex, eModel model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CHANGE_PLAYER_MODEL, playerIndex, model); }
	static bool LocalPlayerIsReadyToStartPlaying() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_LOCAL_PLAYER_IS_READY_TO_START_PLAYING); }
	static void CreatePlayer(unsigned int playerId, float x, float y, float z, unsigned int *pPlayerIndex) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_PLAYER, playerId, x, y, z, pPlayerIndex); }
	static void MarkModelAsNoLongerNeeded(eModel model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_MARK_MODEL_AS_NO_LONGER_NEEDED, model); }
	static void MarkModelAsNoLongerNeeded(unsigned int model) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_MARK_MODEL_AS_NO_LONGER_NEEDED, model); }
	static bool HasModelLoaded(eModel model) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_HAS_MODEL_LOADED, model); }
	static bool HasModelLoaded(unsigned int model) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_HAS_MODEL_LOADED, model); }

	static void DoScreenFadeIn(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_IN, timeMS); }
	static void DoScreenFadeInUnhacked(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_IN_UNHACKED, timeMS); }
	static void DoScreenFadeOut(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_OUT, timeMS); }
	static void DoScreenFadeOutUnhacked(unsigned int timeMS) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DO_SCREEN_FADE_OUT_UNHACKED, timeMS); }

	static void AddExplosion(float x, float y, float z, unsigned int p3, float p4, unsigned int p5, unsigned int p6, float p7) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ADD_EXPLOSION, x, y, z, p3, p4, p5, p6, p7); }

	static bool IsScriptFireExtinguished(unsigned int fire) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_SCRIPT_FIRE_EXTINGUISHED, fire); }
	static unsigned int StartScriptFire(float x, float y, float z, unsigned char numGenerationsAllowed = 0, unsigned int strength = 1) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_START_SCRIPT_FIRE, x, y, z, numGenerationsAllowed, strength); }
	static void RemoveScriptFire(unsigned int fire) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REMOVE_SCRIPT_FIRE, fire); }

	// Player
	static void SetPlayerControl(unsigned int playerIndex, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_PLAYER_CONTROL, playerIndex, value); }
	static void SetPlayerControlAdvanced(unsigned int playerIndex, bool unknown1, bool unknown2, bool unknown3) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_PLAYER_CONTROL_ADVANCED, playerIndex, unknown1, unknown2, unknown3); }
	static void SetCameraControlsDisabledWithPlayerControls(bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS, value); }
	static unsigned int ConvertIntToPlayerIndex(unsigned int playerId) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CONVERT_INT_TO_PLAYERINDEX, playerId); }
	static unsigned int GetPlayerId() { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_PLAYER_ID); }
	static bool IsPlayerControlOn(unsigned int playerIndex) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_PLAYER_CONTROL_ON, playerIndex); }
	static bool IsInteriorScene() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_INTERIOR_SCENE); }
	static void SetDrawPlayerComponent(unsigned int p0, unsigned int p1) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_DRAW_PLAYER_COMPONENT, p0, p1); }
	static bool IsPlayerBeingArrested() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_PLAYER_BEING_ARRESTED); }
	static bool IsPlayerPlaying(unsigned int playerIndex) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_PLAYER_PLAYING, playerIndex); }
	static bool IsPlayerFreeForAmbientTask(unsigned int playerIndex) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_PLAYER_FREE_FOR_AMBIENT_TASK, playerIndex); }

	// Char
	static bool DoesCharExist(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_DOES_CHAR_EXIST, ped); }
	static void GiveWeaponToChar(unsigned int ped, eWeapon weapon, unsigned int ammo, bool unknown0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GIVE_WEAPON_TO_CHAR, ped, weapon, ammo, unknown0); }
	static void GiveWeaponToChar(unsigned int ped, unsigned int weapon, unsigned int ammo, bool unknown0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GIVE_WEAPON_TO_CHAR, ped, weapon, ammo, unknown0); }
	static void GetCharCoordinates(unsigned int ped, float *pX, float *pY, float *pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_COORDINATES, ped, pX, pY, pZ); }

	static bool IsCharInjured(unsigned int ped) { return false; }
	static bool IsCharInAnyCar(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_IN_ANY_CAR, ped); }
	static void BlockPedWeaponSwitching(unsigned int ped, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_BLOCK_PED_WEAPON_SWITCHING, ped, value); }
	static void UnlockRagdoll(unsigned int ped, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_UNLOCK_RAGDOLL, ped, value); }
	static void SetBlockingOfNonTemporaryEvents(unsigned int ped, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS, ped, value); }
	static void SetCharInvincible(unsigned int ped, bool enable) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_INVINCIBLE, ped, enable); }
	static void GetCharVelocity(unsigned int ped, float *pX, float *pY, float *pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_VELOCITY, ped, pX, pY, pZ); }
	static void WarpCharIntoCar(unsigned int ped, unsigned int vehicle) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_WARP_CHAR_INTO_CAR, ped, vehicle); }
	static void WarpCharIntoCarAsPassenger(unsigned int ped, unsigned int vehicle, unsigned int seatIndex) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_WARP_CHAR_INTO_CAR_AS_PASSENGER, ped, vehicle, seatIndex); }
	static void GetCharHeading(unsigned int ped, float *pValue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_HEADING, ped, pValue); }
	static void GetCharAnimCurrentTime(unsigned int ped, const char *animGroup, const char *animName, float *pValue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_ANIM_CURRENT_TIME, ped, animGroup, animName, pValue); }
	static bool IsPedRagdoll(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_PED_RAGDOLL, ped); }
	static void BlendFromNmWithAnim(unsigned int ped, const char* animGroup, const char* animName, unsigned int unknown, float XOffset, float YOffset, float ZOffset) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_BLEND_FROM_NM_WITH_ANIM, ped, animGroup, animName, unknown, XOffset, YOffset, ZOffset); }
	
	static unsigned int GetCurrentCharWeapon(unsigned int ped, eWeapon *pWeapon) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CURRENT_CHAR_WEAPON, ped, pWeapon); }
	static unsigned int GetCurrentCharWeapon(unsigned int ped, unsigned int *pWeapon) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CURRENT_CHAR_WEAPON, ped, pWeapon); }

	static void SetCharCollision(unsigned int ped, bool collision) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_COLLISION, ped, collision); }
	static void SetCarCollision(unsigned int vehicle, unsigned int collision) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_COLLISION, vehicle, collision); }
	static void SetCharHeading(unsigned int ped, float heading) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_HEADING, ped, heading); }
	static void ShakePad(unsigned int p0, unsigned int p1, unsigned int p2) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SHAKE_PAD, p0, p1, p2); }
	static void SetCharRotation(unsigned int ped, float pX, float pY, float pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_ROTATION, ped, pX, pY, pZ); }
	static void SetCharVelocity(unsigned int ped, float x, float y, float z) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_VELOCITY, ped, x, y, z); }
	static void GetCharHeightAboveGround(unsigned int ped, float *pValue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_HEIGHT_ABOVE_GROUND, ped, pValue); }
	static void GetPedBonePosition(unsigned int ped, ePedBone bone, float x, float y, float z, CVector3 *pPosition) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_PED_BONE_POSITION, ped, bone, x, y, z, pPosition); }
	static void GetPedBonePosition(unsigned int ped, unsigned int bone, float x, float y, float z, CVector3 *pPosition) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_PED_BONE_POSITION, ped, bone, x, y, z, pPosition); }
	static bool IsCharInWater(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_IN_WATER, ped); }
	static void ClearCharTasksImmediately(unsigned int ped) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CLEAR_CHAR_TASKS_IMMEDIATELY, ped); }
	static void GetCharHealth(unsigned int ped, unsigned int *pHealth) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_HEALTH, ped, pHealth); }
	static unsigned int SwitchPedToRagdoll(unsigned int ped, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SWITCH_PED_TO_RAGDOLL, ped, p1, p2, p3, p4, p5, p6); }  
	static void SetCharHealth(unsigned int ped, unsigned int health) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_HEALTH, ped, health); }
	static void ClearCharSecondaryTask(unsigned int ped) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CLEAR_CHAR_SECONDARY_TASK, ped); }
	static bool IsCharOnFire(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_ON_FIRE, ped); }
	static bool IsCharInAnyHeli(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_IN_ANY_HELI, ped); }
	static void SetCharVisible(unsigned int ped, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_VISIBLE, ped, value); }
	static void WarpCharFromCarToCoord(unsigned int ped, float x, float y, float z) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_WARP_CHAR_FROM_CAR_TO_COORD, ped, x, y, z); }
	static void AttachPedToCar(unsigned int ped, unsigned int vehicle, unsigned int unknown0_0, float offsetX, float offsetY, float offsetZ, float unknown1_276, float unknown2_0, unsigned int unknown3_0, unsigned int unknown4_0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ATTACH_PED_TO_CAR, ped, vehicle, unknown0_0, offsetX, offsetY, offsetZ, unknown1_276, unknown2_0, unknown3_0, unknown4_0); }
	static bool IsCharOnAnyBike(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_ON_ANY_BIKE, ped); }
	static void GetOffsetFromCharInWorldCoords(unsigned int ped, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS, ped, x, y, z, pOffX, pOffY, pOffZ); }
	static bool IsCharVisible(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_VISIBLE, ped); }
	static bool IsCharGettingUp(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_GETTING_UP, ped); }
	static bool HasCharGotWeapon(unsigned int ped, eWeapon weapon) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_HAS_CHAR_GOT_WEAPON, ped, weapon); }
	static bool HasCharGotWeapon(unsigned int ped, unsigned int weapon) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_HAS_CHAR_GOT_WEAPON, ped, weapon); }
	static void RemoveWeaponFromChar(unsigned int ped, eWeapon weapon) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REMOVE_WEAPON_FROM_CHAR, ped, weapon); }
	static void RemoveWeaponFromChar(unsigned int ped, unsigned int weapon) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REMOVE_WEAPON_FROM_CHAR, ped, weapon); }
	static void GetPlayerChar(unsigned int playerIndex, unsigned int *pPed) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_PLAYER_CHAR, playerIndex, pPed); }
	static unsigned int GetCharDrawableVariation(unsigned int ped, ePedComponent component) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_DRAWABLE_VARIATION, ped, component); }
	static void SetCharComponentVariation(unsigned int ped, ePedComponent component, unsigned int modelVariation, unsigned int textureVariation) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_COMPONENT_VARIATION, ped, component, modelVariation, textureVariation); }
	static unsigned int GetCharDrawableVariation(unsigned int ped, unsigned int component) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_DRAWABLE_VARIATION, ped, component); }
	static void SetCharComponentVariation(unsigned int ped, unsigned int component, unsigned int modelVariation, unsigned int textureVariation) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_COMPONENT_VARIATION, ped, component, modelVariation, textureVariation); }
	static unsigned int GetObjectPedIsHolding(unsigned int ped) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_OBJECT_PED_IS_HOLDING, ped); }

	// Camera
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
	static void CountScriptCams(unsigned int *pCount) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_COUNT_SCRIPT_CAMS, pCount); }
	static void SetGameCameraControlsActive(unsigned int camera, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_GAME_CAMERA_CONTROLS_ACTIVE, camera, value); }
	static void GetGameCam(unsigned int *camera) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_GAME_CAM, camera); }
	static void GetCamRot(unsigned int camera, float *angleX, float *angleY, float *angleZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CAM_ROT, camera, angleX, angleY, angleZ); }
	static void GetCamFov(unsigned int camera, float *fov) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CAM_FOV, camera, fov); }
	static void SetCamMotionBlur(unsigned int camera, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_MOTION_BLUR, camera, value); }
	static void AttachCamToPed(unsigned int camera, unsigned int ped) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ATTACH_CAM_TO_PED, camera, ped); }
	static void SetCamAttachOffset(unsigned int camera, float pX, float pY, float pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_ATTACH_OFFSET, camera, pX, pY, pZ); }
	static void SetCamAttachOffsetIsRelative(unsigned int camera, bool isRelative) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_ATTACH_OFFSET_IS_RELATIVE, camera, isRelative); }
	static void PointCamAtPed(unsigned int cam, unsigned int ped) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_POINT_CAM_AT_PED, cam, ped); }
	static void SetCamPointOffset(unsigned int camera, float fX, float fY, float fZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_POINT_OFFSET, camera, fX, fY, fZ); }
	static void SetCamPointOffsetIsRelative(unsigned int camera, bool isRelative) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_POINT_OFFSET_IS_RELATIVE, camera, isRelative); }
	static void UnattachCam(unsigned int camera) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_UNATTACH_CAM, camera); }
	static void UnpointCam(unsigned int camera) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_UNPOINT_CAM, camera); }
	static void GenerateRandomFloatInRange(float min, float max, float *pValue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GENERATE_RANDOM_FLOAT_IN_RANGE, min, max, pValue); }
	static void SetCamFov(unsigned int camera, float fov) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAM_FOV, camera, fov); }

	// Blip
	static void AddBlipForChar(unsigned int ped, unsigned int *pBlip) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ADD_BLIP_FOR_CHAR, ped, pBlip); }
	static void ChangeBlipSprite(unsigned int blip, eBlipSprite sprite) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CHANGE_BLIP_SPRITE, blip, sprite); }
	static void ChangeBlipScale(unsigned int blip, float scale) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CHANGE_BLIP_SCALE, blip, scale); }
	static void ChangeBlipNameFromAscii(unsigned int blip, const char *blipName) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CHANGE_BLIP_NAME_FROM_ASCII, blip, blipName); }
	static void SetCharCoordinatesNoOffset(unsigned int ped, float x, float y, float z) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CHAR_COORDINATES_NO_OFFSET, ped, x, y, z); }
	static void RemoveBlip(unsigned int blip) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REMOVE_BLIP, blip); }
	static void ChangeBlipColour(unsigned int blip, unsigned int colour) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CHANGE_BLIP_COLOUR, blip, colour); }

	// Vehicle
	static void CreateCar(unsigned int nameHash, float x, float y, float z, unsigned int *pVehicle, bool unknownTrue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_CAR, nameHash, x, y, z, pVehicle, unknownTrue); }
	static void SetCarCanBeDamaged(unsigned int vehicle, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_CAN_BE_DAMAGED, vehicle, value); }
	static void SetCarCanBeVisiblyDamaged(unsigned int vehicle, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_CAN_BE_VISIBLY_DAMAGED, vehicle, value); }
	static void DeleteCar(unsigned int *pVehicle) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DELETE_CAR, pVehicle); }
	static void SetCarCoordinates(unsigned int vehicle, float pX, float pY, float pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_COORDINATES, vehicle, pX, pY, pZ); }
	static void FixCar(unsigned int vehicle) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_FIX_CAR, vehicle); }
	static void SetCarHeading(unsigned int vehicle, float dir) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_HEADING, vehicle, dir); }
	static void SetCarCoordinatesNoOffset(unsigned int vehicle, float x, float y, float z) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_COORDINATES_NO_OFFSET, vehicle, x, y, z); }
	static void SetCarLivery(unsigned int vehicle, int livery) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_LIVERY, vehicle, livery); }
	static void GetCarLivery(unsigned int vehicle, int* livery) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CAR_LIVERY, vehicle, livery); }
	static void LockCarDoor(unsigned int vehicle, int flag) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_LOCK_CAR_DOORS, vehicle, flag); }
	static void SetTaxiLights(unsigned int vehicle, bool toggle) { CIVScript_NativeInvoke::Invoke<unsigned int>( NATIVE_SET_TAXI_LIGHTS, vehicle, toggle); }
	static void ForceCarLights(unsigned int vehicle, int flag) { CIVScript_NativeInvoke::Invoke<unsigned int>( NATIVE_FORCE_CAR_LIGHTS, vehicle, flag); }
	static void ControlCarDoor(unsigned int vehicle, eVehicleDoor door, unsigned int unknown_maybe_open, float angle) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CONTROL_CAR_DOOR, vehicle, door, unknown_maybe_open, angle); }
	static void ControlCarDoor(unsigned int vehicle, unsigned int door, unsigned int unknown_maybe_open, float angle) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CONTROL_CAR_DOOR, vehicle, door, unknown_maybe_open, angle); }
	static void OpenCarDoor(unsigned int vehicle, eVehicleDoor door) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_OPEN_CAR_DOOR, vehicle, door); }
	static void ShutCarDoor(unsigned int vehicle, eVehicleDoor door) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SHUT_CAR_DOOR, vehicle, door); }
	static bool IsVehDriveable(unsigned int vehicle) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_VEH_DRIVEABLE, vehicle); }
	static void MarkCarAsNoLongerNeeded(unsigned int *pVehicle) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_MARK_CAR_AS_NO_LONGER_NEEDED, pVehicle); }
	static void GetCarSpeedVector(unsigned int vehicle, CVector3 *pVector, bool unknownFalse) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CAR_SPEED_VECTOR, vehicle, pVector, unknownFalse); }
	static void GetCarHeading(unsigned int vehicle, float *pValue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CAR_HEADING, vehicle, pValue); }
	static unsigned int GetClosestCar(float x, float y, float z, float radius, unsigned int unknown0_0, unsigned int unknown1_70) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CLOSEST_CAR, x, y, z, radius, unknown0_0, unknown1_70); }
	static bool DoesVehicleExist(unsigned int vehicle) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_DOES_VEHICLE_EXIST, vehicle); }
	static void GetCarSpeed(unsigned int vehicle, float *pValue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CAR_SPEED, vehicle, pValue); }
	static void StoreCarCharIsInNoSave(unsigned int p0, unsigned int p1) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_STORE_CAR_CHAR_IS_IN_NO_SAVE, p0, p1); }
	static bool IsCarAMissionCar(unsigned int vehicle) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CAR_A_MISSION_CAR, vehicle); }
	static void SetCarAsMissionCar(unsigned int vehicle) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_CAR_AS_MISSION_CAR, vehicle); }
	static void GetOffsetFromCarInWorldCoords(unsigned int vehicle, float x, float y, float z, float *pOffX, float *pOffY, float *pOffZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS, vehicle, x, y, z, pOffX, pOffY, pOffZ); }
	static bool IsCarInAirProper(unsigned int vehicle) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CAR_IN_AIR_PROPER, vehicle); }

	// Sound
	static unsigned int RequestAmbientAudioBank(const char* szAudio) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REQUEST_AMBIENT_AUDIO_BANK, szAudio); }
	static void StopSound(unsigned int sound) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_STOP_SOUND, sound); }
	static void ReleaseSoundId(unsigned int sound) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_RELEASE_SOUND_ID, sound); }
	static void PlaySoundFromPed(unsigned int ped, eSound sound, unsigned int unknown) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_PLAY_SOUND_FROM_PED, ped, sound, unknown); }
	static void PlaySoundFromPed(unsigned int ped, unsigned int sound, unsigned int unknown) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_PLAY_SOUND_FROM_PED, ped, sound, unknown); }

	static void PlaySoundFromPed(int SoundId, char *SoundName, unsigned int ped) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_PLAY_SOUND_FROM_PED, SoundId, SoundName, ped); }

	static eSound GetSoundId() { return CIVScript_NativeInvoke::Invoke<eSound>(NATIVE_GET_SOUND_ID); }
	static unsigned int GetSoundId2() { return CIVScript_NativeInvoke::Invoke<eSound>(NATIVE_GET_SOUND_ID); }
	static void SetVariableOnSound(eSound sound, char *varname, float value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_VARIABLE_ON_SOUND, sound, varname, value); }
	static void SetVariableOnSound(unsigned int sound, char *varname, float value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_VARIABLE_ON_SOUND, sound, varname, value); }

	// Object
	static bool DoesObjectExist(unsigned int obj) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_DOES_OBJECT_EXIST, obj); }
	static void DetachObject(unsigned int obj, bool unknown) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DETACH_OBJECT, obj, unknown); }
	static void DeleteObject(unsigned int *pObj) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DELETE_OBJECT, pObj); }
	static void CreateObject(eModel model, float x, float y, float z, unsigned int *pObj, bool unknownTrue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_OBJECT, model, x, y, z, pObj, unknownTrue); }
	static void CreateObject(unsigned int model, float x, float y, float z, unsigned int *pObj, bool unknownTrue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_OBJECT_NO_OFFSET, model, x, y, z, pObj, unknownTrue); }
	static void AttachObjectToPed(unsigned int obj, unsigned int c, ePedBone bone, float pX, float pY, float pZ, float rX, float rY, float rZ, unsigned int unknown1_0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ATTACH_OBJECT_TO_PED, obj, c, bone, pX, pY, pZ, rX, rY, rZ, unknown1_0); }
	static void AttachObjectToPed(unsigned int obj, unsigned int c, unsigned int bone, float pX, float pY, float pZ, float rX, float rY, float rZ, unsigned int unknown1_0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ATTACH_OBJECT_TO_PED, obj, c, bone, pX, pY, pZ, rX, rY, rZ, unknown1_0); }
	static void AttachObjectToPedPhysic(unsigned int obj, unsigned int c, bool bUnkown, unsigned int uiUnkown, float pX, float pY, float pZ, float rX, float rY, float rZ, float fUnkown1, float fUnkown2) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ATTACH_OBJECT_TO_PED_PHYSICALLY, obj, c, bUnkown, uiUnkown, pX, pY, pZ, rX, rY, rZ, fUnkown1, fUnkown2); }
	static unsigned int PlayObjectAnim(unsigned int object, const char* animGroup, const char* animName, float speed, int loop, int ms) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_PLAY_OBJECT_ANIM, object, animGroup, animName, speed, loop, ms); }
	static unsigned int IsObjectPlayingAnim(unsigned int object, const char* animGroup, const char* animName) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_IS_OBJECT_PLAYING_ANIM, object, animGroup, animName); }
	static void SetObjectCollision(unsigned int obj, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_OBJECT_COLLISION, obj, value); }
	static void SetObjectDynamic(unsigned int object, bool dynamic) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_OBJECT_DYNAMIC, object, dynamic); }
	static void GetObjectCoordinates(unsigned int obj, float *pX, float *pY, float *pZ) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_OBJECT_COORDINATES, obj, pX, pY, pZ); }
	static unsigned int SlideObject(unsigned int objectIndex, float pX, float pY, float pZ, float rX, float rY, float rZ, float speed) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SLIDE_OBJECT, objectIndex, pX, pY, pZ, rX, rY, rZ, speed); }
	static void SetObjectAlpha(unsigned int object, float alpha) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_OBJECT_ALPHA, object, alpha); }
	static bool IsObjectAttached(unsigned int object) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_OBJECT_ATTACHED, object); }
	static void FreezeObjectPosition(unsigned int obj, bool frozen) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_FREEZE_OBJECT_POSITION, obj, frozen); }
	static void GetObjectAnimCurrentTime(unsigned int object, const char* animName0, const char* animName1, float* pTime) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_OBJECT_ANIM_CURRENT_TIME, object, animName0, animName1, pTime); }
	static void CreateObjectNoOffset(eModel model, float x, float y, float z, unsigned int *pObj, bool unknownTrue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_OBJECT_NO_OFFSET, model, x, y, z, pObj, unknownTrue); }
	static void CreateObjectNoOffset(unsigned int model, float x, float y, float z, unsigned int *pObj, bool unknownTrue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_OBJECT_NO_OFFSET, model, x, y, z, pObj, unknownTrue); }
	static void SetObjectVisible(unsigned int obj, bool value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_OBJECT_VISIBLE, obj, value); }
	static void SetActivateObjectPhysicsAsSoonAsItIsUnfrozen(unsigned int object, unsigned int physics) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_, object, physics); }

	// Animation
	static bool IsCharPlayingAnim(unsigned int ped, char *animSet, char *animName) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CHAR_PLAYING_ANIM, ped, animSet, animName); }
	static void SwitchPedToAnimated(unsigned int ped, bool unknownTrue) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SWITCH_PED_TO_ANIMATED, ped, unknownTrue); }
	static void TaskPlayAnimNonInterruptable(unsigned int ped, const char *animSequence, const char *animName, float speed, int loop, float x, float y, float z, int ms) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_TASK_PLAY_ANIM_NON_INTERRUPTABLE, ped, animSequence, animName, speed, loop, x, y, z, ms); }
	static void TaskPlayAnimWithFlags(unsigned int ped, char *animName, char *animSet, float unknown0_8, unsigned int unknown1_0, unsigned int flags) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_TASK_PLAY_ANIM_WITH_FLAGS, ped, animName, animSet, unknown0_8, unknown1_0, flags); }
	static void TaskPlayAnim(unsigned int ped, const char *animSequence, const char *animName, float speed, int loop, float x, float y, float z, int ms) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_TASK_PLAY_ANIM, ped, animSequence, animName, speed, loop, x, y, z, ms); }
	static bool HaveAnimsLoaded(const char *animName) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_HAVE_ANIMS_LOADED, animName); }
	static void RequestAnims(const char *animName) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REQUEST_ANIMS, animName); }
	static void RemoveAnims(const char *animName) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REMOVE_ANIMS, animName); }

	// General / Other
	static bool IsControlJustPressed(unsigned int p0, unsigned int p1) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CONTROL_JUST_PRESSED, p0, p1); }
	static unsigned int GetGroundZFor3DCoord(float x, float y, float z, float *pGroundZ) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_GROUND_Z_FOR_3D_COORD, x, y, z, pGroundZ); }
	static float DoABSF(float value) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ABSF, value); }
	static void GetGameTimer(unsigned int *pTimer) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_GAME_TIMER, pTimer); }
	static unsigned int Round(unsigned int value) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ROUND, value); }
	static void GetFrameTime(float *time) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_FRAME_TIME, time); }
	static float ToFloat(unsigned int value) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_TO_FLOAT, value); }
	static unsigned int DoABSI(unsigned int value) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ABSI, value); }
	static void ClearHelp() { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CLEAR_HELP); }
	static unsigned int IsThisHelpMessageBeingDisplayed(unsigned int messageId) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED, messageId); }
	static void PrintHelp(const char *gxtName) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_PRINT_HELP, gxtName); }
	static bool IsControlPressed(unsigned int p0, unsigned int p1) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_CONTROL_PRESSED, p0, p1); }
	static void SetFollowPedPitchLimitDown(unsigned int p0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_FOLLOW_PED_PITCH_LIMIT_DOWN, p0); }
	static unsigned int DoVDIST2(float x0, float y0, float z0, float x1, float y1, float z1) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_VDIST2, x0, y0, z0, x1, y1, z1); }
	static unsigned int IsUsingStandardControls() { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_USING_STANDARD_CONTROLS); }
	static unsigned int DoFloor(float value) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_FLOOR, value); }
	static float GetFloatStat(eFloatStatistic stat) { return CIVScript_NativeInvoke::Invoke<float>(NATIVE_GET_FLOAT_STAT, stat); }
	static void SetFloatStat(eFloatStatistic stat, float value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_FLOAT_STAT, stat, value); }
	static float GetFloatStat(unsigned int stat) { return CIVScript_NativeInvoke::Invoke<float>(NATIVE_GET_FLOAT_STAT, stat); }
	static void SetFloatStat(unsigned int stat, float value) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_FLOAT_STAT, stat, value); }
	static float DoATAN2(float val1, float val2) { return CIVScript_NativeInvoke::Invoke<float>(NATIVE_ATAN2, val1, val2); }
	static bool IsButtonJustPressed(unsigned int padIndex, ePadButton button) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_BUTTON_JUST_PRESSED, padIndex, button); }
	static bool IsButtonJustPressed(unsigned int padIndex, unsigned int button) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_BUTTON_JUST_PRESSED, padIndex, button); }
	static void CreateNmMessage(unsigned int p0, unsigned int p1) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_NM_MESSAGE, p0, p1); }
	static void SendNmMessage(unsigned int p0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SEND_NM_MESSAGE, p0); }
	static void GetPositionOfAnalogueSticks(unsigned int padIndex, unsigned int *pLeftX, unsigned int *pLeftY, unsigned int *pRightX, unsigned int *pRightY) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_POSITION_OF_ANALOGUE_STICKS, padIndex, pLeftX, pLeftY, pRightX, pRightY); }
	static int GetControlValue(unsigned int p0, unsigned int p1) { return CIVScript_NativeInvoke::Invoke<int>(NATIVE_GET_CONTROL_VALUE, p0, p1); }
	static int GetKeyboardMoveInput(unsigned int p0, unsigned int p1) { return CIVScript_NativeInvoke::Invoke<int>(NATIVE_GET_KEYBOARD_MOVE_INPUT, p0, p1); }
	static bool IsHelpMessageBeingDisplayed() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_HELP_MESSAGE_BEING_DISPLAYED); }
	static bool HasScriptLoaded(const char *scriptName) { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_HAS_SCRIPT_LOADED, scriptName); }
	static void	RequestScript(const char *scriptName) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REQUEST_SCRIPT, scriptName); }
	static void StartNewScript(const char *scriptName, int size) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_START_NEW_SCRIPT, scriptName, size); }
	static bool IsScreenFadedIn() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_SCREEN_FADED_IN); }
	static bool IsScreenFadedOut() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_SCREEN_FADED_OUT); }
	static bool IsHUDPreferenceSwitchedOn() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_IS_HUD_PREFERENCE_SWITCHED_ON); }
	static bool AreWidescreenBordersActive() { return CIVScript_NativeInvoke::Invoke<bool>(NATIVE_ARE_WIDESCREEN_BORDERS_ACTIVE); }
	static void ScriptAssert(unsigned int p0) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SCRIPT_ASSERT, p0); }

	// Task
	static void OpenSequenceTask(unsigned int *pTaskSequence) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_OPEN_SEQUENCE_TASK, pTaskSequence); }
	static void CloseSequenceTask(unsigned int taskSequence) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CLOSE_SEQUENCE_TASK, taskSequence); }
	static void TaskPerformSequence(unsigned int ped, unsigned int taskSequence) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_TASK_PERFORM_SEQUENCE, ped, taskSequence); }
	static void ClearSequenceTask(unsigned int taskSequence) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CLEAR_SEQUENCE_TASK, taskSequence); }
	static void ClearCharTasks(unsigned int ped) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CLEAR_CHAR_TASKS, ped); }

	static void AddScore(unsigned int playerIndex, int score) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ADD_SCORE, playerIndex, score); }
	static void AllowPlayerToCarryNonMissionObjects(unsigned int playerIndex, bool allow) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ALLOW_PLAYER_TO_CARRY_NON_MISSION_OBJECTS, playerIndex, allow); }

	// 
	static void AllocateScriptToObject(const char* p0, unsigned int p1, unsigned int p2, float p3, int p4) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ALLOCATE_SCRIPT_TO_OBJECT, p0, p1, p2, p3, p4); }
    static void AllocateScriptToRandomPed(const char* p0, unsigned int p1, int p2, int p3) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ALLOCATE_SCRIPT_TO_RANDOM_PED, p0, p1, p2, p3); }
	static void RegisterWorldPointScriptBrain(const char* p0, float p1) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_REGISTER_WORLD_POINT_SCRIPT_BRAIN, p0, p1); }

	static unsigned int GetNumberOfCharDrawableVariations(unsigned int ped, ePedComponent component) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_NUMBER_OF_CHAR_DRAWABLE_VARIATIONS, ped, component); }
    static unsigned int GetNumberOfCharTextureVariations(unsigned int ped, ePedComponent component, unsigned int unknown1) { return CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_NUMBER_OF_CHAR_TEXTURE_VARIATIONS, ped, component, unknown1); }

	static void TaskAimGunAtCoord(unsigned int ped, float tX, float tY, float tZ, unsigned int duration) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_TASK_AIM_GUN_AT_COORD, ped, tX, tY, tZ, duration); }
	static void TaskShootAtCoord(unsigned int ped, float x, float y, float z, unsigned int p4, unsigned int p5) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_TASK_SHOOT_AT_COORD, ped, x, y, z, p4, p5); }
	
	// unsigned int
    static void CreateMissionTrain(unsigned int unknown1, float x, float y, float z, bool unknown2, unsigned int *pTrain) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_CREATE_MISSION_TRAIN, unknown1, x, y, z, unknown2, pTrain); }
    static void DeleteMissionTrain(unsigned int *pTrain) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DELETE_MISSION_TRAIN, pTrain); }
    static eTrainStation GetCurrentStationForTrain(unsigned int train) { return CIVScript_NativeInvoke::Invoke<eTrainStation>(NATIVE_GET_CURRENT_STATION_FOR_TRAIN, train); }
    static eTrainStation GetNextStationForTrain(unsigned int train) { return CIVScript_NativeInvoke::Invoke<eTrainStation>(NATIVE_GET_NEXT_STATION_FOR_TRAIN, train); }
    static const char *GetStationName(unsigned int train, eTrainStation station) { return CIVScript_NativeInvoke::Invoke<const char *>(NATIVE_GET_STATION_NAME, train, station); }
    static void MarkMissionTrainAsNoLongerNeeded(unsigned int train) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED, train); }
    static void MarkMissionTrainsAsNoLongerNeeded() { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_MARK_MISSION_TRAINS_AS_NO_LONGER_NEEDED); }
    static void SetTrainCuriseSpeed(unsigned int train, float fSpeed) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_TRAIN_CRUISE_SPEED, train, fSpeed); }
	static void SetTrainSpeed(unsigned int train, float fSpeed) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_TRAIN_SPEED, train, fSpeed); }

	static void DrawRect(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_DRAW_RECT, p0, p1, p2, p3, p4, p5, p6, p7); }

	static void GetCharArmour(unsigned int ped, unsigned int *pArmour) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GET_CHAR_ARMOUR, ped, pArmour); }
	static void AddCharArmour(unsigned int ped, unsigned int pArmour) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_ADD_ARMOUR_TO_CHAR, ped, pArmour); }

	static void SetFakeWantedLevel(unsigned int pLevel) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_FAKE_WANTED_LEVEL, pLevel); }

	static void SetMaxWantedLevel(int iMaxWantedLevel) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_MAX_WANTED_LEVEL, iMaxWantedLevel); }
	static void SetWantedMultiplier(float fMulti) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_WANTED_MULTIPLIER, fMulti); }
	
	static void LoadAllObjectsNow(bool bunknown) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_LOAD_ALL_OBJECTS_NOW, bunknown); }

	static void GivePedFakeNetworkName(unsigned int ped, const char* pnick, CColor color) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_GIVE_PED_FAKE_NETWORK_NAME, ped, pnick, color.A, color.R, color.G, color.B); }

	static unsigned int GetViewportPositionOfCoord(CVector3 * vecWordPosition, Vector2 * vecViewportPosition, int type) { float fX; float fY; unsigned int ret = CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_GET_VIEWPORT_POSITION_OF_COORD, vecWordPosition->fX, vecWordPosition->fY, vecWordPosition->fZ, type, &fX, &fY); vecViewportPosition->fX = fX; vecViewportPosition->fY = fY; return ret; } //types: 2: on screen pos

	static void SetPlayerControlForTextChat(unsigned int playerIndex, bool state) { CIVScript_NativeInvoke::Invoke<unsigned int>(NATIVE_SET_PLAYER_CONTROL_FOR_TEXT_CHAT, playerIndex, state); }
};

#endif // CIVScript_h