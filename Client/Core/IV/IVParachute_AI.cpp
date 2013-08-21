//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: IVParachuteAI.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "IVParachute_AI.h"
// TODO, started converting to C++, continue pls

/*

asm sub_0(...)
{
    enter 0 20
    fpush 0.00000000
    plocal 17
    pset 
    fpush 0.00000000
    plocal 18
    pset 
    fpush 0.00000000
    plocal 19
    pset 
    ipush1 0
    plocal 21
    pset 
    ipush1 -1
    plocal 22
    pset 
    ipush1 0
    plocal 23
    pset 
    ipush1 0
    plocal 24
    pset 
    ipush1 0
    plocal 25
    pset 
    ipush1 0
    plocal 26
    pset 
    ipush1 0
    plocal 27
    pset 
    fpush 0.00000000
    plocal 28
    pset 
    fpush 0.00000000
    plocal 29
    pset 
    fpush 0.00000000
    plocal 30
    pset 
    fpush -60.00000000
    plocal 31
    pset 
    fpush -80.00000000
    plocal 32
    pset 
    fpush -50.00000000
    plocal 33
    pset 
    fpush -7.00000000
    plocal 34
    pset 
    fpush -5.50000000
    plocal 35
    pset 
    fpush -12.00000000
    plocal 36
    pset 
    ipush1 0
    plocal 37
    pset 
    ipush1 0
    plocal 38
    pset 
    ipush1 0
    plocal 39
    pset 
    plocal 40
    pget 
    call sub_166
    ipush1 1
    while (...) 
    {
        ipush1 0
        native WAIT 1 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 56
        iadd 
        pget 
        not 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        native IS_CHAR_INJURED 1 1
        or 
        if true (...) 
        {
            call sub_257
        }
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        native IS_CHAR_INJURED 1 1
        not 
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 4
            iadd 
            pget 
            ipush1 0
            icmpne 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 4
            iadd 
            pget 
            ipush1 1
            icmpne 
            and 
            if true (...) 
            {
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush1 0
                iadd 
                pget 
                native IS_CHAR_IN_ANY_CAR 1 1
                if true (...) 
                {
                    call sub_257
                }
            }
        }
        call sub_665
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 56
        iadd 
        pget 
        and 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 68
        iadd 
        pget 
        not 
        and 
        if true (...) 
        {
            plocal 31
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 48
            iadd 
            pget 
            fcmpne 
            if true (...) 
            {
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 48
                iadd 
                pget 
                plocal 31
                pset 
                plocal 31
                pget 
                fpush -60.00000000
                fpush -80.00000000
                fsub 
                fsub 
                plocal 32
                pset 
                plocal 31
                pget 
                fpush -50.00000000
                fpush -60.00000000
                fsub 
                fadd 
                plocal 33
                pset 
            }
            plocal 34
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 52
            iadd 
            pget 
            fcmpne 
            if true (...) 
            {
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 52
                iadd 
                pget 
                plocal 34
                pset 
                plocal 34
                pget 
                fpush -5.50000000
                fpush -7.00000000
                fsub 
                fadd 
                plocal 35
                pset 
                plocal 34
                pget 
                fpush -7.00000000
                fpush -12.00000000
                fsub 
                fsub 
                plocal 36
                pset 
                plocal 35
                pget 
                fpush 2.00000000
                fneg 
                fcmpgt 
                if true (...) 
                {
                    fpush 2.00000000
                    fneg 
                    plocal 35
                    pset 
                }
            }
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            native IS_CHAR_INJURED 1 1
            not 
            if true (...) 
            {
                plocal 38
                pget 
                not 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    ipush1 8
                    ipush1 1
                    ipush1 0
                    native SET_CHAR_COMPONENT_VARIATION 4 0
                    ipush1 1
                    plocal 38
                    pset 
                }
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush1 4
                iadd 
                pget 
                switch  (...) 
                {
                      case 0:
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    native IS_CHAR_IN_ANY_CAR 1 1
                    not 
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        pframe2 
                        native GET_CHAR_HEIGHT_ABOVE_GROUND 2 0
                        pframe2 
                        pget 
                        fpush 30.00000000
                        fcmpgt 
                        pglobal 2784
                        pget 
                        or 
                        if true (...) 
                        {
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 0
                            iadd 
                            pget 
                            pframe3 
                            ipush1 0
                            iadd 
                            pframe3 
                            ipush1 4
                            iadd 
                            pframe3 
                            ipush1 8
                            iadd 
                            native GET_CHAR_VELOCITY 4 0
                            pframe3 
                            ipush1 8
                            iadd 
                            pget 
                            fpush 4.00000000
                            fneg 
                            fcmplt 
                            if true (...) 
                            {
                                ipush1 3
                                pframe3 
                                pnget 
                                call sub_1206
                            }
                        }
                    }
                    else
                    {
                        ipush1 0
                        plocal 37
                        pset 
                        ipush1 1
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 4
                        iadd 
                        pset 
                    }
                    break
                      case 1:
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    native IS_CHAR_IN_ANY_CAR 1 1
                    not 
                    plocal 37
                    pget 
                    ipush1 0
                    icmpeq 
                    and 
                    if true (...) 
                    {
                        plocal 37
                        native GET_GAME_TIMER 1 0
                    }
                    plocal 37
                    pget 
                    ipush1 0
                    icmpne 
                    if true (...) 
                    {
                        pframe6 
                        native GET_GAME_TIMER 1 0
                        pframe6 
                        pget 
                        plocal 37
                        pget 
                        isub 
                        ipush2 1000
                        icmpgt 
                        if true (...) 
                        {
                            ipush1 0
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 4
                            iadd 
                            pset 
                        }
                    }
                    break
                      case 2:
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    native IS_CHAR_INJURED 1 1
                    not 
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        native IS_CHAR_IN_ANY_CAR 1 1
                        not 
                        if true (...) 
                        {
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 0
                            iadd 
                            pget 
                            pframe7 
                            ipush1 0
                            iadd 
                            pframe7 
                            ipush1 4
                            iadd 
                            pframe7 
                            ipush1 8
                            iadd 
                            native GET_CHAR_VELOCITY 4 0
                            ipush1 1
                            plocal 26
                            pset 
                            ipush1 3
                            pframe7 
                            pnget 
                            call sub_1206
                        }
                    }
                    break
                      case 3:
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 8
                    iadd 
                    pget 
                    ipush1 2
                    icmpeq 
                    if true (...) 
                    {
                        call sub_2126
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 12
                        iadd 
                        ipush1 0
                        iadd 
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 12
                        iadd 
                        ipush1 4
                        iadd 
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 12
                        iadd 
                        ipush1 8
                        iadd 
                        native GET_CHAR_COORDINATES 4 0
                    }
                    call sub_2213
                    break
                      case 4:
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    native IS_CHAR_INJURED 1 1
                    not 
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        pframe 10
                        ipush1 0
                        iadd 
                        pframe 10
                        ipush1 4
                        iadd 
                        pframe 10
                        ipush1 8
                        iadd 
                        native GET_CHAR_COORDINATES 4 0
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        native CLEAR_CHAR_TASKS_IMMEDIATELY 1 0
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        ipush1 1
                        native SET_BLOCKING_OF_NON_TEMPORARY_EVENTS 2 0
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        ipush1 0
                        native UNLOCK_RAGDOLL 2 0
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        spush "PARACHUTE"
                        spush "Hang_Idle"
                        native IS_CHAR_PLAYING_ANIM 3 1
                        not 
                        if true (...) 
                        {
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 0
                            iadd 
                            pget 
                            spush "Hang_Idle"
                            spush "PARACHUTE"
                            fpush 10.00000000
                            ipush1 1
                            ipush1 1
                            ipush1 1
                            ipush1 0
                            ipush1 0
                            native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                        }
                        plocal 20
                        pget 
                        native DOES_OBJECT_EXIST 1 1
                        not 
                        if true (...) 
                        {
                            ipush 1490460832
                            pframe 10
                            ipush1 0
                            iadd 
                            pget 
                            pframe 10
                            ipush1 4
                            iadd 
                            pget 
                            pframe 10
                            ipush1 8
                            iadd 
                            pget 
                            fpush 2.00000000
                            fadd 
                            plocal 20
                            ipush1 1
                            native CREATE_OBJECT 6 0
                            plocal 20
                            pget 
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 0
                            iadd 
                            pget 
                            ipush1 0
                            fpush 0.02500000
                            fpush 0.12500000
                            fneg 
                            fpush 5.83000000
                            fpush 0.00000000
                            fpush 0.00000000
                            fpush 0.00000000
                            ipush1 1
                            native ATTACH_OBJECT_TO_PED 10 0
                        }
                        ipush1 5
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 4
                        iadd 
                        pset 
                    }
                    break
                      case 5:
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    native IS_CHAR_INJURED 1 1
                    not 
                    call sub_2126
                    native IS_CHAR_INJURED 1 1
                    not 
                    and 
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 8
                        iadd 
                        pget 
                        ipush1 2
                        icmpeq 
                        if true (...) 
                        {
                            call sub_2126
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 12
                            iadd 
                            ipush1 0
                            iadd 
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 12
                            iadd 
                            ipush1 4
                            iadd 
                            plocal 21
                            pget 
                            ipush1 18
                            pglobal 2692
                            parray 
                            ipush1 12
                            iadd 
                            ipush1 8
                            iadd 
                            native GET_CHAR_COORDINATES 4 0
                        }
                        call sub_5140
                    }
                    break
                      case 7:
                    plocal 20
                    pget 
                    native DOES_OBJECT_EXIST 1 1
                    if true (...) 
                    {
                        plocal 20
                        pget 
                        pframe 13
                        ipush1 0
                        iadd 
                        pframe 13
                        ipush1 4
                        iadd 
                        pframe 13
                        ipush1 8
                        iadd 
                        native GET_OBJECT_COORDINATES 4 0
                        plocal 20
                        pget 
                        pframe 13
                        ipush1 0
                        iadd 
                        pget 
                        pframe 13
                        ipush1 4
                        iadd 
                        pget 
                        pframe 13
                        ipush1 8
                        iadd 
                        pget 
                        fpush 40.00000000
                        fadd 
                        fpush 0.00000000
                        fpush 0.00000000
                        fpush 0.40000000
                        ipush1 0
                        native SLIDE_OBJECT 8 1
                        drop 
                        plocal 20
                        pget 
                        spush "obj_crumple"
                        spush "PARACHUTE"
                        native IS_OBJECT_PLAYING_ANIM 3 1
                        if true (...) 
                        {
                            plocal 20
                            pget 
                            spush "obj_crumple"
                            spush "PARACHUTE"
                            fpush 0.20000000
                            native SET_OBJECT_ANIM_SPEED 4 0
                        }
                        plocal 23
                        pget 
                        ipush1 10
                        iadd 
                        plocal 23
                        pset 
                        plocal 23
                        pget 
                        ipush2 255
                        icmpgt 
                        if true (...) 
                        {
                            ipush2 255
                            plocal 23
                            pset 
                        }
                        plocal 20
                        pget 
                        ipush2 255
                        plocal 23
                        pget 
                        isub 
                        native SET_OBJECT_ALPHA 2 0
                        plocal 23
                        pget 
                        ipush2 255
                        icmpge 
                        if true (...) 
                        {
                            plocal 20
                            native DELETE_OBJECT 1 0
                        }
                    }
                    else
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        spush "PARACHUTE"
                        spush "Land"
                        native IS_CHAR_PLAYING_ANIM 3 1
                        not 
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        spush "PARACHUTE"
                        spush "Land_Safe"
                        native IS_CHAR_PLAYING_ANIM 3 1
                        not 
                        and 
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        spush "PARACHUTE"
                        spush "Land_Fast"
                        native IS_CHAR_PLAYING_ANIM 3 1
                        not 
                        and 
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        native IS_PED_RAGDOLL 1 1
                        not 
                        and 
                        if true (...) 
                        {
                            call sub_257
                        }
                    }
                    break
                }
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush1 0
                iadd 
                pget 
                pframe 16
                native GET_CHAR_HEALTH 2 0
                pframe 16
                pget 
                ipush2 125
                icmple 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    ipush1 1
                    native UNLOCK_RAGDOLL 2 0
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    ipush1 0
                    ipush2 2000
                    ipush1 0
                    ipush1 1
                    ipush1 1
                    ipush1 0
                    native SWITCH_PED_TO_RAGDOLL 7 1
                    drop 
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    ipush1 0
                    native SET_CHAR_HEALTH 2 0
                    call sub_257
                }
            }
            else
            {
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 56
                iadd 
                pget 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    native DOES_CHAR_EXIST 1 1
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        ipush1 1
                        native UNLOCK_RAGDOLL 2 0
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        pframe 17
                        ipush1 0
                        iadd 
                        pframe 17
                        ipush1 4
                        iadd 
                        pframe 17
                        ipush1 8
                        iadd 
                        native N_1363505769 4 0
                        pframe 17
                        ipush1 0
                        iadd 
                        pget 
                        fpush 2.00000000
                        fadd 
                        pframe 17
                        ipush1 4
                        iadd 
                        pget 
                        pframe 17
                        ipush1 8
                        iadd 
                        pget 
                        pframe 17
                        ipush1 0
                        iadd 
                        pget 
                        pframe 17
                        ipush1 4
                        iadd 
                        pget 
                        pframe 17
                        ipush1 8
                        iadd 
                        pget 
                        ipush2 100
                        native FIRE_SINGLE_BULLET 7 0
                        pframe 17
                        ipush1 0
                        iadd 
                        pget 
                        fpush 2.00000000
                        fsub 
                        pframe 17
                        ipush1 4
                        iadd 
                        pget 
                        pframe 17
                        ipush1 8
                        iadd 
                        pget 
                        pframe 17
                        ipush1 0
                        iadd 
                        pget 
                        pframe 17
                        ipush1 4
                        iadd 
                        pget 
                        pframe 17
                        ipush1 8
                        iadd 
                        pget 
                        fpush 0.10000000
                        fadd 
                        ipush2 100
                        native FIRE_SINGLE_BULLET 7 0
                    }
                    call sub_257
                }
            }
        }
    }
    ret 0 0
}

asm sub_166(...)
{
    enter 1 3
    pframe0 
    pget 
    plocal 21
    pset 
    ipush1 1
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 60
    iadd 
    pset 
    ret 1 0
}

asm sub_257(...)
{
    enter 0 2
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pget 
    native IS_CHAR_INJURED 1 1
    not 
    if true (...) 
    {
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        ipush1 0
        native SET_BLOCKING_OF_NON_TEMPORARY_EVENTS 2 0
    }
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pget 
    native DOES_CHAR_EXIST 1 1
    if true (...) 
    {
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        ipush1 1
        native UNLOCK_RAGDOLL 2 0
    }
    plocal 20
    pget 
    native DOES_OBJECT_EXIST 1 1
    if true (...) 
    {
        plocal 20
        pget 
        ipush1 0
        native DETACH_OBJECT 2 0
        plocal 20
        native DELETE_OBJECT 1 0
    }
    pstate 
    pget 
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pset 
    ipush1 0
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 4
    iadd 
    pset 
    ipush1 0
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 8
    iadd 
    pset 
    fpush 0.00000000
    fpush 0.00000000
    fpush 0.00000000
    ipush1 3
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 12
    iadd 
    pnset 
    fpush -60.00000000
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 48
    iadd 
    pset 
    fpush -7.00000000
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 52
    iadd 
    pset 
    ipush1 0
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 56
    iadd 
    pset 
    ipush1 0
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 60
    iadd 
    pset 
    ipush1 0
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 64
    iadd 
    pset 
    ipush1 0
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 68
    iadd 
    pset 
    ipush1 0
    pglobal 2788
    pset 
    native TERMINATE_THIS_SCRIPT 0 0
    ret 0 0
}

asm sub_665(...)
{
    enter 0 2
    ipush 1490460832
    native HAS_MODEL_LOADED 1 1
    spush "PARACHUTE"
    native HAVE_ANIMS_LOADED 1 1
    and 
    if true (...) 
    {
        ipush1 1
        ret 0 1
    }
    ipush1 0
    ret 0 1
}

asm sub_1206(...)
{
    enter 3 5
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pget 
    native IS_CHAR_INJURED 1 1
    not 
    if true (...) 
    {
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        native IS_PED_RAGDOLL 1 1
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            spush "PARACHUTE"
            spush "Free_Fall"
            ipush1 0
            ipush1 0
            itof 
            ipush1 0
            itof 
            ipush1 0
            itof 
            native BLEND_FROM_NM_WITH_ANIM 7 0
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            ipush1 1
            native SWITCH_PED_TO_ANIMATED 2 0
        }
        else
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            spush "PARACHUTE"
            spush "Free_Fall"
            native IS_CHAR_PLAYING_ANIM 3 1
            not 
            if true (...) 
            {
                plocal 26
                pget 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    spush "Free_Fall"
                    spush "PARACHUTE"
                    fpush 1000.00000000
                    ipush1 1
                    ipush1 1
                    ipush1 1
                    ipush1 0
                    ipush1 0
                    native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                }
                else
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    spush "Free_Fall"
                    spush "PARACHUTE"
                    fpush 0.75000000
                    ipush1 1
                    ipush1 1
                    ipush1 1
                    ipush1 0
                    ipush1 0
                    native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                }
            }
        }
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        ipush1 0
        native UNLOCK_RAGDOLL 2 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        ipush1 1
        native SET_BLOCKING_OF_NON_TEMPORARY_EVENTS 2 0
        pframe0 
        ipush1 0
        iadd 
        pget 
        pframe0 
        ipush1 4
        iadd 
        pget 
        fpush 0.00000000
        native VMAG 3 1
        plocal 28
        pset 
        fpush 0.00000000
        plocal 30
        pset 
        plocal 26
        pget 
        if true (...) 
        {
            fpush 30.00000000
            fneg 
            plocal 29
            pset 
        }
        else
        {
            pframe0 
            ipush1 8
            iadd 
            pget 
            plocal 29
            pset 
        }
        ipush1 0
        itof 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 0
        iadd 
        pset 
        ipush1 0
        itof 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 4
        iadd 
        pset 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 8
        iadd 
        native GET_CHAR_HEADING 2 0
    }
    ipush1 3
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 4
    iadd 
    pset 
    call sub_1690
    ret 3 0
}

asm sub_1690(...)
{
    enter 0 2
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pget 
    native IS_CHAR_INJURED 1 1
    not 
    if true (...) 
    {
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 0
        iadd 
        pget 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 4
        iadd 
        pget 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 8
        iadd 
        pget 
        native SET_CHAR_ROTATION 4 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        plocal 28
        pget 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 8
        iadd 
        pget 
        native SIN 1 1
        fneg 
        fmul 
        plocal 28
        pget 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 8
        iadd 
        pget 
        native COS 1 1
        fmul 
        plocal 29
        pget 
        native SET_CHAR_VELOCITY 4 0
    }
    ret 0 0
}

asm sub_2126(...)
{
    enter 0 3
    native GET_PLAYER_ID 0 1
    native CONVERT_INT_TO_PLAYERINDEX 1 1
    pframe2 
    native GET_PLAYER_CHAR 2 0
    pframe2 
    pget 
    ret 0 1
}

asm sub_2213(...)
{
    enter 0 14
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pget 
    native IS_CHAR_INJURED 1 1
    not 
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 12
    iadd 
    ipush1 0
    iadd 
    pget 
    fpush 0.00000000
    fcmpne 
    and 
    if true (...) 
    {
        fpush 0.00000000
        pframe2 
        pset 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        pframe3 
        ipush1 0
        iadd 
        pframe3 
        ipush1 4
        iadd 
        pframe3 
        ipush1 8
        iadd 
        native GET_CHAR_COORDINATES 4 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        pframe6 
        ipush1 0
        iadd 
        pframe6 
        ipush1 4
        iadd 
        pframe6 
        ipush1 8
        iadd 
        native GET_CHAR_VELOCITY 4 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        pframe2 
        native GET_CHAR_HEIGHT_ABOVE_GROUND 2 0
        pframe6 
        ipush1 8
        iadd 
        pget 
        fpush 1.00000000
        fneg 
        fcmplt 
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 64
            iadd 
            pget 
            not 
            if true (...) 
            {
                pframe2 
                pget 
                pframe6 
                ipush1 8
                iadd 
                pget 
                plocal 21
                pget 
                call sub_2396
                pframe 9
                pset 
                fpush 1.25000000
                pframe 10
                pset 
                fpush 0.00000000
                pframe 11
                pset 
                fpush 0.00000000
                pframe 12
                pset 
                pframe2 
                pget 
                fpush 20.00000000
                fcmpgt 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush2 36
                    iadd 
                    ipush1 8
                    iadd 
                    pget 
                    ipush1 3
                    pframe3 
                    pnget 
                    ipush1 3
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 12
                    iadd 
                    pnget 
                    pframe 10
                    pget 
                    call sub_2631
                    pframe 11
                    pset 
                }
                plocal 30
                pframe 11
                pget 
                fpush 0.07500000
                call sub_2917
                plocal 30
                pget 
                pframe 10
                pget 
                fdiv 
                fpush 45.00000000
                fmul 
                pframe 12
                pset 
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 36
                iadd 
                ipush1 4
                iadd 
                pframe 12
                pget 
                fpush 45.00000000
                fpush 2.00000000
                fmul 
                fpush 0.05000000
                fpush 5.00000000
                ipush 1065353216
                call sub_3088
                plocal 28
                fpush 1.00000000
                fpush 0.30000000
                call sub_2917
                plocal 29
                plocal 31
                pget 
                fpush 0.40000000
                call sub_2917
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 36
                iadd 
                ipush1 8
                iadd 
                pget 
                plocal 30
                pget 
                fsub 
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 36
                iadd 
                ipush1 8
                iadd 
                pset 
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 36
                iadd 
                ipush1 8
                iadd 
                pget 
                ipush2 180
                itof 
                fcmpgt 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush2 36
                    iadd 
                    ipush1 8
                    iadd 
                    pget 
                    ipush2 360
                    itof 
                    fsub 
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush2 36
                    iadd 
                    ipush1 8
                    iadd 
                    pset 
                }
                else
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush2 36
                    iadd 
                    ipush1 8
                    iadd 
                    pget 
                    ipush2 65356
                    itof 
                    fcmplt 
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush2 36
                        iadd 
                        ipush1 8
                        iadd 
                        pget 
                        ipush2 360
                        itof 
                        fadd 
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush2 36
                        iadd 
                        ipush1 8
                        iadd 
                        pset 
                    }
                }
                pframe3 
                ipush1 8
                iadd 
                pget 
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush1 12
                iadd 
                ipush1 8
                iadd 
                pget 
                fsub 
                pframe 13
                pset 
                pframe 9
                pget 
                fpush 0.20000000
                fcmplt 
                pframe 13
                pget 
                fpush 100.00000000
                fcmplt 
                or 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    spush "Open_chute"
                    spush "PARACHUTE"
                    fpush 4.00000000
                    ipush1 1
                    ipush1 1
                    ipush1 1
                    ipush1 0
                    ipush1 0
                    native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                    ipush1 1
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush2 64
                    iadd 
                    pset 
                }
                else
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    spush "PARACHUTE"
                    spush "Free_Fall"
                    native IS_CHAR_PLAYING_ANIM 3 1
                    not 
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        spush "Free_Fall"
                        spush "PARACHUTE"
                        fpush 4.00000000
                        ipush1 1
                        ipush1 1
                        ipush1 1
                        ipush1 0
                        ipush1 0
                        native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                    }
                }
            }
            else
            {
                ipush1 3
                pframe3 
                pnget 
                call sub_3620
            }
            call sub_1690
        }
        pframe2 
        pget 
        fpush 10.00000000
        fcmplt 
        pframe6 
        ipush1 8
        iadd 
        pget 
        fpush 5.00000000
        fneg 
        fcmpgt 
        and 
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            native SET_CHAR_HEADING 2 0
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            plocal 28
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            native SIN 1 1
            fneg 
            fmul 
            plocal 28
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            native COS 1 1
            fmul 
            plocal 29
            pget 
            native SET_CHAR_VELOCITY 4 0
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            ipush1 0
            native SET_CHAR_HEALTH 2 0
            call sub_257
        }
    }
    ret 0 0
}

asm sub_2396(...)
{
    enter 3 10
    fpush 1.00000000
    pframe5 
    pset 
    pframe2 
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 4
    iadd 
    pget 
    ipush1 3
    icmpeq 
    if true (...) 
    {
        fpush 15.00000000
        pframe6 
        pset 
        fpush -12.00000000
        pframe1 
        pget 
        fsub 
        pframe6 
        pget 
        fdiv 
        pframe7 
        pset 
        pframe1 
        pget 
        pframe7 
        pget 
        fmul 
        pframe6 
        pget 
        ipush1 2
        itof 
        fdiv 
        pframe7 
        pget 
        pframe7 
        pget 
        fmul 
        fmul 
        fadd 
        native ABSF 1 1
        pframe 8
        pset 
        pframe0 
        pget 
        pframe 8
        pget 
        fsub 
        pframe 9
        pset 
        pframe 9
        pget 
        fpush 0.00000000
        fcmplt 
        if true (...) 
        {
            fpush 0.00000000
            pframe 9
            pset 
        }
        else
        {
            pframe 9
            pget 
            fpush 400.00000000
            fcmpgt 
            if true (...) 
            {
                fpush 400.00000000
                pframe 9
                pset 
            }
        }
        pframe 9
        pget 
        fpush 400.00000000
        fdiv 
        pframe5 
        pset 
    }
    pframe5 
    pget 
    ret 3 1
}

asm sub_2631(...)
{
    enter 8 14
    fpush 0.00000000
    pframe 10
    pset 
    pframe0 
    pget 
    fpush 0.00000000
    fcmplt 
    if true (...) 
    {
        pframe0 
        pget 
        fpush 360.00000000
        fadd 
        pframe0 
        pset 
    }
    pframe4 
    ipush1 0
    iadd 
    pget 
    pframe1 
    ipush1 0
    iadd 
    pget 
    fsub 
    pframe4 
    ipush1 4
    iadd 
    pget 
    pframe1 
    ipush1 4
    iadd 
    pget 
    fsub 
    native ATAN2 2 1
    fneg 
    pframe 11
    pset 
    pframe 11
    pget 
    fpush 0.00000000
    fcmplt 
    if true (...) 
    {
        pframe 11
        pget 
        fpush 360.00000000
        fadd 
        pframe 11
        pset 
    }
    pframe 11
    pget 
    pframe0 
    pget 
    fsub 
    pframe 12
    pset 
    pframe 12
    pget 
    fpush 0.00000000
    fcmplt 
    if true (...) 
    {
        pframe 12
        pget 
        fpush 360.00000000
        fadd 
        pframe 12
        pset 
    }
    pframe0 
    pget 
    pframe 11
    pget 
    fsub 
    pframe 13
    pset 
    pframe 13
    pget 
    fpush 0.00000000
    fcmplt 
    if true (...) 
    {
        pframe 13
        pget 
        fpush 360.00000000
        fadd 
        pframe 13
        pset 
    }
    pframe 12
    pget 
    pframe 13
    pget 
    fcmple 
    if true (...) 
    {
        pframe 12
        pget 
        fpush 25.00000000
        fcmpgt 
        if true (...) 
        {
            pframe7 
            pget 
            fneg 
            pframe 10
            pset 
        }
        else
        {
            pframe 12
            pget 
            fpush 25.00000000
            fdiv 
            pframe7 
            pget 
            fneg 
            fmul 
            pframe 10
            pset 
        }
    }
    else
    {
        pframe 13
        pget 
        fpush 25.00000000
        fcmpgt 
        if true (...) 
        {
            pframe7 
            pget 
            pframe 10
            pset 
        }
        else
        {
            pframe 13
            pget 
            fpush 25.00000000
            fdiv 
            pframe7 
            pget 
            fmul 
            pframe 10
            pset 
        }
    }
    pframe 10
    pget 
    ret 8 1
}

asm sub_2917(...)
{
    enter 3 7
    pframe0 
    pget 
    pget 
    pframe1 
    pget 
    fcmpne 
    if true (...) 
    {
        pframe5 
        native GET_FRAME_TIME 1 0
        pframe2 
        pget 
        fpush 30.00000000
        fmul 
        pframe5 
        pget 
        fmul 
        pframe6 
        pset 
        pframe0 
        pget 
        pget 
        pframe1 
        pget 
        fsub 
        pframe6 
        pget 
        fcmpgt 
        if true (...) 
        {
            pframe0 
            pget 
            pget 
            pframe6 
            pget 
            fsub 
            pframe0 
            pget 
            pset 
        }
        else
        {
            pframe0 
            pget 
            pget 
            pframe1 
            pget 
            fsub 
            pframe6 
            pget 
            fneg 
            fcmplt 
            if true (...) 
            {
                pframe0 
                pget 
                pget 
                pframe6 
                pget 
                fadd 
                pframe0 
                pget 
                pset 
            }
            else
            {
                pframe1 
                pget 
                pframe0 
                pget 
                pset 
            }
        }
    }
    ret 3 0
}

asm sub_3088(...)
{
    enter 6 10
    pframe0 
    pget 
    pget 
    pframe1 
    pget 
    fcmpne 
    if true (...) 
    {
        pframe0 
        pget 
        pget 
        pframe1 
        pget 
        fsub 
        native ABSF 1 1
        pframe2 
        pget 
        fdiv 
        pframe 8
        pset 
        pframe4 
        pget 
        pframe 9
        pset 
        pframe 8
        pget 
        pframe5 
        pget 
        fcmplt 
        if true (...) 
        {
            pframe 8
            pget 
            pframe5 
            pget 
            fdiv 
            pframe4 
            pget 
            fmul 
            pframe 9
            pset 
        }
        pframe 9
        pget 
        pframe3 
        pget 
        fcmplt 
        if true (...) 
        {
            pframe3 
            pget 
            pframe 9
            pset 
        }
        pframe0 
        pget 
        pframe1 
        pget 
        pframe 9
        pget 
        call sub_2917
    }
    ret 6 0
}

asm sub_3620(...)
{
    enter 3 6
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pget 
    native IS_CHAR_INJURED 1 1
    not 
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 4
    iadd 
    pget 
    ipush1 3
    icmpeq 
    and 
    if true (...) 
    {
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        spush "PARACHUTE"
        spush "Open_Chute"
        native IS_CHAR_PLAYING_ANIM 3 1
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            spush "PARACHUTE"
            spush "Open_Chute"
            pframe5 
            native GET_CHAR_ANIM_CURRENT_TIME 4 0
            pframe5 
            pget 
            fpush 0.30000000
            fcmplt 
            if true (...) 
            {
                plocal 29
                fpush -60.00000000
                fpush 0.40000000
                call sub_2917
                plocal 28
                fpush 1.00000000
                fpush 0.30000000
                call sub_2917
            }
            else
            {
                plocal 29
                pget 
                fpush -60.00000000
                fcmpgt 
                if true (...) 
                {
                    plocal 29
                    fpush -7.00000000
                    fpush 1.50000000
                    fpush 2.00000000
                    fmul 
                    call sub_2917
                }
                else
                {
                    plocal 29
                    fpush -7.00000000
                    fpush 1.50000000
                    call sub_2917
                }
                plocal 28
                fpush 12.00000000
                fpush 0.30000000
                call sub_2917
                plocal 25
                pget 
                not 
                if true (...) 
                {
                    ipush1 -1
                    spush "PARACHUTE_OPEN"
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    native PLAY_SOUND_FROM_PED 3 0
                    ipush1 1
                    plocal 25
                    pset 
                }
                pframe5 
                pget 
                fpush 0.40000000
                fcmpgt 
                if true (...) 
                {
                    plocal 20
                    pget 
                    native DOES_OBJECT_EXIST 1 1
                    not 
                    if true (...) 
                    {
                        ipush 1490460832
                        pframe0 
                        ipush1 0
                        iadd 
                        pget 
                        pframe0 
                        ipush1 4
                        iadd 
                        pget 
                        pframe0 
                        ipush1 8
                        iadd 
                        pget 
                        fpush 2.00000000
                        fadd 
                        plocal 20
                        ipush1 1
                        native CREATE_OBJECT 6 0
                        plocal 20
                        pget 
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        ipush1 0
                        fpush 0.02500000
                        fpush 0.12500000
                        fneg 
                        fpush 5.83000000
                        fpush 0.00000000
                        fpush 0.00000000
                        fpush 0.00000000
                        ipush1 1
                        native ATTACH_OBJECT_TO_PED 10 0
                        plocal 20
                        pget 
                        spush "obj_deploy"
                        spush "PARACHUTE"
                        fpush 1000.00000000
                        ipush1 0
                        ipush1 1
                        native PLAY_OBJECT_ANIM 6 1
                        drop 
                    }
                    else
                    {
                        plocal 20
                        pget 
                        spush "obj_wind_low"
                        spush "PARACHUTE"
                        native IS_OBJECT_PLAYING_ANIM 3 1
                        not 
                        if true (...) 
                        {
                            pframe5 
                            pget 
                            fpush 0.60000000
                            fcmpgt 
                            if true (...) 
                            {
                                plocal 20
                                pget 
                                spush "obj_wind_low"
                                spush "PARACHUTE"
                                fpush 10.00000000
                                ipush1 1
                                ipush1 0
                                native PLAY_OBJECT_ANIM 6 1
                                drop 
                            }
                        }
                    }
                }
                pframe5 
                pget 
                fpush 0.95000000
                fcmpgt 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    spush "PARACHUTE"
                    spush "Hang_Idle"
                    native IS_CHAR_PLAYING_ANIM 3 1
                    not 
                    if true (...) 
                    {
                        plocal 21
                        pget 
                        ipush1 18
                        pglobal 2692
                        parray 
                        ipush1 0
                        iadd 
                        pget 
                        spush "Hang_Idle"
                        spush "PARACHUTE"
                        fpush 1000.00000000
                        ipush1 1
                        ipush1 1
                        ipush1 1
                        ipush1 0
                        ipush1 0
                        native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                    }
                    ipush1 5
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 4
                    iadd 
                    pset 
                }
            }
        }
        else
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            spush "Open_chute"
            spush "PARACHUTE"
            fpush 1000.00000000
            ipush1 0
            ipush1 1
            ipush1 1
            ipush1 0
            ipush1 0
            native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
        }
    }
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 36
    iadd 
    ipush1 0
    iadd 
    fpush 0.00000000
    fpush 45.00000000
    fpush 0.05000000
    fpush 5.00000000
    ipush 1065353216
    call sub_3088
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush2 36
    iadd 
    ipush1 4
    iadd 
    fpush 0.00000000
    fpush 45.00000000
    fpush 0.05000000
    fpush 5.00000000
    ipush 1065353216
    call sub_3088
    plocal 30
    fpush 0.00000000
    fpush 0.10000000
    call sub_2917
    ret 3 0
}

asm sub_5140(...)
{
    enter 0 21
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 0
    iadd 
    pget 
    native IS_CHAR_INJURED 1 1
    not 
    plocal 21
    pget 
    ipush1 18
    pglobal 2692
    parray 
    ipush1 12
    iadd 
    ipush1 0
    iadd 
    pget 
    fpush 0.00000000
    fcmpne 
    and 
    if true (...) 
    {
        fpush 0.00000000
        pframe2 
        pset 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        pframe3 
        ipush1 0
        iadd 
        pframe3 
        ipush1 4
        iadd 
        pframe3 
        ipush1 8
        iadd 
        native GET_CHAR_COORDINATES 4 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        pframe6 
        ipush1 0
        iadd 
        pframe6 
        ipush1 4
        iadd 
        pframe6 
        ipush1 8
        iadd 
        native GET_CHAR_VELOCITY 4 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        pframe2 
        native GET_CHAR_HEIGHT_ABOVE_GROUND 2 0
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        native IS_CHAR_IN_WATER 1 1
        pframe3 
        ipush1 8
        iadd 
        pget 
        fpush 0.00000000
        fcmplt 
        or 
        if true (...) 
        {
            plocal 20
            pget 
            native DOES_OBJECT_EXIST 1 1
            if true (...) 
            {
                plocal 20
                pget 
                ipush1 1
                native DETACH_OBJECT 2 0
                plocal 20
                pget 
                ipush1 0
                native SET_OBJECT_COLLISION 2 0
                plocal 20
                pget 
                ipush1 1
                native SET_OBJECT_DYNAMIC 2 0
                plocal 20
                pget 
                spush "obj_crumple"
                spush "PARACHUTE"
                fpush 8.00000000
                ipush1 0
                ipush1 1
                native PLAY_OBJECT_ANIM 6 1
                drop 
            }
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            native CLEAR_CHAR_TASKS_IMMEDIATELY 1 0
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            native SET_CHAR_HEADING 2 0
            ipush1 7
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 4
            iadd 
            pset 
        }
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        spush "PARACHUTE"
        spush "Hang_Idle"
        native IS_CHAR_PLAYING_ANIM 3 1
        not 
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            spush "Hang_Idle"
            spush "PARACHUTE"
            fpush 4.00000000
            ipush1 1
            ipush1 1
            ipush1 1
            ipush1 0
            ipush1 0
            native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
        }
        plocal 20
        pget 
        native DOES_OBJECT_EXIST 1 1
        not 
        if true (...) 
        {
            ipush 1490460832
            pframe3 
            ipush1 0
            iadd 
            pget 
            pframe3 
            ipush1 4
            iadd 
            pget 
            pframe3 
            ipush1 8
            iadd 
            pget 
            fpush 2.00000000
            fadd 
            plocal 20
            ipush1 1
            native CREATE_OBJECT 6 0
            plocal 20
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            ipush1 0
            fpush 0.02500000
            fpush 0.12500000
            fneg 
            fpush 5.83000000
            fpush 0.00000000
            fpush 0.00000000
            fpush 0.00000000
            ipush1 1
            native ATTACH_OBJECT_TO_PED 10 0
        }
        fpush 1.25000000
        fpush 1.25000000
        fmul 
        pframe 9
        pset 
        fpush 12.00000000
        pframe 10
        pset 
        plocal 34
        pget 
        pframe 11
        pset 
        fpush 0.00000000
        pframe 12
        pset 
        fpush 20.00000000
        pframe 13
        pset 
        fpush 0.00000000
        pframe 14
        pset 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 12
        iadd 
        ipush1 0
        iadd 
        pget 
        pframe3 
        ipush1 0
        iadd 
        pget 
        fsub 
        pframe 15
        pset 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 12
        iadd 
        ipush1 4
        iadd 
        pget 
        pframe3 
        ipush1 4
        iadd 
        pget 
        fsub 
        pframe 16
        pset 
        pframe 15
        pget 
        pframe 15
        pget 
        fmul 
        pframe 16
        pget 
        pframe 16
        pget 
        fmul 
        fadd 
        native SQRT 1 1
        pframe 17
        pset 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 12
        iadd 
        ipush1 8
        iadd 
        pget 
        pframe3 
        ipush1 8
        iadd 
        pget 
        fsub 
        native ABSF 1 1
        pframe 18
        pset 
        pframe 17
        pget 
        pframe 18
        pget 
        fdiv 
        pframe 19
        pset 
        pframe 11
        pget 
        pframe 19
        pget 
        fmul 
        native ABSF 1 1
        pframe 10
        pset 
        pframe 10
        pget 
        fpush 6.00000000
        fcmplt 
        if true (...) 
        {
            fpush 6.00000000
            pframe 10
            pset 
        }
        else
        {
            pframe 10
            pget 
            fpush 15.00000000
            fcmpgt 
            if true (...) 
            {
                fpush 15.00000000
                pframe 10
                pset 
            }
        }
        pframe2 
        pget 
        fpush 10.00000000
        fcmpgt 
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            ipush1 3
            pframe3 
            pnget 
            ipush1 3
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 12
            iadd 
            pnget 
            pframe 9
            pget 
            call sub_2631
            pframe 12
            pset 
        }
        plocal 30
        pget 
        pframe 9
        pget 
        fdiv 
        fpush 45.00000000
        fmul 
        pframe 14
        pset 
        plocal 28
        pframe 10
        pget 
        fpush 0.30000000
        call sub_2917
        plocal 29
        pframe 11
        pget 
        fpush 0.25000000
        call sub_2917
        plocal 30
        pframe 12
        pget 
        fpush 0.07500000
        call sub_2917
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 0
        iadd 
        pframe 13
        pget 
        fpush 20.00000000
        fpush 2.00000000
        fmul 
        fpush 0.05000000
        fpush 5.00000000
        ipush 1065353216
        call sub_3088
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 4
        iadd 
        pframe 14
        pget 
        fpush 45.00000000
        fpush 2.00000000
        fmul 
        fpush 0.05000000
        fpush 5.00000000
        ipush 1065353216
        call sub_3088
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 8
        iadd 
        pget 
        plocal 30
        pget 
        fsub 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 8
        iadd 
        pset 
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush2 36
        iadd 
        ipush1 8
        iadd 
        pget 
        ipush2 180
        itof 
        fcmpgt 
        if true (...) 
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            ipush2 360
            itof 
            fsub 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pset 
        }
        else
        {
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            ipush2 65356
            itof 
            fcmplt 
            if true (...) 
            {
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 36
                iadd 
                ipush1 8
                iadd 
                pget 
                ipush2 360
                itof 
                fadd 
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush2 36
                iadd 
                ipush1 8
                iadd 
                pset 
            }
        }
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        native IS_PED_RAGDOLL 1 1
        not 
        if true (...) 
        {
            call sub_1690
        }
        plocal 21
        pget 
        ipush1 18
        pglobal 2692
        parray 
        ipush1 0
        iadd 
        pget 
        native IS_CHAR_WAITING_FOR_WORLD_COLLISION 1 1
        if true (...) 
        {
            ipush1 1
            plocal 27
            pset 
            ipush1 0
            plocal 24
            pset 
        }
        else
        {
            plocal 27
            pget 
            if true (...) 
            {
                plocal 24
                pget 
                ipush1 0
                icmpeq 
                if true (...) 
                {
                    plocal 24
                    native GET_GAME_TIMER 1 0
                }
                else
                {
                    pframe 20
                    native GET_GAME_TIMER 1 0
                    pframe 20
                    pget 
                    plocal 24
                    pget 
                    isub 
                    ipush2 2000
                    icmpgt 
                    pframe6 
                    ipush1 8
                    iadd 
                    pget 
                    fpush 1.00000000
                    fneg 
                    fcmplt 
                    or 
                    if true (...) 
                    {
                        ipush1 0
                        plocal 27
                        pset 
                    }
                }
            }
        }
        pframe2 
        pget 
        fpush 1.20000000
        fcmplt 
        pframe6 
        ipush1 8
        iadd 
        pget 
        fpush 1.00000000
        fneg 
        fcmpgt 
        pframe6 
        ipush1 8
        iadd 
        pget 
        plocal 29
        pget 
        fsub 
        native ABSF 1 1
        fpush 3.00000000
        fcmpgt 
        and 
        plocal 27
        pget 
        not 
        and 
        or 
        if true (...) 
        {
            plocal 20
            pget 
            native DOES_OBJECT_EXIST 1 1
            if true (...) 
            {
                plocal 20
                pget 
                ipush1 1
                native DETACH_OBJECT 2 0
                plocal 20
                pget 
                ipush1 0
                native SET_OBJECT_COLLISION 2 0
                plocal 20
                pget 
                ipush1 1
                native SET_OBJECT_DYNAMIC 2 0
                plocal 20
                pget 
                spush "obj_crumple"
                spush "PARACHUTE"
                fpush 8.00000000
                ipush1 0
                ipush1 1
                native PLAY_OBJECT_ANIM 6 1
                drop 
            }
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush2 36
            iadd 
            ipush1 8
            iadd 
            pget 
            native SET_CHAR_HEADING 2 0
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 0
            iadd 
            pget 
            pframe6 
            ipush1 0
            iadd 
            pget 
            fpush 2.00000000
            fdiv 
            pframe6 
            ipush1 4
            iadd 
            pget 
            fpush 2.00000000
            fdiv 
            pframe6 
            ipush1 8
            iadd 
            pget 
            native SET_CHAR_VELOCITY 4 0
            plocal 29
            pget 
            plocal 34
            pget 
            fpush 2.00000000
            fsub 
            fcmpge 
            if true (...) 
            {
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush1 0
                iadd 
                pget 
                spush "PARACHUTE"
                spush "Land"
                native IS_CHAR_PLAYING_ANIM 3 1
                not 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    spush "Land"
                    spush "PARACHUTE"
                    fpush 4.00000000
                    ipush1 0
                    ipush1 1
                    ipush1 1
                    ipush1 0
                    ipush1 0
                    native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                }
            }
            else
            {
                plocal 21
                pget 
                ipush1 18
                pglobal 2692
                parray 
                ipush1 0
                iadd 
                pget 
                spush "PARACHUTE"
                spush "Land_Fast"
                native IS_CHAR_PLAYING_ANIM 3 1
                not 
                if true (...) 
                {
                    plocal 21
                    pget 
                    ipush1 18
                    pglobal 2692
                    parray 
                    ipush1 0
                    iadd 
                    pget 
                    spush "Land_Fast"
                    spush "PARACHUTE"
                    fpush 4.00000000
                    ipush1 0
                    ipush1 1
                    ipush1 1
                    ipush1 0
                    ipush1 0
                    native TASK_PLAY_ANIM_NON_INTERRUPTABLE 9 0
                }
            }
            ipush1 7
            plocal 21
            pget 
            ipush1 18
            pglobal 2692
            parray 
            ipush1 4
            iadd 
            pset 
        }
    }
    ret 0 0
}


*/