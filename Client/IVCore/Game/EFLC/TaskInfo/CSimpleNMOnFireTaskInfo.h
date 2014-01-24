#ifndef CSimpleNMOnFireTaskInfo_h
#define CSimpleNMOnFireTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMOnFireTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMOnFireTaskInfo();
};

class CSimpleNMOnFireTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMOnFireTaskInfo();
	~CSimpleNMOnFireTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMOnFireTaskInfo_h
