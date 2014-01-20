#ifndef CIVComplexGangDrivebyTaskInfo_h
#define CIVComplexGangDrivebyTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVComplexGangDrivebyTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVComplexGangDrivebyTaskInfo();
};

class CIVComplexGangDrivebyTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVComplexGangDrivebyTaskInfo();
	~CIVComplexGangDrivebyTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVComplexGangDrivebyTaskInfo_h