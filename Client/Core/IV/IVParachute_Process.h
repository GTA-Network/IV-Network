//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: IVParachute.h
// Project: Client.Core
// Author: FRi <FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef IVParachute_h
#define IVParachute_h

#include <Common.h>
#include <Math/CVector3.h>
#include <Math/CMaths.h>
#include <math.h>
#include <IV/CIVScript.h>

#define _USE_MATH_DEFINES

#define sqr(x) ((x)*(x)) 
#define SIN(x) (sin((x)*M_PI/180)) 
#define COS(x) (cos((x)*M_PI/180)) 
#define tan_d(x) (tan((x)*M_PI/180)) 
#define asin_d(x) (asin(x)*180/M_PI) 
#define acos_d(x) (acos(x)*180/M_PI) 
#define atan_d(x) (atan(x)*180/M_PI) 

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

extern CVector3 g_U9105[6];

class CIVParachuteProcess {
public:
	static void InitialiseParachuteLocal();
};

#endif // IVParachute_h