#ifndef CIVDieInfo_h
#define CIVDieInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVDieInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVDieInfo();
};

class CIVDieInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVDieInfo();
	~CIVDieInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVDieInfo_h