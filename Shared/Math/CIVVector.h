//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: CMath.h
// Project: Shared
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CIVVector_h
#define CIVVector_h
struct CVECTOR
{
	float	x;	// 0x0 | 0
	float	y;	// 0x4 | 4
	float	z;	// 0x8 | 8
	float	unk;
};

struct CIVVector
{
	VECTOR	bodyHeading;		// 0x0 | 0
	VECTOR	visionHeading;		// 0x10 | 16
	VECTOR	unkVector;			// 0x20 | 32
	VECTOR	position;			// 0x30 | 48
};

#endif // CIVVector_h