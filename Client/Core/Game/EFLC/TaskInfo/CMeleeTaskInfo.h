#ifndef CMeleeTaskInfo_h
#define CMeleeTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IMeleeTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IMeleeTaskInfo();
};


class CMeleeTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CMeleeTaskInfo();
	CMeleeTaskInfo(IMeleeTaskInfo* taskInfo);

	~CMeleeTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CComplexJumpTaskInfo_h
