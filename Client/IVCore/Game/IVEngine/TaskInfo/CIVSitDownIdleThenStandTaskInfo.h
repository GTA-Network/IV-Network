#ifndef CIVSitDownIdleThenStandTaskInfo_h
#define CIVSitDownIdleThenStandTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSitDownIdleThenStandTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSitDownIdleThenStandTaskInfo();
};

class CIVSitDownIdleThenStandTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSitDownIdleThenStandTaskInfo();
	~CIVSitDownIdleThenStandTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSitDownIdleThenStandTaskInfo_h