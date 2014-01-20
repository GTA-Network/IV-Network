#ifndef CIVSimpleNMExplosionTaskInfo_h
#define CIVSimpleNMExplosionTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMExplosionTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	~IVSimpleNMExplosionTaskInfo();
};


class CIVSimpleNMExplosionTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMExplosionTaskInfo();
	~CIVSimpleNMExplosionTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMExplosionTaskInfo_h