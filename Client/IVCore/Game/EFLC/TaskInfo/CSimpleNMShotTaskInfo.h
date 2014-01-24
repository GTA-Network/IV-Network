#ifndef CSimpleNMShotTaskInfo_h
#define CSimpleNMShotTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMShotTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMShotTaskInfo();
};

class CSimpleNMShotTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMShotTaskInfo();
	~CSimpleNMShotTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMShotTaskInfo_h
