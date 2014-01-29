/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "CModelManager.h"
#include <CCore.h>
#include <Game/COffsets.h>
#include <Game/EFLC/ScriptEnums.h>

extern CCore * g_pCore;

_GAME_BEGIN

int CModelManager::GetModelIndexFromHash( DWORD dwModelHash )
{
	int iModelIndex = -1;

	((int(__cdecl *) (int, int*))(COffsets::FUNC_GetModelIndexFromHash))(dwModelHash, &iModelIndex);

	return iModelIndex;
}

void CModelManager::RequestModel(int iModelIndex, DWORD dwFlags)
{
	((bool(__cdecl *) (int, unsigned int, int))(COffsets::FUNC_RequestResource))(iModelIndex, *(unsigned int *) COffsets::VAR_ResourceTypeWdrIndex, dwFlags);
}

void CModelManager::LoadRequestedModels( )
{
	((int(__cdecl *) (bool))(COffsets::FUNC_LoadAllResources))(true);
}

bool CModelManager::HasModelLoaded( int iModelIndex )
{
	return ((bool(__cdecl *) (int, unsigned int))(COffsets::FUNC_HasResourceLoaded))(iModelIndex, *(unsigned int *) COffsets::VAR_ResourceTypeWdrIndex);
}

void CModelManager::ReleaseModel( int iModelIndex )
{
	((void(__cdecl *) (int, unsigned int))(COffsets::FUNC_ReleaseResource))(iModelIndex, *(unsigned int *) COffsets::VAR_ResourceTypeWdrIndex);
}

DWORD CModelManager::VehicleIdToModelHash(int iModelId)
{
	switch(iModelId)
	{
		case 0: return CScript::MODEL_ADMIRAL;
		case 1: return CScript::MODEL_AIRTUG;
		case 2: return CScript::MODEL_AMBULANCE;
		case 3: return CScript::MODEL_BANSHEE;
		case 4: return CScript::MODEL_BENSON;
		case 5: return CScript::MODEL_BIFF;
		case 6: return CScript::MODEL_BLISTA;
		case 7: return CScript::MODEL_BOBCAT;
		case 8: return CScript::MODEL_BOXVILLE;
		case 9: return CScript::MODEL_BUCCANEER;
		case 10: return CScript::MODEL_BURRITO;
		case 11: return CScript::MODEL_BURRITO2;
		case 12: return CScript::MODEL_BUS;
		case 13: return CScript::MODEL_CABBY;
		case 14: return CScript::MODEL_CAVALCADE;
		case 15: return CScript::MODEL_CHAVOS;
		case 16: return CScript::MODEL_COGNOSCENTI;
		case 17: return CScript::MODEL_COMET;
		case 18: return CScript::MODEL_COQUETTE;
		case 19: return CScript::MODEL_DF8;
		case 20: return CScript::MODEL_DILETTANTE;
		case 21: return CScript::MODEL_DUKES;
		case 22: return CScript::MODEL_E109;
		case 23: return CScript::MODEL_EMPEROR;
		case 24: return CScript::MODEL_EMPEROR2;
		case 25: return CScript::MODEL_ESPERANTO;
		case 26: return CScript::MODEL_FACTION;
		case 27: return CScript::MODEL_FBI;
		case 28: return CScript::MODEL_FELTZER;
		case 29: return CScript::MODEL_FEROCI;
		case 30: return CScript::MODEL_FEROCI2;
		case 31: return CScript::MODEL_FIRETRUK;
		case 32: return CScript::MODEL_FLATBED;
		case 33: return CScript::MODEL_FORTUNE;
		case 34: return CScript::MODEL_FORKLIFT;
		case 35: return CScript::MODEL_FUTO;
		case 36: return CScript::MODEL_FXT;
		case 37: return CScript::MODEL_HABANERO;
		case 38: return CScript::MODEL_HAKUMAI;
		case 39: return CScript::MODEL_HUNTLEY;
		case 40: return CScript::MODEL_INFERNUS;
		case 41: return CScript::MODEL_INGOT;
		case 42: return CScript::MODEL_INTRUDER;
		case 43: return CScript::MODEL_LANDSTALKER;
		case 44: return CScript::MODEL_LOKUS;
		case 45: return CScript::MODEL_MANANA;
		case 46: return CScript::MODEL_MARBELLA;
		case 47: return CScript::MODEL_MERIT;
		case 48: return CScript::MODEL_MINIVAN;
		case 49: return CScript::MODEL_MOONBEAM;
		case 50: return CScript::MODEL_MRTASTY;
		case 51: return CScript::MODEL_MULE;
		case 52: return CScript::MODEL_NOOSE;
		case 53: return CScript::MODEL_NSTOCKADE;
		case 54: return CScript::MODEL_ORACLE;
		case 55: return CScript::MODEL_PACKER;
		case 56: return CScript::MODEL_PATRIOT;
		case 57: return CScript::MODEL_PERENNIAL;
		case 58: return CScript::MODEL_PERENNIAL2;
		case 59: return CScript::MODEL_PEYOTE;
		case 60: return CScript::MODEL_PHANTOM;
		case 61: return CScript::MODEL_PINNACLE;
		case 62: return CScript::MODEL_PMP600;
		case 63: return CScript::MODEL_POLICE;
		case 64: return CScript::MODEL_POLICE2;
		case 65: return CScript::MODEL_POLPATRIOT;
		case 66: return CScript::MODEL_PONY;
		case 67: return CScript::MODEL_PREMIER;
		case 68: return CScript::MODEL_PRES;
		case 69: return CScript::MODEL_PRIMO;
		case 70: return CScript::MODEL_PSTOCKADE;
		case 71: return CScript::MODEL_RANCHER;
		case 72: return CScript::MODEL_REBLA;
		case 73: return CScript::MODEL_RIPLEY;
		case 74: return CScript::MODEL_ROMERO;
		case 75: return CScript::MODEL_ROM;
		case 76: return CScript::MODEL_RUINER;
		case 77: return CScript::MODEL_SABRE;
		case 78: return CScript::MODEL_SABRE2;
		case 79: return CScript::MODEL_SABREGT;
		case 80: return CScript::MODEL_SCHAFTER;
		case 81: return CScript::MODEL_SENTINEL;
		case 82: return CScript::MODEL_SOLAIR;
		case 83: return CScript::MODEL_SPEEDO;
		case 84: return CScript::MODEL_STALION;
		case 85: return CScript::MODEL_STEED;
		case 86: return CScript::MODEL_STOCKADE;
		case 87: return CScript::MODEL_STRATUM;
		case 88: return CScript::MODEL_STRETCH;
		case 89: return CScript::MODEL_SULTAN;
		case 90: return CScript::MODEL_SULTANRS;
		case 91: return CScript::MODEL_SUPERGT;
		case 92: return CScript::MODEL_TAXI;
		case 93: return CScript::MODEL_TAXI2;
		case 94: return CScript::MODEL_TRASH;
		case 95: return CScript::MODEL_TURISMO;
		case 96: return CScript::MODEL_URANUS;
		case 97: return CScript::MODEL_VIGERO;
		case 98: return CScript::MODEL_VIGERO2;
		case 99: return CScript::MODEL_VINCENT;
		case 100: return CScript::MODEL_VIRGO;
		case 101: return CScript::MODEL_VOODOO;
		case 102: return CScript::MODEL_WASHINGTON;
		case 103: return CScript::MODEL_WILLARD;
		case 104: return CScript::MODEL_YANKEE;
		case 105: return CScript::MODEL_BOBBER;
		case 106: return CScript::MODEL_FAGGIO;
		case 107: return CScript::MODEL_HELLFURY;
		case 108: return CScript::MODEL_NRG900;
		case 109: return CScript::MODEL_PCJ;
		case 110: return CScript::MODEL_SANCHEZ;
		case 111: return CScript::MODEL_ZOMBIEB;
		case 112: return CScript::MODEL_ANNIHILATOR;
		case 113: return CScript::MODEL_MAVERICK;
		case 114: return CScript::MODEL_POLMAV;
		case 115: return CScript::MODEL_TOURMAV;
		case 116: return CScript::MODEL_DINGHY;
		case 117: return CScript::MODEL_JETMAX;
		case 118: return CScript::MODEL_MARQUIS;
		case 119: return CScript::MODEL_PREDATOR;
		case 120: return CScript::MODEL_REEFER;
		case 121: return CScript::MODEL_SQUALO;
		case 122: return CScript::MODEL_TUGA;
		case 123: return CScript::MODEL_TROPIC;
		case 124: return CScript::MODEL_CABLECAR;
		case 125: return CScript::MODEL_SUBWAY_LO;
		case 126: return CScript::MODEL_SUBWAY_HI;
		case 127: return CScript::MODEL_SLAMVAN;
		case 128: return CScript::MODEL_CADDY;
		case 129: return CScript::MODEL_APC;
		case 130: return CScript::MODEL_SUPERD;
		case 131: return CScript::MODEL_SUPERD2;
		case 132: return CScript::MODEL_SERRANO;
		case 133: return CScript::MODEL_SERRANO2;
		case 134: return CScript::MODEL_BUFFALO;
		case 135: return CScript::MODEL_AVAN;
		case 136: return CScript::MODEL_SCHAFTER2;
		case 137: return CScript::MODEL_SCHAFTER3;
		case 138: return CScript::MODEL_BULLET;
		case 139: return CScript::MODEL_TAMPA;
		case 140: return CScript::MODEL_CAVALCADE2;
		case 141: return CScript::MODEL_F620;
		case 142: return CScript::MODEL_LIMO2;
		case 143: return CScript::MODEL_POLICE3;
		case 144: return CScript::MODEL_POLICEW;
		case 145: return CScript::MODEL_POLICE4;
		case 146: return CScript::MODEL_POLICEB;
		case 147: return CScript::MODEL_HEXER;
		case 148: return CScript::MODEL_FAGGIO2;
		case 149: return CScript::MODEL_BATI2;
		case 150: return CScript::MODEL_VADER;
		case 151: return CScript::MODEL_AKUMA;
		case 152: return CScript::MODEL_HAKUCHOU;
		case 153: return CScript::MODEL_DOUBLE;
		case 154: return CScript::MODEL_BUZZARD;
		case 155: return CScript::MODEL_SWIFT;
		case 156: return CScript::MODEL_SKYLIFT;
		case 157: return CScript::MODEL_SMUGGLER;
		case 158: return CScript::MODEL_FLOATER;
		case 159: return CScript::MODEL_BLADE;
		case 160: return CScript::MODEL_GBURRITO;
		case 161: return CScript::MODEL_TOWTRUCK;
		case 162: return CScript::MODEL_PACKER2;
		case 163: return CScript::MODEL_PBUS;
		case 164: return CScript::MODEL_YANKEE2;
		case 165: return CScript::MODEL_RHAPSODY;
		case 166: return CScript::MODEL_REGINA;
		case 167: return CScript::MODEL_ANGEL;
		case 168: return CScript::MODEL_BATI;
		case 169: return CScript::MODEL_DAEMON;
		case 170: return CScript::MODEL_DIABOLUS;
		case 171: return CScript::MODEL_DOUBLE2;
		case 172: return CScript::MODEL_HAKUCHOU2;
		case 173: return CScript::MODEL_INNOVATION;
		case 174: return CScript::MODEL_LYCAN;
		case 175: return CScript::MODEL_NIGHTBLADE;
		case 176: return CScript::MODEL_REVENANT;
		case 177: return CScript::MODEL_WAYFARER;
		case 178: return CScript::MODEL_WOLFSBANE;
	}

	return 0x00;
}

int CModelManager::ModelHashToVehicleId(DWORD dwModelHash)
{
	switch(dwModelHash)
	{
		case CScript::MODEL_ADMIRAL: return 0;
		case CScript::MODEL_AIRTUG: return 1;
		case CScript::MODEL_AMBULANCE: return 2;
		case CScript::MODEL_BANSHEE: return 3;
		case CScript::MODEL_BENSON: return 4;
		case CScript::MODEL_BIFF: return 5;
		case CScript::MODEL_BLISTA: return 6;
		case CScript::MODEL_BOBCAT: return 7;
		case CScript::MODEL_BOXVILLE: return 8;
		case CScript::MODEL_BUCCANEER: return 9;
		case CScript::MODEL_BURRITO: return 10;
		case CScript::MODEL_BURRITO2: return 11;
		case CScript::MODEL_BUS: return 12;
		case CScript::MODEL_CABBY: return 13;
		case CScript::MODEL_CAVALCADE: return 14;
		case CScript::MODEL_CHAVOS: return 15;
		case CScript::MODEL_COGNOSCENTI: return 16;
		case CScript::MODEL_COMET: return 17;
		case CScript::MODEL_COQUETTE: return 18;
		case CScript::MODEL_DF8: return 19;
		case CScript::MODEL_DILETTANTE: return 20;
		case CScript::MODEL_DUKES: return 21;
		case CScript::MODEL_E109: return 22;
		case CScript::MODEL_EMPEROR: return 23;
		case CScript::MODEL_EMPEROR2: return 24;
		case CScript::MODEL_ESPERANTO: return 25;
		case CScript::MODEL_FACTION: return 26;
		case CScript::MODEL_FBI: return 27;
		case CScript::MODEL_FELTZER: return 28;
		case CScript::MODEL_FEROCI: return 29;
		case CScript::MODEL_FEROCI2: return 30;
		case CScript::MODEL_FIRETRUK: return 31;
		case CScript::MODEL_FLATBED: return 32;
		case CScript::MODEL_FORTUNE: return 33;
		case CScript::MODEL_FORKLIFT: return 34;
		case CScript::MODEL_FUTO: return 35;
		case CScript::MODEL_FXT: return 36;
		case CScript::MODEL_HABANERO: return 37;
		case CScript::MODEL_HAKUMAI: return 38;
		case CScript::MODEL_HUNTLEY: return 39;
		case CScript::MODEL_INFERNUS: return 40;
		case CScript::MODEL_INGOT: return 41;
		case CScript::MODEL_INTRUDER: return 42;
		case CScript::MODEL_LANDSTALKER: return 43;
		case CScript::MODEL_LOKUS: return 44;
		case CScript::MODEL_MANANA: return 45;
		case CScript::MODEL_MARBELLA: return 46;
		case CScript::MODEL_MERIT: return 47;
		case CScript::MODEL_MINIVAN: return 48;
		case CScript::MODEL_MOONBEAM: return 49;
		case CScript::MODEL_MRTASTY: return 50;
		case CScript::MODEL_MULE: return 51;
		case CScript::MODEL_NOOSE: return 52;
		case CScript::MODEL_NSTOCKADE: return 53;
		case CScript::MODEL_ORACLE: return 54;
		case CScript::MODEL_PACKER: return 55;
		case CScript::MODEL_PATRIOT: return 56;
		case CScript::MODEL_PERENNIAL: return 57;
		case CScript::MODEL_PERENNIAL2: return 58;
		case CScript::MODEL_PEYOTE: return 59;
		case CScript::MODEL_PHANTOM: return 60;
		case CScript::MODEL_PINNACLE: return 61;
		case CScript::MODEL_PMP600: return 62;
		case CScript::MODEL_POLICE: return 63;
		case CScript::MODEL_POLICE2: return 64;
		case CScript::MODEL_POLPATRIOT: return 65;
		case CScript::MODEL_PONY: return 66;
		case CScript::MODEL_PREMIER: return 67;
		case CScript::MODEL_PRES: return 68;
		case CScript::MODEL_PRIMO: return 69;
		case CScript::MODEL_PSTOCKADE: return 70;
		case CScript::MODEL_RANCHER: return 71;
		case CScript::MODEL_REBLA: return 72;
		case CScript::MODEL_RIPLEY: return 73;
		case CScript::MODEL_ROMERO: return 74;
		case CScript::MODEL_ROM: return 75;
		case CScript::MODEL_RUINER: return 76;
		case CScript::MODEL_SABRE: return 77;
		case CScript::MODEL_SABRE2: return 78;
		case CScript::MODEL_SABREGT: return 79;
		case CScript::MODEL_SCHAFTER: return 80;
		case CScript::MODEL_SENTINEL: return 81;
		case CScript::MODEL_SOLAIR: return 82;
		case CScript::MODEL_SPEEDO: return 83;
		case CScript::MODEL_STALION: return 84;
		case CScript::MODEL_STEED: return 85;
		case CScript::MODEL_STOCKADE: return 86;
		case CScript::MODEL_STRATUM: return 87;
		case CScript::MODEL_STRETCH: return 88;
		case CScript::MODEL_SULTAN: return 89;
		case CScript::MODEL_SULTANRS: return 90;
		case CScript::MODEL_SUPERGT: return 91;
		case CScript::MODEL_TAXI: return 92;
		case CScript::MODEL_TAXI2: return 93;
		case CScript::MODEL_TRASH: return 94;
		case CScript::MODEL_TURISMO: return 95;
		case CScript::MODEL_URANUS: return 96;
		case CScript::MODEL_VIGERO: return 97;
		case CScript::MODEL_VIGERO2: return 98;
		case CScript::MODEL_VINCENT: return 99;
		case CScript::MODEL_VIRGO: return 100;
		case CScript::MODEL_VOODOO: return 101;
		case CScript::MODEL_WASHINGTON: return 102;
		case CScript::MODEL_WILLARD: return 103;
		case CScript::MODEL_YANKEE: return 104;
		case CScript::MODEL_BOBBER: return 105;
		case CScript::MODEL_FAGGIO: return 106;
		case CScript::MODEL_HELLFURY: return 107;
		case CScript::MODEL_NRG900: return 108;
		case CScript::MODEL_PCJ: return 109;
		case CScript::MODEL_SANCHEZ: return 110;
		case CScript::MODEL_ZOMBIEB: return 111;
		case CScript::MODEL_ANNIHILATOR: return 112;
		case CScript::MODEL_MAVERICK: return 113;
		case CScript::MODEL_POLMAV: return 114;
		case CScript::MODEL_TOURMAV: return 115;
		case CScript::MODEL_DINGHY: return 116;
		case CScript::MODEL_JETMAX: return 117;
		case CScript::MODEL_MARQUIS: return 118;
		case CScript::MODEL_PREDATOR: return 119;
		case CScript::MODEL_REEFER: return 120;
		case CScript::MODEL_SQUALO: return 121;
		case CScript::MODEL_TUGA: return 122;
		case CScript::MODEL_TROPIC: return 123;
		case CScript::MODEL_CABLECAR: return 124;
		case CScript::MODEL_SUBWAY_LO: return 125;
		case CScript::MODEL_SUBWAY_HI: return 126;
		case CScript::MODEL_SLAMVAN: return 127;
		case CScript::MODEL_CADDY: return 128;
		case CScript::MODEL_APC: return 129;
		case CScript::MODEL_SUPERD: return 130;
		case CScript::MODEL_SUPERD2: return 131;
		case CScript::MODEL_SERRANO: return 132;
		case CScript::MODEL_SERRANO2: return 133;
		case CScript::MODEL_BUFFALO: return 134;
		case CScript::MODEL_AVAN: return 135;
		case CScript::MODEL_SCHAFTER2: return 136;
		case CScript::MODEL_SCHAFTER3: return 137;
		case CScript::MODEL_BULLET: return 138;
		case CScript::MODEL_TAMPA: return 139;
		case CScript::MODEL_CAVALCADE2: return 140;
		case CScript::MODEL_F620: return 141;
		case CScript::MODEL_LIMO2: return 142;
		case CScript::MODEL_POLICE3: return 143;
		case CScript::MODEL_POLICEW: return 144;
		case CScript::MODEL_POLICE4: return 145;
		case CScript::MODEL_POLICEB: return 146;
		case CScript::MODEL_HEXER: return 147;
		case CScript::MODEL_FAGGIO2: return 148;
		case CScript::MODEL_BATI2: return 149;
		case CScript::MODEL_VADER: return 150;
		case CScript::MODEL_AKUMA: return 151;
		case CScript::MODEL_HAKUCHOU: return 152;
		case CScript::MODEL_DOUBLE: return 153;
		case CScript::MODEL_BUZZARD: return 154;
		case CScript::MODEL_SWIFT: return 155;
		case CScript::MODEL_SKYLIFT: return 156;
		case CScript::MODEL_SMUGGLER: return 157;
		case CScript::MODEL_FLOATER: return 158;
		case CScript::MODEL_BLADE: return 159;
		case CScript::MODEL_GBURRITO: return 160;
		case CScript::MODEL_TOWTRUCK: return 161;
		case CScript::MODEL_PACKER2: return 162;
		case CScript::MODEL_PBUS: return 163;
		case CScript::MODEL_YANKEE2: return 164;
		case CScript::MODEL_RHAPSODY: return 165;
		case CScript::MODEL_REGINA: return 166;
		case CScript::MODEL_ANGEL: return 167;
		case CScript::MODEL_BATI: return 168;
		case CScript::MODEL_DAEMON: return 169;
		case CScript::MODEL_DIABOLUS: return 170;
		case CScript::MODEL_DOUBLE2: return 171;
		case CScript::MODEL_HAKUCHOU2: return 172;
		case CScript::MODEL_INNOVATION: return 173;
		case CScript::MODEL_LYCAN: return 174;
		case CScript::MODEL_NIGHTBLADE: return 175;
		case CScript::MODEL_REVENANT: return 176;
		case CScript::MODEL_WAYFARER: return 177;
		case CScript::MODEL_WOLFSBANE: return 178;
	}

	return -1;
}

_GAME_END