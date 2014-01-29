#ifndef CSimpleNMExplosionTaskInfo_h
#define CSimpleNMExplosionTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMExplosionTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMExplosionTaskInfo();
};


class CSimpleNMExplosionTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMExplosionTaskInfo();
	~CSimpleNMExplosionTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMExplosionTaskInfo_h
