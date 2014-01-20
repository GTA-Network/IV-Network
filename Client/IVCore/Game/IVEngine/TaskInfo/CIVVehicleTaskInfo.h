#ifndef CIVVehicleTaskInfo_h
#define CIVVehicleTaskInfo_h

#include "CIVStatusAndTargetTaskInfo.h"

class IVVehicleTaskInfo : public IVStatusAndTargetTaskInfo
{
public:
	virtual ~IVVehicleTaskInfo();
};

class CIVVehicleTaskInfo : public CIVStatusAndTargetTaskInfo
{
public:
	CIVVehicleTaskInfo();
	~CIVVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVVehicleTaskInfo_h