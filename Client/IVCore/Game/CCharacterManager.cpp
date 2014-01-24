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

#include "CCharacterManager.h"
#include <Game/EFLC/CScript.h>

DWORD CCharacterManager::VehicleIdToModelHash(int iModelId)
{
	switch(iModelId)
	{
		case 0: return EFLC::CScript::MODEL_ADMIRAL;
		case 1: return EFLC::CScript::MODEL_AIRTUG;
		case 2: return EFLC::CScript::MODEL_AMBULANCE;
		case 3: return EFLC::CScript::MODEL_BANSHEE;
		case 4: return EFLC::CScript::MODEL_BENSON;
		case 5: return EFLC::CScript::MODEL_BIFF;
		case 6: return EFLC::CScript::MODEL_BLISTA;
		case 7: return EFLC::CScript::MODEL_BOBCAT;
		case 8: return EFLC::CScript::MODEL_BOXVILLE;
		case 9: return EFLC::CScript::MODEL_BUCCANEER;
		case 10: return EFLC::CScript::MODEL_BURRITO;
		case 11: return EFLC::CScript::MODEL_BURRITO2;
		case 12: return EFLC::CScript::MODEL_BUS;
		case 13: return EFLC::CScript::MODEL_CABBY;
		case 14: return EFLC::CScript::MODEL_CAVALCADE;
		case 15: return EFLC::CScript::MODEL_CHAVOS;
		case 16: return EFLC::CScript::MODEL_COGNOSCENTI;
		case 17: return EFLC::CScript::MODEL_COMET;
		case 18: return EFLC::CScript::MODEL_COQUETTE;
		case 19: return EFLC::CScript::MODEL_DF8;
		case 20: return EFLC::CScript::MODEL_DILETTANTE;
		case 21: return EFLC::CScript::MODEL_DUKES;
		case 22: return EFLC::CScript::MODEL_E109;
		case 23: return EFLC::CScript::MODEL_EMPEROR;
		case 24: return EFLC::CScript::MODEL_EMPEROR2;
		case 25: return EFLC::CScript::MODEL_ESPERANTO;
		case 26: return EFLC::CScript::MODEL_FACTION;
		case 27: return EFLC::CScript::MODEL_FBI;
		case 28: return EFLC::CScript::MODEL_FELTZER;
		case 29: return EFLC::CScript::MODEL_FEROCI;
		case 30: return EFLC::CScript::MODEL_FEROCI2;
		case 31: return EFLC::CScript::MODEL_FIRETRUK;
		case 32: return EFLC::CScript::MODEL_FLATBED;
		case 33: return EFLC::CScript::MODEL_FORTUNE;
		case 34: return EFLC::CScript::MODEL_FORKLIFT;
		case 35: return EFLC::CScript::MODEL_FUTO;
		case 36: return EFLC::CScript::MODEL_FXT;
		case 37: return EFLC::CScript::MODEL_HABANERO;
		case 38: return EFLC::CScript::MODEL_HAKUMAI;
		case 39: return EFLC::CScript::MODEL_HUNTLEY;
		case 40: return EFLC::CScript::MODEL_INFERNUS;
		case 41: return EFLC::CScript::MODEL_INGOT;
		case 42: return EFLC::CScript::MODEL_INTRUDER;
		case 43: return EFLC::CScript::MODEL_LANDSTALKER;
		case 44: return EFLC::CScript::MODEL_LOKUS;
		case 45: return EFLC::CScript::MODEL_MANANA;
		case 46: return EFLC::CScript::MODEL_MARBELLA;
		case 47: return EFLC::CScript::MODEL_MERIT;
		case 48: return EFLC::CScript::MODEL_MINIVAN;
		case 49: return EFLC::CScript::MODEL_MOONBEAM;
		case 50: return EFLC::CScript::MODEL_MRTASTY;
		case 51: return EFLC::CScript::MODEL_MULE;
		case 52: return EFLC::CScript::MODEL_NOOSE;
		case 53: return EFLC::CScript::MODEL_NSTOCKADE;
		case 54: return EFLC::CScript::MODEL_ORACLE;
		case 55: return EFLC::CScript::MODEL_PACKER;
		case 56: return EFLC::CScript::MODEL_PATRIOT;
		case 57: return EFLC::CScript::MODEL_PERENNIAL;
		case 58: return EFLC::CScript::MODEL_PERENNIAL2;
		case 59: return EFLC::CScript::MODEL_PEYOTE;
		case 60: return EFLC::CScript::MODEL_PHANTOM;
		case 61: return EFLC::CScript::MODEL_PINNACLE;
		case 62: return EFLC::CScript::MODEL_PMP600;
		case 63: return EFLC::CScript::MODEL_POLICE;
		case 64: return EFLC::CScript::MODEL_POLICE2;
		case 65: return EFLC::CScript::MODEL_POLPATRIOT;
		case 66: return EFLC::CScript::MODEL_PONY;
		case 67: return EFLC::CScript::MODEL_PREMIER;
		case 68: return EFLC::CScript::MODEL_PRES;
		case 69: return EFLC::CScript::MODEL_PRIMO;
		case 70: return EFLC::CScript::MODEL_PSTOCKADE;
		case 71: return EFLC::CScript::MODEL_RANCHER;
		case 72: return EFLC::CScript::MODEL_REBLA;
		case 73: return EFLC::CScript::MODEL_RIPLEY;
		case 74: return EFLC::CScript::MODEL_ROMERO;
		case 75: return EFLC::CScript::MODEL_ROM;
		case 76: return EFLC::CScript::MODEL_RUINER;
		case 77: return EFLC::CScript::MODEL_SABRE;
		case 78: return EFLC::CScript::MODEL_SABRE2;
		case 79: return EFLC::CScript::MODEL_SABREGT;
		case 80: return EFLC::CScript::MODEL_SCHAFTER;
		case 81: return EFLC::CScript::MODEL_SENTINEL;
		case 82: return EFLC::CScript::MODEL_SOLAIR;
		case 83: return EFLC::CScript::MODEL_SPEEDO;
		case 84: return EFLC::CScript::MODEL_STALION;
		case 85: return EFLC::CScript::MODEL_STEED;
		case 86: return EFLC::CScript::MODEL_STOCKADE;
		case 87: return EFLC::CScript::MODEL_STRATUM;
		case 88: return EFLC::CScript::MODEL_STRETCH;
		case 89: return EFLC::CScript::MODEL_SULTAN;
		case 90: return EFLC::CScript::MODEL_SULTANRS;
		case 91: return EFLC::CScript::MODEL_SUPERGT;
		case 92: return EFLC::CScript::MODEL_TAXI;
		case 93: return EFLC::CScript::MODEL_TAXI2;
		case 94: return EFLC::CScript::MODEL_TRASH;
		case 95: return EFLC::CScript::MODEL_TURISMO;
		case 96: return EFLC::CScript::MODEL_URANUS;
		case 97: return EFLC::CScript::MODEL_VIGERO;
		case 98: return EFLC::CScript::MODEL_VIGERO2;
		case 99: return EFLC::CScript::MODEL_VINCENT;
		case 100: return EFLC::CScript::MODEL_VIRGO;
		case 101: return EFLC::CScript::MODEL_VOODOO;
		case 102: return EFLC::CScript::MODEL_WASHINGTON;
		case 103: return EFLC::CScript::MODEL_WILLARD;
		case 104: return EFLC::CScript::MODEL_YANKEE;
		case 105: return EFLC::CScript::MODEL_BOBBER;
		case 106: return EFLC::CScript::MODEL_FAGGIO;
		case 107: return EFLC::CScript::MODEL_HELLFURY;
		case 108: return EFLC::CScript::MODEL_NRG900;
		case 109: return EFLC::CScript::MODEL_PCJ;
		case 110: return EFLC::CScript::MODEL_SANCHEZ;
		case 111: return EFLC::CScript::MODEL_ZOMBIEB;
		case 112: return EFLC::CScript::MODEL_ANNIHILATOR;
		case 113: return EFLC::CScript::MODEL_MAVERICK;
		case 114: return EFLC::CScript::MODEL_POLMAV;
		case 115: return EFLC::CScript::MODEL_TOURMAV;
		case 116: return EFLC::CScript::MODEL_DINGHY;
		case 117: return EFLC::CScript::MODEL_JETMAX;
		case 118: return EFLC::CScript::MODEL_MARQUIS;
		case 119: return EFLC::CScript::MODEL_PREDATOR;
		case 120: return EFLC::CScript::MODEL_REEFER;
		case 121: return EFLC::CScript::MODEL_SQUALO;
		case 122: return EFLC::CScript::MODEL_TUGA;
		case 123: return EFLC::CScript::MODEL_TROPIC;
		case 124: return EFLC::CScript::MODEL_CABLECAR;
		case 125: return EFLC::CScript::MODEL_SUBWAY_LO;
		case 126: return EFLC::CScript::MODEL_SUBWAY_HI;

		case 127: return EFLC::CScript::MODEL_SLAMVAN;
		case 128: return EFLC::CScript::MODEL_CADDY;
		case 129: return EFLC::CScript::MODEL_APC;
		case 130: return EFLC::CScript::MODEL_SUPERD;
		case 131: return EFLC::CScript::MODEL_SUPERD2;
		case 132: return EFLC::CScript::MODEL_SERRANO;
		case 133: return EFLC::CScript::MODEL_SERRANO2;
		case 134: return EFLC::CScript::MODEL_BUFFALO;
		case 135: return EFLC::CScript::MODEL_AVAN;
		case 136: return EFLC::CScript::MODEL_SCHAFTER2;
		case 137: return EFLC::CScript::MODEL_SCHAFTER3;
		case 138: return EFLC::CScript::MODEL_BULLET;
		case 139: return EFLC::CScript::MODEL_TAMPA;
		case 140: return EFLC::CScript::MODEL_CAVALCADE2;
		case 141: return EFLC::CScript::MODEL_F620;
		case 142: return EFLC::CScript::MODEL_LIMO2;
		case 143: return EFLC::CScript::MODEL_POLICE3;
		case 144: return EFLC::CScript::MODEL_POLICEW;
		case 145: return EFLC::CScript::MODEL_POLICE4;
		case 146: return EFLC::CScript::MODEL_POLICEB;
		case 147: return EFLC::CScript::MODEL_HEXER;
		case 148: return EFLC::CScript::MODEL_FAGGIO2;
		case 149: return EFLC::CScript::MODEL_BATI2;
		case 150: return EFLC::CScript::MODEL_VADER;
		case 151: return EFLC::CScript::MODEL_AKUMA;
		case 152: return EFLC::CScript::MODEL_HAKUCHOU;
		case 153: return EFLC::CScript::MODEL_DOUBLE;
		case 154: return EFLC::CScript::MODEL_BUZZARD;
		case 155: return EFLC::CScript::MODEL_SWIFT;
		case 156: return EFLC::CScript::MODEL_SKYLIFT;
		case 157: return EFLC::CScript::MODEL_SMUGGLER;
		case 158: return EFLC::CScript::MODEL_FLOATER;
		case 159: return EFLC::CScript::MODEL_BLADE;
		case 160: return EFLC::CScript::MODEL_GBURRITO;
		case 161: return EFLC::CScript::MODEL_TOWTRUCK;
		case 162: return EFLC::CScript::MODEL_PACKER2;
		case 163: return EFLC::CScript::MODEL_PBUS;
		case 164: return EFLC::CScript::MODEL_YANKEE2;
		case 165: return EFLC::CScript::MODEL_RHAPSODY;
		case 166: return EFLC::CScript::MODEL_REGINA;
		case 167: return EFLC::CScript::MODEL_ANGEL;
		case 168: return EFLC::CScript::MODEL_BATI;
		case 169: return EFLC::CScript::MODEL_DAEMON;
		case 170: return EFLC::CScript::MODEL_DIABOLUS;
		case 171: return EFLC::CScript::MODEL_DOUBLE2;
		case 172: return EFLC::CScript::MODEL_HAKUCHOU2;
		case 173: return EFLC::CScript::MODEL_INNOVATION;
		case 174: return EFLC::CScript::MODEL_LYCAN;
		case 175: return EFLC::CScript::MODEL_NIGHTBLADE;
		case 176: return EFLC::CScript::MODEL_REVENANT;
		case 177: return EFLC::CScript::MODEL_WAYFARER;
		case 178: return EFLC::CScript::MODEL_WOLFSBANE;
		default: return 0;
	}
}

int CCharacterManager::ModelHashToVehicleId(DWORD dwModelHash)
{
	switch(dwModelHash)
	{
	case EFLC::CScript::MODEL_ADMIRAL: return 0;
	case EFLC::CScript::MODEL_AIRTUG: return 1;
	case EFLC::CScript::MODEL_AMBULANCE: return 2;
	case EFLC::CScript::MODEL_BANSHEE: return 3;
	case EFLC::CScript::MODEL_BENSON: return 4;
	case EFLC::CScript::MODEL_BIFF: return 5;
	case EFLC::CScript::MODEL_BLISTA: return 6;
	case EFLC::CScript::MODEL_BOBCAT: return 7;
	case EFLC::CScript::MODEL_BOXVILLE: return 8;
	case EFLC::CScript::MODEL_BUCCANEER: return 9;
	case EFLC::CScript::MODEL_BURRITO: return 10;
	case EFLC::CScript::MODEL_BURRITO2: return 11;
	case EFLC::CScript::MODEL_BUS: return 12;
	case EFLC::CScript::MODEL_CABBY: return 13;
	case EFLC::CScript::MODEL_CAVALCADE: return 14;
	case EFLC::CScript::MODEL_CHAVOS: return 15;
	case EFLC::CScript::MODEL_COGNOSCENTI: return 16;
	case EFLC::CScript::MODEL_COMET: return 17;
	case EFLC::CScript::MODEL_COQUETTE: return 18;
	case EFLC::CScript::MODEL_DF8: return 19;
	case EFLC::CScript::MODEL_DILETTANTE: return 20;
	case EFLC::CScript::MODEL_DUKES: return 21;
	case EFLC::CScript::MODEL_E109: return 22;
	case EFLC::CScript::MODEL_EMPEROR: return 23;
	case EFLC::CScript::MODEL_EMPEROR2: return 24;
	case EFLC::CScript::MODEL_ESPERANTO: return 25;
	case EFLC::CScript::MODEL_FACTION: return 26;
	case EFLC::CScript::MODEL_FBI: return 27;
	case EFLC::CScript::MODEL_FELTZER: return 28;
	case EFLC::CScript::MODEL_FEROCI: return 29;
	case EFLC::CScript::MODEL_FEROCI2: return 30;
	case EFLC::CScript::MODEL_FIRETRUK: return 31;
	case EFLC::CScript::MODEL_FLATBED: return 32;
	case EFLC::CScript::MODEL_FORTUNE: return 33;
	case EFLC::CScript::MODEL_FORKLIFT: return 34;
	case EFLC::CScript::MODEL_FUTO: return 35;
	case EFLC::CScript::MODEL_FXT: return 36;
	case EFLC::CScript::MODEL_HABANERO: return 37;
	case EFLC::CScript::MODEL_HAKUMAI: return 38;
	case EFLC::CScript::MODEL_HUNTLEY: return 39;
	case EFLC::CScript::MODEL_INFERNUS: return 40;
	case EFLC::CScript::MODEL_INGOT: return 41;
	case EFLC::CScript::MODEL_INTRUDER: return 42;
	case EFLC::CScript::MODEL_LANDSTALKER: return 43;
	case EFLC::CScript::MODEL_LOKUS: return 44;
	case EFLC::CScript::MODEL_MANANA: return 45;
	case EFLC::CScript::MODEL_MARBELLA: return 46;
	case EFLC::CScript::MODEL_MERIT: return 47;
	case EFLC::CScript::MODEL_MINIVAN: return 48;
	case EFLC::CScript::MODEL_MOONBEAM: return 49;
	case EFLC::CScript::MODEL_MRTASTY: return 50;
	case EFLC::CScript::MODEL_MULE: return 51;
	case EFLC::CScript::MODEL_NOOSE: return 52;
	case EFLC::CScript::MODEL_NSTOCKADE: return 53;
	case EFLC::CScript::MODEL_ORACLE: return 54;
	case EFLC::CScript::MODEL_PACKER: return 55;
	case EFLC::CScript::MODEL_PATRIOT: return 56;
	case EFLC::CScript::MODEL_PERENNIAL: return 57;
	case EFLC::CScript::MODEL_PERENNIAL2: return 58;
	case EFLC::CScript::MODEL_PEYOTE: return 59;
	case EFLC::CScript::MODEL_PHANTOM: return 60;
	case EFLC::CScript::MODEL_PINNACLE: return 61;
	case EFLC::CScript::MODEL_PMP600: return 62;
	case EFLC::CScript::MODEL_POLICE: return 63;
	case EFLC::CScript::MODEL_POLICE2: return 64;
	case EFLC::CScript::MODEL_POLPATRIOT: return 65;
	case EFLC::CScript::MODEL_PONY: return 66;
	case EFLC::CScript::MODEL_PREMIER: return 67;
	case EFLC::CScript::MODEL_PRES: return 68;
	case EFLC::CScript::MODEL_PRIMO: return 69;
	case EFLC::CScript::MODEL_PSTOCKADE: return 70;
	case EFLC::CScript::MODEL_RANCHER: return 71;
	case EFLC::CScript::MODEL_REBLA: return 72;
	case EFLC::CScript::MODEL_RIPLEY: return 73;
	case EFLC::CScript::MODEL_ROMERO: return 74;
	case EFLC::CScript::MODEL_ROM: return 75;
	case EFLC::CScript::MODEL_RUINER: return 76;
	case EFLC::CScript::MODEL_SABRE: return 77;
	case EFLC::CScript::MODEL_SABRE2: return 78;
	case EFLC::CScript::MODEL_SABREGT: return 79;
	case EFLC::CScript::MODEL_SCHAFTER: return 80;
	case EFLC::CScript::MODEL_SENTINEL: return 81;
	case EFLC::CScript::MODEL_SOLAIR: return 82;
	case EFLC::CScript::MODEL_SPEEDO: return 83;
	case EFLC::CScript::MODEL_STALION: return 84;
	case EFLC::CScript::MODEL_STEED: return 85;
	case EFLC::CScript::MODEL_STOCKADE: return 86;
	case EFLC::CScript::MODEL_STRATUM: return 87;
	case EFLC::CScript::MODEL_STRETCH: return 88;
	case EFLC::CScript::MODEL_SULTAN: return 89;
	case EFLC::CScript::MODEL_SULTANRS: return 90;
	case EFLC::CScript::MODEL_SUPERGT: return 91;
	case EFLC::CScript::MODEL_TAXI: return 92;
	case EFLC::CScript::MODEL_TAXI2: return 93;
	case EFLC::CScript::MODEL_TRASH: return 94;
	case EFLC::CScript::MODEL_TURISMO: return 95;
	case EFLC::CScript::MODEL_URANUS: return 96;
	case EFLC::CScript::MODEL_VIGERO: return 97;
	case EFLC::CScript::MODEL_VIGERO2: return 98;
	case EFLC::CScript::MODEL_VINCENT: return 99;
	case EFLC::CScript::MODEL_VIRGO: return 100;
	case EFLC::CScript::MODEL_VOODOO: return 101;
	case EFLC::CScript::MODEL_WASHINGTON: return 102;
	case EFLC::CScript::MODEL_WILLARD: return 103;
	case EFLC::CScript::MODEL_YANKEE: return 104;
	case EFLC::CScript::MODEL_BOBBER: return 105;
	case EFLC::CScript::MODEL_FAGGIO: return 106;
	case EFLC::CScript::MODEL_HELLFURY: return 107;
	case EFLC::CScript::MODEL_NRG900: return 108;
	case EFLC::CScript::MODEL_PCJ: return 109;
	case EFLC::CScript::MODEL_SANCHEZ: return 110;
	case EFLC::CScript::MODEL_ZOMBIEB: return 111;
	case EFLC::CScript::MODEL_ANNIHILATOR: return 112;
	case EFLC::CScript::MODEL_MAVERICK: return 113;
	case EFLC::CScript::MODEL_POLMAV: return 114;
	case EFLC::CScript::MODEL_TOURMAV: return 115;
	case EFLC::CScript::MODEL_DINGHY: return 116;
	case EFLC::CScript::MODEL_JETMAX: return 117;
	case EFLC::CScript::MODEL_MARQUIS: return 118;
	case EFLC::CScript::MODEL_PREDATOR: return 119;
	case EFLC::CScript::MODEL_REEFER: return 120;
	case EFLC::CScript::MODEL_SQUALO: return 121;
	case EFLC::CScript::MODEL_TUGA: return 122;
	case EFLC::CScript::MODEL_TROPIC: return 123;
	case EFLC::CScript::MODEL_CABLECAR: return 124;
	case EFLC::CScript::MODEL_SUBWAY_LO: return 125;
	case EFLC::CScript::MODEL_SUBWAY_HI: return 126;
	case EFLC::CScript::MODEL_SLAMVAN: return 127;
	case EFLC::CScript::MODEL_CADDY: return 128;
	case EFLC::CScript::MODEL_APC: return 129;
	case EFLC::CScript::MODEL_SUPERD: return 130;
	case EFLC::CScript::MODEL_SUPERD2: return 131;
	case EFLC::CScript::MODEL_SERRANO: return 132;
	case EFLC::CScript::MODEL_SERRANO2: return 133;
	case EFLC::CScript::MODEL_BUFFALO: return 134;
	case EFLC::CScript::MODEL_AVAN: return 135;
	case EFLC::CScript::MODEL_SCHAFTER2: return 136;
	case EFLC::CScript::MODEL_SCHAFTER3: return 137;
	case EFLC::CScript::MODEL_BULLET: return 138;
	case EFLC::CScript::MODEL_TAMPA: return 139;
	case EFLC::CScript::MODEL_CAVALCADE2: return 140;
	case EFLC::CScript::MODEL_F620: return 141;
	case EFLC::CScript::MODEL_LIMO2: return 142;
	case EFLC::CScript::MODEL_POLICE3: return 143;
	case EFLC::CScript::MODEL_POLICEW: return 144;
	case EFLC::CScript::MODEL_POLICE4: return 145;
	case EFLC::CScript::MODEL_POLICEB: return 146;
	case EFLC::CScript::MODEL_HEXER: return 147;
	case EFLC::CScript::MODEL_FAGGIO2: return 148;
	case EFLC::CScript::MODEL_BATI2: return 149;
	case EFLC::CScript::MODEL_VADER: return 150;
	case EFLC::CScript::MODEL_AKUMA: return 151;
	case EFLC::CScript::MODEL_HAKUCHOU: return 152;
	case EFLC::CScript::MODEL_DOUBLE: return 153;
	case EFLC::CScript::MODEL_BUZZARD: return 154;
	case EFLC::CScript::MODEL_SWIFT: return 155;
	case EFLC::CScript::MODEL_SKYLIFT: return 156;
	case EFLC::CScript::MODEL_SMUGGLER: return 157;
	case EFLC::CScript::MODEL_FLOATER: return 158;
	case EFLC::CScript::MODEL_BLADE: return 159;
	case EFLC::CScript::MODEL_GBURRITO: return 160;
	case EFLC::CScript::MODEL_TOWTRUCK: return 161;
	case EFLC::CScript::MODEL_PACKER2: return 162;
	case EFLC::CScript::MODEL_PBUS: return 163;
	case EFLC::CScript::MODEL_YANKEE2: return 164;
	case EFLC::CScript::MODEL_RHAPSODY: return 165;
	case EFLC::CScript::MODEL_REGINA: return 166;
	case EFLC::CScript::MODEL_ANGEL: return 167;
	case EFLC::CScript::MODEL_BATI: return 168;
	case EFLC::CScript::MODEL_DAEMON: return 169;
	case EFLC::CScript::MODEL_DIABOLUS: return 170;
	case EFLC::CScript::MODEL_DOUBLE2: return 171;
	case EFLC::CScript::MODEL_HAKUCHOU2: return 172;
	case EFLC::CScript::MODEL_INNOVATION: return 173;
	case EFLC::CScript::MODEL_LYCAN: return 174;
	case EFLC::CScript::MODEL_NIGHTBLADE: return 175;
	case EFLC::CScript::MODEL_REVENANT: return 176;
	case EFLC::CScript::MODEL_WAYFARER: return 177;
	case EFLC::CScript::MODEL_WOLFSBANE: return 178;
	}

	return -1;
}