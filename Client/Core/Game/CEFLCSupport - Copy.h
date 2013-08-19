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
	DEFAULT_FILE_HOOK = 0x9,
	TBOGT_PAD_DAT_HANDLING = 0x1, 
	TBOGT_PAD_IDE_VEHICLE = 0x2,
	TBOGT_PAD_TXT_IMAGES = 0x3,
	TBOGT_PAD_TXT_CJIMAGES = 0x4,
	TBOGT_PAD_DAT_CARCOLS = 0x5,
	TBOGT_PAD_DAT_CARGRP = 0x6,
	TBOGT_PAD_DAT_VEHICLEEXTRAS = 0x7,
	TBOGT_PAD_CSV_VEHOFF = 0x8,
};
class CEFLCSupport {

private:

public:
					CEFLCSupport();
					~CEFLCSupport();

	static void		InstallSupport();
};

#endif // CEFLCSupport_h