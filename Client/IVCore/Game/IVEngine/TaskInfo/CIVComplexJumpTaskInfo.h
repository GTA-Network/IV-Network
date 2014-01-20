#ifndef CIVComplexJumpTaskInfo_h
#define CIVComplexJumpTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexJumpTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVComplexJumpTaskInfo();
	bool m_bHasPedJumped;
	bool m_bJumpOnSpot;
	bool m_bForceInAir;
};

class CIVComplexJumpTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexJumpTaskInfo();
	CIVComplexJumpTaskInfo(IVComplexJumpTaskInfo* taskInfo);

	~CIVComplexJumpTaskInfo();
	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVComplexJumpTaskInfo_h