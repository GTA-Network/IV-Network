//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: IVParachute.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "IVParachute_Process.h"
#include "IVParachuteData.h"
#include <CCore.h>

typedef unsigned unknown;
extern CCore * g_pCore;

float fVar2;
CVector3 uVar3;
unknown uVar4;
unknown uVar5;
CVector3 uVar6;
unknown uVar7;
unknown uVar8;
CVector3 uVar9;
unknown uVar10;
CVector3 uVar11;
unsigned int iVar12;
unknown uVar13;
unknown uVar14;
CVector3 uVar15;
unknown uVar16;
unknown uVar17;
CVector3 uVar18;
unknown uVar19;
unknown uVar20;
float uVar21;
float uVar22;
float fVar23;
float fVar24;
CVector3 uVar25;
unknown uVar26;
unknown uVar27;
float fVar28;
float fVar29;
unsigned int iVar30;
CVector3 g_U9105[6]; 

float l_U17 = 0.00000000;
float l_U18 = 0.00000000;
float l_U19 = 0.00000000;
unsigned int l_U20 = 0;
unsigned int l_U22 = 0;
unsigned int l_U23 = 0;
unsigned int l_U24 = 0;
unsigned int l_U25 = 0;
unsigned int l_U26 = 0;
unsigned int l_U27 = 0;
unsigned int l_U28 = -1;
unsigned int l_U29 = 0;
unsigned int l_U30 = 0;
unsigned int l_U31 = 0;
unsigned int l_U32 = 0;
unsigned int l_U33 = 1;
unsigned int l_U34 = 0;
unsigned int l_U35 = 0;
unsigned int l_U36 = 0;
unsigned int l_U37 = 0;
unsigned int l_U38 = 0;
unsigned int l_U39 = 0;
unsigned int l_U40 = 0;
unsigned int l_U41 = 0;
unsigned int l_U42 = 0;
unsigned int l_U43 = 0;
unsigned int l_U44 = 0;
float l_U45 = 0.00000000;
float l_U46 = 0.00000000;
float l_U47 = 0.00000000;
float l_U48 = 0.00000000;
float l_U49 = -60.00000000;
float l_U50 = -80.00000000;
float l_U51 = -50.00000000;
float l_U52 = -7.00000000;
float l_U53 = -5.50000000;
float l_U54 = -12.00000000;
float l_U55 = 0.00000000;
float l_U56 = 1000.00000000;
float l_U57 = 0.00000000;
float l_U58 = 0.00000000;
float l_U59 = 0.00000000;
float l_U60 = 0.00000000;
float l_U61 = 0.00000000;
unsigned int l_U62 = 0;
unsigned int l_U63 = 0;
unsigned int l_U64 = 0;
unsigned int l_U65 = 0;
CVector3 l_U77 = CVector3(0.00000000, -8.00000000, -3.50000000);
CVector3 l_U80 = CVector3(0.00000000, 0.00000000, 2.00000000);
float l_U83 = 7.50000000;
float l_U84 = 85.00000000;
float l_U85 = 0.00000000;
float l_U86 = 50.00000000;
float l_U87 = 1.00000000;
unsigned int l_U88 = 0;
unsigned int l_U89 = 0;
unsigned int l_U93 = 0;
unsigned int l_U94 = 0;
float l_U95 = 0.00000000;
float l_U96 = 0.00000000;

unsigned int l_U21 = 0; // object
unsigned int l_U70 = 0; // vehicle

unsigned int g_U2786 = 1;
unsigned int g_U2802 = 1;
unsigned l_U67;
CVector3 l_U71;
CVector3 l_U74;
CVector3 l_U90;
CVector3 l_U0;
CVector3 l_U3;
CVector3 l_U6;
unsigned int g_U2797 = 1;
unsigned int g_U2787 = 0;

unsigned int g_U9200 = 0;
unsigned int g_U10534 = 0;
unsigned int g_U10535 = 0;
unsigned int g_U560 = 0;
unsigned int g_U2795 = 0;
unsigned int g_U2788 = 0;
unsigned int g_U2790 = 0;
unsigned int g_U2792 = 0;
unsigned int g_U2798 = 0;
unsigned int g_U2799 = 0;
unsigned int g_U2800 = 0;
unsigned int g_U2801 = 0;

unsigned int g_U2783 = 1;
float l_U16;
unsigned int g_U2789 = 0;
unsigned int g_U2785= 1;
unsigned int g_U2784 = 1;
unsigned int lU36 = 1;
unsigned int g_U2794 = 1;
unsigned l_U66;
unsigned int g_U2791 = 1;

#define PARA_HANDLE g_pCore->GetGame()->GetLocalPlayer()->GetPlayerInfo()->GetPlayerInfo()->m_bytePlayerNumber

unsigned l_U69;
unsigned l_U68;
void sub_checkcams()
{
	unsigned int iVar2;

	if (DOES_CAM_EXIST(l_U69))
	{
		DESTROY_CAM(l_U69);
	}
	if (DOES_CAM_EXIST(l_U68))
	{
		DESTROY_CAM(l_U68);
	}
	COUNT_SCRIPT_CAMS(&iVar2);
	if (iVar2 == 0)
	{
		ACTIVATE_SCRIPTED_CAMS(0, 0);
	}
	return;
}

int sub_2854()
{
    if ((IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_R")) || (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_R")))
    {
        return 1;
    }
    else if ((IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_L")) || (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_L")))
    {
        return 2;
    }
    return 0;
}

void sub_4940()
{
    float uVar2;

    if (NOT (DOES_CAM_EXIST(l_U67)))
    {
        GET_GAME_CAM(&l_U67);
    }
    GET_CAM_POS(l_U67, &l_U71.fX, &l_U71.fY, &l_U71.fZ);
    GET_CAM_ROT(l_U67, &l_U74.fX, &l_U74.fY, &l_U74.fZ);
    GET_CAM_FOV(l_U67, &uVar2);
    if (NOT (DOES_CAM_EXIST(l_U68)))
    {
        CREATE_CAM(14, &l_U68);
        SET_CAM_MOTION_BLUR(l_U68, 0.10000000);
        ATTACH_CAM_TO_PED(l_U68, PARA_HANDLE);
        SET_CAM_ATTACH_OFFSET(l_U68, l_U77.fX, l_U77.fY, l_U77.fZ);
        SET_CAM_ATTACH_OFFSET_IS_RELATIVE(l_U68, 0);
        POINT_CAM_AT_PED(l_U68, PARA_HANDLE);
        SET_CAM_POINT_OFFSET(l_U68, l_U80.fX, l_U80.fY, l_U80.fZ);
        SET_CAM_POINT_OFFSET_IS_RELATIVE(l_U68, 1);
    }
    if (NOT (DOES_CAM_EXIST(l_U69)))
    {
        CREATE_CAM(14, &l_U69);
    }
    SET_CAM_POS(l_U69, l_U71.fX, l_U71.fY, l_U71.fZ);
    POINT_CAM_AT_PED(l_U69, PARA_HANDLE);
    return;
}
void sub_10238(float * uParam0, float fParam1, unknown uParam2)
{
    float uVar5;
    float fVar6;

    if ((uParam0) != &fParam1)
    {
        GET_FRAME_TIME(&uVar5);
        fVar6 = (uParam2 * 30.00000000) * uVar5;
        if (((uParam0) - &fParam1) > fVar6)
        {
            *(uParam0) -= fVar6;
        }
        else if ((*(uParam0) - fParam1) < -fVar6)
        {
            *(uParam0) += fVar6;
        }
        else
        {
            *(uParam0) = fParam1;
        }
    }
    return;
}


void sub_10452(float *uParam0, float fParam1, unknown uParam2, float fParam3, unknown uParam4, float fParam5)
{
    float fVar8;
    float fVar9;

    if (*(uParam0) != fParam1)
    {
        fVar8 = (ABSF(*(uParam0) - fParam1)) / uParam2;
        fVar9 = uParam4;
        if (fVar8 < fParam5)
        {
            fVar9 = (fVar8 / fParam5) * uParam4;
        }
        if (fVar9 < fParam3)
        {
            fVar9 = fParam3;
        }
        sub_10238(uParam0, fParam1, fVar9);
    }
    return;
}

float sub_3074()
{
    float Result;

    Result = -1.00000000;
    if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_R"))
    {
        GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_R", &Result);
    }
    else if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_R"))
    {
        GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_R", &Result);
    }
    else if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_L"))
    {
        GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_L", &Result);
    }
    else if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_L"))
    {
        GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_L", &Result);
    }
    return Result;
}

int sub_5739(CVector3 uParam0, unknown uParam1, unknown uParam2 = NULL, unknown uParam3 = NULL)
{
    float uVar6;

    GET_GROUND_Z_FOR_3D_COORD(uParam0.fX, uParam0.fY, uParam0.fZ + 1000.00000000, &uVar6);
    if ((uVar6 + uParam3) > uParam0.fZ)
    {
        return 1;
    }
    return 0;
}

void sub_5953(unknown uParam0, unknown uParam1)
{
    SET_CAM_ACTIVE(uParam0, uParam1);
    SET_CAM_PROPAGATE(uParam0, uParam1);
    ACTIVATE_SCRIPTED_CAMS(uParam1, uParam1);
    return;
}

void sub_5343(unknown uParam0, CVector3 uParam1, CVector3 uParam2, unknown uParam3 = NULL, CVector3 uParam4 = CVector3(), unknown uParam5 = NULL, unknown uParam6 = NULL)
{
    CVector3 vVar9;
    float uVar12;
    unsigned int iVar13;

    switch (l_U94)
    {
        case 1:
		{
			l_U84 = 85.00000000;
			break;
		}
        default:
		{
			break;
		}
    };

    UNATTACH_CAM(l_U69);
    UNPOINT_CAM(l_U69);
    SET_CAM_ACTIVE(l_U69, 0);
    SET_CAM_PROPAGATE(l_U69, 0);
    l_U41 = 0;
    COUNT_SCRIPT_CAMS(&iVar13);
    if (iVar13 <= 2)
    {
        ACTIVATE_SCRIPTED_CAMS(0, 0);
    }
    switch (uParam0)
    {
        case 1:
        GET_CAM_ROT(l_U67, &l_U74.fX, &l_U74.fY, &l_U74.fZ);
        l_U84 = ABSF(l_U74.fX);
        l_U85 = ABSF(l_U74.fX);
        break;
        case 3:
        GENERATE_RANDOM_FLOAT_IN_RANGE(-20.00000000, 20.00000000, &l_U90.fX);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-20.00000000, 20.00000000, &l_U90.fY);
        l_U90.fX += uParam4.fX * 3.00000000;
        l_U90.fY += uParam4.fY * 3.00000000;
        vVar9 = CVector3(uParam1.fX + l_U90.fX, uParam1.fY + l_U90.fY, uParam1.fZ - 10.00000000);
        if (sub_5739(vVar9, 1084227584))
        {
            GET_GROUND_Z_FOR_3D_COORD(vVar9.fX, vVar9.fY, vVar9.fZ + 1000.00000000, &uVar12);
            vVar9.fX = uVar12 + 5.00000000;
            l_U41 = 1;
        }
        SET_CAM_POS(l_U69, vVar9.fX, vVar9.fY, vVar9.fZ);
        SET_CAM_FOV(l_U69, 45.00000000);
        POINT_CAM_AT_PED(l_U69, PARA_HANDLE);
        SET_CAM_POINT_OFFSET(l_U69, 0.00000000, 0.00000000, 0.00000000);
        sub_5953(l_U69, 1);
        GET_GAME_TIMER(&l_U89);
        break;
        case 4:
        GENERATE_RANDOM_FLOAT_IN_RANGE(-4.00000000, 4.00000000, &l_U90.fX);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-4.00000000, 4.00000000, &l_U90.fY);
        vVar9 = CVector3(uParam1.fX + l_U90.fX, uParam1.fY + l_U90.fY, uParam1.fZ - 50.00000000);
        if (sub_5739(vVar9, 20.00000000))
        {
            GET_GROUND_Z_FOR_3D_COORD(vVar9.fX, vVar9.fY, vVar9.fZ + 1000.00000000, &uVar12);
            vVar9.fZ = uVar12 + 5.00000000;
            l_U41 = 1;
        }
        SET_CAM_POS(l_U69, vVar9.fX, vVar9.fY, vVar9.fZ);
        POINT_CAM_AT_PED(l_U69, PARA_HANDLE);
        SET_CAM_POINT_OFFSET(l_U69, 0.00000000, 0.00000000, 0.00000000);
        sub_5953(l_U69, 1);
        GET_GAME_TIMER(&l_U89);
        break;
        case 5:
        while ((ABSF(l_U90.fX)) < 3.00000000)
        {
            GENERATE_RANDOM_FLOAT_IN_RANGE(-5.00000000, 5.00000000, &l_U90.fX);
        }
        GENERATE_RANDOM_FLOAT_IN_RANGE(-3.00000000, 3.00000000, &l_U90.fY);
        GENERATE_RANDOM_FLOAT_IN_RANGE(1.00000000, 2.00000000, &l_U90.fZ);
        ATTACH_CAM_TO_PED(l_U69, PARA_HANDLE);
        SET_CAM_ATTACH_OFFSET(l_U69, l_U90.fX, l_U90.fY, l_U90.fZ);
        POINT_CAM_AT_PED(l_U69, PARA_HANDLE);
        SET_CAM_POINT_OFFSET(l_U69, 0.00000000, 0.00000000, 0.00000000);
        sub_5953(l_U69, 1);
        GET_GAME_TIMER(&l_U89);
        break;
        case 6:
        GENERATE_RANDOM_FLOAT_IN_RANGE(-20.00000000, 20.00000000, &l_U90.fX);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-20.00000000, 20.00000000, &l_U90.fY);
        l_U90.fX += uParam4.fX * 3.00000000;
        l_U90.fY += uParam4.fY * 3.00000000;
        l_U90.fZ = -10.00000000;
        vVar9 = CVector3(uParam1.fX + l_U90.fX, uParam1.fY + l_U90.fY, uParam1.fZ + l_U90.fZ);
        if (sub_5739(vVar9, 1084227584))
        {
            GET_GROUND_Z_FOR_3D_COORD(vVar9.fX, vVar9.fY, vVar9.fZ + 1000.00000000, &uVar12);
            vVar9.fZ = uVar12 + 5.00000000;
            l_U41 = 1;
        }
        SET_CAM_POS(l_U69, vVar9.fX, vVar9.fY, vVar9.fZ);
        SET_CAM_FOV(l_U69, 45.00000000);
        POINT_CAM_AT_PED(l_U69, PARA_HANDLE);
        SET_CAM_POINT_OFFSET(l_U69, 0.00000000, 0.00000000, 0.00000000);
        sub_5953(l_U69, 1);
        GET_GAME_TIMER(&l_U89);
        break;
    }
    l_U94 = uParam0;
    return;
}

void sub_6947()
{
    float fVar2;
    float fVar3;

    fVar2 = 0.00000000;
    fVar3 = 0.00000000;
    if (g_U2692[0].fY == 3)
    {
        GENERATE_RANDOM_FLOAT_IN_RANGE(-1.00000000, 1.00000000, &fVar2);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.50000000, 0.50000000, &fVar3);
        SHAKE_PAD(0, 200, ROUND(fVar2 * 128.00000000));
    }
    else if (g_U2692[0].fY == 5)
    {
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.50000000, 0.50000000, &fVar2);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.50000000, 0.50000000, &fVar3);
    }
    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        SET_CHAR_ROTATION(PARA_HANDLE, g_U2692[0]._fU36.fX, g_U2692[0]._fU36.fY, g_U2692[0]._fU36.fZ);
        g_U2692[0]._fU24.fX = ((l_U45 * (-SIN(g_U2692[0]._fU36.fZ))) + (l_U47 * (COS(g_U2692[0]._fU36.fZ)))) + fVar2;
        g_U2692[0]._fU24.fY = ((l_U45 * (COS(g_U2692[0]._fU36.fZ))) + (l_U47 * (SIN(g_U2692[0]._fU36.fZ)))) + fVar3;
        g_U2692[0]._fU24.fZ = l_U46;
        SET_CHAR_VELOCITY(PARA_HANDLE, g_U2692[0]._fU24.fX, g_U2692[0]._fU24.fY, g_U2692[0]._fU24.fZ);
    }
    return;
}

unsigned int sub_8507()
{
    return CONVERT_INT_TO_PLAYERINDEX(GET_PLAYER_ID());
}

void sub_11913(CVector3 uParam0, unknown uParam1 = NULL, unknown uParam2 = NULL)
{
    float fVar5;

    if ((g_U2692[0].fY == 3) AND (NOT (IS_CHAR_INJURED(PARA_HANDLE))))
    {
        if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Open_Chute"))
        {
            GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "PARACHUTE", "Open_Chute", &fVar5);
            if (fVar5 < 0.30000000)
            {
                sub_10238(&l_U46, -60.00000000, 0.40000000);
                sub_10238(&l_U45, 1.00000000, 0.30000000);
            }
            else if (l_U46 > -60.00000000)
            {
                sub_10238(&l_U46, -7.00000000, 1.50000000 * 2.00000000);
            }
            else
            {
                sub_10238(&l_U46, -7.00000000, 1.50000000);
            }
            sub_10238(&l_U45, 13.00000000, 0.30000000);
            if (NOT l_U32)
            {
                PLAY_SOUND_FROM_PED(-1, "PARACHUTE_OPEN", PARA_HANDLE);
                l_U32 = 1;
                l_U28 = GET_SOUND_ID();
                PLAY_SOUND_FROM_PED(l_U28, "PARACHUTE_DESCEND", PARA_HANDLE);
            }
            if (fVar5 > 0.20000000)
            {
                if (NOT (DOES_OBJECT_EXIST(l_U21)))
                {
                    CREATE_OBJECT(1490460832, uParam0.fX, uParam0.fY, uParam0.fZ + 2.00000000, &l_U21, 1);
                    ATTACH_OBJECT_TO_PED(l_U21, PARA_HANDLE, 0, 0.02500000, -0.12500000, 5.45000000, 0.00000000, 0.00000000, 0.00000000, 1);
                    PLAY_OBJECT_ANIM(l_U21, "obj_deploy", "PARACHUTE", 1000.00000000, 0, 1);
                }
                else if (NOT (IS_OBJECT_PLAYING_ANIM(l_U21, "obj_wind_low", "PARACHUTE")))
                {
                    if (fVar5 > 0.65000000)
                    {
                        PLAY_OBJECT_ANIM(l_U21, "obj_wind_low", "PARACHUTE", 10.00000000, 1, 0);
                    }
                }
            }
            if (fVar5 > 0.95000000)
            {
                if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Hang_Idle")))
                {
                    TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Hang_Idle", "PARACHUTE", 1000.00000000, 1, 1, 1, 0, 0);
                }
                l_U33 = 1;
                l_U88 = 0;
                sub_5343(0, uParam0, CVector3(), 0.00000000, CVector3());
                l_U56 = uParam0.fZ;
                g_U2692[0].fY = 5;
            }
        }
        else
        {
            TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Open_chute", "PARACHUTE", 10.00000000, 0, 1, 1, 0, 0);
        }
    }
    sub_10452(&g_U2692[0]._fU36.fX, 0.00000000, 45.00000000, 0.05000000, 2.50000000, 1065353216);
    sub_10452(&g_U2692[0]._fU36.fY, 0.00000000, 45.00000000, 0.05000000, 2.50000000, 1065353216);
    sub_10238(&l_U48, 0.00000000, 0.10000000);
    return;
}

void sub_13051(float iParam0, CVector3 uParam1, CVector3 uParam2, unknown uParam3 = NULL, CVector3 uParam4 = CVector3(), unknown uParam5 = NULL, unknown uParam6 = NULL)
{
    unsigned int iVar9;

    if ((IS_CONTROL_PRESSED(2, 0)) || ((IS_CONTROL_PRESSED(0, 59)) AND (IS_USING_CONTROLLER())))
    {
        COUNT_SCRIPT_CAMS(&iVar9);
        if (iVar9 <= 2)
        {
            if ((l_U94 != 3) AND (NOT l_U88))
            {
                if (iParam0 != 5)
                {
                    sub_5343(4, uParam1, uParam4);
                }
                else
                {
                    sub_5343(6, uParam1, uParam4);
                }
                l_U88 = 1;
            }
        }
    }
    else if (l_U88)
    {
        sub_5343(0, uParam1, uParam4);
        l_U88 = 0;
    }
    return;
}

void Reset()
{
	l_U20 = 0;
	l_U26 = 0;
	l_U27 = 0;
	l_U28 = -1;
	l_U62 = 0;
	l_U63 = 0;
	l_U64 = 0;
	l_U65 = 0;
	l_U32 = 0;
	l_U33 = 1;
	l_U34 = 0;
	l_U35 = 0;
	l_U36 = 0;
	l_U37 = 0;
	l_U38 = 0;
	l_U39 = 0;
	l_U40 = 0;
	l_U41 = 0;
	l_U42 = 0;
	l_U43 = 0;
	l_U44 = 0;
	l_U45 = 0.00000000;
	l_U46 = 0.00000000;
	l_U47 = 0.00000000;
	l_U48 = 0.00000000;
	l_U59 = 0.00000000;
	l_U60 = 0.00000000;
	l_U61 = 0.00000000;
	l_U84 = 85.00000000;
	l_U85 = 0.00000000;
	l_U86 = 50.00000000;
	l_U87 = 1.00000000;
	l_U88 = 0;
	l_U89 = 0;
	l_U93 = 0;
	l_U94 = 0;
	l_U95 = 0.00000000;
	l_U96 = 0.00000000;
	return;
}

void Switch(bool bParam)
{
	if(DOES_CHAR_EXISTS(PARA_HANDLE))
	{
		BLOCK_PED_WEAPON_SWITCHING(PARA_HANDLE, 0);
		UNLOCK_RAGDOLL(PARA_HANDLE, 1);
	}

	//SET_GAME_CAMERA_CONTROLS_ACTIVE(l_U68, 1);
	sub_checkcams();

	if(NOT(IS_CHAR_INJURED(PARA_HANDLE)))
	{
		SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(PARA_HANDLE, 0);
		SET_CHAR_INVINCIBLE(PARA_HANDLE, 0);

	}
	else
	{
		GIVE_CHAR_WEAPON(PARA_HANDLE, 41, 1, 0);
	}

	if(l_U28 != -1)
	{
		STOP_SOUND(l_U28);
		RELEASE_SOUND_ID(l_U28);
		l_U28 = -1;
	}
	if(DOES_OBJECT_EXIST(l_U21))
	{
		DETACH_OBJECT(l_U21, 0);
		DELETE_OBJECT(&l_U21);
	}
	if(IS_VEH_DRIVEABLE(l_U70))
	{
		if(NOT l_U43)
		{
			MARK_CAR_AS_NO_LONGER_NEEDED(&l_U70);
		}
	}

	l_U70 = NULL;
	Reset();
}

void sub_2781()
{
	int iVar2;
	int iVar3;
	float fVar4;
	float uVar5;
	float fVar6;
	float uVar7;
	CVector3 uVar8;
	unknown uVar9;
	unknown uVar10;
	CVector3 uVar11;
	unknown uVar12;
	unknown uVar13;
	CVector3 uVar14;
	unknown uVar15;
	unknown uVar16;
	int I;
	int iVar18;
	float fVar19;

	l_U36 = 0;
	iVar2 = 1;
	iVar3 = 0;
	I = 0;
	if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
	{
		if (IS_CONTROL_JUST_PRESSED(2, 2))
		{
			l_U35 = 1;
		}
		if (l_U35)
		{
			iVar18 = sub_2854();
			if (iVar18 != 0)
			{
				fVar19 = sub_3074();
				if (fVar19 > 0.10000000)
				{
					GET_CHAR_COORDINATES(PARA_HANDLE, &uVar11.fX, &uVar11.fY, &uVar11.fZ);
					GET_CHAR_VELOCITY(PARA_HANDLE, &uVar8.fX, &uVar8.fY, &uVar8.fZ);
					fVar6 = VMAG(uVar8.fX, uVar8.fY, 0.00000000);
					for (I = 0; I < 100; I++)
					{
						uVar14 = uVar11;
						uVar14.fX += (uVar8.fX / fVar6) * (I * 0.03300000);
						uVar14.fY += (uVar8.fY / fVar6) * (I * 0.03300000);
						GET_GROUND_Z_FOR_3D_COORD(uVar14.fX, uVar14.fY, uVar14.fZ + 100.00000000, &uVar5);
						fVar4 = uVar14.fZ - uVar5;
						if (I != 99)
						{
							if (fVar4 < 1.00000000)
							{
								iVar2 = 0;
							}
						}
						else if (fVar4 > 30.00000000)
						{
							iVar3 = 1;
						}
					}
					if (((g_U2791) || ((iVar2) && (NOT IS_INTERIOR_SCENE()))) && (iVar3))
					{
						if (iVar18 == 2)
						{
							TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "jump_takeoff_l", "PARACHUTE", 8.00000000, 0, 1, 1, 0, 0);
						}
						else if (iVar18 == 1)
						{
							TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "jump_takeoff_r", "PARACHUTE", 8.00000000, 0, 1, 1, 0, 0);
						}
						l_U36 = 1;
					}
					l_U35 = 0;
				}
			}
		}
		else if ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "jump_takeoff_r"))) && ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "jump_takeoff_l"))) && ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_L"))) && ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_L"))) && ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_RIFLE", "Jump_TakeOff_R"))) && ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "JUMP_STD", "Jump_TakeOff_R"))) && (g_U2791)))))))
		{
			GET_CHAR_COORDINATES(PARA_HANDLE, &uVar11.fX, &uVar11.fY, &uVar11.fZ);
			GET_CHAR_VELOCITY(PARA_HANDLE, &uVar8.fX, &uVar8.fY, &uVar8.fZ);
			if (uVar11.fX > -244.30000000)
			{
				fVar6 = VMAG(uVar8.fX, uVar8.fY, 0.00000000);
				GET_CHAR_HEADING(PARA_HANDLE, &uVar7);
				if (((ABSF(uVar7 - 270.00000000)) < 45.00000000) && (fVar6 > 0.00000000))
				{
					TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "jump_takeoff_l", "PARACHUTE", 8.00000000, 0, 1, 1, 0, 0);
					l_U36 = 1;
				}
			}
		}
	}
	return;
}

void sub_4486(CVector3 uParam0, unknown uParam1 = NULL, unknown uParam2 = NULL)
{
    CVector3 uVar5;
    unknown uVar6;
    unknown uVar7;
    float fVar8;
    CString sVar9;
    CVector3 uVar10;
    unknown uVar11;
    unknown uVar12;
    float uVar13;

    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        switch (l_U20)
        {
            case 0:
            if (NOT l_U37)
            {
                if (IS_PED_RAGDOLL(PARA_HANDLE))
                {
                    BLEND_FROM_NM_WITH_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall", 0, 0, 0, 0);
                    SWITCH_PED_TO_ANIMATED(PARA_HANDLE, 1);
                }
                else if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall")))
                {
                    if (g_U2786)
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall", "PARACHUTE", 1000.00000000, 1, 1, 1, 0, 0);
                    }
                    else
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall", "PARACHUTE", 0.75000000, 1, 1, 1, 0, 0);
                    }
                }
            }
            SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(PARA_HANDLE, 1);
            l_U45 = VMAG(uParam0.fX, uParam0.fY, 0.00000000);
            l_U48 = 0.00000000;
            l_U46 = uParam0.fZ;
            g_U2692[0]._fU36.fX = 0;
            g_U2692[0]._fU36.fY = 0;
            GET_CHAR_HEADING(PARA_HANDLE, &g_U2692[0]._fU36.fZ);
            GET_CHAR_COORDINATES(PARA_HANDLE, &uVar5.fX, &uVar5.fY, &uVar5.fZ);
            l_U55 = uVar5.fZ;
            sub_4940();
            sub_5343(0, CVector3(), CVector3(), 0.00000000, CVector3(), 0.00000000, 0.00000000);
            l_U33 = 1;
            GET_CURRENT_CHAR_WEAPON(PARA_HANDLE, (unsigned int *)l_U93);
            GIVE_WEAPON_TO_CHAR(PARA_HANDLE, 0, 0, 1);
            BLOCK_PED_WEAPON_SWITCHING(PARA_HANDLE, 1);
            if (NOT l_U37)
            {
                SET_CHAR_COLLISION(PARA_HANDLE, 1);
                GET_GAME_TIMER((unsigned int *)l_U31);
                g_U2802 = 0;
                g_U2692[0].fY = 3;
                sub_6947();
            }
            else
            {
                l_U20 = 1;
            }
            break;
            case 1:
            if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "jump_takeoff_r"))
            {
                sVar9 = "jump_takeoff_r";
            }
            else if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "jump_takeoff_l"))
            {
                sVar9 = "jump_takeoff_l";
            }
            if ((IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "jump_takeoff_l")) || (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "jump_takeoff_r")))
            {
                GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "PARACHUTE", sVar9, &fVar8);
                if (fVar8 > 0.80000000)
                {
                    TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall", "PARACHUTE", 1000.00000000, 1, 1, 1, 0, 0);
                    l_U45 = 5.00000000;
                    l_U46 = 1.00000000;
                    sub_6947();
                }
            }
            else if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall"))
            {
                GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "PARACHUTE", "Free_Fall", &fVar8);
                if (l_U38)
                {
                    if (IS_VEH_DRIVEABLE(l_U70))
                    {
                        SET_CAR_COLLISION(l_U70, 0);
                    }
                }
                if (fVar8 > 0.00000000)
                {
                    if (l_U38)
                    {
                        g_U2692[0]._fU36.fZ = l_U58 + 90.00000000;
                        if (g_U2692[0]._fU36.fZ > 180.00000000)
                        {
                            g_U2692[0]._fU36.fZ = -180.00000000 + (g_U2692[0]._fU36.fZ - 180.00000000);
                        }
                        if (IS_VEH_DRIVEABLE(l_U70))
                        {
                            SET_CAR_COLLISION(l_U70, 0);
                        }
                        if (IS_PED_RAGDOLL(PARA_HANDLE))
                        {
                            SWITCH_PED_TO_ANIMATED(PARA_HANDLE, 1);
                        }
                        SET_CHAR_HEADING(PARA_HANDLE, g_U2692[0]._fU36.fZ);
                        if (IS_VEH_DRIVEABLE(l_U70))
                        {
                            GET_CAR_SPEED_VECTOR(l_U70, &uVar10, 0);
                            GET_CAR_HEADING(l_U70, &uVar13);
                        }
                        l_U45 = ((uVar10.fX * (-COS(uVar13))) + (uVar10.fY * (-SIN(uVar13)))) + 3.00000000;
                        l_U47 = (uVar10.fY * (COS(uVar13))) + (uVar10.fX * (-SIN(uVar13)));
                        l_U46 = uVar10.fZ - 4.00000000;
                    }
                    else
                    {
                        l_U45 = (VMAG(uParam0.fX, uParam0.fY, 0.00000000)) + 3.00000000;
                        l_U46 = uParam0.fZ;
                    }
                    if (IS_VEH_DRIVEABLE(l_U70))
                    {
                        GET_GAME_TIMER(&l_U31);
                        l_U31 -= 1000;
                        SET_CAR_COLLISION(l_U70, 0);
                    }
                    SET_CHAR_COLLISION(PARA_HANDLE, 1);
                    g_U2692[0].fY = 3;
                    g_U2802 = 0;
                    l_U20 = 0;
                    sub_6947();
                }
            }
            break;
        }
    }
    return;
}

void sub_13524(CVector3 uParam0, CVector3 uParam1, unknown uParam2, unknown uParam3, unknown uParam4, unknown uParam5, unknown uParam6, unknown uParam7)
{
    if ((l_U0.fZ != uParam1.fZ) || ((l_U0.fY != uParam1.fY) || (l_U0.fX != uParam1.fX)))
    {
        l_U0 = uParam1;
        l_U6 = CVector3(0.00000000, 0.00000000, 0.00000000);
        l_U3 = CVector3(0.00000000, 0.00000000, 0.00000000);
    }
    if ((l_U6.fZ == l_U3.fZ) AND ((l_U6.fY == l_U3.fY) AND (l_U6.fX == l_U3.fX)))
    {
        GENERATE_RANDOM_FLOAT_IN_RANGE(uParam4, uParam5, &l_U3.fX);
        GENERATE_RANDOM_FLOAT_IN_RANGE(uParam4, uParam5, &l_U3.fY);
        GENERATE_RANDOM_FLOAT_IN_RANGE(uParam4, uParam5, &l_U3.fZ);
        GENERATE_RANDOM_FLOAT_IN_RANGE(uParam6, uParam7, &l_U16);
    }
    else
    {
        sub_10238(&l_U6.fX, l_U3.fX, l_U16);
        sub_10238(&l_U6.fY, l_U3.fY, l_U16);
        sub_10238(&l_U6.fZ, l_U3.fZ, l_U16);
    }
    SET_CAM_POINT_OFFSET(l_U69, uParam1.fX + l_U6.fX, uParam1.fY + l_U6.fY, uParam1.fZ + l_U6.fZ);
    return;
}

void sub_13224(CVector3 uParam0, CVector3 uParam1, unknown uParam2 = NULL, CVector3 uParam3 = CVector3(), unknown uParam4 = NULL, unknown uParam5 = NULL)
{
    float uVar8;
    float uVar9;
    float uVar10;
    float fVar11;
    unsigned int iVar12;
    CVector3 uVar13;
    unknown uVar14;
    unknown uVar15;
    float fVar16;

    GET_GAME_TIMER(&iVar12);
    switch (l_U94)
    {
        case 1:
        sub_10452(&l_U84, l_U86, l_U85, 0.01000000, l_U87, 1065353216);
        SET_FOLLOW_PED_PITCH_LIMIT_DOWN(l_U84);
        break;
        case 3:
        GET_CAM_POS(l_U69, &uVar13.fX, &uVar13.fY, &uVar13.fZ);
        if (NOT l_U41)
        {
            SET_CAM_POS(l_U69, uVar13.fX, uVar13.fY, uVar13.fZ - 0.05000000);
        }
        GET_CAM_FOV(l_U69, &fVar11);
        if ((fVar11 > 15.00000000) AND (VDIST2(uVar13.fX, uVar13.fY, uVar13.fZ, uParam0.fX, uParam0.fY, uParam0.fZ) > 3000.00000000))
        {
            SET_CAM_FOV(l_U69, fVar11 - 1.00000000);
        }
        sub_13524(uVar13, CVector3(), 0.00000000, 0.00000000, -1.00000000, 1.00000000, 0.05000000, 0.10000000);
        if ((iVar12 - l_U89) > 8000)
        {
            GET_CHAR_HEIGHT_ABOVE_GROUND(PARA_HANDLE, &fVar16);
            if (fVar16 > 150.00000000)
            {
                sub_5343(3, uParam0, uParam3);
            }
        }
        break;
        case 4:
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.05000000, 0.05000000, &uVar8);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.05000000, 0.05000000, &uVar9);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.05000000, 0.05000000, &uVar10);
        GET_CAM_POS(l_U69, &uVar13.fX, &uVar13.fY, &uVar13.fZ);
        l_U90.fX += uVar8;
        l_U90.fY += uVar9;
        l_U90.fZ += uVar10;
        if (NOT l_U41)
        {
            SET_CAM_POS(l_U69, uParam0.fX + l_U90.fX, uParam0.fY + l_U90.fY, uVar13.fZ - 0.50000000);
        }
        sub_13524(l_U90, CVector3(), 0.00000000, 0.00000000, -0.50000000, 0.50000000, 0.05000000, 0.10000000);
        if ((iVar12 - l_U89) > 3000)
        {
            sub_5343(5, uParam0, uParam3);
        }
        break;
        case 5:
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.05000000, 0.05000000, &uVar9);
        GENERATE_RANDOM_FLOAT_IN_RANGE(-0.05000000, 0.05000000, &uVar10);
        l_U90.fY += uVar9;
        l_U90.fZ += uVar10;
        SET_CAM_ATTACH_OFFSET(l_U69, l_U90.fX, l_U90.fY, l_U90.fZ);
        sub_13524(l_U90, CVector3(), 0.00000000, 0.00000000, -0.25000000, 0.25000000, 0.05000000, 0.10000000);
        if ((iVar12 - l_U89) > 4000)
        {
            sub_5343(4, uParam0, uParam3);
        }
        break;
        case 6:
        GET_CAM_POS(l_U69, &uVar13.fX, &uVar13.fY, &uVar13.fZ);
        if (NOT l_U41)
        {
            SET_CAM_POS(l_U69, uVar13.fX, uVar13.fY, uVar13.fZ - 0.05000000);
        }
        GET_CAM_FOV(l_U69, &fVar11);
        if ((fVar11 > 15.00000000) AND ((VDIST2(uVar13.fX, uVar13.fY, uVar13.fZ, uParam0.fX, uParam0.fY, uParam0.fZ)) > 3000.00000000))
        {
            SET_CAM_FOV(l_U69, fVar11 - 1.00000000);
        }
        sub_13524(uVar13, CVector3(), 0.00000000, 0.00000000, -1.00000000, 1.00000000, 0.05000000, 0.10000000);
        if ((iVar12 - l_U89) > 8000)
        {
            sub_5343(6, uParam0, uParam3);
        }
        break;
    }
    return;
}

void sub_9868()
{
    CVector3 uVar2;
    unknown uVar3;
    unknown uVar4;
    CVector3 uVar5;
    unknown uVar6;
    unknown uVar7;
    float fVar8;
    float uVar9;
    float fVar10;
    unsigned int iVar11;
    int iVar12;
    int iVar13;
    float uVar14;
    CVector3 uVar15;
    unknown uVar16;
    unknown uVar17;
    float fVar18;
    float fVar19;
    float fVar20;
    unsigned int iVar21;
    int iVar22;

    iVar12 = 0;
    GET_FRAME_TIME(&uVar9);
    GET_GAME_TIMER(&iVar11);
    if (l_U30 == 0)
    {
        l_U30 = iVar11;
    }
    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        GET_CHAR_COORDINATES(PARA_HANDLE, &uVar5.fX, &uVar5.fY, &uVar5.fZ);
        GET_CHAR_VELOCITY(PARA_HANDLE, &uVar2.fX, &uVar2.fY, &uVar2.fZ);
        GET_CHAR_HEIGHT_ABOVE_GROUND(PARA_HANDLE, &fVar8);
    }
    iVar13 = 0;
    if (((ABSF(uVar2.fZ - l_U46)) > 10.00000000) AND (uVar2.fZ > -5.00000000))
    {
        iVar13 = 1;
    }
    fVar10 = -10.00000000;
    if (WAS_PED_SKELETON_UPDATED(PARA_HANDLE))
    {
        GET_PED_BONE_POSITION(PARA_HANDLE, 1205, 0.00000000, 0.00000000, 0.00000000, &uVar15);
        GET_GROUND_Z_FOR_3D_COORD(uVar15.fX, uVar15.fY, uVar15.fZ + 100.00000000, &uVar14);
        fVar10 = uVar15.fZ - uVar14;
    }
    if ((fVar10 < 1.00000000) AND (fVar10 != -10.00000000))
    {
        iVar12 = 1;
    }
    if (true)
    {
        if (l_U23 < 0)
        {
            sub_10238(&l_U46, -60.00000000 - (((TO_FLOAT(l_U23)) / 128.00000000) * (-80.00000000 - -60.00000000)), 0.40000000);
            sub_10238(&l_U45, 1.00000000 - (((TO_FLOAT(l_U23)) / 128.00000000) * (25.00000000 - 1.00000000)), 0.40000000);
            sub_10452(&g_U2692[0]._fU36.fX, ((TO_FLOAT(l_U23)) / 128.00000000) * 45.00000000, 45.00000000, 0.05000000, 2.50000000, 1065353216);
        }
        else if (l_U23 > 0)
        {
            sub_10238(&l_U46, -60.00000000 - (((TO_FLOAT(l_U23)) / 128.00000000) * (-60.00000000 - -50.00000000)), 0.40000000);
            sub_10238(&l_U45, 1.00000000, 0.30000000);
            sub_10452(&g_U2692[0]._fU36.fX, 0.00000000, 45.00000000, 0.05000000, 2.50000000, 1065353216);
        }
        else
        {
            sub_10238(&l_U46, -60.00000000, 0.40000000);
            sub_10238(&l_U45, 1.00000000, 0.30000000);
            sub_10452(&g_U2692[0]._fU36.fX, 0.00000000, 45.00000000, 0.05000000, 2.50000000, 1065353216);
        }
        fVar18 = (TO_FLOAT(l_U22)) / 128.00000000;
        sub_10238(&l_U48, -fVar18 * 1.25000000, 0.10000000);
        g_U2692[0]._fU36.fZ += (l_U48 * uVar9) * 30.00000000;
        if (g_U2692[0]._fU36.fZ > 180)
        {
            g_U2692[0]._fU36.fZ -= 360;
        }
        else if (g_U2692[0]._fU36.fZ < 65356)
        {
            g_U2692[0]._fU36.fZ += 360;
        }
        sub_10452(&g_U2692[0]._fU36.fY, (fVar18 * 45.00000000) / 2.00000000, 45.00000000, 0.05000000, 2.50000000, 1065353216);
        if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
        {
            if (NOT (IS_PED_RAGDOLL(PARA_HANDLE)))
            {
                if (NOT g_U2797)
                {
                    if (l_U23 < 65416)
                    {
                        if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall_Fast")))
                        {
                            TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall_Fast", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                        }
                    }
                    else if (l_U23 > 120)
                    {
                        if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "free_fall_deccelerate")))
                        {
                            TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "free_fall_deccelerate", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                        }
                    }
                    else if (l_U22 > 10)
                    {
                        if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall_Veer_Right")))
                        {
                            TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall_Veer_Right", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                        }
                    }
                    else if (l_U22 < -10)
                    {
                        if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall_Veer_left")))
                        {
                            TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall_Veer_Left", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                        }
                    }
                    else if (((ABSI(l_U27)) < 10) AND ((ABSI(l_U26)) < 10))
                    {
                        if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall")))
                        {
                            TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                        }
                    }
                }
                else if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Free_Fall")))
                {
                    TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Free_Fall", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                }
            }
        }
        if ((IS_PLAYER_CONTROL_ON(sub_8507())) AND ((IS_CONTROL_JUST_PRESSED(0, 137)) || (IS_CONTROL_JUST_PRESSED(0, 1))))
        {
            if ((iVar11 - l_U30) > 500)
            {
                TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Open_chute", "PARACHUTE", 10.00000000, 0, 1, 1, 0, 0);
                CLEAR_HELP();
                l_U57 = fVar8;
                g_U2692[0]._fU64 = 1;
            }
        }
    }
    else
    {
        sub_11913(uVar5);
    }

    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        fVar19 = (l_U46 / -80.00000000) * 1.25000000;
        if (fVar19 < 0.10000000)
        {
            fVar19 = 0.10000000;
        }
        else if (fVar19 > 0.20000000)
        {
            fVar19 = 0.20000000;
        }
        SET_PED_WINDY_CLOTHING_SCALE(PARA_HANDLE, fVar19);
    }
    sub_13051(g_U2692[0].fY, uVar5, uVar2);
    sub_13224(uVar5, uVar2);
    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        if ((uVar5.fZ < -2.00000000) || (IS_CHAR_IN_WATER(PARA_HANDLE)))
        {
            CLEAR_CHAR_TASKS_IMMEDIATELY(PARA_HANDLE);
            SET_CHAR_HEADING(PARA_HANDLE, g_U2692[0]._fU36.fZ);
            l_U46 /= 20.00000000;
            SHAKE_PAD(0, 200, 255);
            if (g_U2692[0]._fU64)
            {
                Switch(0);
            }
            else
            {
                Switch(1);
            }
        }
    }
    sub_10238(&l_U47, 0.00000000, 0.30000000 * 2.00000000);
    sub_6947();
    if ((((l_U55 - uVar5.fZ) > 5.00000000) AND (uVar2.fZ > -1.00000000)) || ((iVar13) AND ((iVar12) || (fVar8 < 2.00000000))))
    {
        fVar20 = l_U55 - uVar5.fZ;
        if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
        {
            SET_CHAR_HEADING(PARA_HANDLE, g_U2692[0]._fU36.fZ);
            SET_CHAR_VELOCITY(PARA_HANDLE, l_U45 * (-SIN(g_U2692[0]._fU36.fZ)), l_U45 * (COS(g_U2692[0]._fU36.fZ)), l_U46);
            GET_CHAR_HEALTH(PARA_HANDLE, &iVar21);
            iVar22 = ROUND((100.00000000 * (fVar20 - 5.00000000)) / 25.00000000);
            iVar21 -= iVar22;
            if (iVar21 < 10)
            {
                iVar21 = 0;
            }
            UNLOCK_RAGDOLL(PARA_HANDLE, 1);
            if (iVar21 > 0)
            {
                CLEAR_CHAR_TASKS_IMMEDIATELY(PARA_HANDLE);
                SWITCH_PED_TO_RAGDOLL(PARA_HANDLE, 1, 2000, 2, 0, 1, 0);
                l_U44 = 1;
            }
            PLAY_SOUND_FROM_PED(-1, "PARACHUTE_SPLAT", PARA_HANDLE);
            SET_CHAR_HEALTH(PARA_HANDLE, iVar21);
            sub_5343(0, CVector3(), CVector3(), 0.00000000, CVector3(), 0.00000000, 0.00000000);
            l_U29 = 0;
            g_U2692[0].fY = 8;
        }
        SHAKE_PAD(0, 200, 255);
    }
    return;
}

void sub_15703()
{
    float fVar2;
    CVector3 uVar3;
    unknown uVar4;
    unknown uVar5;
    CVector3 uVar6;
    unknown uVar7;
    unknown uVar8;
    unsigned int iVar9;
    boolean bVar10;
    boolean bVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    float fVar18;
    float uVar19;
    unknown uVar20;
    float fVar21;
    float fVar22;
    float fVar23;
    unknown uVar24;
    unsigned int iVar25;
    boolean bVar26;
    boolean bVar27;
    float fVar28;
    float fVar29;
    float fVar30;
    float fVar31;
    float fVar32;
    float fVar33;

    GET_GAME_TIMER(&iVar9);
    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        GET_CHAR_COORDINATES(PARA_HANDLE, &uVar3.fX, &uVar3.fY, &uVar3.fZ);
        if ((uVar3.fZ < 0.00000000) || (IS_CHAR_IN_WATER(PARA_HANDLE)))
        {
            PLAY_SOUND_FROM_PED(-1, "PARACHUTE_LAND_WATER", PARA_HANDLE);
            CLEAR_CHAR_TASKS_IMMEDIATELY(PARA_HANDLE);
            SET_CHAR_HEADING(PARA_HANDLE, g_U2692[0]._fU36.fZ);
            Switch(0);
            return;
        }
        GET_CHAR_VELOCITY(PARA_HANDLE, &uVar6.fX, &uVar6.fY, &uVar6.fZ);
        GET_CHAR_HEIGHT_ABOVE_GROUND(PARA_HANDLE, &fVar2);
    }
    bVar10 = false;
    bVar11 = false;
    if (((ABSF(uVar6.fZ - l_U46)) > 3.00000000) AND (uVar6.fZ > -1.00000000))
    {
        bVar10 = true;
    }
    if ((l_U45 - (VMAG(uVar6.fX, uVar6.fY, 0.00000000))) > 5.00000000)
    {
        bVar11 = true;
    }
    fVar12 = (TO_FLOAT(l_U25 - l_U24)) / 255.00000000;
    fVar13 = (TO_FLOAT(l_U22)) / 128.00000000;
    fVar14 = ((fVar12 * 1.10000000) + (fVar13 * 0.90000000)) / 2.00000000;
    sub_10238(&l_U47, 0.00000000, 0.30000000);
    GET_FRAME_TIME(&uVar19);
    fVar15 = fVar14 * 0.40000000;
    fVar16 = (g_U2692[0]._fU36.fY / 75.00000000) * 0.40000000;
    fVar17 = l_U95 * 0.10000000;
    fVar18 = (fVar15 - fVar16) - fVar17;
    l_U95 += fVar18;
    g_U2692[0]._fU36.fY += (l_U95 * uVar19) * 30.00000000;
    l_U48 = (g_U2692[0]._fU36.fY / 75.00000000) * 4.50000000;
    if ((l_U24 == 255) AND (l_U25 == 255))
    {
        sub_10238(&l_U46, -5.50000000, 0.25000000);
        sub_10238(&l_U45, 3.50000000, 0.30000000);
        sub_10452(&g_U2692[0]._fU36.fX, 20.00000000 / 2.00000000, 20.00000000 * 2.00000000, 0.05000000, 2.50000000, 1065353216);
        l_U59 = -7.00000000 - l_U46;
        l_U60 = 13.00000000 - l_U45;
        l_U61 = g_U2692[0]._fU36.fX;
    }
    else
    {
        sub_10238(&l_U59, 0.00000000, 0.25000000);
        sub_10238(&l_U60, 0.00000000, 0.30000000);
        sub_10452(&l_U61, 0.00000000, 20.00000000 * 2.00000000, 0.05000000, 2.50000000, 1065353216);
        fVar15 = (l_U23 / 128.00000000) * 0.30000000;
        fVar16 = (g_U2692[0]._fU36.fX / 20.00000000) * 0.30000000;
        fVar17 = l_U96 * 0.15000000;
        fVar18 = (fVar15 - fVar16) - fVar17;
        l_U96 += fVar18;
        g_U2692[0]._fU36.fX += (l_U96 * uVar19) * 30.00000000;
        uVar20 = ABSF(g_U2692[0]._fU36.fX / 20.00000000);
        if (g_U2692[0]._fU36.fX < 0.00000000)
        {
            l_U46 = -7.00000000 - (uVar20 * (-7.00000000 - -12.00000000));
            l_U45 = 13.00000000 - (uVar20 * (13.00000000 - 10.00000000));
        }
        else if (g_U2692[0]._fU36.fX > 0.00000000)
        {
            l_U46 = -7.00000000 - (uVar20 * (-7.00000000 - -4.50000000));
            l_U45 = 13.00000000 - (uVar20 * (13.00000000 - 14.00000000));
        }
        else
        {
            l_U46 = -7.00000000;
            l_U45 = 13.00000000;
        }
        l_U46 -= l_U59;
        l_U45 -= l_U60;
    }
    fVar21 = 75.00000000 * 0.60000000;
    if ((ABSF(g_U2692[0]._fU36.fY)) > fVar21)
    {
        fVar22 = ((ABSF(g_U2692[0]._fU36.fY)) - fVar21) / (75.00000000 - fVar21);
        l_U46 -= fVar22 * (-7.00000000 - -20.00000000);
        l_U45 -= fVar22 * (13.00000000 - 10.00000000);
        if (l_U46 < -20.00000000)
        {
            l_U46 = -20.00000000;
        }
        if (l_U45 < 3.50000000)
        {
            l_U45 = 3.50000000;
        }
    }
    if ((ABSF(l_U48)) > (4.50000000 * 0.95000000))
    {
        if (l_U62 == 0)
        {
            GET_GAME_TIMER(&l_U62);
        }
        if ((iVar9 - l_U62) > 1500)
        {
            if (l_U94 != 3)
            {
                sub_5343(3, uVar3, uVar6);
                l_U63 = 0;
            }
        }
    }
    else if (l_U94 == 3)
    {
        if (l_U63 == 0)
        {
            GET_GAME_TIMER(&l_U63);
        }
        if ((iVar9 - l_U63) > 1000)
        {
            sub_5343(0, uVar3, uVar6);
            l_U88 = 0;
        }
    }
    l_U62 = 0;
    g_U2692[0]._fU36.fZ -= (l_U48 * uVar19) * 30.00000000;
    if (g_U2692[0]._fU36.fZ > 180)
    {
        g_U2692[0]._fU36.fZ -= 360;
    }
    else if (g_U2692[0]._fU36.fZ < 65356)
    {
        g_U2692[0]._fU36.fZ += 360;
    }
    if (l_U94 != 3)
    {
        sub_13051(g_U2692[0].fY, uVar3, uVar6);
    }
    if (l_U94 == 0)
    {
        if (l_U46 > -7.00000000)
        {
            sub_5343(1, uVar3, uVar6);
        }
        else if (l_U46 < -7.00000000)
        {
            sub_5343(2, uVar3, uVar6);
        }
    }
    else if (l_U94 == 1)
    {
        if (l_U46 <= -7.00000000)
        {
            sub_5343(0, uVar3, uVar6);
        }
    }
    else if (l_U94 == 2)
    {
        if (l_U46 >= -7.00000000)
        {
            sub_5343(0, uVar3, uVar6);
        }
    }
    sub_13224(uVar3, uVar6);
    SET_VARIABLE_ON_SOUND(l_U28, "Velocity", 0.50000000 + (((l_U46 - -5.50000000) / (-20.00000000 - -5.50000000)) * 0.50000000));
    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        fVar23 = (l_U46 / -20.00000000) * 1.40000000;
        if (fVar23 > 1.00000000)
        {
            fVar23 = 1.00000000;
        }
        else if (fVar23 < 0.70000000)
        {
            fVar23 = 0.70000000;
        }
        SET_PED_WINDY_CLOTHING_SCALE(PARA_HANDLE, fVar23);
    }
    sub_6947();
    if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
    {
        uVar24 = GET_CLOSEST_CAR(uVar3.fX, uVar3.fY, uVar3.fZ, 5.00000000, 0, 127);
        if ((bVar10) || (fVar2 < 1.20000000))
        {
            GET_CHAR_HEALTH(PARA_HANDLE, &iVar25);
            SET_CHAR_VELOCITY(PARA_HANDLE, uVar6.fX / 2.00000000, uVar6.fY / 2.00000000, uVar6.fZ);
            CLEAR_CHAR_SECONDARY_TASK(PARA_HANDLE);
            TASK_PLAY_ANIM_WITH_FLAGS_AND_START_PHASE(PARA_HANDLE, "Land_Fast", "PARACHUTE", 4.00000000, 0, 3328, 0.80000000);
            STOP_SOUND(l_U28);
            RELEASE_SOUND_ID(l_U28);
            l_U28 = -1;
            if (DOES_OBJECT_EXIST(l_U21))
            {
                DETACH_OBJECT(l_U21, 1);
                SET_OBJECT_COLLISION(l_U21, 0);
                SET_OBJECT_DYNAMIC(l_U21, 1);
                PLAY_OBJECT_ANIM(l_U21, "obj_crumple", "PARACHUTE", 8.00000000, 0, 1);
            }
            PLAY_SOUND_FROM_PED(-1, "PARACHUTE_LAND", PARA_HANDLE);
            bVar26 = false;
            bVar27 = false;
            if (DOES_VEHICLE_EXIST(uVar24))
            {
                if (bVar10)
                {
                    if (IS_VEH_DRIVEABLE(uVar24))
                    {
                        GET_CAR_SPEED(uVar24, &fVar28);
                        if ((NOT g_U2789) AND ((fVar2 > 1.00000000) AND (fVar28 > 2.00000000)))
                        {
                            bVar26 = true;
                        }
                    }
                }
            }
            if (((((NOT (DOES_VEHICLE_EXIST(uVar24))) AND (g_U2789)) || (NOT g_U2789)) AND (l_U46 < (-12.00000000 * 1.10000000))) || ((ABSF(g_U2692[0]._fU36.fY)) > 30.00000000))
            {
                bVar26 = true;
            }
            if (l_U46 < -12.00000000)
            {
                if (uVar3.fZ > 1.20000000)
                {
                    bVar27 = true;
                }
            }
            if (bVar26)
            {
                if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
                {
                    SET_CHAR_INVINCIBLE(PARA_HANDLE, 1);
                    UNLOCK_RAGDOLL(PARA_HANDLE, 1);
                    CLEAR_CHAR_TASKS_IMMEDIATELY(PARA_HANDLE);
                    SWITCH_PED_TO_RAGDOLL(PARA_HANDLE, 500, 2000, 2, 0, 1, 0);
                }
                if (bVar27)
                {
                    iVar25 -= FLOOR((-12.00000000 - l_U46) * 10.00000000);
                    if (iVar25 < 0)
                    {
                        iVar25 = 0;
                    }
                    SET_CHAR_HEALTH(PARA_HANDLE, iVar25);
                }
            }
            else
            {
                SET_CHAR_HEADING(PARA_HANDLE, g_U2692[0]._fU36.fZ);
                if (g_U2785)
                {
                    if ((l_U45 < 13.00000000) AND (l_U46 >= -5.50000000))
                    {
                        if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land_Safe")))
                        {
                            TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Land_Safe", "PARACHUTE", 4.00000000, 0, 1, 1, 0, 0);
                            TASK_PLAY_ANIM_WITH_FLAGS(PARA_HANDLE, "Land_Safe", "PARACHUTE", 4.00000000, 0, 3328);
                        }
                    }
                    else if (l_U46 >= (-7.00000000 - 2.00000000))
                    {
                        if ((uVar3.fZ > 1.20000000) || ((fVar2 < 1.50000000) AND ((fVar2 != uVar3.fZ) AND (uVar3.fZ <= 1.20000000))))
                        {
                            if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land")))
                            {
                                TASK_PLAY_ANIM(PARA_HANDLE, "Land", "PARACHUTE", 4.00000000, 0, 1, 1, 0, 0);
                            }
                        }
                    }
                    else if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land_Fast")))
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Land_Fast", "PARACHUTE", 4.00000000, 0, 1, 1, 0, 0);
                    };;;
                }
                else if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land_Safe")))
                {
                    TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Land_Safe", "PARACHUTE", 4.00000000, 0, 1, 1, 0, 0);
                    TASK_PLAY_ANIM_WITH_FLAGS(PARA_HANDLE, "Land_Safe", "PARACHUTE", 4.00000000, 0, 3328);
                }
            }
            if (iVar25 >= 100)
            {
                if (NOT bVar26)
                {
                    fVar29 = GET_FLOAT_STAT(208);
                    if (((fVar29 == 0.00000000) || (l_U57 < fVar29)) AND (l_U57 != 0.00000000))
                    {
                        SET_FLOAT_STAT(208, l_U57);
                    }
                }
                sub_5343(0, CVector3(), CVector3(), 0.00000000, CVector3(), 0.00000000, 0.00000000);
                g_U2692[0].fY = 7;
            }
            else
            {
                Switch(0);
            }
        }
        else if (NOT (IS_PED_RAGDOLL(PARA_HANDLE)))
        {
            fVar30 = ABSF(ATAN2(TO_FLOAT(l_U22), TO_FLOAT(l_U23)));
            fVar31 = TO_FLOAT((l_U22 * l_U22) + (l_U23 * l_U23));
            fVar32 = g_U2692[0]._fU36.fY / 45.00000000;
            fVar33 = g_U2692[0]._fU36.fX / 20.00000000;
            if (NOT g_U2797)
            {
                if ((fVar33 < -0.20000000) AND ((fVar31 > 10000.00000000) AND (fVar30 > 100.00000000)))
                {
                    if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Accelerate_Loop")))
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Accelerate_Loop", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                    }
                }
                else if ((fVar33 > 0.20000000) AND ((fVar31 > 10000.00000000) AND (fVar30 < 80.00000000)))
                {
                    if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "deccelerate")))
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "deccelerate", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                    }
                }
                else if ((l_U22 > 20) AND (fVar32 > 0.85000000))
                {
                    if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Steer_R")))
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Steer_R", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                    }
                }
                else if ((l_U22 < 65516) AND (fVar32 < -0.85000000))
                {
                    if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Steer_L")))
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Steer_L", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                    }
                }
                else if ((l_U22 > 20) AND (fVar32 > 0.20000000))
                {
                    if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Steer_R_less")))
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Steer_R_less", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                    }
                }
                else if ((l_U22 < 65516) AND (fVar32 < -0.20000000))
                {
                    if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Steer_L_less")))
                    {
                        TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Steer_L_less", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                    }
                }
                else if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Hang_Idle")))
                {
                    TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Hang_Idle", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
                };;;;;;;
            }
            else if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Hang_Idle")))
            {
                TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Hang_Idle", "PARACHUTE", 4.00000000, 1, 1, 1, 0, 0);
            }
            if ((l_U24 == 255) AND (l_U25 == 255))
            {
                if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Full_Brake_Loop")))
                {
                    TASK_PLAY_ANIM_WITH_FLAGS(PARA_HANDLE, "Full_Brake_Loop", "PARACHUTE", 4.00000000, 0, 3344);
                }
                if (DOES_OBJECT_EXIST(l_U21))
                {
                    if (l_U46 < (-12.00000000 * 0.80000000))
                    {
                        if (NOT (IS_OBJECT_PLAYING_ANIM(l_U21, "obj_wind_high", "PARACHUTE")))
                        {
                            PLAY_OBJECT_ANIM(l_U21, "obj_wind_high", "PARACHUTE", 4.00000000, 1, 0);
                        }
                    }
                    else if (l_U46 >= -7.00000000)
                    {
                        if (NOT (IS_OBJECT_PLAYING_ANIM(l_U21, "obj_wind_low", "PARACHUTE")))
                        {
                            PLAY_OBJECT_ANIM(l_U21, "obj_wind_low", "PARACHUTE", 4.00000000, 1, 0);
                        }
                    }
                }
            }
            else if ((l_U25 > 10) AND (fVar32 > 0.20000000))
            {
                if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Steer_AB_R")))
                {
                    TASK_PLAY_ANIM_WITH_FLAGS(PARA_HANDLE, "Steer_AB_R", "PARACHUTE", 4.00000000, 0, 3344);
                }
            }
            else if ((l_U24 > 10) AND (fVar32 < -0.20000000))
            {
                if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Steer_AB_L")))
                {
                    TASK_PLAY_ANIM_WITH_FLAGS(PARA_HANDLE, "Steer_AB_L", "PARACHUTE", 4.00000000, 0, 3344);
                }
            }
            else if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Hang_Idle2")))
            {
                TASK_PLAY_ANIM_WITH_FLAGS(PARA_HANDLE, "Hang_Idle2", "PARACHUTE", 4.00000000, 0, 3344);
            }
            if (DOES_OBJECT_EXIST(l_U21))
            {
                if (l_U46 < (-12.00000000 * 0.80000000))
                {
                    if (NOT (IS_OBJECT_PLAYING_ANIM(l_U21, "obj_wind_high", "PARACHUTE")))
                    {
                        PLAY_OBJECT_ANIM(l_U21, "obj_wind_high", "PARACHUTE", 4.00000000, 1, 0);
                    }
                }
                else if (l_U46 >= -7.00000000)
                {
                    if (NOT (IS_OBJECT_PLAYING_ANIM(l_U21, "obj_wind_low", "PARACHUTE")))
                    {
                        PLAY_OBJECT_ANIM(l_U21, "obj_wind_low", "PARACHUTE", 4.00000000, 1, 0);
                    }
                }
            }
        }
        if (((bVar11) AND (fVar2 > 3.00000000)) || ((IS_CONTROL_JUST_PRESSED(2, 3)) || (IS_BUTTON_JUST_PRESSED(0, 15))))
        {
            STOP_SOUND(l_U28);
            RELEASE_SOUND_ID(l_U28);
            l_U28 = -1;
            if (bVar11)
            {
                if (l_U46 < -12.00000000)
                {
                    PLAY_SOUND_FROM_PED(-1, "PARACHUTE_PED_HIT_BUILDING_FAST", PARA_HANDLE);
                }
                else if (l_U46 <= -7.00000000)
                {
                    PLAY_SOUND_FROM_PED(-1, "PARACHUTE_PED_HIT_BUILDING_MED", PARA_HANDLE);
                }
                else
                {
                    PLAY_SOUND_FROM_PED(-1, "PARACHUTE_PED_HIT_BUILDING_SLOW", PARA_HANDLE);
                }
            }
            PLAY_SOUND_FROM_PED(-1, "PARACHUTE_UNCLIP", PARA_HANDLE);
            UNLOCK_RAGDOLL(PARA_HANDLE, 1);
            if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
            {
                SET_CHAR_INVINCIBLE(PARA_HANDLE, 1);
                CLEAR_CHAR_TASKS_IMMEDIATELY(PARA_HANDLE);
                SWITCH_PED_TO_RAGDOLL(PARA_HANDLE, 1, 100, 1, 0, 1, 1);
                CREATE_NM_MESSAGE(1, 246);
                SEND_NM_MESSAGE(PARA_HANDLE);
            }
            if (DOES_OBJECT_EXIST(l_U21))
            {
                DETACH_OBJECT(l_U21, 1);
                SET_OBJECT_COLLISION(l_U21, 0);
                SET_OBJECT_DYNAMIC(l_U21, 1);
                PLAY_OBJECT_ANIM(l_U21, "obj_crumple", "PARACHUTE", 8.00000000, 0, 1);
            }
            sub_5343(0, CVector3(), CVector3(), 0.00000000, CVector3(), 0.00000000, 0.00000000);
            g_U2692[0].fY = 8;
            GET_GAME_TIMER(&l_U29);
        }
    }
    return;
}

int sub_2629(int iParam0)
{
    int Result;

    if (iParam0 == NULL)
    {
        return -1;
    }
    Result = 0;
    for (Result = 0; Result < 5; Result++)
    {
        if (NOT (g_U9105[Result].fX == -1))
        {
            if (iParam0 == g_U9105[Result].fY)
            {
                return Result;
            }
        }
    }
    return -1;
}

int sub_2604(int iParam0)
{
    if (iParam0 == NULL)
    {
        return 0;
    }
    if ((sub_2629(iParam0)) == -1)
    {
        return 0;
    }
    return 1;
}

void Para_Main()
{
	Reset();
	while (true)
	{
		Sleep(0);
		if (!IS_CHAR_INJURED(PARA_HANDLE))
		{
			g_pCore->GetGame()->GetLocalPlayer()->GetPosition(uVar9);
			//GET_CHAR_COORDINATES(PARA_HANDLE, &uVar9.fX, &uVar9.fY, &uVar9.fZ);
		}
		if(!l_U34)
		{
			if (REQUEST_AMBIENT_AUDIO_BANK("EP2_SFX\\PARACHUTE"))
			{
				l_U34 = 1;
			}
		}
		if ((IS_CHAR_INJURED(PARA_HANDLE)))
		{
			Switch(0);
		}
		if (NOT(IS_CHAR_INJURED(PARA_HANDLE)))
		{
			if (IS_CHAR_IN_ANY_CAR(PARA_HANDLE))
			{
				Switch(0);
			}
		}
		if (NOT(IS_CHAR_INJURED(PARA_HANDLE)))
		{
			//DISABLE_INTERMEZZO_CAMS();

			if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
			{
				GET_POSITION_OF_ANALOGUE_STICKS(0, &l_U22, &l_U23, &uVar13, &uVar14);
				if (USING_STANDARD_CONTROLS())
				{
					l_U24 = GET_CONTROL_VALUE(0, 6);
					l_U25 = GET_CONTROL_VALUE(0, 4);
				}
				else
				{
					l_U24 = GET_CONTROL_VALUE(0, 4);
					l_U25 = GET_CONTROL_VALUE(0, 6);
				}
				if (NOT IS_USING_CONTROLLER())
				{
					l_U24 = GET_CONTROL_VALUE(0, 137);
					l_U25 = GET_CONTROL_VALUE(0, 138);
					GET_KEYBOARD_MOVE_INPUT(l_U22, l_U23);
				}

				switch((int)g_U2692[0].fY)
				{
				case 0:
					{
						if(NOT(IS_CHAR_IN_ANY_CAR(PARA_HANDLE)))
						{
							if(NOT(IS_CHAR_ON_FIRE(PARA_HANDLE)) && NOT(IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "CLIMG_STD", "Ladder_Slide")))
							{
								GET_CHAR_HEIGHT_ABOVE_GROUND(PARA_HANDLE, &fVar2);
								if(NOT l_U36)
								{
									sub_2781();
								}

								if((l_U20 == 1) || ((lU36) || (((fVar2 > 4.000000000) && (g_U2784)) || (fVar2 > 20.00000000))))
								{
									if(NOT(IS_CHAR_ON_FIRE(PARA_HANDLE)))
									{
										GET_CHAR_VELOCITY(PARA_HANDLE, &uVar3.fX, &uVar3.fY, &uVar3.fZ);
										if((l_U20 == 1) || (l_U36))
										{
											l_U37 = 1;
											sub_4486(uVar3);
										}
										else if(uVar3.fZ< -4.0000000)
										{
											l_U37 = 0;
											sub_4486(uVar3);
										}
									}
									else
									{
										SWITCH_PED_TO_RAGDOLL(PARA_HANDLE, 500, 2000, 2, 0, 1, 0);
										GET_GAME_TIMER(&l_U29);
										g_U2692[0].fY = 8;
									}
								}
							}
						}
						else
						{
							l_U38 = 0;
							l_U64 = 0;
							g_U2692[0].fY = 1;
						}
						break;
					}
				case 1:
					{
						if(NOT l_U34)
						{
							if(((g_U2794) && ((IS_PLAYER_CONTROL_ON(sub_8507())) && (IS_CHAR_IN_ANY_HELI(PARA_HANDLE)))))
							{
								if (IS_CONTROL_JUST_PRESSED(2, 43))
								{
									GET_CHAR_HEIGHT_ABOVE_GROUND(PARA_HANDLE, &fVar2);
									if (fVar2 > 25.00000000)
									{
										l_U43 = 0;
										STORE_CAR_CHAR_IS_IN_NO_SAVE(PARA_HANDLE, l_U70);
										if (NOT (IS_CAR_A_MISSION_CAR(l_U70)))
										{
											SET_CAR_AS_MISSION_CAR(l_U70);
										}
										else
										{
											l_U43 = 1;
										}
										GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(l_U70, 0.00000000, -1.00000000, 0.20000000, &uVar15.fX, &uVar15.fY, &uVar15.fZ);
										GET_CHAR_HEADING(PARA_HANDLE, &l_U58);
										SET_CHAR_COLLISION(PARA_HANDLE, 0);
										SET_CHAR_VISIBLE(PARA_HANDLE, 0);
										WARP_CHAR_FROM_CAR_TO_COORD(PARA_HANDLE, uVar15.fX, uVar15.fY, uVar15.fZ);
										ATTACH_PED_TO_CAR(PARA_HANDLE, l_U70, 0, -1.00000000, 0.90000000, 0.60000000, 0.00000000, 0.00000000, 0, 0);
										OPEN_SEQUENCE_TASK(&l_U66);
										TASK_PLAY_ANIM_WITH_FLAGS(0, "jump_out_ds", "PARACHUTE", 1000.00000000, 0, 64);
										TASK_PLAY_ANIM_NON_INTERRUPTABLE(0, "Free_Fall", "PARACHUTE", 1000.00000000, 1, 1, 1, 0, 0);
										CLOSE_SEQUENCE_TASK(l_U66);
										TASK_PERFORM_SEQUENCE(PARA_HANDLE, l_U66);
										CLEAR_SEQUENCE_TASK(l_U66);
										l_U38 = 1;
										g_U2802 = 1;
									}
								}
							}
						}
						if(NOT l_U42)
						{
							if ((NOT (sub_2604(PARA_HANDLE))) AND ((IS_CONTROL_JUST_PRESSED(2, 43)) AND (IS_CHAR_ON_ANY_BIKE(PARA_HANDLE))))
							{
								l_U43 = 0;
								STORE_CAR_CHAR_IS_IN_NO_SAVE(PARA_HANDLE, l_U70);
								if (NOT (IS_CAR_A_MISSION_CAR(l_U70)))
								{
									SET_CAR_AS_MISSION_CAR(l_U70);
								}
								else
								{
									l_U43 = 1;
								}
								if ((IS_CAR_IN_AIR_PROPER(l_U70)) AND (IS_VEH_DRIVEABLE(l_U70)))
								{
									GET_CHAR_HEIGHT_ABOVE_GROUND(PARA_HANDLE, &fVar23);
									if (fVar23 > 20.00000000)
									{
										GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(PARA_HANDLE, 0.00000000, 0.00000000, -0.50000000, &uVar18.fX, &uVar18.fY, &uVar18.fZ);
										if (WAS_PED_SKELETON_UPDATED(PARA_HANDLE))
										{
											GET_PED_BONE_POSITION(PARA_HANDLE, 0, -0.50000000, 0.00000000, 0.00000000, &uVar18);
										}
										else
										{
											GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(PARA_HANDLE, 0.00000000, 0.00000000, -0.50000000, &uVar18.fX, &uVar18.fY, &uVar18.fZ);
										}
										GET_GROUND_Z_FOR_3D_COORD(uVar18.fX, uVar18.fY, uVar18.fZ, &uVar21);
										GET_CAR_SPEED_VECTOR(l_U70, &uVar3, 0);
										GET_CHAR_HEADING(PARA_HANDLE, &uVar22);
										WARP_CHAR_FROM_CAR_TO_COORD(PARA_HANDLE, uVar18.fX, uVar18.fY, uVar18.fZ - 0.50000000);
										SET_CHAR_HEADING(PARA_HANDLE, uVar22);
										l_U42 = 1;
										g_U2802 = 1;
										SET_CHAR_VELOCITY(PARA_HANDLE, uVar3.fX, uVar3.fY, uVar3.fZ);
										SET_CAR_COLLISION(l_U70, 0);
										SET_CHAR_COLLISION(PARA_HANDLE, 0);
										sub_4486(uVar3);
									}
								}
							}
						}
						else
						{
							sub_4486(uVar3);
						}
						if ((l_U20 == 1) || (l_U38))
						{
							if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "jump_out_ds"))
							{
								GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "PARACHUTE", "jump_out_ds", &fVar24);
								if ((fVar24 < 0.20000000) AND (fVar24 > 0.00000000))
								{
									if (NOT (IS_CHAR_VISIBLE(PARA_HANDLE)))
									{
										SET_CHAR_VISIBLE(PARA_HANDLE, 1);
									}
									if (IS_VEH_DRIVEABLE(l_U70))
									{
										CONTROL_CAR_DOOR(l_U70, 0, 0, fVar24 / 0.20000000);
									}
								}
							}
							GET_CHAR_VELOCITY(PARA_HANDLE, &uVar3.fX, &uVar3.fY, &uVar3.fZ);
							l_U37 = 1;
							sub_4486(uVar3);
						}
						else if ((l_U64 == 0) AND (NOT (IS_CHAR_IN_ANY_CAR(PARA_HANDLE))))
						{
							GET_GAME_TIMER(&l_U64);
						}
						if (l_U64 != 0)
						{
							GET_GAME_TIMER(&iVar12);
							if ((iVar12 - l_U64) > 1000)
							{
								g_U2692[0].fY = 0;
							}
						}
						break;
				case 2:
					if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
					{
						if (NOT (IS_CHAR_IN_ANY_CAR(PARA_HANDLE)))
						{
							GET_CHAR_VELOCITY(PARA_HANDLE, &uVar25.fX, &uVar25.fY, &uVar25.fZ);
							sub_4486(uVar25);
						}
						break;
					}
				case 3:
					{
						sub_9868();
						break;
					}
				case 4:
					if (NOT (IS_CHAR_INJURED(PARA_HANDLE)))
					{
						g_U2692[0]._fU36.fX = 0;
						g_U2692[0]._fU36.fY = 0;
						GET_CHAR_HEADING(PARA_HANDLE, &g_U2692[0]._fU36.fZ);
						GET_CHAR_VELOCITY(PARA_HANDLE, &uVar3.fX, &uVar3.fY, &uVar3.fZ);
						l_U45 = VMAG(uVar3.fX, uVar3.fY, 0.00000000);
						l_U48 = 0.00000000;
						l_U46 = uVar3.fZ;
						l_U95 = 0.00000000;
						CLEAR_CHAR_TASKS_IMMEDIATELY(PARA_HANDLE);
						SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(PARA_HANDLE, 1);
						sub_4940();
						sub_5343(0, CVector3(), CVector3(), 0.00000000, CVector3(), 0.00000000, 0.00000000);
						l_U33 = 1;
						GET_CURRENT_CHAR_WEAPON(PARA_HANDLE, &l_U93);
						GIVE_WEAPON_TO_CHAR(PARA_HANDLE, 0, 0, 1);
						BLOCK_PED_WEAPON_SWITCHING(PARA_HANDLE, 1);
						l_U28 = GET_SOUND_ID();
						PLAY_SOUND_FROM_PED(l_U28, "PARACHUTE_DESCEND", PARA_HANDLE);
						if (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Hang_Idle")))
						{
							TASK_PLAY_ANIM_NON_INTERRUPTABLE(PARA_HANDLE, "Hang_Idle", "PARACHUTE", 1000.00000000, 1, 1, 1, 0, 0);
						}
						if (NOT (DOES_OBJECT_EXIST(l_U21)))
						{
							CREATE_OBJECT(1490460832, uVar9.fX, uVar9.fY, uVar9.fZ + 2.00000000, &l_U21, 1);
							ATTACH_OBJECT_TO_PED(l_U21, PARA_HANDLE, 0, 0.02500000, -0.12500000, 5.45000000, 0.00000000, 0.00000000, 0.00000000, 1);
						}
						g_U2692[0].fY = 5;
					}
					break;
				case 5:
					sub_15703();
					break;
				case 7:
					if (DOES_OBJECT_EXIST(l_U21))
					{
						GET_OBJECT_COORDINATES(l_U21, &uVar6.fX, &uVar6.fY, &uVar6.fZ);
						SLIDE_OBJECT(l_U21, uVar6.fX, uVar6.fY, uVar6.fZ + 20.00000000, 0.00000000, 0.00000000, 0.40000000, 0);
						if (NOT (IS_OBJECT_PLAYING_ANIM(l_U21, "obj_crumple", "PARACHUTE")))
						{
							l_U65 += 10;
							if (l_U65 > 255)
							{
								l_U65 = 255;
							}
							SET_OBJECT_ALPHA(l_U21, 255 - l_U65);
							if (l_U65 >= 255)
							{
								DELETE_OBJECT(&l_U21);
							}
						}
					}
					if ((NOT (IS_CHAR_GETTING_UP(PARA_HANDLE))) AND ((NOT (IS_PED_RAGDOLL(PARA_HANDLE))) AND ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land_Fast"))) AND ((NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land_Safe"))) AND (NOT (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land")))))))
					{
						Switch(0);
					}
					if (IS_CHAR_PLAYING_ANIM(PARA_HANDLE, "PARACHUTE", "Land"))
					{
						GET_CHAR_ANIM_CURRENT_TIME(PARA_HANDLE, "PARACHUTE", "Land", &fVar28);
						if (fVar28 > 0.40000000)
						{
							if ((l_U23 != 0) || (l_U22 != 0))
							{
								CLEAR_CHAR_TASKS(PARA_HANDLE);
								CLEAR_CHAR_SECONDARY_TASK(PARA_HANDLE);
							}
						}
					}
					break;
				case 8:
					if (IS_HELP_MESSAGE_BEING_DISPLAYED())
					{
						CLEAR_HELP();
					}
					if (DOES_OBJECT_EXIST(l_U21))
					{
						GET_OBJECT_COORDINATES(l_U21, &uVar6.fX, &uVar6.fY, &uVar6.fZ);
						SLIDE_OBJECT(l_U21, uVar6.fX, uVar6.fY, uVar6.fZ + 20.00000000, 0.00000000, 0.00000000, 0.25000000, 0);
						if (NOT (IS_OBJECT_PLAYING_ANIM(l_U21, "obj_crumple", "PARACHUTE")))
						{
							l_U65 += 10;
							if (l_U65 > 255)
							{
								l_U65 = 255;
							}
							SET_OBJECT_ALPHA(l_U21, 255 - l_U65);
							if (l_U65 >= 255)
							{
								DELETE_OBJECT(&l_U21);
							}
						}
					}
					if ((IS_CHAR_IN_WATER(PARA_HANDLE)) || (uVar9.fZ < -2.00000000))
					{
						if (NOT (IS_PED_RAGDOLL(PARA_HANDLE)))
						{
							Switch(0);
						}
					}
					else
					{
						GET_CHAR_VELOCITY(PARA_HANDLE, &uVar3.fX, &uVar3.fY, &uVar3.fZ);
						GET_CHAR_HEIGHT_ABOVE_GROUND(PARA_HANDLE, &fVar2);
						if (((uVar9.fZ > 1.10000000) || (fVar2 < 1.50000000)) AND (uVar3.fZ > -1.00000000))
						{
							if (l_U29 != 0)
							{
								GET_GAME_TIMER(&iVar12);
								if ((iVar12 - l_U29) > 500)
								{
									fVar29 = (TO_FLOAT(iVar12 - l_U29)) / 3000.00000000;
									if (NOT l_U40)
									{
										if (fVar29 < 1.00000000)
										{
											if (fVar29 > 0.10000000)
											{
												PLAY_SOUND_FROM_PED(-1, "PED_COLLISIONS_BODY_COLLISION", PARA_HANDLE);
												GET_CHAR_HEALTH(PARA_HANDLE, &iVar30);
												SET_CHAR_HEALTH(PARA_HANDLE, iVar30 - (ROUND(fVar29 * 100.00000000)));
											}
										}
										else
										{
											PLAY_SOUND_FROM_PED(-1, "PED_COLLISIONS_CRUSH_COMPONENTS", PARA_HANDLE);
											SET_CHAR_HEALTH(PARA_HANDLE, 0);
											Switch(0);
										}
										l_U40 = 1;
									}
									else if (NOT (IS_PED_RAGDOLL(PARA_HANDLE)))
									{
										SET_CHAR_INVINCIBLE(PARA_HANDLE, 0);
										g_U2692[0].fY = 7;
									}
								}
							}
							else if (NOT (IS_PED_RAGDOLL(PARA_HANDLE)))
							{
								if (NOT l_U44)
								{
									g_U2692[0].fY = 7;
								}
								else
								{
									l_U44 = 0;
									Switch(1);
								}
							}
						}
					}
					break;
					}
					if (DOES_OBJECT_EXIST(l_U21))
					{
						if ((g_U2692[0].fY == 5) || (g_U2692[0].fY == 3))
						{
							if (IS_OBJECT_ATTACHED(l_U21))
							{
								//ATTACH_PARACHUTE_MODEL_TO_PLAYER(PARA_HANDLE, l_U21);
							}
						}
					}
					if (l_U31 != 0)
					{
						if (IS_VEH_DRIVEABLE(l_U70))
						{
							GET_GAME_TIMER(&iVar12);
							if ((iVar12 - l_U31) > 1500)
							{
								SET_CAR_COLLISION(l_U70, 1);
								if (NOT l_U43)
								{
									MARK_CAR_AS_NO_LONGER_NEEDED(&l_U70);
								}
								l_U31 = 0;
							}
						}
						else
						{
							l_U31 = 0;
						}
					}
					l_U26 = l_U22;
					l_U27 = l_U23;
				}

			}
		}
	}
}

void CIVParachuteProcess::InitialiseParachuteLocal()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Para_Main, 0, 0, 0);
}