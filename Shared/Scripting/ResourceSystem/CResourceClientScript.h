//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CResourceClientScript.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CResourceClientScript_h
#define CResourceClientScript_h

#include "CResourceScriptFile.h"

class CResource;

class CResourceClientScript : public CResourceScriptFile {

private:

public:
	CResourceClientScript(CResource * resource, const char * szShortName, const char * szResourceFileName);
	~CResourceClientScript();

	bool	Start();
	bool	Stop();
};

#endif // CResourceClientScript_h