//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CEventHandler.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEventHandler_h
#define CEventHandler_h

#include <Common.h>
#include <CLogFile.h>
#include <assert.h>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqstate.h>
#include <Squirrel/sqvm.h>
#include "CSquirrelVM.h"
#include "CLuaVM.h"
class CScriptArguments {
	
};

class CEventHandler {
public:
	enum eEventType {
		RESOURCE_EVENT,
		GLOBAL_EVENT,
		REMOTE_EVENT,
	};
private:
	CScriptVM * m_pVM;
	eEventType m_EventType;
	int m_iRef;
	SQObjectPtr m_func;
public:
	CEventHandler(CScriptVM * pVM, int ref, SQObjectPtr func, eEventType EventType = RESOURCE_EVENT)
	{
		m_pVM = pVM;
		m_EventType = EventType;
		m_iRef = ref;
		m_func = func;
	}
	~CEventHandler();
	
	virtual CScriptVM* GetVM() { return m_pVM; }

	SQObjectPtr GetFunction() { return m_func; }
	int GetRef() { return m_iRef; }

	eEventType GetType() { return m_EventType; }
	void Call(CScriptArguments* pArguments)
	{
		if(m_pVM->GetVMType() == LUA_VM)
		{
			lua_rawgeti(((CLuaVM*)m_pVM)->GetVM(), LUA_REGISTRYINDEX, m_iRef);
			lua_pcall(((CLuaVM*)m_pVM)->GetVM(), 0, LUA_MULTRET, NULL);
		} else {
			SQObjectPtr res;
			int iTop = sq_gettop(((CSquirrelVM*)m_pVM)->GetVM());
			((CSquirrelVM*)m_pVM)->GetVM()->Call(m_func, 1, ((CSquirrelVM*)m_pVM)->GetVM()->_top-1, res, true);
			sq_settop(((CSquirrelVM*)m_pVM)->GetVM(), iTop);
		}
	}

	bool equals(CEventHandler* other)
	{
		return (other->GetVM() 
			&& other->GetVM() == GetVM() 
			&& other->GetType() == GetType() 
			&& other->GetRef() == GetRef()
			&& other->GetFunction()._unVal.pClosure == GetFunction()._unVal.pClosure);
	}
};

#endif // CEventHandler_h