//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CBlipEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CBlipEntity_h
#define CBlipEntity_h

#include "CNetworkEntity.h"

class CBlipEntity : public CNetworkEntity {
private:

public:
	CBlipEntity();
	~CBlipEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

#endif // CBlipEntity_h