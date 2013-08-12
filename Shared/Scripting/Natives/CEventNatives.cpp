//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
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

// Helper macro creates a pVM from unknown vm given by the native
#define GET_VM_UNKNOWN CResource* pResource = CResourceManager::GetInstance()->Get(VM); \
					   if(!pResource) \
					       return 1; \
					   CScriptVM * pVM = pResource->GetVM();

#define DEPRECATED(x) CLogFile::Printf("%s is deprecated", x);
#define NOT_IMPLEMENTED(x) CLogFile::Printf("%s is yet not implemented", x);

void CEventNatives::Register(CScriptVM * pVM)
{
	pVM->RegisterFunction("addEvent", AddEvent);
	pVM->RegisterFunction("addGlobalEvent", AddGlobalEvent);
	pVM->RegisterFunction("addRemoteEvent", AddRemoteEvent);

	pVM->RegisterFunction("triggerEvent", TriggerEvent);
	pVM->RegisterFunction("triggerGlobalEvent", TriggerGlobalEvent);
	pVM->RegisterFunction("triggerRemoteEvent", TriggerRemoteEvent);

	CLogFile::Printf(__FUNCTION__);
}

int CEventNatives::AddEvent(int * VM)
{
	GET_VM_UNKNOWN
	NOT_IMPLEMENTED("addEvent");
	return 0;
}

int CEventNatives::AddGlobalEvent(int * VM)
{
	GET_VM_UNKNOWN
	NOT_IMPLEMENTED("addGlobalEvent");
	return 0;
}

int CEventNatives::AddRemoteEvent(int * VM)
{
	GET_VM_UNKNOWN
	NOT_IMPLEMENTED("addRemoteEvent");
	return 0;
}

int CEventNatives::TriggerEvent(int * VM)
{
	GET_VM_UNKNOWN
	NOT_IMPLEMENTED("triggerEvent");
	return 0;
}

int CEventNatives::TriggerGlobalEvent(int * VM)
{
	GET_VM_UNKNOWN
	NOT_IMPLEMENTED("triggerGlobalEvent");
	return 0;
}

int CEventNatives::TriggerRemoteEvent(int * VM)
{
	GET_VM_UNKNOWN
	NOT_IMPLEMENTED("triggerRemoteEvent");
	return 0;
}