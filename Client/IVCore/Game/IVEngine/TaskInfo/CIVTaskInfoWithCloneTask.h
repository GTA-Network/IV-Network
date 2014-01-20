#ifndef CIVTaskInfoWithCloneTask_h
#define CIVTaskInfoWithCloneTask_h

#include "CIVTaskInfo.h"

class IVTaskInfoWithCloneTask : public IVTaskInfo
{
public:
	virtual ~IVTaskInfoWithCloneTask();
	DWORD	field_14;
};

class CIVTaskInfoWithCloneTask : public CIVTaskInfo
{
public:
	CIVTaskInfoWithCloneTask();
	~CIVTaskInfoWithCloneTask();
	
	virtual bool Serialize(RakNet::BitStream * pBitStream);
	virtual bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVTaskInfoWithCloneTask_h