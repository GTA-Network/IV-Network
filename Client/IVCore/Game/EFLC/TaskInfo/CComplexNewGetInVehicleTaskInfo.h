#ifndef CComplexNewGetInVehicleTaskInfo_h
#define CComplexNewGetInVehicleTaskInfo_h

#include "CVehicleTaskInfo.h"

_GAME_BEGIN

class IComplexNewGetInVehicleTaskInfo : public IVehicleTaskInfo
{
public:
	virtual ~IComplexNewGetInVehicleTaskInfo();	
};

class CComplexNewGetInVehicleTaskInfo : public CVehicleTaskInfo
{
public:
	CComplexNewGetInVehicleTaskInfo();
	~CComplexNewGetInVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexNewGetInVehicleTaskInfo_h
