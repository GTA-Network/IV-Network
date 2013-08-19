//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: IVParachuteData.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef IVParachuteData_h
#define IVParachuteData_h

#pragma warning(disable:4305)

#include <IV/CIVScript.h>
 
#define IS_CHAR_INJURED CIVScript::IsCharInjured
#define GET_CHAR_COORDINATES CIVScript::GetCharCoordinates
#define REQUEST_AMBIENT_AUDIO_BANK CIVScript::RequestAmbientAudioBank
#define IS_CHAR_IN_ANY_CAR CIVScript::IsCharInAnyCar
#define DISABLE_INTERMEZZO_CAMS true
#define DOES_CAM_EXIST CIVScript::DoesCamExist
#define DESTROY_CAM CIVScript::DestroyCam
#define COUNT_SCRIPT_CAMS CIVScript::CountScriptCams
#define ACTIVATE_SCRIPTED_CAMS CIVScript::ActivateScriptedCams
#define DOES_CHAR_EXISTS CIVScript::DoesCharExist
#define BLOCK_PED_WEAPON_SWITCHING CIVScript::BlockPedWeaponSwitching
#define UNLOCK_RAGDOLL CIVScript::UnlockRagdoll
#define SET_GAME_CAMERA_CONTROLS_ACTIVE CIVScript::SetGameCameraControlsActive
#define SET_BLOCKING_OF_NON_TEMPORARY_EVENTS CIVScript::SetBlockingOfNonTemporaryEvents
#define SET_CHAR_INVINCIBLE CIVScript::SetCharInvincible
#define GIVE_CHAR_WEAPON CIVScript::GiveWeaponToChar
#define STOP_SOUND CIVScript::StopSound
#define RELEASE_SOUND_ID CIVScript::ReleaseSoundId
#define DOES_OBJECT_EXIST CIVScript::DoesObjectExist
#define DETACH_OBJECT CIVScript::DetachObject
#define DELETE_OBJECT CIVScript::DeleteObject
#define IS_VEH_DRIVEABLE CIVScript::IsVehDriveable
#define MARK_CAR_AS_NO_LONGER_NEEDED CIVScript::MarkCarAsNoLongerNeeded
#define IS_CONTROL_JUST_PRESSED CIVScript::IsControlJustPressed
#define GET_CHAR_VELOCITY CIVScript::GetCharVelocity
#define GET_GROUND_Z_FOR_3D_COORD CIVScript::GetGroundZFor3DCoord
#define IS_INTERIOR_SCENE CIVScript::IsInteriorScene
#define TASK_PLAY_ANIM_NON_INTERRUPTABLE CIVScript::TaskPlayAnimNonInterruptable
#define IS_CHAR_PLAYING_ANIM CIVScript::IsCharPlayingAnim
#define GET_CHAR_HEADING CIVScript::GetCharHeading
#define VMAG __noop
#define ABSF CIVScript::DoABSF
#define GET_CHAR_ANIM_CURRENT_TIME CIVScript::GetCharAnimCurrentTime
#define IS_PED_RAGDOLL CIVScript::IsPedRagdoll
#define BLEND_FROM_NM_WITH_ANIM CIVScript::BlendFromNmWithAnim
#define SWITCH_PED_TO_ANIMATED CIVScript::SwitchPedToAnimated
#define GET_CURRENT_CHAR_WEAPON CIVScript::GetCurrentCharWeapon
#define GIVE_WEAPON_TO_CHAR CIVScript::GiveWeaponToChar
#define SET_CHAR_COLLISION CIVScript::SetCharCollision
#define SET_CAR_COLLISION CIVScript::SetCarCollision
#define GET_GAME_TIMER CIVScript::GetGameTimer
#define SET_CHAR_HEADING CIVScript::SetCharHeading
#define GET_CAR_SPEED_VECTOR CIVScript::GetCarSpeedVector
#define GET_CAR_HEADING CIVScript::GetCarHeading
#define GET_GAME_CAM CIVScript::GetGameCam
#define GET_CAM_POS CIVScript::GetCamPos
#define GET_CAM_ROT CIVScript::GetCamRot
#define GET_CAM_FOV CIVScript::GetCamFov
#define CREATE_CAM CIVScript::CreateCam
#define SET_CAM_MOTION_BLUR CIVScript::SetCamMotionBlur
#define ATTACH_CAM_TO_PED CIVScript::AttachCamToPed
#define SET_CAM_ATTACH_OFFSET CIVScript::SetCamAttachOffset
#define SET_CAM_ATTACH_OFFSET_IS_RELATIVE CIVScript::SetCamAttachOffsetIsRelative
#define POINT_CAM_AT_PED CIVScript::PointCamAtPed
#define SET_CAM_POINT_OFFSET CIVScript::SetCamPointOffset
#define SET_CAM_POINT_OFFSET_IS_RELATIVE CIVScript::SetCamPointOffsetIsRelative
#define SET_CAM_POS CIVScript::SetCamPos
#define UNATTACH_CAM CIVScript::UnattachCam
#define UNPOINT_CAM CIVScript::UnpointCam
#define SET_CAM_ACTIVE CIVScript::SetCamActive
#define SET_CAM_PROPAGATE CIVScript::SetCamPropagate
#define GENERATE_RANDOM_FLOAT_IN_RANGE CIVScript::GenerateRandomFloatInRange
#define SET_CAM_FOV CIVScript::SetCamFov
#define SHAKE_PAD CIVScript::ShakePad
#define ROUND CIVScript::Round
#define SET_CHAR_ROTATION CIVScript::SetCharRotation
#define SET_CHAR_VELOCITY CIVScript::SetCharVelocity
#define CONVERT_INT_TO_PLAYERINDEX CIVScript::ConvertIntToPlayerIndex
#define GET_PLAYER_ID CIVScript::GetPlayerId
#define GET_FRAME_TIME CIVScript::GetFrameTime
#define GET_CHAR_HEIGHT_ABOVE_GROUND CIVScript::GetCharHeightAboveGround
#define WAS_PED_SKELETON_UPDATED __noop
#define GET_PED_BONE_POSITION CIVScript::GetPedBonePosition
#define TO_FLOAT CIVScript::ToFloat
#define ABSI CIVScript::DoABSI
#define IS_PLAYER_CONTROL_ON CIVScript::IsPlayerControlOn
#define CLEAR_HELP CIVScript::ClearHelp
#define IS_THIS_HELP_MESSAGE_BEING_DISPLAYED CIVScript::IsThisHelpMessageBeingDisplayed
#define PRINT_HELP CIVScript::PrintHelp
#define SET_PED_WINDY_CLOTHING_SCALE __noop
#define IS_CHAR_IN_WATER CIVScript::IsCharInWater
#define CLEAR_CHAR_TASKS_IMMEDIATELY CIVScript::ClearCharTasksImmediately
#define GET_CHAR_HEALTH CIVScript::GetCharHealth
#define SWITCH_PED_TO_RAGDOLL CIVScript::SwitchPedToRagdoll
#define PLAY_SOUND_FROM_PED CIVScript::PlaySoundFromPed
#define SET_CHAR_HEALTH CIVScript::SetCharHealth
#define GET_SOUND_ID CIVScript::GetSoundId
#define CREATE_OBJECT CIVScript::CreateObject
#define ATTACH_OBJECT_TO_PED CIVScript::AttachObjectToPed
#define PLAY_OBJECT_ANIM CIVScript::PlayObjectAnim
#define IS_OBJECT_PLAYING_ANIM CIVScript::IsObjectPlayingAnim
#define IS_CONTROL_PRESSED CIVScript::IsControlPressed
#define IS_USING_CONTROLLER __noop
#define SET_FOLLOW_PED_PITCH_LIMIT_DOWN  CIVScript::SetFollowPedPitchLimitDown
#define VDIST2 CIVScript::DoVDIST2
#define USING_STANDARD_CONTROLS CIVScript::IsUsingStandardControls
#define SET_VARIABLE_ON_SOUND CIVScript::SetVariableOnSound
#define GET_CLOSEST_CAR CIVScript::GetClosestCar
#define CLEAR_CHAR_SECONDARY_TASK CIVScript::ClearCharSecondaryTask
#define TASK_PLAY_ANIM_WITH_FLAGS_AND_START_PHASE __noop
#define SET_OBJECT_COLLISION CIVScript::SetObjectCollision
#define SET_OBJECT_DYNAMIC CIVScript::SetObjectDynamic
#define DOES_VEHICLE_EXIST CIVScript::DoesVehicleExist
#define GET_CAR_SPEED CIVScript::GetCarSpeed
#define FLOOR CIVScript::DoFloor
#define TASK_PLAY_ANIM_WITH_FLAGS CIVScript::TaskPlayAnimWithFlags
#define TASK_PLAY_ANIM CIVScript::TaskPlayAnim
#define GET_FLOAT_STAT CIVScript::GetFloatStat
#define SET_FLOAT_STAT CIVScript::SetFloatStat
#define ATAN2 CIVScript::DoATAN2
#define IS_BUTTON_JUST_PRESSED CIVScript::IsButtonJustPressed
#define CREATE_NM_MESSAGE CIVScript::CreateNmMessage
#define SEND_NM_MESSAGE CIVScript::SendNmMessage
#define GET_POSITION_OF_ANALOGUE_STICKS CIVScript::GetPositionOfAnalogueSticks
#define GET_CONTROL_VALUE CIVScript::GetControlValue
#define GET_KEYBOARD_MOVE_INPUT CIVScript::GetKeyboardMoveInput
#define IS_CHAR_ON_FIRE CIVScript::IsCharOnFire
#define IS_CHAR_IN_ANY_HELI CIVScript::IsCharInAnyHeli
#define STORE_CAR_CHAR_IS_IN_NO_SAVE CIVScript::StoreCarCharIsInNoSave
#define IS_CAR_A_MISSION_CAR CIVScript::IsCarAMissionCar
#define SET_CAR_AS_MISSION_CAR CIVScript::SetCarAsMissionCar
#define GET_OFFSET_FROM_CAR_IN_WORLD_COORDS CIVScript::GetOffsetFromCarInWorldCoords
#define SET_CHAR_VISIBLE CIVScript::SetCharVisible
#define WARP_CHAR_FROM_CAR_TO_COORD CIVScript::WarpCharFromCarToCoord
#define ATTACH_PED_TO_CAR CIVScript::AttachPedToCar
#define OPEN_SEQUENCE_TASK CIVScript::OpenSequenceTask
#define CLOSE_SEQUENCE_TASK CIVScript::CloseSequenceTask
#define TASK_PERFORM_SEQUENCE CIVScript::TaskPerformSequence
#define CLEAR_SEQUENCE_TASK CIVScript::ClearSequenceTask
#define IS_CHAR_ON_ANY_BIKE CIVScript::IsCharOnAnyBike
#define IS_CAR_IN_AIR_PROPER CIVScript::IsCarInAirProper
#define GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS CIVScript::GetOffsetFromCharInWorldCoords
#define IS_CHAR_VISIBLE CIVScript::IsCharVisible
#define CONTROL_CAR_DOOR CIVScript::ControlCarDoor
#define GET_OBJECT_COORDINATES CIVScript::GetObjectCoordinates
#define SLIDE_OBJECT CIVScript::SlideObject
#define SET_OBJECT_ALPHA CIVScript::SetObjectAlpha
#define IS_CHAR_GETTING_UP CIVScript::IsCharGettingUp
#define CLEAR_CHAR_TASKS CIVScript::ClearCharTasks
#define IS_HELP_MESSAGE_BEING_DISPLAYED CIVScript::IsHelpMessageBeingDisplayed
#define IS_OBJECT_ATTACHED CIVScript::IsObjectAttached
#define ATTACH_PARACHUTE_MODEL_TO_PLAYER __noop
#define HAS_CHAR_GOT_WEAPON CIVScript::HasCharGotWeapon
#define REMOVE_WEAPON_FROM_CHAR CIVScript::RemoveWeaponFromChar
#define SET_DRAW_PLAYER_COMPONENT CIVScript::SetDrawPlayerComponent
#define HAVE_ANIMS_LOADED CIVScript::HaveAnimsLoaded
#define HAS_MODEL_LOADED CIVScript::HasModelLoaded
#define HAS_SCRIPT_LOADED CIVScript::HasScriptLoaded
#define START_NEW_SCRIPT CIVScript::StartNewScript
#define GET_PLAYER_CHAR CIVScript::GetPlayerChar
#define IS_PLAYER_BEING_ARRESTED CIVScript::IsPlayerBeingArrested
#define FREEZE_OBJECT_POSITION CIVScript::FreezeObjectPosition
#define GET_OBJECT_ANIM_CURRENT_TIME CIVScript::GetObjectAnimCurrentTime
#define IS_SCREEN_FADED_OUT CIVScript::IsScreenFadedOut
#define GET_CHAR_DRAWABLE_VARIATION CIVScript::GetCharDrawableVariation
#define SET_CHAR_COMPONENT_VARIATION CIVScript::SetCharComponentVariation
#define REQUEST_MODEL CIVScript::RequestModel
#define REQUEST_ANIMS CIVScript::RequestAnims
#define MARK_MODEL_AS_NO_LONGER_NEEDED CIVScript::MarkModelAsNoLongerNeeded
#define REMOVE_ANIMS CIVScript::RemoveAnims
#define IS_PLAYER_PLAYING CIVScript::IsPlayerPlaying
#define IS_SCREEN_FADED_IN CIVScript::IsScreenFadedIn
#define IS_PLAYER_FREE_FOR_AMBIENT_TASK CIVScript::IsPlayerFreeForAmbientTask
#define GET_OBJECT_PED_IS_HOLDING CIVScript::GetObjectPedIsHolding
#define CREATE_OBJECT_NO_OFFSET CIVScript::CreateObjectNoOffset
#define SET_OBJECT_VISIBLE CIVScript::SetObjectVisible
#define SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN CIVScript::SetActivateObjectPhysicsAsSoonAsItIsUnfrozen
#define IS_HUD_PREFERENCE_SWITCHED_ON CIVScript::IsHUDPreferenceSwitchedOn
#define ARE_WIDESCREEN_BORDERS_ACTIVE CIVScript::AreWidescreenBordersActive
#define DISPLAY_ALTIMETER_THIS_FRAME __noop
#define SCRIPT_ASSERT CIVScript::ScriptAssert


//
#define NOT !
#define AND &&

class CUnkown
{
public:
	float fX;
	float fY;
	float fZ;
	float fY8;
	
	CVector3 _fU12;
	CVector3 _fU24;
	CVector3 _fU36;

	float _fU4;
	float _fU52;
	float _fU56;
	float _fU60;
	float _fU64;
	float _fU68;
};


extern CUnkown g_U2692[2];

#endif // IVParachuteData_h