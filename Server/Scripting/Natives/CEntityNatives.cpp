//============== IV: Multiplayer - http://code.iv-multiplayer.com ==============
//
// File: CEntityNatives.cpp
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#include "CEntityNatives.h"
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>

#include "../../Entity/Entities.h"

void CEntityNatives::Register(CScriptVM* pVM)
{
	pVM->RegisterClassFunction("setPosition", SetPosition);
	pVM->RegisterClassFunction("getPosition", GetPosition);

	pVM->RegisterClassFunction("setRotation", SetRotation);
	pVM->RegisterClassFunction("getRotation", GetRotation);

	pVM->RegisterClassFunction("setMoveSpeed", SetMoveSpeed);
	pVM->RegisterClassFunction("getMoveSpeed", GetMoveSpeed);

	pVM->RegisterClassFunction("setTurnSpeed", SetTurnSpeed);
	pVM->RegisterClassFunction("getTurnSpeed", GetTurnSpeed);

	pVM->RegisterClassFunction("destroy", Destroy);
}


int	CEntityNatives::SetPosition(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;
		
	CVector3 vecPos;
	pVM->Pop(vecPos);
	pEntity->SetPosition(vecPos);
	pVM->ResetStackIndex();
	
	return 1;
}

int	CEntityNatives::GetPosition(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;

	CVector3 vecPosition;
	pEntity->GetPosition(vecPosition);

	CScriptArguments arg;
	arg.pushVector3(vecPosition);
	pVM->PushArray(arg);
	return 1;
}


int	CEntityNatives::SetRotation(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;

	CVector3 vecRot;
	pVM->Pop(vecRot);
	pEntity->SetRotation(vecRot);
	pVM->ResetStackIndex();
	return 1;
}

int	CEntityNatives::GetRotation(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;

	CVector3 vecRotation;
	pEntity->GetRotation(vecRotation);

	CScriptArguments arg;
	arg.pushVector3(vecRotation);
	pVM->PushArray(arg);
	return 1;
}


int	CEntityNatives::SetMoveSpeed(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;

	CVector3 vecMoveSpeed;
	pVM->Pop(vecMoveSpeed);
	pEntity->SetMoveSpeed(vecMoveSpeed);
	pVM->ResetStackIndex();
	return 1;
}

int	CEntityNatives::GetMoveSpeed(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;

	CVector3 vecMoveSpeed;
	pEntity->GetMoveSpeed(vecMoveSpeed);

	CScriptArguments arg;
	arg.pushVector3(vecMoveSpeed);
	pVM->PushArray(arg);
	return 1;
}


int	CEntityNatives::SetTurnSpeed(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;

	CVector3 vecTurnSpeed;
	pVM->Pop(vecTurnSpeed);
	pEntity->SetMoveSpeed(vecTurnSpeed);
	pVM->ResetStackIndex();
	return 1;
}

int	CEntityNatives::GetTurnSpeed(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	GET_ENTITY_SAFE;

	CVector3 vecTurnSpeed;
	pEntity->GetTurnSpeed(vecTurnSpeed);

	CScriptArguments arg;
	arg.pushVector3(vecTurnSpeed);
	pVM->PushArray(arg);
	return 1;
}

int CEntityNatives::Destroy(int * VM)
{
	return 1;
}