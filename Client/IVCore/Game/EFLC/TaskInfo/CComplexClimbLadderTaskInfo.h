#ifndef CComplexClimbLadderTaskInfo_h
#define CComplexClimbLadderTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexClimbLadderTaskInfo : public ITaskInfoWithCloneTask
{
public:
	bool isClimbingUp;
	bool isClimbingDown;
	bool isSlidingDown;

	virtual ~IComplexClimbLadderTaskInfo();
};

class CComplexClimbLadderTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexClimbLadderTaskInfo();
	~CComplexClimbLadderTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexClimbLadderTaskInfo_h
