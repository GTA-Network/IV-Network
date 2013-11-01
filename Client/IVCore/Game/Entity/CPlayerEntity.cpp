//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPlayerEntity.cpp
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CPlayerEntity.h"
#include "CVehicleEntity.h"

#include <Game/eGame.h>
#include <Game/IVEngine/CIVPad.h>
#include <IV/CIVScript.h>
#include <Game/IVEngine/CIVModelManager.h>
#include <Game/IVEngine/CIVVehicle.h>
#include <Game/IVEngine/CIVTask.h>
#include <Game/IVEngine/IVTasks.h>
#include <Game/IVEngine/CIVPedTaskManager.h>
#include <Math/CMaths.h>
#include <Ptrs.h>

DWORD dwPlayerModelHashes[] = 
{
	CIVScript::MODEL_PLAYER, CIVScript::MODEL_M_Y_MULTIPLAYER, CIVScript::MODEL_F_Y_MULTIPLAYER, CIVScript::MODEL_SUPERLOD,
	CIVScript::MODEL_IG_ANNA, CIVScript::MODEL_IG_ANTHONY, CIVScript::MODEL_IG_BADMAN, CIVScript::MODEL_IG_BERNIE_CRANE,
	CIVScript::MODEL_IG_BLEDAR, CIVScript::MODEL_IG_BRIAN, CIVScript::MODEL_IG_BRUCIE, CIVScript::MODEL_IG_BULGARIN,
	CIVScript::MODEL_IG_CHARISE, CIVScript::MODEL_IG_CHARLIEUC, CIVScript::MODEL_IG_CLARENCE, CIVScript::MODEL_IG_DARDAN,
	CIVScript::MODEL_IG_DARKO, CIVScript::MODEL_IG_DERRICK_MC, CIVScript::MODEL_IG_DMITRI, CIVScript::MODEL_IG_DWAYNE,
	CIVScript::MODEL_IG_EDDIELOW, CIVScript::MODEL_IG_FAUSTIN, CIVScript::MODEL_IG_FRANCIS_MC, CIVScript::MODEL_IG_FRENCH_TOM,
	CIVScript::MODEL_IG_GORDON, CIVScript::MODEL_IG_GRACIE, CIVScript::MODEL_IG_HOSSAN, CIVScript::MODEL_IG_ILYENA, CIVScript::MODEL_IG_ISAAC,
	CIVScript::MODEL_IG_IVAN, CIVScript::MODEL_IG_JAY, CIVScript::MODEL_IG_JASON, CIVScript::MODEL_IG_JEFF, CIVScript::MODEL_IG_JIMMY,
	CIVScript::MODEL_IG_JOHNNYBIKER, CIVScript::MODEL_IG_KATEMC, CIVScript::MODEL_IG_KENNY, CIVScript::MODEL_IG_LILJACOB,
	CIVScript::MODEL_IG_LILJACOBW, CIVScript::MODEL_IG_LUCA, CIVScript::MODEL_IG_LUIS, CIVScript::MODEL_IG_MALLORIE, CIVScript::MODEL_IG_MAMC,
	CIVScript::MODEL_IG_MANNY, CIVScript::MODEL_IG_MARNIE, CIVScript::MODEL_IG_MEL, CIVScript::MODEL_IG_MICHAEL, CIVScript::MODEL_IG_MICHELLE,
	CIVScript::MODEL_IG_MICKEY, CIVScript::MODEL_IG_PACKIE_MC, CIVScript::MODEL_IG_PATHOS, CIVScript::MODEL_IG_PETROVIC,
	CIVScript::MODEL_IG_PHIL_BELL, CIVScript::MODEL_IG_PLAYBOY_X, CIVScript::MODEL_IG_RAY_BOCCINO, CIVScript::MODEL_IG_RICKY,
	CIVScript::MODEL_IG_ROMAN, CIVScript::MODEL_IG_ROMANW, CIVScript::MODEL_IG_SARAH, CIVScript::MODEL_IG_TUNA, CIVScript::MODEL_IG_VINNY_SPAZ,
	CIVScript::MODEL_IG_VLAD, CIVScript::MODEL_M_Y_GAFR_LO_01, CIVScript::MODEL_M_Y_GAFR_LO_02, CIVScript::MODEL_M_Y_GAFR_HI_01,
	CIVScript::MODEL_M_Y_GAFR_HI_02, CIVScript::MODEL_M_Y_GALB_LO_01, CIVScript::MODEL_M_Y_GALB_LO_02, CIVScript::MODEL_M_Y_GALB_LO_03,
	CIVScript::MODEL_M_Y_GALB_LO_04, CIVScript::MODEL_M_M_GBIK_LO_03, CIVScript::MODEL_M_Y_GBIK_HI_01, CIVScript::MODEL_M_Y_GBIK_HI_02,
	CIVScript::MODEL_M_Y_GBIK02_LO_02, CIVScript::MODEL_M_Y_GBIK_LO_01, CIVScript::MODEL_M_Y_GBIK_LO_02, CIVScript::MODEL_M_Y_GIRI_LO_01,
	CIVScript::MODEL_M_Y_GIRI_LO_02, CIVScript::MODEL_M_Y_GIRI_LO_03, CIVScript::MODEL_M_M_GJAM_HI_01, CIVScript::MODEL_M_M_GJAM_HI_02,
	CIVScript::MODEL_M_M_GJAM_HI_03, CIVScript::MODEL_M_Y_GJAM_LO_01, CIVScript::MODEL_M_Y_GJAM_LO_02, CIVScript::MODEL_M_Y_GKOR_LO_01,
	CIVScript::MODEL_M_Y_GKOR_LO_02, CIVScript::MODEL_M_Y_GLAT_LO_01, CIVScript::MODEL_M_Y_GLAT_LO_02, CIVScript::MODEL_M_Y_GLAT_HI_01,
	CIVScript::MODEL_M_Y_GLAT_HI_02, CIVScript::MODEL_M_Y_GMAF_HI_01, CIVScript::MODEL_M_Y_GMAF_HI_02, CIVScript::MODEL_M_Y_GMAF_LO_01,
	CIVScript::MODEL_M_Y_GMAF_LO_02, CIVScript::MODEL_M_O_GRUS_HI_01, CIVScript::MODEL_M_Y_GRUS_LO_01, CIVScript::MODEL_M_Y_GRUS_LO_02,
	CIVScript::MODEL_M_Y_GRUS_HI_02, CIVScript::MODEL_M_M_GRU2_HI_01, CIVScript::MODEL_M_M_GRU2_HI_02, CIVScript::MODEL_M_M_GRU2_LO_02,
	CIVScript::MODEL_M_Y_GRU2_LO_01, CIVScript::MODEL_M_M_GTRI_HI_01, CIVScript::MODEL_M_M_GTRI_HI_02, CIVScript::MODEL_M_Y_GTRI_LO_01,
	CIVScript::MODEL_M_Y_GTRI_LO_02, CIVScript::MODEL_F_O_MAID_01, CIVScript::MODEL_F_O_BINCO, CIVScript::MODEL_F_Y_BANK_01, CIVScript::MODEL_F_Y_DOCTOR_01,
	CIVScript::MODEL_F_Y_GYMGAL_01, CIVScript::MODEL_F_Y_FF_BURGER_R, CIVScript::MODEL_F_Y_FF_CLUCK_R, CIVScript::MODEL_F_Y_FF_RSCAFE,
	CIVScript::MODEL_F_Y_FF_TWCAFE, CIVScript::MODEL_F_Y_FF_WSPIZZA_R, CIVScript::MODEL_F_Y_HOOKER_01, CIVScript::MODEL_F_Y_HOOKER_03,
	CIVScript::MODEL_F_Y_NURSE, CIVScript::MODEL_F_Y_STRIPPERC01, CIVScript::MODEL_F_Y_STRIPPERC02, CIVScript::MODEL_F_Y_WAITRESS_01,
	CIVScript::MODEL_M_M_ALCOHOLIC, CIVScript::MODEL_M_M_ARMOURED, CIVScript::MODEL_M_M_BUSDRIVER, CIVScript::MODEL_M_M_CHINATOWN_01,
	CIVScript::MODEL_M_M_CRACKHEAD, CIVScript::MODEL_M_M_DOC_SCRUBS_01, CIVScript::MODEL_M_M_DOCTOR_01, CIVScript::MODEL_M_M_DODGYDOC,
	CIVScript::MODEL_M_M_EECOOK, CIVScript::MODEL_M_M_ENFORCER, CIVScript::MODEL_M_M_FACTORY_01, CIVScript::MODEL_M_M_FATCOP_01,
	CIVScript::MODEL_M_M_FBI, CIVScript::MODEL_M_M_FEDCO, CIVScript::MODEL_M_M_FIRECHIEF, CIVScript::MODEL_M_M_GUNNUT_01, CIVScript::MODEL_M_M_HELIPILOT_01,
	CIVScript::MODEL_M_M_HPORTER_01, CIVScript::MODEL_M_M_KOREACOOK_01, CIVScript::MODEL_M_M_LAWYER_01, CIVScript::MODEL_M_M_LAWYER_02,
	CIVScript::MODEL_M_M_LOONYBLACK, CIVScript::MODEL_M_M_PILOT, CIVScript::MODEL_M_M_PINDUS_01, CIVScript::MODEL_M_M_POSTAL_01,
	CIVScript::MODEL_M_M_SAXPLAYER_01, CIVScript::MODEL_M_M_SECURITYMAN, CIVScript::MODEL_M_M_SELLER_01, CIVScript::MODEL_M_M_SHORTORDER,
	CIVScript::MODEL_M_M_STREETFOOD_01, CIVScript::MODEL_M_M_SWEEPER, CIVScript::MODEL_M_M_TAXIDRIVER, CIVScript::MODEL_M_M_TELEPHONE,
	CIVScript::MODEL_M_M_TENNIS, CIVScript::MODEL_M_M_TRAIN_01, CIVScript::MODEL_M_M_TRAMPBLACK, CIVScript::MODEL_M_M_TRUCKER_01,
	CIVScript::MODEL_M_O_JANITOR, CIVScript::MODEL_M_O_HOTEL_FOOT, CIVScript::MODEL_M_O_MPMOBBOSS, CIVScript::MODEL_M_Y_AIRWORKER,
	CIVScript::MODEL_M_Y_BARMAN_01, CIVScript::MODEL_M_Y_BOUNCER_01, CIVScript::MODEL_M_Y_BOUNCER_02, CIVScript::MODEL_M_Y_BOWL_01,
	CIVScript::MODEL_M_Y_BOWL_02, CIVScript::MODEL_M_Y_CHINVEND_01, CIVScript::MODEL_M_Y_CLUBFIT, CIVScript::MODEL_M_Y_CONSTRUCT_01,
	CIVScript::MODEL_M_Y_CONSTRUCT_02, CIVScript::MODEL_M_Y_CONSTRUCT_03, CIVScript::MODEL_M_Y_COP, CIVScript::MODEL_M_Y_COP_TRAFFIC,
	CIVScript::MODEL_M_Y_COURIER, CIVScript::MODEL_M_Y_COWBOY_01, CIVScript::MODEL_M_Y_DEALER, CIVScript::MODEL_M_Y_DRUG_01,
	CIVScript::MODEL_M_Y_FF_BURGER_R, CIVScript::MODEL_M_Y_FF_CLUCK_R, CIVScript::MODEL_M_Y_FF_RSCAFE, CIVScript::MODEL_M_Y_FF_TWCAFE,
	CIVScript::MODEL_M_Y_FF_WSPIZZA_R, CIVScript::MODEL_M_Y_FIREMAN, CIVScript::MODEL_M_Y_GARBAGE, CIVScript::MODEL_M_Y_GOON_01,
	CIVScript::MODEL_M_Y_GYMGUY_01, CIVScript::MODEL_M_Y_MECHANIC_02, CIVScript::MODEL_M_Y_MODO, CIVScript::MODEL_M_Y_NHELIPILOT,
	CIVScript::MODEL_M_Y_PERSEUS, CIVScript::MODEL_M_Y_PINDUS_01, CIVScript::MODEL_M_Y_PINDUS_02, CIVScript::MODEL_M_Y_PINDUS_03, 
	CIVScript::MODEL_M_Y_PMEDIC, CIVScript::MODEL_M_Y_PRISON, CIVScript::MODEL_M_Y_PRISONAOM, CIVScript::MODEL_M_Y_ROMANCAB, CIVScript::MODEL_M_Y_RUNNER,
	CIVScript::MODEL_M_Y_SHOPASST_01, CIVScript::MODEL_M_Y_STROOPER, CIVScript::MODEL_M_Y_SWAT, CIVScript::MODEL_M_Y_SWORDSWALLOW,
	CIVScript::MODEL_M_Y_THIEF, CIVScript::MODEL_M_Y_VALET, CIVScript::MODEL_M_Y_VENDOR, CIVScript::MODEL_M_Y_FRENCHTOM, CIVScript::MODEL_M_Y_JIM_FITZ,
	CIVScript::MODEL_F_O_PEASTEURO_01, CIVScript::MODEL_F_O_PEASTEURO_02, CIVScript::MODEL_F_O_PHARBRON_01, CIVScript::MODEL_F_O_PJERSEY_01,
	CIVScript::MODEL_F_O_PORIENT_01, CIVScript::MODEL_F_O_RICH_01, CIVScript::MODEL_F_M_BUSINESS_01, CIVScript::MODEL_F_M_BUSINESS_02,
	CIVScript::MODEL_F_M_CHINATOWN, CIVScript::MODEL_F_M_PBUSINESS, CIVScript::MODEL_F_M_PEASTEURO_01, CIVScript::MODEL_F_M_PHARBRON_01,
	CIVScript::MODEL_F_M_PJERSEY_01, CIVScript::MODEL_F_M_PJERSEY_02, CIVScript::MODEL_F_M_PLATIN_01, CIVScript::MODEL_F_M_PLATIN_02,
	CIVScript::MODEL_F_M_PMANHAT_01, CIVScript::MODEL_F_M_PMANHAT_02, CIVScript::MODEL_F_M_PORIENT_01, CIVScript::MODEL_F_M_PRICH_01,
	CIVScript::MODEL_F_Y_BUSINESS_01, CIVScript::MODEL_F_Y_CDRESS_01, CIVScript::MODEL_F_Y_PBRONX_01, CIVScript::MODEL_F_Y_PCOOL_01,
	CIVScript::MODEL_F_Y_PCOOL_02, CIVScript::MODEL_F_Y_PEASTEURO_01, CIVScript::MODEL_F_Y_PHARBRON_01, CIVScript::MODEL_F_Y_PHARLEM_01,
	CIVScript::MODEL_F_Y_PJERSEY_02, CIVScript::MODEL_F_Y_PLATIN_01, CIVScript::MODEL_F_Y_PLATIN_02, CIVScript::MODEL_F_Y_PLATIN_03,
	CIVScript::MODEL_F_Y_PMANHAT_01, CIVScript::MODEL_F_Y_PMANHAT_02, CIVScript::MODEL_F_Y_PMANHAT_03, CIVScript::MODEL_F_Y_PORIENT_01,
	CIVScript::MODEL_F_Y_PQUEENS_01, CIVScript::MODEL_F_Y_PRICH_01, CIVScript::MODEL_F_Y_PVILLBO_02, CIVScript::MODEL_F_Y_SHOP_03,
	CIVScript::MODEL_F_Y_SHOP_04, CIVScript::MODEL_F_Y_SHOPPER_05, CIVScript::MODEL_F_Y_SOCIALITE, CIVScript::MODEL_F_Y_STREET_02,
	CIVScript::MODEL_F_Y_STREET_05, CIVScript::MODEL_F_Y_STREET_09, CIVScript::MODEL_F_Y_STREET_12, CIVScript::MODEL_F_Y_STREET_30,
	CIVScript::MODEL_F_Y_STREET_34, CIVScript::MODEL_F_Y_TOURIST_01, CIVScript::MODEL_F_Y_VILLBO_01, CIVScript::MODEL_M_M_BUSINESS_02,
	CIVScript::MODEL_M_M_BUSINESS_03, CIVScript::MODEL_M_M_EE_HEAVY_01, CIVScript::MODEL_M_M_EE_HEAVY_02, CIVScript::MODEL_M_M_FATMOB_01,
	CIVScript::MODEL_M_M_GAYMID, CIVScript::MODEL_M_M_GENBUM_01, CIVScript::MODEL_M_M_LOONYWHITE, CIVScript::MODEL_M_M_MIDTOWN_01,
	CIVScript::MODEL_M_M_PBUSINESS_01, CIVScript::MODEL_M_M_PEASTEURO_01, CIVScript::MODEL_M_M_PHARBRON_01, CIVScript::MODEL_M_M_PINDUS_02,
	CIVScript::MODEL_M_M_PITALIAN_01, CIVScript::MODEL_M_M_PITALIAN_02, CIVScript::MODEL_M_M_PLATIN_01, CIVScript::MODEL_M_M_PLATIN_02,
	CIVScript::MODEL_M_M_PLATIN_03, CIVScript::MODEL_M_M_PMANHAT_01, CIVScript::MODEL_M_M_PMANHAT_02, CIVScript::MODEL_M_M_PORIENT_01,
	CIVScript::MODEL_M_M_PRICH_01, CIVScript::MODEL_M_O_EASTEURO_01, CIVScript::MODEL_M_O_HASID_01, CIVScript::MODEL_M_O_MOBSTER,
	CIVScript::MODEL_M_O_PEASTEURO_02, CIVScript::MODEL_M_O_PHARBRON_01, CIVScript::MODEL_M_O_PJERSEY_01, CIVScript::MODEL_M_O_STREET_01,
	CIVScript::MODEL_M_O_SUITED, CIVScript::MODEL_M_Y_BOHO_01, CIVScript::MODEL_M_Y_BOHOGUY_01, CIVScript::MODEL_M_Y_BRONX_01,
	CIVScript::MODEL_M_Y_BUSINESS_01, CIVScript::MODEL_M_Y_BUSINESS_02, CIVScript::MODEL_M_Y_CHINATOWN_03, CIVScript::MODEL_M_Y_CHOPSHOP_01,
	CIVScript::MODEL_M_Y_CHOPSHOP_02, CIVScript::MODEL_M_Y_DODGY_01, CIVScript::MODEL_M_Y_DORK_02, CIVScript::MODEL_M_Y_DOWNTOWN_01, 
	CIVScript::MODEL_M_Y_DOWNTOWN_02, CIVScript::MODEL_M_Y_DOWNTOWN_03, CIVScript::MODEL_M_Y_GAYYOUNG, CIVScript::MODEL_M_Y_GENSTREET_11, 
	CIVScript::MODEL_M_Y_GENSTREET_16, CIVScript::MODEL_M_Y_GENSTREET_20, CIVScript::MODEL_M_Y_GENSTREET_34, CIVScript::MODEL_M_Y_HARDMAN_01,
	CIVScript::MODEL_M_Y_HARLEM_01, CIVScript::MODEL_M_Y_HARLEM_02, CIVScript::MODEL_M_Y_HARLEM_04, CIVScript::MODEL_M_Y_HASID_01,
	CIVScript::MODEL_M_Y_LEASTSIDE_01, CIVScript::MODEL_M_Y_PBRONX_01, CIVScript::MODEL_M_Y_PCOOL_01, CIVScript::MODEL_M_Y_PCOOL_02, 
	CIVScript::MODEL_M_Y_PEASTEURO_01, CIVScript::MODEL_M_Y_PHARBRON_01, CIVScript::MODEL_M_Y_PHARLEM_01, CIVScript::MODEL_M_Y_PJERSEY_01,
	CIVScript::MODEL_M_Y_PLATIN_01, CIVScript::MODEL_M_Y_PLATIN_02, CIVScript::MODEL_M_Y_PLATIN_03, CIVScript::MODEL_M_Y_PMANHAT_01,
	CIVScript::MODEL_M_Y_PMANHAT_02, CIVScript::MODEL_M_Y_PORIENT_01, CIVScript::MODEL_M_Y_PQUEENS_01, CIVScript::MODEL_M_Y_PRICH_01,
	CIVScript::MODEL_M_Y_PVILLBO_01, CIVScript::MODEL_M_Y_PVILLBO_02, CIVScript::MODEL_M_Y_PVILLBO_03, CIVScript::MODEL_M_Y_QUEENSBRIDGE,
	CIVScript::MODEL_M_Y_SHADY_02, CIVScript::MODEL_M_Y_SKATEBIKE_01, CIVScript::MODEL_M_Y_SOHO_01, CIVScript::MODEL_M_Y_STREET_01,
	CIVScript::MODEL_M_Y_STREET_03, CIVScript::MODEL_M_Y_STREET_04, CIVScript::MODEL_M_Y_STREETBLK_02, CIVScript::MODEL_M_Y_STREETBLK_03,
	CIVScript::MODEL_M_Y_STREETPUNK_02, CIVScript::MODEL_M_Y_STREETPUNK_04, CIVScript::MODEL_M_Y_STREETPUNK_05, CIVScript::MODEL_M_Y_TOUGH_05,
	CIVScript::MODEL_M_Y_TOURIST_02, CIVScript::F_Y_BIKESTRIPPER_01, CIVScript::F_Y_BUSIASIAN, CIVScript::F_Y_EMIDTOWN_01, 
	CIVScript::F_Y_GANGELS_01, CIVScript::F_Y_GANGELS_02, CIVScript::F_Y_GANGELS_03, CIVScript::F_Y_GLOST_01,
	CIVScript::F_Y_GLOST_02, CIVScript::F_Y_GLOST_03, CIVScript::F_Y_GLOST_04, CIVScript::F_Y_GRYDERS_01, 
	CIVScript::F_Y_UPTOWN_01, CIVScript::F_Y_UPTOWN_CS, CIVScript::IG_ASHLEYA, CIVScript::IG_BILLY,
	CIVScript::IG_BILLYPRISON, CIVScript::IG_BRIANJ, CIVScript::IG_CLAY, CIVScript::IG_DAVE_GROSSMAN,
	CIVScript::IG_DESEAN, CIVScript::IG_EVAN, CIVScript::IG_JASON_M, CIVScript::IG_JIM_FITZ,
	CIVScript::IG_LOSTGIRL, CIVScript::IG_MALC, CIVScript::IG_MARTA, CIVScript::IG_MATTHEWS, 
	CIVScript::IG_MCCORNISH, CIVScript::IG_NIKO, CIVScript::IG_PGIRL_01, CIVScript::IG_PGIRL_02,
	CIVScript::IG_ROMAN_E1, CIVScript::IG_STROOPER, CIVScript::IG_TERRY, CIVScript::LOSTBUDDY_01,
	CIVScript::LOSTBUDDY_02, CIVScript::LOSTBUDDY_03, CIVScript::LOSTBUDDY_04, CIVScript::LOSTBUDDY_05,
	CIVScript::LOSTBUDDY_06, CIVScript::LOSTBUDDY_07, CIVScript::LOSTBUDDY_08, CIVScript::LOSTBUDDY_09,
	CIVScript::LOSTBUDDY_10, CIVScript::LOSTBUDDY_11, CIVScript::LOSTBUDDY_12, CIVScript::LOSTBUDDY_13,
	CIVScript::M_M_SMARTBLACK, CIVScript::M_M_SPRETZER, CIVScript::M_M_UPEAST_01, CIVScript::M_M_UPTOWN_01,
	CIVScript::M_O_HISPANIC_01, CIVScript::M_Y_BIKEMECH, CIVScript::M_Y_BUSIASIAN, CIVScript::M_Y_BUSIMIDEAST,
	CIVScript::M_Y_CIADLC_01, CIVScript::M_Y_CIADLC_02, CIVScript::M_Y_DOORMAN_01, CIVScript::M_Y_GANGELS_02,
	CIVScript::M_Y_GANGELS_03, CIVScript::M_Y_GANGELS_04, CIVScript::M_Y_GANGELS_05, CIVScript::M_Y_GANGELS_06,
	CIVScript::M_Y_GAYGANG_01, CIVScript::M_Y_GLOST_01, CIVScript::M_Y_GLOST_02, CIVScript::M_Y_GLOST_03,
	CIVScript::M_Y_GLOST_04, CIVScript::M_Y_GLOST_05, CIVScript::M_Y_GLOST_06, CIVScript::M_Y_GRYDERS_01,
	CIVScript::M_Y_GRYDERS_02, CIVScript::M_Y_GTRI_02, CIVScript::M_Y_GTRIAD_HI_01, CIVScript::M_Y_HIP_02,
	CIVScript::M_Y_HIPMALE_01, CIVScript::M_Y_HISPANIC_01, CIVScript::M_Y_PRISONBLACK, CIVScript::M_Y_PRISONDLC_01,
	CIVScript::M_Y_PRISONGUARD, CIVScript::F_Y_ASIANCLUB_01, CIVScript::F_Y_ASIANCLUB_02, CIVScript::F_Y_CLOEPARKER,
	CIVScript::F_Y_CLUBEURO_01, CIVScript::F_Y_DANCER_01, CIVScript::F_Y_DOMGIRL_01, CIVScript::F_Y_EMIDTOWN_02,
	CIVScript::F_Y_HOSTESS, CIVScript::F_Y_HOTCHICK_01, CIVScript::F_Y_HOTCHICK_02, CIVScript::F_Y_HOTCHICK_03,
	CIVScript::F_Y_JONI, CIVScript::F_Y_PGIRL_01, CIVScript::F_Y_PGIRL_02, CIVScript::F_Y_SMID_01, 
	CIVScript::F_Y_TRENDY_01, CIVScript::IG_AHMAD, CIVScript::IG_ARMANDO, CIVScript::IG_ARMSDEALER,
	CIVScript::IG_ARNAUD, CIVScript::IG_BANKER, CIVScript::IG_BLUEBROS, CIVScript::IG_BRUCIE2,
	CIVScript::IG_BULGARIN2, CIVScript::IG_DAISY, CIVScript::IG_DEEJAY, CIVScript::IG_DESSIE,
	CIVScript::IG_GRACIE2, CIVScript::IG_HENRIQUE, CIVScript::IG_ISSAC2, CIVScript::IG_JACKSON,
	CIVScript::IG_JOHNNY2, CIVScript::IG_LUIS2, CIVScript::IG_MARGOT, CIVScript::IG_MORI_K,
	CIVScript::IG_MR_SANTOS, CIVScript::IG_NAPOLI, CIVScript::IG_OYVEY, CIVScript::IG_ROCCO,
	CIVScript::IG_ROYAL, CIVScript::IG_SPADE, CIVScript::IG_TAHIR, CIVScript::IG_TIMUR,
	CIVScript::IG_TONY, CIVScript::IG_TRAMP2, CIVScript::IG_TRIAD, CIVScript::IG_TROY,
	CIVScript::IG_VIC, CIVScript::IG_VICGIRL, CIVScript::IG_VINCE, CIVScript::IG_YUSEF,
	CIVScript::M_M_E2MAF_01, CIVScript::M_M_E2MAF_02, CIVScript::M_M_MAFUNION, CIVScript::M_Y_AMIRGUARD_01,
	CIVScript::M_Y_BARMAISON, CIVScript::M_Y_BATHROOM, CIVScript::M_Y_CELEBBLOG, CIVScript::M_Y_CLUBBLACK_01, 
	CIVScript::M_Y_CLUBEURO_01, CIVScript::M_Y_CLUBEURO_02, CIVScript::M_Y_CLUBEURO_03, CIVScript::M_Y_CLUBWHITE_01,
	CIVScript::M_Y_DOMDRUG_01, CIVScript::M_Y_DOMGUY_01, CIVScript::M_Y_DOMGUY_02, CIVScript::M_Y_DOORMAN_02,
	CIVScript::M_Y_E2RUSSIAN_01, CIVScript::M_Y_E2RUSSIAN_02, CIVScript::M_Y_E2RUSSIAN_03, CIVScript::M_Y_EXSPORTS,
	CIVScript::M_Y_FIGHTCLUB_01, CIVScript::M_Y_FIGHTCLUB_02, CIVScript::M_Y_FIGHTCLUB_03, CIVScript::M_Y_FIGHTCLUB_04,
	CIVScript::M_Y_FIGHTCLUB_05, CIVScript::M_Y_FIGHTCLUB_06, CIVScript::M_Y_FIGHTCLUB_07, CIVScript::M_Y_FIGHTCLUB_08,
	CIVScript::M_Y_GAYBLACK_01, CIVScript::M_Y_GAYDANCER, CIVScript::M_Y_GAYGENERAL_01, CIVScript::M_Y_GAYWHITE_01,
	CIVScript::M_Y_GUIDO_01, CIVScript::M_Y_GUIDO_02, CIVScript::M_Y_MIDEAST_01, CIVScript::M_Y_MOBPARTY,
	CIVScript::M_Y_PAPARAZZI_01, CIVScript::M_Y_UPTOWN_01
};

DWORD SkinIdToModelHash(int modelid)
{
	if(modelid >= 0 || modelid < sizeof(dwPlayerModelHashes))
		return dwPlayerModelHashes[modelid];

	return 0x00;
}

CPlayerEntity::CPlayerEntity(bool bLocalPlayer) :
	CNetworkEntity(PLAYER_ENTITY), m_iWantedLevel(0), m_bLocalPlayer(bLocalPlayer),
	m_usPlayerId(INVALID_ENTITY_ID), m_usPing(0), m_bNetworked(false),
	m_uiColor(0xFFFFFFFF), m_bSpawned(false), m_pPlayerPed(NULL),
	m_pPlayerInfo(NULL), m_bytePlayerNumber(INVALID_PLAYER_PED), m_pContextData(NULL),
	m_pVehicle(NULL), m_byteSeat(0)
{
	m_pModelInfo = g_pCore->GetGame()->GetModelInfo(INVALID_PLAYER_PED);
	m_vecPosition = CVector3();
	memset(&m_lastControlState, NULL, sizeof(CControls));
	memset(&m_ControlState, NULL, sizeof(CControls));

	// Initialise & Reset all stuff(classes,structs)
	m_pVehicleEnterExit = new sPlayerEntity_VehicleData;
	m_pInterpolationData = new sPlayerEntity_InterpolationData;
	ResetVehicleEnterExit();

	// Is this the localplayer?
	if(IsLocalPlayer())
	{
		// Set the localplayer CIVScript handle
		m_bytePlayerNumber = (BYTE)g_pCore->GetGame()->GetPools()->GetLocalPlayerIndex();

		// Create a new player ped instance
		m_pPlayerPed = new CIVPlayerPed(g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(m_bytePlayerNumber)->m_pPlayerPed);

		// Get the localplayer info pointer
		m_pPlayerInfo = new CIVPlayerInfo(g_pCore->GetGame()->GetPools()->GetPlayerInfoFromIndex(m_bytePlayerNumber));

		// Create a new context data instance with the local player info
		m_pContextData = CContextDataManager::CreateContextData(m_pPlayerInfo);

		// Set the context data player ped pointer
		m_pContextData->SetPlayerPed(m_pPlayerPed);

		// Add our model reference
		m_pModelInfo->AddReference(false);

		// Set the localplayer name
		// ViruZz: We're setting the nick that the client has in his settings, if not you're just setting it to NULL and we don't want that.
		SetNick(CVAR_GET_STRING("nick").Get());

		// Mark as spawned
		m_bSpawned = true;

		CLogFile::Printf("LOCALPLAYER: m_bytePlayerNumber: %d, m_pPlayerPed: 0x%p, m_pPlayerInfo: 0x%p", m_bytePlayerNumber, m_pPlayerPed, m_pPlayerInfo);
	}
}

CPlayerEntity::~CPlayerEntity()
{
	// Is this not the localplayer?
	if(!IsLocalPlayer())
		Destroy();

	delete m_pVehicleEnterExit;
	delete m_pInterpolationData;
}

unsigned short CPlayerEntity::GetPing()
{
	if(IsLocalPlayer())
	{
		//TODO: Get ping to current connected server.
		return -1;
	}
	else
		return m_usPing;
}

void CPlayerEntity::Pulse()
{
	// Is the player spawned?
	if(IsSpawned())
	{
		// Is this the localplayer?
		if(IsLocalPlayer())
		{

		}
		if(!IsLocalPlayer())
		{
			// Are we not in a vehicle?
			if(!IsInVehicle())
			{
				if (!IsJumping())
				{
					// Process interpolation
					Interpolate();
				}
			}
		}
	}
}

bool CPlayerEntity::Create()
{
	// Is this the localplayer or are we alread spawned?
	if(IsLocalPlayer() && IsSpawned())
		return false;

	// Add our model reference and load the model
	m_pModelInfo->AddReference(true);

	// Find a free player number
	m_bytePlayerNumber = (BYTE)g_pCore->GetGame()->GetPools()->FindFreePlayerInfoIndex();

	// Invalid player number?
	if(m_bytePlayerNumber == INVALID_PLAYER_PED)
		return false;

	// Create the player info instance
	m_pPlayerInfo = new CIVPlayerInfo(m_bytePlayerNumber);

	// Create our context data
	m_pContextData = CContextDataManager::CreateContextData(m_pPlayerInfo);

	// Set the game player info pointer
	g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex(m_bytePlayerNumber, m_pPlayerInfo->GetPlayerInfo());

	// Allocate the player ped
	IVPlayerPed * pPlayerPed = (IVPlayerPed *)g_pCore->GetGame()->GetPools()->GetPedPool()->Allocate();

	CLogFile::Printf("CREATE: m_bytePlayerNumber: %d, m_pPlayerInfo: 0x%p, pPlayerPed: 0x%p", m_bytePlayerNumber, m_pPlayerInfo, pPlayerPed);

	// Ensure the ped was allocated
	if(!pPlayerPed)
		return false;

	// Create the ped
	WORD wPlayerData = MAKEWORD(0, 1);
	((void(__thiscall*) (IVPed *, WORD*, int, unsigned int)) (COffsets::IV_Func__CreatePed))(pPlayerPed, &wPlayerData, m_pModelInfo->GetIndex(), m_bytePlayerNumber);

	// Setup the ped
	Matrix34 * pMatrix = NULL;
	int iModelIndex = m_pModelInfo->GetIndex();
	_asm  push iModelIndex;
	_asm  push COffsets::IV_Var__PedFactory;
	_asm  mov edi, pMatrix;
	_asm  mov esi, pPlayerPed;
	_asm  call COffsets::IV_Func__SetupPed;

	// Set the player info
	m_pPlayerInfo->SetPlayerPed(pPlayerPed);

	// Set the player state to spawned
	m_pPlayerInfo->GetPlayerInfo()->m_dwState = 2;
	*(DWORD *)((char*)pPlayerPed + 0x260) |= 1u;

	// Set our player info with the ped
	pPlayerPed->m_pPlayerInfo = m_pPlayerInfo->GetPlayerInfo();

	// Create the player ped instance
	m_pPlayerPed = new CIVPlayerPed(pPlayerPed);

	// Set the context data player ped pointer
	m_pContextData->SetPlayerPed(m_pPlayerPed);

	// Setup ped intelligence
	((void(__thiscall*) (IVPed *, BYTE)) (COffsets::IV_Func__SetupPedIntelligence))(pPlayerPed, 2);

	// Add to the world
	m_pPlayerPed->AddToWorld();

	// Create the player blip
	CIVScript::AddBlipForChar(GetScriptingHandle(), &m_uiBlip);
	CIVScript::ChangeBlipNameFromAscii(m_uiBlip, m_strNick.Get());

	// Unfreeze the player
	CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_FREEZE_CHAR_POSITION, GetScriptingHandle(), false);

	// Disable head ik
	CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_BLOCK_CHAR_HEAD_IK, GetScriptingHandle(), true);

	// Disable shot los
	CIVScript_NativeInvoke::Invoke<unsigned int>(CIVScript::NATIVE_SET_CHAR_WILL_ONLY_FIRE_WITH_CLEAR_LOS, GetScriptingHandle(), false);

	// Mark as spawned
	m_bSpawned = true;

	return true;
}

bool CPlayerEntity::Destroy()
{
	// Is this the localplayer?
	if(IsLocalPlayer())
		return false;

	// Is the player not spawned?
	if(!IsSpawned())
		return false;

	// Get the ped pointer
	IVPlayerPed * pPlayerPed = m_pPlayerPed->GetPlayerPed();

	// Deconstruct the ped intelligence
	((void(__thiscall*) (IVPedIntelligence *, BYTE)) (COffsets::IV_Func__ShutdownPedIntelligence))(pPlayerPed->m_pPedIntelligence, 0);

	*(DWORD *)((char*)pPlayerPed + 0x260) &= 0xFFFFFFFE;

	// Remove the ped from the world
	m_pPlayerPed->RemoveFromWorld();

	// Delete the player ped
	((void(__thiscall*) (IVPed *, BYTE)) (COffsets::IV_Func__DeletePed))(pPlayerPed, 1);

	// Remove the model reference
	m_pModelInfo->RemoveReference();

	// Do we have a valid context data record?
	if(m_pContextData)
	{
		// Delete the context data instance
		CContextDataManager::DestroyContextData(m_pContextData);

		// Invalidate the context data pointer
		m_pContextData = NULL;
	}

	// Delete the player ped instance
	SAFE_DELETE(m_pPlayerPed);

	// Delete the player info instance
	SAFE_DELETE(m_pPlayerInfo);

	// Do we have a valid CIVScript handle?
	if(m_bytePlayerNumber != INVALID_PLAYER_PED)
	{
		// Reset the game player info pointer
		g_pCore->GetGame()->GetPools()->SetPlayerInfoAtIndex((unsigned int)m_bytePlayerNumber, NULL);

		// Invalidate the player number
		m_bytePlayerNumber = INVALID_PLAYER_PED;
	}

	// Mark as not spawned
	m_bSpawned = false;

	// Remove the blip
	CIVScript::RemoveBlip(m_uiBlip);

	return true;
}

void CPlayerEntity::SetPosition(CVector3& vecPosition, bool bForce)
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Are we not in a vehicle and not entering a vehicle?
		if(!InternalIsInVehicle() && !HasVehicleEnterExit())
		{
			Vector4 coords(vecPosition.fX, vecPosition.fY, vecPosition.fZ, 0);
			m_pPlayerPed->GetPed()->SetCoordinates(&coords, 1, 0);
			m_pPlayerPed->GetPed()->UpdatePhysicsMatrix(true);
		}
	}

	// Just update the position
	if (bForce) 
	{
		RemoveTargetPosition();
		m_vecPosition = vecPosition;
	}
	CNetworkEntity::SetPosition(vecPosition);
}

void CPlayerEntity::GetPosition(CVector3& vecPosition)
{
	if (IsSpawned())
		m_pPlayerPed->GetPosition(vecPosition);
	else
		vecPosition = m_vecPosition;
}

CVector3 CPlayerEntity::GetPosition()
{
	CVector3 vecPosition;

	if (IsSpawned())
		m_pPlayerPed->GetPosition(vecPosition);
	else
		vecPosition = m_vecPosition;

	return vecPosition;
}

void CPlayerEntity::Teleport(CVector3 vecPosition)
{
	CIVScript::SetCharCoordinatesNoOffset(GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ);

	// Set position for varible.
	m_vecPosition = m_vecPosition;
	CNetworkEntity::SetPosition(vecPosition);
}

void CPlayerEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->SetMoveSpeed(vecMoveSpeed);

	CNetworkEntity::SetMoveSpeed(vecMoveSpeed);
}

void CPlayerEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->GetMoveSpeed(vecMoveSpeed);
	else
		vecMoveSpeed = CVector3();
}

void CPlayerEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->SetTurnSpeed(vecTurnSpeed);

	CNetworkEntity::SetTurnSpeed(vecTurnSpeed);
}

void CPlayerEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	if(IsSpawned())
		m_pPlayerPed->GetTurnSpeed(vecTurnSpeed);
	else
		vecTurnSpeed = CVector3();
}

void CPlayerEntity::SetNick(CString strNick)
{
	m_strNick = strNick;
	CLogFile::Printf("Setting name to %s", strNick.Get());
	//CIVScript::GivePedFakeNetworkName(GetScriptingHandle(), m_strNick.Get(), CColor(m_uiColor));
}


void CPlayerEntity::SetColor(unsigned uiColor)
{
	// Save the colour
	m_uiColor = uiColor;

	// Do we have an active blip?
	if(m_uiBlip)
	{
		// Set the blip colour
		CIVScript::ChangeBlipColour(m_uiBlip, uiColor);
	}

	// Do we have a vaid player info pointer?
	if(m_pPlayerInfo)
	{
		// Set the player colour
		m_pPlayerInfo->SetColour(uiColor);
	}
}

unsigned CPlayerEntity::GetScriptingHandle()
{
	return g_pCore->GetGame()->GetPools()->GetPedPool()->HandleOf(m_pPlayerPed->GetPed());
}

void CPlayerEntity::SetHealth(float fHealth)
{
	CIVScript::SetCharHealth(GetScriptingHandle(), fHealth + 100);
}

float CPlayerEntity::GetHealth()
{
	unsigned fHealth;
	CIVScript::GetCharHealth(GetScriptingHandle(), &fHealth);
	return (float)fHealth;
}

void CPlayerEntity::SetArmour(float fnewArmour)
{
	if (IsSpawned())
	{
		unsigned int uiArmour;
		CIVScript::GetCharArmour(GetScriptingHandle(), &uiArmour);

		CIVScript::AddCharArmour(GetScriptingHandle(), fnewArmour - uiArmour);
	}
}

float CPlayerEntity::GetArmour()
{
	// Are we spawned?
    if(IsSpawned())
    {
        unsigned int uiArmour;
        CIVScript::GetCharArmour(GetScriptingHandle(), &uiArmour);
        return uiArmour;
    }

    // Not spawned
    return 0;
}

void CPlayerEntity::SetRotation(CVector3& vecRotation)
{
	if (IsSpawned())
	{
		// Get the player matrix
		Matrix matMatrix;
		m_pPlayerPed->GetMatrix(matMatrix);

		// Convert the rotation from degrees to radians
		CVector3 vecNewRotation = Math::ConvertDegreesToRadians(vecRotation);

		// Apply the rotation to the vehicle matrix
		CGameFunction::ConvertEulerAnglesToRotationMatrix(vecNewRotation, matMatrix);

		// Set the new vehicle matrix
		m_pPlayerPed->SetMatrix(matMatrix);
	}

	m_vecRotation = vecRotation;
}

void CPlayerEntity::GetRotation(CVector3& vecRotation)
{
	if (IsSpawned())
	{
		// Get the player matrix
		Matrix matMatrix;
		m_pPlayerPed->GetMatrix(matMatrix);

		// Convert the matrix to euler angles
		CVector3 vecNewRotation;
		CGameFunction::ConvertRotationMatrixToEulerAngles(matMatrix, vecNewRotation);

		// Flip the rotation
		vecNewRotation.fX = ((2 * PI) - vecNewRotation.fX);
		vecNewRotation.fY = ((2 * PI) - vecNewRotation.fY);
		vecNewRotation.fZ = ((2 * PI) - vecNewRotation.fZ);

		// Convert the rotation from radians to degrees
		vecRotation = Math::ConvertRadiansToDegrees(vecNewRotation);
	}
	else
		vecRotation = m_vecRotation;
}


void CPlayerEntity::SetHeading(float fAngle)
{
	IVPed * pPed = m_pPlayerPed->GetPed();

	if(pPed)
		pPed->m_fCurrentHeading = fAngle;
}

float CPlayerEntity::GetHeading()
{
	IVPed * pPed = m_pPlayerPed->GetPed();

	if(pPed)
		return (pPed->m_fCurrentHeading);

	return 0.0f;
}

void CPlayerEntity::SetModel(int iModelId)
{
	// Get the model hash from skin id
	DWORD dwModelHash = SkinIdToModelHash(iModelId);

	if (dwModelHash == m_pModelInfo->GetHash())
		return;

	// Get the model index
	int iModelIndex = CIVModelManager::GetModelIndexFromHash(dwModelHash);

	// Get the model info
	CIVModelInfo * pModelInfo = g_pCore->GetGame()->GetModelInfo(iModelIndex);

	m_pModelInfo->RemoveReference();
	m_pModelInfo = pModelInfo;

	if(IsSpawned())
	{
		// Add reference
		m_pModelInfo->AddReference(true);

		CIVScript::GetCharDrawableVariation(GetScriptingHandle(), CIVScript::ePedComponent::PED_COMPONENT_FACE);

		// change the model from the player
		CIVScript::ChangePlayerModel(m_bytePlayerNumber,(CIVScript::eModel)dwModelHash);

		m_pPlayerPed->SetPed(m_pPlayerInfo->GetPlayerPed());
	}
}

void CPlayerEntity::SetWantedLevel(int iWantedLevel)
{
	if (IsSpawned())
	{
		m_iWantedLevel = iWantedLevel;
		CIVScript::SetFakeWantedLevel(iWantedLevel);
	}
}

int CPlayerEntity::GetWantedLevel()
{
	if (IsSpawned())
	{
		return m_iWantedLevel;
	}

	return 0;
}

void CPlayerEntity::SetControlState(CControls * pControlState)
{
	// Is the player spawned?
	if(IsSpawned())
	{
		// Get the game pad
		CIVPad * pPad = g_pCore->GetGame()->GetPad();

		// Is this not the localplayr?
		if(!IsLocalPlayer())
		{
			// Get the context data pad
			pPad = m_pContextData->GetPad();
		}

		// Set the last control state
		pPad->SetLastControlState(m_ControlState);

		// Set the current control state
		pPad->SetCurrentControlState(*pControlState);
	}

	// Copy the current control state
	memcpy(&m_lastControlState, &m_ControlState, sizeof(CControls));

	// Copy the control state
	memcpy(&m_ControlState, pControlState, sizeof(CControls));
}

void CPlayerEntity::GetControlState(CControls * pControlState)
{
	// Copy the current controls
	memcpy(pControlState, &m_ControlState, sizeof(CControls));
}

void CPlayerEntity::GetLastControlState(CControls * pControlState)
{
	// Copy the last controls
	memcpy(pControlState, &m_lastControlState, sizeof(CControls));
}

void CPlayerEntity::InternalPutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat)
{
	// Is the player spawned and not in a vehicle?
	if(IsSpawned() && !InternalIsInVehicle())
	{
		// Is this the driver seat?
		if(byteSeat == 0)
		{
			CIVScript::WarpCharIntoCar(GetScriptingHandle(), pVehicle->GetScriptingHandle());
		}
		else
		{
			// Is the passenger seat valid?
			if(byteSeat <= pVehicle->GetMaxPassengers())
			{
				CIVScript::WarpCharIntoCarAsPassenger(GetScriptingHandle(), pVehicle->GetScriptingHandle(), (byteSeat - 1));
			}
		}
	}
}

void CPlayerEntity::InternalRemoveFromVehicle()
{
	// Are we spawned and in a vehicle?
	if(IsSpawned() && m_pVehicle)
	{
		// Create the car set ped out task
		CIVTaskSimpleCarSetPedOut * pTask = new CIVTaskSimpleCarSetPedOut(m_pVehicle->GetGameVehicle(), 0xF, 0, 1);

		// Was the task created?
		if(pTask)
		{
			// Process the ped
			pTask->ProcessPed(m_pPlayerPed);

			// Destroy the task
			pTask->Destroy();
		}
	}
}

bool CPlayerEntity::InternalIsInVehicle()
{
	// Are we spawned?
	if(IsSpawned())
		return (m_pPlayerPed->IsInVehicle());

	return false;
}

CVehicleEntity * CPlayerEntity::InternalGetVehicle()
{
	//m_pPlayerPed->GetCurrentVehicle();
	return NULL;
}

void CPlayerEntity::PutInVehicle(CVehicleEntity * pVehicle, BYTE byteSeat)
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Is the vehicle invalid?
	if(!pVehicle)
		return;

	// Are we already in a vehicle?
	if(IsInVehicle())
	{
		// Remove from the vehicle
		RemoveFromVehicle();
	}

	// Put the player in the vehicle
	InternalPutInVehicle(pVehicle, byteSeat);

	// Reset entry/exit
	ResetVehicleEnterExit();

	// Store the vehicle pointer
	m_pVehicle = pVehicle;

	// Store the seat
	m_byteSeat = byteSeat;

	// Set us in the vehicle
	m_pVehicle->SetOccupant(byteSeat, this);
}

void CPlayerEntity::RemoveFromVehicle()
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Are we not in a vehicle?
	if(!m_pVehicle)
		return;

	// Internally remove ourselfs from the vehicle
	InternalRemoveFromVehicle();

	// Reset the vehicle seat
	m_pVehicle->SetOccupant(m_byteSeat, NULL);

	// Reset our vehicle pointer
	m_pVehicle = NULL;

	// Reset our seat
	m_byteSeat = 0;

	// Reset entry/exit
	ResetVehicleEnterExit();
}

bool CPlayerEntity::IsAnyWeaponUser()
{
	//TODO: Remote player task check.
	bool bReturn = false;

	return bReturn;
}

void CPlayerEntity::EnterVehicle(CVehicleEntity * pVehicle, BYTE byteSeat)
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Is the vehicle invalid?
	if(!pVehicle)
		return;

	// Are we already in a vehicle?
	if(IsInVehicle())
		return;

	// Create the enter vehicle task
	int iUnknown = -4;

	switch(byteSeat)
	{
	case 0: iUnknown = -7; break;
	case 1: iUnknown = 2; break;
	case 2: iUnknown = 1; break;
	case 3: iUnknown = 3; break;
	}

	unsigned int uiUnknown = 0;
	if(byteSeat > 0)
		uiUnknown = 0x200000;

	CIVTaskComplexNewGetInVehicle * pTask = new CIVTaskComplexNewGetInVehicle(pVehicle->GetGameVehicle(), iUnknown, 27, uiUnknown, -2.0f);

	// Did the task get created?
	if(pTask)
	{
		// Set it as the ped task
		pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_PRIMARY);
	}

	// Mark as enter a vehicle
	m_pVehicleEnterExit->bEntering = true;
	m_pVehicleEnterExit->pVehicle = pVehicle;
	m_pVehicleEnterExit->byteSeat = byteSeat;
}

void CPlayerEntity::ExitVehicle(eExitVehicleType exitType)
{
	// Are we not spawned?
	if(!IsSpawned())
		return;

	// Are we not in a vehicle?
	if(!m_pVehicle)
	{
		// Are we entering a vehicle?
		if(HasVehicleEnterExit())
		{
			// Clear the vehicle entry task
			ClearVehicleEntryTask();
		}
		return;
	}

	CVector3 vecMoveSpeed;
	int iModelId;
	int iExitMode = 0xF;

	m_pVehicle->GetMoveSpeed(vecMoveSpeed);
	iModelId = CIVModelManager::ModelHashToVehicleId(m_pVehicle->GetModelInfo()->GetHash());

	if(exitType == EXIT_VEHICLE_NORMAL)
	{
		if(vecMoveSpeed.fX < -10 || vecMoveSpeed.fX > 10 || vecMoveSpeed.fY < -10 || vecMoveSpeed.fY > 10)
		{
			switch(iModelId)
			{
			case 2: case 4: case 5: case 7: case 8: case 10: case 11:
			case 31: case 32: case 49: case 50: case 51: case 52:
			case 53: case 55: case 56: case 60: case 66: case 73:
			case 85: case 86: case 94: case 104:
				iExitMode = 0x40B;
				break;

			default:
				{
					if(iModelId != 12 && iModelId < 166)
						iExitMode = 0x100E;
				}
			}
		}
	}
	else
	{
		iExitMode = 0x9C4;
	}

	// Create the vehile exit task
	CIVTaskComplexNewExitVehicle * pTask = new CIVTaskComplexNewExitVehicle(m_pVehicle->GetGameVehicle(), iExitMode, 0, 0);

	// Did the task get created
	if(pTask)
	{
		// Set the ped task
		pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_PRIMARY);
	}

	// Mark as exiting vehicle
	m_pVehicleEnterExit->bExiting = true;
}

void CPlayerEntity::CheckVehicleEnterExit()
{
	// Are we spawned?
	if(IsSpawned() && g_pCore->GetGame()->GetLocalPlayer()->GetAdvancedControlState())
	{

		// Are we not in a vehicle?
		if(!InternalIsInVehicle())
		{
			if(m_pVehicleEnterExit->bEntering)
			{
				// Is the flag wrong (did the player cancel entering ?)
				if (!IsGettingIntoAVehicle())
				{
					if (IsLocalPlayer())
					{
						g_pCore->GetChat()->Print("VehicleEntryAborted");
						m_pVehicleEnterExit->bEntering = false;
					}
				}
			}

			// Has the enter/exit vehicle key been pressed?
			if(m_lastControlState.IsUsingEnterExitVehicle() || m_lastControlState.IsUsingHorn())
			{
				// Are we not already requesting an enter?
				if(!m_pVehicleEnterExit->bEntering)
				{
					CVehicleEntity * pVehicle = NULL;
					BYTE byteSeat = 0;
					bool bFound = GetClosestVehicle(m_lastControlState.IsUsingHorn(), &pVehicle, byteSeat);

					// Have we found a vehicle?
					if(bFound)
					{
						if (m_pVehicle)
							m_pVehicle = NULL;
						// Enter the vehicle
						EnterVehicle(pVehicle, byteSeat);

						// Send to the server
						RakNet::BitStream bitStream;
						bitStream.Write(m_pVehicleEnterExit->pVehicle->GetId());
						bitStream.Write(byteSeat);
						g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_ENTER_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);

						g_pCore->GetChat()->Print(CString("HandleVehicleEntry(%d, %d)", pVehicle->GetId(), byteSeat));
					}
				}
			}
		}
		else
		{
			// Has the enter/exit vehicle key been pressed?
			if(m_lastControlState.IsUsingEnterExitVehicle())
			{
				// Are we not already requesting an exit?
				if(!m_pVehicleEnterExit->bExiting)
				{
					// Exit the vehicle
					ExitVehicle(EXIT_VEHICLE_NORMAL);

					// Send to the server
					RakNet::BitStream bitStream;
					bitStream.Write(m_pVehicle->GetId());
					bitStream.Write(m_byteSeat);
					g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_EXIT_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);

					g_pCore->GetChat()->Print(CString("HandleVehicleExit(%d, %d)", m_pVehicle->GetId(), m_byteSeat));
				}
			}
		}
	}
}

bool CPlayerEntity::GetClosestVehicle(bool bPassenger, CVehicleEntity ** pVehicle, BYTE& byteSeat)
{
	// Are we spawned?
	if(IsSpawned())
	{
		float fCurrent = 6.0f;
		CVector3 vecVehiclePosition;
		CVehicleEntity * pClosestVehicle = NULL;

		// Get our current position
		CVector3 vecPosition;
		GetPosition(vecPosition);

		// Loop through all current vehicles
		for(int i = 0; i < g_pCore->GetGame()->GetVehicleManager()->GetCount(); i++)
		{
			// Get a pointer to this vehicle
			CVehicleEntity * pThisVehicle = g_pCore->GetGame()->GetVehicleManager()->GetAt(i);

			// Get this vehicle position
			pThisVehicle->GetPosition(vecVehiclePosition);

			// Get the disance between us and the vehicle
			float fDistance = Math::GetDistanceBetweenPoints3D(vecPosition.fX, vecPosition.fY, vecPosition.fZ, vecVehiclePosition.fX, vecVehiclePosition.fY, vecVehiclePosition.fZ);

			// Is the distance less than the current?
			if(fDistance < fCurrent)
			{
				// Set the current distance
				fCurrent = fDistance;

				// Set the closest vehicle pointer
				pClosestVehicle = pThisVehicle;
			}
		}

		// Do we have a valid vehicle pointer?
		if(!pClosestVehicle)
			return false;

		// Are we looking for a passenger seat?
		if(bPassenger)
		{
			// Loop through all passenger seats
			BYTE byteCurrentSeat = 0;

			for(BYTE i = 0; i < pClosestVehicle->GetMaxPassengers(); i++)
			{
				byteCurrentSeat = (i + 1);
			}

			// Do we not have a valid seat?
			if(byteCurrentSeat == 0)
				return false;

			// Set the seat
			byteSeat = byteCurrentSeat;
		}
		else
		{
			// Set the seat
			byteSeat = 0;
		}
		// Set the vehicle pointer
		*pVehicle = pClosestVehicle;
		return true;
	}

	return false;
}

void CPlayerEntity::GiveMoney(int iAmount)
{
	if(IsSpawned())
	{
		// this shows +/-$12345
		CIVScript::AddScore(m_bytePlayerNumber, iAmount);

		// would take forever
		if(iAmount < -1000000 || iAmount > 1000000)
			m_pPlayerInfo->SetDisplayScore(m_pPlayerInfo->GetScore());
	}
}
void CPlayerEntity::SetMoney(int iAmount)
{
	if(IsSpawned())
	{
		m_pPlayerInfo->SetScore(iAmount);

		// would take forever
		int iDiff = (iAmount - m_pPlayerInfo->GetDisplayScore());

		if(iDiff < -1000000 || iDiff > 1000000)
			m_pPlayerInfo->SetDisplayScore(iAmount);
	}
}

void CPlayerEntity::ResetMoney()
{
	if(IsSpawned())
	{
		m_pPlayerInfo->SetScore(0);
		m_pPlayerInfo->SetDisplayScore(0);
	}
}

int CPlayerEntity::GetMoney()
{
	if(IsSpawned())
		return m_pPlayerInfo->GetScore();

	return 0;
}

void CPlayerEntity::ClearVehicleEntryTask()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		CIVTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is the task valid?
		if(pTask)
		{
			// Is this task getting in a vehicle?
			if(pTask->GetType() == TASK_COMPLEX_NEW_GET_IN_VEHICLE)
			{
				m_pPlayerPed->GetPedTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);
			}
		}
	}
}

void CPlayerEntity::ClearVehicleExitTask()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		CIVTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is the task valid?
		if(pTask)
		{
			// Is this task getting out of a vehicle?
			if(pTask->GetType() == TASK_COMPLEX_NEW_EXIT_VEHICLE)
			{
				m_pPlayerPed->GetPedTaskManager()->RemoveTask(TASK_PRIORITY_PRIMARY);
			}
		}
	}
}

void CPlayerEntity::ProcessVehicleEnterExit()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Are we internally in a vehicle?
		if(InternalIsInVehicle())
		{
			// Are we flagged as entering a vehicle?
			if(m_pVehicleEnterExit->bEntering)
			{
				// Has the enter vehicle task finished?
				if(!IsGettingIntoAVehicle())
				{
					// Vehicle entry is complete
					m_pVehicleEnterExit->pVehicle->SetOccupant(m_pVehicleEnterExit->byteSeat, this);

					// Store the vehicle
					m_pVehicle = m_pVehicleEnterExit->pVehicle;

					// Store the seat
					m_byteSeat = m_pVehicleEnterExit->byteSeat;

					// Reset vehicle enter/exit
					ResetVehicleEnterExit();

					// We dont have to send it to the server its handled automatically by the sync

					g_pCore->GetChat()->Print("VehicleEntryComplete()");
				}
			}
		}
		else
		{
			// Are we flagged as exiting?
			if(m_pVehicleEnterExit->bExiting)
			{
				// Has the exit vehicle task finished?
				if(!IsGettingOutOfAVehicle())
				{
					// Reset vehicle enter/exit
					ResetVehicleEnterExit();

					// We dont have to send it to the server its handled automatically by the sync

					g_pCore->GetChat()->Print("VehicleExitComplete()");
				}
			}
		}
	}
}

void CPlayerEntity::ResetVehicleEnterExit()
{
	// If player was exiting vehicle, process to proper reset first
	if(m_pVehicle && m_pVehicleEnterExit->bExiting)
	{
		// Reset the seat
		m_pVehicle->SetOccupant(m_byteSeat, NULL);
		m_byteSeat = 0;

		// Reset the vehicle
		m_pVehicle = NULL;
	}

	// Reset
	m_pVehicleEnterExit->bEntering = false;
	m_pVehicleEnterExit->pVehicle = NULL;
	m_pVehicleEnterExit->byteSeat = 0;
	m_pVehicleEnterExit->bExiting = false;
	m_pVehicleEnterExit->bRequesting = false;

	// Clear the vehicle entry task
	ClearVehicleEntryTask();

	// Clear the vehicle exit task
	ClearVehicleExitTask();
}

bool CPlayerEntity::IsGettingIntoAVehicle()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		CIVTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is the task valid?
		if(pTask)
		{
			// Is this task getting in a vehicle?
			if(pTask->GetType() == TASK_COMPLEX_NEW_GET_IN_VEHICLE)
				return true;
		}
	}

	return false;
}

bool CPlayerEntity::IsJumping()
{
	if (IsSpawned())
	{
		// Get the ped task
		CIVTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is the task valid?
		if (pTask)
		{
			// Is this task getting in a vehicle?
			if (pTask->GetType() == TASK_COMPLEX_JUMP)
				return true;
		}
	}

	return false;
}
bool CPlayerEntity::IsGettingOutOfAVehicle()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Get the ped task
		CIVTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_PRIMARY);

		// Is the task valid?
		if(pTask)
		{
			// Is this task getting in a vehicle?
			if(pTask->GetType() == TASK_COMPLEX_NEW_EXIT_VEHICLE)
				return true;
		}
	}

	return false;
}


void CPlayerEntity::UpdateTargetPosition()
{
	if(HasTargetPosition())
	{
		unsigned long ulCurrentTime = SharedUtility::GetTime();

		// Get our position
		CVector3 vecCurrentPosition;
		GetPosition(vecCurrentPosition);

		// Get the factor of time spent from the interpolation start
		// to the current time.
		float fAlpha = Math::Unlerp(m_pInterpolationData->pPosition.ulStartTime, ulCurrentTime, m_pInterpolationData->pPosition.ulFinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_pInterpolationData->pPosition.fLastAlpha);
		m_pInterpolationData->pPosition.fLastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_pInterpolationData->pPosition.vecError);

		// If we finished compensating the error, finish it for the next pulse
		if(fAlpha == 1.0f)
			m_pInterpolationData->pPosition.ulFinishTime = 0;

		// Calculate the new position
		CVector3 vecNewPosition = (vecCurrentPosition + vecCompensation);

		// Check if the distance to interpolate is too far
		if((vecCurrentPosition - m_pInterpolationData->pPosition.vecTarget).Length() > 5)
		{
			// Abort all interpolation
			m_pInterpolationData->pPosition.ulFinishTime = 0;
			vecNewPosition = m_pInterpolationData->pPosition.vecTarget;
		}

		// Set our new position
		SetPosition(vecNewPosition, false);
	}
}

void CPlayerEntity::Interpolate()
{
	// Are we not getting in/out of a vehicle?
	if(true)
		UpdateTargetPosition();
}

void CPlayerEntity::ApplySyncData(CVector3 vecPosition, CVector3 vecMovement, CVector3 vecTurnSpeed, CVector3 vecRoll, CVector3 vecDirection, bool bDuck, float fHeading)
{
	CLogFile::Printf("%f %f %f, %f %f %f, %f %f %f, %f %f %f, %f %f %f, %d, %f", 
		vecPosition.fX, vecPosition.fY, vecPosition.fZ,
		vecMovement.fX, vecMovement.fY, vecMovement.fZ,
		vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ,
		vecRoll.fX, vecRoll.fY, vecRoll.fZ,
		vecDirection.fX, vecDirection.fY, vecDirection.fZ,
		bDuck, fHeading);

	
}

#if 0
void CPlayerEntity::ApplyWeaponSync()
{

}
#endif

void CPlayerEntity::SetTargetPosition(const CVector3 &vecPosition, unsigned long ulDelay)
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Update our target position
		UpdateTargetPosition();

		// Get our position
		CVector3 vecCurrentPosition;
		GetPosition(vecCurrentPosition);

		// Set the target position
		m_pInterpolationData->pPosition.vecTarget = vecPosition;

		// Calculate the relative error
		m_pInterpolationData->pPosition.vecError = (vecPosition - vecCurrentPosition);

		// Get the interpolation interval
		unsigned long ulTime = SharedUtility::GetTime();
		m_pInterpolationData->pPosition.ulStartTime = ulTime;
		m_pInterpolationData->pPosition.ulFinishTime = (ulTime + ulDelay);

		// Initialize the interpolation
		m_pInterpolationData->pPosition.fLastAlpha = 0.0f;
	}
}

void CPlayerEntity::SetMoveToDirection(CVector3 vecPos, CVector3 vecMove, int iMoveType)
{
	if(IsSpawned()) {

		float tX = (vecPos.fX + (vecMove.fX * (10)));
		float tY = (vecPos.fY + (vecMove.fY * (10)));
		float tZ = (vecPos.fZ + (vecMove.fZ * (10)));
		unsigned int uiPlayerIndex = GetScriptingHandle();


		_asm	push 1000;
		_asm	push iMoveType;
		_asm	push tZ;
		_asm	push tY;
		_asm	push tX;
		_asm	push uiPlayerIndex;
		_asm	call COffsets::IV_Func__MovePedToPositionInterpolated;
		_asm	add esp, 18h;
	}
}

void CPlayerEntity::RemoveTargetPosition()
{
	m_pInterpolationData->pPosition.ulFinishTime = 0;
}

void CPlayerEntity::ResetInterpolation()
{
	RemoveTargetPosition();
}


void CPlayerEntity::SetAimData(bool bSwitch, CVector3 vecPosition)
{
	switch(bSwitch)
	{
	case true:
		{
			m_aimData.bSwitch = bSwitch;
			memcpy(&m_aimData, &vecPosition, sizeof(CVector3));
		}
	case false:
		{
			m_aimData.bSwitch = bSwitch;
			memcpy(&m_aimData, NULL, sizeof(CVector3));
		}
	}
}

void CPlayerEntity::SetShotData(bool bSwitch, CVector3 vecPosition)
{
	switch(bSwitch)
	{
	case true:
		{
			m_shotData.bSwitch = bSwitch;
			memcpy(&m_shotData, &vecPosition, sizeof(CVector3));
		}
	case false:
		{
			m_shotData.bSwitch = bSwitch;
			memcpy(&m_shotData, NULL, sizeof(CVector3));
		}
	}
}

void CPlayerEntity::UpdateTargetRotation()
{
	if(HasTargetRotation())
	{
		unsigned long ulCurrentTime = SharedUtility::GetTime();

		// Get the factor of time spent from the interpolation start
		// to the current time.
		float fAlpha = Math::Unlerp(m_pInterpolationData->pRotation.ulStartTime, ulCurrentTime, m_pInterpolationData->pRotation.ulFinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - m_pInterpolationData->pRotation.fLastAlpha);
		m_pInterpolationData->pRotation.fLastAlpha = fAlpha;

		// Apply the error compensation
		float fCompensation = Math::Lerp(0.0f, fCurrentAlpha, m_pInterpolationData->pRotation.fError);

		// If we finished compensating the error, finish it for the next pulse
		if(fAlpha == 1.0f)
			m_pInterpolationData->pRotation.ulFinishTime = 0;

		// Get our rotation
		float fCurrentHeading = GetHeading();

		// Calculate the new rotation
		float fNewRotation = (fCurrentHeading + fCompensation);

		// Set our new rotation
		SetHeading(fNewRotation);
	}
}

void CPlayerEntity::KillPed(bool bInstantly)
{
	// Are we spawned and not already dead?
	if(IsSpawned() && !IsDead())
	{
		// Are we getting killed instantly?
		if(bInstantly) {

			// Create the dead task
			CIVTaskSimpleDead * pTask = new CIVTaskSimpleDead(CGameFunction::GetTimeOfDay(), 1, 0);

			// Did the task create successfully?
			if(pTask)
				pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
		}
		else { // We are not getting killed instantly

			// Are we already dying?
			if(IsDying())
				return;

			// Create the death task
			CIVTaskComplexDie * pTask = new CIVTaskComplexDie(0, 0, 44, 190, 4.0f, 0.0f, 1);

			// Did the task create successfully?
			if(pTask)
				pTask->SetAsPedTask(m_pPlayerPed, TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);
		}

		// Reset ped health, armour etc. values
		SetHealth(0);

		// Reset the control state
		CControls * controlState = new CControls;
		SetControlState(controlState);
		SAFE_DELETE(controlState);

		// Reset vehicle entry/exit flags
		m_pVehicleEnterExit->bExiting = true;
		ResetVehicleEnterExit();

		// Reset interpolation
		ResetInterpolation();
	}
}

bool CPlayerEntity::IsDying()
{
	if(IsSpawned())
	{
		CIVTask * pTask = m_pPlayerPed->GetPedTaskManager()->GetTask(TASK_PRIORITY_EVENT_RESPONSE_NONTEMP);

		if(pTask)
			if(pTask->GetType() == TASK_COMPLEX_DIE)
				return true;
	}

	return false;
}

bool CPlayerEntity::IsDead()
{
	if(IsSpawned())
		return IsDying();

	return false;
}

IVEntity * CPlayerEntity::GetLastDamageEntity()
{
	if(IsSpawned())
		return m_pPlayerPed->GetLastDamageEntity();

	return NULL;
}

bool CPlayerEntity::GetKillInfo(EntityId * playerId, EntityId * vehicleId, EntityId * weaponId)
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Reset player id and vehicle id
		*playerId = INVALID_ENTITY_ID;
		*vehicleId = INVALID_ENTITY_ID;
		*weaponId = INVALID_ENTITY_ID;

		// Loop through all players
		for(EntityId i = 0; i < MAX_PLAYERS; i++)
		{
			// Is this player connected and spawned?
			CPlayerEntity * pPlayer = g_pCore->GetGame()->GetPlayerManager()->GetAt(i);

			if(pPlayer && pPlayer->IsSpawned())
			{
				// Is this player the last damage entity?
				if(GetLastDamageEntity() == (IVEntity *)pPlayer->GetPlayerPed()->GetPed())
				{
					// This player killed us
					*playerId = i;
					//*weaponId = pPlayer->();
					break;
				}
				else
				{
					// Is this players vehicle the last damage entity?
					if(pPlayer->IsInVehicle() && !pPlayer->IsPassenger() && 
						(GetLastDamageEntity() == (IVEntity *)pPlayer->GetVehicleEntity()))
					{
						// This player killed us with their vehicle
						*playerId = i;
						//*weaponId = pPlayer->GetCurrentWeapon();
						*vehicleId = i;
						break;
					}
				}
			}
		}

		// Have we not yet found a killer?
		if(*playerId == INVALID_ENTITY_ID && *vehicleId == INVALID_ENTITY_ID)
		{
			// Loop through all players
			for(EntityId i = 0; i < MAX_VEHICLES; i++)
			{
				// Is this player connected and spawned?
				CVehicleEntity * pVehicle = g_pCore->GetGame()->GetVehicleManager()->GetAt(i);

				if(pVehicle && pVehicle->IsSpawned())
				{
					// Is this vehicle the last damage entity?
					if(GetLastDamageEntity() == pVehicle->GetGameVehicle()->GetEntity())
					{
						// This vehicle killed us
						*vehicleId = pVehicle->GetId();
						break;
					}
				}
			}
		}

		return true;
	}

	return false;
}

void CPlayerEntity::SetWeaponAimAtTask(CVector3 vecAimAt)
{
	if(IsSpawned())
	{
		CIVTaskSimpleAimGun * pTask = new CIVTaskSimpleAimGun(vecAimAt.fX, vecAimAt.fY, vecAimAt.fZ, 10000, 4, -4);

		// Was the task created?
		if(pTask)
		{
			// Process the ped
			pTask->ProcessPed(m_pPlayerPed);

			// Destroy the task
			pTask->Destroy();
		}
	}
}

void CPlayerEntity::SetWeaponShotAtTask(CVector3 vecAimAt)
{
	if (IsSpawned())
	{
		CIVTaskSimpleFireGun * pTask = new CIVTaskSimpleFireGun(vecAimAt.fX, vecAimAt.fY, vecAimAt.fZ, 10000, 4, -4);

		// Was the task created?
		if (pTask)
		{
			// Process the ped
			pTask->ProcessPed(m_pPlayerPed);

			// Destroy the task
			pTask->Destroy();
		}
	}
}

void CPlayerEntity::SetPedClothes(unsigned short ucBodyLocation, unsigned  char ucClothes)
{
	// Check if the bodylocation is out of our index
	if(ucBodyLocation > 10)
		return;

	if(IsSpawned()) {
		unsigned char ucClothesIdx = 0;
		unsigned uiDrawableVariations = m_pPlayerPed->GetNumberOfCharDrawableVariations(ucBodyLocation);

		for(unsigned uiDrawable = 0; uiDrawable < uiDrawableVariations; ++uiDrawable) {
			unsigned uiTextureVariations = m_pPlayerPed->GetNumberOfCharTextureVariations(ucBodyLocation, uiDrawable);

			for(unsigned uiTexture = 0; uiTexture < uiTextureVariations; ++uiTexture) {

				if(ucClothesIdx == ucClothes) {
					m_pPlayerPed->SetClothes(ucBodyLocation, uiDrawable, uiTexture);
					SetClothesValue(ucBodyLocation, ucClothes);
					return;
				}

				++ucClothesIdx;
			}
		}

		m_pPlayerPed->SetClothes(ucBodyLocation, 0, 0);
		SetClothesValue(ucBodyLocation, 0);
	}
	else
		SetClothesValue(ucBodyLocation, ucClothes);
}

unsigned char CPlayerEntity::GetPedClothes(unsigned short ucBodyLocation)
{
	// Check if the bodylocation is out of our index
	if(ucBodyLocation > 10)
		return 0;

	return GetClothesValueFromSlot(ucBodyLocation);
}

void CPlayerEntity::GiveWeapon(unsigned uiWeaponId, unsigned uiAmmunation)
{
	if (IsSpawned())
		CIVScript::GiveWeaponToChar(GetScriptingHandle(), uiWeaponId, uiAmmunation, true);
}

void CPlayerEntity::RemoveWeapon(unsigned uiWeaponId)
{
	if (IsSpawned())
		m_pPlayerPed->GetPedWeapons()->RemoveWeapon((eWeaponType) uiWeaponId);
}

void CPlayerEntity::RemoveAllWeapons()
{
	if (IsSpawned())
		m_pPlayerPed->GetPedWeapons()->RemoveAllWeapons();
}

void CPlayerEntity::SetCurrentWeapon(unsigned uiWeaponId)
{
	if (IsSpawned())
		m_pPlayerPed->GetPedWeapons()->SetCurrentWeaponByType((eWeaponType) uiWeaponId);
}

unsigned CPlayerEntity::GetCurrentWeapon()
{
	if (IsSpawned())
		return m_pPlayerPed->GetPedWeapons()->GetCurrentWeapon()->GetType();

	return eWeaponType::WEAPON_TYPE_UNARMED;
}

void CPlayerEntity::SetAmmunation(unsigned uiWeaponId, unsigned uiAmmunation)
{
	if (IsSpawned())
		m_pPlayerPed->GetPedWeapons()->SetAmmoByType((eWeaponType) uiWeaponId, uiAmmunation);
}

unsigned CPlayerEntity::GetAmmunation(unsigned uiWeaponId)
{
	if (IsSpawned())
		return m_pPlayerPed->GetPedWeapons()->GetAmmoByType((eWeaponType) uiWeaponId);
	
	return 0;
}

void CPlayerEntity::GetWeaponInSlot(unsigned uiWeaponSlot, unsigned &uiWeaponId, unsigned &uiAmmunation, unsigned &uiUnkown)
{
	if (IsSpawned())
	{
		uiAmmunation = m_pPlayerPed->GetPedWeapons()->GetAmmoBySlot((eWeaponSlot) uiWeaponSlot);
		uiWeaponId = m_pPlayerPed->GetPedWeapons()->GetWeaponInSlot((eWeaponSlot) uiWeaponSlot);
	}
}

unsigned CPlayerEntity::GetAmmunationInClip(unsigned uiWeapon)
{
	if (IsSpawned())
		return m_pPlayerPed->GetPedWeapons()->GetAmmoInClip();

	return 0;
}

void CPlayerEntity::SetAmmunationInClip(unsigned uiAmmunationInClip)
{
	if (IsSpawned())
		m_pPlayerPed->GetPedWeapons()->SetAmmoInClip(uiAmmunationInClip);
}

unsigned CPlayerEntity::GetMaxAmmunationInClip(unsigned uiWeapon)
{
	if (IsSpawned())
		return m_pPlayerPed->GetPedWeapons()->GetCurrentWeapon()->GetClipSize();

	return 0;
}

void CPlayerEntity::Serialize(RakNet::BitStream * pBitStream)
{
	if (IsOnFoot())
	{
		CNetworkPlayerSyncPacket PlayerPacket;

		// Apply current 3D Position to the sync package
		GetPosition(PlayerPacket.vecPosition);
		GetMoveSpeed(PlayerPacket.vecMoveSpeed);
		GetTurnSpeed(PlayerPacket.vecTurnSpeed);
		GetDirectionSpeed(PlayerPacket.vecDirection);
		GetRollSpeed(PlayerPacket.vecRoll);
		PlayerPacket.bDuckState = m_pPlayerPed->IsDucking();
		PlayerPacket.fHeading = GetHeading();
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(PlayerPacket.pControlState);

		PlayerPacket.fHealth = GetHealth();
		PlayerPacket.fArmor = GetArmour();

		PlayerPacket.weapon.iAmmo = GetAmmunation(GetCurrentWeapon());
		PlayerPacket.weapon.weaponType = GetCurrentWeapon();

		// Write player onfoot flag into raknet bitstream
		pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_ONFOOT);
		pBitStream->Write(PlayerPacket);

		// I know its hacky i will clean it up later its just working
		if (PlayerPacket.pControlState.IsAiming() || PlayerPacket.pControlState.IsFiring())
		{
			CNetworkPlayerWeaponSyncPacket WeaponPacket;

			if (PlayerPacket.pControlState.IsFiring())
			{
				m_pContextData->GetWeaponShotTarget(WeaponPacket.vecAimShotAtCoordinates);
				
			}
			else
			{
				m_pContextData->GetWeaponAimTarget(WeaponPacket.vecAimShotAtCoordinates);
			}

			m_pContextData->GetWeaponShotSource(WeaponPacket.vecShotSource);

			WeaponPacket.weapon.iAmmo = GetAmmunation(GetCurrentWeapon());
			WeaponPacket.weapon.weaponType = GetCurrentWeapon();

			pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_WEAPON);
			pBitStream->Write(WeaponPacket);
		}
	}
	else if (IsInVehicle() && !IsPassenger())
	{
		CNetworkPlayerVehicleSyncPacket VehiclePacket;
		VehiclePacket.vehicleId = m_pVehicle->GetId();
		m_pVehicle->GetGameVehicle()->GetMatrix(VehiclePacket.matrix);
		m_pVehicle->GetMoveSpeed(VehiclePacket.vecMoveSpeed);
		m_pVehicle->GetTurnSpeed(VehiclePacket.vecTurnSpeed);
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(VehiclePacket.ControlState);

		VehiclePacket.vehHealth = m_pVehicle->GetHealth();
		//VehiclePacket. = m_pVehicle->GetPetrolTankHealth();
		VehiclePacket.bEngineState = m_pVehicle->GetEngineState();
		VehiclePacket.playerArmor = GetArmour();
		VehiclePacket.playerHealth = GetHealth();
		VehiclePacket.weapon.iAmmo = GetAmmunation(GetCurrentWeapon());
		VehiclePacket.weapon.weaponType = GetCurrentWeapon();

		CIVScript::GetCarHeading(m_pVehicle->GetScriptingHandle(), &VehiclePacket.fHeading);

		pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_VEHICLE);
		pBitStream->Write(VehiclePacket);
	}
	else if (IsInVehicle() && IsPassenger())
	{
		CNetworkPlayerPassengerSyncPacket PassengerPacket;

		PassengerPacket.byteSeatId = m_byteSeat;
		g_pCore->GetGame()->GetPad()->GetCurrentControlState(PassengerPacket.ControlState);
		PassengerPacket.playerArmor = GetArmour();
		PassengerPacket.playerHealth = GetHealth();
		PassengerPacket.vecPosition = GetPosition();
		PassengerPacket.vehicleId = m_pVehicle->GetId();
		PassengerPacket.byteSeatId = m_byteSeat;
		
		pBitStream->Write(RPC_PACKAGE_TYPE_PLAYER_PASSENGER);
		pBitStream->Write(PassengerPacket);
	}

	
}

void CPlayerEntity::Deserialize(RakNet::BitStream * pBitStream)
{
	// TODO: move sync to functions
	ePackageType eType;
	pBitStream->Read(eType);
	if (eType == RPC_PACKAGE_TYPE_PLAYER_ONFOOT)
	{
		CNetworkPlayerSyncPacket PlayerPacket;
		if (IsInVehicle())
			m_pVehicle = nullptr;

		pBitStream->Read(PlayerPacket);

		unsigned int interpolationTime = SharedUtility::GetTime() - m_ulLastSyncReceived;

		if (GetCurrentWeapon() != PlayerPacket.weapon.weaponType)
			GiveWeapon(PlayerPacket.weapon.weaponType, PlayerPacket.weapon.iAmmo); // Set our current weapon
		if (GetAmmunation(PlayerPacket.weapon.iAmmo) != PlayerPacket.weapon.iAmmo) // Do we not have the right ammo?
			SetAmmunation(PlayerPacket.weapon.weaponType, PlayerPacket.weapon.iAmmo); // Set our ammo


		if (!IsGettingIntoAVehicle()
			&& !IsGettingOutOfAVehicle())
		{

			SetTargetPosition(PlayerPacket.vecPosition, interpolationTime);
			SetHeading(PlayerPacket.fHeading);
			SetMoveSpeed(PlayerPacket.vecMoveSpeed);
			SetTurnSpeed(PlayerPacket.vecTurnSpeed);
			m_pPlayerPed->SetDirection(PlayerPacket.vecDirection);
			m_pPlayerPed->SetRoll(PlayerPacket.vecRoll);
		}
		unsigned int uiPlayerIndex = GetScriptingHandle();

		char chMoveStyle = 0;
		if (PlayerPacket.vecMoveSpeed.Length() < 1.0)
		{
			// Delete any task lol 
			_asm	push 17;
			_asm	push 0;
			_asm	push uiPlayerIndex;
			_asm	call COffsets::IV_Func__DeletePedTaskID;
			_asm	add esp, 0Ch;
			chMoveStyle = 0;
		}
		else if (PlayerPacket.vecMoveSpeed.Length() < 3.0 && PlayerPacket.vecMoveSpeed.Length() >= 1.0)
			chMoveStyle = 1;
		else if (PlayerPacket.vecMoveSpeed.Length() < 5.0 && PlayerPacket.vecMoveSpeed.Length() > 3.0)
			chMoveStyle = 2;
		else
			chMoveStyle = 3;

		SetMoveToDirection(PlayerPacket.vecPosition, PlayerPacket.vecMoveSpeed, chMoveStyle + 1);

		GetPlayerPed()->SetDucking(PlayerPacket.bDuckState);

		SetHealth(PlayerPacket.fHealth);

		SetControlState(&PlayerPacket.pControlState);

		if (PlayerPacket.pControlState.IsJumping())
		{
			char iJumpStyle = 0;
			if (PlayerPacket.vecMoveSpeed.Length() < 1.0)
				iJumpStyle = 0; // jump index, 1 = jump while movment, 2 = jump while standing still
			else if (PlayerPacket.vecMoveSpeed.Length() >= 1.0)
				iJumpStyle = 1; // jump index, 1 = jump while movment, 2 = jump while standing still

			_asm	push iJumpStyle;
			_asm	push uiPlayerIndex;
			_asm	call COffsets::IV_FUNC__TaskPedJump;
			_asm	add esp, 8;
		}

		m_ulLastSyncReceived = SharedUtility::GetTime();
	}
	else if (eType == RPC_PACKAGE_TYPE_PLAYER_VEHICLE)
	{
		CNetworkPlayerVehicleSyncPacket VehiclePacket;
		pBitStream->Read(VehiclePacket);

		unsigned int interpolationTime = SharedUtility::GetTime() - m_ulLastSyncReceived;

		if (IsInVehicle())
		{
			if (m_pVehicle->GetId() == VehiclePacket.vehicleId)
			{
				Matrix matrix;

				m_pVehicle->GetGameVehicle()->GetMatrix(matrix);
				matrix.vecForward = VehiclePacket.matrix.vecForward;
				matrix.vecRight = VehiclePacket.matrix.vecRight;
				matrix.vecUp = VehiclePacket.matrix.vecUp;
				m_pVehicle->GetGameVehicle()->SetMatrix(matrix);

				SetControlState(&VehiclePacket.ControlState);
				
				m_pVehicle->SetTargetPosition(VehiclePacket.matrix.vecPosition, interpolationTime);
				CIVScript::SetCarHeading(m_pVehicle->GetScriptingHandle(), VehiclePacket.fHeading);

				m_pVehicle->SetMoveSpeed(VehiclePacket.vecMoveSpeed);
				m_pVehicle->SetTurnSpeed(VehiclePacket.vecTurnSpeed);
				
				
				m_pVehicle->SetHealth(VehiclePacket.vehHealth);
				//m_pVehicle->SetPetrolTankHealth(VehiclePacket.petrol);
				m_pVehicle->SetEngineState(VehiclePacket.bEngineState);

				SetArmour(VehiclePacket.playerArmor);
				SetHealth(VehiclePacket.playerHealth);
			}
			else
			{
				g_pCore->GetChat()->Print("mhm player is not in the correct vehicle");
			}
		}
		else
		{
			ResetVehicleEnterExit();

			// Put the player in the vehicle if vehicle enter/exit sync failed or not completed
			if (g_pCore->GetGame()->GetVehicleManager()->GetAt(VehiclePacket.vehicleId))
			{
				WarpIntoVehicle(g_pCore->GetGame()->GetVehicleManager()->GetAt(VehiclePacket.vehicleId));
			}
		}

		if (GetCurrentWeapon() != VehiclePacket.weapon.weaponType)
			GiveWeapon(VehiclePacket.weapon.weaponType, VehiclePacket.weapon.iAmmo); // Set our current weapon
		if (GetAmmunation(VehiclePacket.weapon.iAmmo) != VehiclePacket.weapon.iAmmo) // Do we not have the right ammo?
			SetAmmunation(VehiclePacket.weapon.weaponType, VehiclePacket.weapon.iAmmo); // Set our ammo


		m_ulLastSyncReceived = SharedUtility::GetTime();
	}
	else if (eType == RPC_PACKAGE_TYPE_PLAYER_PASSENGER)
	{
		unsigned int interpolationTime = SharedUtility::GetTime() - m_ulLastSyncReceived;

		CNetworkPlayerPassengerSyncPacket PassengerPacket;
		pBitStream->Read(PassengerPacket);

		SetPosition(PassengerPacket.vecPosition);

		SetArmour(PassengerPacket.playerArmor);
		SetHealth(PassengerPacket.playerHealth);

		if (!IsInVehicle() || !InternalIsInVehicle())
		{
			ResetVehicleEnterExit();

			// Put the player in the vehicle if vehicle enter/exit sync failed or not completed
			if (g_pCore->GetGame()->GetVehicleManager()->GetAt(PassengerPacket.vehicleId))
			{
				WarpIntoVehicle(g_pCore->GetGame()->GetVehicleManager()->GetAt(PassengerPacket.vehicleId), PassengerPacket.byteSeatId);
			}
		}
		
		m_ulLastSyncReceived = SharedUtility::GetTime();
	}


	// Check if we have additional packets
	if (pBitStream->Read(eType))
	{
		if (eType == RPC_PACKAGE_TYPE_PLAYER_WEAPON)
		{
			CNetworkPlayerWeaponSyncPacket AimSync;
			pBitStream->Read(AimSync);
			// First check if we're having any weapon data
			if (IsLocalPlayer())
				return;

			if (GetCurrentWeapon() != AimSync.weapon.weaponType) {
				// Set our current weapon
				GiveWeapon(AimSync.weapon.weaponType, AimSync.weapon.iAmmo);
			}
			// Do we not have the right ammo?
			if (GetAmmunation(AimSync.weapon.iAmmo) != AimSync.weapon.iAmmo) {
				// Set our ammo
				SetAmmunation(AimSync.weapon.weaponType, AimSync.weapon.iAmmo);
			}

			if (m_ControlState.IsAiming() && !m_ControlState.IsFiring())
			{
				m_pContextData->SetWeaponAimTarget(AimSync.vecAimShotAtCoordinates);

				unsigned int st = 0;
				CIVScript::OpenSequenceTask(&st);
				CIVScript::TaskAimGunAtCoord(GetScriptingHandle(), AimSync.vecAimShotAtCoordinates.fX, AimSync.vecAimShotAtCoordinates.fY, AimSync.vecAimShotAtCoordinates.fZ, 2000);
				CIVScript::CloseSequenceTask(st);
				if (!CIVScript::IsCharInjured(GetScriptingHandle()))
					CIVScript::TaskPerformSequence(GetScriptingHandle(), st);
				CIVScript::ClearSequenceTask(st);
			}
			else if (m_ControlState.IsFiring())
			{
				m_pContextData->SetWeaponShotSource(AimSync.vecShotSource);
				m_pContextData->SetWeaponShotTarget(AimSync.vecAimShotAtCoordinates);

				unsigned int st = 0;
				CIVScript::OpenSequenceTask(&st);
				CIVScript::TaskShootAtCoord(0, AimSync.vecAimShotAtCoordinates.fX, AimSync.vecAimShotAtCoordinates.fY, AimSync.vecAimShotAtCoordinates.fZ, 2000, 5); // 3 - fake shot
				CIVScript::CloseSequenceTask(st);
				if (!CIVScript::IsCharInjured(GetScriptingHandle()))
					CIVScript::TaskPerformSequence(GetScriptingHandle(), st);
				CIVScript::ClearSequenceTask(st);
			}
			else
			{
				unsigned int uiPlayerIndex = GetScriptingHandle();

				// Destroy shotat task
				_asm  push 36;
				_asm  push 0;
				_asm  push uiPlayerIndex;
				_asm  call COffsets::IV_Func__DeletePedTaskID;
				_asm  add esp, 0Ch;

				// Destroy aimat task
				_asm  push 35;
				_asm  push 0;
				_asm  push uiPlayerIndex;
				_asm  call COffsets::IV_Func__DeletePedTaskID;
				_asm  add esp, 0Ch;

			}
		}
	}
}

void CPlayerEntity::WarpIntoVehicle(CVehicleEntity * pVehicle, BYTE seat)
{
	if (seat > 3)
		return;

	if (seat == 0)
		CIVScript::WarpCharIntoCar(GetScriptingHandle(), pVehicle->GetScriptingHandle());
	else
		CIVScript::WarpCharIntoCarAsPassenger(GetScriptingHandle(), pVehicle->GetScriptingHandle(), seat - 1);

	m_pVehicle = pVehicle;
	m_byteSeat = seat;
}

bool CPlayerEntity::IsOnScreen()
{
	return g_pCore->GetGame()->GetCamera()->IsOnScreen(GetPosition());
}