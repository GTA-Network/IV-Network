//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CDevelopment.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CDevelopment_h
#define CDevelopment_h

#include "Entity\CPlayerEntity.h"

class CDevelopment {
private:
	bool				bDebugView;
	bool				bDebugPlayerPresent;
	CPlayerEntity		*m_pDebugPlayer;
	bool				bHasAimSyncData;
	bool				m_bStoreOnFootSwitch;
	int					m_iOldMoveStyle;
public:
						CDevelopment();
						~CDevelopment();

	void				Process();
	void				SetDebugView(bool bView) { bDebugView = bView; }
	bool				GetDebugView() { return bDebugView; }

	void				CreateDebugPlayer();
};

#endif // CDevelopment_h