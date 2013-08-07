//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CPlayerEntity.cpp
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
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

#include <CCore.h>
extern CCore * g_pCore;

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
	CIVScript::MODEL_M_Y_TOURIST_02,
};

DWORD SkinIdToModelHash(int modelid)
{
	if(modelid >= 0 || modelid < sizeof(dwPlayerModelHashes))
		return dwPlayerModelHashes[modelid];

	return 0x00;
}

CPlayerEntity::CPlayerEntity(bool bLocalPlayer) : CNetworkEntity()
{
	m_bLocalPlayer = bLocalPlayer;
	m_strNick.Set("Player");
	m_usPlayerId = -1;
	m_usPing = 0;
	m_bNetworked = false;
	m_uiColor = 0xFFFFFFFF;
	m_bSpawned = false;
	m_pPlayerPed = NULL;
	m_pPlayerInfo = NULL;
	m_pModelInfo = g_pCore->GetGame()->GetModelInfo(211);
	m_bytePlayerNumber = INVALID_PLAYER_PED;
	m_pContextData = NULL;
	m_vecPosition = CVector3();
	m_pVehicle = NULL;
	m_byteSeat = 0;
	memset(&m_lastControlState, 0, sizeof(CControls));
	memset(&m_ControlState, 0, sizeof(CControls));
	ResetVehicleEnterExit();

	CNetworkEntity::SetType(PLAYER_ENTITY);

	// Is this the localplayer?
	if(IsLocalPlayer())
	{
		// Set the localplayer CIVScript handle
		m_bytePlayerNumber = (BYTE)CPools::GetLocalPlayerIndex();

		// Create a new player ped instance
		IVPlayerInfo * pInfo = CPools::GetPlayerInfoFromIndex(0);
		m_pPlayerPed = new CIVPlayerPed(pInfo->m_pPlayerPed);

		// Get the localplayer info pointer
		m_pPlayerInfo = new CIVPlayerInfo(CPools::GetPlayerInfoFromIndex(0));

		// Create a new context data instance with the local player info
        m_pContextData = CContextDataManager::CreateContextData(m_pPlayerInfo);

        // Set the context data player ped pointer
        m_pContextData->SetPlayerPed(m_pPlayerPed);

		// Add our model reference
		m_pModelInfo->AddReference(false);

		// Set the localplayer name
		SetNick(g_pCore->GetNick());

		// Setup localplayer
		CIVScript::SetPlayerControlAdvanced(m_bytePlayerNumber, true, true, true);
		CIVScript::SetCameraControlsDisabledWithPlayerControls(true);

		m_bSpawned = true;

		CLogFile::Printf("m_bytePlayerNumber: %d, m_pPlayerPed: 0x%p, m_pPlayerInfo: 0x%p", m_bytePlayerNumber, m_pPlayerPed, m_pPlayerInfo);
	}
	else
    {
        // Set the player ped instance to NULL
        m_pPlayerPed = NULL;

        // Set the player info instance to NULL
        m_pPlayerInfo = NULL;
		
		// Set the context data instance to NULL
		m_pContextData = NULL;
    }

}

CPlayerEntity::~CPlayerEntity()
{
	// Is this not the localplayer?
	if(!IsLocalPlayer())
		Destroy();
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

void CPlayerEntity::Process()
{
	// Is the player spawned?
	if(IsSpawned() && 0 != 0) // disable current processing
	{
		// Check vehicle enter/exit
		//CheckVehicleEnterExit();

		// Process vehicle enter/exit
		//ProcessVehicleEnterExit();

		// Is this the localplayer?
		if(IsLocalPlayer())
		{
			// Copy the current control state to the previous control state
			memcpy(&m_lastControlState, &m_ControlState, sizeof(CControls));

			// Update the current control state
			g_pCore->GetGame()->GetPad()->GetCurrentControlState(m_ControlState);

			// Are we on-foot?
			if(IsOnFoot())
			{
				// Send on foot sync data
				Serialize(RPC_PACKAGE_TYPE_PLAYER_ONFOOT);
			}
			else
			{
				// Are we the vehicle driver?
				if(!IsPassenger())
				{
					// Send in vehicle data
					Serialize(RPC_PACKAGE_TYPE_PLAYER_VEHICLE);
				}
				else
				{
					// Send passenger data
					Serialize(RPC_PACKAGE_TYPE_PLAYER_PASSENGER);
				}
			}
		}
	}

	CNetworkEntity::Pulse();
}

bool CPlayerEntity::Create()
{
	// Is this the localplayer or are we alread spawned?
	if(IsLocalPlayer() && IsSpawned())
		return false;

	// Find a free player number
	m_bytePlayerNumber = (BYTE)CPools::FindFreePlayerInfoIndex();

	// Invalid player number?
	if(m_bytePlayerNumber == INVALID_PLAYER_PED)
		return false;

	// Add our model reference and load the model
	m_pModelInfo->AddReference(true);

	// Get the model index
	int iModelIndex = m_pModelInfo->GetIndex();

	// Create the player info instance
	m_pPlayerInfo = new CIVPlayerInfo(m_bytePlayerNumber);

	// Create our context data
	m_pContextData = CContextDataManager::CreateContextData(m_pPlayerInfo);

	// Allocate the player ped
	IVPlayerPed * pPlayerPed = (IVPlayerPed *)g_pCore->GetGame()->GetPools()->GetPedPool()->Allocate();

	CLogFile::Printf("m_bytePlayerNumber: %d, m_pPlayerInfo: 0x%p, pPlayerPed: 0x%p", m_bytePlayerNumber, m_pPlayerInfo, pPlayerPed);

	// Ensure the ped was allocated
	if(!pPlayerPed)
		return false;

	// Create the ped
	DWORD dwFunc = (g_pCore->GetBase() + 0x9C1910);
	unsigned int uiPlayerIndex = (unsigned int)m_bytePlayerNumber;
	WORD wPlayerData = MAKEWORD(0, 1);
	WORD * pwPlayerData = &wPlayerData;

	_asm push uiPlayerIndex;
	_asm push iModelIndex;
	_asm push pwPlayerData;
	_asm mov ecx, pPlayerPed;
	_asm call dwFunc;

	// Setup the ped
	dwFunc = (g_pCore->GetBase() + 0x43A6A0);
	DWORD dwPedFactory = (g_pCore->GetBase() + 0x15E35A0);
	Matrix34 * pMatrix = NULL;

	_asm push iModelIndex;
	_asm push dwPedFactory;
	_asm mov edi, pMatrix;
	_asm mov esi, pPlayerPed;
	_asm call dwFunc;

	// Setup ped intelligence
	*(DWORD *)(pPlayerPed + 0x260) |= 1u;
	dwFunc = (g_pCore->GetBase() + 0x89EC20);

	_asm push 2;
	_asm mov ecx, pPlayerPed;
	_asm call dwFunc;

	// Set the player info
	m_pPlayerInfo->SetPlayerPed(pPlayerPed);

	// Set our player info with the ped
	pPlayerPed->m_pPlayerInfo = m_pPlayerInfo->GetPlayerInfo();

	// Set the game player info pointer
	CPools::SetPlayerInfoAtIndex((unsigned int)m_bytePlayerNumber, m_pPlayerInfo->GetPlayerInfo());

	// Create the player ped instance
	m_pPlayerPed = new CIVPlayerPed(pPlayerPed);

	// Set the context data player ped pointer
	m_pContextData->SetPlayerPed(m_pPlayerPed);

	// Add to the world
	m_pPlayerPed->AddToWorld();

	// Create the player blip
	CIVScript::ChangeBlipNameFromAscii(m_uiBlip, "Im_BATMAN");

	// Set the player internal name
	CIVScript_NativeInvoke::Invoke< unsigned int >(CIVScript::NATIVE_GIVE_PED_FAKE_NETWORK_NAME, GetScriptingHandle(), GetNick().Get(), 255, 255, 255, 255);

	// Temp
	CIVScript_NativeInvoke::Invoke< unsigned int >(CIVScript::NATIVE_SET_CHAR_INVINCIBLE, GetScriptingHandle(), true);

	// Mark as spawned
	Spawn();

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
	DWORD dwFunc = (g_pCore->GetBase() + 0x9C4DF0);
	IVPedIntelligence * pPedIntelligence = pPlayerPed->m_pPedIntelligence;

	_asm push 0;
	_asm mov ecx, pPedIntelligence;
	_asm call dwFunc;

	*(DWORD *)(pPlayerPed + 0x260) &= 0xFFFFFFFE;

	// Remove the ped from the world
	m_pPlayerPed->RemoveFromWorld();

	// Delete the player ped
	dwFunc = (g_pCore->GetBase() + 0x8ACAC0);

	_asm push 1;
	_asm mov ecx, pPlayerPed;
	_asm call dwFunc;

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
		CPools::SetPlayerInfoAtIndex((unsigned int)m_bytePlayerNumber, NULL);

		// Invalidate the player number
		m_bytePlayerNumber = INVALID_PLAYER_PED;
	}

	// Mark as not spawned
	m_bSpawned = false;

	// Remove the blip
	CIVScript::RemoveBlip(m_uiBlip);

	return true;
}

void CPlayerEntity::SetPosition(CVector3 vecPosition)
{
	if(IsSpawned())
		m_pPlayerPed->SetPosition(vecPosition);
	else
		m_vecPosition = vecPosition;

	CNetworkEntity::SetPosition(vecPosition);
}

bool CPlayerEntity::GetPosition(CVector3 *vecPosition)
{
	if(IsSpawned())
		m_pPlayerPed->GetPosition(vecPosition);
	else
		vecPosition = &m_vecPosition;

	return true;
}

void CPlayerEntity::Teleport(CVector3 vecPosition)
{
	CIVScript::SetCharCoordinatesNoOffset(GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ);

	// Set position for varible.
	m_vecPosition = m_vecPosition;
	CNetworkEntity::SetPosition(vecPosition);
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
	m_pPlayerPed->SetHealth(fHealth);
}

float CPlayerEntity::GetHealth()
{
	return (m_pPlayerPed->GetHealth());
}

void CPlayerEntity::SetRotation(float fAngle)
{
	IVPed * pPed = m_pPlayerPed->GetPed();

	if(pPed)
		pPed->m_fCurrentHeading = fAngle;
}

float CPlayerEntity::GetRotation()
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
         
    // Get the model index
    int iModelIndex = CIVModelManager::GetModelIndexFromHash(dwModelHash);

    // Get the model info
    CIVModelInfo * pModelInfo = g_pCore->GetGame()->GetModelInfo(iModelIndex);

    // Add reference
    pModelInfo->AddReference(true);

    // change the model from the player
    CIVScript::ChangePlayerModel(GetScriptingHandle(),(CIVScript::eModel)dwModelHash);
  
	// remove from world
	m_pPlayerPed->RemoveFromWorld();

    // set the new ped
    m_pPlayerPed->SetPed(m_pPlayerInfo->GetPlayerPed());

	// re add to world
    m_pPlayerPed->AddToWorld();
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
		return (m_pPlayerPed->IsInVehicle() && m_pPlayerPed->GetCurrentVehicle());
	
	return false;
}

CVehicleEntity * CPlayerEntity::InternalGetVehicle()
{
	
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
	m_vehicleEnterExit.bEntering = true;
	m_vehicleEnterExit.pVehicle = pVehicle;
	m_vehicleEnterExit.byteSeat = byteSeat;
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
	m_vehicleEnterExit.bExiting = true;
}

void CPlayerEntity::CheckVehicleEnterExit()
{
	// Are we spawned?
	if(IsSpawned())
	{
		// Are we not in a vehicle?
		if(!InternalIsInVehicle())
		{
			// Has the enter/exit vehicle key been pressed?
			if(m_lastControlState.IsUsingEnterExitVehicle() || m_lastControlState.IsUsingHorn())
			{
				// Are we not already requesting an enter?
				if(!m_vehicleEnterExit.bEntering)
				{
					CVehicleEntity * pVehicle = NULL;
					BYTE byteSeat = 0;
					bool bFound = GetClosestVehicle(m_lastControlState.IsUsingHorn(), &pVehicle, byteSeat);

					// Have we found a vehicle?
					if(bFound)
					{
						// Enter the vehicle
						EnterVehicle(pVehicle, byteSeat);

						g_pCore->GetChat()->Outputf(false, "HandleVehicleEntry(%d, %d)", pVehicle->GetId(), byteSeat);
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
				if(!m_vehicleEnterExit.bExiting)
				{
					// Exit the vehicle
					ExitVehicle(EXIT_VEHICLE_NORMAL);

					g_pCore->GetChat()->Outputf(false, "HandleVehicleExit(%d, %d)", m_pVehicle->GetId(), m_byteSeat);
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
		GetPosition(&vecPosition);

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
			if(m_vehicleEnterExit.bEntering)
			{
				// Has the enter vehicle task finished?
				if(!IsGettingIntoAVehicle())
				{
					// Vehicle entry is complete
					m_vehicleEnterExit.pVehicle->SetOccupant(m_vehicleEnterExit.byteSeat, this);

					// Store the vehicle
					m_pVehicle = m_vehicleEnterExit.pVehicle;

					// Store the seat
					m_byteSeat = m_vehicleEnterExit.byteSeat;

					// Reset vehicle enter/exit
					ResetVehicleEnterExit();

					// Send to the server
					CBitStream bitStream;
					bitStream.WriteCompressed(m_pVehicle->GetId());
					bitStream.Write(m_byteSeat);

					//g_pClient->GetChat()->Output("VehicleEntryComplete()");
				}
			}
		}
		else
		{
			// Are we flagged as exiting?
			if(m_vehicleEnterExit.bExiting)
			{
				// Has the exit vehicle task finished?
				if(!IsGettingOutOfAVehicle())
				{
					// Send to the server
					CBitStream bitStream;
					bitStream.WriteCompressed(m_pVehicle->GetId());
					bitStream.Write(m_byteSeat);

					// Vehicle exit is complete
					m_pVehicle->SetOccupant(m_byteSeat, NULL);

					// Reset vehicle enter/exit
					ResetVehicleEnterExit();

					// Reset the vehicle
					m_pVehicle = NULL;

					// Reset the seat
					m_byteSeat = 0;

					//g_pClient->GetChat()->Output("VehicleExitComplete()");
				}
			}
		}
	}
}

void CPlayerEntity::ResetVehicleEnterExit()
{
	// Reset
	m_vehicleEnterExit.bEntering = false;
	m_vehicleEnterExit.pVehicle = NULL;
	m_vehicleEnterExit.byteSeat = 0;
	m_vehicleEnterExit.bExiting = false;
	m_vehicleEnterExit.bRequesting = false;

	// Clear the vehicle entry task
	//ClearVehicleEntryTask();

	// Clear the vehicle exit task
	//ClearVehicleExitTask();
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