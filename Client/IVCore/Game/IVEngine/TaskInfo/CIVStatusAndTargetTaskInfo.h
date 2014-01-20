#ifndef CIVStatusAndTargetTaskInfo_h
#define CIVStatusAndTargetTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVStatusAndTargetTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVStatusAndTargetTaskInfo();
	DWORD	m_dwStatus;
};

class CIVStatusAndTargetTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVStatusAndTargetTaskInfo();
	~CIVStatusAndTargetTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVStatusAndTargetTaskInfo_h