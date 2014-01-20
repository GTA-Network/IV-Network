#ifndef CIVComplexClearVehicleSeatTaskInfo_h
#define CIVComplexClearVehicleSeatTaskInfo_h

#include "CIVStatusTaskInfo.h"

class IVComplexClearVehicleSeatTaskInfo : public IVStatusTaskInfo
{
public:
	virtual ~IVComplexClearVehicleSeatTaskInfo();
};

class CIVComplexClearVehicleSeatTaskInfo : public CIVStatusTaskInfo
{
public:
	CIVComplexClearVehicleSeatTaskInfo();
	~CIVComplexClearVehicleSeatTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexClearVehicleSeatTaskInfo_h