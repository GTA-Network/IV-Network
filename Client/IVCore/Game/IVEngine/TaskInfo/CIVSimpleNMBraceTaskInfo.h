#ifndef CIVSimpleNMBraceTaskInfo_h
#define CIVSimpleNMBraceTaskInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleNMBraceTaskInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleNMBraceTaskInfo();
};

class CIVSimpleNMBraceTaskInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleNMBraceTaskInfo();
	~CIVSimpleNMBraceTaskInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleNMBraceTaskInfo_h