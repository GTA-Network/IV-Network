#ifndef CIVComplexOpenVehicleDoorTaskInfo_h
#define CIVComplexOpenVehicleDoorTaskInfo_h

#include "CIVStatusTaskInfo.h"

class IVComplexOpenVehicleDoorTaskInfo : public IVStatusTaskInfo
{
public:
	virtual ~IVComplexOpenVehicleDoorTaskInfo();
};

class CIVComplexOpenVehicleDoorTaskInfo : public CIVStatusTaskInfo
{
public:
	CIVComplexOpenVehicleDoorTaskInfo();
	~CIVComplexOpenVehicleDoorTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexOpenVehicleDoorTaskInfo_h