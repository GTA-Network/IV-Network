#ifndef CComplexJumpTaskInfo_h
#define CComplexJumpTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexJumpTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IComplexJumpTaskInfo();
	bool m_bHasPedJumped;
	bool m_bJumpOnSpot;
	bool m_bForceInAir;
};

class CComplexJumpTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexJumpTaskInfo();
	CComplexJumpTaskInfo(IComplexJumpTaskInfo* taskInfo);

	~CComplexJumpTaskInfo();
	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CComplexJumpTaskInfo_h
