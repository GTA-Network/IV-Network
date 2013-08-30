//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CCharacterManager.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CCharacterManager_h
#define CCharacterManager_h

#include <Common.h>

class CCharacterManager {
public:
    static DWORD VehicleIdToModelHash(int iModelId);
    static int ModelHashToVehicleId(DWORD dwModelHash);
};

#endif // CCharacterManager_h