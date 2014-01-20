#ifndef CIVComplexClimbLadderTaskInfo_h
#define CIVComplexClimbLadderTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexClimbLadderTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	bool isClimbingUp;
	bool isClimbingDown;
	bool isSlidingDown;

	virtual ~IVComplexClimbLadderTaskInfo();
};

class CIVComplexClimbLadderTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexClimbLadderTaskInfo();
	~CIVComplexClimbLadderTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexClimbLadderTaskInfo_h