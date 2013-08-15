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
}


int	CEntityNatives::SetPosition(int * VM)
{
	CResource* pResource = CResourceManager::GetInstance()->Get(VM);
	
	if(pResource)
	{
		CScriptVM * pVM = pResource->GetVM();
		CNetworkEntity* pEntity = (CNetworkEntity*)pVM->GetClassInstance("");
		
		CVector3 vecPos;
		pVM->PopVector(vecPos);
		pEntity->SetPosition(vecPos);
		pVM->ResetStackIndex();
	}
	return 1;
}

int	CEntityNatives::GetPosition(int * VM)
{

	return 1;
}


int	CEntityNatives::SetRotation(int * VM)
{

	return 1;
}

int	CEntityNatives::GetRotation(int * VM)
{

	return 1;
}


int	CEntityNatives::SetMoveSpeed(int * VM)
{

	return 1;
}

int	CEntityNatives::GetMoveSpeed(int * VM)
{

	return 1;
}


int	CEntityNatives::SetTurnSpeed(int * VM)
{

	return 1;
}

int	CEntityNatives::GetTurnSpeed(int * VM)
{

	return 1;
}
