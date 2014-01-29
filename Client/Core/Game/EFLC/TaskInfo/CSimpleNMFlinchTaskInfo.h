#ifndef CSimpleNMFlinchTaskInfo_h
#define CSimpleNMFlinchTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMFlinchTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMFlinchTaskInfo();
};


class CSimpleNMFlinchTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMFlinchTaskInfo();
	~CSimpleNMFlinchTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMFlinchTaskInfo_h
