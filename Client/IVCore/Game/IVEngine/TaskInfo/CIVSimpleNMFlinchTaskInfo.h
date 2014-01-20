#ifndef CIVSimpleNMFlinchTaskInfo_h
#define CIVSimpleNMFlinchTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMFlinchTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleNMFlinchTaskInfo();
};


class CIVSimpleNMFlinchTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMFlinchTaskInfo();
	~CIVSimpleNMFlinchTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMFlinchTaskInfo_h