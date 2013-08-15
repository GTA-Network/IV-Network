//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CVehicleEntity.h
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CVehicleEntity_h
#define CVehicleEntity_h

#include "CNetworkEntity.h"

class CVehicleEntity : public CNetworkEntity
{
private:

public:
	CVehicleEntity();
	~CVehicleEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

#endif // CVehicleEntity_h