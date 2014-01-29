#ifndef CStandUpTaskInfo_h
#define CStandUpTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IStandUpTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IStandUpTaskInfo();
};

class CStandUpTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CStandUpTaskInfo();
	~CStandUpTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CStandUpTaskInfo_h
