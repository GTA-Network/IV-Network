//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: eGame.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef eGame_h
#define eGame_h

enum eGAMEStates
{
	GAME_STATE_NONE,
	GAME_STATE_MAIN_MENU,
	GAME_STATE_LOADING,
	GAME_STATE_INGAME,
	GAME_STATE_PAUSE_MENU,
	GAME_STATE_IVMP_PAUSE_MENU,
};

enum eWeather
{
	WEATHER_EXTRA_SUNNY,
	WEATHER_SUNNY,
	WEATHER_SUNNY_WINDY,
	WEATHER_CLOUDY,
	WEATHER_RAINING,
	WEATHER_DRIZZLE,
	WEATHER_FOGGY,
	WEATHER_LIGHTNING,
	WEATHER_EXTRA_SUNNY_2,
	WEATHER_SUNNY_WINDY_2
};

enum eAbortPriority
{
	ABORT_PRIORITY_LEISURE = 0,
	ABORT_PRIORITY_URGENT,
	ABORT_PRIORITY_IMMEDIATE
};

enum eTaskPriority
{
	TASK_PRIORITY_PHYSICAL_RESPONSE,
	TASK_PRIORITY_EVENT_RESPONSE_TEMP,
	TASK_PRIORITY_EVENT_RESPONSE_NONTEMP,
	TASK_PRIORITY_PRIMARY,
	TASK_PRIORITY_DEFAULT,
	TASK_PRIORITY_MAX
};

enum eTaskSecondary
{
	TASK_SECONDARY_ATTACK,
	TASK_SECONDARY_DUCK,
	TASK_SECONDARY_SAY,
	TASK_SECONDARY_FACIAL_COMPLEX,
	TASK_SECONDARY_PARTIAL_ANIM,
	TASK_SECONDARY_IK,
	TASK_SECONDARY_MAX
};

enum eTaskMovement
{
	TASK_MOVEMENT_UNKNOWN0,
	TASK_MOVEMENT_UNKNOWN1,
	TASK_MOVEMENT_UNKNOWN2,
	TASK_MOVEMENT_MAX
};

enum eModelType
{
	MODEL_TYPE_BASE = 1,
	MODEL_TYPE_MLO,
	MODEL_TYPE_TIME,
	MODEL_TYPE_WEAPON,
	MODEL_TYPE_VEHICLE,
	MODEL_TYPE_PED
};

// Controller stuff
enum eInput
{
	INPUT_NEXT_CAMERA,                      // 
	INPUT_SPRINT,                           // On Foot - Sprint
	INPUT_JUMP,                             // On Foot - Jump
	INPUT_ENTER,                            // 
	INPUT_ATTACK,                           // On Foot - Attack
	INPUT_ATTACK2,                          // On Foot - Lock On 1
	INPUT_AIM,                              // On Foot - Lock On 2
	INPUT_LOOK_BEHIND,                      // General - Look Behind
	INPUT_NEXT_WEAPON,                      // On Foot - Next Weapon
	INPUT_PREV_WEAPON,                      // On Foot - Previous Weapon
	INPUT_NEXT_TARGET_LEFT,                 // 
	INPUT_NEXT_TARGET_RIGHT,                // 
	INPUT_MOVE_LEFT,                        // On Foot - Move Left
	INPUT_MOVE_RIGHT,                       // On Foot - Move Right
	INPUT_MOVE_UP,                          // On Foot - Move Forward
	INPUT_MOVE_DOWN,                        // On Foot - Move Backwards
	INPUT_LOOK_LEFT,                        // 
	INPUT_LOOK_RIGHT,                       // 
	INPUT_LOOK_UP,                          // 
	INPUT_LOOK_DOWN,                        // 
	INPUT_DUCK,                             // On Foot - Crouch
	INPUT_PHONE_TAKE_OUT,                   // On Foot - Take Phone Out
	INPUT_PHONE_PUT_AWAY,                   // 
	INPUT_PICKUP,                           // On Foot - Action
	INPUT_SNIPER_ZOOM_IN,                   // On Foot - Sniper Zoom In
	INPUT_SNIPER_ZOOM_OUT,                  // On Foot - Sniper Zoom Out
	INPUT_SNIPER_ZOOM_IN_ALTERNATE,         // 
	INPUT_SNIPER_ZOOM_OUT_ALTERNATE,        // 
	INPUT_COVER,                            // 
	INPUT_RELOAD,                           // On Foot - Reload
	INPUT_VEH_MOVE_LEFT,                    // In Vehicle - Steer Left
	INPUT_VEH_MOVE_RIGHT,                   // In Vehicle - Steer Right
	INPUT_VEH_MOVE_UP,                      // In Vehicle - Lean Forward
	INPUT_VEH_MOVE_DOWN,                    // In Vehicle - Lean Back
	INPUT_VEH_GUN_LEFT,                     // 
	INPUT_VEH_GUN_RIGHT,                    // 
	INPUT_VEH_GUN_UP,                       // 
	INPUT_VEH_GUN_DOWN,                     // 
	INPUT_VEH_ATTACK,                       // In Vehicle - Drive By
	INPUT_VEH_ATTACK2,                      // In Vehicle - Helicoptor Primary Fire
	INPUT_VEH_ACCELERATE,                   // In Vehicle - Accelerate
	INPUT_VEH_BRAKE,                        // In Vehicle - Reverse
	INPUT_VEH_HEADLIGHT,                    // In Vehicle - Headlight
	INPUT_VEH_EXIT,                         // 
	INPUT_VEH_HANDBRAKE,                    // In Vehicle - Handbrake 1
	INPUT_VEH_HANDBRAKE_ALT,                // In Vehicle - Handbrake 2
	INPUT_VEH_HOTWIRE_LEFT,                 // In Vehicle - Hotwire 1
	INPUT_VEH_HOTWIRE_RIGHT,                // In Vehicle - Hotwire 2
	INPUT_VEH_LOOK_LEFT,                    // 
	INPUT_VEH_LOOK_RIGHT,                   // 
	INPUT_VEH_LOOK_BEHIND,                  // In Vehicle - Look Behind
	INPUT_VEH_CIN_CAM,                      // In Vehicle - Cinematic Camera
	INPUT_VEH_NEXT_RADIO,                   // 
	INPUT_VEH_PREV_RADIO,                   // 
	INPUT_VEH_HORN,                         // In Vehicle - Horn
	INPUT_VEH_FLY_THROTTLE_UP,              // Helicoptor - Throttle Up
	INPUT_VEH_FLY_THROTTLE_DOWN,            // Helicoptor - Throttle Down
	INPUT_VEH_FLY_YAW_LEFT,                 // Helicoptor - Rotate Left
	INPUT_VEH_FLY_YAW_RIGHT,                // Helicoptor - Rotate Right
	INPUT_MELEE_ATTACK1,                    // On Foot - Combat Punch 1
	INPUT_MELEE_ATTACK2,                    // On Foot - Combat Punch 2
	INPUT_MELEE_ATTACK3,                    // 
	INPUT_MELEE_KICK,                       // On Foot - Combat Kick
	INPUT_MELEE_BLOCK,                      // On Foot - Combat Block
	INPUT_FRONTEND_DOWN,                    // 
	INPUT_FRONTEND_UP,                      // 
	INPUT_FRONTEND_LEFT,                    // 
	INPUT_FRONTEND_RIGHT,                   // 
	INPUT_FRONTEND_RDOWN,                   // 
	INPUT_FRONTEND_RUP,                     // 
	INPUT_FRONTEND_RLEFT,                   // 
	INPUT_FRONTEND_RRIGHT,                  // 
	INPUT_FRONTEND_AXIS_X,                  // 
	INPUT_FRONTEND_AXIS_Y,                  // 
	INPUT_FRONTEND_RIGHT_AXIS_X,            // 
	INPUT_FRONTEND_RIGHT_AXIS_Y,            // 
	INPUT_FRONTEND_PAUSE,                   // 
	INPUT_FRONTEND_ACCEPT,                  // 
	INPUT_FRONTEND_CANCEL,                  // 
	INPUT_FRONTEND_X,                       // 
	INPUT_FRONTEND_Y,                       // 
	INPUT_FRONTEND_LB,                      // 
	INPUT_FRONTEND_RB,                      // 
	INPUT_FRONTEND_LT,                      // Page Down
	INPUT_FRONTEND_RT,                      // Page Up
	INPUT_MELEE_ATTACK4,                    // 
	INPUT_ZOOM_RADAR,                       // General - Radar Zoom
	INPUT_FREE_AIM,                         // On Foot - Lock On 3
	INPUT_MOUSE_UD,                         // 
	INPUT_MOUSE_LR,                         // 
	INPUT_MOVE_KEY_FB,                      // 
	INPUT_MOVE_KEY_LR,                      // 
	INPUT_MOVE_KEY_STUNTJUMP,               // 
	INPUT_MOUSE_WHEEL_UP,                   // 
	INPUT_MOUSE_WHEEL_DOWN,                 // 
	INPUT_FRONTEND_AXIS_UD,                 // 
	INPUT_FRONTEND_AXIS_LR,                 // 
	INPUT_FRONTEND_LEGEND,                  // 
	INPUT_FRONTEND_APPLY,                   // 
	INPUT_FRONTEND_SHOWSCORE,               // 
	INPUT_WEAPON_UNARMED,                   // Weapons - Unarmed
	INPUT_WEAPON_MELEE,                     // Weapons - Melee
	INPUT_WEAPON_HANDGUN,                   // Weapons - Handgun
	INPUT_WEAPON_SHOTGUN,                   // Weapon - Shotgun
	INPUT_WEAPON_SMG,                       // Weapons - Sub Machine Gun
	INPUT_WEAPON_RIFLE,                     // Weapons - Automatic Rifle
	INPUT_WEAPON_SNIPER,                    // Weapons - Sniper Rifle
	INPUT_WEAPON_HEAVY,                     // Weapons - Heavy Weapon
	INPUT_WEAPON_THROWN,                    // Weapons - Grenade/Molotov
	INPUT_WEAPON_SPECIAL,                   // Weapons - Special
	INPUT_VEH_KEY_UD,                       // 
	INPUT_VEH_KEY_LR,                       // 
	INPUT_VEH_NEXT_WEAPON,                  // In Vehicle - Next Weapon
	INPUT_VEH_PREV_WEAPON,                  // In Vehicle - Previous Weapon
	INPUT_TURN_OFF_RADIO,                   // In Vehicle - Turn Off Radio
	INPUT_FRONTEND_MINIGAME_1,              // 
	INPUT_FRONTEND_MINIGAME_2,              // 
	INPUT_FRONTEND_MINIGAME_3,              // 
	INPUT_FRONTEND_MINIGAME_4,              // 
	INPUT_FRONTEND_MODEL_SCREEN,            // 
	INPUT_FRONTEND_VEHICLE_TOGGLE,          // 
	INPUT_FRONTEND_DELETE_FILTER,           // 
	INPUT_FRONTEND_REFRESH,                 // 
	INPUT_FRONTEND_PLAYER_LIST,             // 
	INPUT_TEXT_CHAT_TOGGLE,                 // 
	INPUT_TEXT_CHAT_TEAM,                   // General - Team Chat Team
	INPUT_TEXT_CHAT_UNIVERSAL,              // General - Team Chat All
	INPUT_TEXT_CHAT_RESULTS_TOGGLE,         // 
	INPUT_TEXT_CHAT_Y,                      // 
	INPUT_FRONTEND_LOCK_LOBBY,              // 
	INPUT_KB_UP,                            // General - Phone Up
	INPUT_KB_DOWN,                          // General - Phone Down
	INPUT_KB_LEFT,                          // General - Phone Left
	INPUT_KB_RIGHT,                         // General - Phone Right
	INPUT_NEXT_TRACK,                       // In Vehicle - Next Song
	INPUT_PREV_TRACK,                       // In Vehicle - Previous Song
	INPUT_DROP_WEAPON,                      // In Vehicle - Drop Weapon
	INPUT_MOUSE_LMB,                        // 
	INPUT_MOUSE_RMB,                        // 
	INPUT_FE_MOUSE_UD,                      // 
	INPUT_FE_MOUSE_LR,                      // 
	INPUT_VEH_FLY_PITCH_UP,                 // Helicopter - Pitch Forward
	INPUT_VEH_FLY_PITCH_DOWN,               // Helicopter - Pitch Back
	INPUT_VEH_FLY_ROLL_LEFT,                // Helicopter - Bank Left
	INPUT_VEH_FLY_ROLL_RIGHT,               // Helicopter - Bank Right
	INPUT_REPLAY_PLAY,                      // F1
	INPUT_REPLAY_SAVE_TO_HDD,               // F2
	INPUT_REPLAY_LOAD_FROM_HDD,             // F3
	INPUT_REPLAY_EXIT,                      // 
	INPUT_FRONTEND_MARKER_DELETE,           // 
	INPUT_FRONTEND_REPLAY_PAUSE,            // 
	INPUT_FRONTEND_REPLAY_REWIND,           // 
	INPUT_FRONTEND_REPLAY_FFWD,             // 
	INPUT_FRONTEND_REPLAY_NEWMARKER,        // 
	INPUT_FRONTEND_REPLAY_RECORD,           // 
	INPUT_FRONTEND_REPLAY_SCREENSHOT,       // 
	INPUT_FRONTEND_REPLAY_HIDEHUD,          // H
	INPUT_FRONTEND_REPLAY_STARTPOINT,       // [
	INPUT_FRONTEND_REPLAY_ENDPOINT,         // ]
	INPUT_FRONTEND_REPLAY_ADVANCE,          // 
	INPUT_FRONTEND_REPLAY_BACK,             // 
	INPUT_FRONTEND_REPLAY_SHOWHOTKEY,       // 
	INPUT_FRONTEND_REPLAY_TOOLS,            // 
	INPUT_FRONTEND_REPLAY_RESTART,          // K
	INPUT_FRONTEND_REPLAY_CYCLEMARKERLEFT,  // ,
	INPUT_FRONTEND_REPLAY_CYCLEMARKERRIGHT, // .
	INPUT_FRONTEND_AXIS_FWD,                // 
	INPUT_FRONTEND_AXIS_BACK,               // 
	INPUT_FRONTEND_AXIS_LEFT,               // 
	INPUT_FRONTEND_AXIS_RIGHT,              // 
	INPUT_FRONTEND_DEFINITION,              // General - Toggle Definition
	INPUT_FRONTEND_F6,                      // 
	INPUT_FE_REPLAY_TOGGLETIME,             // 
	INPUT_FE_REPLAY_TOGGLETIPS,             // 
	INPUT_FE_REPLAY_PREVIEW,                // 
	INPUT_FRONTEND_PASTE,                   // 
	INPUT_FRONTEND_CUT,                     // 
	INPUT_FRONTEND_COPY,                    // 
	INPUT_VOICE_CHAT,                       // 
	INPUT_SNIPER_ZOOM_IN_KB,                // On Foot - Sniper Zoom In Alt
	INPUT_SNIPER_ZOOM_OUT_KB,               // On Foot - Sniper Zoom Out Alt
	INPUT_KB_PHONE_ACCEPT,                  // General - Phone Accept
	INPUT_KB_PHONE_CANCEL,                  // General - Phone Cancel
	INPUT_VEH_ATTACK3_KB,                   // Helicopter - Shoot Secondary
	INPUT_DETONATE,                         // On Foot - Detonate
	INPUT_VEH_MOVE_LEFT_2,                  // 
	INPUT_VEH_MOVE_RIGHT_2,                 // 
	INPUT_COUNT
};

#define TASK_TYPE_NONE 9999
#define TASK_SIMPLE_MOVE_PLAYER 2
#define TASK_COMPLEX_PLAYER_ON_FOOT 4
#define TASK_COMPLEX_PLAYER_GUN 6
#define TASK_COMPLEX_PLAYER_PLACE_CAR_BOMB 7
#define TASK_COMPLEX_PLAYER_IDLES 8
#define TASK_COMPLEX_MEDIC_TREAT_INJURED_PED 100
#define TASK_COMPLEX_DRIVE_FIRE_TRUCK 107
#define TASK_COMPLEX_MEDIC_DRIVER 112
#define TASK_COMPLEX_MEDIC_PASSENGER 113
#define TASK_COMPLEX_MEDIC_WANDERING 113
#define TASK_COMPLEX_PLAYER_SETTINGS_TASK 115
#define TASK_SIMPLE_STAND_STILL 203
#define TASK_SIMPLE_GET_UP 205
#define TASK_COMPLEX_GET_UP_AND_STAND_STILL 206
#define TASK_SIMPLE_FALL 207
#define TASK_COMPLEX_FALL_AND_GET_UP 208
#define TASK_SIMPLE_JUMP_LAUNCH 210
#define TASK_COMPLEX_JUMP 211
#define TASK_COMPLEX_DIE 217
#define TASK_SIMPLE_DEAD 218
#define TASK_SIMPLE_TIRED 219
#define TASK_COMPLEX_SIT_IDLE 221
#define TASK_COMPLEX_SIT_DOWN_THEN_IDLE_THEN_STAND_UP 223
#define TASK_COMPLEX_HIT_RESPONSE 230
#define TASK_SIMPLE_JUMP_IN_AIR 241
#define TASK_SIMPLE_JUMP_LAND 242
#define TASK_COMPLEX_SEQUENCE 244
#define TASK_COMPLEX_ON_FIRE 250
#define TASK_SIMPLE_CLIMB 254
#define TASK_COMPLEX_IN_WATER 268
#define TASK_COMPLEX_INJURED_ON_GROUND 278
#define TASK_SIMPLE_DO_NOTHING 281
#define TASK_SIMPLE_MOVE_DO_NOTHING 283
#define TASK_COMPLEX_CONTROL_MOVEMENT 285
#define TASK_COMPLEX_MOVE_SEQUENCE 286
#define TASK_COMPLEX_CLIMB_LADDER 287
#define TASK_COMPLEX_CLIMB_LADDER_FULLY 289
#define TASK_COMPLEX_MOVE_AROUND_COVER_POINTS 290
#define TASK_SIMPLE_PLAY_RANDOM_AMBIENTS 291
#define TASK_SIMPLE_MOVE_IN_AIR 293
#define TASK_COMPLEX_PICK_UP_OBJECT 314
#define TASK_COMPLEX_PICK_UP_AND_CARRY_OBJECT 315
#define TASK_SIMPLE_OPEN_DOOR 317
#define TASK_SIMPLE_SWAP_WEAPON 319
#define TASK_COMPLEX_SHOCKING_EVENT_WATCH 321
#define TASK_COMPLEX_SHOCKING_EVENT_FLEE 322
#define TASK_COMPLEX_SHOCKING_EVENT_GOTO 323
#define TASK_COMPLEX_SHOCKING_EVENT_HURRY_AWAY 324
#define TASK_SIMPLE_PUT_ON_HELMET 325
#define TASK_SIMPLE_TAKE_OFF_HELMET 326
#define TASK_COMPLEX_CAR_REACT_TO_VEHICLE_COLLISION 327
#define TASK_COMPLEX_REACT_TO_PED_RAN_OVER 328
#define TASK_COMPLEX_CAR_REACT_TO_VEHICLE_COLLISION_GET_OUT 329
#define TASK_COMPLEX_STATIONARY_SCENARIO 350
#define TASK_COMPLEX_SEATED_SCENARIO 351
#define TASK_COMPLEX_DRIVING_SCENARIO 353
#define TASK_COMPLEX_DRIVE_WANDER_FOR_TIME 359
#define TASK_COMPLEX_MOBILE_CHAT_SCENARIO 363
#define TASK_COMPLEX_POLICE_SNIPER_SCENARIO 365
#define TASK_COMPLEX_MOBILE_MAKE_CALL 366
#define TASK_COMPLEX_MELEE 431
#define TASK_SIMPLE_MOVE_MELEE_MOVEMENT 432
#define TASK_SIMPLE_MELEE_ACTION_RESULT 433
#define TASK_COMPLEX_MOVE_BETWEEN_POINTS_SCENARIO 354
#define TASK_COMPLEX_CHAT_SCENARIO 355
#define TASK_COMPLEX_GET_IN_CAR_SCENARIO 361
#define TASK_COMPLEX_EVASIVE_STEP 502
#define TASK_COMPLEX_MOVE_STEP_AWAY_FROM_COLLISION_OBJECTS 516
#define TASK_COMPLEX_WALK_ROUND_ENTITY 517
#define TASK_COMPLEX_LEAVE_CAR_AND_WANDER 572
#define TASK_COMPLEX_INVESTIGATE_DEAD_PED 600
#define TASK_COMPLEX_REACT_TO_GUN_AIMED_AT 601
#define TASK_COMPLEX_EXTINGUISH_FIRES 604
#define TASK_COMPLEX_AVOID_PLAYER_TARGETTING 605
#define TASK_COMPLEX_STEAL_CAR 702
#define TASK_COMPLEX_LEAVE_CAR_AND_FLEE 706
#define TASK_COMPLEX_SCREAM_IN_CAR_THEN_LEAVE 708
#define TASK_COMPLEX_CAR_DRIVE_BASIC 709
#define TASK_COMPLEX_DRIVE_TO_POINT 710
#define TASK_COMPLEX_CAR_DRIVE_WANDER 711
#define TASK_COMPLEX_LEAVE_ANY_CAR 714
#define TASK_COMPLEX_GET_OFF_BOAT 716
#define TASK_COMPLEX_ENTER_ANY_CAR_AS_DRIVER 717
#define TASK_COMPLEX_CAR_DRIVE_TIMED 719
#define TASK_COMPLEX_DRIVE_POINT_ROUTE 721
#define TASK_COMPLEX_CAR_SET_TEMP_ACTION 723
#define TASK_COMPLEX_CAR_DRIVE_MISSION 724
#define TASK_COMPLEX_CAR_DRIVE 725
#define TASK_COMPLEX_CAR_DRIVE_MISSION_FLEE_SCENE 726
#define TASK_COMPLEX_CAR_DRIVE_MISSION_KILLED_PED 729
#define TASK_COMPLEX_PLAYER_DRIVE 732
#define TASK_COMPLEX_NEW_GET_IN_VEHICLE 734
#define TASK_COMPLEX_OPEN_VEHICLE_DOOR 735
#define TASK_COMPLEX_CLIMB_INTO_VEHICLE 736
#define TASK_COMPLEX_CLEAR_VEHICLE_SEAT 737
#define TASK_COMPLEX_NEW_EXIT_VEHICLE 738
#define TASK_COMPLEX_SHUFFLE_BETWEEN_SEATS 739
#define TASK_COMPLEX_GANG_DRIVEBY 740
#define TASK_COMPLEX_CLOSE_VEHICLE_DOOR 741
#define TASK_COMPLEX_BACK_OFF 742
#define TASK_COMPLEX_BE_ARRESTED_AND_DRIVEN_AWAY 743
#define TASK_COMPLEX_ARRESTED_AI_PED_AND_DRIVE_AWAY 744
#define TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL 800
#define TASK_SIMPLE_CAR_ALIGN 801
#define TASK_SIMPLE_CAR_OPEN_DOOR_FROM_OUTSIDE 802
#define TASK_SIMPLE_CAR_OPEN_LOCKED_DOOR_FROM_OUTSIDE 803
#define TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_INSIDE 805
#define TASK_SIMPLE_CAR_CLOSE_DOOR_FROM_OUTSIDE 806
#define TASK_SIMPLE_CAR_GET_IN 807
#define TASK_SIMPLE_CAR_SHUFFLE 808
#define TASK_SIMPLE_CAR_SET_PED_IN_VEHICLE 811
#define TASK_SIMPLE_CAR_GET_OUT 813
#define TASK_SIMPLE_CAR_JUMP_OUT 814
#define TASK_SIMPLE_CAR_SET_PED_OUT 816
#define TASK_SIMPLE_CAR_SLOW_DRAG_OUT_PED 820
#define TASK_SIMPLE_CAR_SLOW_BE_DRAGGED_OUT 821
#define TASK_SIMPLE_SET_PED_AS_AUTO_DRIVER 827
#define TASK_SIMPLE_WAIT_UNTIL_PED_IS_OUT_OF_CAR 829
#define TASK_SIMPLE_CREATE_CAR_AND_GET_IN 832
#define TASK_SIMPLE_START_CAR 835
#define TASK_SIMPLE_SHUNT 836
#define TASK_SIMPLE_SMASH_CAR_WINDOW 838
#define TASK_SIMPLE_MOVE_GO_TO_POINT 900
#define TASK_COMPLEX_GO_TO_POINT_SHOOTING 901
#define TASK_COMPLEX_MOVE_GO_TO_POINT_AND_STAND_STILL 903
#define TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL_TIMED 903
#define TASK_COMPLEX_MOVE_FOLLOW_POINT_ROUTE 905
#define TASK_COMPLEX_MOVE_SEEK_ENTITY 907
#define TASK_COMPLEX_SMART_FLEE_POINT 910
#define TASK_COMPLEX_SMART_FLEE_ENTITY 911
#define TASK_COMPLEX_FOLLOW_LEADER_IN_FORMATION 913
#define TASK_COMPLEX_GO_TO_ATTRACTOR 915
#define TASK_COMPLEX_MOVE_AVOID_OTHER_PED_WHILE_WONDERING 917
#define TASK_COMPLEX_GO_TO_POINT_ANY_MEANS 918
#define TASK_COMPLEX_SEEK_ENTITY_ANY_MEANS 922
#define TASK_COMPLEX_FOLLOW_LEADER_ANY_MEANS 923
#define TASK_COMPLEX_GO_TO_POINT_AIMING 924
#define TASK_COMPLEX_FLEE_ANY_MEANS 927
#define TASK_COMPLEX_FLEE_SHOOTING 928
#define TASK_COMPLEX_FOLLOW_PATROL_ROUTE 931
#define TASK_COMPLEX_SEEK_ENTITY_AIMING 933
#define TASK_COMPLEX_FOLLOW_PED_FOOTSTEPS 936
#define TASK_COMPLEX_MOVE_FOLLOW_NAV_MESH_ROUTE 942
#define TASK_SIMPLE_MOVE_GO_TO_POINT_ON_ROUTE 943
#define TASK_COMPLEX_ESCAPE_BLAST 944
#define TASK_COMPLEX_MOVE_GET_TO_POINT_CONTINUOUS 945
#define TASK_COMPLEX_COP 946
#define TASK_COMPLEX_SEARCH_FOR_PED_ON_FOOT 947
#define TASK_COMPLEX_SEARCH_FOR_PED_IN_CAR 948
#define TASK_COMPLEX_MOVE_WANDER 949
#define TASK_COMPLEX_MOVE_BE_IN_FORMATION 950
#define TASK_COMPLEX_MOVE_CROWD_AROUND_LOCATION 951
#define TASK_COMPLEX_MOVE_CROSS_ROAD_AT_TRAFFIC_LIGHTS 952
#define TASK_COMPLEX_MOVE_WAIT_FOR_TRAFFIC 953
#define TASK_COMPLEX_MOVE_GO_TO_POINT_STAND_STILL_ACHIVE_HEADING 955
#define TASK_COMPLEX_MOVE_RETURN_TO_ROUTE 958
#define TASK_COMPLEX_MOVE_GO_TO_SHELTER_AND_WAIT 959
#define TASK_COMPLEX_MOVE_GET_ON_TO_MAIN_NAV_MESH 960
#define TASK_COMPLEX_MOVE_GO_TO_POINT_RELATIVE_TO_ENTITY_AND_STAND_STILL 962
#define TASK_COMPLEX_COP_HELICOPTOR 963
#define TASK_COMPLEX_HELICOPTOR_STRAFE 964
#define TASK_COMPLEX_FLEE_AND_DRIVE 966
#define TASK_COMPLEX_GET_OUT_OF_WATER 967
#define TASK_COMPLEX_DESTROY_CAR 1003
#define TASK_COMPLEX_DESTROY_CAR_ARMED 1005
#define TASK_SIMPLE_THROW_PROJECTILE 1018
#define TASK_COMPLEX_SEEK_COVER 1036
#define TASK_COMPLEX_SEEK_COVER_SHOOTING 1036
#define TASK_COMPLEX_AIM_AND_THROW_PROJECTILE 1038
#define TASK_SIMPLE_PLAYER_AIM_PROJECTILE 1039
#define TASK_COMPLEX_GUN 1040
#define TASK_SIMPLE_AIM_GUN 1041
#define TASK_SIMPLE_FIRE_GUN 1042
#define TASK_SIMPLE_RELOAD_GUN 1043
#define TASK_COMPLEX_SLIDE_INTO_COVER 1044
#define TASK_COMPLEX_PLAYER_IN_COVER 1046
#define TASK_COMPLEX_GO_INTO_COVER 1047
#define TASK_COMPLEX_COMBAT_CLOSEST_TARGET_IN_AREA 1048
#define TASK_SIMPLE_NEW_GANG_DRIVE_BY 1049
#define TASK_COMPLEX_COMBAT_ADDITIONAL_TASK 1050
#define TASK_COMPLEX_NEW_USE_COVER 1054
#define TASK_COMPLEX_THROW_PROJECTILE 1058
#define TASK_COMPLEX_ARREST_PED 1101
#define TASK_COMPLEX_GANG_HASSLE_PED 1212
#define TASK_SIMPLE_MOVE_SWIM 1304
#define TASK_COMPLEX_MOVE_ABOUT_INJURED 1310
#define TASK_COMPLEX_REVIVE 1311
#define TASK_COMPLEX_COMBAT 1900
#define TASK_COMPLEX_COMBAT_FIRE_SUBTASK 1901
#define TASK_COMPLEX_COMBAT_ADVANCE_SUBTASK 1902
#define TASK_COMPLEX_COMBAT_SEEK_COVER_SUBTASK 1903
#define TASK_COMPLEX_COMBAT_RETREAT_SUBTASK 1904
#define TASK_COMPLEX_COMBAT_CHARGE_SUBTASK 1905
#define TASK_COMPLEX_COMBAT_INVESTIGATE_SUBTASK 1906
#define TASK_COMPLEX_COMBAT_PULL_FROM_CAR_SUBTASK 1907
#define TASK_COMPLEX_COMBAT_PERSUE_IN_CAR_SUBTASK 1908
#define TASK_COMPLEX_COMBAT_BUST_PED 1910
#define TASK_COMPLEX_COMBAT_EXECUTE_PED_SUBTASK 1911
#define TASK_COMPLEX_COMBAT_FLANK_SUBTASK 1913
#define TASK_COMPLEX_SET_AND_GUARD_AREA 1932
#define TASK_COMPLEX_STAND_GUARD 1933
#define TASK_COMPLEX_SEPERATE 1934
#define TASK_COMPLEX_REACT 1312
#define TASK_SIMPLE_NM_RELAX 2104
#define TASK_SIMPLE_NM_ROLL_UP_AND_RELAX 2104
#define TASK_SIMPLE_NM_POSE 2105
#define TASK_SIMPLE_NM_BRACE 2106
#define TASK_SIMPLE_NM_SHOT 2107
#define TASK_SIMPLE_NM_HIGH_FALL 2108
#define TASK_SIMPLE_NM_BALANCE 2109
#define TASK_SIMPLE_NM_EXPLOSION 2110
#define TASK_SIMPLE_NM_ON_FIRE 2111
#define TASK_SIMPLE_NM_SCRIPT_CONTROL 2112
#define TASK_SIMPLE_NM_JUMP_ROLL_FROM_ROAD_VEHICLE 2113
#define TASK_SIMPLE_NM_SIT 2115
#define TASK_SIMPLE_BLEND_FROM_NM 2117
#define TASK_COMPLEX_NM 2118

class CControls
{

public:

	unsigned char		ucOnFootMove[4];
	unsigned char		ucInVehicleMove[4];
	unsigned char		ucInVehicleTriggers[2];
	
	enum { KEY_COUNT = 16 };

	struct
	{

		bool bEnterExitVehicle : 1;

		bool bSprint : 1;
		bool bJump : 1;
		bool bAttack : 1;
		bool bAttack2 : 1;
		bool bAim : 1;
		bool bFreeAim : 1;
		bool bMeleeAttack1 : 1;
		bool bMeleeAttack2 : 1;
		bool bMeleeKick : 1;
		bool bMeleeBlock : 1;

		bool bHandbrake : 1;
		bool bHandbrake2 : 1;
		bool bHorn : 1;
		bool bDriveBy : 1;
		bool bHeliPrimaryFire : 1;

	} keys;

	CControls( );

	bool IsInCombat( )						const { return (keys.bMeleeAttack1 || keys.bMeleeAttack2 || keys.bMeleeKick || keys.bMeleeBlock); }
	bool IsFiring( )						const { return (keys.bAttack); }
	bool IsAiming( )						const { return (keys.bAttack2 || keys.bAim || keys.bFreeAim); }
	bool IsSprinting( )						const { return (keys.bSprint); }
	bool IsJumping( )						const { return (keys.bJump); }
	bool IsUsingEnterExitVehicle( )			const { return (keys.bEnterExitVehicle); }
	bool IsUsingHorn()						const { return (keys.bHorn); }

};

#endif