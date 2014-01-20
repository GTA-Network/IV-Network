#ifndef CIVSimpleNMJumpRollTaskInfo_h
#define CIVSimpleNMJumpRollTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMJumpRollTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleNMJumpRollTaskInfo();
};

class CIVSimpleNMJumpRollTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMJumpRollTaskInfo();
	~CIVSimpleNMJumpRollTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMJumpRollTaskInfo_h