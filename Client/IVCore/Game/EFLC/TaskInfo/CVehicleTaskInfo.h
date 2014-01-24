#ifndef CVehicleTaskInfo_h
#define CVehicleTaskInfo_h

#include "CStatusAndTargetTaskInfo.h"

_GAME_BEGIN

class IVehicleTaskInfo : public IStatusAndTargetTaskInfo
{
public:
	virtual ~IVehicleTaskInfo();
};

class CVehicleTaskInfo : public CStatusAndTargetTaskInfo
{
public:
	CVehicleTaskInfo();
	~CVehicleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CVehicleTaskInfo_h
