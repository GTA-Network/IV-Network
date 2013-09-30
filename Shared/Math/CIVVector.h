//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVVector.h
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
	CVECTOR	bodyHeading;		// 0x0 | 0
	CVECTOR	visionHeading;		// 0x10 | 16
	CVECTOR	unkVector;			// 0x20 | 32
	CVECTOR	position;			// 0x30 | 48
};

#endif // CIVVector_h