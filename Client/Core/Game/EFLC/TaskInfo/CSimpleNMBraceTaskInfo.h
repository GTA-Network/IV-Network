#ifndef CSimpleNMBraceTaskInfo_h
#define CSimpleNMBraceTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class ISimpleNMBraceTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~ISimpleNMBraceTaskInfo();
};

class CSimpleNMBraceTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CSimpleNMBraceTaskInfo();
	~CSimpleNMBraceTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CSimpleNMBraceTaskInfo_h
