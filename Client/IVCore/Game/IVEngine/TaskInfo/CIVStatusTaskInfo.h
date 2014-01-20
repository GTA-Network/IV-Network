#ifndef CIVStatusTaskInfo_h
#define CIVStatusTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVStatusTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVStatusTaskInfo();
	DWORD	m_dwStatus;
};

class CIVStatusTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVStatusTaskInfo();
	~CIVStatusTaskInfo();
	
	virtual bool Serialize(RakNet::BitStream * pBitStream);
	virtual bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVStatusTaskInfo_h