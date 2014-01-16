/*
* Copyright C GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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