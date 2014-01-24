#ifndef CSimpleThrowProjectileInfo_h
#define CSimpleThrowProjectileInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleThrowProjectileInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleThrowProjectileInfo();
};

class CSimpleThrowProjectileInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleThrowProjectileInfo();
	~CSimpleThrowProjectileInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleThrowProjectileInfo_h
