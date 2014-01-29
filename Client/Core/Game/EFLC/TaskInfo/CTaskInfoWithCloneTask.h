#ifndef CTaskInfoWithCloneTask_h
#define CTaskInfoWithCloneTask_h

#include "CTaskInfo.h"

_GAME_BEGIN

class ITaskInfoWithCloneTask : public ITaskInfo
{
public:
	virtual ~ITaskInfoWithCloneTask();
	DWORD	field_14;
};

class CTaskInfoWithCloneTask : public CTaskInfo
{
public:
	CTaskInfoWithCloneTask();
	~CTaskInfoWithCloneTask();
	
	virtual bool Serialize(RakNet::BitStream * pBitStream);
	virtual bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CTaskInfoWithCloneTask_h