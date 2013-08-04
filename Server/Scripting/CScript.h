//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CScript.h
// Project: Client.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScript_h
#define CScript_h

#include <Common.h>

class CScript {

private:
	CString				m_strName;
	CString				m_strPath;
public:
	CScript();
	~CScript();

	virtual bool		Load(CString strName, CString strPath) = 0;
	virtual void		Unload() = 0;

	virtual bool		Execute() = 0;

	void				SetName(CString strName) { m_strName = strName; }
	void				SetPath(CString strPath) { m_strPath = strPath; }

	CString				GetName() { return m_strName; }
	CString				GetPath() { return m_strPath; }

	//virtual void		Call(CScriptingFunction*, CScriptingArguments * pArguments, CScriptingArgument * pReturn) = 0;
};

#endif // CScript_h