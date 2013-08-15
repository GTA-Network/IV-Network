//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CEvents.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEvents_h
#define CEvents_h

#include <Common.h>

class CEvents {

private:
	static CEvents* s_pInstance;
public:
	CEvents();
	~CEvents();


	bool Add(CString strName);


	static CEvents* GetInstance() { return s_pInstance; }
};

#endif // CEvents_h