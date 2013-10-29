//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: NetCommon.h
// Project: Network.Core
// Author: CrackHD
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef NetCommon_h
#define NetCommon_h

#include <Common.h>

//#ifdef _CLIENT
#include <RakNet/RakPeerInterface.h>
#include <RakNet/BitStream.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/RPC4Plugin.h>
#include <RakNet/DirectoryDeltaTransfer.h>
#include <RakNet/FileListTransfer.h>
#include <RakNet/IncrementalReadInterface.h>
using namespace RakNet;
//#endif

#include <Network/PacketIdentifiers.h>
#include <Network/RPCIdentifiers.h>
#include <Network/CBitStream.h>
#include <Math/CVector3.h>

// Macro
#define PEER_IS_STARTED(res) (res == RakNet::RAKNET_STARTED || res == RakNet::RAKNET_ALREADY_STARTED)

#endif // NetCommon_h