#ifndef CComplexGangDrivebyTaskInfo_h
#define CComplexGangDrivebyTaskInfo_h

#include "CTaskInfoWithCloneTask.h"

_GAME_BEGIN

class IComplexGangDrivebyTaskInfo : public ITaskInfoWithCloneTask
{
public:
	virtual ~IComplexGangDrivebyTaskInfo();
};

class CComplexGangDrivebyTaskInfo : public CTaskInfoWithCloneTask
{
public:
	CComplexGangDrivebyTaskInfo();
	~CComplexGangDrivebyTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

_GAME_END

#endif // CComplexGangDrivebyTaskInfo_h
