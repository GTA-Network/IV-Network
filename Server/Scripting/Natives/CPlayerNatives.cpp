//========== IV:Multiplayer - https://github.com/IVMultiplayer/IVMultiplayer ==========
//
// File: CPlayerNatives.cpp
// Project: Server.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CPlayerNatives.h"
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include <CLogFile.h>

void CPlayerNatives::Register(CScriptVM * pVM)
{
	pVM->RegisterClassFunction("setArmour", SetArmour);
	pVM->RegisterClassFunction("getArmour", GetArmour);

	pVM->RegisterClassFunction("getClothes", GetClothes);
	pVM->RegisterClassFunction("setClothes", SetClothes);

	pVM->RegisterClassFunction("getColor", GetColor);
	pVM->RegisterClassFunction("setColor", SetColor);

	pVM->RegisterClassFunction("getDimension", GetDimension);
	pVM->RegisterClassFunction("setDimension", SetDimension);

	pVM->RegisterClassFunction("getHeading", GetHeading);
	pVM->RegisterClassFunction("setHeading", SetHeading);

	pVM->RegisterClassFunction("getHealth", GetHealth);
	pVM->RegisterClassFunction("setHealth", SetHealth);

	pVM->RegisterClassFunction("getModel", GetModel);
	pVM->RegisterClassFunction("setModel", SetModel);

	pVM->RegisterClassFunction("getName", GetName);
	pVM->RegisterClassFunction("setName", SetName);
}

int CPlayerNatives::GetArmour(int * VM)
{

	return 1;
}

int CPlayerNatives::SetArmour(int * VM)
{

	return 1;
}


int CPlayerNatives::GetClothes(int * VM)
{

	return 1;
}

int CPlayerNatives::SetClothes(int * VM)
{

	return 1;
}


int CPlayerNatives::GetColor(int * VM)
{

	return 1;
}

int CPlayerNatives::SetColor(int * VM)
{

	return 1;
}


int CPlayerNatives::GetDimension(int * VM)
{

	return 1;
}

int CPlayerNatives::SetDimension(int * VM)
{

	return 1;
}


int CPlayerNatives::GetHeading(int * VM)
{

	return 1;
}

int CPlayerNatives::SetHeading(int * VM)
{

	return 1;
}


int CPlayerNatives::GetHealth(int * VM)
{

	return 1;
}

int CPlayerNatives::SetHealth(int * VM)
{

	return 1;
}


int CPlayerNatives::GetModel(int * VM)
{
	
	return 1;
}

int CPlayerNatives::SetModel(int * VM)
{

	return 1;
}


int CPlayerNatives::GetName(int * VM)
{

	return 1;
}

int CPlayerNatives::SetName(int * VM)
{

	return 1;
}