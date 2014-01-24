#ifndef CComplexPickUpAndCarryObjectTaskInfo_h
#define CComplexPickUpAndCarryObjectTaskInfo_h

#include "CStatusAndTargetTaskInfo.h"

_GAME_BEGIN

class IComplexPickUpAndCarryObjectTaskInfo : public IStatusAndTargetTaskInfo
{
public:
	~IComplexPickUpAndCarryObjectTaskInfo();
};

class CComplexPickUpAndCarryObjectTaskInfo : public CStatusAndTargetTaskInfo
{
public:
	CComplexPickUpAndCarryObjectTaskInfo();
	~CComplexPickUpAndCarryObjectTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexPickUpAndCarryObjectTaskInfo_h
