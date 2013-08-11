//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResourceServerScript.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResourceServerScript_h
#define CResourceServerScript_h

#include "CResourceScriptFile.h"

class CResource;

class CResourceServerScript : public CResourceScriptFile {

private:

public:
	CResourceServerScript(CResource * resource, const char * szShortName, const char * szResourceFileName);
	~CResourceServerScript();

	bool	Start();
	bool	Stop();
};

#endif // CResourceServerScript_h