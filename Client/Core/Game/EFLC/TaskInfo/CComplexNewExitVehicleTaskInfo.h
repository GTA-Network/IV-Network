#ifndef CComplexNewExitVehicleTaskInfo_h
#define CComplexNewExitVehicleTaskInfo_h

#include "CVehicleTaskInfo.h"

_GAME_BEGIN

class IComplexNewExitVehicleTaskInfo : public IVehicleTaskInfo
{
public:
	virtual ~IComplexNewExitVehicleTaskInfo();
};


class CComplexNewExitVehicleTaskInfo : public CVehicleTaskInfo
{
public:
	CComplexNewExitVehicleTaskInfo();
	~CComplexNewExitVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexNewExitVehicleTaskInfo_h
