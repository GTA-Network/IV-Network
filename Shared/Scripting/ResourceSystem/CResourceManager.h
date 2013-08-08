//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResourceManager.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResourceManager_h
#define CResourceManager_h

#include "CResource.h"
#include "../CLuaVM.h"

class CResourceManager {

private:
	std::list<CResource*> m_resources;
public:
	CResourceManager();
	~CResourceManager();

	CResource * Get(int * pVM);
};

#endif // CResourceManager_h