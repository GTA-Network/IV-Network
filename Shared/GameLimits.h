//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: GameLimits.h
// Project: (Shared)
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef GameLimits_h
#define GameLimits_h

#define MAX_PLAYERS 32/*128*/ // Player Info Array Size: 32 // Ped Pool Size: ~200
#define MAX_VEHICLES 140 // Streamed. See note on Pickups. Vehicle Pool Size: 140
#define MAX_OBJECTS 0x1000 // Streamed. See note on Pickups. Object Pool Size: 1300
#define MAX_CHECKPOINTS 0x1000 // Streamed. Checkpoint Pool Size: See CStreamer.h
#define MAX_BLIPS 1300 // Blip Pool Size: 1500
#define MAX_PICKUPS 0x1000 // Streamed. Pickup Pool Size: TODO: 1500?
#define MAX_FIRE 32
#define MAX_ACTORS 85
#define MAX_3D_LABELS 512
#define MAX_TRAINS 254

#define MAX_STREAMED_VEHICLES 500
#define MAX_STREAMED_PICKUPS 128
#define MAX_STREAMED_OBJECTS 512
#define MAX_STREAMED_CHECKPOINTS 64
#define MAX_STREAMED_PLAYERS 32
#define MAX_STREAMED_LABELS MAX_3D_LABELS
#define MAX_STREAMED_ACTORS 85

// Max amount of characters a player can use in their name
#define MAX_NAME_LENGTH 18

// Max vehicle passengers (NOTE: This is also a GTA limit)
#define MAX_VEHICLE_PASSENGERS 8

// Type used for entity ids
typedef unsigned short EntityId;

// Type used for dimension ids
typedef unsigned char DimensionId;

// Define used for invalid dimension ids
#define INVALID_DIMENSION_ID (DimensionId)0xFF

#endif // GameLimits_h