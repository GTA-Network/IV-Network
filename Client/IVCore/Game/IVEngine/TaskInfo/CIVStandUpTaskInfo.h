#ifndef CIVStandUpTaskInfo_h
#define CIVStandUpTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVStandUpTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVStandUpTaskInfo();
};

class CIVStandUpTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVStandUpTaskInfo();
	~CIVStandUpTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVStandUpTaskInfo_h