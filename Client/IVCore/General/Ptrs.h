//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: Ptrs.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef Ptrs_h
#define Ptrs_h

#include <Common.h>
#include <Game/COffsets.h>
#include <CCore.h>
extern CCore * g_pCore;

#define PTR_CHAT g_pCore->GetChat()
#define PTR_LOCALPLAYER g_pCore->GetGame()->GetLocalPlayer()

#endif // Ptrs_h