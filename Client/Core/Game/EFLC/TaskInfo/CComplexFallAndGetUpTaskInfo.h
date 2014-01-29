#ifndef CComplexFallAndGetUpTaskInfo_h
#define CComplexFallAndGetUpTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexFallAndGetUpTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IComplexFallAndGetUpTaskInfo();
};

class CComplexFallAndGetUpTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexFallAndGetUpTaskInfo();
	~CComplexFallAndGetUpTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexFallAndGetUpTaskInfo_h
