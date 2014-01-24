#ifndef CSimpleSidewaysDiveTaskInfo_h
#define CSimpleSidewaysDiveTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleSidewaysDiveTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleSidewaysDiveTaskInfo();
};

class CSimpleSidewaysDiveTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleSidewaysDiveTaskInfo();
	~CSimpleSidewaysDiveTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleSidewaysDiveTaskInfo_h
