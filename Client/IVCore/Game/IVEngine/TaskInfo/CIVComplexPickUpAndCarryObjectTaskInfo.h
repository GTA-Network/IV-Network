#ifndef CIVComplexPickUpAndCarryObjectTaskInfo_h
#define CIVComplexPickUpAndCarryObjectTaskInfo_h

#include "CIVStatusAndTargetTaskInfo.h"

class IVComplexPickUpAndCarryObjectTaskInfo : public IVStatusAndTargetTaskInfo
{
public:
	~IVComplexPickUpAndCarryObjectTaskInfo();
};

class CIVComplexPickUpAndCarryObjectTaskInfo : public CIVStatusAndTargetTaskInfo
{
public:
	CIVComplexPickUpAndCarryObjectTaskInfo();
	~CIVComplexPickUpAndCarryObjectTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexPickUpAndCarryObjectTaskInfo_h