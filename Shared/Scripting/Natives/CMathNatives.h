//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CMathNatives.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>, ApocKalipsS <apockalipss@hotmail.fr>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CMathNatives_h
#define CMathNatives_h

#include <Scripting/CScriptVM.h>

class CMathNatives {

private:
	static int	GetDistanceBetweenPoints2D(int * pVM);
	static int	GetDistanceBetweenPoints3D(int * pVM);
	static int	IsPointInCircle(int * pVM);
	static int	IsPointInTube(int * pVM);
	static int	IsPointInBall(int * pVM);
	static int	IsPointInArea(int * pVM);
	static int	IsPointInCuboid(int * pVM);
	static int	IsPointInPolygon(int * pVM);
public:
	static void Register(CScriptVM* pVM);
};

#endif // CMathNatives_h