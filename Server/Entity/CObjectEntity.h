////================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CObjectEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CObjectEntity_h
#define CObjectEntity_h

#include "CNetworkEntity.h"

class CObjectEntity : public CNetworkEntity {
private:

public:
	CObjectEntity();
	~CObjectEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

#endif // CObjectEntity_h