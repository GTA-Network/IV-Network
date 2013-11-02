//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVTask.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CIVTask.h"
#include "CIVPed.h"
#include <CCore.h>
#include "CIVPedTaskManager.h"

extern CCore * g_pCore;

struct _IVTask
{
	int iTaskType;
	const char * szTaskName;
};

_IVTask IVTaskNames[] = 
{
	{ TASK_TYPE_NONE, "None" },
	{ TASK_SIMPLE_MOVE_PLAYER, "SimpleMovePlayer" },
	{ TASK_COMPLEX_PLAYER_ON_FOOT, "ComplexPlayerOnFoot" },
	{ TASK_COMPLEX_PLAYER_GUN, "ComplexPlayerGun" },
	{ TASK_COMPLEX_PLAYER_PLACE_CAR_BOMB, "ComplexPlayerPlaceCarBomb" },
	{ TASK_COMPLEX_PLAYER_IDLES, "ComplexPlayerIdles" },
	{ TASK_COMPLEX_MEDIC_TREAT_INJURED_PED, "ComplexMedicTreatInjuredPed" },
	{ TASK_COMPLEX_DRIVE_FIRE_TRUCK, "ComplexDriveFireTruck" },
	{ TASK_COMPLEX_MEDIC_DRIVER, "ComplexMedicDriver" },
	{ TASK_COMPLEX_MEDIC_PASSENGER, "ComplexMedicPassenger" },
	{ TASK_COMPLEX_PLAYER_SETTINGS_TASK, "ComplexPlayerSettingsTask" },
	{ TASK_SIMPLE_STAND_STILL, "SimpleStandStill" },
	{ TASK_SIMPLE_GET_UP, "SimpleGetUp" },
	{ TASK_COMPLEX_GET_UP_AND_STAND_STILL, "ComplexGetUpAndStandStill" },
	{ TASK_SIMPLE_FALL, "SimpleFall" },
	{ TASK_COMPLEX_FALL_AND_GET_UP, "ComplexFallAndGetUp" },
	{ TASK_SIMPLE_JUMP_LAUNCH, "SimpleJumpLaunch" },
	{ TASK_COMPLEX_JUMP, "ComplexJump" },
	{ TASK_COMPLEX_DIE, "ComplexDie" },
	{ TASK_SIMPLE_DEAD, "SimpleDead" },
	{ TASK_SIMPLE_TIRED, "SimpleTired" },
	{ TASK_COMPLEX_SIT_IDLE, "ComplexSitIdle" },
	{ TASK_COMPLEX_SIT_DOWN_THEN_IDLE_THEN_STAND_UP, "ComplexSitDownThenIdleThenStandUp" },
	{ TASK_COMPLEX_HIT_RESPONSE, "ComplexHitResponse" },
	{ TASK_SIMPLE_JUMP_IN_AIR, "SimpleJumpInAir" },
	{ TASK_SIMPLE_JUMP_LAND, "SimpleJumpLand" },
	{ TASK_COMPLEX_SEQUENCE, "ComplexSequence" },
	{ TASK_COMPLEX_ON_FIRE, "ComplexOnFire" },
	{ TASK_SIMPLE_CLIMB, "SimpleClimb" },
	{ TASK_COMPLEX_IN_WATER, "ComplexInWater" },
	{ TASK_SIMPLE_TRIGGER_LOOK_AT, "SimpleTriggerLookAt" },
	{ TASK_COMPLEX_INJURED_ON_GROUND, "ComplexInjuredOnGround" },
	{ TASK_SIMPLE_DO_NOTHING, "SimpleDoNothing" },
	{ TASK_SIMPLE_MOVE_DO_NOTHING, "SimpleMoveDoNothing" },
	{ TASK_COMPLEX_CONTROL_MOVEMENT, "ComplexControlMovement" },
	{ TASK_COMPLEX_MOVE_SEQUENCE, "ComplexMoveSequence" },
	{ TASK_COMPLEX_CLIMB_LADDER, "ComplexClimbLadder" },
	{ TASK_COMPLEX_CLIMB_LADDER_FULLY, "ComplexClimbLadderFully" },
	{ TASK_COMPLEX_MOVE_AROUND_COVER_POINTS, "ComplexMoveAroundCoverPoints" },
	{ TASK_SIMPLE_PLAY_RANDOM_AMBIENTS, "SimplePlayRandomAmbients" },
	{ TASK_SIMPLE_MOVE_IN_AIR, "SimpleMoveInAir" },
	{ TASK_COMPLEX_PICK_UP_OBJECT, "ComplexPickUpObject" },
	{ TASK_COMPLEX_PICK_UP_AND_CARRY_OBJECT, "ComplexPickUpAndCarryObject" },
	{ TASK_SIMPLE_OPEN_DOOR, "SimpleOpenDoor" },
	{ TASK_SIMPLE_SWAP_WEAPON, "SimpleSwapWeapon" },
	{ TASK_COMPLEX_SHOCKING_EVENT_WATCH, "ComplexShockingEventWatch" },
	{ TASK_COMPLEX_SHOCKING_EVENT_FLEE, "ComplexShockingEventFlee" },
	{ TASK_COMPLEX_SHOCKING_EVENT_GOTO, "ComplexShockingEventGoto" },
	{ TASK_COMPLEX_SHOCKING_EVENT_HURRY_AWAY, "ComplexShockingEventHurryAway" },
	{ TASK_SIMPLE_PUT_ON_HELMET, "SimplePutOnHelmet" },
	{ TASK_SIMPLE_TAKE_OFF_HELMET, "SimpleTakeOfHelmet" },
	{ TASK_COMPLEX_CAR_REACT_TO_VEHICLE_COLLISION, "ComplexCarReactToVehicleCollision" },
	{ TASK_COMPLEX_REACT_TO_PED_RAN_OVER, "ComplexReactToPedRanOver" },
	{ TASK_COMPLEX_CAR_REACT_TO_VEHICLE_COLLISION_GET_OUT, "ComplexCarReactToVehicleCollisionGetOut" },
	{ TASK_COMPLEX_STATIONARY_SCENARIO, "ComplexStationaryScenario" },
	{ TASK_COMPLEX_SEATED_SCENARIO, "ComplexSeatedScenario" },
	{ TASK_COMPLEX_DRIVING_SCENARIO, "ComplexDrivingScenario" },
	{ TASK_COMPLEX_DRIVE_WANDER_FOR_TIME, "ComplexDriveWanderForTime" },
	{ TASK_COMPLEX_MOBILE_CHAT_SCENARIO, "ComplexMobileChatScenario" },
	{ TASK_COMPLEX_POLICE_SNIPER_SCENARIO, "ComplexPoliceSniperScenario" },
	{ TASK_COMPLEX_MOBILE_MAKE_CALL, "ComplexMobileMakeCall" },
	{ TASK_COMPLEX_MELEE, "ComplexMelee" },
	{ TASK_SIMPLE_MOVE_MELEE_MOVEMENT, "SimpleMoveMeleeMovement" },
	{ TASK_SIMPLE_MELEE_ACTION_RESULT, "SimpleMeleeActionResult" },
	{ TASK_COMPLEX_MOVE_BETWEEN_POINTS_SCENARIO, "ComplexMoveBetweenPointsScenario" },
	{ TASK_COMPLEX_CHAT_SCENARIO, "ComplexChatScenario" },
	{ TASK_COMPLEX_GET_IN_CAR_SCENARIO, "ComplexGetInCarScenario" },
	{ TASK_COMPLEX_EVASIVE_STEP, "ComplexEvasiveStep" },
	{ TASK_COMPLEX_MOVE_STEP_AWAY_FROM_COLLISION_OBJECTS, "ComplexMoveStepAwayFromCollisionObjects" },
	{ TASK_COMPLEX_WALK_ROUND_ENTITY, "ComplexWalkRoundEntity" },
	{ TASK_COMPLEX_LEAVE_CAR_AND_WANDER, "ComplexLeaveCarAndWander" },
	{ TASK_COMPLEX_INVESTIGATE_DEAD_PED, "ComplexInvestigateDeadPed" },
	{ TASK_COMPLEX_REACT_TO_GUN_AIMED_AT, "ComplexReactToGunAimedAt" },
	{ TASK_COMPLEX_EXTINGUISH_FIRES, "ComplexExtinguishFires" },
	{ TASK_COMPLEX_AVOID_PLAYER_TARGETTING, "ComplexAvoidPlayerTargetting" },
	{ TASK_COMPLEX_STEAL_CAR, "ComplexStealCar" },
	{ TASK_COMPLEX_LEAVE_CAR_AND_FLEE, "ComplexLeaveCarAndFlee" },
	{ TASK_COMPLEX_SCREAM_IN_CAR_THEN_LEAVE, "ComplexScreamInCarThenLeave" },
	{ TASK_COMPLEX_CAR_DRIVE_BASIC, "ComplexCarDriveBasic" },
	{ TASK_COMPLEX_DRIVE_TO_POINT, "ComplexDriveToPoint" },
	{ TASK_COMPLEX_CAR_DRIVE_WANDER, "ComplexCarDriveWander" },
	{ TASK_COMPLEX_LEAVE_ANY_CAR, "ComplexLeaveAnyCar" },
	{ TASK_COMPLEX_GET_OFF_BOAT, "ComplexGetOffBoat" },
	{ TASK_COMPLEX_ENTER_ANY_CAR_AS_DRIVER, "ComplexEnterAnyCarAsDriver" },
	{ TASK_COMPLEX_CAR_DRIVE_TIMED, "ComplexCarDriveTimed" },
	{ TASK_COMPLEX_DRIVE_POINT_ROUTE, "ComplexDrivePointRoute" },
	{ TASK_COMPLEX_CAR_SET_TEMP_ACTION, "ComplexCarSetTempAction" },
	{ TASK_COMPLEX_CAR_DRIVE_MISSION, "ComplexCarDriveMission" },
	{ TASK_COMPLEX_CAR_DRIVE, "ComplexCarDrive" },
	{ TASK_COMPLEX_CAR_DRIVE_MISSION_FLEE_SCENE, "ComplexCarDriveMissionFleeScene" },
	{ TASK_COMPLEX_CAR_DRIVE_MISSION_KILLED_PED, "ComplexCarDriveMissionKilledPed" },
	{ TASK_COMPLEX_PLAYER_DRIVE, "ComplexPlayerDrive" },
	{ TASK_COMPLEX_NEW_GET_IN_VEHICLE, "ComplexNewGetInVehicle" },
	{ TASK_COMPLEX_OPEN_VEHICLE_DOOR, "ComplexOpenVehicleDoor" },
	{ TASK_COMPLEX_CLIMB_INTO_VEHICLE, "ComplexClimbIntoVehicle" },
	{ TASK_COMPLEX_CLEAR_VEHICLE_SEAT, "ComplexClearVehicleSeat" },
	{ TASK_COMPLEX_NEW_EXIT_VEHICLE, "ComplexNewExitVehicle" },
	{ TASK_COMPLEX_SHUFFLE_BETWEEN_SEATS, "ComplexShuffleBetweenSeats" },
	{ TASK_COMPLEX_GANG_DRIVEBY, "ComplexGangDriveby" },
	{ TASK_COMPLEX_CLOSE_VEHICLE_DOOR, "ComplexCloseVehicleDoor" },
	{ TASK_COMPLEX_BACK_OFF, "ComplexBackOff" },
	{ TASK_COMPLEX_BE_ARRESTED_AND_DRIVEN_AWAY, "ComplexBeArrestedAndDrivenAway" },
	{ TASK_COMPLEX_ARRESTED_AI_PED_AND_DRIVE_AWAY, "ComplexArrestedAIPedAndDriveAway" },
	{ TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL, "ComplexGoToCarDoorAndStandStill" },
	{ TASK_SIMPLE_CAR_ALIGN, "SimpleCarAlign" },
	{ TASK_SIMPLE_CAR_OPEN_DOOR_FROM_OUTSIDE, "SimpleCarOpenDoorFromOutside" },
	{ TASK_SIMPLE_CAR_OPEN_LOCKED_DOOR_FROM_OUTSIDE, "SimpleCarOpenLockedDoorFromOutside" },
	{ TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_INSIDE, "SimpleCarCloseDoorFromInside" },
	{ TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_OUTSIDE, "SimpleCarCloseDoorFromOutside" },
	{ TASK_SIMPLE_CAR_GET_IN, "SimpleCarGetIn" },
	{ TASK_SIMPLE_CAR_SHUFFLE, "SimpleCarShuffle" },
	{ TASK_SIMPLE_CAR_SET_PED_IN_VEHICLE, "SimpleCarSetPedInVehicle" },
	{ TASK_SIMPLE_CAR_GET_OUT, "SimpleCarGetOut" },
	{ TASK_SIMPLE_CAR_JUMP_OUT, "SimpleCarJumpOut" },
	{ TASK_SIMPLE_CAR_SET_PED_OUT, "SimpleCarSetPedOut" },
	{ TASK_SIMPLE_CAR_SLOW_DRAG_OUT_PED, "SimpleCarSlowDragOutPed" },
	{ TASK_SIMPLE_CAR_SLOW_BE_DRAGGED_OUT, "SimpleCarSlowBeDraggedOut" },
	{ TASK_SIMPLE_SET_PED_AS_AUTO_DRIVER, "SimpleSetPedAsAutoDriver" },
	{ TASK_SIMPLE_WAIT_UNTIL_PED_IS_OUT_OF_CAR, "SimpleWaitUntilPedIsOutOfCar" },
	{ TASK_SIMPLE_CREATE_CAR_AND_GET_IN, "SimpleCreateCarAndGetIn" },
	{ TASK_SIMPLE_START_CAR, "SimpleStartCar" },
	{ TASK_SIMPLE_SHUNT, "SimpleShunt" },
	{ TASK_SIMPLE_SMASH_CAR_WINDOW, "SimpleSmashCarWindow" },
	{ TASK_SIMPLE_MOVE_GO_TO_POINT, "SimpleMoveGoToPoint" },
	{ TASK_COMPLEX_GO_TO_POINT_SHOOTING, "ComplexGoToPointShooting" },
	{ TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL, "ComplexGoToPointAndStandStill" },
	{ TASK_COMPLEX_MOVE_FOLLOW_POINT_ROUTE, "ComplexMoveFollowPointRoute" },
	{ TASK_COMPLEX_MOVE_SEEK_ENTITY, "ComplexMoveSeekEntity" },
	{ TASK_COMPLEX_SMART_FLEE_POINT, "ComplexSmartFleePoint" },
	{ TASK_COMPLEX_SMART_FLEE_ENTITY, "ComplexSmartFleeEntity" },
	{ TASK_COMPLEX_FOLLOW_LEADER_IN_FORMATION, "ComplexFollowLeaderInFormation" },
	{ TASK_COMPLEX_GO_TO_ATTRACTOR, "ComplexGoToAttractor" },
	{ TASK_COMPLEX_MOVE_AVOID_OTHER_PED_WHILE_WONDERING, "ComplexMoveAvoidOtherPedWhileWondering" },
	{ TASK_COMPLEX_GO_TO_POINT_ANY_MEANS, "ComplexGoToPointAnyMeans" },
	{ TASK_COMPLEX_SEEK_ENTITY_ANY_MEANS, "ComplexSeekEntityAnyMeans" },
	{ TASK_COMPLEX_FOLLOW_LEADER_ANY_MEANS, "ComplexFollowLeaderAnyMeans" },
	{ TASK_COMPLEX_GO_TO_POINT_AIMING, "ComplexGoToPointAiming" },
	{ TASK_COMPLEX_FLEE_ANY_MEANS, "ComplexFleeAnyMeans" },
	{ TASK_COMPLEX_FLEE_SHOOTING, "ComplexFleeShooting" },
	{ TASK_COMPLEX_FOLLOW_PATROL_ROUTE, "ComplexFollowPatrolRoute" },
	{ TASK_COMPLEX_SEEK_ENTITY_AIMING, "ComplexSeekEntityAiming" },
	{ TASK_COMPLEX_FOLLOW_PED_FOOTSTEPS, "ComplexFollowPedFootsteps" },
	{ TASK_COMPLEX_MOVE_FOLLOW_NAV_MESH_ROUTE, "ComplexMoveFollowNavMeshRoute" },
	{ TASK_SIMPLE_MOVE_GO_TO_POINT_ON_ROUTE, "SimpleMoveGoToPointOnRoute" },
	{ TASK_COMPLEX_ESCAPE_BLAST, "ComplexEscapeBlast" },
	{ TASK_COMPLEX_MOVE_GET_TO_POINT_CONTINUOUS, "ComplexMoveGetToPointContinuous" },
	{ TASK_COMPLEX_COP, "ComplexCop" },
	{ TASK_COMPLEX_SEARCH_FOR_PED_ON_FOOT, "ComplexSearchForPedOnFoot" },
	{ TASK_COMPLEX_SEARCH_FOR_PED_IN_CAR, "ComplexSearchForPedInCar" },
	{ TASK_COMPLEX_MOVE_WANDER, "ComplexMoveWander" },
	{ TASK_COMPLEX_MOVE_BE_IN_FORMATION, "ComplexMoveBeInFormation" },
	{ TASK_COMPLEX_MOVE_CROWD_AROUND_LOCATION, "ComplexMoveCrowdAroundLocation" },
	{ TASK_COMPLEX_MOVE_CROSS_ROAD_AT_TRAFFIC_LIGHTS, "ComplexMoveCrossRoadAtTrafficLights" },
	{ TASK_COMPLEX_MOVE_WAIT_FOR_TRAFFIC, "ComplexMoveWaitForTraffic" },
	{ TASK_COMPLEX_MOVE_GO_TO_POINT_STAND_STILL_ACHIVE_HEADING, "ComplexMoveGoToPointStandStillAchiveHeading" },
	{ TASK_COMPLEX_MOVE_RETURN_TO_ROUTE, "ComplexMoveReturnToRoute" },
	{ TASK_COMPLEX_MOVE_GO_TO_SHELTER_AND_WAIT, "ComplexMoveGoToShelterAndWait" },
	{ TASK_COMPLEX_MOVE_GET_ON_TO_MAIN_NAV_MESH, "ComplexMoveGetOnToMainNavMesh" },
	{ TASK_COMPLEX_MOVE_GO_TO_POINT_RELATIVE_TO_ENTITY_AND_STAND_STILL, "ComplexMoveGoToPointRelativeToEntityAndStandStill" },
	{ TASK_COMPLEX_COP_HELICOPTOR, "ComplexCopHelicoptor" },
	{ TASK_COMPLEX_HELICOPTOR_STRAFE, "ComplexHelicoptorStrafe" },
	{ TASK_COMPLEX_FLEE_AND_DRIVE, "ComplexFleeAndDrive" },
	{ TASK_COMPLEX_GET_OUT_OF_WATER, "ComplexGetOutOfWater" },
	{ TASK_COMPLEX_DESTROY_CAR, "ComplexDestroyCar" },
	{ TASK_COMPLEX_DESTROY_CAR_ARMED, "ComplexDestroyCarArmed" },
	{ TASK_SIMPLE_THROW_PROJECTILE, "SimpleThrowProjectile" },
	{ TASK_COMPLEX_SEEK_COVER, "ComplexSeekCover" },
	{ TASK_COMPLEX_AIM_AND_THROW_PROJECTILE, "ComplexAimAndThrowProjectile" },
	{ TASK_SIMPLE_PLAYER_AIM_PROJECTILE, "SimplePlayerAimProjectile" },
	{ TASK_COMPLEX_GUN, "ComplexGun" },
	{ TASK_SIMPLE_AIM_GUN, "SimpleAimGun" },
	{ TASK_SIMPLE_FIRE_GUN, "SimpleFireGun" },
	{ TASK_SIMPLE_RELOAD_GUN, "SimpleReloadGun" },
	{ TASK_COMPLEX_SLIDE_INTO_COVER, "ComplexSlideIntoCover" },
	{ TASK_COMPLEX_PLAYER_IN_COVER, "ComplexPlayerInCover" },
	{ TASK_COMPLEX_GO_INTO_COVER, "ComplexGoIntoCover" },
	{ TASK_COMPLEX_COMBAT_CLOSEST_TARGET_IN_AREA, "ComplexCombatClosestTargetInArea" },
	{ TASK_SIMPLE_NEW_GANG_DRIVE_BY, "SimpleNewGangDriveBy" },
	{ TASK_COMPLEX_COMBAT_ADDITIONAL_TASK, "ComplexCombatAdditionalTask" },
	{ TASK_COMPLEX_NEW_USE_COVER, "ComplexNewUseCover" },
	{ TASK_COMPLEX_THROW_PROJECTILE, "ComplexThrowProjectile" },
	{ TASK_COMPLEX_ARREST_PED, "ComplexArrestPed" },
	{ TASK_COMPLEX_GANG_HASSLE_PED, "ComplexGangHasslePed" },
	{ TASK_SIMPLE_MOVE_SWIM, "SimpleMoveSwim" },
	{ TASK_COMPLEX_MOVE_ABOUT_INJURED, "ComplexMoveAboutInjured" },
	{ TASK_COMPLEX_REVIVE, "ComplexRevive" },
	{ TASK_COMPLEX_COMBAT, "ComplexCombat" },
	{ TASK_COMPLEX_COMBAT_FIRE_SUBTASK, "ComplexCombatFireSubtask" },
	{ TASK_COMPLEX_COMBAT_ADVANCE_SUBTASK, "ComplexCombatAdvanceSubtask" },
	{ TASK_COMPLEX_COMBAT_SEEK_COVER_SUBTASK, "ComplexCombatSeekCoverSubtask" },
	{ TASK_COMPLEX_COMBAT_RETREAT_SUBTASK, "ComplexCombatRetreatSubtask" },
	{ TASK_COMPLEX_COMBAT_CHARGE_SUBTASK, "ComplexCombatChargeSubtask" },
	{ TASK_COMPLEX_COMBAT_INVESTIGATE_SUBTASK, "ComplexCombatInvestigateSubtask" },
	{ TASK_COMPLEX_COMBAT_PULL_FROM_CAR_SUBTASK, "ComplexCombatPullFromCarSubtask" },
	{ TASK_COMPLEX_COMBAT_PERSUE_IN_CAR_SUBTASK, "ComplexCombatPersueInCarSubtask" },
	{ TASK_COMPLEX_COMBAT_BUST_PED, "ComplexCombatBustPed" },
	{ TASK_COMPLEX_COMBAT_EXECUTE_PED_SUBTASK, "ComplexCombatExecutePedSubtask" },
	{ TASK_COMPLEX_COMBAT_FLANK_SUBTASK, "ComplexCombatFlankSubtask" },
	{ TASK_COMPLEX_SET_AND_GUARD_AREA, "ComplexSetAndGuardArea" },
	{ TASK_COMPLEX_STAND_GUARD, "ComplexStandGuard" },
	{ TASK_COMPLEX_SEPERATE, "ComplexSeperate" },
	{ TASK_COMPLEX_REACT, "ComplexReact" },
	{ TASK_SIMPLE_NM_RELAX, "SimpleNMRelax" },
	{ TASK_SIMPLE_NM_POSE, "SimpleNMPose" },
	{ TASK_SIMPLE_NM_BRACE, "SimpleNMBrace" },
	{ TASK_SIMPLE_NM_SHOT, "SimpleNMShot" },
	{ TASK_SIMPLE_NM_HIGH_FALL, "SimpleNMHighFall" },
	{ TASK_SIMPLE_NM_BALANCE, "SimpleNMBalance" },
	{ TASK_SIMPLE_NM_EXPLOSION, "SimpleNMExplosion" },
	{ TASK_SIMPLE_NM_ON_FIRE, "SimpleNMOnFire" },
	{ TASK_SIMPLE_NM_SCRIPT_CONTROL, "SimpleNMScriptControl" },
	{ TASK_SIMPLE_NM_JUMP_ROLL_FROM_ROAD_VEHICLE, "SimpleNMJumpRollFromRoadVehicle" },
	{ TASK_SIMPLE_NM_SIT, "SimpleNMSit" },
	{ TASK_SIMPLE_BLEND_FROM_NM, "SimpleBlendFromNM" },
	{ TASK_COMPLEX_NM, "ComplexNM" }
};

const char * GetTaskName(int iTaskType)
{
	for(int i = 0; i < ARRAY_LENGTH(IVTaskNames); i++)
	{
		if(IVTaskNames[i].iTaskType == iTaskType)
			return IVTaskNames[i].szTaskName;
	}

	return "Unknown Task";
}

CIVTask::CIVTask()
: m_pTask(NULL)
{
}

CIVTask::CIVTask(IVTask * pTask)
: m_pTask(pTask)
{
}

CIVTask::~CIVTask()
{
}

void CIVTask::SetTask(IVTask * pTask)
{
	m_pTask = pTask;
}

IVTask * CIVTask::GetTask()
{
	return m_pTask;
}

void CIVTask::Create()
{
	if(!m_pTask)
	{
		// Allocate the task
		m_pTask = g_pCore->GetGame()->GetPools()->GetTaskPool()->Allocate();

		// Add ourself to the client task manager
		g_pCore->GetGame()->GetTaskManager()->AddTask(this);
	}
}

void CIVTask::Destroy()
{
	if (m_pTask)
	{
		IVTask * pTask = m_pTask;
		DWORD dwFunc = *((int**) m_pTask)[0];
		_asm
		{
			push 1
			mov ecx, pTask
			call dwFunc
		}
	}
}

CIVTask * CIVTask::GetParent()
{
	if (m_pTask)
		return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pTask->m_pParent);

	return NULL;
}

CIVTask * CIVTask::Clone()
{
	if(m_pTask)
		return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pTask->Clone());

	return NULL;
}

bool CIVTask::IsSimple()
{
	// now we can do it like this
	if (m_pTask)
		return m_pTask->IsSimple();
	else
		return true;
}

int CIVTask::GetType()
{
	if(m_pTask)
		return m_pTask->GetType();

	return TASK_TYPE_NONE;
}


const char * CIVTask::GetName()
{
	return GetTaskName(GetType());
}

bool CIVTask::MakeAbortable(CIVPed * pPed, int iAbortPriority, CIVEvent * pEvent)
{
	if(m_pTask)
		return m_pTask->MakeAbortable(pPed->GetPed(), iAbortPriority, pEvent->GetEvent());

	return false;
}

void CIVTask::SetAsPedTask(CIVPed * pPed, int iTaskPriority, bool bForceNewTask)
{
	if(m_pTask)
	{
		// Get the game task pointer
		CIVTask * pClientTask = g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pTask);

		// Set the task as the ped task
		pPed->GetPedTaskManager()->SetTask(pClientTask, iTaskPriority, bForceNewTask);
	}
}

void CIVTask::SetAsPedTaskSecondary(CIVPed * pPed, int iTaskPriority)
{
	if(m_pTask)
	{
		// Get the game task pointer
		CIVTask * pClientTask = g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(m_pTask);

		// Set the task as the ped task
		pPed->GetPedTaskManager()->SetTaskSecondary(pClientTask, iTaskPriority);
	}
}

bool CIVTaskSimple::ProcessPed(CIVPed * pPed)
{
	IVTaskSimple * pTask = (IVTaskSimple *)GetTask();

	if (pTask)
		pTask->ProcessPed(pPed->GetPed());

	return false;
}

CIVTask * CIVTaskComplex::GetSubTask()
{
	IVTaskComplex * pTask = (IVTaskComplex *)GetTask();

	if(pTask)
		return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(pTask->m_pSubTask);

	return NULL;
}

void CIVTaskComplex::SetSubTask(CIVTask * pSubTask)
{
	IVTaskComplex * pTask = (IVTaskComplex *)GetTask();

	if(pTask)
		pTask->SetSubTask(pSubTask->GetTask());
}

CIVTask * CIVTaskComplex::CreateNextSubTask(CIVPed * pPed)
{
	IVTaskComplex * pTask = (IVTaskComplex *)GetTask();

	if(pTask)
		return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(pTask->CreateNextSubTask(pPed->GetPed()));

	return NULL;
}

CIVTask * CIVTaskComplex::CreateFirstSubTask(CIVPed * pPed)
{
	IVTaskComplex * pTask = (IVTaskComplex *)GetTask();

	if(pTask)
		return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(pTask->CreateFirstSubTask(pPed->GetPed()));

	return NULL;
}

CIVTask * CIVTaskComplex::ControlSubTask(CIVPed * pPed)
{
	IVTaskComplex * pTask = (IVTaskComplex *)GetTask();

	if(pTask)
		return g_pCore->GetGame()->GetTaskManager()->GetClientTaskFromGameTask(pTask->ControlSubTask(pPed->GetPed()));

	return NULL;
}