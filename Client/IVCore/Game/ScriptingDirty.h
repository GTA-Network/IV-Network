//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: ScriptingDirty.h
// Project: Client.Core
// Author(s): aru
// License: Contains zlib licensed code from ScriptHook by aru
//
//==============================================================================


#pragma once

// NOTE: Don't include or use this file! 

// The function definitions in this file were generated using a script and thus do not have proper
// function signatures.

// Move the definitions out of here into Scripting.h and clean up the parameter/return types to 
// proper C++ types. Remember to only use 32-bit or smaller types -- don't use double/f64 (use 
// the lower precision f32 instead), and don't use structs that are larger than 4 bytes.

namespace ScriptingDirty
{

// Wanted to cleanup, but couldn't find params

	static unsigned int GetEpisodeName(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_EPISODE_NAME", p0); }
	static unsigned int GetLeftPlayerCashToReachLevel(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_LEFT_PLAYER_CASH_TO_REACH_LEVEL", p0); }
	static unsigned int GetNumberLinesWithSubstrings(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("GET_NUMBER_LINES_WITH_SUBSTRINGS", p0, p1, p2, p3, p4); }
	static bool HasPlayerCollectedPickup(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<bool>("HAS_PLAYER_COLLECTED_PICKUP", p0, p1); }
	static void GetCurrentDate(unsigned int *pUnknown1, unsigned int *pUnknown2) { NativeInvoke::Invoke<unsigned int>("GET_CURRENT_DATE", pUnknown1, pUnknown2); }
	static void GetPedGroupIndex(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_PED_GROUP_INDEX", p0, p1); }
	static void RenderWeaponPickupsBigger(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RENDER_WEAPON_PICKUPS_BIGGER", p0); }


// Interesting ones to cleanup:

	static void GetPedBonePosition(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("GET_PED_BONE_POSITION", p0, p1, p2, p3, p4, p5); }
	static void GetRandomCarBackBumperInSphere(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("GET_RANDOM_CAR_BACK_BUMPER_IN_SPHERE", p0, p1, p2, p3, p4, p5, p6); }
	static void GetRandomCarFrontBumperInSphereNoSave(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("GET_RANDOM_CAR_FRONT_BUMPER_IN_SPHERE_NO_SAVE", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void GetRandomCarInSphere(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("GET_RANDOM_CAR_IN_SPHERE", p0, p1, p2, p3, p4, p5, p6); }
	static void GetRandomCarInSphereNoSave(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("GET_RANDOM_CAR_IN_SPHERE_NO_SAVE", p0, p1, p2, p3, p4, p5, p6); }
	static void GetRandomCharInAreaOffsetNoSave(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int GetStatFrontEndVisibility(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_STAT_FRONTEND_VISIBILITY", p0); }
	static unsigned int GetStringFromString(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("GET_STRING_FROM_STRING", p0, p1, p2); }
	static unsigned int GetStringWidth(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_STRING_WIDTH", p0); }
	static unsigned int GetStringWidthWithNumber(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("GET_STRING_WIDTH_WITH_NUMBER", p0, p1); }
	static unsigned int GetStringWidthWithString(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("GET_STRING_WIDTH_WITH_STRING", p0, p1); }
	static void GetTimeOfDay(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_TIME_OF_DAY", p0, p1); }
	static unsigned int GetTimeTilNextStation(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_TIME_TIL_NEXT_STATION", p0); }
	static void GetTrainCaboose(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_TRAIN_CABOOSE", p0, p1); }
	static void GetTrainCarriage(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("GET_TRAIN_CARRIAGE", p0, p1, p2); }
	static void GetTrainPlayerWouldEnter(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_TRAIN_PLAYER_WOULD_ENTER", p0, p1); }
	static void GetVehicleDirtLevel(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_VEHICLE_DIRT_LEVEL", p0, p1); }
	static void GetVehicleQuaternion(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("GET_VEHICLE_QUATERNION", p0, p1, p2, p3, p4); }
	static unsigned int GetWaterHeight(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("GET_WATER_HEIGHT", p0, p1, p2, p3); }
	static unsigned int GetWaterHeightNoWaves(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("GET_WATER_HEIGHT_NO_WAVES", p0, p1, p2, p3); }
	static void GetWeaponTypeModel(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_WEAPONTYPE_MODEL", p0, p1); }
	static void GetWeaponTypeSlot(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_WEAPONTYPE_SLOT", p0, p1); }
	static void GiveDelayedWeaponToChar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("GIVE_DELAYED_WEAPON_TO_CHAR", p0, p1, p2, p3); }
	static void GivePedAmbientObject(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GIVE_PED_AMBIENT_OBJECT", p0, p1); }
	static void GivePedHelmet(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GIVE_PED_HELMET", p0); }
	static void GivePedHelmetWithOpts(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GIVE_PED_HELMET_WITH_OPTS", p0, p1); }
	static void GivePedPickupObject(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("GIVE_PED_PICKUP_OBJECT", p0, p1, p2); }
	static void GivePlayerRagdollControl(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GIVE_PLAYER_RAGDOLL_CONTROL", p0, p1); }
	static void GiveWeaponToChar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("GIVE_WEAPON_TO_CHAR", p0, p1, p2, p3); }
	static void GrabNearbyObjectWithSpecialAttribute(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GRAB_NEARBY_OBJECT_WITH_SPECIAL_ATTRIBUTE", p0, p1); }

	static unsigned int IsClosestObjectOfTypeSmashedOrDamaged(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return NativeInvoke::Invoke<unsigned int>("IS_CLOSEST_OBJECT_OF_TYPE_SMASHED_OR_DAMAGED", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int IsControlJustPressed(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("IS_CONTROL_JUST_PRESSED", p0, p1); }
	static unsigned int IsControlPressed(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("IS_CONTROL_PRESSED", p0, p1); }
	static unsigned int IsCopVehicleInArea3DNoSave(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("IS_COP_VEHICLE_IN_AREA_3D_NO_SAVE", p0, p1, p2, p3, p4, p5); }
	static unsigned int IsEpisodeAvailable(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_EPISODE_AVAILABLE", p0); }
	static unsigned int IsExplosionInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return NativeInvoke::Invoke<unsigned int>("IS_EXPLOSION_IN_AREA", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int IsExplosionInSphere(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("IS_EXPLOSION_IN_SPHERE", p0, p1, p2, p3, p4); }
	static unsigned int IsFollowVehicleCamOffsetActive() { return NativeInvoke::Invoke<unsigned int>("IS_FOLLOW_VEHICLE_CAM_OFFSET_ACTIVE"); }
	static unsigned int IsFontLoaded(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_FONT_LOADED", p0); }
	static unsigned int IsGameKeyboardKeyJustPressed(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_GAME_KEYBOARD_KEY_JUST_PRESSED", p0); }
	static unsigned int IsGameKeyboardKeyPressed(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_GAME_KEYBOARD_KEY_PRESSED", p0); }
	static unsigned int IsHeliPartBroken(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("IS_HELI_PART_BROKEN", p0, p1, p2, p3); }

	static unsigned int IsKeyboardKeyJustPressed(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_KEYBOARD_KEY_JUST_PRESSED", p0); }
	static unsigned int IsKeyboardKeyPressed(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_KEYBOARD_KEY_PRESSED", p0); }

	static unsigned int IsObjectAttached(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_OBJECT_ATTACHED", p0); }
	static unsigned int IsObjectInAngledArea3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("IS_OBJECT_IN_ANGLED_AREA_3D", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static unsigned int IsObjectInArea3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("IS_OBJECT_IN_AREA_3D", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int IsObjectPlayingAnim(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("IS_OBJECT_PLAYING_ANIM", p0, p1, p2); }
	static unsigned int IsObjectReassignmentInProgress() { return NativeInvoke::Invoke<unsigned int>("IS_OBJECT_REASSIGNMENT_IN_PROGRESS"); }

	static unsigned int IsPointObscuredByAMissionEntity(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("IS_POINT_OBSCURED_BY_A_MISSION_ENTITY", p0, p1, p2, p3, p4, p5); }
	static unsigned int IsProjectileInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("IS_PROJECTILE_IN_AREA", p0, p1, p2, p3, p4, p5); }

	static unsigned int IsSittingObjectNear(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("IS_SITTING_OBJECT_NEAR", p0, p1, p2, p3); }
	static unsigned int IsSniperBulletInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("IS_SNIPER_BULLET_IN_AREA", p0, p1, p2, p3, p4, p5); }

	static unsigned int IsVehStuck(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("IS_VEH_STUCK", p0, p1, p2, p3, p4); }

	static void Line(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("LINE", p0, p1, p2, p3, p4, p5); }

	static void LoadScene(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("LOAD_SCENE", p0, p1, p2); }
	static void LoadSceneForRoomByKey(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("LOAD_SCENE_FOR_ROOM_BY_KEY", p0, p1); }

	static unsigned int LocateCar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CAR_2D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CAR_3D", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int LocateCharAnyMeans2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_2D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharAnyMeans3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_3D", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int LocateCharAnyMeansCar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_CAR_2D", p0, p1, p2, p3, p4); }
	static unsigned int LocateCharAnyMeansCar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_CAR_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharAnyMeansChar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_CHAR_2D", p0, p1, p2, p3, p4); }
	static unsigned int LocateCharAnyMeansChar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_CHAR_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharAnyMeansObject2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_OBJECT_2D", p0, p1, p2, p3, p4); }
	static unsigned int LocateCharAnyMeansObject3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ANY_MEANS_OBJECT_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharInCar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_IN_CAR_2D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharInCar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_IN_CAR_3D", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int LocateCharInCarCar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_IN_CAR_CAR_2D", p0, p1, p2, p3, p4); }
	static unsigned int LocateCharInCarCar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_IN_CAR_CAR_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharInCarChar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_IN_CAR_CHAR_2D", p0, p1, p2, p3, p4); }
	static unsigned int LocateCharInCarChar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_IN_CAR_CHAR_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharInCarObject3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_IN_CAR_OBJECT_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharOnFoot2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ON_FOOT_2D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharOnFoot3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ON_FOOT_3D", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int LocateCharOnFootCar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ON_FOOT_CAR_2D", p0, p1, p2, p3, p4); }
	static unsigned int LocateCharOnFootCar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ON_FOOT_CAR_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharOnFootChar2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ON_FOOT_CHAR_2D", p0, p1, p2, p3, p4); }
	static unsigned int LocateCharOnFootChar3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ON_FOOT_CHAR_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateCharOnFootObject3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_CHAR_ON_FOOT_OBJECT_3D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateObject2D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOCATE_OBJECT_2D", p0, p1, p2, p3, p4, p5); }
	static unsigned int LocateObject3D(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("LOCATE_OBJECT_3D", p0, p1, p2, p3, p4, p5, p6, p7); }

	static unsigned int PlayObjectAnim(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("PLAY_OBJECT_ANIM", p0, p1, p2, p3, p4, p5); }
	static void PlaySound(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PLAY_SOUND", p0, p1); }
	static void PlaySoundFromObject(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("PLAY_SOUND_FROM_OBJECT", p0, p1, p2); }
	static void PlaySoundFromPed(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("PLAY_SOUND_FROM_PED", p0, p1, p2); }
	static void PlaySoundFromPosition(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("PLAY_SOUND_FROM_POSITION", p0, p1, p2, p3, p4); }
	static void PlaySoundFromVehicle(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("PLAY_SOUND_FROM_VEHICLE", p0, p1, p2); }
	static void PlaySoundFrontend(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PLAY_SOUND_FRONTEND", p0, p1); }
	static void PlayStreamFromObject(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PLAY_STREAM_FROM_OBJECT", p0); }
	static void PlayStreamFromPed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PLAY_STREAM_FROM_PED", p0); }
	static void PlayStreamFrontEnd() { NativeInvoke::Invoke<unsigned int>("PLAY_STREAM_FRONTEND"); }

	static void RegisterIntStat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("REGISTER_INT_STAT", p0, p1); }
	static unsigned int RegisterSaveHouse(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("REGISTER_SAVE_HOUSE", p0, p1, p2, p3, p4, p5); }

	static void RequestScript(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REQUEST_SCRIPT", p0); }
	static void ResetCarWheels(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("RESET_CAR_WHEELS", p0, p1); }
	static void ResetStuckTimer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("RESET_STUCK_TIMER", p0, p1); }
	static void ResetVisiblePedDamage(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RESET_VISIBLE_PED_DAMAGE", p0); }
	static void RetuneRadioDown() { NativeInvoke::Invoke<unsigned int>("RETUNE_RADIO_DOWN"); }
	static void RetuneRadioToStationIndex(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RETUNE_RADIO_TO_STATION_INDEX", p0); }
	static void RetuneRadioToStationName(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RETUNE_RADIO_TO_STATION_NAME", p0); }
	static void RetuneRadioUp() { NativeInvoke::Invoke<unsigned int>("RETUNE_RADIO_UP"); }
	static void ReviveInjuredPed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REVIVE_INJURED_PED", p0); }
	static unsigned int RotateObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("ROTATE_OBJECT", p0, p1, p2, p3); }
	static unsigned int Round(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("ROUND", p0); }
	static void SetActivateObjectPhysicsAsSoonAsItIsUnfrozen(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN", p0, p1); }
	static void SetAllCarsCanBeDamaged(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ALL_CARS_CAN_BE_DAMAGED", p0); }
	static void SetAllPickupsOfTypeCollectableByCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ALL_PICKUPS_OF_TYPE_COLLECTABLE_BY_CAR", p0, p1); }
	static void SetAllRandomPedsFlee(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ALL_RANDOM_PEDS_FLEE", p0, p1); }
	static void SetAlwaysDisplayWeaponPickupMessage(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ALWAYS_DISPLAY_WEAPON_PICKUP_MESSAGE", p0); }

	static void SetBlipAsFriendly(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_BLIP_AS_FRIENDLY", p0, p1); }
	static void SetBlipAsShortRange(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_BLIP_AS_SHORT_RANGE", p0, p1); }
	static void SetBlipMarkerLongDistance(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_BLIP_MARKER_LONG_DISTANCE", p0, p1); }
	static void SetBlipThrottleRandomly(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_BLIP_THROTTLE_RANDOMLY", p0, p1); }
	static void SetCarAsMissionCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CAR_AS_MISSION_CAR", p0); }
	static void SetCarCanBeDamaged(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_CAN_BE_DAMAGED", p0, p1); }
	static void SetCarCanBeVisiblyDamaged(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_CAN_BE_VISIBLY_DAMAGED", p0, p1); }
	static void SetCarCollision(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_COLLISION", p0, p1); }
	static void SetCarColourCombination(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_COLOUR_COMBINATION", p0, p1); }
	static void SetCarDensityMultiplier(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CAR_DENSITY_MULTIPLIER", p0); }
	static void SetCarDoorLatched(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CAR_DOOR_LATCHED", p0, p1, p2, p3); }
	static void SetCarEngineOn(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CAR_ENGINE_ON", p0, p1, p2); }
	static void SetCarForwardSpeed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_FORWARD_SPEED", p0, p1); }
	static void SetCarHasBeenCreatedInInterior(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CAR_HAS_BEEN_CREATED_IN_INTERIOR", p0); }
	static void SetCarHealth(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_HEALTH", p0, p1); }
	static void SetCarInCutscene(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_IN_CUTSCENE", p0, p1); }
	static void SetCarLightMultiplier(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_LIGHT_MULTIPLIER", p0, p1); }
	static void SetCarLivery(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_LIVERY", p0, p1); }
	static unsigned int SetCarOnGroundProperly(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("SET_CAR_ON_GROUND_PROPERLY", p0); }
	static void SetCarOnlyDamagedByPlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_ONLY_DAMAGED_BY_PLAYER", p0, p1); }
	static void SetCarRandomRouteSeed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_RANDOM_ROUTE_SEED", p0, p1); }
	static void SetCarStrong(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_STRONG", p0, p1); }
	static void SetCarVisible(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAR_VISIBLE", p0, p1); }
	static void SetCharAccuracy(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_ACCURACY", p0, p1); }
	static void SetCharAllowedToDuck(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_ALLOWED_TO_DUCK", p0, p1); }
	static void SetCharAmmo(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_AMMO", p0, p1, p2); }
	static void SetCharAngledDefensiveArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_ANGLED_DEFENSIVE_AREA", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void SetCharAnimSpeed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_ANIM_SPEED", p0, p1, p2, p3); }
	static void SetCharAsEnemy(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_AS_ENEMY", p0, p1); }
	static void SetCharAsMissionChar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_AS_MISSION_CHAR", p0); }
	static void SetCharCanBeKnockedOffBike(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE", p0, p1); }
	static void SetCharCanBeShotInVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_CAN_BE_SHOT_IN_VEHICLE", p0, p1); }
	static void SetCharCanSmashGlass(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_CAN_SMASH_GLASS", p0, p1); }
	static void SetCharCantBeDraggedOut(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_CANT_BE_DRAGGED_OUT", p0, p1); }
	static void SetCharClimbAnimRate(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_CLIMB_ANIM_RATE", p0, p1); }
	static void SetCharCollision(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_COLLISION", p0, p1); }
	static void SetCharComponentVariation(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_COMPONENT_VARIATION", p0, p1, p2, p3); }
	static void SetCharCoordinates(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_COORDINATES", p0, p1, p2, p3); }
	static void SetCharCoordinatesDontWarpGang(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_COORDINATES_DONT_WARP_GANG", p0, p1, p2, p3); }
	static void SetCharCoordinatesNoOffset(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_COORDINATES_NO_OFFSET", p0, p1, p2, p3); }
	static void SetCharCurrentWeaponVisible(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_CURRENT_WEAPON_VISIBLE", p0, p1); }
	static void SetCharDefaultComponentVariation(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DEFAULT_COMPONENT_VARIATION", p0); }
	static void SetCharDesiredHeading(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DESIRED_HEADING", p0, p1); }
	static void SetCharDiesInstantlyInWater(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DIES_INSTANTLY_IN_WATER", p0, p1); }
	static void SetCharDropsWeaponsWhenDead(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DROPS_WEAPONS_WHEN_DEAD", p0, p1); }
	static void SetCharDrownsInSinkingVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DROWNS_IN_SINKING_VEHICLE", p0, p1); }
	static void SetCharDrownsInWater(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DROWNS_IN_WATER", p0, p1); }
	static void SetCharDruggedUp(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DRUGGED_UP", p0, p1); }
	static unsigned int SetCharDucking(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("SET_CHAR_DUCKING", p0, p1); }
	static void SetCharFireDamageMultiplier(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_FIRE_DAMAGE_MULTIPLIER", p0, p1); }
	static void SetCharForceDieInCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_FORCE_DIE_IN_CAR", p0, p1); }
	static void SetCharGravity(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_GRAVITY", p0, p1); }
	static void SetCharHeading(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_HEADING", p0, p1); }
	static void SetCharInvincible(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_INVINCIBLE", p0, p1); }
	static void SetCharIsTargetPriority(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_IS_TARGET_PRIORITY", p0, p1); }
	static void SetCharKeepTask(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_KEEP_TASK", p0, p1); }
	static void SetCharMaxHealth(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_MAX_HEALTH", p0, p1); }
	static void SetCharMaxTimeInWater(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_MAX_TIME_IN_WATER", p0, p1); }
	static void SetCharMaxTimeUnderwater(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_MAX_TIME_UNDERWATER", p0, p1); }
	static void SetCharMeleeActionFlag0(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_MELEE_ACTION_FLAG0", p0, p1); }
	static void SetCharMeleeActionFlag1(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_MELEE_ACTION_FLAG1", p0, p1); }
	static void SetCharMeleeMovementConstaintBox(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_MELEE_MOVEMENT_CONSTAINT_BOX", p0, p1, p2, p3, p4, p5, p6); }
	static void SetCharMoveAnimSpeedMultiplier(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER", p0, p1); }
	static void SetCharNeverLeavesGroup(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_NEVER_LEAVES_GROUP", p0, p1); }
	static void SetCharNeverTargetted(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_NEVER_TARGETTED", p0, p1); }
	static void SetCharOnlyDamagedByPlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_ONLY_DAMAGED_BY_PLAYER", p0, p1); }
	static void SetCharPropIndex(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_PROP_INDEX", p0, p1, p2); }
	static void SetCharRandomComponentVariation(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_RANDOM_COMPONENT_VARIATION", p0); }
	static void SetCharReadyToBeExecuted(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_READY_TO_BE_EXECUTED", p0, p1); }
	static void SetCharReadyToBeStunned(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_READY_TO_BE_STUNNED", p0, p1); }
	static void SetCharRotation(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_ROTATION", p0, p1, p2, p3); }
	static void SetCharShootRate(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_SHOOT_RATE", p0, p1); }
	static void SetCharSphereDefensiveArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_SPHERE_DEFENSIVE_AREA", p0, p1, p2, p3, p4); }
	static void SetCharStayInCarWhenJacked(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_STAY_IN_CAR_WHEN_JACKED", p0, p1); }
	static void SetCharSuffersCriticalHits(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_SUFFERS_CRITICAL_HITS", p0, p1); }
	static void SetCharUsesDeafultAnimGroupWhenFleeing(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_USES_DEAFULT_ANIM_GROUP_WHEN_FLEEING", p0, p1); }
	static void SetCharVelocity(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_VELOCITY", p0, p1, p2, p3); }
	static void SetCharVisible(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_VISIBLE", p0, p1); }
	static void SetCharWantedByPolice(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WANTED_BY_POLICE", p0, p1); }
	static void SetCharWeaponSkill(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WEAPON_SKILL", p0, p1); }
	static void SetCharWillCowerInsteadOfFleeing(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING", p0, p1); }
	static void SetCharWillDoDrivebys(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_DO_DRIVEBYS", p0, p1); }
	static void SetCharWillFlyThroughWindscreen(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN", p0, p1); }
	static void SetCharWillLeaveCarInCombat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_LEAVE_CAR_IN_COMBAT", p0, p1); }
	static void SetCharWillMoveWhenInjured(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_MOVE_WHEN_INJURED", p0, p1); }
	static void SetCharWillOnlyFireWithClearLos(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_ONLY_FIRE_WITH_CLEAR_LOS", p0, p1); }
	static void SetCharWillRemainOnBoatAfterMissionEnds(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_REMAIN_ON_BOAT_AFTER_MISSION_ENDS", p0, p1); }
	static void SetCharWillUseCarsInCombat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_WILL_USE_CARS_IN_COMBAT", p0, p1); }
	static void SetCollideWithPeds(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_COLLIDE_WITH_PEDS", p0); }
	static void SetCreateRandomCops(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CREATE_RANDOM_COPS", p0); }
	static void SetCurrentCharWeapon(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CURRENT_CHAR_WEAPON", p0, p1, p2); }
	static void SetCurrentMovie(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CURRENT_MOVIE", p0); }
	static void SetDeadCharCoordinates(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_DEAD_CHAR_COORDINATES", p0, p1, p2, p3); }
	static void SetDeadPedsDropWeapons(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_DEAD_PEDS_DROP_WEAPONS", p0); }
	static void SetDitchPoliceModels(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_DITCH_POLICE_MODELS", p0); }
	static void SetDoNotSpawnParkedCarsOnTop(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DO_NOT_SPAWN_PARKED_CARS_ON_TOP", p0, p1); }
	static void SetDontActivateRagdollFromPlayerImpact(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT", p0, p1); }
	static void SetDrawPlayerComponent(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DRAW_PLAYER_COMPONENT", p0, p1); }
	static void SetDriveTaskCruiseSpeed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DRIVE_TASK_CRUISE_SPEED", p0, p1); }
	static void SetDrunkCam(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_DRUNK_CAM", p0, p1, p2); }
	static void SetEnableNearClipScan(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ENABLE_NEAR_CLIP_SCAN", p0); }
	static void SetEveryoneIgnorePlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_EVERYONE_IGNORE_PLAYER", p0, p1); }
	static void SetExtraCarColours(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_EXTRA_CAR_COLOURS", p0, p1, p2); }
	static void SetFakeWantedLevel(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_FAKE_WANTED_LEVEL", p0); }
	static void SetFloatStat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_FLOAT_STAT", p0, p1); }
	static void SetGroupCharDucksWhenAimedAt(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT", p0, p1); }
	static void SetGroupFollowStatus(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_FOLLOW_STATUS", p0, p1); }
	static void SetGroupFormation(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_FORMATION", p0, p1); }
	static void SetGroupFormationSpacing(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_FORMATION_SPACING", p0, p1); }
	static void SetGroupLeader(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_LEADER", p0, p1); }
	static void SetGroupMember(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_MEMBER", p0, p1); }
	static void SetGroupSeparationRange(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_SEPARATION_RANGE", p0, p1); }
	static void SetHasBeenOwnedByPlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_HAS_BEEN_OWNED_BY_PLAYER", p0, p1); }

	static void SetHeliBladesFullSpeed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_HELI_BLADES_FULL_SPEED", p0); }	
	static void SetIgnoreLowPriorityShockingEvents(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS", p0, p1); }
	static void SetInstantWidescreenBorders(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_INSTANT_WIDESCREEN_BORDERS", p0); }
	static void SetInterpFromGameToScript(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_INTERP_FROM_GAME_TO_SCRIPT", p0, p1); }
	static void SetMaxWantedLevel(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MAX_WANTED_LEVEL", p0); }
	static void SetMinigameInProgress(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MINIGAME_IN_PROGRESS", p0); }
	static void SetMissionFlag(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MISSION_FLAG", p0); }
	static void SetMissionTrainCoordinates(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_MISSION_TRAIN_COORDINATES", p0, p1, p2, p3); }
	static void SetMobilePhonePosition(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_MOBILE_PHONE_POSITION", p0, p1, p2); }
	static void SetMobilePhoneRadioState(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MOBILE_PHONE_RADIO_STATE", p0); }
	static void SetMobilePhoneRotation(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_MOBILE_PHONE_ROTATION", p0, p1, p2); }
	static void SetMobilePhoneScale(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MOBILE_PHONE_SCALE", p0); }
	static void SetMobileRadioEnabledDuringGameplay(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY", p0); }
	static void SetMobileRingType(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MOBILE_RING_TYPE", p0); }
	static void SetMoneyCarriedByAllNewPeds(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MONEY_CARRIED_BY_ALL_NEW_PEDS", p0); }

	static void SetMovieTime(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MOVIE_TIME", p0); }
	static void SetMovieVolume(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MOVIE_VOLUME", p0); }
	static void SetNeedsToBeHotwired(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NEEDS_TO_BE_HOTWIRED", p0, p1); }
	static void SetNextDesiredMoveState(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_NEXT_DESIRED_MOVE_STATE", p0); }

	static void SetObjectAlpha(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_ALPHA", p0, p1); }
	static void SetObjectAnimCurrentTime(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_ANIM_CURRENT_TIME", p0, p1, p2, p3); }
	static void SetObjectAnimSpeed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_ANIM_SPEED", p0, p1, p2, p3); }
	static void SetObjectAsStealable(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_AS_STEALABLE", p0, p1); }
	static void SetObjectDynamic(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_DYNAMIC", p0, p1); }
	static void SetObjectHealth(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_HEALTH", p0, p1); }
	static void SetObjectInitialVelocity(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_INITIAL_VELOCITY", p0, p1, p2, p3); }
	static void SetObjectInvincible(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_INVINCIBLE", p0, p1); }
	static void SetObjectLights(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_LIGHTS", p0, p1); }
	static void SetObjectOnlyDamagedByPlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_ONLY_DAMAGED_BY_PLAYER", p0, p1); }
	static void SetObjectPhysicsParams(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_PHYSICS_PARAMS", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static void SetObjectQuaternion(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_QUATERNION", p0, p1, p2, p3, p4); }
	static void SetObjectScale(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_SCALE", p0, p1); }
	static void SetObjectUsedInPoolGame(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_USED_IN_POOL_GAME", p0, p1); }
	static void SetParkedCarDensityMultiplier(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PARKED_CAR_DENSITY_MULTIPLIER", p0); }
	static void SetPedAlpha(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_ALPHA", p0, p1); }
	static void SetPedDensityMultiplier(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PED_DENSITY_MULTIPLIER", p0); }
	static void SetPedDiesWhenInjured(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_DIES_WHEN_INJURED", p0, p1); }
	static void SetPedEnableLegIK(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_ENABLE_LEG_IK", p0, p1); }
	static void SetPedGeneratesDeadBodyEvents(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_GENERATES_DEAD_BODY_EVENTS", p0, p1); }
	static void SetPedHeedsTheEveryoneIgnorePlayerFlag(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_HEEDS_THE_EVERYONE_IGNORE_PLAYER_FLAG", p0, p1); }
	static void SetPedIsBlindRaging(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_IS_BLIND_RAGING", p0, p1); }
	static void SetPedIsDrunk(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_IS_DRUNK", p0, p1); }
	static void SetPedNonRemovalArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SET_PED_NON_REMOVAL_AREA", p0, p1, p2, p3, p4, p5); }
	static void SetPedPathMayDropFromHeight(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_PATH_MAY_DROP_FROM_HEIGHT", p0, p1); }
	static void SetPedPathMayUseClimbovers(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_PATH_MAY_USE_CLIMBOVERS", p0, p1); }
	static void SetPedPathMayUseLadders(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_PATH_MAY_USE_LADDERS", p0, p1); }
	static void SetPedWontAttackPlayerWithoutWantedLevel(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_WONT_ATTACK_PLAYER_WITHOUT_WANTED_LEVEL", p0, p1); }
	static void SetPetrolTankHealth(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PETROL_TANK_HEALTH", p0, p1); }
	static void SetPhoneHUDItem(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_PHONE_HUD_ITEM", p0, p1, p2); }
	static void SetPickupCollectableByCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PICKUP_COLLECTABLE_BY_CAR", p0, p1); }
	static void SetPickupsFixCars(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PICKUPS_FIX_CARS", p0); }

	static void SetPlayerCanDropWeaponsInCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PLAYER_CAN_DROP_WEAPONS_IN_CAR", p0); }

	static void SetPoliceFocusWillTrackCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_POLICE_FOCUS_WILL_TRACK_CAR", p0, p1); }
	static void SetPoliceIgnorePlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_POLICE_IGNORE_PLAYER", p0, p1); }
	static void SetPoliceRadarBlips(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_POLICE_RADAR_BLIPS", p0); }

	static void SetRadarZoom(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_RADAR_ZOOM", p0); }
	static void SetRandomCarDensityMultiplier(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_RANDOM_CAR_DENSITY_MULTIPLIER", p0); }
	static void SetRandomSeed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_RANDOM_SEED", p0); }
	static void SetReducePedModelBudget(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_REDUCE_PED_MODEL_BUDGET", p0); }
	static void SetReduceVehicleModelBudget(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_REDUCE_VEHICLE_MODEL_BUDGET", p0); }

	static void SetRenderTrainAsDerailed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_RENDER_TRAIN_AS_DERAILED", p0, p1); }
	static void SetRocketLauncherFreebieInHeli(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ROCKET_LAUNCHER_FREEBIE_IN_HELI", p0); }

	static void SetRoomForCarByName(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ROOM_FOR_CAR_BY_NAME", p0, p1); }
	static void SetRoomForCharByName(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ROOM_FOR_CHAR_BY_NAME", p0, p1); }
	static void SetRotOrder(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ROT_ORDER", p0); }
	static void SetRotationForAttachedPed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_ROTATION_FOR_ATTACHED_PED", p0, p1, p2, p3); }
	static void SetScreenFade(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10) { NativeInvoke::Invoke<unsigned int>("SET_SCREEN_FADE", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static void SetSleepModeActive(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_SLEEP_MODE_ACTIVE", p0); }
	static void SetSniperZoomFactor(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_SNIPER_ZOOM_FACTOR", p0); }
	static void SetStateOfClosestDoorOfType(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SET_STATE_OF_CLOSEST_DOOR_OF_TYPE", p0, p1, p2, p3, p4, p5); }
	static void SetSyncWeatherAndGameTime(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_SYNC_WEATHER_AND_GAME_TIME", p0); }
	static void SetTaxiGarageRadioState(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TAXI_GARAGE_RADIO_STATE", p0); }
	static void SetTaxiLights(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TAXI_LIGHTS", p0, p1); }
	static void SetTextBackground(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_BACKGROUND", p0); }
	static void SetTextCentre(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_CENTRE", p0); }
	static void SetTextColour(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_COLOUR", p0, p1, p2, p3); }
	static void SetTextDrawBeforeFade(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_DRAW_BEFORE_FADE", p0); }
	static void SetTextDropshadow(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_DROPSHADOW", p0, p1, p2, p3, p4); }
	static void SetTextEdge(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_EDGE", p0, p1, p2, p3, p4); }
	static void SetTextFont(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_FONT", p0); }
	static void SetTextJustify(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_JUSTIFY", p0); }
	static void SetTextLineDisplay(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TEXT__LINE__DISPLAY", p0, p1); }
	static void SetTextLineHeightMult(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT__LINE__HEIGHT_MULT", p0); }
	static void SetTextProportional(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_PROPORTIONAL", p0); }
	static void SetTextRenderId(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_RENDER_ID", p0); }
	static void SetTextRightJustify(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_RIGHT_JUSTIFY", p0); }
	static void SetTextScale(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_SCALE", p0, p1); }
	static void SetTextToUseTextFileColours(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_TO_USE_TEXT__FILE__COLOURS", p0); }
	static void SetTextUseUnderscore(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_USE_UNDERSCORE", p0); }
	static void SetTextWrap(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TEXT_WRAP", p0, p1); }

	static void SetThisScriptCanRemoveBlipsCreatedByAnyScript(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT", p0); }
	static void SetTimeOfDay(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TIME_OF_DAY", p0, p1); }
	static void SetTimeOneDayBack() { NativeInvoke::Invoke<unsigned int>("SET_TIME_ONE_DAY_BACK"); }
	static void SetTimeOneDayForward() { NativeInvoke::Invoke<unsigned int>("SET_TIME_ONE_DAY_FORWARD"); }
	static void SetTimeScale(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TIME_SCALE", p0); }
	static void SetTrainAudioRolloff(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TRAIN_AUDIO_ROLLOFF", p0, p1); }
	static void SetTrainCruiseSpeed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TRAIN_CRUISE_SPEED", p0, p1); }
	static void SetTrainForcedToSlowDown(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TRAIN_FORCED_TO_SLOW_DOWN", p0, p1); }
	static void SetTrainIsStoppedAtStation(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TRAIN_IS_STOPPED_AT_STATION", p0); }
	static void SetTrainSpeed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TRAIN_SPEED", p0, p1); }
	static void SetTrainStopsForStations(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_TRAIN_STOPS_FOR_STATIONS", p0, p1); }
	static void SetUseHighDOF(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_USE_HIGHDOF", p0); }
	static void SetUseLegIK(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_USE_LEG_IK", p0, p1); }

	static void SetVehAlarm(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VEH_ALARM", p0, p1); }
	static void SetVehHasStrongAxles(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VEH_HAS_STRONG_AXLES", p0, p1); }
	static void SetVehInteriorlight(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VEH_INTERIORLIGHT", p0, p1); }
	static void SetVehicleAlpha(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VEHICLE_ALPHA", p0, p1); }
	static void SetVehicleCanBeTargetted(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VEHICLE_CAN_BE_TARGETTED", p0, p1); }
	static void SetVehicleDirtLevel(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VEHICLE_DIRT_LEVEL", p0, p1); }
	static void SetVehicleIsConsideredByPlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VEHICLE_IS_CONSIDERED_BY_PLAYER", p0, p1); }
	static void SetVehicleQuaternion(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_VEHICLE_QUATERNION", p0, p1, p2, p3, p4); }

	static void SetWidescreenBorders(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_WIDESCREEN_BORDERS", p0); }
	static void SetWidescreenFormat(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_WIDESCREEN_FORMAT", p0); }
	static void SetZoneNoCops(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ZONE_NO_COPS", p0, p1); }
	static void SetZonePopulationType(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ZONE_POPULATION_TYPE", p0, p1); }
	static void SetZoneScumminess(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ZONE_SCUMMINESS", p0, p1); }
	static void ShakePad(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SHAKE_PAD", p0, p1, p2); }
	static void ShakePlayerpadWhenControllerDisabled() { NativeInvoke::Invoke<unsigned int>("SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED"); }
	static void SkipRadioForward() { NativeInvoke::Invoke<unsigned int>("SKIP_RADIO_FORWARD"); }

	static void SkipToNextAllowedStation(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SKIP_TO_NEXT_ALLOWED_STATION", p0); }
	static unsigned int SlideObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("SLIDE_OBJECT", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void SmashCarWindow(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SMASH_CAR_WINDOW", p0, p1); }
	static unsigned int SmashGlassOnObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("SMASH_GLASS_ON_OBJECT", p0, p1, p2, p3, p4, p5); }
	static void SoundCarHorn(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SOUND_CAR_HORN", p0, p1); }
	static unsigned int StartCharFire(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("START_CHAR_FIRE", p0); }
	static void StartFiringAmnesty() { NativeInvoke::Invoke<unsigned int>("START_FIRING_AMNESTY"); }
	static unsigned int StartNewScript(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("START_NEW_SCRIPT", p0, p1); }
	static unsigned int StartNewScriptWithArgs(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("START_NEW_SCRIPT_WITH_ARGS", p0, p1, p2, p3); }

	static unsigned int StartScriptFire(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("START_SCRIPT_FIRE", p0, p1, p2, p3, p4); }
	static void StopCarBreaking(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("STOP_CAR_BREAKING", p0, p1); }
	static void StopMovie() { NativeInvoke::Invoke<unsigned int>("STOP_MOVIE"); }
	static void StopPedDoingFallOffTestsWhenShot(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("STOP_PED_DOING_FALL_OFF_TESTS_WHEN_SHOT", p0); }
	static void StopPedSpeaking(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("STOP_PED_SPEAKING", p0, p1); }
	static void StopPedWeaponFiringWhenDropped(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("STOP_PED_WEAPON_FIRING_WHEN_DROPPED", p0); }
	static void SuppressCarModel(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SUPPRESS_CAR_MODEL", p0); }
	static void SuppressPedModel(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SUPPRESS_PED_MODEL", p0); }
	static void SwapNearestBuildingModel(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SWAP_NEAREST_BUILDING_MODEL", p0, p1, p2, p3, p4, p5); }
	
	static void SwitchCarSiren(unsigned int car, bool on) { NativeInvoke::Invoke<unsigned int>("SWITCH_CAR_SIREN", car, on); }

	static unsigned int SwitchPedToRagdoll(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return NativeInvoke::Invoke<unsigned int>("SWITCH_PED_TO_RAGDOLL", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int SwitchPedToRagdollWithFall(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12, unsigned int p13) { return NativeInvoke::Invoke<unsigned int>("SWITCH_PED_TO_RAGDOLL_WITH_FALL", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	static void SwitchRoadsBackToOriginal(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SWITCH_ROADS_BACK_TO_ORIGINAL", p0, p1, p2, p3, p4, p5); }
	static void SwitchRoadsOff(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SWITCH_ROADS_OFF", p0, p1, p2, p3, p4, p5); }
	static void SwitchRoadsOn(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SWITCH_ROADS_ON", p0, p1, p2, p3, p4, p5); }

	static unsigned int UsingStandardControls() { return NativeInvoke::Invoke<unsigned int>("USING_STANDARD_CONTROLS"); }

	static unsigned int UpdateLoadScene() { return NativeInvoke::Invoke<unsigned int>("UPDATE_LOAD_SCENE"); }

// For later....

	static unsigned int AbortScriptedConversation(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("ABORT_SCRIPTED_CONVERSATION", p0); }
	static void ActivateDamageTrackerOnNetworkId(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID", p0, p1); }
	static void ActivateHeliSpeedCheat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ACTIVATE_HELI_SPEED_CHEAT", p0, p1); }
	static void ActivateNetworkSettingsMenu() { NativeInvoke::Invoke<unsigned int>("ACTIVATE_NETWORK_SETTINGS_MENU"); }
	static void ActivateScriptedCams(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ACTIVATE_SCRIPTED_CAMS", p0, p1); }
	static void ActivateViewport(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ACTIVATE_VIEWPORT", p0, p1); }
	static void AddCamSplineNode(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ADD_CAM_SPLINE_NODE", p0, p1); }
	static void AddCarToMissionDeletionList(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_CAR_TO_MISSION_DELETION_LIST", p0); }
	static void AddCharDecisionMakerEventResponse(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void AddCoverBlockingArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("ADD_COVER_BLOCKING_AREA", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void AddCoverPoint(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("ADD_COVER_POINT", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void AddFollowNavmeshToPhoneTask(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("ADD_FOLLOW_NAVMESH_TO_PHONE_TASK", p0, p1, p2, p3); }
	static void AddGroupToNetworkRestartNodeGroupList(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_GROUP_TO_NETWORK_RESTART_NODE_GROUP_LIST", p0); }
	static void AddHospitalRestart(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("ADD_HOSPITAL_RESTART", p0, p1, p2, p3, p4); }
	static void AddLineToConversation(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("ADD__LINE__TO_CONVERSATION", p0, p1, p2, p3, p4); }
	static void AddLineToMobilePhoneCall(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("ADD__LINE__TO_MOBILE_PHONE_CALL", p0, p1, p2); }
	static void AddNeededAtPosN(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("ADD_NEEDED_AT_POSN", p0, p1, p2); }
	static void AddNewConversationSpeaker(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("ADD_NEW_CONVERSATION_SPEAKER", p0, p1, p2); }
	static void AddNextMessageToPreviousBriefs(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS", p0); }
	static void AddObjectToInteriorRoomByKey(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ADD_OBJECT_TO_INTERIOR_ROOM_BY_KEY", p0, p1); }
	static void AddObjectToInteriorRoomByName(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME", p0, p1); }
	static void AddPedToMissionDeletionList(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ADD_PED_TO_MISSION_DELETION_LIST", p0, p1); }
	static void AddPointToGpsRaceTrack(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_POINT_TO_GPS_RACE_TRACK", p0); }
	static void AddPoliceRestart(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("ADD_POLICE_RESTART", p0, p1, p2, p3, p4); }
	static void AddScenarioBlockingArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("ADD_SCENARIO_BLOCKING_AREA", p0, p1, p2, p3, p4, p5); }
	static void AddSpawnBlockingArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("ADD_SPAWN_BLOCKING_AREA", p0, p1, p2, p3); }
	static void AddStringToNewsScrollbar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_STRING_TO_NEWS_SCROLLBAR", p0); }
	static void AddStuckCarCheck(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("ADD_STUCK_CAR_CHECK", p0, p1, p2); }
	static void AddStuckCarCheckWithWarp(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("ADD_STUCK_CAR_CHECK_WITH_WARP", p0, p1, p2, p3, p4, p5, p6); }
	static void AddStuntJump(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12, unsigned int p13, unsigned int p14, unsigned int p15) { NativeInvoke::Invoke<unsigned int>("ADD_STUNT_JUMP", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15); }
	static void AddToHtmlScriptObject(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ADD_TO_HTML_SCRIPT_OBJECT", p0, p1); }
	static void AddToPreviousBrief(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_TO_PREVIOUS_BRIEF", p0); }
	static void AddToPreviousBriefWithUnderscore(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_TO_PREVIOUS_BRIEF_WITH_UNDERSCORE", p0); }
	static void AddToWidgetCombo(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ADD_TO_WIDGET_COMBO", p0); }
	static unsigned int AddWidgetFloatReadOnly(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("ADD_WIDGET_FLOAT_READ_ONLY", p0, p1); }
	static unsigned int AddWidgetFloatSlider(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("ADD_WIDGET_FLOAT_SLIDER", p0, p1, p2, p3, p4); }
	static unsigned int AddWidgetReadOnly(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("ADD_WIDGET_READ_ONLY", p0, p1); }
	static unsigned int AddWidgetSlider(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("ADD_WIDGET_SLIDER", p0, p1, p2, p3, p4); }
	static unsigned int AddWidgetToggle(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("ADD_WIDGET_TOGGLE", p0, p1); }
	static void AllocateScriptToObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("ALLOCATE_SCRIPT_TO_OBJECT", p0, p1, p2, p3, p4); }
	static void AllocateScriptToRandomPed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("ALLOCATE_SCRIPT_TO_RANDOM_PED", p0, p1, p2, p3); }
	static void AllowAutoConversationLookats(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ALLOW_AUTO_CONVERSATION_LOOKATS", p0, p1); }
	static void AllowGangRelationshipsToBeChangedByNextCommand(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ALLOW_GANG_RELATIONSHIPS_TO_BE_CHANGED_BY_NEXT_COMMAND", p0); }
	static void AllowLockonToFriendlyPlayers(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ALLOW_LOCKON_TO_FRIENDLY_PLAYERS", p0, p1); }
	static void AllowMultipleDrivebyPickups(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ALLOW_MULTIPLE_DRIVEBY_PICKUPS", p0); }
	static unsigned int AllowOneTimeOnlyCommandsToRun() { return NativeInvoke::Invoke<unsigned int>("ALLOW_ONE_TIME_ONLY_COMMANDS_TO_RUN"); }
	static void AllowReactionAnims(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ALLOW_REACTION_ANIMS", p0, p1); }
	static void AllowScenarioPedsToBeReturnedByNextCommand(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ALLOW_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND", p0); }
	static void AllowTargetWhenInjured(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ALLOW_TARGET_WHEN_INJURED", p0, p1); }
	static void AllowThisScriptToBePaused(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ALLOW_THIS_SCRIPT_TO_BE_PAUSED", p0); }
	static void AlwaysUseHeadOnHornAnimWhenDeadInCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ALWAYS_USE_HEAD_ON_HORN_ANIM_WHEN_DEAD_IN_CAR", p0, p1); }
	static void AmbientAudioBankNoLongerNeeded() { NativeInvoke::Invoke<unsigned int>("AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED"); }
	static void AnchorObject(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("ANCHOR_OBJECT", p0, p1, p2); }
	static void ApplyForceToCar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11) { NativeInvoke::Invoke<unsigned int>("APPLY_FORCE_TO_CAR", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static void ApplyForceToObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11) { NativeInvoke::Invoke<unsigned int>("APPLY_FORCE_TO_OBJECT", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static void ApplyForceToPed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11) { NativeInvoke::Invoke<unsigned int>("APPLY_FORCE_TO_PED", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static unsigned int AreAllNavmeshRegionsLoaded() { return NativeInvoke::Invoke<unsigned int>("ARE_ALL_NAVMESH_REGIONS_LOADED"); }
	static unsigned int AreEnemyPedsInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("ARE_ENEMY_PEDS_IN_AREA", p0, p1, p2, p3, p4); }
	static void AttachCamToObject(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ATTACH_CAM_TO_OBJECT", p0, p1); }
	static void AttachCamToPed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ATTACH_CAM_TO_PED", p0, p1); }
	static void AttachCamToVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ATTACH_CAM_TO_VEHICLE", p0, p1); }
	static void AttachCarToCar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("ATTACH_CAR_TO_CAR", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void AttachCarToObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("ATTACH_CAR_TO_OBJECT", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void AttachObjectToCar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("ATTACH_OBJECT_TO_CAR", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void AttachObjectToCarPhysically(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12, unsigned int p13, unsigned int p14) { NativeInvoke::Invoke<unsigned int>("ATTACH_OBJECT_TO_CAR_PHYSICALLY", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); }
	static void AttachObjectToObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("ATTACH_OBJECT_TO_OBJECT", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void AttachObjectToPed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("ATTACH_OBJECT_TO_PED", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void AttachPedToCar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("ATTACH_PED_TO_CAR", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void AttachPedToCarPhysically(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("ATTACH_PED_TO_CAR_PHYSICALLY", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void AttachPedToObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("ATTACH_PED_TO_OBJECT", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void BeginCamCommands(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("BEGIN_CAM_COMMANDS", p0); }
	static void BeginCharSearchCriteria() { NativeInvoke::Invoke<unsigned int>("BEGIN_CHAR_SEARCH_CRITERIA"); }
	static void BlendFromNmWithAnim(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("BLEND_FROM_NM_WITH_ANIM", p0, p1, p2, p3, p4, p5, p6); }
	static void BlockPedWeaponSwitching(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("BLOCK_PED_WEAPON_SWITCHING", p0, p1); }
	static void BlendOutCharMoveAnims(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("BLEND_OUT_CHAR_MOVE_ANIMS", p0); }
	static unsigned int CamIsSphereVisible(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("CAM_IS_SPHERE_VISIBLE", p0, p1, p2, p3, p4); }
	static void CamProcess(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CAM_PROCESS", p0); }
	static void CamSetInterpGraphPos(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CAM_SET_INTERP_GRAPH_POS", p0, p1); }
	static void CamSetInterpGraphRot(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CAM_SET_INTERP_GRAPH_ROT", p0, p1); }
	static unsigned int CanCreateRandomChar(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("CAN_CREATE_RANDOM_CHAR", p0, p1); }
	static unsigned int CanPlayerStartMission(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("CAN_PLAYER_START_MISSION", p0); }
	static unsigned int CanRegisterMissionObject() { return NativeInvoke::Invoke<unsigned int>("CAN_REGISTER_MISSION_OBJECT"); }
	static unsigned int CanRegisterMissionPed() { return NativeInvoke::Invoke<unsigned int>("CAN_REGISTER_MISSION_PED"); }
	static unsigned int CanRegisterMissionVehicle() { return NativeInvoke::Invoke<unsigned int>("CAN_REGISTER_MISSION_VEHICLE"); }
	static unsigned int CanStartMissionPassedTune() { return NativeInvoke::Invoke<unsigned int>("CAN_START_MISSION_PASSED_TUNE"); }
	static unsigned int CanTheStatHaveString(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("CAN_THE_STAT_HAVE_STRING", p0); }
	static void CancelCurrentlyPlayingAmbientSpeech(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH", p0); }
	static void CellCamActivate(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CELL_CAM_ACTIVATE", p0, p1); }
	static unsigned int CellCamIsCharVisible(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("CELL_CAM_IS_CHAR_VISIBLE", p0); }
	static unsigned int CellCamIsCharVisibleNoFaceCheck(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK", p0); }
	static void CellCamSetCentrePos(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CELL_CAM_SET_CENTRE_POS", p0, p1); }
	static void CellCamSetZoom(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CELL_CAM_SET_ZOOM", p0); }
	static void ChangeCharSitIdleAnim(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("CHANGE_CHAR_SIT_IDLE_ANIM", p0, p1, p2, p3); }
	static void ChangeGarageType(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CHANGE_GARAGE_TYPE", p0, p1); }
	static void ChangePickupBlipColour(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CHANGE_PICKUP_BLIP_COLOUR", p0); }
	static void ChangePickupBlipDisplay(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CHANGE_PICKUP_BLIP_DISPLAY", p0); }
	static void ChangePickupBlipPriority(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CHANGE_PICKUP_BLIP_PRIORITY", p0); }
	static void ChangePickupBlipScale(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CHANGE_PICKUP_BLIP_SCALE", p0); }
	static void ChangePickupBlipSprite(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CHANGE_PICKUP_BLIP_SPRITE", p0); }
	static void ChangePlaybackToUseAI(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CHANGE_PLAYBACK_TO_USE_AI", p0); }
	static unsigned int CheckNmFeedback(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("CHECK_NM_FEEDBACK", p0, p1, p2); }
	static unsigned int CheckStuckTimer(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("CHECK_STUCK_TIMER", p0, p1, p2); }
	static void ClearAdditionalText(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CLEAR_ADDITIONAL_TEXT", p0, p1); }
	static void ClearAngledAreaOfCars(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("CLEAR_ANGLED_AREA_OF_CARS", p0, p1, p2, p3, p4, p5, p6); }
	static void ClearBit(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CLEAR_BIT", p0, p1); }
	static void ClearBrief() { NativeInvoke::Invoke<unsigned int>("CLEAR_BRIEF"); }
	static void ClearCharDecisionMakerEventResponse(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CLEAR_CHAR_DECISION_MAKER_EVENT_RESPONSE", p0, p1); }
	static void ClearCharRelationship(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("CLEAR_CHAR_RELATIONSHIP", p0, p1, p2); }
	static void ClearHelp() { NativeInvoke::Invoke<unsigned int>("CLEAR_HELP"); }
	static void ClearNamedCutscene(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_NAMED_CUTSCENE", p0); }
	static void ClearNetworkRestartNodeGroupList() { NativeInvoke::Invoke<unsigned int>("CLEAR_NETWORK_RESTART_NODE_GROUP_LIST"); }
	static void ClearNewsScrollbar() { NativeInvoke::Invoke<unsigned int>("CLEAR_NEWS_SCROLLBAR"); }
	static void ClearOnscreenCounter(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_ONSCREEN_COUNTER", p0); }
	static void ClearOnscreenTimer(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_ONSCREEN_TIMER", p0); }
	static void ClearPrints() { NativeInvoke::Invoke<unsigned int>("CLEAR_PRINTS"); }
	static void ClearRelationship(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("CLEAR_RELATIONSHIP", p0, p1, p2); }
	static void ClearRoomForViewport(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_ROOM_FOR_VIEWPORT", p0); }
	static void ClearScriptArrayFromScratchpad(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_SCRIPT_ARRAY_FROM_SCRATCHPAD", p0); }
	static void ClearScriptedConversionCentre() { NativeInvoke::Invoke<unsigned int>("CLEAR_SCRIPTED_CONVERSION_CENTRE"); }
	static void ClearSequenceTask(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_SEQUENCE_TASK", p0); }
	static void ClearSmallPrints() { NativeInvoke::Invoke<unsigned int>("CLEAR_SMALL_PRINTS"); }
	static void ClearTextLabel(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_TEXT_LABEL", p0); }
	static void ClearThisPrint(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_THIS_PRINT", p0); }
	static void ClearThisPrintBigNow(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLEAR_THIS_PRINT_BIG_NOW", p0); }
	static void CloseDebugFile() { NativeInvoke::Invoke<unsigned int>("CLOSE_DEBUG_FILE"); }
	static void CloseSequenceTask(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CLOSE_SEQUENCE_TASK", p0); }
	static unsigned int CodeWantsMobilePhoneRemoved() { return NativeInvoke::Invoke<unsigned int>("CODE_WANTS_MOBILE_PHONE_REMOVED"); }
	static unsigned int CodeWantsMobilePhoneRemovedForWeaponSwitching() { return NativeInvoke::Invoke<unsigned int>("CODE_WANTS_MOBILE_PHONE_REMOVED_FOR_WEAPON_SWITCHING"); }
	static unsigned int CompareString(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("COMPARE_STRING", p0, p1); }
	static unsigned int CompareTwoDates(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("COMPARE_TWO_DATES", p0, p1, p2, p3); }
	static void ControlCarDoor(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("CONTROL_CAR_DOOR", p0, p1, p2, p3); }
	static void CopyAnimations(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("COPY_ANIMATIONS", p0, p1, p2); }
	static void CopyCharDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("COPY_CHAR_DECISION_MAKER", p0, p1); }
	static void CopyCombatDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("COPY_COMBAT_DECISION_MAKER", p0, p1); }
	static void CopyGroupCharDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("COPY_GROUP_CHAR_DECISION_MAKER", p0, p1); }
	static void CopySharedCombatDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("COPY_SHARED_COMBAT_DECISION_MAKER", p0, p1); }
	static unsigned int CountPickupsOfType(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("COUNT_PICKUPS_OF_TYPE", p0); }
	static unsigned int CountScriptCams() { return NativeInvoke::Invoke<unsigned int>("COUNT_SCRIPT_CAMS"); }
	static unsigned int CountScriptCamsByTypeAndOrState(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("COUNT_SCRIPT_CAMS_BY_TYPE_AND_OR_STATE", p0, p1, p2); }
	static void CreateCarGenerator(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12, unsigned int p13, unsigned int p14) { NativeInvoke::Invoke<unsigned int>("CREATE_CAR_GENERATOR", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14); }
	static unsigned int CreateCheckpoint(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("CREATE_CHECKPOINT", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int CreateEmergencyServicesCarReturnDriver(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return NativeInvoke::Invoke<unsigned int>("CREATE_EMERGENCY_SERVICES_CAR_RETURN_DRIVER", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int CreateEmergencyServicesCarThenWalk(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("CREATE_EMERGENCY_SERVICES_CAR_THEN_WALK", p0, p1, p2, p3); }
	static unsigned int CreateHtmlScriptObject(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("CREATE_HTML_SCRIPT_OBJECT", p0); }
	static void CreateHtmlViewport(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CREATE_HTML_VIEWPORT", p0); }
	static void CreateMobilePhone(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("CREATE_MOBILE_PHONE", p0); }
	static void CreateNmMessage(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("CREATE_NM_MESSAGE", p0, p1); }
	static void CreateTemporaryRadarBlipsForPickupsInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("CREATE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS_IN_AREA", p0, p1, p2, p3, p4); }
	static unsigned int CreateWidgetGroup(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("CREATE_WIDGET_GROUP", p0); }
	static void DeactivateNetworkSettingsMenu() { NativeInvoke::Invoke<unsigned int>("DEACTIVATE_NETWORK_SETTINGS_MENU"); }
	static void DebugOff() { NativeInvoke::Invoke<unsigned int>("DEBUG_OFF"); }
	static void DeleteAllHtmlScriptObjects() { NativeInvoke::Invoke<unsigned int>("DELETE_ALL_HTML_SCRIPT_OBJECTS"); }
	static void DeleteAllTrains() { NativeInvoke::Invoke<unsigned int>("DELETE_ALL_TRAINS"); }
	static void DeleteCarGenerator(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DELETE_CAR_GENERATOR", p0); }
	static void DeleteCheckpoint(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DELETE_CHECKPOINT", p0); }
	static void DeleteHtmlScriptObject(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DELETE_HTML_SCRIPT_OBJECT", p0); }
	static void DeleteWidgetGroup(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DELETE_WIDGET_GROUP", p0); }
	static void DestroyAllCams() { NativeInvoke::Invoke<unsigned int>("DESTROY_ALL_CAMS"); }
	static void DestroyCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DESTROY_CAM", p0); }
	static void DestroyMobilePhone() { NativeInvoke::Invoke<unsigned int>("DESTROY_MOBILE_PHONE"); }
	static void DestroyThread(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DESTROY_THREAD", p0); }
	static void DestroyViewport(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DESTROY_VIEWPORT", p0); }
	static void DisableCarGenerators(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DISABLE_CAR_GENERATORS", p0); }
	static void DisableCarGeneratorsWithHeli(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DISABLE_CAR_GENERATORS_WITH_HELI", p0); }
	static void DisableEndCreditsFade() { NativeInvoke::Invoke<unsigned int>("DISABLE_END_CREDITS_FADE"); }
	static void DisableGPS(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DISABLE_GPS", p0); }
	static void DisplayHelpTextThisFrame(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("DISPLAY_HELP_TEXT_THIS_FRAME", p0, p1); }
	static void DisplayNonMinigameHelpMessages(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DISPLAY_NON_MINIGAME_HELP_MESSAGES", p0); }
	static void DisplayPlaybackRecordedCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("DISPLAY_PLAYBACK_RECORDED_CAR", p0, p1); }
	static unsigned int DoesCamExist(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_CAM_EXIST", p0); }
	static unsigned int DoesDecisionMakerExist(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_DECISION_MAKER_EXIST", p0); }
	static unsigned int DoesGameCodeWantToLeaveNetworkSession() { return NativeInvoke::Invoke<unsigned int>("DOES_GAME_CODE_WANT_TO_LEAVE_NETWORK_SESSION"); }
	static unsigned int DoesObjectExistWithNetworkId(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_OBJECT_EXIST_WITH_NETWORK_ID", p0); }
	static unsigned int DoesPedExistWithNetworkId(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_PED_EXIST_WITH_NETWORK_ID", p0); }
	static unsigned int DoesScenarioExistInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("DOES_SCENARIO_EXIST_IN_AREA", p0, p1, p2, p3, p4); }
	static unsigned int DoesScriptExist(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_SCRIPT_EXIST", p0); }
	static unsigned int DoesTextLabelExist(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_TEXT_LABEL_EXIST", p0); }
	static unsigned int DoesThisMinigameScriptAllowNonMinigameHelpMessages() { return NativeInvoke::Invoke<unsigned int>("DOES_THIS_MINIGAME_SCRIPT_ALLOW_NON_MINIGAME_HELP_MESSAGES"); }
	static unsigned int DoesVehicleExistWithNetworkId(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_VEHICLE_EXIST_WITH_NETWORK_ID", p0); }
	static unsigned int DoesViewportExist(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_VIEWPORT_EXIST", p0); }
	static unsigned int DoesWebPageExist(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_WEB_PAGE_EXIST", p0); }
	static unsigned int DoesWidgetGroupExist(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("DOES_WIDGET_GROUP_EXIST", p0); }
	static void DontAbortCarConversations(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("DONT_ABORT_CAR_CONVERSATIONS", p0, p1); }
	static void DontDispatchCopsForPlayer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("DONT_DISPATCH_COPS_FOR_PLAYER", p0, p1); }
	static void DontDisplayLoadingOnFadeThisFrame() { NativeInvoke::Invoke<unsigned int>("DONT_DISPLAY_LOADING_ON_FADE_THIS_FRAME"); }
	static void DontSuppressAnyPedModels() { NativeInvoke::Invoke<unsigned int>("DONT_SUPPRESS_ANY_PED_MODELS"); }
	static void DontSuppressCarModel(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DONT_SUPPRESS_CAR_MODEL", p0); }
	static void DontSuppressPedModel(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("DONT_SUPPRESS_PED_MODEL", p0); }
	static void DrawCheckpoint(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("DRAW_CHECKPOINT", p0, p1, p2, p3, p4, p5, p6); }
	static void DrawCheckpointWithAlpha(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("DRAW_CHECKPOINT_WITH_ALPHA", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void DrawColouredCylinder(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("DRAW_COLOURED_CYLINDER", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void DrawCurvedWindow(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("DRAW_CURVED_WINDOW", p0, p1, p2, p3, p4); }
	static void DrawFrontendHelperText(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("DRAW_FRONTEND_HELPER_TEXT", p0, p1, p2); }
	static void DrawLightWithRange(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("DRAW_LIGHT_WITH_RANGE", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void DrawMovie(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("DRAW_MOVIE", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void DrawRect(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("DRAW_RECT", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void DrawSprite(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("DRAW_SPRITE", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void DrawSpritePhoto(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("DRAW_SPRITE_PHOTO", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void EnableChaseAudio(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ENABLE_CHASE_AUDIO", p0); }
	static void EnableEndCreditsFade() { NativeInvoke::Invoke<unsigned int>("ENABLE_END_CREDITS_FADE"); }
	static void EnableSaveHouse(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("ENABLE_SAVE_HOUSE", p0, p1); }
	static void EnableXboxScreenSaver(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("ENABLE_XBOX_SCREEN_SAVER", p0); }
	static void EndCamCommands(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("END_CAM_COMMANDS", p0); }
	static void EndCharSearchCriteria() { NativeInvoke::Invoke<unsigned int>("END_CHAR_SEARCH_CRITERIA"); }
	static void EndWidgetGroup() { NativeInvoke::Invoke<unsigned int>("END_WIDGET_GROUP"); }
	static void EvolvePtFx(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("EVOLVE_PTFX", p0, p1, p2); }
	static void ExplodeCarInCutscene(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("EXPLODE_CAR_IN_CUTSCENE", p0, p1); }
	static void FindStreetNameAtPosition(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("FIND_STREET_NAME_AT_POSITION", p0, p1, p2, p3, p4); }
	static void FindNearestCollectableBinBags(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("FIND_NEAREST_COLLECTABLE_BIN_BAGS", p0, p1, p2); }
	static unsigned int FindNetworkKillerOfPlayer(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("FIND_NETWORK_KILLER_OF_PLAYER", p0); }
	static unsigned int FindPositionInRecording(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("FIND_POSITION_IN_RECORDING", p0); }
	static void FindPrimaryPopulationZoneGroup(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("FIND_PRIMARY_POPULATION_ZONE_GROUP", p0, p1); }
	static unsigned int FindTimePositionInRecording(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("FIND_TIME_POSITION_IN_RECORDING", p0); }
	static unsigned int FinishWidgetCombo(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("FINISH_WIDGET_COMBO", p0, p1); }
	static void FlashRoute(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("FLASH_ROUTE", p0); }
	static void FlushAllOutOfDateRadarBlipsFromMissionCleanupList() { NativeInvoke::Invoke<unsigned int>("FLUSH_ALL_OUT_OF_DATE_RADAR_BLIPS_FROM_MISSION_CLEANUP_LIST"); }
	static void FlushAllSpawnBlockingAreas() { NativeInvoke::Invoke<unsigned int>("FLUSH_ALL_SPAWN_BLOCKING_AREAS"); }
	static void FlushCoverBlockingAreas() { NativeInvoke::Invoke<unsigned int>("FLUSH_COVER_BLOCKING_AREAS"); }
	static void FlushScenarioBlockingAreas() { NativeInvoke::Invoke<unsigned int>("FLUSH_SCENARIO_BLOCKING_AREAS"); }
	static void ForceAirDragMultForPlayersCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("FORCE_AIR_DRAG_MULT_FOR_PLAYERS_CAR", p0, p1); }
	static void ForceFullVoice(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("FORCE_FULL_VOICE", p0); }
	static void ForceHighLod(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("FORCE_HIGH_LOD", p0); }
	static void ForceNoCamPause(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("FORCE_NO_CAM_PAUSE", p0); }
	static void ForcePedToFleeWhilstDrivingVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("FORCE_PED_TO_FLEE_WHILST_DRIVING_VEHICLE", p0, p1); }
	static void ForcePedToLoadCover(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("FORCE_PED_TO_LOAD_COVER", p0, p1); }
	static void ForceRadioTrack(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("FORCE_RADIO_TRACK", p0, p1, p2, p3); }
	static void ForceSpawnScenarioPedsInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("FORCE_SPAWN_SCENARIO_PEDS_IN_AREA", p0, p1, p2, p3, p4); }
	static void GenerateDirections(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("GENERATE_DIRECTIONS", p0, p1, p2, p3, p4); }
	static unsigned int GetAudibleMusicTrackTextId() { return NativeInvoke::Invoke<unsigned int>("GET_AUDIBLE_MUSIC_TRACK_TEXT_ID"); }
	static unsigned int GetBitsInRange(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("GET_BITS_IN_RANGE", p0, p1, p2); }
	static void GetCamFov(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_CAM_FOV", p0, p1); }
	static void GetCamPos(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("GET_CAM_POS", p0, p1, p2, p3); }
	static void GetCamRot(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("GET_CAM_ROT", p0, p1, p2, p3); }
	static void GetCarModelValue(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_CAR_MODEL_VALUE", p0, p1); }
	static void GetCinematicCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_CINEMATIC_CAM", p0); }
	static unsigned int GetClosestCarNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("GET_CLOSEST_CAR_NODE", p0, p1, p2, p3, p4, p5); }
	static unsigned int GetClosestCarNodeWithHeading(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return NativeInvoke::Invoke<unsigned int>("GET_CLOSEST_CAR_NODE_WITH_HEADING", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int GetClosestMajorCarNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("GET_CLOSEST_MAJOR_CAR_NODE", p0, p1, p2, p3, p4, p5); }
	static unsigned int GetClosestNetworkRestartNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("GET_CLOSEST_NETWORK_RESTART_NODE", p0, p1, p2, p3, p4); }
	static unsigned int GetClosestRoad(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { return NativeInvoke::Invoke<unsigned int>("GET_CLOSEST_ROAD", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void GetCoordinatesForNetworkRestartNode(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("GET_COORDINATES_FOR_NETWORK_RESTART_NODE", p0, p1, p2); }
	static unsigned int GetCurrentPlaybackNumberForCar(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_CURRENT_PLAYBACK_NUMBER_FOR_CAR", p0); }	
	static unsigned int GetCurrentScriptedConversationLine() { return NativeInvoke::Invoke<unsigned int>("GET_CURRENT_SCRIPTED_CONVERSATION_LINE"); }
	static unsigned int GetCutsceneAudioTimeMs() { return NativeInvoke::Invoke<unsigned int>("GET_CUTSCENE_AUDIO_TIME_MS"); }
	static void GetCutscenePedPosition(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_CUTSCENE_PED_POSITION", p0, p1); }
	static unsigned int GetCutsceneSectionPlaying() { return NativeInvoke::Invoke<unsigned int>("GET_CUTSCENE_SECTION_PLAYING"); }
	static unsigned int GetCutsceneTime() { return NativeInvoke::Invoke<unsigned int>("GET_CUTSCENE_TIME"); }
	static void GetDebugCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_DEBUG_CAM", p0); }
	static unsigned int GetDestroyerOfNetworkId(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("GET_DESTROYER_OF_NETWORK_ID", p0, p1); }
	static void GetFollowVehicleCamSubmode(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_FOLLOW_VEHICLE_CAM_SUBMODE", p0); }
	static void GetFrameTime(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_FRAME_TIME", p0); }
	static void GetFrontEndDesignValue(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("GET_FRONTEND_DESIGN_VALUE", p0, p1, p2); }
	static void GetGameCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_GAME_CAM", p0); }
	static void GetGameCamChild(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_GAME_CAM_CHILD", p0); }
	static void GetGameViewportId(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_GAME_VIEWPORT_ID", p0); }
	static unsigned int GetGamerNetworkScore(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("GET_GAMER_NETWORK_SCORE", p0, p1, p2); }
	static void GetHelpMessageBoxSize(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_HELP_MESSAGE_BOX_SIZE", p0, p1); }
	static unsigned int GetHostId() { return NativeInvoke::Invoke<unsigned int>("GET_HOST_ID"); }
	static void GetKeyForViewportInRoom(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_KEY_FOR_VIEWPORT_IN_ROOM", p0, p1); }
	static unsigned int GetLocalGamerlevelFromProfilesettings() { return NativeInvoke::Invoke<unsigned int>("GET_LOCAL_GAMERLEVEL_FROM_PROFILESETTINGS"); }
	static unsigned int GetLocalPlayerMPCash() { return NativeInvoke::Invoke<unsigned int>("GET_LOCAL_PLAYER_MP_CASH"); }
	static void GetMobilePhoneRenderId(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_MOBILE_PHONE_RENDER_ID", p0); }
	static unsigned int GetMobilePhoneTaskSubTask(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("GET_MOBILE_PHONE_TASK_SUB_TASK", p0, p1); }
	static unsigned int GetMotionControlPreference(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_MOTION_CONTROL_PREFERENCE", p0); }
	static void GetNetworkIdFromObject(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_NETWORK_ID_FROM_OBJECT", p0, p1); }
	static void GetNetworkIdFromPed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_NETWORK_ID_FROM_PED", p0, p1); }
	static void GetNetworkIdFromVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_NETWORK_ID_FROM_VEHICLE", p0, p1); }
	static void GetNetworkTimer(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_NETWORK_TIMER", p0); }
	static unsigned int GetNextClosestCarNodeWithHeadingOnIsland(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("GET_NEXT_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int GetNoOfPlayersInTeam(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_NO_OF_PLAYERS_IN_TEAM", p0); }
	static unsigned int GetNthClosestCarNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return NativeInvoke::Invoke<unsigned int>("GET_NTH_CLOSEST_CAR_NODE", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int GetNthClosestCarNodeFavourDirection(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("GET_NTH_CLOSEST_CAR_NODE_FAVOUR_DIRECTION", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static unsigned int GetNthClosestCarNodeWithHeading(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int GetNthClosestCarNodeWithHeadingOnIsland(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { return NativeInvoke::Invoke<unsigned int>("GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static unsigned int GetNumberOfPlayers() { return NativeInvoke::Invoke<unsigned int>("GET_NUMBER_OF_PLAYERS"); }
	static unsigned int GetNumberOfWebPageLinks(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_NUMBER_OF_WEB_PAGE_LINKS", p0); }
	static void GetObjectFromNetworkId(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_OBJECT_FROM_NETWORK_ID", p0, p1); }
	static void GetPedFromNetworkId(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_PED_FROM_NETWORK_ID", p0, p1); }
	static unsigned int GetPlayerRankLevelDuringMP(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_PLAYER_RANK_LEVEL_DURING_MP", p0); }
	static void GetPlayerRGBColour(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("GET_PLAYER_RGB_COLOUR", p0, p1, p2, p3); }
	static unsigned int GetPlayerTeam(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_PLAYER_TEAM", p0); }
	static unsigned int GetPlayerToPlaceBombInCar(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_PLAYER_TO_PLACE_BOMB_IN_CAR", p0); }
	static void GetPlayersLastCarNoSave(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_PLAYERS_LAST_CAR_NO_SAVE", p0); }
	static unsigned int GetPlayerSettingsModelChoice() { return NativeInvoke::Invoke<unsigned int>("GET_PLAYERSETTINGS_MODEL_CHOICE"); }
	static void GetPositionOfCarRecordingAtTime(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("GET_POSITION_OF_CAR_RECORDING_AT_TIME", p0, p1, p2); }
	static unsigned int GetProfileSetting(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_PROFILE_SETTING", p0); }
	static unsigned int GetRandomCarNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("GET_RANDOM_CAR_NODE", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static unsigned int GetRandomNetworkRestartNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("GET_RANDOM_NETWORK_RESTART_NODE", p0, p1, p2, p3, p4, p5); }
	static unsigned int GetRandomNetworkRestartNodeUsingGroupList(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("GET_RANDOM_NETWORK_RESTART_NODE_USING_GROUP_LIST", p0, p1, p2, p3, p4, p5); }
	static void GetRootCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_ROOT_CAM", p0); }
	static void GetScreenViewportId(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_SCREEN_VIEWPORT_ID", p0); }
	static void GetScriptCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_SCRIPT_CAM", p0); }
	static void GetScriptRendertargetRenderId(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("GET_SCRIPT_RENDERTARGET_RENDER_ID", p0); }
	static void GetScriptTaskStatus(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("GET_SCRIPT_TASK_STATUS", p0, p1, p2); }
	static void GetSequenceProgress(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_SEQUENCE_PROGRESS", p0, p1); }
	static unsigned int GetSortedNetworkRestartNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("GET_SORTED_NETWORK_RESTART_NODE", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static unsigned int GetSortedNetworkRestartNodeUsingGroupList(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("GET_SORTED_NETWORK_RESTART_NODE_USING_GROUP_LIST", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void GetSpawnCoordinatesForCarNode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("GET_SPAWN_COORDINATES_FOR_CAR_NODE", p0, p1, p2, p3, p4, p5); }
	static unsigned int GetSpeechForEmergencyServiceCall() { return NativeInvoke::Invoke<unsigned int>("GET_SPEECH_FOR_EMERGENCY_SERVICE_CALL"); }
	static void GetStateOfClosestDoorOfType(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("GET_STATE_OF_CLOSEST_DOOR_OF_TYPE", p0, p1, p2, p3, p4, p5); }
	static unsigned int GetStringFromTextFile(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_STRING_FROM_TEXT_FILE", p0); }
	static unsigned int GetTaskPlaceCarBombUnsuccessful() { return NativeInvoke::Invoke<unsigned int>("GET_TASK_PLACE_CAR_BOMB_UNSUCCESSFUL"); }
	static void GetTeamRGBColour(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("GET_TEAM_RGB_COLOUR", p0, p1, p2, p3); }
	static unsigned int GetTotalDurationOfCarRecording(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_TOTAL_DURATION_OF_CAR_RECORDING", p0); }
	static void GetVehicleFromNetworkId(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("GET_VEHICLE_FROM_NETWORK_ID", p0, p1); }
	static unsigned int GetWebPageHeight(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("GET_WEB_PAGE_HEIGHT", p0); }
	static unsigned int GetWebPageLinkAtPosn(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("GET_WEB_PAGE_LINK_AT_POSN", p0, p1, p2); }
	static unsigned int GetWebPageLinkHref(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("GET_WEB_PAGE_LINK_HREF", p0, p1); }
	static void GivePedFakeNetworkName(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("GIVE_PED_FAKE_NETWORK_NAME", p0, p1, p2, p3, p4, p5); }
	static void HandleAudioAnimEvent(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("HANDLE_AUDIO_ANIM_EVENT", p0, p1); }
	static unsigned int HasCarRecordingBeenLoaded(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("HAS_CAR_RECORDING_BEEN_LOADED", p0); }
	static unsigned int HasCharAnimFinished(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("HAS_CHAR_ANIM_FINISHED", p0, p1, p2); }
	static unsigned int HasControlOfNetworkId(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("HAS_CONTROL_OF_NETWORK_ID", p0); }
	static unsigned int HasCutsceneFinished() { return NativeInvoke::Invoke<unsigned int>("HAS_CUTSCENE_FINISHED"); }
	static unsigned int HasCutsceneLoaded() { return NativeInvoke::Invoke<unsigned int>("HAS_CUTSCENE_LOADED"); }
	static unsigned int HasFragmentRootOfClosestObjectOfTypeBeenDamaged(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("HAS_FRAGMENT_ROOT_OF_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED", p0, p1, p2, p3, p4); }
	static unsigned int HasGamerChangedNetworkModelSettings() { return NativeInvoke::Invoke<unsigned int>("HAS_GAMER_CHANGED_NETWORK_MODEL_SETTINGS"); }
	static unsigned int HasNetworkPlayerLeftGame(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("HAS_NETWORK_PLAYER_LEFT_GAME", p0); }
	static unsigned int HasOverridenSitIdleAnimFinished(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("HAS_OVERRIDEN_SIT_IDLE_ANIM_FINISHED", p0); }
	static unsigned int HasReloadedWithMotionControl(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("HAS_RELOADED_WITH_MOTION_CONTROL", p0, p1); }
	static void HideCharWeaponForScriptedCutscene(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("HIDE_CHAR_WEAPON_FOR_SCRIPTED_CUTSCENE", p0, p1); }
	static void HintCam(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("HINT_CAM", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int HowLongHasNetworkPlayerBeenDeadFor(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("HOW_LONG_HAS_NETWORK_PLAYER_BEEN_DEAD_FOR", p0); }
	static void InitCutscene(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("INIT_CUTSCENE", p0); }
	static void InitDebugWidgets() { NativeInvoke::Invoke<unsigned int>("INIT_DEBUG_WIDGETS"); }
	static void InitFrontendHelperText() { NativeInvoke::Invoke<unsigned int>("INIT_FRONTEND_HELPER_TEXT"); }
	static unsigned int IsAmbientSpeechDisabled(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_AMBIENT_SPEECH_DISABLED", p0); }
	static unsigned int IsAmbientSpeechPlaying(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_AMBIENT_SPEECH_PLAYING", p0); }
	static unsigned int IsAnyCharShootingInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { return NativeInvoke::Invoke<unsigned int>("IS_ANY_CHAR_SHOOTING_IN_AREA", p0, p1, p2, p3, p4, p5, p6); }
	static unsigned int IsAnySpeechPlaying(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_ANY_SPEECH_PLAYING", p0); }
	static unsigned int IsBitSet(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("IS_BIT_SET", p0, p1); }
	static unsigned int IsCamActive(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_CAM_ACTIVE", p0); }
	static unsigned int IsCamInterpolating() { return NativeInvoke::Invoke<unsigned int>("IS_CAM_INTERPOLATING"); }
	static unsigned int IsCamPropagating(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_CAM_PROPAGATING", p0); }
	static unsigned int IsCharPlayingAnim(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("IS_CHAR_PLAYING_ANIM", p0, p1, p2); }
	static unsigned int IsCharRespondingToEvent(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("IS_CHAR_RESPONDING_TO_EVENT", p0, p1); }
	static unsigned int IsDamageTrackerActiveOnNetworkId(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID", p0); }
	static unsigned int IsDebugCameraOn() { return NativeInvoke::Invoke<unsigned int>("IS_DEBUG_CAMERA_ON"); }
	static unsigned int IsNetworkGamePending() { return NativeInvoke::Invoke<unsigned int>("IS_NETWORK_GAME_PENDING"); }
	static unsigned int IsNetworkPlayerActive(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_NETWORK_PLAYER_ACTIVE", p0); }
	static unsigned int IsNetworkSession() { return NativeInvoke::Invoke<unsigned int>("IS_NETWORK_SESSION"); }
	static unsigned int IsNonFragObjectSmashed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { return NativeInvoke::Invoke<unsigned int>("IS_NON_FRAG_OBJECT_SMASHED", p0, p1, p2, p3, p4); }
	static unsigned int IsPlaybackGoingOnForCar(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_PLAYBACK_GOING_ON_FOR_CAR", p0); }
	static unsigned int IsPlayerLoggingInNp() { return NativeInvoke::Invoke<unsigned int>("IS_PLAYER_LOGGING_IN_NP"); }
	static unsigned int IsPlayerOnline() { return NativeInvoke::Invoke<unsigned int>("IS_PLAYER_ONLINE"); }
	static unsigned int IsPlayerOnlineGamespy() { return NativeInvoke::Invoke<unsigned int>("IS_PLAYER_ONLINE_GAMESPY"); }
	static unsigned int IsPlayerOnlineNp() { return NativeInvoke::Invoke<unsigned int>("IS_PLAYER_ONLINE_NP"); }
	static unsigned int IsPlayerReadyForCutscene(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_PLAYER_READY_FOR_CUTSCENE", p0); }
	static unsigned int IsPlayerScriptControlOn(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_PLAYER_SCRIPT_CONTROL_ON", p0); }
	static unsigned int IsRecordingGoingOnForCar(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_RECORDING_GOING_ON_FOR_CAR", p0); }
	static unsigned int IsScriptedConversationOngoing() { return NativeInvoke::Invoke<unsigned int>("IS_SCRIPTED_CONVERSATION_ONGOING"); }
	static unsigned int IsScriptedSpeechPlaying(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_SCRIPTED_SPEECH_PLAYING", p0); }
	static unsigned int IsSpecificCamInterpolating(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_SPECIFIC_CAM_INTERPOLATING", p0); }
	static unsigned int IsSphereVisibleToAnotherMachine(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE", p0, p1, p2, p3); }
	static unsigned int IsStreamingPriorityRequests() { return NativeInvoke::Invoke<unsigned int>("IS_STREAMING_PRIORITY_REQUESTS"); }
	static unsigned int IsThisHelpMessageBeingDisplayed(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("IS_THIS_HELP_MESSAGE_BEING_DISPLAYED", p0); }
	static unsigned int IsThisHelpMessageWithNumberBeingDisplayed(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("IS_THIS_HELP_MESSAGE_WITH_NUMBER_BEING_DISPLAYED", p0, p1); }
	static unsigned int IsThisHelpMessageWithStringBeingDisplayed(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("IS_THIS_HELP_MESSAGE_WITH_STRING_BEING_DISPLAYED", p0, p1); }
	static unsigned int IsThisMachineTheServer() { return NativeInvoke::Invoke<unsigned int>("IS_THIS_MACHINE_THE_SERVER"); }
	static unsigned int IsThisPrintBeingDisplayed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10) { return NativeInvoke::Invoke<unsigned int>("IS_THIS_PRINT_BEING_DISPLAYED", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static unsigned int IsWorldPointWithinBrainActivationRange() { return NativeInvoke::Invoke<unsigned int>("IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE"); }
	static unsigned int IsXbox360Version() { return NativeInvoke::Invoke<unsigned int>("IS_XBOX360_VERSION"); }
	static void LaunchLocalPlayerInNetworkGame() { NativeInvoke::Invoke<unsigned int>("LAUNCH_LOCAL_PLAYER_IN_NETWORK_GAME"); }
	static unsigned int LoadAllPathNodes(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("LOAD_ALL_PATH_NODES", p0); }
	static void LoadCharDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("LOAD_CHAR_DECISION_MAKER", p0, p1); }
	static void LoadCombatDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("LOAD_COMBAT_DECISION_MAKER", p0, p1); }
	static void LoadPathNodesInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("LOAD_PATH_NODES_IN_AREA", p0, p1, p2, p3); }
	static void LoadWebPage(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("LOAD_WEB_PAGE", p0, p1); }
	static unsigned int LocalPlayerIsReadyToStartPlaying() { return NativeInvoke::Invoke<unsigned int>("LOCAL_PLAYER_IS_READY_TO_START_PLAYING"); }
	static unsigned int LookAtNearbyEntityWithSpecialAttribute(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("LOOK_AT_NEARBY_ENTITY_WITH_SPECIAL_ATTRIBUTE", p0, p1, p2, p3, p4, p5); }
	static void MakePlayerSafeForCutscene(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("MAKE_PLAYER_SAFE_FOR_CUTSCENE", p0); }
	static void MissionAudioBankNoLongerNeeded() { NativeInvoke::Invoke<unsigned int>("MISSION_AUDIO_BANK_NO_LONGER_NEEDED"); }
	static void MuteGameworldAndPositionedRadioForTv(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV", p0); }
	static void MuteGameworldAudio(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("MUTE_GAMEWORLD_AUDIO", p0); }
	static void MutePositionedRadio(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("MUTE_POSITIONED_RADIO", p0); }
	static unsigned int NetworkAcceptInvite(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_ACCEPT_INVITE", p0); }
	static unsigned int NetworkAdvertiseSession(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_ADVERTISE_SESSION", p0); }
	static unsigned int NetworkAllPartyMembersPresent() { return NativeInvoke::Invoke<unsigned int>("NETWORK_ALL_PARTY_MEMBERS_PRESENT"); }
	static unsigned int NetworkAmIBlockedByPlayer(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_AM_I_BLOCKED_BY_PLAYER", p0); }
	static unsigned int NetworkAmIMutedByPlayer(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_AM_I_MUTED_BY_PLAYER", p0); }
	static unsigned int NetworkChangeGameMode(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { return NativeInvoke::Invoke<unsigned int>("NETWORK_CHANGE_GAME_MODE", p0, p1, p2, p3); }
	static unsigned int NetworkChangeGameModePending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_CHANGE_GAME_MODE_PENDING"); }
	static unsigned int NetworkChangeGameModeSucceeded() { return NativeInvoke::Invoke<unsigned int>("NETWORK_CHANGE_GAME_MODE_SUCCEEDED"); }
	static unsigned int NetworkCheckInviteArrival() { return NativeInvoke::Invoke<unsigned int>("NETWORK_CHECK_INVITE_ARRIVAL"); }
	static void NetworkClearInviteArrival() { NativeInvoke::Invoke<unsigned int>("NETWORK_CLEAR_INVITE_ARRIVAL"); }
	static unsigned int NetworkClearSummons() { return NativeInvoke::Invoke<unsigned int>("NETWORK_CLEAR_SUMMONS"); }
	static unsigned int NetworkDidInviteFriend(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_DID_INVITE_FRIEND", p0); }
	static unsigned int NetworkEndSession() { return NativeInvoke::Invoke<unsigned int>("NETWORK_END_SESSION"); }
	static unsigned int NetworkEndSessionPending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_END_SESSION_PENDING"); }
	static void NetworkFindGame(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("NETWORK_FIND_GAME", p0, p1, p2, p3); }
	static unsigned int NetworkFindGamePending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_FIND_GAME_PENDING"); }
	static unsigned int NetworkGetFriendCount() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_FRIEND_COUNT"); }
	static unsigned int NetworkGetFriendName(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_FRIEND_NAME", p0); }
	static unsigned int NetworkGetGameMode() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_GAME_MODE"); }
	static unsigned int NetworkGetMaxPrivateSlots() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_MAX_PRIVATE_SLOTS"); }
	static unsigned int NetworkGetMaxSlots() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_MAX_SLOTS"); }
	static unsigned int NetworkGetMetPlayerName(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_MET_PLAYER_NAME", p0); }
	static unsigned int NetworkGetNumPartyMembers() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_NUM_PARTY_MEMBERS"); }
	static unsigned int NetworkGetNumPlayersMet() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_NUM_PLAYERS_MET"); }
	static unsigned int NetworkGetNumUnacceptedInvites() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_NUM_UNACCEPTED_INVITES"); }
	static unsigned int NetworkGetNumUnfilledReservations() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_NUM_UNFILLED_RESERVATIONS"); }
	static unsigned int NetworkGetNumberOfGames() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_NUMBER_OF_GAMES"); }
	static unsigned int NetworkGetRendezvousHostPlayerId() { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_RENDEZVOUS_HOST_PLAYER_ID"); }
	static unsigned int NetworkGetUnacceptedInviteEpisode(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_UNACCEPTED_INVITE_EPISODE", p0); }
	static unsigned int NetworkGetUnacceptedInviteGameMode(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_UNACCEPTED_INVITE_GAME_MODE", p0); }
	static unsigned int NetworkGetUnacceptedInviterName(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_GET_UNACCEPTED_INVITER_NAME", p0); }
	static unsigned int NetworkHaveAcceptedInvite() { return NativeInvoke::Invoke<unsigned int>("NETWORK_HAVE_ACCEPTED_INVITE"); }
	static unsigned int NetworkHaveOnlinePrivileges() { return NativeInvoke::Invoke<unsigned int>("NETWORK_HAVE_ONLINE_PRIVILEGES"); }
	static unsigned int NetworkHaveSummons() { return NativeInvoke::Invoke<unsigned int>("NETWORK_HAVE_SUMMONS"); }
	static unsigned int NetworkHostGame(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { return NativeInvoke::Invoke<unsigned int>("NETWORK_HOST_GAME", p0, p1, p2, p3, p4, p5); }
	static unsigned int NetworkHostGamePending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_HOST_GAME_PENDING"); }
	static unsigned int NetworkHostGameSucceeded() { return NativeInvoke::Invoke<unsigned int>("NETWORK_HOST_GAME_SUCCEEDED"); }
	static unsigned int NetworkHostRendezvous(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("NETWORK_HOST_RENDEZVOUS", p0, p1, p2); }
	static unsigned int NetworkInviteFriend(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("NETWORK_INVITE_FRIEND", p0, p1); }
	static unsigned int NetworkIsCommonEpisode(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_COMMON_EPISODE", p0); }
	static unsigned int NetworkIsFriendInSameTitle(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_FRIEND_IN_SAME_TITLE", p0); }
	static unsigned int NetworkIsFriendOnline(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_FRIEND_ONLINE", p0); }
	static unsigned int NetworkIsGameRanked() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_GAME_RANKED"); }
	static unsigned int NetworkIsInviteeOnline() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_INVITEE_ONLINE"); }
	static unsigned int NetworkIsOperationPending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_OPERATION_PENDING"); }
	static unsigned int NetworkIsPlayerBlockedByMe(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_PLAYER_BLOCKED_BY_ME", p0); }
	static unsigned int NetworkIsPlayerMutedByMe(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_PLAYER_MUTED_BY_ME", p0); }
	static unsigned int NetworkIsPlayerTalking(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_PLAYER_TALKING", p0); }
	static unsigned int NetworkIsRendezvous() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_RENDEZVOUS"); }
	static unsigned int NetworkIsRendezvousHost() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_RENDEZVOUS_HOST"); }
	static unsigned int NetworkIsSessionAdvertised() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_SESSION_ADVERTISED"); }
	static unsigned int NetworkIsSessionInvitable() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_SESSION_INVITABLE"); }
	static unsigned int NetworkIsSessionStarted() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_SESSION_STARTED"); }
	static unsigned int NetworkIsTvt() { return NativeInvoke::Invoke<unsigned int>("NETWORK_IS_TVT"); }
	static unsigned int NetworkJoinGame(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_JOIN_GAME", p0); }
	static unsigned int NetworkJoinGamePending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_JOIN_GAME_PENDING"); }
	static unsigned int NetworkJoinGameSucceeded() { return NativeInvoke::Invoke<unsigned int>("NETWORK_JOIN_GAME_SUCCEEDED"); }
	static unsigned int NetworkJoinSummons() { return NativeInvoke::Invoke<unsigned int>("NETWORK_JOIN_SUMMONS"); }
	static void NetworkKickPlayer(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_KICK_PLAYER", p0); }
	static unsigned int NetworkLeaveGame() { return NativeInvoke::Invoke<unsigned int>("NETWORK_LEAVE_GAME"); }
	static unsigned int NetworkLeaveGamePending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_LEAVE_GAME_PENDING"); }
	static unsigned int NetworkPlayerHasDiedRecently(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_PLAYER_HAS_DIED_RECENTLY", p0); }
	static unsigned int NetworkPlayerHasHeadset(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_PLAYER_HAS_HEADSET", p0); }
	static unsigned int NetworkRestoreGameConfig(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("NETWORK_RESTORE_GAME_CONFIG", p0); }
	static unsigned int NetworkReturnToRendezvous() { return NativeInvoke::Invoke<unsigned int>("NETWORK_RETURN_TO_RENDEZVOUS"); }
	static unsigned int NetworkReturnToRendezvousPending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_RETURN_TO_RENDEZVOUS_PENDING"); }
	static unsigned int NetworkReturnToRendezvousSucceeded() { return NativeInvoke::Invoke<unsigned int>("NETWORK_RETURN_TO_RENDEZVOUS_SUCCEEDED"); }
	static void NetworkSetFriendlyFireOption(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SET_FRIENDLY_FIRE_OPTION", p0); }
	static void NetworkSetHealthReticuleOption(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SET_HEALTH_RETICULE_OPTION", p0); }
	static unsigned int NetworkSetPlayerMuted(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("NETWORK_SET_PLAYER_MUTED", p0, p1); }
	static void NetworkSetTalkerFocus(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SET_TALKER_FOCUS", p0); }
	static void NetworkSetTalkerProximity(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SET_TALKER_PROXIMITY", p0); }
	static void NetworkSetTeamOnlyChat(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SET_TEAM_ONLY_CHAT", p0); }
	static void NetworkShowFriendProfileUi(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SHOW_FRIEND_PROFILE_UI", p0); }
	static void NetworkShowMetPlayerFeedbackUi(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SHOW_MET_PLAYER_FEEDBACK_UI", p0); }
	static void NetworkShowMetPlayerProfileUi(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SHOW_MET_PLAYER_PROFILE_UI", p0); }
	static void NetworkShowPlayerProfileUi(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_SHOW_PLAYER_PROFILE_UI", p0); }
	static unsigned int NetworkStartSession() { return NativeInvoke::Invoke<unsigned int>("NETWORK_START_SESSION"); }
	static unsigned int NetworkStartSessionPending() { return NativeInvoke::Invoke<unsigned int>("NETWORK_START_SESSION_PENDING"); }
	static unsigned int NetworkStartSessionSucceeded() { return NativeInvoke::Invoke<unsigned int>("NETWORK_START_SESSION_SUCCEEDED"); }
	static void NetworkStoreGameConfig(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("NETWORK_STORE_GAME_CONFIG", p0); }
	static unsigned int NetworkStoreSinglePlayerGame() { return NativeInvoke::Invoke<unsigned int>("NETWORK_STORE_SINGLE_PLAYER_GAME"); }
	static void NewMobilePhoneCall() { NativeInvoke::Invoke<unsigned int>("NEW_MOBILE_PHONE_CALL"); }
	static void NewScriptedConversation() { NativeInvoke::Invoke<unsigned int>("NEW_SCRIPTED_CONVERSATION"); }
	static void OpenDebugFile() { NativeInvoke::Invoke<unsigned int>("OPEN_DEBUG_FILE"); }
	static void OpenSequenceTask(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("OPEN_SEQUENCE_TASK", p0); }
	static void OverrideFreezeFlags(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("OVERRIDE_FREEZE_FLAGS", p0); }
	static void OverrideNextRestart(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("OVERRIDE_NEXT_RESTART", p0, p1, p2, p3); }
	static void OverrideNumberOfParkedCars(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("OVERRIDE_NUMBER_OF_PARKED_CARS", p0); }
	static void PausePlaybackRecordedCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PAUSE_PLAYBACK_RECORDED_CAR", p0); }
	static void PauseScriptedConversation(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PAUSE_SCRIPTED_CONVERSATION", p0); }
	static void PlayAudioEvent(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PLAY_AUDIO_EVENT", p0); }
	static void PlayAudioEventFromObject(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PLAY_AUDIO_EVENT_FROM_OBJECT", p0, p1); }
	static void PlayAudioEventFromPed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PLAY_AUDIO_EVENT_FROM_PED", p0, p1); }
	static void PlayAudioEventFromVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PLAY_AUDIO_EVENT_FROM_VEHICLE", p0, p1); }
	static void PlayFireSoundFromPosition(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("PLAY_FIRE_SOUND_FROM_POSITION", p0, p1, p2, p3); }
	static unsigned int PlayerWantsToJoinNetworkGame(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("PLAYER_WANTS_TO_JOIN_NETWORK_GAME", p0); }
	static void PlayStatsInt(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PLAYSTATS_INT", p0, p1); }
	static void PlayStatsMissionCancelled(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PLAYSTATS_MISSION_CANCELLED", p0); }
	static void PlayStatsMissionFailed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PLAYSTATS_MISSION_FAILED", p0); }
	static void PlayStatsMissionPassed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PLAYSTATS_MISSION_PASSED", p0); }
	static void PlayStatsMissionStarted(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PLAYSTATS_MISSION_STARTED", p0); }
	static void PointCamAtCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("POINT_CAM_AT_COORD", p0, p1, p2, p3); }
	static void PointCamAtObject(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("POINT_CAM_AT_OBJECT", p0, p1); }
	static void PointCamAtPed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("POINT_CAM_AT_PED", p0, p1); }
	static void PointCamAtVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("POINT_CAM_AT_VEHICLE", p0, p1); }
	static unsigned int PreloadStream(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("PRELOAD_STREAM", p0); }
	static unsigned int PreloadStreamWithStartOffset(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("PRELOAD_STREAM_WITH_START_OFFSET", p0, p1); }
	static void PreviewRingtone(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PREVIEW_RINGTONE", p0); }
	static void Print(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("PRINT", p0, p1, p2); }
	static void PrintBig(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("PRINT_BIG", p0, p1, p2); }
	static void PrintHelp(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP", p0); }
	static void PrintHelpForever(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP_FOREVER", p0); }
	static void PrintHelpForeverWithNumber(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP_FOREVER_WITH_NUMBER", p0, p1); }
	static void PrintHelpForeverWithString(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP_FOREVER_WITH_STRING", p0, p1); }
	static void PrintHelpForeverWithStringNoSound(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP_FOREVER_WITH_STRING_NO_SOUND", p0, p1); }
	static void PrintHelpWithNumber(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP_WITH_NUMBER", p0, p1); }
	static void PrintHelpWithString(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP_WITH_STRING", p0, p1); }
	static void PrintHelpWithStringNoSound(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("PRINT_HELP_WITH_STRING_NO_SOUND", p0, p1); }
	static void PrintNow(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("PRINT_NOW", p0, p1, p2); }
	static void PrintStringInString(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("PRINT_STRING_IN_STRING", p0, p1, p2, p3); }
	static void PrintStringInStringNow(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("PRINT_STRING_IN_STRING_NOW", p0, p1, p2, p3); }
	static void PrintStringWithLiteralStringNow(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("PRINT_STRING_WITH_LITERAL_STRING_NOW", p0, p1, p2, p3); }
	static void PrintWith2Numbers(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("PRINT_WITH_2_NUMBERS", p0, p1, p2, p3, p4); }
	static void PrintWith2NumbersNow(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("PRINT_WITH_2_NUMBERS_NOW", p0, p1, p2, p3, p4); }
	static void PrintWithNumber(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("PRINT_WITH_NUMBER", p0, p1, p2, p3); }
	static void PrintWithNumberBig(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("PRINT_WITH_NUMBER_BIG", p0, p1, p2, p3); }
	static void PrintWithNumberNow(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("PRINT_WITH_NUMBER_NOW", p0, p1, p2, p3); }
	static void PrintFloat(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PRINTFLOAT", p0); }
	static void PrintInt(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PRINTINT", p0); }
	static void PrintNL() { NativeInvoke::Invoke<unsigned int>("PRINTNL"); }
	static void PrintString(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PRINTSTRING", p0); }
	static void PrintVector(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("PRINTVECTOR", p0, p1, p2); }
	static void PrioritizeStreamingRequest() { NativeInvoke::Invoke<unsigned int>("PRIORITIZE_STREAMING_REQUEST"); }
	static void ProcessMissionDeletionList() { NativeInvoke::Invoke<unsigned int>("PROCESS_MISSION_DELETION_LIST"); }
	static void ProstituteCamActivate(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("PROSTITUTE_CAM_ACTIVATE", p0); }
	static void RegisterBestPosition(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("REGISTER_BEST_POSITION", p0, p1); }
	static void RegisterClientBroadcastVariables(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("REGISTER_CLIENT_BROADCAST_VARIABLES", p0, p1, p2); }
	static void RegisterHatedTargetsAroundPed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("REGISTER_HATED_TARGETS_AROUND_PED", p0, p1); }
	static void RegisterHatedTargetsInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("REGISTER_HATED_TARGETS_IN_AREA", p0, p1, p2, p3, p4); }
	static void RegisterHostBroadcastVariables(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("REGISTER_HOST_BROADCAST_VARIABLES", p0, p1, p2); }
	static void RegisterKillInMultiplayerGame(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("REGISTER_KILL_IN_MULTIPLAYER_GAME", p0, p1, p2); }
	static void RegisterMissionPassed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REGISTER_MISSION_PASSED", p0); }
	static void RegisterMultiplayerGameWin(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("REGISTER_MULTIPLAYER_GAME_WIN", p0, p1); }
	static void RegisterNetworkBestGameScores(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("REGISTER_NETWORK_BEST_GAME_SCORES", p0, p1, p2); }
	static void RegisterScriptWithAudio(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REGISTER_SCRIPT_WITH_AUDIO", p0); }
	static void RegisterStringForFrontendStat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("REGISTER_STRING_FOR_FRONTEND_STAT", p0, p1); }
	static void RegisterTarget(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("REGISTER_TARGET", p0, p1); }
	static void RegisterTrackNumber(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REGISTER_TRACK_NUMBER", p0); }
	static void RegisterWorldPointScriptBrain(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("REGISTER_WORLD_POINT_SCRIPT_BRAIN", p0, p1); }
	static void ReleasePathNodes() { NativeInvoke::Invoke<unsigned int>("RELEASE_PATH_NODES"); }
	static void ReleaseSoundId(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RELEASE_SOUND_ID", p0); }
	static void ReloadWebPage(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RELOAD_WEB_PAGE", p0); }
	static void RemoveCarRecording(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REMOVE_CAR_RECORDING", p0); }
	static void RemoveCarsFromGeneratorsInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("REMOVE_CARS_FROM_GENERATORS_IN_AREA", p0, p1, p2, p3, p4, p5); }
	static void RemoveDecisionMaker(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REMOVE_DECISION_MAKER", p0); }
	static void RemoveFakeNetworkNameFromPed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REMOVE_FAKE_NETWORK_NAME_FROM_PED", p0); }
	static void RemoveProjtexFromObject(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REMOVE_PROJTEX_FROM_OBJECT", p0); }
	static void RemovePtfxFromPed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REMOVE_PTFX_FROM_PED", p0); }
	static void RenderRaceTrack(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RENDER_RACE_TRACK", p0); }
	static void ReportTaggedRadioTrack(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REPORT_TAGGED_RADIO_TRACK", p0); }
	static unsigned int RequestAmbientAudioBank(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("REQUEST_AMBIENT_AUDIO_BANK", p0); }
	static void RequestCarRecording(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("REQUEST_CAR_RECORDING", p0); }
	static void RequestCollisionAtPosn(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("REQUEST_COLLISION_AT_POSN", p0, p1, p2); }


//////////

	static unsigned int RequestControlOfNetworkId(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("REQUEST_CONTROL_OF_NETWORK_ID", p0); }
	static unsigned int RequestMissionAudioBank(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("REQUEST_MISSION_AUDIO_BANK", p0); }
	static void ReserveNetworkMissionObjectsForHost(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RESERVE_NETWORK_MISSION_OBJECTS_FOR_HOST", p0); }
	static void ReserveNetworkMissionPeds(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RESERVE_NETWORK_MISSION_PEDS", p0); }
	static void ReserveNetworkMissionPedsForHost(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RESERVE_NETWORK_MISSION_PEDS_FOR_HOST", p0); }
	static void ReserveNetworkMissionVehicles(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RESERVE_NETWORK_MISSION_VEHICLES", p0); }
	static void ReserveNetworkMissionVehiclesForHost(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("RESERVE_NETWORK_MISSION_VEHICLES_FOR_HOST", p0); }
	static void ResetCamInterpCustomSpeedGraph() { NativeInvoke::Invoke<unsigned int>("RESET_CAM_INTERP_CUSTOM_SPEED_GRAPH"); }
	static void RestoreScriptArrayFromScratchpad(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("RESTORE_SCRIPT_ARRAY_FROM_SCRATCHPAD", p0, p1, p2, p3); }
	static unsigned int RestoreScriptValuesForNetworkGame(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("RESTORE_SCRIPT_VALUES_FOR_NETWORK_GAME", p0); }
	static void ResurrectNetworkPlayer(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("RESURRECT_NETWORK_PLAYER", p0, p1, p2, p3, p4); }
	static void SaveFloatToDebugFile(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SAVE_FLOAT_TO_DEBUG_FILE", p0); }
	static void SaveIntToDebugFile(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SAVE_INT_TO_DEBUG_FILE", p0); }
	static void SaveNewlineToDebugFile() { NativeInvoke::Invoke<unsigned int>("SAVE_NEWLINE_TO_DEBUG_FILE"); }
	static void SaveScriptArrayInScratchpad(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SAVE_SCRIPT_ARRAY_IN_SCRATCHPAD", p0, p1, p2, p3); }
	static void SaveStringToDebugFile(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SAVE_STRING_TO_DEBUG_FILE", p0); }
	static void SayAmbientSpeech(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SAY_AMBIENT_SPEECH", p0, p1, p2, p3, p4); }
	static void SayAmbientSpeechWithVoice(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SAY_AMBIENT_SPEECH_WITH_VOICE", p0, p1, p2, p3, p4, p5); }
	static void ScriptAssert(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SCRIPT_ASSERT", p0); }
	static void ScriptIsMovingMobilePhoneOffscreen(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN", p0); }
	static void ScriptIsUsingMobilePhone(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SCRIPT_IS_USING_MOBILE_PHONE", p0); }
	static void SearchCriteriaConsiderPedsWithFlagTrue(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_TRUE", p0); }
	static void SearchCriteriaRejectPedsWithFlagTrue(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_TRUE", p0); }
	static void SendNmMessage(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SEND_NM_MESSAGE", p0); }
	static void SetAllCarGeneratorsBackToActive() { NativeInvoke::Invoke<unsigned int>("SET_ALL_CAR_GENERATORS_BACK_TO_ACTIVE"); }
	static void SetAllMotionControlPreferencesOnOff(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ALL_MOTION_CONTROL_PREFERENCES_ON_OFF", p0); }
	static void SetAmbientVoiceName(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_AMBIENT_VOICE_NAME", p0, p1); }
	static void SetArmourPickupNetworkRegenTime(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ARMOUR_PICKUP_NETWORK_REGEN_TIME", p0); }
	static void SetBit(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_BIT", p0, p1); }
	static void SetBitsInRange(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_BITS_IN_RANGE", p0, p1, p2, p3); }
	static void SetBlockingOfNonTemporaryEvents(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_BLOCKING_OF_NON_TEMPORARY_EVENTS", p0, p1); }
	static void SetBriansMood(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_BRIANS_MOOD", p0); }
	static void SetCamActive(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_ACTIVE", p0, p1); }
	static void SetCamAttachOffset(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CAM_ATTACH_OFFSET", p0, p1, p2, p3); }
	static void SetCamAttachOffsetIsRelative(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_ATTACH_OFFSET_IS_RELATIVE", p0, p1); }
	static void SetCamBehindPed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CAM_BEHIND_PED", p0); }
	static void SetCamComponentShake(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("SET_CAM_COMPONENT_SHAKE", p0, p1, p2, p3, p4, p5, p6); }
	static void SetCamDofFocuspoint(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_CAM_DOF_FOCUSPOINT", p0, p1, p2, p3, p4); }
	static void SetCamFarClip(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_FAR_CLIP", p0, p1); }
	static void SetCamFarDof(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_FAR_DOF", p0, p1); }
	static void SetCamFov(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_FOV", p0, p1); }
	static void SetCamInFrontOfPed(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CAM_IN_FRONT_OF_PED", p0); }
	static void SetCamInheritRollVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_INHERIT_ROLL_VEHICLE", p0, p1); }
	static void SetCamInterpCustomSpeedGraph(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CAM_INTERP_CUSTOM_SPEED_GRAPH", p0); }
	static void SetCamInterpStyleCore(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_CAM_INTERP_STYLE_CORE", p0, p1, p2, p3, p4); }
	static void SetCamInterpStyleDetailed(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("SET_CAM_INTERP_STYLE_DETAILED", p0, p1, p2, p3, p4); }
	static void SetCamMotionBlur(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_MOTION_BLUR", p0, p1); }
	static void SetCamName(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_NAME", p0, p1); }
	static void SetCamNearClip(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_NEAR_CLIP", p0, p1); }
	static void SetCamNearDof(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_NEAR_DOF", p0, p1); }
	static void SetCamPointOffset(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CAM_POINT_OFFSET", p0, p1, p2, p3); }
	static void SetCamPointOffsetIsRelative(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_POINT_OFFSET_IS_RELATIVE", p0, p1); }
	static void SetCamPos(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CAM_POS", p0, p1, p2, p3); }
	static void SetCamPropagate(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_PROPAGATE", p0, p1); }
	static void SetCamRot(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_CAM_ROT", p0, p1, p2, p3); }
	static void SetCamShake(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CAM_SHAKE", p0, p1, p2); }
	static void SetCamSplineDuration(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_SPLINE_DURATION", p0, p1); }
	static void SetCamSplineProgress(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_SPLINE_PROGRESS", p0, p1); }
	static void SetCamSplineSpeedConstant(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_SPLINE_SPEED_CONSTANT", p0, p1); }
	static void SetCamSplineSpeedGraph(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_SPLINE_SPEED_GRAPH", p0, p1); }
	static void SetCamTargetPed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAM_TARGET_PED", p0, p1); }
	static void SetCameraControlsDisabledWithPlayerControls(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS", p0); }
	static void SetCanBurstCarTyres(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAN_BURST_CAR_TYRES", p0, p1); }
	static void SetCanResprayCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAN_RESPRAY_CAR", p0, p1); }
	static void SetCanTargetCharWithoutLos(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CAN_TARGET_CHAR_WITHOUT_LOS", p0, p1); }
	static void SetCarGeneratorsActiveInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("SET_CAR_GENERATORS_ACTIVE_IN_AREA", p0, p1, p2, p3, p4, p5, p6); }
	static void SetCarOnlyDamagedByRelationshipGroup(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP", p0, p1, p2); }
	static void SetCarProofs(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SET_CAR_PROOFS", p0, p1, p2, p3, p4, p5); }
	static void SetCharDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DECISION_MAKER", p0, p1); }
	static void SetCharDecisionMakerToDefault(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_DECISION_MAKER_TO_DEFAULT", p0); }
	static void SetCharInCutscene(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_IN_CUTSCENE", p0, p1); }
	static void SetCharNameDebug(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_NAME_DEBUG", p0, p1); }
	static void SetCharNotDamagedByRelationshipGroup(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP", p0, p1, p2); }
	static void SetCharOnlyDamagedByRelationshipGroup(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP", p0, p1, p2); }
	static void SetCharProofs(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_PROOFS", p0, p1, p2, p3, p4, p5); }
	static void SetCharRelationship(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_RELATIONSHIP", p0, p1, p2); }
	static void SetCharRelationshipGroup(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_CHAR_RELATIONSHIP_GROUP", p0, p1); }
	static void SetCinematicButtonEnabled(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_CINEMATIC_BUTTON_ENABLED", p0); }
	static void SetCombatDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_COMBAT_DECISION_MAKER", p0, p1); }
	static void SetCutsceneExtraRoomPos(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_CUTSCENE_EXTRA_ROOM_POS", p0, p1, p2); }
	static void SetDecisionMakerAttributeCanChangeTarget(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_CAN_CHANGE_TARGET", p0, p1); }
	static void SetDecisionMakerAttributeCaution(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_CAUTION", p0, p1); }
	static void SetDecisionMakerAttributeFireRate(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_FIRE_RATE", p0, p1); }
	static void SetDecisionMakerAttributeMovementStyle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_MOVEMENT_STYLE", p0, p1); }
	static void SetDecisionMakerAttributeNavigationStyle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_NAVIGATION_STYLE", p0, p1); }
	static void SetDecisionMakerAttributeRetreatingBehaviour(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_RETREATING_BEHAVIOUR", p0, p1); }
	static void SetDecisionMakerAttributeSightRange(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE", p0, p1); }
	static void SetDecisionMakerAttributeStandingStyle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_STANDING_STYLE", p0, p1); }
	static void SetDecisionMakerAttributeTargetInjuredReaction(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_TARGET_INJURED_REACTION", p0, p1); }
	static void SetDecisionMakerAttributeTargetLossResponse(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_TARGET_LOSS_RESPONSE", p0, p1); }
	static void SetDecisionMakerAttributeTeamwork(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_TEAMWORK", p0, p1); }
	static void SetDecisionMakerAttributeWeaponAccuracy(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_DECISION_MAKER_ATTRIBUTE_WEAPON_ACCURACY", p0, p1); }
	static void SetFollowPedPitchLimitDown(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_FOLLOW_PED_PITCH_LIMIT_DOWN", p0); }
	static void SetFollowPedPitchLimitUp(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_FOLLOW_PED_PITCH_LIMIT_UP", p0); }
	static void SetFollowVehicleCamOffset(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_FOLLOW_VEHICLE_CAM_OFFSET", p0, p1, p2, p3); }
	static void SetFollowVehicleCamSubmode(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_FOLLOW_VEHICLE_CAM_SUBMODE", p0); }
	static void SetFreeResprays(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_FREE_RESPRAYS", p0); }
	static void SetFreebiesInVehicle(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_FREEBIES_IN_VEHICLE", p0, p1); }
	static void SetGameCamHeading(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_GAME_CAM_HEADING", p0); }
	static void SetGameCamPitch(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_GAME_CAM_PITCH", p0); }
	static void SetGarageLeaveCameraAlone(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GARAGE_LEAVE_CAMERA_ALONE", p0, p1); }
	static void SetGlobalInstancePriority(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_GLOBAL_INSTANCE_PRIORITY", p0); }
	static void SetGlobalRenderFlags(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_GLOBAL_RENDER_FLAGS", p0, p1, p2, p3); }
	static void SetGroupCharDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_GROUP_CHAR_DECISION_MAKER", p0, p1); }
	static void SetHealthPickupNetworkRegenTime(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_HEALTH_PICKUP_NETWORK_REGEN_TIME", p0); }
	static void SetHelpMessageBoxSize(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_HELP_MESSAGE_BOX_SIZE", p0); }
	static void SetHintFov(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_HINT_FOV", p0); }
	static void SetHintTimes(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_HINT_TIMES", p0, p1, p2); }
	static void SetHintTimesDefault() { NativeInvoke::Invoke<unsigned int>("SET_HINT_TIMES_DEFAULT"); }
	static void SetInMPTutorial(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_IN_MP_TUTORIAL", p0); }
	static void SetInSpectatorMode(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_IN_SPECTATOR_MODE", p0); }
	static void SetInformRespectedFriends(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_INFORM_RESPECTED_FRIENDS", p0, p1, p2); }
	static void SetInterpFromScriptToGame(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_INTERP_FROM_SCRIPT_TO_GAME", p0, p1); }
	static void SetInterpInOutVehicleEnabledThisFrame(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_INTERP_IN_OUT_VEHICLE_ENABLED_THIS_FRAME", p0); }
	static void SetLoadCollisionForCarFlag(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_LOAD_COLLISION_FOR_CAR_FLAG", p0, p1); }
	static void SetLoadCollisionForCharFlag(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_LOAD_COLLISION_FOR_CHAR_FLAG", p0, p1); }
	static void SetLobbyMuteOverride(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_LOBBY_MUTE_OVERRIDE", p0); }
	static void SetLoudVehicleRadio(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_LOUD_VEHICLE_RADIO", p0, p1); }
	static void SetMask(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_MASK", p0, p1, p2, p3); }
	static void SetMessagesWaiting(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MESSAGES_WAITING", p0); }
	static void SetMsgForLoadingScreen(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MSG_FOR_LOADING_SCREEN", p0); }
	static void SetMultiplayerHUDCash(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MULTIPLAYER_HUD_CASH", p0); }
	static void SetMultiplayerHUDTime(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_MULTIPLAYER_HUD_TIME", p0); }
	static void SetNetworkIdCanMigrate(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NETWORK_ID_CAN_MIGRATE", p0, p1); }
	static void SetNetworkIdExistsOnAllMachines(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES", p0, p1); }
	static void SetNetworkIdStopCloning(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NETWORK_ID_STOP_CLONING", p0, p1); }
	static void SetNetworkPlayerAsVip(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NETWORK_PLAYER_AS_VIP", p0, p1); }
	static void SetNetworkVehicleRespotTimer(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NETWORK_VEHICLE_RESPOT_TIMER", p0, p1); }
	static void SetNmAnimPose(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_NM_ANIM_POSE", p0, p1, p2, p3); }
	static void SetNmMessageBool(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NM_MESSAGE_BOOL", p0, p1); }
	static void SetNmMessageFloat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NM_MESSAGE_FLOAT", p0, p1); }
	static void SetNmMessageInstanceIndex(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_NM_MESSAGE_INSTANCE_INDEX", p0, p1, p2, p3); }
	static void SetNmMessageInt(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NM_MESSAGE_INT", p0, p1); }
	static void SetNmMessageString(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_NM_MESSAGE_STRING", p0, p1); }
	static void SetNmMessageVec3(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_NM_MESSAGE_VEC3", p0, p1, p2, p3); }
	static void SetObjectProofs(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_PROOFS", p0, p1, p2, p3, p4, p5); }
	static void SetObjectRecordsCollisions(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_OBJECT_RECORDS_COLLISIONS", p0, p1); }
	static void SetOverrideNoSprintingOnPhoneInMultiplayer(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_OVERRIDE_NO_SPRINTING_ON_PHONE_IN_MULTIPLAYER", p0); }
	static void SetPedWithBrainCanBeConvertedToDummyPed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PED_WITH_BRAIN_CAN_BE_CONVERTED_TO_DUMMY_PED", p0, p1); }
	static void SetPlaybackSpeed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PLAYBACK_SPEED", p0, p1); }
	static void SetPlayerControlForNetwork(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_PLAYER_CONTROL_FOR_NETWORK", p0, p1, p2); }
	static void SetPlayerControlOnInMissionCleanup(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PLAYER_CONTROL_ON_IN_MISSION_CLEANUP", p0); }
	static void SetPlayerIconColour(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PLAYER_ICON_COLOUR", p0); }
	static void SetPlayerPlayerTargetting(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PLAYER_PLAYER_TARGETTING", p0); }
	static void SetPlayerTeam(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_PLAYER_TEAM", p0, p1); }
	static void SetPlayersDropMoneyInNetworkGame(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PLAYERS_DROP_MONEY_IN_NETWORK_GAME", p0); }
	static void SetPlayerSettingsModelVariationsChoice(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PLAYERSETTINGS_MODEL_VARIATIONS_CHOICE", p0); }
	static void SetPtfxCamInsideVehicle(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_PTFX_CAM_INSIDE_VEHICLE", p0); }
	static void SetRelationship(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_RELATIONSHIP", p0, p1, p2); }
	static void SetRichPresenceTemplateLobby(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATELOBBY", p0); }
	static void SetRichPresenceTemplateMP1(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATEMP1", p0, p1, p2, p3); }
	static void SetRichPresenceTemplateMP2(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATEMP2", p0); }
	static void SetRichPresenceTemplateMP3(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATEMP3", p0, p1); }
	static void SetRichPresenceTemplateMP4(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATEMP4", p0, p1); }
	static void SetRichPresenceTemplateMP5(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATEMP5", p0, p1, p2); }
	static void SetRichPresenceTemplateMP6(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATEMP6", p0, p1, p2); }
	static void SetRichPresenceTemplateParty() { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATEPARTY"); }
	static void SetRichPresenceTemplateSP1(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATESP1", p0, p1, p2); }
	static void SetRichPresenceTemplateSP2(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_RICH_PRESENCE_TEMPLATESP2", p0); }
	static void SetRomansMood(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_ROMANS_MOOD", p0); }
	static void SetRoomForViewportByKey(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ROOM_FOR_VIEWPORT_BY_KEY", p0, p1); }
	static void SetRoomForViewportByName(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ROOM_FOR_VIEWPORT_BY_NAME", p0, p1); }
	static void SetRoute(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_ROUTE", p0, p1); }
	static void SetScenarioPedDensityMultiplier(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_SCENARIO_PED_DENSITY_MULTIPLIER", p0, p1); }
	static void SetScriptedAnimSeatOffset(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_SCRIPTED_ANIM_SEAT_OFFSET", p0, p1); }
	static void SetScriptedConversionCentre(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_SCRIPTED_CONVERSION_CENTRE", p0, p1, p2); }
	static void SetSenseRange(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_SENSE_RANGE", p0, p1); }
	static void SetSequenceToRepeat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_SEQUENCE_TO_REPEAT", p0, p1); }
	static void SetSpecificPassengerIndexToUseInGroups(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_SPECIFIC_PASSENGER_INDEX_TO_USE_IN_GROUPS", p0, p1); }
	static void SetSpritesDrawBeforeFade(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_SPRITES_DRAW_BEFORE_FADE", p0); }
	static void SetStatFrontEndVisibility(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_STAT_FRONTEND_VISIBILITY", p0, p1); }
	static void SetThisMachineRunningServerScript(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_THIS_MACHINE_RUNNING_SERVER_SCRIPT", p0); }
	static void SetTimecycleModifier(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_TIMECYCLE_MODIFIER", p0); }
	static void SetUsePoolGamePhysicsSettings(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SET_USE_POOL_GAME_PHYSICS_SETTINGS", p0); }
	static void SetUsesCollisionOfClosestObjectOfType(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SET_USES_COLLISION_OF_CLOSEST_OBJECT_OF_TYPE", p0, p1, p2, p3, p4, p5); }
	static void SetVariableOnSound(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_VARIABLE_ON_SOUND", p0, p1, p2); }
	static void SetViewportPriority(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_VIEWPORT_PRIORITY", p0, p1); }
	static void SetVisibilityOfClosestObjectOfType(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE", p0, p1, p2, p3, p4, p5); }
	static void SetVoiceIdFromHeadComponent(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_VOICE_ID_FROM_HEAD_COMPONENT", p0, p1, p2); }
	static void SetWeaponPickupNetworkRegenTime(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_WEAPON_PICKUP_NETWORK_REGEN_TIME", p0, p1); }
	static void SetWebPageLinkActive(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("SET_WEB_PAGE_LINK_ACTIVE", p0, p1, p2); }
	static void SetWebPageScroll(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SET_WEB_PAGE_SCROLL", p0, p1); }
	static void ShowSigninUi() { NativeInvoke::Invoke<unsigned int>("SHOW_SIGNIN_UI"); }
	static void ShutdownAndLaunchNetworkGame(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SHUTDOWN_AND_LAUNCH_NETWORK_GAME", p0); }
	static void ShutdownAndLaunchSinglePlayerGame() { NativeInvoke::Invoke<unsigned int>("SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME"); }
	static void SkipTimeInPlaybackRecordedCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SKIP_TIME_IN_PLAYBACK_RECORDED_CAR", p0, p1); }
	static void SkipToEndAndStopPlaybackRecordedCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_CAR", p0); }
	static void SkipToNextScriptedConversationLine() { NativeInvoke::Invoke<unsigned int>("SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE"); }
	static void StartCredits() { NativeInvoke::Invoke<unsigned int>("START_CREDITS"); }
	static void StartCustomMobilePhoneRinging(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("START_CUSTOM_MOBILE_PHONE_RINGING", p0); }
	static void StartCutscene() { NativeInvoke::Invoke<unsigned int>("START_CUTSCENE"); }
	static void StartCutsceneNow(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("START_CUTSCENE_NOW", p0); }
	static void StartEndCreditsMusic() { NativeInvoke::Invoke<unsigned int>("START_END_CREDITS_MUSIC"); }
	static void StartGpsRaceTrack(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("START_GPS_RACE_TRACK", p0); }
	static void StartLoadScene(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("START_LOAD_SCENE", p0, p1, p2); }
	static void StartMobilePhoneCall(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("START_MOBILE_PHONE_CALL", p0, p1, p2, p3, p4, p5); }
	static void StartMobilePhoneCalling() { NativeInvoke::Invoke<unsigned int>("START_MOBILE_PHONE_CALLING"); }
	static void StartNewWidgetCombo() { NativeInvoke::Invoke<unsigned int>("START_NEW_WIDGET_COMBO"); }
	static void StartPlaybackRecordedCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("START_PLAYBACK_RECORDED_CAR", p0, p1); }
	static void StartPlaybackRecordedCarUsingAi(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("START_PLAYBACK_RECORDED_CAR_USING_AI", p0, p1); }
	static unsigned int StartPtfx(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("START_PTFX", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int StartPtfxOnObj(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("START_PTFX_ON_OBJ", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static unsigned int StartPtfxOnPedBone(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { return NativeInvoke::Invoke<unsigned int>("START_PTFX_ON_PED_BONE", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static unsigned int StartPtfxOnVeh(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("START_PTFX_ON_VEH", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void StartScriptConversation(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("START_SCRIPT_CONVERSATION", p0, p1); }
	static void StopCredits() { NativeInvoke::Invoke<unsigned int>("STOP_CREDITS"); }
	static void StopEndCreditsMusic() { NativeInvoke::Invoke<unsigned int>("STOP_END_CREDITS_MUSIC"); }
	static void StopMobilePhoneRinging() { NativeInvoke::Invoke<unsigned int>("STOP_MOBILE_PHONE_RINGING"); }
	static void StopPlaybackRecordedCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("STOP_PLAYBACK_RECORDED_CAR", p0); }
	static void StopPreviewRingtone() { NativeInvoke::Invoke<unsigned int>("STOP_PREVIEW_RINGTONE"); }
	static void StopPtfx(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("STOP_PTFX", p0); }
	static void StopRecordingCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("STOP_RECORDING_CAR", p0); }
	static void StopStream() { NativeInvoke::Invoke<unsigned int>("STOP_STREAM"); }
	static void StoreCarCharIsInNoSave(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("STORE_CAR_CHAR_IS_IN_NO_SAVE", p0, p1); }
	static unsigned int StoreDamageTrackerForNetworkPlayer(unsigned int p0, unsigned int p1, unsigned int p2) { return NativeInvoke::Invoke<unsigned int>("STORE_DAMAGE_TRACKER_FOR_NETWORK_PLAYER", p0, p1, p2); }
	static void StoreScore(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("STORE_SCORE", p0, p1); }
	static void StoreScriptValuesForNetworkGame(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("STORE_SCRIPT_VALUES_FOR_NETWORK_GAME", p0); }
	static void StoreWantedLevel(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("STORE_WANTED_LEVEL", p0, p1); }
	static void StreamCutscene() { NativeInvoke::Invoke<unsigned int>("STREAM_CUTSCENE"); }
	static unsigned int StringToInt(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("STRING_TO_INT", p0, p1); }
	static void SwitchCarGenerator(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SWITCH_CAR_GENERATOR", p0, p1); }
	static void SwitchOffWaypoint() { NativeInvoke::Invoke<unsigned int>("SWITCH_OFF_WAYPOINT"); }
	static void SwitchPedPathsOff(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SWITCH_PED_PATHS_OFF", p0, p1, p2, p3, p4, p5); }
	static void SwitchPedPathsOn(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SWITCH_PED_PATHS_ON", p0, p1, p2, p3, p4, p5); }
	static void SwitchPedRoadsBackToOriginal(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("SWITCH_PED_ROADS_BACK_TO_ORIGINAL", p0, p1, p2, p3, p4, p5); }
	static void SwitchPedToAnimated(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("SWITCH_PED_TO_ANIMATED", p0, p1); }
	static void SwitchStreaming(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("SWITCH_STREAMING", p0); }
	static void TakeCarOutOfParkedCarsBudget(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TAKE_CAR_OUT_OF_PARKED_CARS_BUDGET", p0, p1); }
	static void TaskAchieveHeading(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_ACHIEVE_HEADING", p0, p1); }
	static void TaskAimGunAtChar(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_AIM_GUN_AT_CHAR", p0, p1, p2); }
	static void TaskAimGunAtCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_AIM_GUN_AT_COORD", p0, p1, p2, p3, p4); }
	static void TaskCarDriveToCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_DRIVE_TO_COORD", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static void TaskCarDriveToCoordNotAgainstTraffic(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_DRIVE_TO_COORD_NOT_AGAINST_TRAFFIC", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static void TaskCarDriveWander(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_DRIVE_WANDER", p0, p1, p2, p3); }
	static void TaskCarMission(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_MISSION", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskCarMissionCoorsTarget(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_MISSION_COORS_TARGET", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void TaskCarMissionCoorsTargetNotAgainstTraffic(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void TaskCarMissionNotAgainstTraffic(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_MISSION_NOT_AGAINST_TRAFFIC", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskCarMissionPedTarget(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_MISSION_PED_TARGET", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskCarTempAction(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_CAR_TEMP_ACTION", p0, p1, p2, p3); }
	static void TaskCharSlideToCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_CHAR_SLIDE_TO_COORD", p0, p1, p2, p3, p4, p5); }
	static void TaskCharSlideToCoordAndPlayAnim(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12, unsigned int p13) { NativeInvoke::Invoke<unsigned int>("TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	static void TaskCharSlideToCoordHdgRate(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("TASK_CHAR_SLIDE_TO_COORD_HDG_RATE", p0, p1, p2, p3, p4, p5, p6); }
	static void TaskChatWithChar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_CHAT_WITH_CHAR", p0, p1, p2, p3); }
	static void TaskClearLookAt(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TASK_CLEAR_LOOK_AT", p0); }
	static void TaskClimb(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_CLIMB", p0, p1); }
	static void TaskClimbLadder(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_CLIMB_LADDER", p0, p1); }
	static void TaskCombat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_COMBAT", p0, p1); }
	static void TaskCombatHatedTargetsAroundChar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_COMBAT_HATED_TARGETS_AROUND_CHAR", p0, p1); }
	static void TaskCombatHatedTargetsAroundCharTimed(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_COMBAT_HATED_TARGETS_AROUND_CHAR_TIMED", p0, p1, p2); }
	static void TaskCombatHatedTargetsInArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_COMBAT_HATED_TARGETS_IN_AREA", p0, p1, p2, p3, p4); }
	static void TaskCombatRoll(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_COMBAT_ROLL", p0, p1); }
	static void TaskCombatTimed(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_COMBAT_TIMED", p0, p1, p2); }
	static void TaskCower(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TASK_COWER", p0); }
	static void TaskDead(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TASK_DEAD", p0); }
	static void TaskDie(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TASK_DIE", p0); }
	static void TaskDriveBy(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("TASK_DRIVE_BY", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void TaskDrivePointRoute(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_DRIVE_POINT_ROUTE", p0, p1, p2); }
	static void TaskDrivePointRouteAdvanced(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_DRIVE_POINT_ROUTE_ADVANCED", p0, p1, p2, p3, p4, p5); }
	static void TaskDuck(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_DUCK", p0, p1); }
	static void TaskEnterCarAsDriver(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_ENTER_CAR_AS_DRIVER", p0, p1, p2); }
	static void TaskEnterCarAsPassenger(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_ENTER_CAR_AS_PASSENGER", p0, p1, p2, p3); }
	static void TaskEveryoneLeaveCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TASK_EVERYONE_LEAVE_CAR", p0); }
	static void TaskExtendRoute(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_EXTEND_ROUTE", p0, p1, p2); }
	static void TaskFleeCharAnyMeans(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_FLEE_CHAR_ANY_MEANS", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskFlushRoute() { NativeInvoke::Invoke<unsigned int>("TASK_FLUSH_ROUTE"); }
	static void TaskFollowNavMeshAndSlideToCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_FOLLOW_NAV_MESH_AND_SLIDE_TO_COORD", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskFollowNavMeshToCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("TASK_FOLLOW_NAV_MESH_TO_COORD", p0, p1, p2, p3, p4, p5, p6); }
	static void TaskFollowNavMeshToCoordNoStop(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP", p0, p1, p2, p3, p4, p5, p6); }
	static void TaskFollowPointRoute(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_FOLLOW_POINT_ROUTE", p0, p1, p2); }
	static void TaskGetOffBoat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_GET_OFF_BOAT", p0, p1); }
	static void TaskGoStraightToCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_GO_STRAIGHT_TO_COORD", p0, p1, p2, p3, p4, p5); }
	static void TaskGoStraightToCoordRelativeToCar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_CAR", p0, p1, p2, p3, p4, p5, p6); }
	static void TaskGoToChar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_GO_TO_CHAR", p0, p1, p2, p3); }
	static void TaskGoToCoordAnyMeans(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_GO_TO_COORD_ANY_MEANS", p0, p1, p2, p3, p4, p5); }
	static void TaskGoToCoordWhileAiming(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11) { NativeInvoke::Invoke<unsigned int>("TASK_GO_TO_COORD_WHILE_AIMING", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static void TaskGoToCoordWhileShooting(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_GO_TO_COORD_WHILE_SHOOTING", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskGoToObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_GO_TO_OBJECT", p0, p1, p2, p3); }
	static void TaskGotoCar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_GOTO_CAR", p0, p1, p2, p3); }
	static void TaskGotoCharOffset(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_GOTO_CHAR_OFFSET", p0, p1, p2, p3, p4); }
	static void TaskGuardAngledDefensiveArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12, unsigned int p13) { NativeInvoke::Invoke<unsigned int>("TASK_GUARD_ANGLED_DEFENSIVE_AREA", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	static void TaskGuardAssignedDefensiveArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("TASK_GUARD_ASSIGNED_DEFENSIVE_AREA", p0, p1, p2, p3, p4, p5, p6); }
	static void TaskGuardCurrentPosition(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_GUARD_CURRENT_POSITION", p0, p1, p2, p3); }
	static void TaskGuardSphereDefensiveArea(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10) { NativeInvoke::Invoke<unsigned int>("TASK_GUARD_SPHERE_DEFENSIVE_AREA", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	static void TaskHandsUp(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_HANDS_UP", p0, p1); }
	static void TaskHeliMission(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11, unsigned int p12) { NativeInvoke::Invoke<unsigned int>("TASK_HELI_MISSION", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	static void TaskLeaveAnyCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TASK_LEAVE_ANY_CAR", p0); }
	static void TaskLeaveCar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_LEAVE_CAR", p0, p1); }
	static void TaskLeaveCarAndFlee(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_LEAVE_CAR_AND_FLEE", p0, p1, p2, p3, p4); }
	static void TaskLeaveCarDontCloseDoor(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_LEAVE_CAR_DONT_CLOSE_DOOR", p0, p1); }
	static void TaskLeaveCarImmediately(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_LEAVE_CAR_IMMEDIATELY", p0, p1); }
	static void TaskLeaveCarInDirection(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_LEAVE_CAR_IN_DIRECTION", p0, p1, p2); }
	static void TaskLookAtChar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_LOOK_AT_CHAR", p0, p1, p2, p3); }
	static void TaskLookAtCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_LOOK_AT_COORD", p0, p1, p2, p3, p4, p5); }
	static void TaskLookAtObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_LOOK_AT_OBJECT", p0, p1, p2, p3); }
	static void TaskLookAtVehicle(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_LOOK_AT_VEHICLE", p0, p1, p2, p3); }
	static void TaskMobileConversation(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_MOBILE_CONVERSATION", p0, p1); }
	static void TaskOpenPassengerDoor(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_OPEN_PASSENGER_DOOR", p0, p1, p2, p3); }
	static void TaskPause(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_PAUSE", p0, p1); }
	static void TaskPerformSequence(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_PERFORM_SEQUENCE", p0, p1); }
	static void TaskPerformSequenceFromProgress(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_PERFORM_SEQUENCE_FROM_PROGRESS", p0, p1, p2, p3); }
	static void TaskPerformSequenceLocally(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_PERFORM_SEQUENCE_LOCALLY", p0, p1); }
	static void TaskPickupAndCarryObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_PICKUP_AND_CARRY_OBJECT", p0, p1, p2, p3, p4, p5); }
	static void TaskPlayAnim(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskPlayAnimFacial(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_FACIAL", p0, p1, p2, p3, p4, p5, p6); }
	static void TaskPlayAnimNonInterruptable(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_NON_INTERRUPTABLE", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskPlayAnimReadyToBeExecuted(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_READY_TO_BE_EXECUTED", p0, p1, p2, p3); }
	static void TaskPlayAnimSecondary(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_SECONDARY", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskPlayAnimSecondaryInCar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_SECONDARY_IN_CAR", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskPlayAnimSecondaryNoInterrupt(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_SECONDARY_NO_INTERRUPT", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskPlayAnimSecondaryUpperBody(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_SECONDARY_UPPER_BODY", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskPlayAnimUpperBody(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_UPPER_BODY", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TaskPlayAnimWithAdvancedFlags(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9, unsigned int p10, unsigned int p11) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_WITH_ADVANCED_FLAGS", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	static void TaskPlayAnimWithFlags(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_PLAY_ANIM_WITH_FLAGS", p0, p1, p2, p3, p4, p5); }
	static void TaskPutCharDirectlyIntoCover(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_PUT_CHAR_DIRECTLY_INTO_COVER", p0, p1, p2, p3, p4); }
	static void TaskSeekCoverFromPed(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_SEEK_COVER_FROM_PED", p0, p1, p2); }
	static void TaskSeekCoverFromPos(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_SEEK_COVER_FROM_POS", p0, p1, p2, p3, p4); }
	static void TaskSeekCoverToCoords(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_SEEK_COVER_TO_COORDS", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskSeekCoverToCoverPoint(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_SEEK_COVER_TO_COVER_POINT", p0, p1, p2, p3, p4, p5); }
	static void TaskSetCharDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_SET_CHAR_DECISION_MAKER", p0, p1); }
	static void TaskSetCombatDecisionMaker(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_SET_COMBAT_DECISION_MAKER", p0, p1); }
	static void TaskSetIgnoreWeaponRangeFlag(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_SET_IGNORE_WEAPON_RANGE_FLAG", p0, p1); }
	static void TaskShimmy(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_SHIMMY", p0, p1); }
	static unsigned int TaskShimmyInDirection(unsigned int p0, unsigned int p1) { return NativeInvoke::Invoke<unsigned int>("TASK_SHIMMY_IN_DIRECTION", p0, p1); }
	static unsigned int TaskShimmyLetGo(unsigned int p0) { return NativeInvoke::Invoke<unsigned int>("TASK_SHIMMY_LET_GO", p0); }
	static void TaskShootAtChar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_SHOOT_AT_CHAR", p0, p1, p2, p3); }
	static void TaskShuffleToNextCarSeat(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_SHUFFLE_TO_NEXT_CAR_SEAT", p0, p1); }
	static void TaskSitDown(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_SIT_DOWN", p0, p1, p2, p3); }
	static void TaskSitDownInstantly(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_SIT_DOWN_INSTANTLY", p0, p1, p2, p3); }
	static void TaskSitDownOnNearestObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("TASK_SIT_DOWN_ON_NEAREST_OBJECT", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void TaskSitDownOnObject(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { NativeInvoke::Invoke<unsigned int>("TASK_SIT_DOWN_ON_OBJECT", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static void TaskSitDownOnSeat(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_SIT_DOWN_ON_SEAT", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskSmartFleeChar(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_SMART_FLEE_CHAR", p0, p1, p2, p3); }
	static void TaskSmartFleeCharPreferringPavements(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_SMART_FLEE_CHAR_PREFERRING_PAVEMENTS", p0, p1, p2, p3); }
	static void TaskSmartFleePoint(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_SMART_FLEE_POINT", p0, p1, p2, p3, p4, p5); }
	static void TaskStandGuard(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { NativeInvoke::Invoke<unsigned int>("TASK_STAND_GUARD", p0, p1, p2, p3, p4, p5, p6, p7); }
	static void TaskStandStill(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_STAND_STILL", p0, p1); }
	static void TaskStartScenarioAtPosition(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { NativeInvoke::Invoke<unsigned int>("TASK_START_SCENARIO_AT_POSITION", p0, p1, p2, p3, p4, p5); }
	static void TaskStartScenarioInPlace(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_START_SCENARIO_IN_PLACE", p0, p1, p2); }
	static void TaskSwapWeapon(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_SWAP_WEAPON", p0, p1); }
	static void TaskToggleDuck(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_TOGGLE_DUCK", p0, p1); }
	static void TaskTurnCharToFaceChar(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_TURN_CHAR_TO_FACE_CHAR", p0, p1); }
	static void TaskTurnCharToFaceCoord(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("TASK_TURN_CHAR_TO_FACE_COORD", p0, p1, p2, p3); }
	static void TaskUseMobilePhone(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_USE_MOBILE_PHONE", p0, p1); }
	static void TaskUseMobilePhoneTimed(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_USE_MOBILE_PHONE_TIMED", p0, p1); }
	static void TaskUseNearestScenarioToPos(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_USE_NEAREST_SCENARIO_TO_POS", p0, p1, p2, p3, p4); }
	static void TaskUseNearestScenarioToPosWarp(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4) { NativeInvoke::Invoke<unsigned int>("TASK_USE_NEAREST_SCENARIO_TO_POS_WARP", p0, p1, p2, p3, p4); }
	static void TaskWanderStandard(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TASK_WANDER_STANDARD", p0); }
	static void TaskWarpCharIntoCarAsDriver(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TASK_WARP_CHAR_INTO_CAR_AS_DRIVER", p0, p1); }
	static void TaskWarpCharIntoCarAsPassenger(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER", p0, p1, p2); }
	static void TellNetPlayerToStartPlaying(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("TELL_NET_PLAYER_TO_START_PLAYING", p0, p1); }
	static void TerminateAllScriptsWithThisName(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME", p0); }
	static void ThisScriptIsSafeForNetworkGame() { NativeInvoke::Invoke<unsigned int>("THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME"); }
	static void ThisScriptShouldBeSaved() { NativeInvoke::Invoke<unsigned int>("THIS_SCRIPT_SHOULD_BE_SAVED"); }
	static void TrainLeaveStation(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TRAIN_LEAVE_STATION", p0); }
	static void TriggerMissionCompleteAudio(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TRIGGER_MISSION_COMPLETE_AUDIO", p0); }
	static void TriggerPoliceReport(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("TRIGGER_POLICE_REPORT", p0); }
	static unsigned int TriggerPtfx(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7) { return NativeInvoke::Invoke<unsigned int>("TRIGGER_PTFX", p0, p1, p2, p3, p4, p5, p6, p7); }
	static unsigned int TriggerPtfxOnObj(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("TRIGGER_PTFX_ON_OBJ", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static unsigned int TriggerPtfxOnPedBone(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8, unsigned int p9) { return NativeInvoke::Invoke<unsigned int>("TRIGGER_PTFX_ON_PED_BONE", p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	static unsigned int TriggerPtfxOnVeh(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, unsigned int p8) { return NativeInvoke::Invoke<unsigned int>("TRIGGER_PTFX_ON_VEH", p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	static void TurnOffRadioHUBInLobby() { NativeInvoke::Invoke<unsigned int>("TURN_OFF_RADIOHUD_IN_LOBBY"); }
	static void UnattachCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("UNATTACH_CAM", p0); }
	static void UnfreezeRadioStation(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("UNFREEZE_RADIO_STATION", p0); }
	static void UnlockMissionNewsStory(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("UNLOCK_MISSION_NEWS_STORY", p0); }
	static void UnlockRagdoll(unsigned int p0, unsigned int p1) { NativeInvoke::Invoke<unsigned int>("UNLOCK_RAGDOLL", p0, p1); }
	static void UnpausePlaybackRecordedCar(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("UNPAUSE_PLAYBACK_RECORDED_CAR", p0); }
	static void UnpointCam(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("UNPOINT_CAM", p0); }
	static void UpdateNetworkRelativeScore(unsigned int p0, unsigned int p1, unsigned int p2) { NativeInvoke::Invoke<unsigned int>("UPDATE_NETWORK_RELATIVE_SCORE", p0, p1, p2); }
	static void UpdateNetworkStatistics(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3) { NativeInvoke::Invoke<unsigned int>("UPDATE_NETWORK_STATISTICS", p0, p1, p2, p3); }
	static void UpdatePtfxOffsets(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5, unsigned int p6) { NativeInvoke::Invoke<unsigned int>("UPDATE_PTFX_OFFSETS", p0, p1, p2, p3, p4, p5, p6); }
	static void UseMask(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("USE_MASK", p0); }
	static void UsePlayerColourInsteadOfTeamColour(unsigned int p0) { NativeInvoke::Invoke<unsigned int>("USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR", p0); }
	static void UsePreviousFontSettings() { NativeInvoke::Invoke<unsigned int>("USE_PREVIOUS_FONT_SETTINGS"); }
}
