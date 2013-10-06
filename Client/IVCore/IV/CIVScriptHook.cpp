//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVScriptHook.cpp
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include <CCore.h>
#include "CIVScriptHook.h"
#include "CIVScript.h"
extern	CCore				* g_pCore;

sRAGETHREAD *	g_pRageScriptThread = NULL;
bool			g_bRageScriptLoaded = false;
int				g_iRageScriptFrames = 0;
bool			bScriptProcssSwitch = false;

struct CIVScriptInstance
{
	int		iSlotID;
	CString	strScriptName;
	DWORD	dwScriptHash;
};

CIVScriptInstance civScripts[] = {
	{0, "ability_backup", 0x71263FB3},
	{1, "ability_bomb", 0xDA511C00},
	{2, "ability_gun_car", 0x703E1C7F},
	{3, "ability_vehicle", 0xC73046F2},
	{4, "advanced_car_actions", 0x61F946BD},
	{5, "air_hockey", 0x98CD90D1},
	{6, "air_hockey_trigger", 0x518D2C1C},
	{7, "ambairpotarea", 0x3C05B89F},
	{8, "ambatmq", 0x0E4777CC},
	{9, "ambbar", 0x7BE0260D},
	{10, "ambbarrier", 0xE862E5FB},
	{11, "ambbeggar", 0xBFBA3FAC},
	{12, "ambblkhawk", 0xB348D246},
	{13, "ambbouncer", 0x4230D4FF},
	{14, "ambbridgepatrol", 0x839084B0},
	{15, "ambbusker", 0x01C1ED17},
	{16, "ambcabaret", 0xA90E793F},
	{17, "ambcargoholddoors", 0x55CEDBC1},
	{18, "ambchurchdoors", 0x46ACFC4C},
	{19, "ambclublights", 0x6CA650B9},
	{20, "ambcomedyclub", 0x7DE95ED9},
	{21, "ambcontrolloader", 0xB8F607A7},
	{22, "ambcontrolmain", 0xA0447973},
	{23, "ambdealer", 0x71E5B8BC},
	{24, "ambdebug", 0x25E4750B},
	{25, "ambdrinking", 0x3D63648B},
	{26, "ambfloater", 0x255D5830},
	{27, "ambfoodeating", 0xACA5B0A9},
	{28, "ambfunfair", 0x51BB315F},
	{29, "ambgerry3doorlock", 0x3325ED3C},
	{30, "ambhelicopter", 0x527035B8},
	{31, "ambhomelandcordon", 0xE7F4D13A},
	{32, "ambhomelandfed", 0x2E11949E},
	{33, "ambhomelandsirens", 0x0E9E8C39},
	{34, "ambhotel", 0xB14945B1},
	{35, "ambinternetcafe", 0xF05A9BC4},
	{36, "ambjerseydocksgates", 0xD4D11204},
	{37, "ambjimslocks", 0x48767D99},
	{38, "ambliftdoors", 0x09BF0E27},
	{39, "ambnightclubbm", 0x0935D0A0},
	{40, "ambnightclubbm2", 0xFF98A5D4},
	{41, "ambnightclubbm_min", 0x83271B9B},
	{42, "ambnightclubext", 0x0AAC612E},
	{43, "ambnightclubhc", 0xFD0B3683},
	{44, "ambnightclubhc2", 0xB9359772},
	{45, "ambnightclubm9", 0xEF6070B1},
	{46, "ambnightclubm92", 0x9808DBF9},
	{47, "ambpimpnpros", 0xCB41B172},
	{48, "ambpoledancer", 0x9DBDECD9},
	{49, "ambpolrdblk", 0x771784D7},
	{50, "ambpreacher", 0x17CEEBCC},
	{51, "ambprisonwanted", 0xBBCB77B8},
	{52, "ambsavebed", 0x3B22A70D},
	{53, "ambshowroom", 0xF4D02818},
	{54, "ambstripclub", 0x0D98964A},
	{55, "ambtaxdpt", 0x1F803874},
	{56, "ambtaxihail", 0xDD098F7C},
	{57, "ambtoiletdoors", 0x63CA45F4},
	{58, "ambtunnelcops", 0x0649BB15},
	{59, "ambtv", 0xD0169A3C},
	{60, "ambunarea", 0x38E948C4},
	{61, "ambwardrobe", 0x962372BF},
	{62, "ambwindowlift", 0xD58EBCE6},
	{63, "arnaud1", 0x0A2FF225},
	{64, "arnaud2", 0xFC8256CA},
	{65, "arrestescapehelp", 0x391CF21A},
	{66, "atmobj", 0x7BF7BB6A},
	{67, "badman_1", 0x0A37C71E},
	{68, "basejumping", 0x18DF9A35},
	{69, "basejumplauncher", 0x9997670E},
	{70, "basejumpscreen", 0x5FA2FE95},
	{71, "bell2", 0x17C0D75F},
	{72, "bell3m", 0x59C8059A},
	{73, "bell3p", 0x94597AC0},
	{74, "bell5", 0x39531A83},
	{75, "bell6", 0x4B20BE1E},
	{76, "bell7", 0x980C57EC},
	{77, "bernie1", 0x96BCDEC9},
	{78, "bernie2", 0x806DB22B},
	{79, "bernie3", 0xA81A8184},
	{80, "berniecar", 0xF1F419AC},
	{81, "binco_brook_s", 0xFFEA2652},
	{82, "boating", 0x94C8CB23},
	{83, "bootycall", 0x9B889B55},
	{84, "bootycallcontroll", 0x2B651CD2},
	{85, "bowling_lane", 0x585FB99D},
	{86, "bowl_trigger", 0x01BDF165},
	{87, "brian_1", 0x969A14AB},
	{88, "brian_2", 0xB1F94B69},
	{89, "brian_3", 0xC43DEFF2},
	{90, "brother1", 0xA2E4F8CF},
	{91, "brother2", 0x8835C371},
	{92, "brother3", 0xB6BAA07A},
	{93, "brucie1", 0x196C2FC3},
	{94, "brucie2", 0xC4A1862F},
	{95, "brucie3a", 0xB96F033B},
	{96, "brucie3b", 0xABB567C8},
	{97, "brucie3_meetguy", 0x87C80997},
	{98, "brucie4", 0xAE3CD966},
	{99, "brucie5m", 0x1F304C74},
	{100, "brucie5p", 0xA492573A},
	{101, "brucieboat", 0x26DBE081},
	{102, "bruciecopter", 0x1FCFD48A},
	{103, "bruciedrink", 0xDFB1A7B5},
	{104, "brucieeat", 0xBABA0E5E},
	{105, "brucielift", 0xBEDDB17F},
	{106, "brucieshow", 0xD9615450},
	{107, "bruciestrip", 0xEAC1100B},
	{108, "brucietenpin", 0x4FD04CC7},
	{109, "brucie_heli", 0x4457A957},
	{110, "bulgarin1", 0xB3AE857D},
	{111, "bulgarin2", 0x2E907B2B},
	{112, "bulgarin3", 0x3CD197AD},
	{113, "burgervendor", 0x081054F4},
	{114, "busstop", 0xFC886CC9},
	{115, "cablecars", 0x45BBAD0E},
	{116, "cardivehelp", 0x7320F75E},
	{117, "carfoodrunjack", 0x421CED43},
	{118, "carwash", 0x9978380B},
	{119, "car_theft_texts", 0x26E02435},
	{120, "cherise", 0x8A941072},
	{121, "cia1", 0x14EC4D4A},
	{122, "cia2", 0x434729FF},
	{123, "cia3", 0xD0BF44F5},
	{124, "cia4", 0xFE6D2050},
	{125, "ciawanted", 0xF0FDE76D},
	{126, "clarence", 0x00357063},
	{127, "cleanupray5trains", 0x47BC09BE},
	{128, "clubmanblips", 0xFA4B8F0C},
	{129, "clubmanphonecalls", 0x433CF887},
	{130, "clubsecurity", 0xA050E6EE},
	{131, "computermain", 0xCB1BABDC},
	{132, "computernews", 0x3FCA64FC},
	{133, "computerstreamed", 0x272ED25B},
	{134, "copbootsearch", 0xB02A1AC5},
	{135, "daisy1", 0x9127B746},
	{136, "dancing", 0x87E51030},
	{137, "darts", 0x8E8E6AF8},
	{138, "darts_launcher", 0x1B422F71},
	{139, "darts_trigger", 0xB22A33D8},
	{140, "date_activity", 0x78B9D855},
	{141, "date_food", 0xFC8282F5},
	{142, "dating_alex", 0x157E64C9},
	{143, "dating_carmen", 0xED6B6417},
	{144, "dating_kate", 0xE6633854},
	{145, "dating_kiki", 0x17768EB9},
	{146, "dating_michelle", 0x33D97328},
	{147, "deatharresthelp", 0x68914395},
	{148, "derrick1", 0x43085EBD},
	{149, "derrick2", 0x262724FB},
	{150, "derrick3", 0x176B8784},
	{151, "dominicanfriend", 0x0A97155F},
	{152, "drinking", 0xDE14822E},
	{153, "drinkingrect", 0xC50A9D17},
	{154, "drugwarscontrol", 0xB7BA8FCB},
	{155, "drugwarsconvoy", 0x7FE9E249},
	{156, "drugwarscreen", 0x4A160A68},
	{157, "drugwarsdeal", 0x524CAEDC},
	{158, "drugwarspickup", 0xE3FD26AF},
	{159, "drugwarsshipment", 0xA7627AED},
	{160, "drunk", 0x3FDBA102},
	{161, "drunkcontroller", 0x2BAE9297},
	{162, "dwayne1", 0x56761474},
	{163, "dwayne3", 0x7AF3DD6F},
	{164, "dwaynecherise", 0x83BA235C},
	{165, "dwaynedrink", 0x20CC5DEC},
	{166, "dwayneeat", 0xCCDE3C1C},
	{167, "dwayneemail", 0x838D9A09},
	{168, "dwayneshow", 0xBE839211},
	{169, "dwaynestrip", 0x4857F8D8},
	{170, "dwaynetenpin", 0x2E8FA300},
	{171, "dwayne_backup", 0x22459B37},
	{172, "e2endcredits", 0xE7793361},
	{173, "e2rewards", 0xB670C396},
	{174, "e2stattracker", 0x143C70F2},
	{175, "eddie1", 0xE840FD39},
	{176, "eddie2", 0x4188AFC3},
	{177, "elizabeta1", 0x165F5045},
	{178, "elizabeta2", 0x489034A6},
	{179, "elizabeta3", 0xFAD9993A},
	{180, "elizabeta3vehicle", 0x7C375335},
	{181, "elizabeta4", 0x2D037D8D},
	{182, "emergencycall", 0xFA2AD384},
	{183, "empiredown", 0x006416B2},
	{184, "empiretelescope", 0x2CE6804B},
	{185, "endcreditroll", 0xBE54CD5E},
	{186, "endgamenews", 0x6AA1F30E},
	{187, "faustin1", 0xC1568EFB},
	{188, "faustin2", 0xD1C32FD4},
	{189, "faustin3", 0x9F634B11},
	{190, "faustin4", 0xB2977179},
	{191, "faustin5", 0x88511CED},
	{192, "faustin5_fire", 0xCEF8B541},
	{193, "faustin6", 0xDD13C67D},
	{194, "faustin7", 0x07251A9F},
	{195, "fightclublauncher", 0x0CD9E668},
	{196, "fightclubring", 0x7CEB8820},
	{197, "fightclubscreen", 0xEA80B13B},
	{198, "finale1a", 0x8F959493},
	{199, "finale1b", 0xFB236BB5},
	{200, "finale1c", 0xECE5CF3A},
	{201, "finale1d", 0x96C722FE},
	{202, "finale2", 0xEA2671F0},
	{203, "finaleaorb", 0xC1719B5C},
	{204, "finaleintrocut", 0x1DEE2AD6},
	{205, "finalewedtxts", 0x35E83D24},
	{206, "foodserver", 0xA9C429D7},
	{207, "francis1", 0x455B7828},
	{208, "francis2a", 0x985FAC5D},
	{209, "francis2b", 0x7B35F1DE},
	{210, "francis2_appointment", 0x8B34E832},
	{211, "francis3", 0x8BBA84E9},
	{212, "francis4", 0x9AF82364},
	{213, "francis5", 0x7058CE22},
	{214, "francis6", 0xF04C4E0B},
	{215, "friends1", 0xA6D3F36A},
	{216, "friends2", 0x289A7701},
	{217, "gambetti1", 0x1B40EAF1},
	{218, "gambetti2", 0x9DCEF00B},
	{219, "gambetti3", 0x748F9D8D},
	{220, "garbage_trucks", 0x86B22CB7},
	{221, "gerry1", 0xFF61524E},
	{222, "gerry1_base", 0x4DA30466},
	{223, "gerry2", 0xF5F33F6A},
	{224, "gerry3a", 0x2E25024F},
	{225, "gerry3b", 0x3DD7A1B4},
	{226, "gerry3c", 0x6B88FD16},
	{227, "gerry3_phonegirl", 0x903A5733},
	{228, "gerry4", 0x0E54F02D},
	{229, "gerry5", 0x010F55A2},
	{230, "golf", 0x299717F2},
	{231, "golf_launcher", 0xEFB046A8},
	{232, "go_on_date", 0xAA2741AF},
	{233, "gracie", 0x4855E988},
	{234, "gunlockup", 0x67603488},
	{235, "gunlockupct", 0x789E1BE4},
	{236, "handbrakehelp", 0xDE6D4BB0},
	{237, "happytshirt", 0x0D713D41},
	{238, "helicopter", 0xBEBEE520},
	{239, "hospitalpickup", 0xC95A3943},
	{240, "hossan_1", 0x87A5FE07},
	{241, "hotwirehelp", 0x670C10FA},
	{242, "ilyena", 0x04AF02E0},
	{243, "ilyena_calls", 0x64BC793E},
	{244, "independencefm", 0xE4AEDEE7},
	{245, "initial", 0x8C56D5FD},
	{246, "internet_dating", 0x12E2D9FA},
	{247, "ivan_1", 0x753DA828},
	{248, "jacob1", 0x37F80AC6},
	{249, "jacob2", 0x9AA7D024},
	{250, "jacob3m", 0x87AF3AF7},
	{251, "jacob3p", 0x29C6FF24},
	{252, "jacobdarts", 0x29604C39},
	{253, "jacobdrink", 0xB9DDEBE5},
	{254, "jacobeat", 0xFEBDB85E},
	{255, "jacoblift", 0x7947B9E2},
	{256, "jacobpool", 0x5740BCF0},
	{257, "jacobshow", 0xADC71162},
	{258, "jacobstrip", 0x7894BF3B},
	{259, "jacob_gun_car", 0xCED350C1},
	{260, "jeff_1", 0x07C9B53C},
	{261, "jeff_1_mission", 0x59C19917},
	{262, "jeff_2", 0x860C31C7},
	{263, "jeff_3", 0x765D926A},
	{264, "jimmy1", 0xBCBF1A30},
	{265, "jimmy2", 0xCF56BF5F},
	{266, "jimmy3", 0x064BAD54},
	{267, "jimmy4", 0x10FCC2B6},
	{268, "jimmy4a", 0x7746C78B},
	{269, "jimmysuit", 0xA82C1D63},
	{270, "laterweapons", 0x1387A01F},
	{271, "magvendor", 0xF9ABA52C},
	{272, "main", 0x27EB33D7},
	{273, "manhat_heli_tours", 0x7C3C3420},
	{274, "manny1", 0xAC360909},
	{275, "manny2", 0xBE8BADB4},
	{276, "manny3", 0x4471397D},
	{277, "margot1", 0x6DEAC215},
	{278, "margot2", 0x2F8AC552},
	{279, "marnie1", 0x06453059},
	{280, "marnie2", 0xD89754FE},
	{281, "mel", 0x0571AE34},
	{282, "michelle1", 0x0B1FD642},
	{283, "michelle1_queue", 0x5781C526},
	{284, "michelle_introcalls", 0x34940F6E},
	{285, "missionresulthelp", 0xE8FB5E29},
	{286, "missionresultstimer", 0x18B3B49E},
	{287, "missionstattracker", 0xFEED33D0},
	{288, "modo_manhat_5", 0x7882221E},
	{289, "mostwanted", 0x9132101E},
	{290, "mptutoriallauncher", 0xAD58A292},
	{291, "multiplayertutorial", 0x63609BDC},
	{292, "multitutorial", 0xD277C86A},
	{293, "mum1", 0xA9A0CD6C},
	{294, "network_session", 0xA5971010},
	{295, "nutvendor", 0x334D24CD},
	{296, "opening_credits", 0x8EFA5B1C},
	{297, "organiserhelp", 0x8115C24D},
	{298, "packie1", 0xEEFAC141},
	{299, "packie2", 0x00C864DC},
	{300, "packie3", 0xDBD81AFC},
	{301, "packiedarts", 0xBE9E9620},
	{302, "packiedrink", 0xDEC5232D},
	{303, "packiepool", 0x45BCFE9A},
	{304, "packieshow", 0x45837CE0},
	{305, "packiestrip", 0x014BAD25},
	{306, "packiesuit", 0x7F946CF9},
	{307, "packietenpin", 0x01A4C625},
	{308, "packie_bomb", 0xC7164234},
	{309, "parachutelauncher", 0xDB64F5BB},
	{310, "parachute_ai", 0xF7866625},
	{311, "parachute_player", 0x98751695},
	{312, "pathos1", 0x3B4E8E80},
	{313, "pathos2", 0x848820EE},
	{314, "pdbhangoutmgr", 0xEC05A6DF},
	{315, "pdbhomemgr", 0xA1211084},
	{316, "pdbmostwanted", 0x87B1C68B},
	{317, "perseus_manhat_8", 0x84F10489},
	{318, "phonepadhelp", 0xF67B5D50},
	{319, "phoneprofilehelp", 0xEEEA9592},
	{320, "physicstestbed", 0x8972E1B8},
	{321, "placeholder", 0xC1287E2E},
	{322, "playboy2", 0xED2E64EB},
	{323, "playboy3", 0xE87A5B83},
	{324, "playboy4", 0x99BB3E06},
	{325, "policebackup", 0xE0F8F4EA},
	{326, "policetest", 0xA2E0F8A4},
	{327, "pool_game", 0x88123A9C},
	{328, "pool_table", 0x1CD1F336},
	{329, "puzzle", 0x881750F6},
	{330, "puzzle_launcher", 0x6EF7E685},
	{331, "pxdfcut", 0x14A98617},
	{332, "racesp", 0xAAA6EBB9},
	{333, "racesplauncher", 0x2273A76D},
	{334, "racesscreen", 0xF3C8C659},
	{335, "ray1", 0xE3C1011B},
	{336, "ray2", 0x10755A6F},
	{337, "ray3", 0xE73407ED},
	{338, "ray4", 0xAC0F11A4},
	{339, "ray5", 0x21D5FD30},
	{340, "ray6", 0xCECE5722},
	{341, "repeat", 0xFF80069D},
	{342, "replayhelp", 0x97FFEDEC},
	{343, "replaytutorial", 0xA8DD67E0},
	{344, "rocco1", 0x3C52E5B3},
	{345, "roman1", 0xFCF2C3F4},
	{346, "roman10m", 0x98456D63},
	{347, "roman10p", 0x168CE9F8},
	{348, "roman11", 0xE1B461AE},
	{349, "roman12", 0x657D6946},
	{350, "roman13", 0x5B5754FA},
	{351, "roman14", 0x4919B07F},
	{352, "roman2", 0xCF9C6948},
	{353, "roman3", 0xA0778AFF},
	{354, "roman3txtmsgrepeat", 0x76E59873},
	{355, "roman4", 0x64DC13E5},
	{356, "roman5", 0x96A4F776},
	{357, "roman6", 0x8836DA9A},
	{358, "roman7", 0x3A27BE7D},
	{359, "roman8m", 0x33BA3476},
	{360, "roman8p", 0xDA9B0245},
	{361, "roman9", 0x3EFFC82D},
	{362, "romanblips", 0x5E38E67F},
	{363, "romandarts", 0xE3C77EE7},
	{364, "romandrink", 0x601582DB},
	{365, "romaneat", 0x52BD5AD6},
	{366, "romanmarker", 0x679C53CC},
	{367, "romanpool", 0x30B53479},
	{368, "romanshow", 0x0F5C3DB6},
	{369, "romanstrip", 0xF03A430E},
	{370, "romantenpin", 0x84D5BCD2},
	{371, "roman_bleedoutintro", 0x5634B9F2},
	{372, "roman_fakeblip", 0x0EF28C44},
	{373, "roman_taxi", 0xCACD9E09},
	{374, "sara2", 0xB062E737},
	{375, "sara_1", 0xBCBA32CF},
	{376, "scratchpad", 0x8DE092F5},
	{377, "sixaxistutlauncher", 0xEB15507F},
	{378, "sixaxistutorial", 0x06208CC1},
	{379, "spcellphone", 0x22C04136},
	{380, "spcellphonecalling", 0x80F1E2C9},
	{381, "spcellphonedebug", 0x000D3211},
	{382, "spcellphoneendcall", 0x5D5F147A},
	{383, "spcellphonemain", 0xF1D7116F},
	{384, "spcellphonenetwork", 0x07564A14},
	{385, "spcellphonetutorial", 0x2D2A1660},
	{386, "speechcontrol", 0x65474C6E},
	{387, "sprunk", 0xCD3B6887},
	{388, "startup", 0x41D6F794},
	{389, "stattracker", 0xFDA96C63},
	{390, "stat_bridge", 0xEA9BC9C7},
	{391, "storytimer", 0x91ACD097},
	{392, "stunt", 0x81794C70},
	{393, "taxi", 0xC703DB5F},
	{394, "taxi_trigger", 0x33147A63},
	{395, "telescope", 0xFCB3CFDB},
	{396, "tenpinbowl", 0xF9F91D07},
	{397, "text_link_mission", 0xB63948A2},
	{398, "till", 0xF24DB8B1},
	{399, "toilet_activity", 0x0E0C8AE2},
	{400, "tollbooth", 0x07B3C2BF},
	{401, "tony1", 0x5BEE6FEC},
	{402, "tony10", 0x9E3F748D},
	{403, "tony11", 0x696E0AEB},
	{404, "tony2", 0x12D95DB3},
	{405, "tony3", 0x0021B844},
	{406, "tony4a", 0xE2621209},
	{407, "tony4b", 0xF8303DA5},
	{408, "tony5", 0x80ED39CD},
	{409, "tony6", 0x6DD713A1},
	{410, "tony7", 0xDC387066},
	{411, "tony8", 0xCB894F08},
	{412, "tony9", 0xB9CEAB93},
	{413, "tonylauncher", 0x52B78D34},
	{414, "tonym1", 0x0C11FA69},
	{415, "tonym2", 0x225326EB},
	{416, "tonym3", 0xED96BD73},
	{417, "tonym4", 0xDBC419CE},
	{418, "tonym5", 0xC8FEF444},
	{419, "tonym6", 0xB75150E9},
	{420, "tonym7", 0xC134E4B4},
	{421, "tonym8", 0xAF074059},
	{422, "tonypreblogb", 0xF32BCEA5},
	{423, "trainhelper", 0x545BCD56},
	{424, "txtmsghelp", 0x20D7EBBE},
	{425, "vendor", 0x70A868FF},
	{426, "vigilante", 0xB5EF4C33},
	{427, "vlad1", 0x295FE359},
	{428, "vlad2", 0xF300F6A0},
	{429, "vlad3", 0x0CD42A42},
	{430, "vlad4", 0x1D8F4B80},
	{431, "wantedhelp", 0x11F4888C},
	{432, "waypointhelp", 0xE22DC121},
	{433, "webalexblog", 0xAB4EA03E},
	{434, "webautoeroticar", 0x055B8993},
	{435, "webcelebcomment", 0xDE1634A8},
	{436, "webcelebinatorblog", 0x9A24F321},
	{437, "webcraplist", 0x2773346F},
	{438, "webdating", 0x2C92B946},
	{439, "webdatingboys", 0xE918397C},
	{440, "webdatingfullprofile", 0x79DAB8ED},
	{441, "webdatinggirls", 0x50263875},
	{442, "webeddieblog", 0xF7F53DCC},
	{443, "webemail", 0xB30CF82A},
	{444, "weberror", 0xB35EBE6E},
	{445, "webeyefind", 0xD94FE846},
	{446, "webeyefindsearch", 0x9EF7A83F},
	{447, "weblawyerscareer", 0x8D7377B4},
	{448, "weblawyerscv", 0x199E2F68},
	{449, "weblcpd", 0x234006F6},
	{450, "weblcpdprofile", 0xAB7B6DD0},
	{451, "weblibertytree", 0x7B4A0485},
	{452, "weblibertytreenews", 0x664EF3AB},
	{453, "webourownreality", 0x168C9D24},
	{454, "webpublicliberty", 0xFDEB09C8},
	{455, "webrealestate", 0x934E51AF},
	{456, "webringtones", 0xD65B4DCC},
	{457, "webringtonesmono", 0xB47D6F4E},
	{458, "webringtonespoly", 0xD35931CB},
	{459, "webringtonespurchase", 0xA0F833A0},
	{460, "webringtonestheme", 0x4CA42BC0},
	{461, "webweazel", 0xE82F6918},
	{462, "webweazelnews", 0x5E8D3929},
	{463, "webwhatthey", 0x50DE8373},
	{464, "window_lift_launcher", 0xC6926665},
	{465, "yusuf1", 0x79E1F503},
	{466, "yusuf1cleanup", 0x435678FC},
	{467, "yusuf2", 0x67B650AC},
	{468, "yusuf3", 0x456F0C1E},
	{469, "yusuf4", 0x36966E4D},
};

void CRageThread_Script_Process()
{
	//GameScriptProcess();
	if(g_iRageScriptFrames < 5)
	{
		g_iRageScriptFrames++;
		g_pCore->OnGameLoad();
	}

	if(!g_bRageScriptLoaded)
	{
		// Mark RageScriptThread as loaded
		g_bRageScriptLoaded = !g_bRageScriptLoaded;
		g_pCore->SetClientState(GAME_STATE_INGAME);
	}
	else
		g_pCore->GetGame()->RenderRAGEScripts();
}

bool g_startupProcessed = false;
DWORD CScriptVM_Process_JmpBack = 0;
sRAGETHREAD * thread = 0;
int i = 0;
bool bPostStartupLoaded = false;
bool bScriptFound = false;

void _declspec(naked) CScriptVM__Process()
{
	_asm	mov thread, ecx;
	_asm	pushad;

	// Set jumpout default
	CScriptVM_Process_JmpBack = g_pCore->GetBase() + 0x4CE0C6;

	switch(thread->m_Context.ScriptHash)
	{
		case 0x8C56D5FD: // initial
		{
			g_startupProcessed = true;
			bScriptFound = true;
			break;
		}
		case 0x27EB33D7: // main
		{
			bScriptFound = true;
			if(g_startupProcessed)
			{
				bScriptFound = true;
				CScriptVM_Process_JmpBack = g_pCore->GetBase() + 0x4CE0CD;
				_asm	popad;
				_asm	jmp [CScriptVM_Process_JmpBack];
			}
			break;
		}
	}
	
	//CLogFile::Printf("%d, %d",ARRAY_LENGTH(civScripts), i);
	
	// Check if we can match 
	if(thread->m_Context.ScriptHash == 0x8C56D5FD || thread->m_Context.ScriptHash == 0x27EB33D7 || thread->m_Context.ScriptHash == 0x41D6F794) { }
	else 
	{

		CScriptVM_Process_JmpBack = g_pCore->GetBase() + 0x4CE0CD;
		_asm	popad;
		_asm	jmp CScriptVM_Process_JmpBack;
		while(i < ARRAY_LENGTH(civScripts))
		{
			if(civScripts[i].dwScriptHash == thread->m_Context.ScriptHash) 
			{
				bScriptFound = true;
				switch(civScripts[i].iSlotID)
				{
					case 7:
					case 8:
					case 9:
					case 10:
					//case 11:
					case 12:
					case 13:
					case 14:
					case 15:
					//case 16:
					case 17: 
					case 18: 
					case 19: 
					//case 20: 
					case 21: 
					case 22: 
					case 23: 
					case 24: 
					case 25: 
					case 26: 
					case 27: 
					case 28: 
					case 29: 
					case 30: 
					case 31: 
					case 32: 
					case 33: 
					case 34: 
					case 35: 
					case 36: 
					case 37: 
					case 38: 
					//case 39: 
					//case 40: 
					//case 41: 
					//case 42: 
					//case 43: 
					//case 44: 
					//case 45: 
					//case 46: 
					case 47: 
					case 48: 
					case 49: 
					case 50: 
					case 51: 
					case 52: 
					case 53: 
					case 54: 
					case 55: 
					case 56: 
					case 57: 
					case 58: 
					case 59: 
					case 60: 
					case 61: 
					case 62: 
					case 68: 
					case 69: 
					case 70: 
					case 114: 
					case 115: 
					case 116: 
					case 117: 
					case 118: 
					case 119: 
					case 127: 
					case 152: 
					case 153: 
					case 160: 
					case 161: 
					case 183: 
					case 184: 
					case 185: 
					case 206: 
					case 220: 
					case 230: 
					case 231: 
					case 234: 
					case 235: 
					case 236: 
					case 237: 
					case 238: 
					case 241: 
					case 244: 
					case 270: 
					case 271: 
					case 281: 
					case 288: 
					case 295: 
					case 309: 
					case 310: 
					case 311: 
					case 312: 
					case 313: 
					case 314: 
					case 315: 
					case 316: 
					case 317: 
					case 331: 
					case 332: 
					case 333: 
					case 334: 
					case 341: 
					case 342: 
					case 376: 
					case 377: 
					case 378: 
					case 387: 
					case 392: 
					case 395: 
					case 398: 
					case 399: 
					case 400: 
					case 423: 
					case 424: 
					case 425: 
					case 426: 
					case 432: 
					case 464:
					{
						//CLogFile::Printf("Process script %s",civScripts[i].strScriptName.Get());
						break;
					}
					default:
					{
						//CLogFile::Printf("Ignore script %s",civScripts[i].strScriptName.Get());

						CScriptVM_Process_JmpBack = g_pCore->GetBase() + 0x4CE0CD;
						_asm	popad;
						_asm	jmp CScriptVM_Process_JmpBack;
						break;
					}
				}
			}
			i++;
		}
	}

	if(!bScriptFound)
		CLogFile::Printf("[%s] Processing unkown script 0x%p[%s]",__FUNCTION__, thread->m_Context.ScriptHash, thread->m_szProgramName);

	// Restore default
	i = 0;
	bScriptFound = false;

	_asm	popad;
	_asm	mov edx, [ecx];
	_asm	mov eax, [edx+0Ch];
	_asm	push edi;
	_asm	call eax;
	_asm	pushad;

	// Post Process our stuff
	switch(thread->m_Context.ScriptHash)
	{
		/*case 0x41D6F794:
		{
			if(bPostStartupLoaded)
				break;
			
			CLogFile::Printf("PostProcess startup.sco!");

			bPostStartupLoaded = !bPostStartupLoaded;

			CIVScript::AllocateScriptToObject("puzzle_launcher", 691499124, 100, 10.00000000, -1);
			CIVScript::AllocateScriptToObject("puzzle_launcher", -386570734, 100, 10.00000000, -1);
			CIVScript::AllocateScriptToObject("bowl_trigger", 1071999466, 100, 25.00000000, -1);
			CIVScript::AllocateScriptToObject("darts_launcher", 33267265, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("ATMobj", 943099328, 100, 30.00000000, -1);
			CIVScript::AllocateScriptToObject("ATMobj", 1646518682, 100, 30.00000000, -1);
			CIVScript::AllocateScriptToObject("ATMobj", -1707894766, 100, 30.00000000, -1);
			CIVScript::AllocateScriptToObject("CarWash", -582605513, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("ambBarrier", 21350196, 100, 100.00000000, -1);
			CIVScript::AllocateScriptToObject("till", -1321409645, 100, 100.00000000, -1);
			CIVScript::AllocateScriptToObject("vendor", 526100790, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("vendor", 1914818237, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("vendor", 1139438163, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("burgerVendor", 381327348, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("nutVendor", 1179300952, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("magVendor", -2047685421, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("magVendor", -1654925163, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("telescope", -1028473, 100, 2.00000000, -1);
			CIVScript::AllocateScriptToObject("sprunk", -2033273140, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("sprunk", -1702863313, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("computerStreamed", -681677032, 100, 3.00000000, -1);
			CIVScript::AllocateScriptToObject("computerStreamed", -1699088948, 100, 3.00000000, -1);
			CIVScript::AllocateScriptToObject("computerStreamed", -1185959097, 100, 3.00000000, -1);
			CIVScript::AllocateScriptToObject("computerStreamed", -805425417, 100, 5.00000000, -1);
			CIVScript::AllocateScriptToObject("pool_table", -1693860173, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("pool_table", 1823613694, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("pool_table", -1570172664, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("ambTV", -1618524073, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("ambTV", -1058927856, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("ambTV", 1243139908, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("ambTV", 900769396, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("ambTV", -1336305346, 100, 80.00000000, -1);
			CIVScript::AllocateScriptToObject("ambClubLights", 1005973733, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("ambClubLights", 1781111577, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("ambClubLights", -21824081, 100, 50.00000000, -1);
			CIVScript::AllocateScriptToObject("ambFunFair", -601413519, 100, 100.00000000, -1);
			CIVScript::AllocateScriptToObject("air_hockey", 1948842064, 100, 50.00000000, -1);
			CIVScript::RegisterWorldPointScriptBrain("ambATMQ", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("EmpireTelescope", 80.00000000);
			CIVScript::RegisterWorldPointScriptBrain("EmpireDown", 80.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambTaxiHail", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("copbootsearch", 80.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambgerry3doorlock", 5.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambSaveBed", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambWardrobe", 25.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambnightclubext", 150.00000000);
			CIVScript::RegisterWorldPointScriptBrain("gunLockup", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("gunLockupCT", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambBar", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("TollBooth", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambBridgePatrol", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambTunnelCops", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambHotel", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("foodServer", 80.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambInternetCafe", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambCargoHoldDoors", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambJerseyDocksGates", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambBouncer", 150.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambStripClub", 60.00000000);
			CIVScript::AllocateScriptToObject("ambPoleDancer", -132862690, 100, 50.00000000, -1);
			CIVScript::RegisterWorldPointScriptBrain("ambNightclubBM", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambNightclubM9", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambNightclubHC", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambHomelandCordon", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambChurchDoors", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambLiftDoors", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambToiletDoors", 25.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambJimsLocks", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambPolRdBlk", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("Ambblkhawk", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambhelicopter", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("Manhat_heli_tours", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("drinking", 110.00000000);
			CIVScript::RegisterWorldPointScriptBrain("AmbWindowLift", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("bowling_lane", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambAirpotarea", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambUNarea", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambShowroom", 75.00000000);
			CIVScript::RegisterWorldPointScriptBrain("cablecars", 75.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambSecurityCameras", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambPrisonWanted", 200.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambFoodEating", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("ambDrinking", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("FightClubLauncher", 50.00000000);
			CIVScript::RegisterWorldPointScriptBrain("golf_launcher", 100.00000000);
			CIVScript::RegisterWorldPointScriptBrain("raceSPLAUNCHER", 50.00000000);
			CIVScript::AllocateScriptToRandomPed("garbage_trucks", 1136499716, 100, 0);
			CIVScript::AllocateScriptToRandomPed("ambbeggar", -1080673049, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambbeggar", -1827421800, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambbeggar", -142386662, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambpimpnpros", 552542187, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambpimpnpros", 996267216, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambdealer", 1448755353, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambpreacher", 495499562, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambpreacher", 379171768, 100, 1);
			CIVScript::AllocateScriptToRandomPed("ambbusker", -1188246269, 100, 1);
			break;
		}*/
	}
	
	_asm	popad;
	_asm	jmp CScriptVM_Process_JmpBack;

	//*(sRAGETHREAD **)COffsets::VAR_ScrVM__ActiveThread = g_pRageScriptThread;
}
sRAGETHREAD* g_pOldScriptThread = 0;
void _declspec(naked) CScriptVM_Prcoess_End()
{
	_asm	pushad;

	//g_pOldScriptThread = *(sRAGETHREAD**)(g_pCore->GetBase() + 0x16EAD50);
	//*(sRAGETHREAD**)(g_pCore->GetBase() + 0x16EAD50) = g_pRageScriptThread;

	CRageThread_Script_Process();

	//*(sRAGETHREAD**)(g_pCore->GetBase() + 0x16EAD50) = g_pOldScriptThread;

	_asm	popad;
	_asm	pop esi;
	_asm	mov al, bl;
	_asm	pop ebx;
	_asm	retn;
}

__declspec(naked) int GetRunningScriptThread()
{
	//CLogFile::Printf("%s",__FUNCTION__);
	_asm mov eax, g_pRageScriptThread;
	_asm retn;
}

void CIVScriptingHook::InstallScriptHooks()
{
	g_pRageScriptThread = new sRAGETHREAD;
	memset(g_pRageScriptThread, NULL, sizeof(sRAGETHREAD));

	bScriptProcssSwitch = false;

	// Hook CScriptVM Process
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x4CE0BE, (DWORD)CScriptVM__Process);
	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x4CE0DC, (DWORD)CScriptVM_Prcoess_End);

	// Disable check to invalid threads
	CPatcher::InstallJmpPatch((g_pCore->GetBase() + 0x82E7E0), (DWORD)GetRunningScriptThread, 5);
	//CPatcher::InstallNopPatch((g_pCore->GetBase() + 0x830DE1), 39);
	//CPatcher::InstallNopPatch((g_pCore->GetBase() + 0830E64), 22);
}

void CIVScriptingHook::UninstallScriptHooks()
{
	SAFE_DELETE(g_pRageScriptThread);
}