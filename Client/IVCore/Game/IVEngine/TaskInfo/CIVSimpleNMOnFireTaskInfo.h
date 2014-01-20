#ifndef CIVSimpleNMOnFireTaskInfo_h
#define CIVSimpleNMOnFireTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMOnFireTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleNMOnFireTaskInfo();
};

class CIVSimpleNMOnFireTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMOnFireTaskInfo();
	~CIVSimpleNMOnFireTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMOnFireTaskInfo_h