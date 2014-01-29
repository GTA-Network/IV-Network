#ifndef CComplexClearVehicleSeatTaskInfo_h
#define CComplexClearVehicleSeatTaskInfo_h

#include "CStatusTaskInfo.h"

_GAME_BEGIN

class IComplexClearVehicleSeatTaskInfo : public IStatusTaskInfo
{
public:
	virtual ~IComplexClearVehicleSeatTaskInfo();
};

class CComplexClearVehicleSeatTaskInfo : public CStatusTaskInfo
{
public:
	CComplexClearVehicleSeatTaskInfo();
	~CComplexClearVehicleSeatTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexClearVehicleSeatTaskInfo_h