#ifndef CComplexClimbIntoVehicleTaskInfo_h
#define CComplexClimbIntoVehicleTaskInfo_h

#include "CStatusTaskInfo.h"

_GAME_BEGIN

class IComplexClimbIntoVehicleTaskInfo : public IStatusTaskInfo
{
public:
	virtual ~IComplexClimbIntoVehicleTaskInfo();	
};

class CComplexClimbIntoVehicleTaskInfo : public CStatusTaskInfo
{
public:
	CComplexClimbIntoVehicleTaskInfo();
	~CComplexClimbIntoVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexClimbIntoVehicleTaskInfo_h
