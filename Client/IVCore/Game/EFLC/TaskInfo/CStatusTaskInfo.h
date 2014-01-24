#ifndef CStatusTaskInfo_h
#define CStatusTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IStatusTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IStatusTaskInfo();
	DWORD	m_dwStatus;
};

class CStatusTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CStatusTaskInfo();
	~CStatusTaskInfo();
	
	virtual bool Serialize(RakNet::BitStream * pBitStream);
	virtual bool Deserialize(RakNet::BitStream * pBitStream);
};

_GAME_END

#endif // CStatusTaskInfo_h