//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: IVParachute_Manager.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include <Common.h>
#include "IVParachute_Manager.h"
#include "IVParachuteData.h"
#define WAIT Sleep

extern unsigned int l_U40;
extern unsigned int l_U41;
typedef unsigned unknown;
extern CVector3 g_U9105[6]; 
CUnkown g_U2692[2];
C95Class g_U95;

float l_U0;
float l_U1;
int l_U35 = 0;
int l_U36;
int l_U37;
int l_U38;
int l_U39;
int l_U42;
int l_U43;

unsigned int sub_196()
{
    unknown Result;

    GET_PLAYER_CHAR( CONVERT_INT_TO_PLAYERINDEX( GET_PLAYER_ID() ), &Result );
    return Result;
}

unsigned int sub_3739()
{
    return CONVERT_INT_TO_PLAYERINDEX( GET_PLAYER_ID() );
}

void sub_346()
{
    int I;

    g_U2783 = 1;
    g_U2784 = 0;
    g_U2785 = 1;
    g_U2786 = 0;
    g_U2787 = 0;
    g_U2795 = 0;
    g_U2788 = 0;
    g_U2789 = 0;
    g_U2790 = 0;
    g_U2791 = 0;
    g_U2789 = 0;
    g_U2792 = 0;
    g_U2794 = 1;
    g_U2797 = 0;
    g_U2798 = 0;
    g_U2799 = 0;
    g_U2800 = 0;
    g_U2801 = 0;
    g_U2802 = 0;
    I = 0;
	for ( I = 0; I < ARRAY_LENGTH(g_U2692); I++ )
    {
        g_U2692[I].fX = NULL;
        g_U2692[I].fY = 0;
        g_U2692[I].fZ = 0;
        g_U2692[I]._fU12 = CVector3(0.00000000, 0.00000000, 0.00000000);
        g_U2692[I]._fU24 = CVector3(0.00000000, 0.00000000, 0.00000000);
        g_U2692[I]._fU36 = CVector3(0.00000000, 0.00000000, 0.00000000);
        g_U2692[I].fY8 = -60.00000000;
        g_U2692[I]._fU52 = -7.00000000;
        g_U2692[I]._fU56 = 0;
        g_U2692[I]._fU60 = 0;
        g_U2692[I]._fU64 = 0;
        g_U2692[I]._fU68 = 0;
    }
    return;
}

int sub_2896()
{
    unknown uVar2;

    if (NOT (IS_CHAR_INJURED( sub_196() )))
    {
        uVar2 = GET_CHAR_DRAWABLE_VARIATION( sub_196(), 1 );
        switch (uVar2)
        {
            case 0:
            return 1;
            break;
            case 1:
            return 2;
            break;
            case 2:
            return 2;
            break;
            case 3:
            return 1;
            break;
            case 4:
            return 1;
            break;
        }
    }
    return 1;
}

int sub_2869()
{
    int iVar2;
    int iVar3;

    if (NOT (IS_CHAR_INJURED( sub_196() )))
    {
        iVar2 = sub_2896();
        iVar3 = GET_CHAR_DRAWABLE_VARIATION( sub_196(), 8 );
        if (iVar2 != iVar3)
        {
            return 0;
        }
    }
    return 1;
}

void sub_3087()
{
    unknown uVar2;

    uVar2 = sub_2896();
    SET_CHAR_COMPONENT_VARIATION( sub_196(), 8, uVar2, 0 );
    WAIT( 0 );
    if (NOT g_U2787)
    {
        SET_DRAW_PLAYER_COMPONENT( 8, 0 );
    }
    return;
}

void sub_3254()
{
    REQUEST_MODEL( 1490460832 );
    REQUEST_ANIMS( "PARACHUTE" );
    return;
}

void sub_3586()
{
    if (HAS_MODEL_LOADED( 1490460832 ))
    {
        MARK_MODEL_AS_NO_LONGER_NEEDED( 1490460832 );
    }
    if (HAVE_ANIMS_LOADED( "PARACHUTE" ))
    {
        REMOVE_ANIMS( "PARACHUTE" );
    }
    return;
}

int sub_3852()
{
    if (g_U560 == 9)
    {
        return 0;
    }
    return 1;
}

int sub_3948(boolean bParam0, unknown uParam1)
{
    if (bParam0)
    {
        g_U95._fU104 = 1;
    }
    if ((g_U560 != 9) AND (uParam1))
    {
        g_U95._fU100 = 1;
    }
    return 1;
}

int sub_3937()
{
    return sub_3948( 0, 0 );
}

int sub_3730(int iParam0, unknown uParam1)
{
    if (IS_PLAYER_PLAYING( sub_3739() ))
    {
        if (IS_SCREEN_FADED_IN())
        {
            if ((iParam0 == 5) || (IS_PLAYER_CONTROL_ON( sub_3739() )))
            {
                if (((g_U9200) AND (uParam1)) || ((iParam0 == 4) || ((iParam0 == 5) || (IS_PLAYER_FREE_FOR_AMBIENT_TASK( sub_3739() )))))
                {
                    if (NOT sub_3852())
                    {
                        if ((GET_OBJECT_PED_IS_HOLDING( sub_196() )) == NULL)
                        {
                            if (g_U10534 <= iParam0)
                            {
                                if (g_U10535 == 0)
                                {
                                    if (sub_3937())
                                    {
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int sub_4172(int iParam0)
{
    int Result;

    Result = 0;
    for ( Result = 0; Result < ARRAY_LENGTH(g_U2692); Result++ )
    {
        if (g_U2692[Result].fX == iParam0)
        {
            if (g_U2692[Result]._fU56)
            {
                return Result;
            }
        }
    }
    return -1;
}

void sub_4161(int iParam0)
{
    int iVar3;
    int I;

    iVar3 = sub_4172( iParam0 );
    if (iVar3 == -1)
    {
        if (NOT (IS_CHAR_INJURED( iParam0 )))
        {
            if (iParam0 != sub_196())
            {
                I = 1;
                for ( I = 0; I < ARRAY_LENGTH(g_U2692); I++ )
                {
                    if (NOT g_U2692[I]._fU56)
                    {
                        iVar3 = I;
                    }
                }
            }
            else
            {
                iVar3 = 0;
            }
            if (iVar3 != -1)
            {
                if (NOT g_U2692[iVar3]._fU56)
                {
                    g_U2692[iVar3].fX = iParam0;
                    g_U2692[iVar3].fY = 0;
                    g_U2692[iVar3].fZ = 0;
                    g_U2692[iVar3]._fU12 = CVector3(0.00000000, 0.00000000, 0.00000000);
                    g_U2692[iVar3]._fU56 = 1;
                    g_U2692[iVar3]._fU60 = 0;
                    g_U2692[iVar3]._fU64 = 0;
                    g_U2692[iVar3].fY8 = -60.00000000;
                    g_U2692[iVar3]._fU52 = -7.00000000;
                    g_U2791 = 0;
                    g_U2789 = 0;
                    g_U2785 = 1;
                    g_U2784 = 0;
                    g_U2783 = 0;
                    g_U2786 = 0;
                    g_U2790 = 0;
                }
            }
            else
            {
				//SCRIPT_ASSERT( "GIVE_PED_A_PARACHUTE: All AI parachute ped slots are currently in use." );
            }
        }
    }
    return;
}

int sub_4804()
{
    int iVar2;

    if (NOT (IS_CHAR_INJURED( sub_196() )))
    {
        iVar2 = GET_CHAR_DRAWABLE_VARIATION( sub_196(), 8 );
        if (iVar2 == 0)
        {
            return 0;
        }
    }
    return 1;
}

void sub_4767(boolean bParam0)
{
    if (NOT bParam0)
    {
        SET_DRAW_PLAYER_COMPONENT( 8, 0 );
        g_U2787 = 0;
    }
    else if (NOT sub_4804())
    {
        sub_3087();
    }
    SET_DRAW_PLAYER_COMPONENT( 8, 1 );
    g_U2787 = 1;;
    return;
}

void sub_4976()
{
    CVector3 uVar2;
    unknown uVar3;
    unknown uVar4;

    if (NOT (HAS_MODEL_LOADED( 1276771907 )))
    {
        REQUEST_MODEL( 1276771907 );
    }
    else if (NOT (IS_CHAR_INJURED( sub_196() )))
    {
        GET_CHAR_COORDINATES( sub_196(), &uVar2.fX, &uVar2.fY, &uVar2.fZ );
        CREATE_OBJECT_NO_OFFSET( 1276771907, uVar2.fX, uVar2.fY, -25.00000000, &l_U40, 1 );
        SET_OBJECT_DYNAMIC( l_U40, 0 );
        SET_OBJECT_COLLISION( l_U40, 0 );
        SET_OBJECT_VISIBLE( l_U40, 0 );
        SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN( l_U40, 1 );
        MARK_MODEL_AS_NO_LONGER_NEEDED( 1276771907 );
    }
    return;
}

void sub_5286()
{
    if (DOES_OBJECT_EXIST( l_U40 ))
    {
        SET_OBJECT_DYNAMIC( l_U40, 1 );
        SET_OBJECT_COLLISION( l_U40, 1 );
        SET_OBJECT_VISIBLE( l_U40, 1 );
        ATTACH_OBJECT_TO_PED( l_U40, sub_196(), 1202, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 0.00000000, 1 );
        PLAY_OBJECT_ANIM( l_U40, "obj_chute_off", "PARACHUTE", 1000.00000000, 0, 1 );
        if (NOT (IS_CHAR_INJURED( sub_196() )))
        {
            TASK_PLAY_ANIM_WITH_FLAGS( sub_196(), "chute_off", "PARACHUTE", 3.00000000, 0, 1280 );
        }
    }
    return;
}

void sub_5771()
{
    if (DOES_OBJECT_EXIST( l_U40 ))
    {
        DELETE_OBJECT( &l_U40 );
        l_U41 = 0;
        l_U35 = 0;
    }
    return;
}

void sub_6107()
{
    if (NOT (IS_CHAR_INJURED( sub_196() )))
    {
        if ((IS_HUD_PREFERENCE_SWITCHED_ON()) AND ((NOT ARE_WIDESCREEN_BORDERS_ACTIVE()) AND ((IS_CHAR_IN_ANY_HELI( sub_196() )) || (((g_U2692[0].fY == 5) || (g_U2692[0].fY == 3)) AND (g_U2692[0]._fU56)))))
        {
            DISPLAY_ALTIMETER_THIS_FRAME();
        }
    }
    return;
}

void ParaManager_Main()
{
    int iVar2;
    int iVar3;
    int I;
    unsigned int iVar5;
    float fVar6;
    unsigned int iVar7;
    int iVar8;
    float uVar9;
    CVector3 uVar10;
    unknown uVar11;
    unknown uVar12;
    unknown uVar13;
    unknown uVar14;
    unknown uVar15;

    l_U0 = 86.00000000;
    l_U1 = 274.00000000;
    l_U35 = 0;
    l_U36 = 0;
    l_U37 = 0;
    l_U38 = 0;
    l_U39 = 0;
    l_U41 = 0;
    l_U42 = 0;
    l_U43 = 0;
    while (true)
    {
        WAIT( 0 );
        if ((g_U2799) || (g_U2792))
        {
            if (DOES_OBJECT_EXIST( l_U40 ))
            {
                DELETE_OBJECT( &l_U40 );
            }
            if (NOT g_U2799)
            {
                if (g_U2692[0]._fU56)
                {
                    if ((g_U2692[0].fY == 1) || (g_U2692[0].fY == 0))
                    {
                        if (NOT (IS_CHAR_INJURED( sub_196() )))
                        {
                            if (NOT (HAS_CHAR_GOT_WEAPON( sub_196(), 41 )))
                            {
                                GIVE_WEAPON_TO_CHAR( sub_196(), 41, 1, 0 );
                            }
                        }
                    }
                }
            }
            else if (NOT (IS_CHAR_INJURED( sub_196() )))
            {
                if (HAS_CHAR_GOT_WEAPON( sub_196(), 41 ))
                {
                    REMOVE_WEAPON_FROM_CHAR( sub_196(), 41 );
                }
            }
            sub_346();
            SET_DRAW_PLAYER_COMPONENT( 8, 0 );
        }
        if (NOT g_U2795)
        {
            if (NOT sub_2869())
            {
                sub_3087();
            }
            if (NOT g_U2787)
            {
                SET_DRAW_PLAYER_COMPONENT( 8, 0 );
            }
        }

        if ((NOT (HAVE_ANIMS_LOADED( "PARACHUTE" ))) || (NOT (HAS_MODEL_LOADED( 1490460832 ))))
        {
            sub_3254();
        }

        if (NOT (DOES_OBJECT_EXIST( l_U40 )))
        {
            sub_3586();
        }
        else
        {
            sub_3254();
        }
        if (NOT (IS_CHAR_INJURED( sub_196() )))
        {
            GET_CURRENT_CHAR_WEAPON( sub_196(), &iVar5 );
            if (iVar5 == 41)
            {
                if ((NOT g_U2800) AND (sub_3730( 4, 0 )))
                {
                    if ((NOT IS_HELP_MESSAGE_BEING_DISPLAYED()) AND ((l_U42 < 2) AND (NOT l_U43)))
                    {
                        PRINT_HELP( "PARA_EQUIP" );
                        l_U43 = 1;
                        l_U42++;
                    }
                    if (IS_CONTROL_JUST_PRESSED( 0, 4 ))
                    {
                        REMOVE_WEAPON_FROM_CHAR( sub_196(), 41 );
                        GIVE_WEAPON_TO_CHAR( sub_196(), 0, 0, 1 );
                        sub_4161( sub_196() );
                    }
                }
            }
        }
        if (NOT (IS_CHAR_INJURED( sub_196() )))
        {
            if (g_U2692[0]._fU56)
            {
                if (NOT g_U2787)
                {
                    sub_4767( 1 );
                }
                if (NOT (DOES_OBJECT_EXIST( l_U40 )))
                {
                    if ((g_U2692[0].fY == 8) || ((g_U2692[0].fY == 7) || ((g_U2692[0].fY == 5) || (g_U2692[0].fY == 3))))
                    {
                        sub_4976();
                    }
                }
            }
            else if (DOES_OBJECT_EXIST( l_U40 ))
            {
                if (NOT IS_SCREEN_FADED_OUT())
                {
                    if (NOT (IS_CHAR_IN_WATER( sub_196() )))
                    {
                        if (HAVE_ANIMS_LOADED( "PARACHUTE" ))
                        {
                            if (g_U2787)
                            {
                                if (NOT l_U35)
                                {
                                    if ((NOT (IS_CHAR_IN_ANY_CAR( sub_196() ))) AND (sub_3730( 4, 0 )))
                                    {
                                        sub_5286();
                                        l_U35 = 1;
                                    }
                                }
                                else if (l_U41 == 0)
                                {
                                    SET_DRAW_PLAYER_COMPONENT( 8, 0 );
                                    if (IS_OBJECT_PLAYING_ANIM( l_U40, "obj_chute_off", "PARACHUTE" ))
                                    {
                                        GET_OBJECT_ANIM_CURRENT_TIME( l_U40, "obj_chute_off", "PARACHUTE", &fVar6 );
                                        if (fVar6 > 0.95000000)
                                        {
                                            DETACH_OBJECT( l_U40, 1 );
                                            PLAY_OBJECT_ANIM( l_U40, "obj_chute_off_idle", "PARACHUTE", 8.00000000, 1, 0 );
                                            GET_GAME_TIMER( &l_U41 );
                                        }
                                        if (NOT (IS_CHAR_PLAYING_ANIM( sub_196(), "PARACHUTE", "chute_off" )))
                                        {
                                            sub_5771();
                                        }
                                    }
                                }
                                else
                                {
                                    GET_GAME_TIMER( &iVar7 );
                                    GET_OBJECT_COORDINATES( l_U40, &uVar10.fX, &uVar10.fY, &uVar10.fZ );
                                    GET_GROUND_Z_FOR_3D_COORD( uVar10.fX, uVar10.fY, uVar10.fZ + 1000.00000000, &uVar9 );
                                    if (uVar10.fZ < (uVar9 + 1.00000000))
                                    {
                                        FREEZE_OBJECT_POSITION( l_U40, 1 );
                                    }
                                    iVar8 = iVar7 - l_U41;
                                    if (iVar8 > 2000)
                                    {
                                        sub_5771();
                                    }
                                    else if (iVar8 > 1000)
                                    {
                                        SET_OBJECT_ALPHA( l_U40, 255 - (ROUND( ((TO_FLOAT( iVar8 - 1000 )) / 1000.00000000) * 255.00000000 )) );
                                    }
                                }
                            }
                            else
                            {
                                sub_5771();
                            }
                        }
                        else
                        {
                            sub_5771();
                        }
                    }
                    else
                    {
                        sub_5771();
                    }
                }
                else
                {
                    sub_5771();
                }
            }
            else if (g_U2787)
            {
                if (NOT IS_PLAYER_BEING_ARRESTED())
                {
                    sub_4767( 0 );
                }
            }
        }
        else
        {
            sub_5771();
        }
        sub_6107();
    }
    return;
}

void CIVParachuteManager::InitialiseParachuteManager()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ParaManager_Main, 0, 0, 0);
}