//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CEFLCSupport.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEFLCSupport_h
#define CEFLCSupport_h

enum eEFLCStruct {
	TBOGT_PAD_DAT_HANDLING = 0x1, 
	TBOGT_PAD_IDE_VEHICLE = 0x2,
	TBOGT_PAD_TXT_IMAGES = 0x3,
	TBOGT_PAD_TXT_CJIMAGES = 0x4,
	TBOGT_PAD_DAT_CARCOLS = 0x5,
	TBOGT_PAD_DAT_CARGRP = 0x6,
	TBOGT_PAD_DAT_VEHICLEEXTRAS = 0x7,
	TBOGT_PAD_CSV_VEHOFF = 0x8,
	DEFAULT_FILE_HOOK = 0x9,
	TBOGT_PAD_PAD_DAT = 0xA,
	TBOGT_PAD_PAD_DAT_2 = 0xB,
	TBOGT_PAD_XML_WEAPONS = 0xC,
	TBOGT_PAD_IDE_WEAPONS = 0xD,
	TBOGT_PAD_XML_RPC = 0xE,
	TBOGT_PAD_EXTRA_MAP = 0xF,
};

class CEFLCSupport {
private:
	static bool		m_bVehicles;
	inline void		InstallVehicles()
	{
		m_bVehicles = true;
	}

	static bool		m_bPeds;
	static void		InstallPeds()
	{
		m_bPeds = true;
	}

	static bool		m_bWeapons;
	static void		InstallWeapons()
	{
		m_bWeapons = true;
	}

	static bool		m_bMaps;
	static void		InstallMaps()
	{
		m_bMaps = true;
	}

	static bool		m_bParachute;
	static void		InstallParachute()
	{
		m_bParachute = true;
	}

public:
	static void		SpecificSupport(bool bVehicles, bool bPeds, bool bWeapons, bool bMaps, bool bParachute)
	{
		m_bVehicles = bVehicles;
		m_bPeds = bPeds;
		m_bWeapons = bWeapons;
		m_bMaps = bMaps;
		m_bParachute = bParachute;
	}

	static void		InstallSupport();
	static bool		OpenFile_Decision(char* j);

	static void		InstallPreGameLoad();
};

#endif // CEFLCSupport_h