#ifndef CScenarioTaskInfo_h
#define CScenarioTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IScenarioTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IScenarioTaskInfo();
};

class CScenarioTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CScenarioTaskInfo();
	~CScenarioTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CScenarioTaskInfo_h
