#ifndef CIVScenarioTaskInfo_h
#define CIVScenarioTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVScenarioTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVScenarioTaskInfo();
};

class CIVScenarioTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVScenarioTaskInfo();
	~CIVScenarioTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVScenarioTaskInfo_h