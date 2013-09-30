//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CCheckpointEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CCheckpointEntity_h
#define CCheckpointEntity_h

#include "CNetworkEntity.h"

class CCheckpointEntity : public CNetworkEntity {
private:

public:
	CCheckpointEntity();
	~CCheckpointEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

#endif // CCheckpointEntity_h