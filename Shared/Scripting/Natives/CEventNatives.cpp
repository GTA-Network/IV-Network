//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CEventNatives.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CEventNatives.h"
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include <Scripting/CEvents.h>
#include <Squirrel/squirrel.h>
#include <Squirrel/sqstate.h>
#include <Squirrel/sqvm.h>

// Helper macro creates a pVM from unknown vm given by the native
#define GET_VM_UNKNOWN CResource* pResource = CResourceManager::GetInstance()->Get(VM); \
					   if(!pResource) \
					       return 1; \
					   IScriptVM * pVM = pResource->GetVM();

#define DEPRECATED(x) CLogFile::Printf("%s is deprecated", x);
#define NOT_IMPLEMENTED(x) CLogFile::Printf("%s is not implemented", x);

void CEventNatives::Register(IScriptVM * pVM)
{
	pVM->RegisterFunction("addEvent", AddEvent);	
	pVM->RegisterFunction("addGlobalEvent", AddGlobalEvent);
	pVM->RegisterFunction("addRemoteEvent", AddRemoteEvent);

	pVM->RegisterFunction("triggerEvent", TriggerEvent);
	pVM->RegisterFunction("triggerGlobalEvent", TriggerGlobalEvent);
	pVM->RegisterFunction("triggerRemoteEvent", TriggerRemoteEvent);
	
	pVM->RegisterFunction("addCommandHandler", AddCommandHandler);
}

int CEventNatives::AddEvent(int * VM)
{
	GET_VM_UNKNOWN;
	CString strName;
	pVM->ResetStackIndex();
	pVM->Pop(strName);
	int ref = -1;
	SQObjectPtr pFunction;
	if(pVM->GetVMType() == LUA_VM)
	{
		if(lua_isfunction((lua_State*)VM, 2))
		{
			ref = luaL_ref((lua_State*)VM, LUA_REGISTRYINDEX);
		}
	} else {
		
		pFunction = stack_get((SQVM*)VM, 3);
	}
	pVM->ResetStackIndex();
	CEventHandler * pEvent = new CEventHandler(pVM, ref, pFunction, CEventHandler::RESOURCE_EVENT);
	CEvents::GetInstance()->Add(strName, pEvent);

	return 0;
}

int CEventNatives::AddCommandHandler(int * VM)
{
	GET_VM_UNKNOWN;
	CString strName;
	pVM->ResetStackIndex();
	pVM->Pop(strName);
	int ref = -1;
	SQObjectPtr pFunction;
	if(pVM->GetVMType() == LUA_VM)
	{
		if(lua_isfunction((lua_State*)VM, 2))
		{
			ref = luaL_ref((lua_State*)VM, LUA_REGISTRYINDEX);
		}
	} else {
		
		pFunction = stack_get((SQVM*)VM, 3);
	}
	pVM->ResetStackIndex();
	
	strName.Format("CMD_%s", strName.C_String());
	CEventHandler * pEvent = new CEventHandler(pVM, ref, pFunction, CEventHandler::RESOURCE_EVENT);
	CEvents::GetInstance()->Add(strName, pEvent);
	
	return 0;
}

int CEventNatives::AddGlobalEvent(int * VM)
{
	GET_VM_UNKNOWN;
	
	CString strName;
	pVM->ResetStackIndex();
	pVM->Pop(strName);
	int ref = -1;
	SQObjectPtr pFunction;
	if(pVM->GetVMType() == LUA_VM)
	{
		if(lua_isfunction((lua_State*)VM, 2))
		{
			ref = luaL_ref((lua_State*)VM, LUA_REGISTRYINDEX);
		}
	} else {
		
		pFunction = stack_get((SQVM*)VM, 3);
	}
	pVM->ResetStackIndex();
	CEventHandler * pEvent = new CEventHandler(pVM, ref, pFunction, CEventHandler::GLOBAL_EVENT);
	CEvents::GetInstance()->Add(strName, pEvent);

	return 0;
}

int CEventNatives::AddRemoteEvent(int * VM)
{
	GET_VM_UNKNOWN;
	NOT_IMPLEMENTED("addRemoteEvent");
	return 0;
}

int CEventNatives::TriggerEvent(int * VM)
{
	GET_VM_UNKNOWN;

	CString strName;
	pVM->Pop(strName);
	pVM->ResetStackIndex();
	CEvents::GetInstance()->Call(strName, 0, CEventHandler::RESOURCE_EVENT, pVM);

	return 0;
}

int CEventNatives::TriggerGlobalEvent(int * VM)
{
	GET_VM_UNKNOWN;

	CString strName;
	pVM->Pop(strName);
	pVM->ResetStackIndex();
	CEvents::GetInstance()->Call(strName, 0, CEventHandler::GLOBAL_EVENT, 0);

	return 0;
}

int CEventNatives::TriggerRemoteEvent(int * VM)
{
	GET_VM_UNKNOWN;
	NOT_IMPLEMENTED("triggerRemoteEvent");
	return 0;
}