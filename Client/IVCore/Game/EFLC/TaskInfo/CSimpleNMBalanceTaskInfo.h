#ifndef CSimpleNMBalanceTaskInfo_h
#define CSimpleNMBalanceTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMBalanceTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMBalanceTaskInfo();
};

class CSimpleNMBalanceTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMBalanceTaskInfo();
	~CSimpleNMBalanceTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMBalanceTaskInfo_h
