//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CNetSync.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CNetSync_h
#define CNetSync_h

enum ePackageType
{
	RPC_PACKAGE_TYPE_SMALL = 0x1,
	RPC_PACKAGE_TYPE_PLAYER_ONFOOT = 0x21,
	RPC_PACKAGE_TYPE_PLAYER_VEHICLE = 0x22,
	RPC_PACKAGE_TYPE_PLAYER_PASSENGER = 0x23,
	RPC_PACKAGE_TYPE_VEHICLE = 0x3,
	RPC_PACKAGE_TYPE_ACTOR = 0x4,
	RPC_PACKAGE_TYPE_OBJECT = 0x5
};

#endif // CNetSync_h