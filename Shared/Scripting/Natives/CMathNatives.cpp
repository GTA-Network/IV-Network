//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CMathNatives.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>, ApocKalipsS <apockalipss@hotmail.fr>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CMathNatives.h"

#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>

void CMathNatives::Register(CScriptVM * pVM)
{
	pVM->RegisterFunction("getDistanceBetweenPoints2D", GetDistanceBetweenPoints2D);
	pVM->RegisterFunction("getDistanceBetweenPoints3D", GetDistanceBetweenPoints3D);
	pVM->RegisterFunction("isPointInCircle", IsPointInCircle);
	pVM->RegisterFunction("isPointInTube", IsPointInTube);
	pVM->RegisterFunction("isPointInBall", IsPointInBall);
	pVM->RegisterFunction("isPointInArea", IsPointInArea);
	pVM->RegisterFunction("isPointInCuboid", IsPointInCuboid);
	pVM->RegisterFunction("isPointInPolygon", IsPointInPolygon);
}

int CMathNatives::GetDistanceBetweenPoints2D(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	pVM->ResetStackIndex();

	float x, y, xx, yy;

	pVM->Pop(x);
	pVM->Pop(y);
	pVM->Pop(xx);
	pVM->Pop(yy);

	pVM->Push(Math::GetDistanceBetweenPoints2D(x, y, xx, yy));

	pVM->ResetStackIndex();

	return 1;
}

int CMathNatives::GetDistanceBetweenPoints3D(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	pVM->ResetStackIndex();

	float x, y, z, xx, yy, zz;

	pVM->Pop(x);
	pVM->Pop(y);
	pVM->Pop(z);
	pVM->Pop(xx);
	pVM->Pop(yy);
	pVM->Pop(zz);

	pVM->Push(Math::GetDistanceBetweenPoints3D(x, y, z, xx, yy, zz));

	pVM->ResetStackIndex();

	return 1;
}

int CMathNatives::IsPointInCircle(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	pVM->ResetStackIndex();

	float x, y, xx, yy, radius;

	pVM->Pop(x);
	pVM->Pop(y);
	pVM->Pop(xx);
	pVM->Pop(yy);
	pVM->Pop(radius);

	pVM->Push(Math::IsPointInCircle(x, y, radius, xx, yy));

	pVM->ResetStackIndex();

	return 1;
}

int CMathNatives::IsPointInTube(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	pVM->ResetStackIndex();

	float tubex, tubey, tubez, tubeheight, tuberadius, x, y, z;

	pVM->Pop(tubex);
	pVM->Pop(tubey);
	pVM->Pop(tubez);
	pVM->Pop(tubeheight);
	pVM->Pop(tuberadius);
	pVM->Pop(x);
	pVM->Pop(y);
	pVM->Pop(z);

	pVM->Push(Math::IsPointInTube(tubex, tubey, tubez, tubeheight, tuberadius, x, y, z));

	pVM->ResetStackIndex();

	return 1;
}

int CMathNatives::IsPointInBall(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	pVM->ResetStackIndex();

	float x, y, z, xx, yy, zz, radius;

	pVM->Pop(x);
	pVM->Pop(y);
	pVM->Pop(z);
	pVM->Pop(xx);
	pVM->Pop(yy);
	pVM->Pop(zz);
	pVM->Pop(radius);

	pVM->Push(Math::IsPointInBall(x, y, z, radius, xx, yy, zz));

	pVM->ResetStackIndex();

	return 1;
}

int CMathNatives::IsPointInArea(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	pVM->ResetStackIndex();

	float areax, areay, areaxx, areayy, pointx, pointy;

	pVM->Pop(areax);
	pVM->Pop(areay);
	pVM->Pop(areaxx);
	pVM->Pop(areayy);
	pVM->Pop(pointx);
	pVM->Pop(pointy);

	pVM->Push(Math::IsPointInArea(areax, areay, areaxx, areayy, pointx, pointy));

	pVM->ResetStackIndex();

	return 1;
}

int CMathNatives::IsPointInCuboid(int * VM)
{
	GET_SCRIPT_VM_SAFE;
	pVM->ResetStackIndex();

	float areax, areay, areaz, areaxx, areayy, areazz, pointx, pointy, pointz;

	pVM->Pop(areax);
	pVM->Pop(areay);
	pVM->Pop(areaz);
	pVM->Pop(areaxx);
	pVM->Pop(areayy);
	pVM->Pop(areazz);
	pVM->Pop(pointx);
	pVM->Pop(pointy);
	pVM->Pop(pointz);

	pVM->Push(Math::IsPointInCuboid(areax, areay, areaz, areaxx, areayy, areazz, pointx, pointy, pointz));

	pVM->ResetStackIndex();

	return 1;
}

int CMathNatives::IsPointInPolygon(int * VM)
{
	// TODO

	return 1;
}