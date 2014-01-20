#ifndef CIVSimpleNMHighFallTaskInfo_h
#define CIVSimpleNMHighFallTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMHighFallTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleNMHighFallTaskInfo();
};

class CIVSimpleNMHighFallTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMHighFallTaskInfo();
	~CIVSimpleNMHighFallTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMHighFallTaskInfo_h