////================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CPickupEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CPickupEntity_h
#define CPickupEntity_h

#include "CNetworkEntity.h"

class CPickupEntity : public CNetworkEntity {
private:

public:
	CPickupEntity();
	~CPickupEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

#endif // CPickupEntity_h