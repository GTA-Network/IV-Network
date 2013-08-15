//================ IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ================
//
// File: C3DLabelEntity.h
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef C3DLabelEntity_h
#define C3DLabelEntity_h

#include "CNetworkEntity.h"

class C3DLabelEntity : public CNetworkEntity {
private:

public:
	C3DLabelEntity();
	~C3DLabelEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

#endif // C3DLabelEntity_h