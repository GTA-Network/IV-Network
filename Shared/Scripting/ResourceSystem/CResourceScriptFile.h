//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CResourceScriptFile.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResourceScriptFile_h
#define CResourceScriptFile_h

#include "CResourceFile.h"

class CResource;

class CResourceScriptFile : public CResourceFile {

private:

public:
	CResourceScriptFile(CResource * resource, const char * szShortName, const char * szResourceFileName);
	~CResourceScriptFile();

	virtual bool	Start() = 0;
	virtual bool	Stop() = 0;
};

#endif // CResourceScriptFile_h