#ifndef CSitDownIdleThenStandTaskInfo_h
#define CSitDownIdleThenStandTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISitDownIdleThenStandTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISitDownIdleThenStandTaskInfo();
};

class CSitDownIdleThenStandTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSitDownIdleThenStandTaskInfo();
	~CSitDownIdleThenStandTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSitDownIdleThenStandTaskInfo_h
