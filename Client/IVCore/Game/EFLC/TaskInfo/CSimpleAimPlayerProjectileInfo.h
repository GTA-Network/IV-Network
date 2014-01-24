#ifndef CSimpleAimPlayerProjectileInfo_h
#define CSimpleAimPlayerProjectileInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleAimPlayerProjectileInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleAimPlayerProjectileInfo();
};

class CSimpleAimPlayerProjectileInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleAimPlayerProjectileInfo();
	~CSimpleAimPlayerProjectileInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleAimPlayerProjectileInfo_h
