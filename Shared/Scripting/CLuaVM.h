//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
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

	eVMType GetVMType() { return LUA_VM; }
	lua_State*		GetVM() { return m_pVM; }

	bool LoadScript(CString script);		// Replace string with script
	bool LoadScripts(std::list<CScript> scripts);

	void Pop(bool& b);
	void Pop(int& i);
	void Pop(unsigned int& i);
	void Pop(long& i);
	void Pop(unsigned long& i);
	void Pop(float& f);
	void Pop(CString& str);
	void Pop(CVector3& vec);

	void Pop(bool& b, bool bDefaultValue);
	void Pop(int& i, int iDefaultValue);
	void Pop(unsigned int& i, unsigned int iDefaultValue);
	void Pop(long& i, long iDefaultValue);
	void Pop(unsigned long& i, unsigned long iDefaultValue);
	void Pop(float& f, float fDefaultValue);
	void Pop(stScriptFunction& function);
	void Pop(CString& str, CString strDefaultValue);
	void Pop(CVector3& vec, CVector3 vecDefaultValue);
	void PopTable(CScriptArguments &table) {}

	void Push(const bool& b);
	void Push(const int& i);
	void Push(const unsigned int& i);
	void Push(const long& i);
	void Push(const unsigned long& i);
	void Push(const float& f);
	void Push(const CString& str);
	void Push(const CVector3& vec);
	void PushArray(const CScriptArguments &array);
	void PushTable(const CScriptArguments &table);

	CScriptArgument::ArgumentType GetType(int idx);

	void		 SetStackIndex(int iStackIndex) { m_iStackIndex = iStackIndex; }
	void		 ResetStackIndex() { m_iStackIndex = 1; }

	int			 GetArgumentCount() { return lua_gettop(m_pVM); }
	void		 Call(stScriptFunction, CScriptArguments * pArgument = 0) { }

	void		 RegisterScriptClass(const char* className, scriptFunction pfnFunction, void* userPointer = 0, const char* baseClass = 0);
	void		 RegisterClassFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL);
	void		 FinishRegisterScriptClass();
	void		*GetUserData(int idx);

	void		 SetClassInstance(const char* szClassName, void * pInstance);
	void		*GetClassInstance(const char* szClassName);
	void		 PushInstance(const char* szClassName, void * pInstance) { }
	void		 RegisterFunction(const char* szFunctionName, scriptFunction pfnFunction, int iParameterCount = -1, const char* szFunctionTemplate = NULL, bool bPushRootTable = false);
};

#endif // CLuaVM_h