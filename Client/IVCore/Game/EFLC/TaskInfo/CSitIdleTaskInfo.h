#ifndef CSitIdleTaskInfo_h
#define CSitIdleTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISitIdleTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISitIdleTaskInfo();
};


class CSitIdleTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSitIdleTaskInfo();
	~CSitIdleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSitIdleTaskInfo_h
