#ifndef CIVSimpleSidewaysDiveTaskInfo_h
#define CIVSimpleSidewaysDiveTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleSidewaysDiveTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleSidewaysDiveTaskInfo();
};

class CIVSimpleSidewaysDiveTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleSidewaysDiveTaskInfo();
	~CIVSimpleSidewaysDiveTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleSidewaysDiveTaskInfo_h
