//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: COffsets.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef COffsets_h
#define COffsets_h

#include <assert.h>

enum eGameVersion
{
	GAME_VERSION_UNKNOWN, // ?.?.?.?
	GAME_VERSION_4,       // 1.0.4.0
	GAME_VERSION_5,       // 1.0.0.4
	GAME_VERSION_6,       // 1.0.6.0
	GAME_VERSION_7,       // 1.0.7.0
	GAME_VERSION_EFLC_1,  // EFLC 1.1.1.0
	GAME_VERSION_EFLC_2,  // EFLC 1.1.2.0
};

/* COffsets helper macros */

// Defines a offset
#define DEF_OFF(x) static unsigned int x;

// Initialize a offset
#define INIT_OFF(x) unsigned int COffsets::x = 0;

// Sets a offset
#define SET_OFF(x, y) x = (uiBase + y);

class COffsets {
private:
	static eGameVersion m_GameVersion;

public:
	static void         Initialize(unsigned int uiBase);
	static eGameVersion GetVersion() { return m_GameVersion; }

	DEF_OFF(VAR_IPedDataNY);
	DEF_OFF(FUNC_CPedMoveBlendOnFoot__Constructor);
	DEF_OFF(FUNC_NEW_CPedData);

	DEF_OFF(FUNC_CEpisodes__IsEpisodeAvaliable);
	DEF_OFF(FUNC_GetIndexFromPlayerInfo);
	DEF_OFF(FUNC_GetLocalPlayerPed);
	DEF_OFF(FUNC_CTask__Destructor);
	DEF_OFF(FUNC_RemoveInitialLoadingScreens);
	DEF_OFF(FUNC_GENERATETEXTURE);

	DEF_OFF(CALL_StartLoadingTune);
	DEF_OFF(VAR_NumberOfParkedCars);
	DEF_OFF(FUNC_CVehicle__RefreshLivery);

	// Players
	DEF_OFF(FUNC_CreatePlayerPed);
	DEF_OFF(FUNC_SetupPedIntelligence);
	DEF_OFF(FUNC_CPlayerPed__SetModelIndex);
	DEF_OFF(VAR_Ped_Factory);
	DEF_OFF(FUNC_Setup_Ped);
	DEF_OFF(FUNC_CPlayerPed__Constructor);
	DEF_OFF(FUNC_CPedIntelligence__Reset);
	DEF_OFF(FUNC_CPed__ScalarDeletingDestructor);

	// Game
	DEF_OFF(VAR_MenuActive_1);
	DEF_OFF(VAR_MenuActive_2);

	// Script
	DEF_OFF(FUNC_GetRunningScriptThread);
	DEF_OFF(CALL_CScriptVM__Process);
	DEF_OFF(VAR_ScrVM__ThreadPool);
	DEF_OFF(VAR_ScrVM__ActiveThread);
	DEF_OFF(FUNC_ScrVM__FindNativeAddress);
	DEF_OFF(VAR_ScrVM__GlobalVariablesPool);

	// Weather
	DEF_OFF(FUNC_SetWeather);
	DEF_OFF(VAR_CurrentWeather);

	// Clock
	DEF_OFF(FUNC_SetTimeOfDay);
	DEF_OFF(VAR_TimeOfDay);
	DEF_OFF(VAR_CClock__Hour);
	DEF_OFF(VAR_CClock__Minute);
	DEF_OFF(VAR_CClock__LockedHour);
	DEF_OFF(VAR_CClock__LockedMinute);
	DEF_OFF(VAR_CClock__DayOfWeek);

	// HUD
	DEF_OFF(VAR_HudEnabled);
	DEF_OFF(VAR_RadarVisible);
	DEF_OFF(VAR_PlayerNamesVisible);
	DEF_OFF(VAR_AreaNamesDisabled);

	// World
	DEF_OFF(FUNC_CWorld__AddEntity);
	DEF_OFF(FUNC_CWorld__RemoveEntity);
	DEF_OFF(FUNC_CEntity__IsTouchingEntity);
	DEF_OFF(FUNC_CMatrix__ConvertFromEulerAngles);
	DEF_OFF(FUNC_CMatrix__ConvertFromQuaternion);
	DEF_OFF(FUNC_CQuaternion__ConvertFromMatrix);

	// Vehicle
	DEF_OFF(FUNC_CVehicle__SetLoadCollision);
	DEF_OFF(FUNC_CVehicle__TurnEngineOn);
	DEF_OFF(FUNC_CVehicle__TurnEngineOff);
	DEF_OFF(FUNC_CVehicle__RefreshColours);

	// Misc
	DEF_OFF(VAR_CurrentWantedLevel);
	DEF_OFF(VAR_ScrollBarText);
	DEF_OFF(VAR_ScrollBarColor);
	DEF_OFF(VAR_CameraManager);
	DEF_OFF(VAR_LocalPlayerState);
	DEF_OFF(FUNC_GetLocalPlayerSpawnPosition);
	DEF_OFF(CALL_SpawnLocalPlayer);
	DEF_OFF(FUNC_SpawnPlayer);
	DEF_OFF(FUNC_GetTrafficLightState1);
	DEF_OFF(FUNC_GetTrafficLightState2);
	DEF_OFF(VAR_CurrentAreaName);
	DEF_OFF(VAR_CurrentStreetName);
	DEF_OFF(VAR_NumLoadingScreens);
	DEF_OFF(VAR_FirstLoadingScreenDuration);
	DEF_OFF(VAR_FirstLoadingScreenType);
	DEF_OFF(VAR_HWnd);
	DEF_OFF(VAR_Time);

	// Input
	DEF_OFF(VAR_Pads);
	DEF_OFF(FUNC_CPad__Constructor);
	DEF_OFF(FUNC_CPad__Initialize);
	DEF_OFF(FUNC_CPad__Destructor);

	// Key Sync
	DEF_OFF(VAR_CPlayerPed__VFTable);
	DEF_OFF(VAR_CAutomobile__VFTable);
	DEF_OFF(VAR_CBike__VFTable);
	DEF_OFF(VAR_CBoat__VFTable);
	DEF_OFF(VAR_CTrain__VFTable);
	DEF_OFF(VAR_CHeli__VFTable);
	DEF_OFF(VAR_CPlane__VFTable);
	DEF_OFF(FUNC_CPlayerPed__ProcessInput);
	DEF_OFF(FUNC_CAutomobile__ProcessInput);
	DEF_OFF(FUNC_CBike__ProcessInput);
	DEF_OFF(FUNC_CBoat__ProcessInput);
	DEF_OFF(FUNC_CTrain__ProcessInput);
	DEF_OFF(FUNC_CHeli__ProcessInput);
	DEF_OFF(FUNC_CPlane__ProcessInput);

	// Checkpoints
	DEF_OFF(VAR_RenderCheckpoints_FirstCP);
	DEF_OFF(VAR_RenderCheckpoints_LastCP);

	// Pools
	DEF_OFF(VAR_PedPool);
	DEF_OFF(VAR_VehiclePool);
	DEF_OFF(VAR_PtrNodeSinglePool);
	DEF_OFF(VAR_PtrNodeDoublePool);
	DEF_OFF(VAR_EntryInfoNodesPool);
	DEF_OFF(VAR_AnimatedBuildingPool);
	DEF_OFF(VAR_BuildingPool);
	DEF_OFF(VAR_ObjectPool);
	DEF_OFF(VAR_DummyObjectPool);
	DEF_OFF(VAR_InteriorInstPool);
	DEF_OFF(VAR_PortalInstPool);
	DEF_OFF(VAR_AnimBlenderPool);
	DEF_OFF(VAR_AtdNodeAnimChangePooledObjectPool);
	DEF_OFF(VAR_AtdNodeAnimPlayerPool);
	DEF_OFF(VAR_crFrameFilterBoneMaskPool);
	DEF_OFF(VAR_crFrameFilterBoneAnaloguePool);
	DEF_OFF(VAR_crExpressionProcessorPool);
	DEF_OFF(VAR_crmtObserverPool);
	DEF_OFF(VAR_TaskPool);
	DEF_OFF(VAR_DummyTaskPool);
	DEF_OFF(VAR_EventPool);
	DEF_OFF(VAR_PointRoutePool);
	DEF_OFF(VAR_PatrolRoutePool);
	DEF_OFF(VAR_NavMeshRoutePool);
	DEF_OFF(VAR_CamPool);
	DEF_OFF(VAR_ExplosionTypePool);
	DEF_OFF(VAR_PedMoveBlendPool);
	DEF_OFF(VAR_ParticleSystemPool);
	DEF_OFF(VAR_VehicleStructPool);
	DEF_OFF(VAR_PedBasePool);
	DEF_OFF(VAR_TaskInfoPool);
	DEF_OFF(VAR_PedAttractorPool);
	DEF_OFF(VAR_TargettingPool);
	DEF_OFF(FUNC_CPool__Allocate);
	DEF_OFF(FUNC_CPool__Release);
	DEF_OFF(FUNC_CPool__AtHandle);
	DEF_OFF(FUNC_CPool__HandleOf);
	DEF_OFF(FUNC_CPlayer__GetPlayerByNumber);
	DEF_OFF(VAR_PlayerInfoArray);
	DEF_OFF(VAR_LocalPlayerId);

	// Physical
	DEF_OFF(FUNC_CPhysical__SetMoveSpeed);
	DEF_OFF(FUNC_CPhysical__GetMoveSpeed);
	DEF_OFF(FUNC_CPhysical__SetTurnSpeed);
	DEF_OFF(FUNC_CPhysical__GetTurnSpeed);
	DEF_OFF(FUNC_CPhysical__SetLastDamageEntity);

	// Indicators
	DEF_OFF(PATCH_CVehicle__HazzardLightsOn);
	DEF_OFF(FUNC_CVehicle__DrawIndicator);
	DEF_OFF(RETURN_CVehicle__DrawIndicator);
	DEF_OFF(FUNC_CVehicleAudio__SetIndicators);

	// Streaming
	DEF_OFF(VAR_ResourceTypeWdrIndex);
	DEF_OFF(VAR_ResourceTypeWadIndex);
	DEF_OFF(VAR_ResourceTypeScoIndex);
	DEF_OFF(VAR_ResourceTypeWtdIndex);
	DEF_OFF(VAR_ResourceTypeCutIndex);
	DEF_OFF(VAR_ResourceTypeWddIndex);
	DEF_OFF(VAR_ResourceTypeWnvIndex);
	DEF_OFF(VAR_ResourceTypeRrrIndex);
	DEF_OFF(VAR_ResourceTypeWbdIndex);
	DEF_OFF(VAR_ResourceTypeIplIndex);
	DEF_OFF(VAR_ResourceTypeWbnIndex);
	DEF_OFF(VAR_ResourceTypeWbsIndex);
	DEF_OFF(FUNC_RequestResource);
	DEF_OFF(FUNC_LoadAllResources);
	DEF_OFF(FUNC_HasResourceLoaded);
	DEF_OFF(FUNC_ReleaseResource);
	DEF_OFF(FUNC_GetModelIndexFromHash);
	DEF_OFF(FUNC_CAnimStore__GetIndexFromHash);
	DEF_OFF(FUNC_LoadWorldAtPosition);
	DEF_OFF(FUNC_LoadWorldAtPositionStream);

	// Ped
	DEF_OFF(FUNC_CPed__SetDucking);
	DEF_OFF(FUNC_CPed__IsDucking);
	DEF_OFF(FUNC_CPed__DisableRagdoll);

	// Tasks
	DEF_OFF(FUNC_CPedTaskManager__SetTaskPriority);
	DEF_OFF(FUNC_CPedTaskManager__SetTaskSecondary);
	DEF_OFF(FUNC_CPedTaskManager__SetTaskMovement);
	DEF_OFF(VAR_CTask__VFTable);
	DEF_OFF(RETURN_CTask__Destructor);
	DEF_OFF(FUNC_CTaskComplexNewGetInVehicle__Constructor);
	DEF_OFF(FUNC_CTaskComplexNewExitVehicle__Constructor);
	DEF_OFF(FUNC_CTaskComplexDie__Constructor);
	DEF_OFF(FUNC_CTaskSimpleDead__Constructor);
	DEF_OFF(FUNC_CTaskSimpleCarSetPedInVehicle__Constructor);
	DEF_OFF(FUNC_CTaskSimpleCarSetPedOut__Constructor);
	DEF_OFF(FUNC_CTaskSimpleStopWalking__Constructor);
	DEF_OFF(FUNC_CTaskSimpleStartWalking__Constructor);
	DEF_OFF(FUNC_CTaskComplexJump__Constructor);
	DEF_OFF(FUNC_CTaskSimpleTriggerLookAt__Constructor);
	DEF_OFF(FUNC_CTaskComplexPlayerOnFoot__Constructor);
	DEF_OFF(FUNC_CTaskComplexGun__Constructor);
	DEF_OFF(FUNC_CTaskSimpleFireGun__Counstructor);
	DEF_OFF(FUNC_CTaskSimpleAimGun__Constructor);
	DEF_OFF(FUNC_CTaskSimpleReloadGun__Constructor);

	// Weapons
	DEF_OFF(FUNC_CPedWeapons__RemoveWeapon);
	DEF_OFF(FUNC_CPedWeapons__RemoveAllWeapons);

	// Game Funcs
	DEF_OFF(FUNC_IVGAME_FREEMEMORY);
	DEF_OFF(FUNC_IVGAME_ALLOCMEMORY);
	DEF_OFF(FUNC_IVGAME_GETSCREENCOORDSFROM3DCOORDS);
	DEF_OFF(FUNC_IVGAME_TOGGLELAZLOW_1);
	DEF_OFF(FUNC_IVGAME_TOGGLELAZLOW_2);
	DEF_OFF(FUNC_IVGAME_INITCUTSCENE);
	DEF_OFF(FUNC_IVGAME_STOPCUTSCENE);
	DEF_OFF(FUNC_IVGAME_LOADWORLDATPOSITION);
	
	// Misc
	DEF_OFF(CGame_Process__Sleep);
	DEF_OFF(CGame_Process_InitialiseRageGame);
	DEF_OFF(RAGE_LoadGame);
	DEF_OFF(RAGE_StartNewGame);

	DEF_OFF(FUNC_CVehicle__SetEngineOn);
	DEF_OFF(FUNC_CVehicle__SetEngineOff);
	DEF_OFF(FUNC_CVehicle__SetComponentDisabled);
	DEF_OFF(FUNC_CVehicle__SetTextureVariation);
	DEF_OFF(FUNC_CVehicle__BurstCarTyre);
	DEF_OFF(FUNC_CVehicle__RemoveVehicleWindow);

	DEF_OFF(FUNC_CWeapon__Initialize);

	DEF_OFF(FUNC_CPedWeapon__SetCurrentWeapon);
	DEF_OFF(FUNC_CPedWeapon__ShowWeapon);
	DEF_OFF(FUNC_CPedWeapon__HideWeapon);
	DEF_OFF(FUNC_CPedWeapon__SetAmmoByType);

	DEF_OFF(FUNC_CPlayerInfo__Constructor);
	DEF_OFF(FUNC_CPlayerInfo__Deconstructor);

	DEF_OFF(FUNC_IV_LOADWORLDATPOS_BYTE);

	// New
	DEF_OFF(RAGE_Camera__UnkownVoidPtr);
	DEF_OFF(IV_CamPool);
	DEF_OFF(FUNC_IV__CreateCamera);
	DEF_OFF(RAGE_AssetManager__OpenFile);
	DEF_OFF(RAGE_AssetManager__OpenFileJmpBack);
	DEF_OFF(RAGE_OpenFile);
	DEF_OFF(RAGE_OpenFileHook);

	DEF_OFF(IV_HookLoadingFiles);
	DEF_OFF(IV_HookLoadingScreen__DAT);
	DEF_OFF(IV_HookLoadingScreen__WTD);
	DEF_OFF(IV_HookLoadingTune);

	DEF_OFF(IV_Pool__SetPtrSinglePoolLimit);
	DEF_OFF(IV_Pool__SetPtrNodeDoublePoolLimit);
	DEF_OFF(IV_Pool__SetEntryInfoNodePoolLimit);
	DEF_OFF(IV_Pool__SetPedPoolLimit_1);
	DEF_OFF(IV_Pool__SetPedPoolLimit_2);
	DEF_OFF(IV_Pool__SetPedPoolLimit_3);
	DEF_OFF(IV_Pool__SetPedPoolLimit_4);

	DEF_OFF(IV_Pool__SetVehiclePoolLimit);
	DEF_OFF(IV_Pool__SetVehicleStructPoolLimit);

	DEF_OFF(IV_Hook__DisableParkedCars);
	DEF_OFF(IV_Hook__DisableEmergencyAndGarbageTrucks);
	DEF_OFF(IV_Hook__DisableVehicleEntries);
	DEF_OFF(IV_Hook__DisableVehicleExists);
	DEF_OFF(IV_Hook__DisableRandomPedsAndVehicles_1);
	DEF_OFF(IV_Hook__DisableRandomPedsAndVehicles_2);
	DEF_OFF(IV_Hook__DisableRandomPedsAndVehicles_3);
	DEF_OFF(IV_Hook__DisableScenarioPeds);
	DEF_OFF(IV_Hook__DisableFakeCars);

	DEF_OFF(IV_Hook__CIKManager_AimWeapon__JmpBack);
	DEF_OFF(IV_Hook__CIKManager_PointArms__JmpBack);
	DEF_OFF(IV_Hook__CIKManager_FireWeapon__JmpBack);
	DEF_OFF(IV_Hook__CIKManager_AimWeapon);
	DEF_OFF(IV_Hook__CIKManager_PointArms);
	DEF_OFF(IV_Hook__CIKManager_FireWeapon);

	DEF_OFF(IV_Hook__LoadHUD);
	DEF_OFF(IV_Hook__LoadInternalHud);
	DEF_OFF(IV_Hook__LoadHudHook);

	DEF_OFF(IV_Hook__LoadRadioLogo);
	DEF_OFF(IV_Hook__LoadInternalRadioLogo);
	DEF_OFF(IV_Hook__LoadRadioLogoHook);

	DEF_OFF(IV_Hook__LoadWorldAtPosition);

	DEF_OFF(IV_Hook__TextureSelect__JmpBack);

	DEF_OFF(IV_Hook__StartGameLoading_1);
	DEF_OFF(IV_Hook__StartGameLoading_2);
	DEF_OFF(IV_Hook__StartGameLoading_3);
	DEF_OFF(IV_Hook__StartGameLoading_4);
	DEF_OFF(IV_Hook__StartGameLoading_5);
	DEF_OFF(IV_Hook__StartGameLoading_6);
	DEF_OFF(IV_Hook__StartGameLoading_7);
	DEF_OFF(IV_Hook__StartGameLoading_8);

	DEF_OFF(IV_Hook__GameProcess_1);
	DEF_OFF(IV_Hook__GameProcess_2);
	DEF_OFF(IV_Hook__GameProcess_3);
	DEF_OFF(IV_Hook__GameProcess_4);
	DEF_OFF(IV_Hook__GameProcess_5);
	DEF_OFF(IV_Hook__GameProcess_6);
	DEF_OFF(IV_Hook__GameProcess_7);
	DEF_OFF(IV_Hook__GameProcess_8);

	DEF_OFF(IV_Hook__IncreasePoolSizes);

	DEF_OFF(IV_Hook__UnkownPatch1);
	DEF_OFF(IV_Hook__UnkownPatch2);

	DEF_OFF(IV_Hook__PatchRandomTasks);
	DEF_OFF(IV_Hook__PatchInternet_1);
	DEF_OFF(IV_Hook__PatchInternet_2);
	DEF_OFF(IV_Hook__PatchHelpMessageBox);
	DEF_OFF(IV_Hook__PatchStartNewGame);
	DEF_OFF(IV_Hook__PatchStartupDOTsco);
	DEF_OFF(IV_Hook__PatchVehicleDriverProcess);
	DEF_OFF(IV_Hook__PatchErrorReporting);
	DEF_OFF(IV_Hook__PatchMissingTests1);
	DEF_OFF(IV_Hook__PatchMissingTests2);

	DEF_OFF(IV_Hook__PatchUnkownAddress1);
	DEF_OFF(IV_Hook__PatchUnkownAddress2);

	DEF_OFF(IV_Hook__PatchSecuromCheck);
	DEF_OFF(IV_Hook__PatchPreventVehicleCrash);
	DEF_OFF(IV_Hook__PatchErrorMessageBoxes);

	DEF_OFF(IV_Hook__DisableStartupResourceCheck_1);
	DEF_OFF(IV_Hook__DisableStartupResourceCheck_2);
	DEF_OFF(IV_Hook__DisableStartupResourceCheck_3);
	DEF_OFF(IV_Hook__DisableStartupResourceCheck_4);

	DEF_OFF(IV_Hook__DisableAutomaticRadarTurnon_1);
	DEF_OFF(IV_Hook__DisableAutomaticRadarTurnon_2);

	DEF_OFF(IV_Hook__PatchWeaponGiveWhenEnterVehicle);
	DEF_OFF(IV_Hook__PatchEnableAndFixVehicleModels);
	DEF_OFF(IV_Hook__PatchUnkownByte1);

	DEF_OFF(IV_Hook__PatchDeathLoadingScreen);
	DEF_OFF(IV_Func__CreatePed);
	DEF_OFF(IV_Func__SetupPed);
	DEF_OFF(IV_Var__PedFactory);
	DEF_OFF(IV_Func__SetupPedIntelligence);
	DEF_OFF(IV_Func__ShutdownPedIntelligence);
	DEF_OFF(IV_Func__DeletePed);

	DEF_OFF(IV_Func__DeletePedTaskID);
	DEF_OFF(IV_Func__DeletePedTaskJump);
	DEF_OFF(IV_FUNC__TaskPedJump);
	DEF_OFF(IV_Func__MovePedToPositionInterpolated);
};

#endif