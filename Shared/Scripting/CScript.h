//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CScript.h
// Project: Shared
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScript_h
#define CScript_h

#include <Common.h>

enum eScriptType
{
	SERVER_SCRIPT,
	CLIENT_SCRIPT,
	SHARED_SCRIPT,
};

class CScript
{
private:
	eScriptType	m_eType;
	CString		m_strScriptFileName;
public:
	CScript();
	~CScript();

	eScriptType		GetType() { return m_eType; }
	void			SetType(eScriptType eType) { m_eType = eType; }

	CString			GetScriptFileName() { return m_strScriptFileName; }
	void			SetScriptFilename(const CString& strScriptFileName) { m_strScriptFileName = strScriptFileName; }
};

#endif // CScript_h