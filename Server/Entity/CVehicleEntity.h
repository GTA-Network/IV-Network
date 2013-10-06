//========= IV: Network - https://github.com/GTA-Network/IV-Network ============
//
// File: CVehicleEntity.h
// Project: Server.Core
// Author: xForce
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CVehicleEntity_h
#define CVehicleEntity_h

#include "CNetworkEntity.h"

class CVehicleEntity : public CNetworkEntity
{
private:

public:
	CVehicleEntity();
	~CVehicleEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}
};

class CScriptVehicle : public CScriptEntity
{
public:
	CScriptVehicle() { SetEntity(new CVehicleEntity); };
	~CScriptVehicle() { delete GetEntity(); };

	virtual const char* GetScriptClassName() { return "CVehicleEntity"; }
};

#endif // CVehicleEntity_h