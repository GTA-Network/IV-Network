#ifndef CStatusAndTargetTaskInfo_h
#define CStatusAndTargetTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IStatusAndTargetTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IStatusAndTargetTaskInfo();
	DWORD	m_dwStatus;
};

class CStatusAndTargetTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CStatusAndTargetTaskInfo();
	~CStatusAndTargetTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CStatusAndTargetTaskInfo_h
