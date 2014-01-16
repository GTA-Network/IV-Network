/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CEventHandler_h
#define CEventHandler_h

#include <Common.h>
#include <CLogFile.h>
#include <assert.h>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqstate.h>
#include <Squirrel/sqvm.h>
#include <Squirrel/sqstring.h>
#include "CScriptArguments.h"
#include "CSquirrelVM.h"
#include "CLuaVM.h"

class CEventHandler {
public:
	enum eEventType {
		RESOURCE_EVENT,
		GLOBAL_EVENT,
		REMOTE_EVENT,
		NATIVE_EVENT,
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
	~CEventHandler()
	{

	}
	
	virtual CScriptVM* GetVM() { return m_pVM; }

	SQObjectPtr GetFunction() { return m_func; }
	int GetRef() { return m_iRef; }

	eEventType GetType() { return m_EventType; }
	void Call(CScriptArguments* pArguments, CScriptArgument * pReturn = 0)
	{
		if(m_pVM->GetVMType() == LUA_VM)
		{
			// TODO: push arguments
			CLogFile::Printf("[TODO] Push arguments [%s | %i]", __FILE__, __LINE__);
			lua_rawgeti(((CLuaVM*)m_pVM)->GetVM(), LUA_REGISTRYINDEX, m_iRef);
			lua_pcall(((CLuaVM*)m_pVM)->GetVM(), 0, LUA_MULTRET, NULL);
			lua_settop(((CLuaVM*)m_pVM)->GetVM(), 0);
		} else {
			SQObjectPtr res;
			int iTop = sq_gettop(((CSquirrelVM*)m_pVM)->GetVM());
			if (pArguments)
			{
				for (auto it : pArguments->m_Arguments)
				{
					it->Push(m_pVM);
				}

				if (((CSquirrelVM*) m_pVM)->GetVM()->Call(m_func, pArguments->m_Arguments.size() + 1, ((CSquirrelVM*) m_pVM)->GetVM()->_top - (pArguments->m_Arguments.size() + 1), res, true))
				{
					if (pReturn)
					{
						switch (res._type)
						{
						case OT_FLOAT:
							{
								pReturn->set(CScriptArgument(res._unVal.fFloat));
									 }
							break;
						case OT_INTEGER:
							{
								pReturn->set(CScriptArgument(res._unVal.nInteger));
									   }
							break;
						case OT_BOOL:
							{
								pReturn->set(CScriptArgument(res._unVal.nInteger != 0));
									}
							break;
						case OT_STRING:
							{
								pReturn->set(CScriptArgument(CString(res._unVal.pString->_val)));
									  }
							break;
						}
					}
				}
			}
			else
			{
				if (((CSquirrelVM*) m_pVM)->GetVM()->Call(m_func, 1, ((CSquirrelVM*) m_pVM)->GetVM()->_top - 1, res, true))
				{
					if (pReturn)
					{
						switch (res._type)
						{
						case OT_FLOAT:
							{
								pReturn->set(CScriptArgument(res._unVal.fFloat));
							}
							break;
						case OT_INTEGER:
							{
								pReturn->set(CScriptArgument(res._unVal.nInteger));
							}
							break;
						case OT_BOOL:
							{
								pReturn->set(CScriptArgument(res._unVal.nInteger != 0));
							}
							break;
						case OT_STRING:
							{
								pReturn->set(CScriptArgument(CString(res._unVal.pString->_val)));
							}
							break;
						}
					}
				}
			}
			
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