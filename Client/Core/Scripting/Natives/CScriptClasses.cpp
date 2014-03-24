//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CScriptClasses.cpp
// Project: Client.Core
// Authors: xForce <xf0rc3.11@gmail.com>, g3o0or
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptClasses.h"
#include <Game/EFLC/CScript.h>
#include <CCore.h>
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include "Scripting/Natives/Natives_Client.h"

extern CCore * g_pCore;

int SendMessage(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString sMessage;
	DWORD dwColor;
	bool bAllowFormatting;
	
	pVM->Pop(sMessage);
	pVM->Pop(dwColor);
	pVM->Pop(bAllowFormatting);
	
	g_pCore->GetGraphics()->GetChat()->Print(CString("#%s%s", CString::DecimalToString(dwColor).Get(), sMessage.C_String()));
	return 1;
}

int GetLocalPlayer(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	pVM->PushInstance("CPlayerEntity", g_pCore->GetGame()->GetLocalPlayer());
	return 1;
}

int TriggerServerEvent(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString eventName;

	pVM->Pop(eventName);

	RakNet::BitStream bitStream;
	bitStream.Write(eventName);
	g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_ENTER_VEHICLE), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);
	return 1;
}

void CScriptClasses::Register(IScriptVM * pVM)
{
	pVM->RegisterFunction("getLocalPlayer", GetLocalPlayer);
	pVM->RegisterFunction("sendMessage", SendMessage);
	pVM->RegisterFunction("triggerServerEvent", TriggerServerEvent);
}
