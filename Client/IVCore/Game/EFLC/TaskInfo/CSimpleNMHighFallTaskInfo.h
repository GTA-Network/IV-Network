#ifndef CSimpleNMHighFallTaskInfo_h
#define CSimpleNMHighFallTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMHighFallTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMHighFallTaskInfo();
};

class CSimpleNMHighFallTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMHighFallTaskInfo();
	~CSimpleNMHighFallTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMHighFallTaskInfo_h
