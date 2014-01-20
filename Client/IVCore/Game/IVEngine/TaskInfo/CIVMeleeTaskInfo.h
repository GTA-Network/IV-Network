#ifndef CIVMeleeTaskInfo_h
#define CIVMeleeTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVMeleeTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVMeleeTaskInfo();
};


class CIVMeleeTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVMeleeTaskInfo();
	CIVMeleeTaskInfo(IVMeleeTaskInfo* taskInfo);

	~CIVMeleeTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);
};

#endif // CIVComplexJumpTaskInfo_h