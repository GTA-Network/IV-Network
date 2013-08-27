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
#include <Common.h>
#include "CScriptVM.h"

#include "CScriptArgument.h"

class CLuaVM : public CScriptVM {

private:
	lua_State* m_pVM;
	int m_iStackIndex;
	CString m_strClassName;
public:
	CLuaVM(CResource* pResource);
	~CLuaVM();

	virtual eVMType GetVMType() { return LUA_VM; }
	lua_State*		GetVM() { return m_pVM; }

	virtual bool LoadScript(CString script);		// Replace string with script
	virtual bool LoadScripts(std::list<CScript> scripts);

	virtual void Pop(bool& b);
	virtual void Pop(int& i);
	virtual void Pop(float& f);
	virtual void Pop(CString& str);
	virtual void Pop(CVector3& vec);

	virtual void Pop(bool& b, bool bDefaultValue);
	virtual void Pop(int& i, int iDefaultValue);
	virtual void Pop(float& f, float fDefaultValue);
	virtual void Pop(CString& str, CString strDefaultValue);
	virtual void Pop(CVector3& vec, CVector3 vecDefaultValue);

	virtual void Push(const bool& b);
	virtual void Push(const int& i);
	virtual void Push(const float& f);
	virtual void Push(const CString& str);
	virtual void Push(const CVector3& vec);
	virtual void PushArray(const CScriptArguments &array);
	virtual void PushTable(const CScriptArguments &table);

	virtual CScriptArgument::ArgumentType GetType(int idx);

	void		 SetStackIndex(int iStackIndex) { m_iStackIndex = iStackIndex; }
	void		 ResetStackIndex() { m_iStackIndex = 1; }

	int			 GetArgumentCount() { return lua_gettop(m_pVM); }

	virtual void RegisterScriptClass(const char* className, scriptFunction pfnFunction, const char* baseClass = 0);
	virtual void RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL);
	virtual void SetClassInstance(const char* szClassName, void * pInstance);
	void		*GetClassInstance(const char* szClassName);
	void		 RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false);
};

#endif // CLuaVM_h