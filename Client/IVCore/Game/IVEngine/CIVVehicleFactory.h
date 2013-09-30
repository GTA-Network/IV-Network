//================= IV:Network - https://github.com/GTA-Network/IV-Network =================
//
// File: CIVVehicleFactory.h
// Project: Client.Core
// Author: FRi<FRi.developing@gmail.com>
// License: See LICENSE in root directory
//
//==========================================================================================

#ifndef CIVVehicleFactory_h
#define CIVVehicleFactory_h

#include "CIVVehicle.h"
#include <Game/CGame.h>
#include <Game/COffsets.h>
#include <CLogFile.h>

class IVVehicleFactory
{
public:
	virtual 			~IVVehicleFactory();
	virtual IVVehicle*	Create(int modelIndex, int creator, int a3, int network);
	virtual int 		Delete(IVVehicle*);
	virtual IVVehicle*	Get_0(int a1); //Get index=0 
	virtual IVVehicle*	Get(int a1);
	virtual bool		m14(int a1, int a2, int a3);
};

class IVVehicleFactoryNY : public IVVehicleFactory
{

};

#endif // CIVVehicleFactory_h