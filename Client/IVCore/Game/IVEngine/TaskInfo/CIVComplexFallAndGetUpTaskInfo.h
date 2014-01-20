#ifndef CIVComplexFallAndGetUpTaskInfo_h
#define CIVComplexFallAndGetUpTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexFallAndGetUpTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVComplexFallAndGetUpTaskInfo();
};

class CIVComplexFallAndGetUpTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexFallAndGetUpTaskInfo();
	~CIVComplexFallAndGetUpTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexFallAndGetUpTaskInfo_h