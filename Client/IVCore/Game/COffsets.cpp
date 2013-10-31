//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: COffsets.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>, xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#include "COffsets.h"
#include "CGame.h"
#include <CLogFile.h>

eGameVersion COffsets::m_GameVersion = GAME_VERSION_UNKNOWN;

// Players
INIT_OFF(FUNC_CreatePlayerPed);
INIT_OFF(FUNC_SetupPedIntelligence);
INIT_OFF(FUNC_CPlayerPed__SetModelIndex);
INIT_OFF(VAR_Ped_Factory);
INIT_OFF(FUNC_Setup_Ped);
INIT_OFF(FUNC_CPlayerPed__Constructor);
INIT_OFF(FUNC_CPedIntelligence__Reset);
INIT_OFF(FUNC_CPed__ScalarDeletingDestructor);

INIT_OFF(FUNC_CEpisodes__IsEpisodeAvaliable);
INIT_OFF(FUNC_GetIndexFromPlayerInfo);
INIT_OFF(FUNC_GetLocalPlayerPed);
INIT_OFF(FUNC_CTask__Destructor);
INIT_OFF(FUNC_RemoveInitialLoadingScreens);
INIT_OFF(FUNC_GENERATETEXTURE);

// Game
INIT_OFF(VAR_MenuActive_1);
INIT_OFF(VAR_MenuActive_2);

// Script
INIT_OFF(FUNC_GetRunningScriptThread);
INIT_OFF(CALL_CScriptVM__Process);
INIT_OFF(VAR_ScrVM__ThreadPool);
INIT_OFF(VAR_ScrVM__ActiveThread);
INIT_OFF(FUNC_ScrVM__FindNativeAddress);
INIT_OFF(VAR_ScrVM__GlobalVariablesPool);

// Weather
INIT_OFF(FUNC_SetWeather);
INIT_OFF(VAR_CurrentWeather);

// Clock
INIT_OFF(FUNC_SetTimeOfDay);
INIT_OFF(VAR_TimeOfDay);
INIT_OFF(VAR_CClock__Hour);
INIT_OFF(VAR_CClock__Minute);
INIT_OFF(VAR_CClock__LockedHour);
INIT_OFF(VAR_CClock__LockedMinute);
INIT_OFF(VAR_CClock__DayOfWeek);

// HUD
INIT_OFF(VAR_HudEnabled);
INIT_OFF(VAR_RadarVisible);
INIT_OFF(VAR_PlayerNamesVisible);
INIT_OFF(VAR_AreaNamesDisabled);

// World
INIT_OFF(FUNC_CWorld__AddEntity);
INIT_OFF(FUNC_CWorld__RemoveEntity);
INIT_OFF(FUNC_CEntity__IsTouchingEntity);
INIT_OFF(FUNC_CMatrix__ConvertFromEulerAngles);
INIT_OFF(FUNC_CMatrix__ConvertFromQuaternion);
INIT_OFF(FUNC_CQuaternion__ConvertFromMatrix);

// Vehicle
INIT_OFF(FUNC_CVehicle__SetLoadCollision);
INIT_OFF(FUNC_CVehicle__TurnEngineOn);
INIT_OFF(FUNC_CVehicle__TurnEngineOff);
INIT_OFF(FUNC_CVehicle__RefreshColours);

// Misc
INIT_OFF(VAR_CurrentWantedLevel);
INIT_OFF(VAR_ScrollBarText);
INIT_OFF(VAR_ScrollBarColor);
INIT_OFF(VAR_CameraManager);
INIT_OFF(VAR_LocalPlayerState);
INIT_OFF(FUNC_GetLocalPlayerSpawnPosition);
INIT_OFF(CALL_SpawnLocalPlayer);
INIT_OFF(FUNC_SpawnPlayer);
INIT_OFF(FUNC_GetTrafficLightState1);
INIT_OFF(FUNC_GetTrafficLightState2);
INIT_OFF(VAR_CurrentAreaName);
INIT_OFF(VAR_CurrentStreetName);
INIT_OFF(VAR_NumLoadingScreens);
INIT_OFF(VAR_FirstLoadingScreenDuration);
INIT_OFF(VAR_FirstLoadingScreenType);
INIT_OFF(VAR_HWnd);
INIT_OFF(VAR_Time);

// Input
INIT_OFF(VAR_Pads);
INIT_OFF(FUNC_CPad__Constructor);
INIT_OFF(FUNC_CPad__Initialize);
INIT_OFF(FUNC_CPad__Destructor);

// Key Sync
INIT_OFF(VAR_CPlayerPed__VFTable);
INIT_OFF(VAR_CAutomobile__VFTable);
INIT_OFF(VAR_CBike__VFTable);
INIT_OFF(VAR_CBoat__VFTable);
INIT_OFF(VAR_CTrain__VFTable);
INIT_OFF(VAR_CHeli__VFTable);
INIT_OFF(VAR_CPlane__VFTable);
INIT_OFF(FUNC_CPlayerPed__ProcessInput);
INIT_OFF(FUNC_CAutomobile__ProcessInput);
INIT_OFF(FUNC_CBike__ProcessInput);
INIT_OFF(FUNC_CBoat__ProcessInput);
INIT_OFF(FUNC_CTrain__ProcessInput);
INIT_OFF(FUNC_CHeli__ProcessInput);
INIT_OFF(FUNC_CPlane__ProcessInput);

// Checkpoints
INIT_OFF(VAR_RenderCheckpoints_FirstCP);
INIT_OFF(VAR_RenderCheckpoints_LastCP);

// Pools
INIT_OFF(VAR_PedPool);
INIT_OFF(VAR_VehiclePool);
INIT_OFF(VAR_PtrNodeSinglePool);
INIT_OFF(VAR_PtrNodeDoublePool);
INIT_OFF(VAR_EntryInfoNodesPool);
INIT_OFF(VAR_AnimatedBuildingPool);
INIT_OFF(VAR_BuildingPool);
INIT_OFF(VAR_ObjectPool);
INIT_OFF(VAR_DummyObjectPool);
INIT_OFF(VAR_InteriorInstPool);
INIT_OFF(VAR_PortalInstPool);
INIT_OFF(VAR_AnimBlenderPool);
INIT_OFF(VAR_AtdNodeAnimChangePooledObjectPool);
INIT_OFF(VAR_AtdNodeAnimPlayerPool);
INIT_OFF(VAR_crFrameFilterBoneMaskPool);
INIT_OFF(VAR_crFrameFilterBoneAnaloguePool);
INIT_OFF(VAR_crExpressionProcessorPool);
INIT_OFF(VAR_crmtObserverPool);
INIT_OFF(VAR_TaskPool);
INIT_OFF(VAR_DummyTaskPool);
INIT_OFF(VAR_EventPool);
INIT_OFF(VAR_PointRoutePool);
INIT_OFF(VAR_PatrolRoutePool);
INIT_OFF(VAR_NavMeshRoutePool);
INIT_OFF(VAR_CamPool);
INIT_OFF(VAR_ExplosionTypePool);
INIT_OFF(VAR_PedMoveBlendPool);
INIT_OFF(VAR_ParticleSystemPool);
INIT_OFF(VAR_VehicleStructPool);
INIT_OFF(VAR_PedBasePool);
INIT_OFF(VAR_TaskInfoPool);
INIT_OFF(VAR_PedAttractorPool);
INIT_OFF(VAR_TargettingPool);
INIT_OFF(FUNC_CPool__Allocate);
INIT_OFF(FUNC_CPool__Release);
INIT_OFF(FUNC_CPool__AtHandle);
INIT_OFF(FUNC_CPool__HandleOf);
INIT_OFF(FUNC_CPlayer__GetPlayerByNumber);
INIT_OFF(VAR_PlayerInfoArray);
INIT_OFF(VAR_LocalPlayerId);

// Physical
INIT_OFF(FUNC_CPhysical__SetMoveSpeed);
INIT_OFF(FUNC_CPhysical__GetMoveSpeed);
INIT_OFF(FUNC_CPhysical__SetTurnSpeed);
INIT_OFF(FUNC_CPhysical__GetTurnSpeed);
INIT_OFF(FUNC_CPhysical__SetLastDamageEntity);

// Indicators
INIT_OFF(PATCH_CVehicle__HazzardLightsOn);
INIT_OFF(FUNC_CVehicle__DrawIndicator);
INIT_OFF(RETURN_CVehicle__DrawIndicator);
INIT_OFF(FUNC_CVehicleAudio__SetIndicators);

// Streaming
INIT_OFF(VAR_ResourceTypeWdrIndex);
INIT_OFF(VAR_ResourceTypeWadIndex);
INIT_OFF(VAR_ResourceTypeScoIndex);
INIT_OFF(VAR_ResourceTypeWtdIndex);
INIT_OFF(VAR_ResourceTypeCutIndex);
INIT_OFF(VAR_ResourceTypeWddIndex);
INIT_OFF(VAR_ResourceTypeWnvIndex);
INIT_OFF(VAR_ResourceTypeRrrIndex);
INIT_OFF(VAR_ResourceTypeWbdIndex);
INIT_OFF(VAR_ResourceTypeIplIndex);
INIT_OFF(VAR_ResourceTypeWbnIndex);
INIT_OFF(VAR_ResourceTypeWbsIndex);
INIT_OFF(FUNC_RequestResource);
INIT_OFF(FUNC_LoadAllResources);
INIT_OFF(FUNC_HasResourceLoaded);
INIT_OFF(FUNC_ReleaseResource);
INIT_OFF(FUNC_GetModelIndexFromHash);
INIT_OFF(FUNC_CAnimStore__GetIndexFromHash);
INIT_OFF(FUNC_LoadWorldAtPosition);
INIT_OFF(FUNC_LoadWorldAtPositionStream);

// Ped
INIT_OFF(FUNC_CPed__SetDucking);
INIT_OFF(FUNC_CPed__IsDucking);
INIT_OFF(FUNC_CPed__DisableRagdoll);

// Tasks
INIT_OFF(FUNC_CPedTaskManager__SetTaskPriority);
INIT_OFF(FUNC_CPedTaskManager__SetTaskSecondary);
INIT_OFF(FUNC_CPedTaskManager__SetTaskMovement);
INIT_OFF(VAR_CTask__VFTable);
INIT_OFF(RETURN_CTask__Destructor);
INIT_OFF(FUNC_CTaskComplexNewGetInVehicle__Constructor);
INIT_OFF(FUNC_CTaskComplexNewExitVehicle__Constructor);
INIT_OFF(FUNC_CTaskComplexDie__Constructor);
INIT_OFF(FUNC_CTaskSimpleDead__Constructor);
INIT_OFF(FUNC_CTaskSimpleCarSetPedInVehicle__Constructor);
INIT_OFF(FUNC_CTaskSimpleCarSetPedOut__Constructor);
INIT_OFF(FUNC_CTaskSimpleStartWalking__Constructor);
INIT_OFF(FUNC_CTaskSimpleStopWalking__Constructor);
INIT_OFF(FUNC_CTaskComplexJump__Constructor);
INIT_OFF(FUNC_CTaskSimpleTriggerLookAt__Constructor);
INIT_OFF(FUNC_CTaskComplexPlayerOnFoot__Constructor);
INIT_OFF(FUNC_CTaskComplexGun__Constructor);
INIT_OFF(FUNC_CTaskSimpleFireGun__Counstructor);
INIT_OFF(FUNC_CTaskSimpleAimGun__Constructor);
INIT_OFF(FUNC_CTaskSimpleReloadGun__Constructor);

// Weapons
INIT_OFF(FUNC_CPedWeapons__RemoveWeapon);
INIT_OFF(FUNC_CPedWeapons__RemoveAllWeapons);

INIT_OFF(VAR_IPedDataNY);
INIT_OFF(FUNC_CPedMoveBlendOnFoot__Constructor);
INIT_OFF(FUNC_NEW_CPedData);

INIT_OFF(CALL_StartLoadingTune);
INIT_OFF(VAR_NumberOfParkedCars);
INIT_OFF(FUNC_CVehicle__RefreshLivery);

INIT_OFF(FUNC_IVGAME_FREEMEMORY);
INIT_OFF(FUNC_IVGAME_ALLOCMEMORY);
INIT_OFF(FUNC_IVGAME_GETSCREENCOORDSFROM3DCOORDS);
INIT_OFF(FUNC_IVGAME_TOGGLELAZLOW_1);
INIT_OFF(FUNC_IVGAME_TOGGLELAZLOW_2);
INIT_OFF(FUNC_IVGAME_INITCUTSCENE);
INIT_OFF(FUNC_IVGAME_STOPCUTSCENE);
INIT_OFF(FUNC_IVGAME_LOADWORLDATPOSITION);

INIT_OFF(CGame_Process__Sleep);
INIT_OFF(CGame_Process_InitialiseRageGame);
INIT_OFF(RAGE_LoadGame);
INIT_OFF(RAGE_StartNewGame);

INIT_OFF(FUNC_CVehicle__SetEngineOn);
INIT_OFF(FUNC_CVehicle__SetEngineOff);
INIT_OFF(FUNC_CVehicle__SetComponentDisabled);
INIT_OFF(FUNC_CVehicle__SetTextureVariation);
INIT_OFF(FUNC_CVehicle__BurstCarTyre);
INIT_OFF(FUNC_CVehicle__RemoveVehicleWindow);

INIT_OFF(FUNC_CWeapon__Initialize);

INIT_OFF(FUNC_CPedWeapon__SetCurrentWeapon);
INIT_OFF(FUNC_CPedWeapon__ShowWeapon);
INIT_OFF(FUNC_CPedWeapon__HideWeapon);
INIT_OFF(FUNC_CPedWeapon__SetAmmoByType);

INIT_OFF(FUNC_CPlayerInfo__Constructor);
INIT_OFF(FUNC_CPlayerInfo__Deconstructor);

INIT_OFF(FUNC_IV_LOADWORLDATPOS_BYTE);

// New
INIT_OFF(RAGE_Camera__UnkownVoidPtr);
INIT_OFF(IV_CamPool);
INIT_OFF(FUNC_IV__CreateCamera);
INIT_OFF(RAGE_AssetManager__OpenFile);
INIT_OFF(RAGE_AssetManager__OpenFileJmpBack);
INIT_OFF(RAGE_OpenFile);
INIT_OFF(RAGE_OpenFileHook);

INIT_OFF(IV_HookLoadingFiles);
INIT_OFF(IV_HookLoadingScreen__DAT);
INIT_OFF(IV_HookLoadingScreen__WTD);
INIT_OFF(IV_HookLoadingTune);

INIT_OFF(IV_Pool__SetPtrSinglePoolLimit);
INIT_OFF(IV_Pool__SetPtrNodeDoublePoolLimit);
INIT_OFF(IV_Pool__SetEntryInfoNodePoolLimit);
INIT_OFF(IV_Pool__SetPedPoolLimit_1);
INIT_OFF(IV_Pool__SetPedPoolLimit_2);
INIT_OFF(IV_Pool__SetPedPoolLimit_3);
INIT_OFF(IV_Pool__SetPedPoolLimit_4);

INIT_OFF(IV_Pool__SetVehiclePoolLimit);
INIT_OFF(IV_Pool__SetVehicleStructPoolLimit);

INIT_OFF(IV_Hook__DisableParkedCars);
INIT_OFF(IV_Hook__DisableEmergencyAndGarbageTrucks);
INIT_OFF(IV_Hook__DisableVehicleEntries);
INIT_OFF(IV_Hook__DisableVehicleExists);
INIT_OFF(IV_Hook__DisableRandomPedsAndVehicles_1);
INIT_OFF(IV_Hook__DisableRandomPedsAndVehicles_2);
INIT_OFF(IV_Hook__DisableRandomPedsAndVehicles_3);
INIT_OFF(IV_Hook__DisableScenarioPeds);
INIT_OFF(IV_Hook__DisableFakeCars);

INIT_OFF(IV_Hook__CIKManager_AimWeapon__JmpBack);
INIT_OFF(IV_Hook__CIKManager_PointArms__JmpBack);
INIT_OFF(IV_Hook__CIKManager_FireWeapon__JmpBack);
INIT_OFF(IV_Hook__CIKManager_AimWeapon);
INIT_OFF(IV_Hook__CIKManager_PointArms);
INIT_OFF(IV_Hook__CIKManager_FireWeapon);

INIT_OFF(IV_Hook__LoadHUD);
INIT_OFF(IV_Hook__LoadInternalHud);
INIT_OFF(IV_Hook__LoadHudHook);

INIT_OFF(IV_Hook__LoadRadioLogo);
INIT_OFF(IV_Hook__LoadInternalRadioLogo);
INIT_OFF(IV_Hook__LoadRadioLogoHook);

INIT_OFF(IV_Hook__LoadWorldAtPosition);

INIT_OFF(IV_Hook__TextureSelect__JmpBack);

INIT_OFF(IV_Hook__StartGameLoading_1);
INIT_OFF(IV_Hook__StartGameLoading_2);
INIT_OFF(IV_Hook__StartGameLoading_3);
INIT_OFF(IV_Hook__StartGameLoading_4);
INIT_OFF(IV_Hook__StartGameLoading_5);
INIT_OFF(IV_Hook__StartGameLoading_6);
INIT_OFF(IV_Hook__StartGameLoading_7);
INIT_OFF(IV_Hook__StartGameLoading_8);

INIT_OFF(IV_Hook__GameProcess_1);
INIT_OFF(IV_Hook__GameProcess_2);
INIT_OFF(IV_Hook__GameProcess_3);
INIT_OFF(IV_Hook__GameProcess_4);
INIT_OFF(IV_Hook__GameProcess_5);
INIT_OFF(IV_Hook__GameProcess_6);
INIT_OFF(IV_Hook__GameProcess_7);
INIT_OFF(IV_Hook__GameProcess_8);

INIT_OFF(IV_Hook__IncreasePoolSizes);

INIT_OFF(IV_Hook__UnkownPatch1);
INIT_OFF(IV_Hook__UnkownPatch2);

INIT_OFF(IV_Hook__PatchRandomTasks);
INIT_OFF(IV_Hook__PatchInternet_1);
INIT_OFF(IV_Hook__PatchInternet_2);
INIT_OFF(IV_Hook__PatchHelpMessageBox);
INIT_OFF(IV_Hook__PatchStartNewGame);
INIT_OFF(IV_Hook__PatchStartupDOTsco);
INIT_OFF(IV_Hook__PatchVehicleDriverProcess);
INIT_OFF(IV_Hook__PatchErrorReporting);
INIT_OFF(IV_Hook__PatchMissingTests1);
INIT_OFF(IV_Hook__PatchMissingTests2);

INIT_OFF(IV_Hook__PatchUnkownAddress1);
INIT_OFF(IV_Hook__PatchUnkownAddress2);

INIT_OFF(IV_Hook__PatchSecuromCheck);
INIT_OFF(IV_Hook__PatchPreventVehicleCrash);
INIT_OFF(IV_Hook__PatchErrorMessageBoxes);

INIT_OFF(IV_Hook__DisableStartupResourceCheck_1);
INIT_OFF(IV_Hook__DisableStartupResourceCheck_2);
INIT_OFF(IV_Hook__DisableStartupResourceCheck_3);
INIT_OFF(IV_Hook__DisableStartupResourceCheck_4);

INIT_OFF(IV_Hook__DisableAutomaticRadarTurnon_1);
INIT_OFF(IV_Hook__DisableAutomaticRadarTurnon_2);

INIT_OFF(IV_Hook__PatchWeaponGiveWhenEnterVehicle);
INIT_OFF(IV_Hook__PatchEnableAndFixVehicleModels);
INIT_OFF(IV_Hook__PatchUnkownByte1);

INIT_OFF(IV_Hook__PatchDeathLoadingScreen);
INIT_OFF(IV_Func__CreatePed);
INIT_OFF(IV_Func__SetupPed);
INIT_OFF(IV_Var__PedFactory);
INIT_OFF(IV_Func__SetupPedIntelligence);
INIT_OFF(IV_Func__ShutdownPedIntelligence);
INIT_OFF(IV_Func__DeletePed);

INIT_OFF(IV_Func__DeletePedTaskID);
INIT_OFF(IV_Func__DeletePedTaskJump);
INIT_OFF(IV_FUNC__TaskPedJump);
INIT_OFF(IV_Func__MovePedToPositionInterpolated);


enum ePATCH_SIG
{
	IV_101 = 0x831F7518,
	IV_102 = 0xC483FFE4,
	IV_103 = 0x280F0000,
	IV_104 = 0x110FF300,
	IV_105 = 0xF3385058,
	IV_106 = 0x00A42494,
	IV_106J = 0xDA280F30,
	IV_107 = 0x1006E857,
	EFLC_111 = 0x0F14247C,
	EFLC_112 = 0x0D5C0FF3,
};

void COffsets::Initialize(unsigned int uiBase)
{
	CLogFile::Printf( "Starting patching addresses to offsets" );

	m_GameVersion = GAME_VERSION_UNKNOWN;
	unsigned int * uiTestAddr = (unsigned int *)(uiBase + 0x608C34);

	switch(*uiTestAddr)
	{
		case EFLC_112:
		{
			m_GameVersion = GAME_VERSION_EFLC_2;

			SET_OFF(VAR_IPedDataNY, 0xE9B124); // done
			SET_OFF(FUNC_CPedMoveBlendOnFoot__Constructor, 0xA24D90); // done
			SET_OFF(FUNC_NEW_CPedData, __noop); // not needed
			SET_OFF(CALL_StartLoadingTune, 0x492D20); // DONE
			SET_OFF(VAR_NumberOfParkedCars, __noop); // not needed

			SET_OFF(FUNC_CEpisodes__IsEpisodeAvaliable,  __noop); // removed
			SET_OFF(FUNC_GetIndexFromPlayerInfo,  0x86CB20); // done
			SET_OFF(FUNC_GetLocalPlayerPed,  0x86CCA0); // done
			SET_OFF(FUNC_CTask__Destructor,  0xA2AD20); // done
			SET_OFF(FUNC_RemoveInitialLoadingScreens,  0x4921B6); // done
			SET_OFF(FUNC_GENERATETEXTURE,  0x425A60); // done

			//Player
			SET_OFF(FUNC_CreatePlayerPed, 0x871920); // done
			SET_OFF(FUNC_SetupPedIntelligence, 0x8E8C10); // done
			SET_OFF(FUNC_CPlayerPed__SetModelIndex, 0xA177C0); // done
			SET_OFF(FUNC_CPlayerPed__Constructor, 0xA18630); // done
			SET_OFF(VAR_Ped_Factory, 0x156B764); // done
			SET_OFF(FUNC_Setup_Ped, 0x4AAB30); // done
			SET_OFF(FUNC_CPedIntelligence__Reset, 0x9E6960); // done
			SET_OFF(FUNC_CPed__ScalarDeletingDestructor, 0x8F6AC0); // done

			//Game
			SET_OFF(VAR_MenuActive_1, 0x104E130); // done
			SET_OFF(VAR_MenuActive_2, 0x104E11F); // done

			//Script
			SET_OFF(FUNC_GetRunningScriptThread, 0x4CCD20); // done 
			SET_OFF(CALL_CScriptVM__Process, 0x8346A2); // done
			SET_OFF(VAR_ScrVM__ThreadPool, 0x186595C); // done
			SET_OFF(VAR_ScrVM__ActiveThread, 0x16EAD50); // done
			SET_OFF(FUNC_ScrVM__FindNativeAddress, 0x4CF760); // done
			SET_OFF(VAR_ScrVM__GlobalVariablesPool, 0x16EAD5C); // done

			//Weather
			SET_OFF(FUNC_SetWeather, 0x9E1580); // done
			SET_OFF(VAR_CurrentWeather, 0x15A0548); // done

			//Time
			SET_OFF(FUNC_SetTimeOfDay, 0x846970); // done
			SET_OFF(VAR_TimeOfDay, 0x10A4EA8); // done //PoorNaming(CouldbesomememberofCClock)
			SET_OFF(VAR_CClock__Hour, 0x10C9398); // done
			SET_OFF(VAR_CClock__Minute, 0x10C9394); // done
			SET_OFF(VAR_CClock__LockedHour, 0x10C93A0); // done
			SET_OFF(VAR_CClock__LockedMinute, 0x10C9388); // done
			SET_OFF(VAR_CClock__DayOfWeek, 0x10C93A8); // done

			//HUD
			SET_OFF(VAR_HudEnabled, 0x010A53DC); // done
			SET_OFF(VAR_RadarVisible, 0x010A53DF); // done
			SET_OFF(VAR_PlayerNamesVisible, 0x1906FB8); // done
			SET_OFF(VAR_AreaNamesDisabled, 0x151D5D5); // done

			//World
			SET_OFF(FUNC_CWorld__AddEntity, 0x86C0B0); // done
			SET_OFF(FUNC_CWorld__RemoveEntity, 0x86C120); // done
			SET_OFF(FUNC_CEntity__IsTouchingEntity, 0xA7C420); // done
			SET_OFF(FUNC_CMatrix__ConvertFromEulerAngles, 0x449870); // done
			SET_OFF(FUNC_CMatrix__ConvertFromQuaternion, 0x462F30); // done
			SET_OFF(FUNC_CQuaternion__ConvertFromMatrix, 0x44F810); // done

			//Vehicle
			SET_OFF(FUNC_CVehicle__SetLoadCollision, 0xBE6780); // done
			SET_OFF(FUNC_CVehicle__TurnEngineOn, 0x9FD530); // done
			SET_OFF(FUNC_CVehicle__TurnEngineOff, 0x9F03A0); // done
			SET_OFF(FUNC_CVehicle__RefreshColours, 0x9EEF70); // done
			SET_OFF(FUNC_CVehicle__RefreshLivery, 0xCE1B30); // done

			//Indicators
			SET_OFF(PATCH_CVehicle__HazzardLightsOn, 0x9FBC83); // done
			SET_OFF(FUNC_CVehicle__DrawIndicator, 0x9F7010); // done
			SET_OFF(RETURN_CVehicle__DrawIndicator, 0x9F7016); // done
			SET_OFF(FUNC_CVehicle__SetEngineOn,  0x9FD530); // done
			SET_OFF(FUNC_CVehicle__SetEngineOff,  0x9F03A0); // done
			SET_OFF(FUNC_CVehicle__SetComponentDisabled,  0x9F0240); // done
			SET_OFF(FUNC_CVehicle__SetTextureVariation,  0xCE1B30); // done
			SET_OFF(FUNC_CVehicle__BurstCarTyre,  0x9EF1A0); // done
			SET_OFF(FUNC_CVehicle__RemoveVehicleWindow,  0x9F0190); // done 
			SET_OFF(FUNC_CVehicleAudio__SetIndicators, 0xB18A00); // done

			// Weapon
			SET_OFF(FUNC_CWeapon__Initialize,  0x99D9D0); // done

			//Misc
			SET_OFF(VAR_CurrentWantedLevel, 0x10B416C);// done //PoorNaming(CouldbesomememberofCWanted)
			SET_OFF(VAR_ScrollBarText, 0x11B4508); // done
			SET_OFF(VAR_ScrollBarColor, 0x8DC8FD); // done
			SET_OFF(VAR_CameraManager, 0xF21B5C); // done
			SET_OFF(VAR_LocalPlayerState, 0x10619C8); // done
			SET_OFF(FUNC_GetLocalPlayerSpawnPosition, 0x7D5BC2); // done
			SET_OFF(CALL_SpawnLocalPlayer, 0x7D5C72); // done
			SET_OFF(FUNC_SpawnPlayer, 0x7D5220); // done
			SET_OFF(FUNC_GetTrafficLightState1, 0x9B27A0); // done
			SET_OFF(FUNC_GetTrafficLightState2, 0x9B2800); // done
			SET_OFF(VAR_CurrentAreaName, 0x1107606); // done
			SET_OFF(VAR_CurrentStreetName, 0x1107600 + 0x188); // done
			SET_OFF(VAR_NumLoadingScreens, 0x1821964); // done
			SET_OFF(VAR_FirstLoadingScreenDuration, 0x18480E8); // done
			SET_OFF(VAR_FirstLoadingScreenType, 0x18480F0); // done
			SET_OFF(VAR_HWnd, 0x16A9A54); // done
			SET_OFF(VAR_Time, 0x116E35C); // done

			//Input
			SET_OFF(VAR_Pads, 0x1088F68); // done
			SET_OFF(FUNC_CPad__Constructor, 0x865DA0); // done
			SET_OFF(FUNC_CPad__Initialize, 0x86B1D0); // done
			SET_OFF(FUNC_CPad__Destructor, 0x7FD6E0); // done

			//KeySync
			SET_OFF(VAR_CPlayerPed__VFTable, 0xD85714); // done
			SET_OFF(VAR_CAutomobile__VFTable, 0xDBA57C); // done
			SET_OFF(VAR_CBike__VFTable, 0xD9ED74); // done
			SET_OFF(VAR_CBoat__VFTable, 0xD9E974); // done
			SET_OFF(VAR_CTrain__VFTable, 0xD7D354); // done
			SET_OFF(VAR_CHeli__VFTable, 0xD6F0A4); // done
			SET_OFF(VAR_CPlane__VFTable, 0xD8BB1C); // done
			SET_OFF(FUNC_CPlayerPed__ProcessInput, 0xA17820); // done
			SET_OFF(FUNC_CAutomobile__ProcessInput, 0xC44780); // done
			SET_OFF(FUNC_CBike__ProcessInput, 0xB45490); // done
			SET_OFF(FUNC_CBoat__ProcessInput, 0xB41900); // done
			SET_OFF(FUNC_CTrain__ProcessInput, 0x998C30); // done
			SET_OFF(FUNC_CHeli__ProcessInput, 0x904920); // done
			SET_OFF(FUNC_CPlane__ProcessInput, 0xA61DA0); // done

			//Checkpoints
			SET_OFF(VAR_RenderCheckpoints_FirstCP, 0x825FB5); // done
			SET_OFF(VAR_RenderCheckpoints_LastCP, 0x826D55); // done

			//Pools
			SET_OFF(VAR_PedPool, 0x18219EC); // done
			SET_OFF(VAR_VehiclePool, 0x15C17B0); // done
			SET_OFF(VAR_PtrNodeSinglePool, 0x164CDF8); // done
			SET_OFF(VAR_PtrNodeDoublePool, 0x164CDFC); // done
			SET_OFF(VAR_EntryInfoNodesPool, 0x1697184); // done
			SET_OFF(VAR_AnimatedBuildingPool, 0x1696E1C); // done
			SET_OFF(VAR_BuildingPool, 0x1648A00); // done
			SET_OFF(VAR_ObjectPool, 0x118A660); // done
			SET_OFF(VAR_DummyObjectPool, 0x1648C38); // done
			SET_OFF(VAR_InteriorInstPool, 0x15E6B04); // done
			SET_OFF(VAR_PortalInstPool, 0x166069C); // done
			SET_OFF(VAR_AnimBlenderPool, 0x159C5E0); // done
			SET_OFF(VAR_AtdNodeAnimChangePooledObjectPool, 0x159C5E8); // done
			SET_OFF(VAR_AtdNodeAnimPlayerPool, 0x159C5E4); // done
			SET_OFF(VAR_crFrameFilterBoneMaskPool, 0x159C5EC); // done
			SET_OFF(VAR_crFrameFilterBoneAnaloguePool, 0x159C5F0); // done
			SET_OFF(VAR_crExpressionProcessorPool, 0x159C5F4); // done
			SET_OFF(VAR_crmtObserverPool, 0x159C5F8); // done
			SET_OFF(VAR_TaskPool, 0x15C353C); // done
			SET_OFF(VAR_DummyTaskPool, 0x160601C); // done
			SET_OFF(VAR_EventPool, 0x131FF4C); // done
			SET_OFF(VAR_PointRoutePool, 0x1697178); // done
			SET_OFF(VAR_PatrolRoutePool, 0x1697180); // done
			SET_OFF(VAR_NavMeshRoutePool, 0x169717C); // done
			SET_OFF(VAR_CamPool, 0x15A056C); // done
			SET_OFF(VAR_ExplosionTypePool, 0x1697170); // done
			SET_OFF(VAR_PedMoveBlendPool, 0x18219F4); // done
			SET_OFF(VAR_ParticleSystemPool, 0x162E080); // done
			SET_OFF(VAR_VehicleStructPool, 0x1606B44); // done
			SET_OFF(VAR_PedBasePool, 0x18219F8); // done
			SET_OFF(VAR_TaskInfoPool, 0x15C33C4); // done
			SET_OFF(VAR_PedAttractorPool, 0x169C82C); // done
			SET_OFF(VAR_TargettingPool, 0x1695C94); // done
			SET_OFF(FUNC_CPool__Allocate, 0x4AAF70); // done
			SET_OFF(FUNC_CPool__Release, 0x4B7DD0); // done
			SET_OFF(FUNC_CPool__AtHandle, 0x497750); // done
			SET_OFF(FUNC_CPool__HandleOf, 0x4B47D0); // done
			SET_OFF(FUNC_CPlayer__GetPlayerByNumber, 0x86CC80); // done
			SET_OFF(VAR_PlayerInfoArray, 0x10D9458); // done
			SET_OFF(VAR_LocalPlayerId, 0xF16134); // done

			//Physical
			SET_OFF(FUNC_CPhysical__SetMoveSpeed, 0xA7C040); // done
			SET_OFF(FUNC_CPhysical__GetMoveSpeed, 0xA7C0E0); // done
			SET_OFF(FUNC_CPhysical__SetTurnSpeed, 0xA7C130); // done
			SET_OFF(FUNC_CPhysical__GetTurnSpeed, 0xA7C1D0); // done
			SET_OFF(FUNC_CPhysical__SetLastDamageEntity, 0xA7C280); // done

			//Streaming
			SET_OFF(VAR_ResourceTypeWdrIndex, 0x157D300); // done
			SET_OFF(VAR_ResourceTypeWadIndex, 0xF1DD6C); // done
			SET_OFF(VAR_ResourceTypeScoIndex, 0xF3AC94); // done
			SET_OFF(VAR_ResourceTypeWtdIndex, 0xF16124); // done
			SET_OFF(VAR_ResourceTypeCutIndex, 0xF16190); // done

			SET_OFF(VAR_ResourceTypeWddIndex, 0xF1D5B8); // done
			SET_OFF(VAR_ResourceTypeWnvIndex, 0xF27ED4); // done
			SET_OFF(VAR_ResourceTypeRrrIndex, 0x11B8F30); // done
			SET_OFF(VAR_ResourceTypeWbdIndex, 0xF1E858); // done
			SET_OFF(VAR_ResourceTypeIplIndex, 0xF36D58); // done
			SET_OFF(VAR_ResourceTypeWbnIndex, 0xF36D7C); // done
			SET_OFF(VAR_ResourceTypeWbsIndex, 0xF3D220); // done
			SET_OFF(FUNC_RequestResource, 0x8978E0); // done
			SET_OFF(FUNC_LoadAllResources, 0x8978C0); // done
			SET_OFF(FUNC_HasResourceLoaded, 0x897A70); // done
			SET_OFF(FUNC_ReleaseResource, 0x897800); // done
			SET_OFF(FUNC_GetModelIndexFromHash, 0x9BCB70); // done
			SET_OFF(FUNC_CAnimStore__GetIndexFromHash, 0x48F080); // done
			SET_OFF(FUNC_LoadWorldAtPosition, 0xB8CE40); // done
			SET_OFF(FUNC_LoadWorldAtPositionStream, 0xAA2E00); // done

			//Ped
			SET_OFF(FUNC_CPed__SetDucking, 0x8F10C0); // done
			SET_OFF(FUNC_CPed__IsDucking, 0x8E6A80); // done
			SET_OFF(FUNC_CPed__DisableRagdoll, 0x8F0910); // done

			// PedWeapon
			SET_OFF(FUNC_CPedWeapon__SetCurrentWeapon, 0x9DDCF0); // done
			SET_OFF(FUNC_CPedWeapon__ShowWeapon, 0x9DFAD0); // done
			SET_OFF(FUNC_CPedWeapon__HideWeapon, 0x9DF8C0); // done
			SET_OFF(FUNC_CPedWeapon__SetAmmoByType, 0x9DD6D0); // done

			SET_OFF(FUNC_CPlayerInfo__Constructor,  0x849140); // done
			SET_OFF(FUNC_CPlayerInfo__Deconstructor,  0x8470C0); // done

			SET_OFF(FUNC_IV_LOADWORLDATPOS_BYTE,  0x110DFAC); // done

			//Tasks
			SET_OFF(FUNC_CPedTaskManager__SetTaskPriority, 0x9E3220); // done // TBC
			SET_OFF(FUNC_CPedTaskManager__SetTaskSecondary, 0x9E3430); // done
			SET_OFF(FUNC_CPedTaskManager__SetTaskMovement, 0x9E3790); // done
			SET_OFF(VAR_CTask__VFTable, 0xD87ECC);	// done
			SET_OFF(RETURN_CTask__Destructor, 0xA2AD2A); // done
			SET_OFF(FUNC_CTaskComplexNewGetInVehicle__Constructor, 0xA3C6F0); // done
			SET_OFF(FUNC_CTaskComplexNewExitVehicle__Constructor, 0xA3D310); // done
			SET_OFF(FUNC_CTaskComplexDie__Constructor, 0xAE33A0); // done
			SET_OFF(FUNC_CTaskSimpleDead__Constructor, 0xAE3BC0); // done
			SET_OFF(FUNC_CTaskSimpleCarSetPedInVehicle__Constructor, 0xAECB60); // done
			SET_OFF(FUNC_CTaskSimpleCarSetPedOut__Constructor, 0xAECFB0); // done
			SET_OFF(FUNC_CTaskSimpleStartWalking__Constructor, 0xA2F980); // done
			SET_OFF(FUNC_CTaskSimpleStopWalking__Constructor, 0xA43DE0); // done
			SET_OFF(FUNC_CTaskComplexJump__Constructor, 0xADDE00); // done
			SET_OFF(FUNC_CTaskSimpleTriggerLookAt__Constructor, 0xA47720); // done
			SET_OFF(FUNC_CTaskComplexPlayerOnFoot__Constructor, 0xA006C0); // done
			SET_OFF(FUNC_CTaskComplexGun__Constructor, 0xA8DF60); // done
			SET_OFF(FUNC_CTaskSimpleFireGun__Counstructor, 0xCFC1D0); // done
			SET_OFF(FUNC_CTaskSimpleAimGun__Constructor, 0xCFD5C0); // done 
			SET_OFF(FUNC_CTaskSimpleReloadGun__Constructor, 0xCFFAF0); // done

			//Weapons
			SET_OFF(FUNC_CPedWeapons__RemoveWeapon, 0x9DF990); // done
			SET_OFF(FUNC_CPedWeapons__RemoveAllWeapons, 0x9DFA00); // done

			// Game funcs
			SET_OFF(FUNC_IVGAME_FREEMEMORY, 0x401210); // done
			SET_OFF(FUNC_IVGAME_ALLOCMEMORY, 0x4011D0); // done
			SET_OFF(FUNC_IVGAME_GETSCREENCOORDSFROM3DCOORDS, 0xAF94C0); // done
			SET_OFF(FUNC_IVGAME_TOGGLELAZLOW_1, 0xF36F44); // done
			SET_OFF(FUNC_IVGAME_TOGGLELAZLOW_2, 0x160719C); // done
			SET_OFF(FUNC_IVGAME_INITCUTSCENE, 0x879660); // done
			SET_OFF(FUNC_IVGAME_STOPCUTSCENE, 0x878AF0); // done
			SET_OFF(FUNC_IVGAME_LOADWORLDATPOSITION, 0xB8CE40); // done

			// New tasks
			SET_OFF(FUNC_CTaskComplexGun__Constructor, 0xA8DF60); // done
			SET_OFF(FUNC_CTaskSimpleFireGun__Counstructor, 0xCFC1D0); // done
			SET_OFF(FUNC_CTaskSimpleAimGun__Constructor, 0xCFD5C0); // done
			SET_OFF(FUNC_CTaskSimpleReloadGun__Constructor, 0xCFFAF0); // done

			SET_OFF(CGame_Process__Sleep, 0x47342C); // done
			SET_OFF(CGame_Process_InitialiseRageGame, 0x4734F7); // done
			SET_OFF(RAGE_LoadGame, 0x6DECB1); // done
			SET_OFF(RAGE_StartNewGame, 0x6DED5F); // done !NO PATTERN  [TODO]!
 
			// New
			SET_OFF(RAGE_Camera__UnkownVoidPtr, 0xF21B5C); // done
			SET_OFF(IV_CamPool, 0x15A056C); // done
			SET_OFF(FUNC_IV__CreateCamera, 0x4B47D0); // done
			SET_OFF(RAGE_AssetManager__OpenFile, 0x45B016); // done
			SET_OFF(RAGE_AssetManager__OpenFileJmpBack, 0x45DA50); // done
			SET_OFF(RAGE_OpenFile, 0x7CB1C0); // done
			SET_OFF(RAGE_OpenFileHook, 0x491991); // done

			SET_OFF(IV_HookLoadingFiles, 0x45B00A); // done
			SET_OFF(IV_HookLoadingScreen__DAT,0x491991); // done
			SET_OFF(IV_HookLoadingScreen__WTD,0x491594); // done
			SET_OFF(IV_HookLoadingTune, 0x7FB998); // done

			SET_OFF(IV_Pool__SetPtrSinglePoolLimit, 0xFFFFFF); // fuck you
			SET_OFF(IV_Pool__SetPtrNodeDoublePoolLimit, 0xC4C366); // done
			SET_OFF(IV_Pool__SetEntryInfoNodePoolLimit, 0xCC79F6); // done
			SET_OFF(IV_Pool__SetPedPoolLimit_1, 0xFFFFFF); 
			SET_OFF(IV_Pool__SetPedPoolLimit_2, 0xFFFFFF);
			SET_OFF(IV_Pool__SetPedPoolLimit_3, 0xFFFFFF);
			SET_OFF(IV_Pool__SetPedPoolLimit_4, 0xFFFFFF);

			SET_OFF(IV_Pool__SetVehiclePoolLimit, 0xFFFFFF);
			SET_OFF(IV_Pool__SetVehicleStructPoolLimit, 0xFFFFFF);

			SET_OFF(IV_Hook__DisableParkedCars, 0xAF5E50); // done
			SET_OFF(IV_Hook__DisableEmergencyAndGarbageTrucks, 0x49454F); // done
			SET_OFF(IV_Hook__DisableVehicleEntries, 0xA04AB0); // done
			SET_OFF(IV_Hook__DisableVehicleExists, 0xA0EA2C); // done
			SET_OFF(IV_Hook__DisableRandomPedsAndVehicles_1,0x915DA4); // done
			SET_OFF(IV_Hook__DisableRandomPedsAndVehicles_2,0x494590); // done
			SET_OFF(IV_Hook__DisableRandomPedsAndVehicles_3,0x86FFCE); // done
			SET_OFF(IV_Hook__DisableScenarioPeds, 0xA646A0); // done
			SET_OFF(IV_Hook__DisableFakeCars, 0x977B20); // done

			SET_OFF(IV_Hook__CIKManager_AimWeapon__JmpBack, 0x90CA36); // done
			SET_OFF(IV_Hook__CIKManager_PointArms__JmpBack, 0x90A536); // done
			SET_OFF(IV_Hook__CIKManager_FireWeapon__JmpBack, 0x9A4576); // done
			SET_OFF(IV_Hook__CIKManager_AimWeapon, 0x90A530); // done
			SET_OFF(IV_Hook__CIKManager_PointArms, 0x9A4570); // done
			SET_OFF(IV_Hook__CIKManager_FireWeapon, 0x90CA30); // done

			SET_OFF(IV_Hook__LoadHUD, 0x8F241A); // done
			SET_OFF(IV_Hook__LoadInternalHud, 0x863DB0); // done
			SET_OFF(IV_Hook__LoadHudHook, 0xD6284C); // done

			SET_OFF(IV_Hook__LoadRadioLogo, 0x8559B6); // done
			SET_OFF(IV_Hook__LoadInternalRadioLogo, 0x855970); // done
			SET_OFF(IV_Hook__LoadRadioLogoHook, 0xD60FB0); // done

			SET_OFF(IV_Hook__LoadWorldAtPosition, 0x110DFAC); // done

			SET_OFF(IV_Hook__TextureSelect__JmpBack, 0x425A65); // done

			SET_OFF(IV_Hook__StartGameLoading_1, 0x10619E8); // done
			SET_OFF(IV_Hook__StartGameLoading_2, 0x45F890); // done
			SET_OFF(IV_Hook__StartGameLoading_3, 0x10619D8); // done
			SET_OFF(IV_Hook__StartGameLoading_4, 0x10619BC); // done
			SET_OFF(IV_Hook__StartGameLoading_5, 0x7CB7B0); // done
			SET_OFF(IV_Hook__StartGameLoading_6, 0x1821964); // done
			SET_OFF(IV_Hook__StartGameLoading_7, 0x18480F0); // done
			SET_OFF(IV_Hook__StartGameLoading_8, 0x18480E8); // done

			SET_OFF(IV_Hook__GameProcess_1, 0x4733F3); // done
			SET_OFF(IV_Hook__GameProcess_2, 0x4734C3); // done
			SET_OFF(IV_Hook__GameProcess_3, 0x104D691); // done sorry no pattern yet
			SET_OFF(IV_Hook__GameProcess_4, 0x104DB94); // done
			SET_OFF(IV_Hook__GameProcess_5, 0x10C3C64); // done
			SET_OFF(IV_Hook__GameProcess_6, 0x10619D8); // done see IV_Hook__StartGameLoading_3
			SET_OFF(IV_Hook__GameProcess_7, 0x16EA6D4); // done
			SET_OFF(IV_Hook__GameProcess_8, 0x493530); // done no pattern function changed

			SET_OFF(IV_Hook__IncreasePoolSizes, 0x86B650); // done

			SET_OFF(IV_Hook__UnkownPatch1, 0x9C34A0); // done
			SET_OFF(IV_Hook__UnkownPatch2, 0x40D6B5); // done

			SET_OFF(IV_Hook__PatchRandomTasks, 0x937BD0); // done
			SET_OFF(IV_Hook__PatchInternet_1, 0x1064940); // done
			SET_OFF(IV_Hook__PatchInternet_2, 0x7DEDA0); // done
			SET_OFF(IV_Hook__PatchHelpMessageBox, 0xF16700); // done
			SET_OFF(IV_Hook__PatchStartNewGame, 0x6DECB1); // done
			SET_OFF(IV_Hook__PatchStartupDOTsco, 0x83409A); // done
			SET_OFF(IV_Hook__PatchVehicleDriverProcess, 0xAEF300); // done
			SET_OFF(IV_Hook__PatchErrorReporting, 0x7CA700); // done
			SET_OFF(IV_Hook__PatchMissingTests1, 0x473402); // done
			SET_OFF(IV_Hook__PatchMissingTests2, 0x473607); // done

			SET_OFF(IV_Hook__PatchUnkownAddress1, 0x474160); // done
			SET_OFF(IV_Hook__PatchUnkownAddress2, 0x474B40); // done

			SET_OFF(IV_Hook__PatchSecuromCheck, 0xC1AD20); // done
			SET_OFF(IV_Hook__PatchPreventVehicleCrash, 0x9C34A0); // done
			SET_OFF(IV_Hook__PatchErrorMessageBoxes, 0x452700); // done

			SET_OFF(IV_Hook__DisableStartupResourceCheck_1, 0x10C2C64); // done
			SET_OFF(IV_Hook__DisableStartupResourceCheck_2, 0x9CFDF0); // done
			SET_OFF(IV_Hook__DisableStartupResourceCheck_3, 0xCCF2D0); // done
			SET_OFF(IV_Hook__DisableStartupResourceCheck_4, 0x4B3EE0); // done

			SET_OFF(IV_Hook__DisableAutomaticRadarTurnon_1, 0x4A5821); // done
			SET_OFF(IV_Hook__DisableAutomaticRadarTurnon_2, 0x83DDBE); // done

			SET_OFF(IV_Hook__PatchWeaponGiveWhenEnterVehicle, 0x9EF624); // done
			SET_OFF(IV_Hook__PatchEnableAndFixVehicleModels, 0x08BFCA0); // done
			SET_OFF(IV_Hook__PatchUnkownByte1, 0x853073); // done

			SET_OFF(IV_Hook__PatchDeathLoadingScreen, 0x88AA87); // done
			SET_OFF(IV_Func__CreatePed, 0xA18630); // done
			SET_OFF(IV_Func__SetupPed, 0x4AAB30); // done
			SET_OFF(IV_Var__PedFactory, 0x156B764); // done
			SET_OFF(IV_Func__SetupPedIntelligence, 0x8E8C10); // done
			SET_OFF(IV_Func__ShutdownPedIntelligence, 0x9E6960); // done
			SET_OFF(IV_Func__DeletePed, 0x8F6AC0); // done

			SET_OFF(IV_Func__DeletePedTaskID, 0x830DC0); // done
			SET_OFF(IV_Func__DeletePedTaskJump, 0xBF54C0); // done
			SET_OFF(IV_FUNC__TaskPedJump, 0xBF5600); // done
			SET_OFF(IV_Func__MovePedToPositionInterpolated, 0xBF6060); // done
			break;
		}
		case IV_107:
			m_GameVersion = GAME_VERSION_7;

			SET_OFF(VAR_IPedDataNY, 0xE9EC50);
			SET_OFF(FUNC_CPedMoveBlendOnFoot__Constructor, 0xA35410);
			SET_OFF(FUNC_NEW_CPedData, 0x43A960);
			SET_OFF(CALL_StartLoadingTune, 0x41FDA0);
			SET_OFF(VAR_NumberOfParkedCars, 0xF1D964);

			SET_OFF(FUNC_CEpisodes__IsEpisodeAvaliable,  0x814810);
			SET_OFF(FUNC_GetIndexFromPlayerInfo,  0x817DC0);
			SET_OFF(FUNC_GetLocalPlayerPed,  0x817F40);
			SET_OFF(FUNC_CTask__Destructor,  0xA288D0);
			SET_OFF(FUNC_RemoveInitialLoadingScreens,  0x424B26);
			SET_OFF(FUNC_GENERATETEXTURE,  0x639710);

			//Player
			SET_OFF(FUNC_CreatePlayerPed, 0x81CB90);
			SET_OFF(FUNC_SetupPedIntelligence, 0x89EC20);
			SET_OFF(FUNC_CPlayerPed__SetModelIndex, 0x9C0AA0);
			SET_OFF(FUNC_CPlayerPed__Constructor, 0x9C1910);
			SET_OFF(VAR_Ped_Factory, 0x15E35A0);
			SET_OFF(FUNC_Setup_Ped, 0x43A6A0);
			SET_OFF(FUNC_CPedIntelligence__Reset, 0x9C4DF0);
			SET_OFF(FUNC_CPed__ScalarDeletingDestructor, 0x8ACAC0);

			//Game
			SET_OFF(VAR_MenuActive_1, 0x10C7F80);
			SET_OFF(VAR_MenuActive_2, 0x10C7F6F);

			//Script
			SET_OFF(FUNC_GetRunningScriptThread, 0x5A4CA0);
			SET_OFF(CALL_CScriptVM__Process, 0x80A092);
			SET_OFF(VAR_ScrVM__ThreadPool, 0x1983310);
			SET_OFF(VAR_ScrVM__ActiveThread, 0x1849AE0);
			SET_OFF(FUNC_ScrVM__FindNativeAddress, 0x5A76D0);
			SET_OFF(VAR_ScrVM__GlobalVariablesPool, 0x1849AEC);

			//Weather
			SET_OFF(FUNC_SetWeather, 0x9E41D0);
			SET_OFF(VAR_CurrentWeather, 0x1639524);

			//Time
			SET_OFF(FUNC_SetTimeOfDay, 0x821200);
			SET_OFF(VAR_TimeOfDay, 0x11E8F0C);//PoorNaming(CouldbesomememberofCClock)
			SET_OFF(VAR_CClock__Hour, 0x11D5300);
			SET_OFF(VAR_CClock__Minute, 0x11D52FC);
			SET_OFF(VAR_CClock__LockedHour, 0x11D5308);
			SET_OFF(VAR_CClock__LockedMinute, 0x11D52F0);
			SET_OFF(VAR_CClock__DayOfWeek, 0x11D5310);

			//HUD
			SET_OFF(VAR_HudEnabled, 0x118034C);
			SET_OFF(VAR_RadarVisible, 0x118034F);
			SET_OFF(VAR_PlayerNamesVisible, 0x1967DD8);
			SET_OFF(VAR_AreaNamesDisabled, 0x118F0D2);

			//World
			SET_OFF(FUNC_CWorld__AddEntity, 0x817350);
			SET_OFF(FUNC_CWorld__RemoveEntity, 0x8173C0);
			SET_OFF(FUNC_CEntity__IsTouchingEntity, 0xA47B30);
			SET_OFF(FUNC_CMatrix__ConvertFromEulerAngles, 0x42F8A0);
			SET_OFF(FUNC_CMatrix__ConvertFromQuaternion, 0x5BE050);
			SET_OFF(FUNC_CQuaternion__ConvertFromMatrix, 0x506DB0);

			//Vehicle
			SET_OFF(FUNC_CVehicle__SetLoadCollision, 0xB77BB0);
			SET_OFF(FUNC_CVehicle__TurnEngineOn, 0x9D3600);
			SET_OFF(FUNC_CVehicle__TurnEngineOff, 0x9C6710);
			SET_OFF(FUNC_CVehicle__RefreshColours, 0x9C52E0);
			SET_OFF(FUNC_CVehicle__RefreshLivery, 0xCBA620);

			//Indicators
			SET_OFF(PATCH_CVehicle__HazzardLightsOn, 0x9D1D53);
			SET_OFF(FUNC_CVehicle__DrawIndicator, 0x9CD0F0);
			SET_OFF(RETURN_CVehicle__DrawIndicator, 0x9CD0F6);
			SET_OFF(FUNC_CVehicle__SetEngineOn,  0x9D3600);
			SET_OFF(FUNC_CVehicle__SetEngineOff,  0x9C6710);
			SET_OFF(FUNC_CVehicle__SetComponentDisabled,  0x9C65B0);
			SET_OFF(FUNC_CVehicle__SetTextureVariation,  0xCBA620);
			SET_OFF(FUNC_CVehicle__BurstCarTyre,  0x9C5510);
			SET_OFF(FUNC_CVehicle__RemoveVehicleWindow,  0x9C6500);
			SET_OFF(FUNC_CVehicleAudio__SetIndicators, 0xAEAC00);

			// Weapon
			SET_OFF(FUNC_CWeapon__Initialize,  0x976C20);

			//Misc
			SET_OFF(VAR_CurrentWantedLevel, 0x118F0DC);//PoorNaming(CouldbesomememberofCWanted)
			SET_OFF(VAR_ScrollBarText, 0x15F2228);
			SET_OFF(VAR_ScrollBarColor, 0x972FFD);
			SET_OFF(VAR_CameraManager, 0xF21A6C);
			SET_OFF(VAR_LocalPlayerState, 0x10F8068);//0=alive, 1=dead(?), 2=beingarrested(?), 5=respawning
			SET_OFF(FUNC_GetLocalPlayerSpawnPosition, 0x7B84E2);
			SET_OFF(CALL_SpawnLocalPlayer, 0x7B8592);
			SET_OFF(FUNC_SpawnPlayer, 0x7B7B40);
			SET_OFF(FUNC_GetTrafficLightState1, 0x88C6F0);
			SET_OFF(FUNC_GetTrafficLightState2, 0x88C750);
			SET_OFF(VAR_CurrentAreaName, 0x11DE0DE);
			SET_OFF(VAR_CurrentStreetName, 0x11DE260);
			SET_OFF(VAR_NumLoadingScreens, 0x18A8258);
			SET_OFF(VAR_FirstLoadingScreenDuration, 0x18A8F40);
			SET_OFF(VAR_FirstLoadingScreenType, 0x18A8F48);
			SET_OFF(VAR_HWnd, 0x1849DDC);
			SET_OFF(VAR_Time, 0x11DDE74);

			//Input
			SET_OFF(VAR_Pads, 0x10FB818);
			SET_OFF(FUNC_CPad__Constructor, 0x834180);
			SET_OFF(FUNC_CPad__Initialize, 0x8395B0);
			SET_OFF(FUNC_CPad__Destructor, 0x7C3680);

			//KeySync
			SET_OFF(VAR_CPlayerPed__VFTable, 0xD819C4);
			SET_OFF(VAR_CAutomobile__VFTable, 0xDB3C3C);
			SET_OFF(VAR_CBike__VFTable, 0xDB4064);
			SET_OFF(VAR_CBoat__VFTable, 0xDCA0E4);
			SET_OFF(VAR_CTrain__VFTable, 0xD78D4C);
			SET_OFF(VAR_CHeli__VFTable, 0xD6B1CC);
			SET_OFF(VAR_CPlane__VFTable, 0xD86104);
			SET_OFF(FUNC_CPlayerPed__ProcessInput, 0x9C0B00);
			SET_OFF(FUNC_CAutomobile__ProcessInput, 0xBFE870);
			SET_OFF(FUNC_CBike__ProcessInput, 0xC05C30);
			SET_OFF(FUNC_CBoat__ProcessInput, 0xCA8C60);
			SET_OFF(FUNC_CTrain__ProcessInput, 0x94CE70);
			SET_OFF(FUNC_CHeli__ProcessInput, 0x8B9290);
			SET_OFF(FUNC_CPlane__ProcessInput, 0xA1B080);

			//Checkpoints
			SET_OFF(VAR_RenderCheckpoints_FirstCP, 0x855966);
			SET_OFF(VAR_RenderCheckpoints_LastCP, 0x856705);

			//Pools
			SET_OFF(VAR_PedPool, 0x18A82AC);
			SET_OFF(VAR_VehiclePool, 0x1619240);
			SET_OFF(VAR_PtrNodeSinglePool, 0x16B7758);
			SET_OFF(VAR_PtrNodeDoublePool, 0x16B775C);
			SET_OFF(VAR_EntryInfoNodesPool, 0x1706E98);
			SET_OFF(VAR_AnimatedBuildingPool, 0x1706E94);
			SET_OFF(VAR_BuildingPool, 0x168FED0);
			SET_OFF(VAR_ObjectPool, 0x1350CE0);
			SET_OFF(VAR_DummyObjectPool, 0x168FF90);
			SET_OFF(VAR_InteriorInstPool, 0x165D2E4);
			SET_OFF(VAR_PortalInstPool, 0x16C3364);
			SET_OFF(VAR_AnimBlenderPool, 0x16397B0);
			SET_OFF(VAR_AtdNodeAnimChangePooledObjectPool, 0x16397B8);
			SET_OFF(VAR_AtdNodeAnimPlayerPool, 0x16397B4);
			SET_OFF(VAR_crFrameFilterBoneMaskPool, 0x16397BC);
			SET_OFF(VAR_crFrameFilterBoneAnaloguePool, 0x16397C0);
			SET_OFF(VAR_crExpressionProcessorPool, 0x16397C4);
			SET_OFF(VAR_crmtObserverPool, 0x16397C8);
			SET_OFF(VAR_TaskPool, 0x164B01C);
			SET_OFF(VAR_DummyTaskPool, 0x1706E8C);
			SET_OFF(VAR_EventPool, 0x152F4B4);
			SET_OFF(VAR_PointRoutePool, 0x1706E80);
			SET_OFF(VAR_PatrolRoutePool, 0x1706E88);
			SET_OFF(VAR_NavMeshRoutePool, 0x1706E84);
			SET_OFF(VAR_CamPool, 0x1618020);
			SET_OFF(VAR_ExplosionTypePool, 0x1706E78);
			SET_OFF(VAR_PedMoveBlendPool, 0x18A82B4);
			SET_OFF(VAR_ParticleSystemPool, 0x169F4C4);
			SET_OFF(VAR_VehicleStructPool, 0x16D6594);
			SET_OFF(VAR_PedBasePool, 0x18A82B8);
			SET_OFF(VAR_TaskInfoPool, 0x1618040);
			SET_OFF(VAR_PedAttractorPool, 0x17168BC);
			SET_OFF(VAR_TargettingPool, 0x1711134);
			SET_OFF(FUNC_CPool__Allocate, 0x439CB0);
			SET_OFF(FUNC_CPool__Release, 0x448300);
			SET_OFF(FUNC_CPool__AtHandle, 0x426700);
			SET_OFF(FUNC_CPool__HandleOf, 0x447230);
			SET_OFF(FUNC_CPlayer__GetPlayerByNumber, 0x817F20);
			SET_OFF(VAR_PlayerInfoArray, 0x11A7008);
			SET_OFF(VAR_LocalPlayerId, 0xF1CC68);

			//Physical
			SET_OFF(FUNC_CPhysical__SetMoveSpeed, 0xA47750);
			SET_OFF(FUNC_CPhysical__GetMoveSpeed, 0xA477F0);
			SET_OFF(FUNC_CPhysical__SetTurnSpeed, 0xA47840);
			SET_OFF(FUNC_CPhysical__GetTurnSpeed, 0xA478E0);
			SET_OFF(FUNC_CPhysical__SetLastDamageEntity, 0xA47990);

			//Streaming
			SET_OFF(VAR_ResourceTypeWdrIndex, 0x15F73A0);
			SET_OFF(VAR_ResourceTypeWadIndex, 0xF27324);
			SET_OFF(VAR_ResourceTypeScoIndex, 0xF3E28C);
			SET_OFF(VAR_ResourceTypeWtdIndex, 0xF1CD84);
			SET_OFF(VAR_ResourceTypeCutIndex, 0xF1EFC0);
			SET_OFF(VAR_ResourceTypeWddIndex, 0xF272E4);
			SET_OFF(VAR_ResourceTypeWnvIndex, 0xF2A0C4);
			SET_OFF(VAR_ResourceTypeRrrIndex, 0x15DAEB0);
			SET_OFF(VAR_ResourceTypeWbdIndex, 0xF2AAA0);
			SET_OFF(VAR_ResourceTypeIplIndex, 0xF3BE40);
			SET_OFF(VAR_ResourceTypeWbnIndex, 0xF3F224);
			SET_OFF(VAR_ResourceTypeWbsIndex, 0xF412E0);
			SET_OFF(FUNC_RequestResource, 0x832C40);
			SET_OFF(FUNC_LoadAllResources, 0x832C20);
			SET_OFF(FUNC_HasResourceLoaded, 0x832DD0);
			SET_OFF(FUNC_ReleaseResource, 0x832B60);
			SET_OFF(FUNC_GetModelIndexFromHash, 0x98AAE0);
			SET_OFF(FUNC_CAnimStore__GetIndexFromHash, 0x862C90);
			SET_OFF(FUNC_LoadWorldAtPosition, 0xB2BBA0);
			SET_OFF(FUNC_LoadWorldAtPositionStream, 0xA74790);

			//Ped
			SET_OFF(FUNC_CPed__SetDucking, 0x8A70C0);
			SET_OFF(FUNC_CPed__IsDucking, 0x89C780);
			SET_OFF(FUNC_CPed__DisableRagdoll, 0x8A6910);

			// PedWeapon
			SET_OFF(FUNC_CPedWeapon__SetCurrentWeapon, 0x9AA330);
			SET_OFF(FUNC_CPedWeapon__ShowWeapon, 0x9AC110);
			SET_OFF(FUNC_CPedWeapon__HideWeapon, 0x9ABF00);
			SET_OFF(FUNC_CPedWeapon__SetAmmoByType, 0x9A9D60);

			SET_OFF(FUNC_CPlayerInfo__Constructor,  0x87AB70);
			SET_OFF(FUNC_CPlayerInfo__Deconstructor,  0x878AF0);

			SET_OFF(FUNC_IV_LOADWORLDATPOS_BYTE,  0x11DC444);

			//Tasks
			SET_OFF(FUNC_CPedTaskManager__SetTaskPriority, 0x9E58B0);
			SET_OFF(FUNC_CPedTaskManager__SetTaskSecondary, 0x9E5AC0);
			SET_OFF(FUNC_CPedTaskManager__SetTaskMovement, 0x9E5E20);
			SET_OFF(VAR_CTask__VFTable, 0xD87224);
			SET_OFF(RETURN_CTask__Destructor, 0xA288DA);
			SET_OFF(FUNC_CTaskComplexNewGetInVehicle__Constructor, 0xA2BCF0);
			SET_OFF(FUNC_CTaskComplexNewExitVehicle__Constructor, 0xA2C920);
			SET_OFF(FUNC_CTaskComplexDie__Constructor, 0xABC6C0);
			SET_OFF(FUNC_CTaskSimpleDead__Constructor, 0xABCF10);
			SET_OFF(FUNC_CTaskSimpleCarSetPedInVehicle__Constructor, 0xA9CB60);
			SET_OFF(FUNC_CTaskSimpleCarSetPedOut__Constructor, 0xA9CFB0);
			SET_OFF(FUNC_CTaskSimpleStartWalking__Constructor, 0xA0E310);//0xA1D830//0xA0DFF0
			SET_OFF(FUNC_CTaskSimpleStopWalking__Constructor, 0xA1D730);
			SET_OFF(FUNC_CTaskComplexJump__Constructor, 0xAB4D90);
			SET_OFF(FUNC_CTaskSimpleTriggerLookAt__Constructor, 0xA20FF0);
			SET_OFF(FUNC_CTaskComplexPlayerOnFoot__Constructor, 0x9AD950);
			SET_OFF(FUNC_CTaskComplexGun__Constructor, 0xA5FD80);
			SET_OFF(FUNC_CTaskSimpleFireGun__Counstructor, 0xCC7400);
			SET_OFF(FUNC_CTaskSimpleAimGun__Constructor, 0xCC87F0);
			SET_OFF(FUNC_CTaskSimpleReloadGun__Constructor, 0xCCAD20);

			//Weapons
			SET_OFF(FUNC_CPedWeapons__RemoveWeapon, 0x9ABFD0);
			SET_OFF(FUNC_CPedWeapons__RemoveAllWeapons, 0x9AC040);

			// Game funcs
			SET_OFF(FUNC_IVGAME_FREEMEMORY, 0x5B1C10);
			SET_OFF(FUNC_IVGAME_ALLOCMEMORY, 0x4011D0);
			SET_OFF(FUNC_IVGAME_GETSCREENCOORDSFROM3DCOORDS, 0xAFF3A0);
			SET_OFF(FUNC_IVGAME_TOGGLELAZLOW_1, 0xF38728);
			SET_OFF(FUNC_IVGAME_TOGGLELAZLOW_2, 0x166805C);
			SET_OFF(FUNC_IVGAME_INITCUTSCENE, 0x866980);
			SET_OFF(FUNC_IVGAME_STOPCUTSCENE, 0x865E10);
			SET_OFF(FUNC_IVGAME_LOADWORLDATPOSITION, 0xB2BBA0);

			// New tasks
			SET_OFF(FUNC_CTaskComplexGun__Constructor, 0xA5FD80);
			SET_OFF(FUNC_CTaskSimpleFireGun__Counstructor, 0xCC7400);
			SET_OFF(FUNC_CTaskSimpleAimGun__Constructor, 0xCC87F0); 
			SET_OFF(FUNC_CTaskSimpleReloadGun__Constructor, 0xCCAD20);

			SET_OFF(CGame_Process__Sleep, 0x402B3C);
			SET_OFF(CGame_Process_InitialiseRageGame, 0x402C07);
			SET_OFF(RAGE_LoadGame, 0x5B0311);
			SET_OFF(RAGE_StartNewGame, 0x5B03BF);

			// New
			SET_OFF(RAGE_Camera__UnkownVoidPtr, 0xF21A6C);
			SET_OFF(IV_CamPool, 0x1618020);
			SET_OFF(FUNC_IV__CreateCamera, 0x447230);
			SET_OFF(RAGE_AssetManager__OpenFile, 0x5B2796);
			SET_OFF(RAGE_AssetManager__OpenFileJmpBack, 0x5B4F60);
			SET_OFF(RAGE_OpenFile, 0x7B2740);
			SET_OFF(RAGE_OpenFileHook, 0x424301);

			SET_OFF(IV_HookLoadingFiles, 0x5B278A);
			SET_OFF(IV_HookLoadingScreen__DAT,0x424301);
			SET_OFF(IV_HookLoadingScreen__WTD,0x423F04);
			SET_OFF(IV_HookLoadingTune, 0x7B99C8);

			SET_OFF(IV_Pool__SetPtrSinglePoolLimit, 0xB534B6);
			SET_OFF(IV_Pool__SetPtrNodeDoublePoolLimit, 0xB534F6);
			SET_OFF(IV_Pool__SetEntryInfoNodePoolLimit, 0xC796D6);
			SET_OFF(IV_Pool__SetPedPoolLimit_1, 0x43A9FC); 
			SET_OFF(IV_Pool__SetPedPoolLimit_2, 0x43AA1A);
			SET_OFF(IV_Pool__SetPedPoolLimit_3, 0x43AA27);
			SET_OFF(IV_Pool__SetPedPoolLimit_4, 0x43AA5C);

			SET_OFF(IV_Pool__SetVehiclePoolLimit, 0x9D43B8);
			SET_OFF(IV_Pool__SetVehicleStructPoolLimit, 0xBEA871);

			SET_OFF(IV_Hook__DisableParkedCars, 0xB3EDF0);
			SET_OFF(IV_Hook__DisableEmergencyAndGarbageTrucks, 0x4215CF);
			SET_OFF(IV_Hook__DisableVehicleEntries, 0x9B1ED0);
			SET_OFF(IV_Hook__DisableVehicleExists, 0x9BBBFC);
			SET_OFF(IV_Hook__DisableRandomPedsAndVehicles_1,0x8ACD64);
			SET_OFF(IV_Hook__DisableRandomPedsAndVehicles_2,0x421610);
			SET_OFF(IV_Hook__DisableRandomPedsAndVehicles_3,0x81B22E);
			SET_OFF(IV_Hook__DisableScenarioPeds, 0x9F72C0);
			SET_OFF(IV_Hook__DisableFakeCars, 0x9055D0);

			SET_OFF(IV_Hook__CIKManager_AimWeapon__JmpBack, 0x950D66);
			SET_OFF(IV_Hook__CIKManager_PointArms__JmpBack, 0x94E866);
			SET_OFF(IV_Hook__CIKManager_FireWeapon__JmpBack, 0x97D7C6);
			SET_OFF(IV_Hook__CIKManager_AimWeapon, 0x94E860);
			SET_OFF(IV_Hook__CIKManager_PointArms, 0x97D7C0);
			SET_OFF(IV_Hook__CIKManager_FireWeapon, 0x950D60);

			SET_OFF(IV_Hook__LoadHUD, 0x8A841A);
			SET_OFF(IV_Hook__LoadInternalHud, 0x848390);
			SET_OFF(IV_Hook__LoadHudHook, 0xD5DCF4);

			SET_OFF(IV_Hook__LoadRadioLogo, 0x822E76);
			SET_OFF(IV_Hook__LoadInternalRadioLogo, 0x822E30);
			SET_OFF(IV_Hook__LoadRadioLogoHook, 0xD5B7B8);

			SET_OFF(IV_Hook__LoadWorldAtPosition, 0x11DC444);

			SET_OFF(IV_Hook__TextureSelect__JmpBack, 0x639715);

			SET_OFF(IV_Hook__StartGameLoading_1, 0x10F8088);
			SET_OFF(IV_Hook__StartGameLoading_2, 0x5AF930);
			SET_OFF(IV_Hook__StartGameLoading_3, 0x10F8078);
			SET_OFF(IV_Hook__StartGameLoading_4, 0x10F805C);
			SET_OFF(IV_Hook__StartGameLoading_5, 0x7B2DF0);
			SET_OFF(IV_Hook__StartGameLoading_6, 0x18A8258);
			SET_OFF(IV_Hook__StartGameLoading_7, 0x18A8F48);
			SET_OFF(IV_Hook__StartGameLoading_8, 0x18A8F40);

			SET_OFF(IV_Hook__GameProcess_1, 0x402B03);
			SET_OFF(IV_Hook__GameProcess_2, 0x402BD3);
			SET_OFF(IV_Hook__GameProcess_3, 0x10C74E1);
			SET_OFF(IV_Hook__GameProcess_4, 0x10C79E4);
			SET_OFF(IV_Hook__GameProcess_5, 0x119EB14);
			SET_OFF(IV_Hook__GameProcess_6, 0x10F8078);
			SET_OFF(IV_Hook__GameProcess_7, 0x172427C);
			SET_OFF(IV_Hook__GameProcess_8, 0x4205B0);

			SET_OFF(IV_Hook__IncreasePoolSizes, 0xC72F10);

			SET_OFF(IV_Hook__UnkownPatch1, 0xCBA1F0);
			SET_OFF(IV_Hook__UnkownPatch2, 0x625F15);

			SET_OFF(IV_Hook__PatchRandomTasks, 0x9849F0);
			SET_OFF(IV_Hook__PatchInternet_1, 0x10F1390);
			SET_OFF(IV_Hook__PatchInternet_2, 0x7AF1A0);
			SET_OFF(IV_Hook__PatchHelpMessageBox, 0xF1DC40);
			SET_OFF(IV_Hook__PatchStartNewGame, 0x5B0311);
			SET_OFF(IV_Hook__PatchStartupDOTsco, 0x809A8A);
			SET_OFF(IV_Hook__PatchVehicleDriverProcess, 0xA9F300);
			SET_OFF(IV_Hook__PatchErrorReporting, 0xD356D0);
			SET_OFF(IV_Hook__PatchMissingTests1, 0x402B12);
			SET_OFF(IV_Hook__PatchMissingTests2, 0x402D17);

			SET_OFF(IV_Hook__PatchUnkownAddress1, 0x403870);
			SET_OFF(IV_Hook__PatchUnkownAddress2, 0x404250);

			SET_OFF(IV_Hook__PatchSecuromCheck, 0xBAC160);
			SET_OFF(IV_Hook__PatchPreventVehicleCrash, 0xCBA1F0);
			SET_OFF(IV_Hook__PatchErrorMessageBoxes, 0x5A8CB0);

			SET_OFF(IV_Hook__DisableStartupResourceCheck_1, 0x119DB14);
			SET_OFF(IV_Hook__DisableStartupResourceCheck_2, 0x9E2E30);
			SET_OFF(IV_Hook__DisableStartupResourceCheck_3, 0xCA76E0);
			SET_OFF(IV_Hook__DisableStartupResourceCheck_4, 0x446970);

			SET_OFF(IV_Hook__DisableAutomaticRadarTurnon_1, 0x42D3D1);
			SET_OFF(IV_Hook__DisableAutomaticRadarTurnon_2, 0x811B6E);

			SET_OFF(IV_Hook__PatchWeaponGiveWhenEnterVehicle, 0x9C5994);
			SET_OFF(IV_Hook__PatchEnableAndFixVehicleModels, 0x8F2F40);
			SET_OFF(IV_Hook__PatchUnkownByte1, 0x857133);

			SET_OFF(IV_Hook__PatchDeathLoadingScreen, 0x874EF7);
			SET_OFF(IV_Func__CreatePed, 0x9C1910);
			SET_OFF(IV_Func__SetupPed, 0x43A6A0);
			SET_OFF(IV_Var__PedFactory, 0x15E35A0);
			SET_OFF(IV_Func__SetupPedIntelligence, 0x89EC20);
			SET_OFF(IV_Func__ShutdownPedIntelligence, 0x9C4DF0);
			SET_OFF(IV_Func__DeletePed, 0x8ACAC0);

			SET_OFF(IV_Func__DeletePedTaskID, 0x8067A0);
			SET_OFF(IV_Func__DeletePedTaskJump, 0xB868E0);
			SET_OFF(IV_FUNC__TaskPedJump, 0xB86A20);
			SET_OFF(IV_Func__MovePedToPositionInterpolated, 0xB87480);

			break;
		default:
			break;

	};
	CLogFile::Printf( "Finished patching addresses to offsets" );
}