#ifndef CIVSimpleNMShotTaskInfo_h
#define CIVSimpleNMShotTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMShotTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleNMShotTaskInfo();
};

class CIVSimpleNMShotTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMShotTaskInfo();
	~CIVSimpleNMShotTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMShotTaskInfo_h