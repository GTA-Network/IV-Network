//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CFireEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CFireEntity_h
#define CFireEntity_h

#include "CNetworkEntity.h"

class CFireEntity : public CNetworkEntity {
private:

public:
	CFireEntity();
	~CFireEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

#endif // CFireEntity_h