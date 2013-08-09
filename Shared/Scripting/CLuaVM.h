//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CLuaVM.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CLuaVM_h
#define CLuaVM_h

#include <lua/lua.hpp>
#include "CScriptVM.h"


class CLuaVM : public CScriptVM {

private:
	lua_State* m_pVM;
	int m_iStackIndex;
public:
	CLuaVM(CResource* pResource);
	~CLuaVM();

	virtual eVMType GetVMType() { return LUA_VM; }
	lua_State*		GetVM() { return m_pVM; }

	virtual bool LoadScript(CString script);		// Replace string with script
	virtual bool LoadScripts(std::list<CScript> scripts);

	virtual void PopBool(bool& b);
	virtual void PopInteger(int& i);
	virtual void PopFloat(float& f);
	virtual void PopString(CString& str);
	virtual void PopVector(CVector3& vec);

	virtual void PopBool(bool& b, bool bDefaultValue);
	virtual void PopInteger(int& i, int iDefaultValue);
	virtual void PopFloat(float& f, float fDefaultValue);
	virtual void PopString(CString& str, CString strDefaultValue);
	virtual void PopVector(CVector3& vec, CVector3 vecDefaultValue);

	virtual void PushBool(const bool& b);
	virtual void PushInteger(const int& i);
	virtual void PushFloat(const float& f);
	virtual void PushString(const CString& str);
	virtual void PushVector(const CVector3& vec);

	void ResetStackIndex() { m_iStackIndex = 0; }

	void RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false);
};

#endif // CLuaVM_h