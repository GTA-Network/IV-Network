#ifndef CIVComplexClimbIntoVehicleTaskInfo_h
#define CIVComplexClimbIntoVehicleTaskInfo_h

#include "CIVStatusTaskInfo.h"

class IVComplexClimbIntoVehicleTaskInfo : public IVStatusTaskInfo
{
public:
	virtual ~IVComplexClimbIntoVehicleTaskInfo();	
};

class CIVComplexClimbIntoVehicleTaskInfo : public CIVStatusTaskInfo
{
public:
	CIVComplexClimbIntoVehicleTaskInfo();
	~CIVComplexClimbIntoVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexClimbIntoVehicleTaskInfo_h