#ifndef CComplexOpenVehicleDoorTaskInfo_h
#define CComplexOpenVehicleDoorTaskInfo_h

#include "CStatusTaskInfo.h"

_GAME_BEGIN

class IComplexOpenVehicleDoorTaskInfo : public IStatusTaskInfo
{
public:
	virtual ~IComplexOpenVehicleDoorTaskInfo();
};

class CComplexOpenVehicleDoorTaskInfo : public CStatusTaskInfo
{
public:
	CComplexOpenVehicleDoorTaskInfo();
	~CComplexOpenVehicleDoorTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexOpenVehicleDoorTaskInfo_h
