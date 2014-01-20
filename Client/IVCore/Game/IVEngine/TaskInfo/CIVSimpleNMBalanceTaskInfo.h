#ifndef CIVSimpleNMBalanceTaskInfo_h
#define CIVSimpleNMBalanceTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMBalanceTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleNMBalanceTaskInfo();
};

class CIVSimpleNMBalanceTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMBalanceTaskInfo();
	~CIVSimpleNMBalanceTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMBalanceTaskInfo_h