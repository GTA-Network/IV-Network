#ifndef CSimpleNMJumpRollTaskInfo_h
#define CSimpleNMJumpRollTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMJumpRollTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMJumpRollTaskInfo();
};

class CSimpleNMJumpRollTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMJumpRollTaskInfo();
	~CSimpleNMJumpRollTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMJumpRollTaskInfo_h
