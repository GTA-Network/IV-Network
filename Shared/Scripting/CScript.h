//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScript.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScript_h
#define CScript_h

#include <Common.h>

enum eScriptType {
	CLIENT_SCRIPT,
	SERVER_SCRIPT,
	SHARED_SCRIPT,
};

class CScript {
private:
	eScriptType		m_ScriptType;
	CString			m_strScriptFileName;
public:
	CScript();
	~CScript();

	eScriptType		GetType() { return m_ScriptType; }

	CString			GetScriptFileName() { return m_strScriptFileName; }
};

#endif // CScript_h