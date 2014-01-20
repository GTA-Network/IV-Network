#ifndef CIVSitIdleTaskInfo_h
#define CIVSitIdleTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSitIdleTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSitIdleTaskInfo();
};


class CIVSitIdleTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSitIdleTaskInfo();
	~CIVSitIdleTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSitIdleTaskInfo_h