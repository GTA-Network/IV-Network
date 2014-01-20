#ifndef CIVSimpleThrowProjectileInfo_h
#define CIVSimpleThrowProjectileInfo_h

#include "CIVTaskInfoWithCloneTask.h"

class IVSimpleThrowProjectileInfo : public IVTaskInfoWithCloneTask
{
public:
	virtual ~IVSimpleThrowProjectileInfo();
};

class CIVSimpleThrowProjectileInfo : public CIVTaskInfoWithCloneTask
{
public:
	CIVSimpleThrowProjectileInfo();
	~CIVSimpleThrowProjectileInfo();

	bool Serialize(RakNet::BitStream * pBitStream);
	bool Deserialize(RakNet::BitStream * pBitStream);	
};

#endif // CIVSimpleThrowProjectileInfo_h